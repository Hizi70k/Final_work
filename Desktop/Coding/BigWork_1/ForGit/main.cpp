#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<fstream>
#include<algorithm>
#include<conio.h>
#define cheat_ "Administrator"
#define abs( X )  ( X>0 ) ? X : -X

using namespace std;
enum level {boss=1,manager,normal};
const int no_object = -1;

class User;
class Goods;
int lvl ;
string file_name;

vector<int> query_cus(string);
vector<int> query_goods(string);


void macro(void);
int cash_stat(int level_);
void user_buy();
void user_deposit();

string login(string,int);	// p = password ,return name of the User
void get_lvl();
class User
{
	private:
		string name,phone;
		string encrypt_pswd;
		int wealth;
		static int name_num;
	public:
		User()	{
			name = "Unknown"+to_string(name_num);
			ID = 10000+(name_num++);
			wealth=0;
		}
		~User()	{	name_num--;	}
		int lvl = normal;
		int ID;
		string name_()
		{
			return name;
		}
		string pswd()
		{
			return encrypt_pswd;
		}
		void purchase_(Goods& , int&);
		void deposit_(int cash)
		{
			wealth = wealth + cash;
		}
		void chg_info();
		bool operator <(const User &a)
		{
			if(ID == a.ID) ID++;
			if(lvl != a.lvl ) return lvl < a.lvl;
			return ID < a.ID;
		}
		User operator=(const User &a)
		{
			lvl = a.lvl;
			ID = a.ID;
			name = a.name.substr();
			phone = a.phone.substr();
			encrypt_pswd =  a.encrypt_pswd.substr() ;
			wealth = a.wealth;
			return a;
		}
		int add_(int l = normal ,const string u_name = "" );

		friend ostream& operator<<(ostream&, User& pt );
		friend int cash_stat(int level_);

		void load_(ifstream &f_);
		void save_(ofstream &f_);
};

class Goods
{
	private:
		string name;
		int price,storage;
		static int name_num;
	public:
		Goods()		{	ID = 100000+(name_num++)*19 % 10000;	}
		~Goods()	{	name_num--;	}
		int ID;
		int add_();
		int sum_(int);
		int sold(int num_);
		void chg_info();
		string name_()	{	return name;	}
		bool operator <(const Goods a){
			if(ID == a.ID) ID++;
			return ID < a.ID;
		}
		Goods operator =(const Goods a){
			ID = a.ID;
			name = a.name.substr();
			price = a.price;
			storage = a.storage;
			return *this;
		}
		friend ostream& operator<<(ostream&, Goods& pt);
		void load_(ifstream &f_);
		void save_(ofstream &f_);
};
int num_cus,num_gds,dlt_;
User *cus;
Goods *gds;
// cus[0] is the user using it, so check idendity is necessary
int Get_Target_Customer(); // return subscript
int Get_Target_Goods();

int login( string );	// p = password ,return subscript of the User
int manager_login();	//return 1 when log as manager
// return who has the top privilege when many has same pswd

string encrypt(string s)  		// encrypt a string,maybe can be proved
{
	// notice that when using MD5 or HASH, Password as "" can't casually log in
	string ans;
	ans = s;
	for(int i=0 ; i<s.size() ; i++)	ans[i] = ans[i] ^ (32+i);
	return ans;
}
string lv_name(int a)  	// a DULL func
{
	if(a==1) return "Chief   ";
	if(a==2) return "Manager ";
	return "Customer";
}

int short_cmp(string input_string,string source_string)
{
	// notice that when source== "",it return 1 for any input
	return ( source_string.substr(0,input_string.size() ) ==  input_string);
}

string get_content(string &target)
{
	target = "";
	while( target=="" )	getline(cin,target);
	while( target[0] == ' ') target = target.substr(1);
	return target;
}
string login(string p,int user)  	 // p = password ,return name of the User
{
// for user[int] to login
//if cant sign in , return "error"
	int flag = 0;
	//backdoor:
	if(p == cheat_) flag =1;

	if( ( cus[user].pswd() ).size()<=1 )	flag =1;
	if( encrypt(p) == cus[user].pswd() )	flag =1;
	//if(flag)	lvl = cus[user].lvl;
	return (flag)?( cus[user].name_() ):("error");
}
int manager_login()
{
	string s;
	cout << "Please login as Manager.Password:";
	get_content(s);
	int oprtor;  // operator( literally )
	oprtor = login( s );
	if( cus[ oprtor ].lvl <=2  ){
		cout << "\t Log in Successfully with License\n";
		return 1;
	}
	return 0;
}
int login( string pswd )   // return subscript
{
	int ans = no_object;
	for(int i = 0; i< num_cus ; i++)
		if( login(pswd,i) !="error" )	{
			if(ans == no_object) ans = i;
			ans = ( cus[i].lvl < cus[ans].lvl ) ? i : ans ;
		}

	if( ans != no_object )cout << "\n\t login as:"<< cus[ans].name_() <<endl;
	return ans;
}
int create()
{
	cout << "\t Creating a new file\n";
	num_cus = 1;
	cus = new User[10];
	int a = cus[num_cus-1].add_(1,"Admin");
	cout <<"\n Administrator is added! \n";
	lvl = 1;
	return 1;
}


int User::name_num=1;
int Goods::name_num=1;

ostream& operator<<(ostream& ios, User& p )
{
	ios << "\t"<<lv_name(p.lvl)<<"\t" << p.ID <<"\t\t";
	ios << p.name <<"\t\t"<< p.wealth <<"\t\t"<< p.phone;
	return ios;
}
ostream& operator<<(ostream& ios, Goods& p)
{
	ios <<"\t"<< p.ID <<"\t "<< p.name <<"\t\t"<< p.price <<"\t"<< p.storage;
	return ios;
}

void print_cus(void)
{
	//print all
	sort( cus , cus+num_cus );
	cout <<"\n\t Number of Customers: "<< num_cus <<endl;
	cout <<"\tLevel\t\t ID\t\tName\t\tWealth\t\tPhone Number\n";
	for(int i = 0; i < num_cus ; i++) cout << cus[i] << endl;
}
void print_gds(void)
{
	//print all
	sort( gds , gds+num_gds );
	cout <<"\n\t Number of Goods: "<< num_gds <<endl;
	cout << "\t ID \t Name  \t\tPrice \tStorage \n";
	for(int i = 0; i<num_gds ; i++) cout << gds[i] << endl;
}
void print_cus( vector<int> arr )
{
	// to print  the list
	if(arr.size()==0){
		cout << "\n\tNo Such Customer!\n";
		return;
	}
	cout <<"\n\t Number of Customers: "<< arr.size()  <<endl;
	cout <<"\tLevel\t\t ID\t\tName\t\tWealth\t\tPhone Number\n";
	for(int i:arr) cout << cus[i] << endl;
}
void print_gds( vector<int> arr )
{
	if(arr.size()==0)	{
		cout << "\n\tNo Such Goods!\n";
		return;
	}
	//print the list
	cout <<"\n\t Number of Goods: "<< arr.size() <<endl;
	cout << "\t ID \t Name\t\tPrice\tStorage \n";
	for(int i:arr) cout << gds[i] << endl;
}
void print_cus( int N ){
	print_cus( vector<int> (1,N) );
}
void print_gds( int N ){
	print_gds( vector<int> (1,N) );
}
// IO part
int save_gds()
{
	ofstream  fout;
	fout.open(file_name+"_goods.sp",ios::out);
	fout << num_gds <<endl;
	for(int i = 0; i<num_gds; i++)	gds[i].save_( fout );
	fout.close();
	return 0;
}
int save_cus()
{
	ofstream  fout;
	fout.open(file_name+"_user.sp",ios::out);
	fout << num_cus << " " << dlt_ <<endl;
	for(int i = 0; i < num_cus ; i++ )	cus[i].save_( fout );
	fout.close();
	return 0;
}
int load_gds()
{
	ifstream  fin;
	fin.open(file_name+"_goods.sp",ios::in);
	if(!fin)
	{
		cout << "\t Can't find goods file!\n";
		return 1;
	}
	fin >> num_gds;
	gds = new Goods[ num_gds + 2 ];
	for(int i = 0; i<num_gds; i++)	gds[i].load_( fin );
	fin.close();
	return 0;
}
int load_cus()
{
	ifstream  fin;
	fin.open(file_name+"_user.sp",ios::in);
	if(!fin)
	{
		cout << "\t Can't find customer file!\n";
		return 1;
	}
	fin >> num_cus >> dlt_;
	cus = new User[ num_cus + 2 ];
	for(int i = 0; i < num_cus ; i++ )	cus[i].load_( fin );
	fin.close();
	return 0;
}

void Goods::load_(ifstream &fin)
{
	fin >> ID >> name;
	//getline(fin,name,'\n');
	fin >> price >> storage;
}
void Goods::save_(ofstream &fout )
{
	fout << ID <<"\n"<< name <<endl;
	fout << price<<" "<<storage<<endl;
}
void User::load_(ifstream &fin)
{
	fin >> lvl >> ID ;
	// notice that u need to read a "\n" ,btw
	getline(fin,name,'\n');
	getline(fin,name,'\n');
	getline(fin,encrypt_pswd,'\n');
	fin >> wealth;
	getline(fin, phone );
	while(phone[0] == ' ') phone = phone.substr(1);
}
void User::save_(ofstream &fout)
{
	fout << lvl <<" " << ID <<endl;
	fout << name <<endl;
	fout << encrypt_pswd <<endl;
	fout << wealth << " " << phone <<endl;
	//cout << encrypt_pswd<<endl;
}
//IO Part Completed

int User::add_(int level_,const string u_name)
{
	int rpt=0,flag = 0;
	lvl = level_;
	string a,b;
	a = u_name;
	b = "-";
	// notice that u need to read a "\n"
	// rpt means repeat times
	if(u_name == ""){
		flag = 1;
		cout << "\t Name:";
		while( rpt++ <2 && a=="")getline(cin,a);
		if( a=="" )	a = "Unknown_"+to_string(name_num);
		name = a;
	}	// do not use content because use Unknown_%d
	name = a;
	while(a!=b && cin){
		cout << "\n\t Input password:";
		getline(cin, a);
		cout << "\t Confirm password:";
		getline(cin, b);
		if( !(a==b) )
			cout << "\t Different password!\n\t Please Try again";
	}
	encrypt_pswd = encrypt(a);
	cout << "\t Password set Successfully!\n";

	if(flag){
		cout << "\t Input the wealth: ";
		cin >> wealth;
		cout << "\t Input Phone Number: ";
		cin >> phone;
	}

	cout << "\t New user is added Successfully!\n";
	return 0;
}
int Goods::add_()
{
	int rpt=0;
	cout << "\t Name:";
	get_content(name);
	cout << "\t Input price:";
	cin >> price;
	price = abs(price); 
	cout << "\t Input storage:";
	cin >> storage;
	storage = abs(storage);
	return 0;
}
void add_cus()
{
	User *cch;
	cch = new User[2 + num_cus ];
	for(int i=0 ; i<num_cus ; i++ ) cch[i]=cus[i];
	if(num_cus)	delete[]cus;
	cus = cch;	cch = nullptr;

	cout << "\t please input your information below\n";
	cout << "Input the privilege (1 for top, 2 for manager,others for customer)";
	char an;	cin >> an;

	if( (an-49)*(an-50)!=0  || lvl == 3  ) an = 51 ;  // asc('1') = 49
	// when the shop has no manager, u cant create one
	cout << "\tAdding a "<< lv_name( an - 48 );
	cus[num_cus++] .add_( an - 48 );
}
void add_goods()
{
	Goods *cch;
	cch = new Goods[2 + num_gds ];
	for(int i = 0; i<num_gds; i++) cch[i] = gds[i];
	if(num_gds) delete[]gds;
	gds = cch;
	cch = nullptr;

	gds[num_gds++].add_();
}

void dlt_cus()
{
	if(num_cus == 0 )
	{
		cout << "\n\tNo Customers!\n";
		return;
	}
	if( manager_login() == 0 ) return;
	int sub = Get_Target_Customer(); // return subscript

	if(sub != no_object )
	{
		for(int i = sub+1 ; i<num_cus ; i++ ) cus[ i-1 ] = cus[i];

		num_cus--;
		dlt_++;
		//if( sub == 0 ) lvl = cus[0].lvl;
		cout << "delete done.\n";
		lvl = cus[0].lvl;
	}
	//print result
	cout << "Rest:\t";
	print_cus();
}

void dlt_goods()
{
	if(num_gds == 0 )
	{
		cout << "\n\tNo Goods!\n";
		return;
	}
	if( manager_login() == 0 ) return;
	int sub = Get_Target_Goods(); // return subscript
	if(sub == no_object ) return;

	for(int i = sub+1 ; i<num_gds ; i++ ) gds[ i-1 ] = gds[i];
	num_gds--;

	cout << "Rest:\t";
	print_gds();
}
// Add and Delete Part Completed

void chg_cus_info()
{
	int sub = Get_Target_Customer();
	if(sub == no_object) return;

	string s,s2;
	cout << "\nPlease check your identity.Password:";
	getline(cin,s);
	if( login(s,sub) != "error" )
		cus[sub].chg_info();
	
	lvl = cus[0].lvl;
	//show result
	print_cus(sub);
}
void chg_gds_info()
{
	string s;
	int sub = Get_Target_Goods();
	if( sub == no_object) return;

	if( manager_login()  )
		gds[sub].chg_info();
	//show result
	print_gds(sub);
}
void Goods::chg_info()
{
	string s;
	cout << "\n\tInput enter to maintain the last info:";
	cout << "\n\tNew Name:";
	getline(cin,s);
	if( s.size()>1 ) name = s;
	cout << "\tChange Prize?:";
	getline(cin,s);
	if( s.size()>1 ) price = stoi(s);
	cout << "\tChange Storage?:";
	getline(cin,s);
	if( s.size()>1 ) storage = stoi(s);
}
void User::chg_info()
{
	string s,s2;
	cout << "Log in Success!\n\tInput enter to maintain last info:";
	cout << "\n\tNew Name:";
	getline(cin,s);
	if( s.size()>1 ) name = s;
	cout << "\n\tNew Password:";
	getline(cin,s);
	if( s.size()>1 )
	{
		cout << "\n\tConfirm New Password:";
		getline(cin,s2);
		if( s == s2 )  encrypt_pswd = encrypt(s);
	}
	cout << "\n\t New Phone Number:";
	getline(cin,s);
	if( s.size()>1 ) phone = s;
	cout << "Revise Successfully!";
}
int Goods::sum_(int num)
{
	return (num >storage)?storage:num*price;
}
int Goods::sold(int num_)
{
	int mx_ = (num_ >storage)?storage:num_;
	storage = storage - mx_;
	return 0;
}
void User::purchase_(Goods &gd, int &num_)
{
	if(lvl == normal){
		//customer can not have nagative wealth
		while( gd.sum_(num_)  > wealth ) (num_)--;
		cout << "\n\tYou can buy "<<num_;
		wealth = wealth - gd.sum_( num_ );
		gd.sold(num_);
	}
	else{
		//chief and manager can have nagative wealth
		wealth = wealth - gd.sum_( num_ );
		gd.sold(num_);
	}

}
void user_buy(){
	int num,tgt_p,tgt_g; // p for target person , g for target goods
	tgt_p = Get_Target_Customer();	//  p is the subscript of the target people
	if(tgt_p == no_object) return;

	cout << "\t Identity checked: "<< cus[ tgt_p ].name_()<<" \tPlease input your password:";
	string a;
	getline(cin,a);	//notice that password can be void, so not use get_content
	if( login( a ,tgt_p ) == "error")	{
		cout << "\t Password Wrong!";
		return;
	}
	cout << "\tLog in Success!\n";
	tgt_g = Get_Target_Goods();
	if(tgt_g == no_object )	return;

	cout << "\t How much do you want? ";
	cin >> num;
	num = abs(num);

	cus[ tgt_p ].purchase_( gds[tgt_g] , num );
	// to show the result
	print_gds( tgt_g );
	print_cus( tgt_p );

}
void user_deposit()
{
	int cash,tgt_cus;
	if( manager_login() )
	{
		tgt_cus = Get_Target_Customer();
		if(tgt_cus == no_object) return;

		cout << "\tInput the cash(abs):";
		cin >> cash;
		cash = abs(cash);
		cus[ tgt_cus ].deposit_( cash );
		// to show the result
		print_cus(tgt_cus);
	}
}

// query returns a vector with all posibilities ( )
vector<int> query_cus(string s)
{
	int n =0;
	// rtn is just a short for return
	static vector<int> rtn;
	rtn.clear();
	// maybe query name first , then query the ID
	string c;
	for(int i = 0; i< num_cus ; i++)
		if( short_cmp( s , cus[i].name_() ) ) rtn.push_back(i);
	// if cant find in name space , then check the ID space
	if( rtn.size() == 0)
		for(int i = 0; i< num_cus ; i++)
			if( short_cmp(s, to_string(cus[i].ID ) ) ) rtn.push_back(i);

	return rtn;
}
vector<int> query_goods(string s)   // the same query algorithm as customer query£¬ but ID first
{
	int n =0;
	static vector<int> rtn;
	rtn.clear();
	string c;
	for(int i = 0; i< num_gds ; i++)
		if( short_cmp(s, to_string(gds[i].ID ) ) ) rtn.push_back(i);
	if( rtn.size() == 0)
	{
		for(int i = 0,j = 1 ; i< num_gds ; i++)
			if( short_cmp( s,gds[i].name_() )) rtn.push_back(i);
	}
	return rtn;
}
int Get_Target_Customer()   // return one single int of target user
{
	vector<int> cch;
	string a;
	while(cch.size() !=1 )
	{
		cout << "\n\tInput the Target Customer Info:( name part or ID )";
		cout << "\n\tMore details needed.Input the Target or -q to quit:";
		get_content(a);
		if(a == "-q") return no_object;
		cch.clear();
		cch = query_cus(a);
		print_cus( cch );
	}
	return cch[0];
}
int Get_Target_Goods()   // return one single int of target goods
{
	vector<int> cch;
	string a;
	while(cch.size() !=1 )
	{
		cout << "\n\tInput the target Goods Info:( name part or ID )";
		cout << "\n\tMore details needed.Input Target Goods or -q to quit:";
		get_content(a);
		if(a == "-q") return no_object;
		cch.clear();
		cch = query_goods(a);
		print_gds( cch );
	}
	return cch[0];
}

void macro(void)
{
	cout << "\n\tNum of all customer:" << num_cus + dlt_;
	cout << "\n\tNum of live customer:" << num_cus;
	cout << "\n\tNum of deleted customer:" << dlt_;
	cout << "\n\tNum of goods:" << num_gds;
	cout << "\n\tSum of customer cash:"<< cash_stat( normal );
	cout << "\n\tSum of cash current:" << cash_stat( boss );
}
int cash_stat(int level_ )
{
	int ans = 0;
	for(int i = 0 ; i< num_cus ; i++ )
		if( cus[i].lvl >= level_ ) ans += cus[i].wealth;
	return ans;
}
int shop_init()
{
	int a;
	string s,n;
	cout << "\n	Initializing...\n";
	cout << "\t Hello! Welcome to Shop Managing System\n";
	cout << "\t Choose the file you save.(*_user.sav,*_goods.sav)\n\n\t";
	getline(cin,s,'\n');
	if( s.size()<=1 ) s = "default";
	file_name = s;
	cout << "\tloading " << file_name << endl;
	a = load_cus() + load_gds();
	// if load successfully
	if(a!=0)
		return create();
	else
	{
		cout << "\t Please sign in or quit(input q) \n\t";
		getline(cin,s,'\n');
		if(s == "q" || s == "Q") return 0;
		//User[0] is the administrator
		n = login( s , 0 );
		if( n!="error" )
		{
			cout << "\t Sign in successfully!\n\t Welcome, "<< n <<"\n\n";
			lvl = cus[0].lvl;
			return 1;
		}
		cout << "password wrong!";
	}
	return 0;
}

int interact()
{
	char input;
	vector<int> b;
	string s;
	cout << "\n\t Operation Privilege:\t " << lv_name( lvl ) << endl;
	cout << "\n\t What operation do you want to do next\n";
	cout << "\t 1 :Print all customers" << endl;
	cout << "\t 2 :Print all Goods" << endl;
	cout << "\t 3 :Add a customer" << endl;
	cout << "\t 4 :Add Goods" << endl;
	cout << "\t 5 :Customer buy" << endl;
	cout << "\t 6 :Customer deposit" << endl;
	cout << "\t 7 :Query customer info" << endl;
	cout << "\t 8 :Query goods info" << endl;
	cout << "\t 9 :Macroscope Query" << endl;
	if(lvl <= 2){
		cout << "\t q :Change Customer Info" << endl;
		cout << "\t w :Change Goods Info" << endl;
		cout << "\t e :Delete a customer" << endl;
		cout << "\t r :Delete Goods" << endl;
	}
	cout << "\n\t ~: Clear Screen" << endl;
	cout << "\t 0 :Save & Quit" << endl;
	input = getch();
	if(lvl == normal && input >= 56) input = '`';
	switch(input)
	{
		case '`':
			system("cls");	break;
		case '0':
			return 0;		break;
		case '1':
			print_cus();	break;
		case '2':
			print_gds();	break;
		case '3':
			add_cus();		break;
		case '4':
			add_goods();	break;
		case '5':
			user_buy();		break;
		case '6':
			user_deposit();	break;
		case '7':
			cout << "\tInput the keyword or part of ID:";
			while( s.size()==0 )getline(cin,s);
			b = query_cus(s);	print_cus( b );
			break;
		case '8':
			cout << "\tInput the keyword or part of ID:";
			while( s.size()==0 )getline(cin,s);
			b = query_goods(s);	print_gds( b );
			break;
		case '9':
			macro();		break;
		case 'q':
			chg_cus_info();	break;
		case 'w':
			chg_gds_info();	break;
		case 'e':
			dlt_cus();		break;
		case 'r':
			dlt_goods();	break;
	}
	return input;
}
int farewell(){
	// save and quit
	cout << "\n\t Saving.\n";
	save_cus(); save_gds();
	cout << "\t Looking forward to your next use\n";
	cout << "\t Goodbye!\n";
	return 0;
}

int main(int argc, char** argv)
{
	int state;

	state = shop_init();
	while(state && cin)  	//notice that maybe some noob can input ^Z
	{
		state = interact( );
		//system("pause");
	}
	farewell();
	return 0;
}
