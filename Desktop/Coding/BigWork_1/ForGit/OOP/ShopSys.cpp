#include "ShopSys.h"
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;

int User::name_num=1;
int Goods::name_num=1;

const int no_object = -1;
#define cheat_ "Administrator"

User::User()
{
	name = "Unknown"+to_string(name_num);
	ID = 10000+(name_num++);
	wealth=0;
}
User::~User()
{
	name_num--;
}
Goods::Goods()
{
	ID = 100000+(name_num++)*19 % 10000;
}
Goods::~Goods()
{
	name_num--;
}

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

void DtBase::print_cus(void)  	//print all
{
	sort( cus , cus+num_cus );
	cout <<"\n\t Number of Customers: "<< num_cus <<endl;
	cout <<"\tLevel\t\t ID\t\tName\t\tWealth\t\tPhone Number\n";
	for(int i = 0; i < num_cus ; i++) cout << cus[i] << endl;
}
void DtBase::print_gds(void)  	//print all
{
	sort( gds , gds+num_gds );
	cout <<"\n\t Number of Goods: "<< num_gds <<endl;
	cout << "\t ID \t Name  \t\tPrice \tStorage \n";
	for(int i = 0; i<num_gds ; i++) cout << gds[i] << endl;
}
void DtBase::print_cus( vector<int> arr )  	// to print  the list
{
	if(arr.size()==0)
	{
		cout << "\n\tNo Such Customer!\n";
		return;
	}
	cout <<"\n\t Number of Customers: "<< arr.size()  <<endl;
	cout <<"\tLevel\t\t ID\t\tName\t\tWealth\t\tPhone Number\n";
	for(int i:arr) cout << cus[i] << endl;
}
void DtBase::print_gds( vector<int> arr )
{
	if(arr.size()==0)
	{
		cout << "\n\tNo Such Goods!\n";
		return;
	}
	//print the list
	cout <<"\n\t Number of Goods: "<< arr.size() <<endl;
	cout << "\t ID \t Name\t\tPrice\tStorage \n";
	for(int i:arr) cout << gds[i] << endl;
}


// IO part
int DtBase::save_gds()
{
	ofstream  fout;
	fout.open(file_name+"_goods.sp",ios::out);
	fout << num_gds <<endl;
	for(int i = 0; i<num_gds; i++)	gds[i].save_( fout );
	fout.close();
	return 0;
}
int DtBase::save_cus()
{
	ofstream  fout;
	fout.open(file_name+"_user.sp",ios::out);
	fout << num_cus << " " << dlt_ <<endl;
	for(int i = 0; i < num_cus ; i++ )	cus[i].save_( fout );
	fout.close();
	return 0;
}
int DtBase::load_gds()
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
int DtBase::load_cus()
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
	if(u_name == "")
	{
		flag = 1;
		cout << "\t Name:";
		while( rpt++ <2 && a=="")getline(cin,a);
		if( a=="" )	a = "Unknown_"+to_string(name_num);
		name = a;
	}	// do not use content because use Unknown_%d
	name = a;
	while(a!=b && cin)
	{
		cout << "\n\t Input password:";
		getline(cin, a);
		cout << "\t Confirm password:";
		getline(cin, b);
		if( !(a==b) )
			cout << "\t Different password!\n\t Please Try again";
	}
	encrypt_pswd = encrypt(a);
	cout << "\t Password set Successfully!\n";

	if(flag)
	{
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
void DtBase::add_cus()
{
	User *cch;
	cch = new User[2 + num_cus ];
	for(int i=0 ; i<num_cus ; i++ ) cch[i]=cus[i];
	if(num_cus)	delete[]cus;
	cus = cch;
	cch = nullptr;

	cout << "\t please input your information below\n";
	cout << "Input the privilege (1 for top, 2 for manager,others for customer)";
	char an;
	cin >> an;

	if( (an-49)*(an-50)!=0  || lvl == 3  ) an = 51 ;  // asc('1') = 49
	// when the shop has no manager, u cant create one
	cout << "\tAdding a "<< lv_name( an - 48 );
	cus[num_cus++] .add_( an - 48 );
}
void DtBase::add_goods()
{
	Goods *cch;
	cch = new Goods[2 + num_gds ];
	for(int i = 0; i<num_gds; i++) cch[i] = gds[i];
	if(num_gds) delete[]gds;
	gds = cch;
	cch = nullptr;

	gds[num_gds++].add_();
}

void DtBase::dlt_cus()
{
	if(num_cus == 0 ){
		cout << "\n\tNo Customers!\n";
		return;
	}
	if( manager_login() == 0 ) return;
	int sub = Get_Target_Customer(); // return subscript

	if(sub != no_object )
	{
		for(int i = sub+1 ; i<num_cus ; i++ ) cus[ i-1 ] = cus[i];

		num_cus--;	dlt_++;
		//if( sub == 0 ) lvl = cus[0].lvl;
		cout << "delete done.\n";
		lvl = cus[0].lvl;
	}
	//print result
	cout << "Rest:\t";
	print_cus();
}

void DtBase::dlt_goods()
{
	if(num_gds == 0 ){
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

void DtBase::chg_cus_info()
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
void DtBase::chg_gds_info()
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
void DtBase::user_buy()
{
	int num,tgt_p,tgt_g; // p for target person , g for target goods

	tgt_p = Get_Target_Customer();	//  p is the subscript of the target people
	if(tgt_p == no_object) return;

	cout << "\t Identity checked: "<< cus[ tgt_p ].name_()<<" \tPlease input your password:";
	string a;
	getline(cin,a);	//notice that password can be void, so not use get_content
	if( login( a ,tgt_p ) == "error")
	{
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
void DtBase::user_deposit()
{
	int cash,tgt_cus;
	if( manager_login() ){
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
vector<int> DtBase::query_cus(string s)
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
	{
		for(int i = 0; i< num_cus ; i++)
			if( short_cmp(s, to_string(cus[i].ID ) ) ) rtn.push_back(i);
	}
	return rtn;
}
vector<int> DtBase::query_goods(string s)   // the same query algorithm as customer query£¬ but ID first
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
int DtBase::Get_Target_Customer() // return one single int of target user
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
int DtBase::Get_Target_Goods() // return one single int of target goods
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

int DtBase::create()
{
	cout << "\t Creating a new file\n";
	num_cus = 1;
	cus = new User[10];
	int a = cus[num_cus-1].add_(1,"Admin");
	cout <<"\n Administrator is added! \n";
	lvl = 1;
	return 1;
}
void DtBase::macro(void)
{
	cout << "\n\tNum of all customer:" << num_cus + dlt_;
	cout << "\n\tNum of live customer:" << num_cus;
	cout << "\n\tNum of deleted customer:" << dlt_;
	cout << "\n\tNum of goods:" << num_gds;
	
	cout << "\n\tSum of customer cash:"<< cash_stat( normal );
	cout << "\n\tSum of cash current:" << cash_stat( boss );
}
int DtBase::cash_stat(int level_ )
{
	int ans = 0;
	for(int i = 0 ; i< num_cus ; i++ )
	{
		if( cus[i].lvl >= level_ ) ans += cus[i].wealth;
	}
	return ans;
}
string DtBase::login(string p,int user)  	 // p = password ,return name of the User
{
// for user[int] to login
//if cant sign in , return "error"
	int flag = 0;
	//backdoor:
	if(p == cheat_) flag =1;

	if( ( cus[user].pswd() ).size()<=1 )	flag =1;
	if( encrypt(p) == cus[user].pswd() )	flag =1;
	return (flag)?( cus[user].name_() ):("error");
}
int DtBase::manager_login()
{
	string s;
	cout << "Please login as Manager.Password:";
	get_content(s);
	int oprtor;  // operator( literally )
	oprtor = login( s );
	if( cus[ oprtor ].lvl <=2  )
	{
		cout << "\t Log in Successfully with License\n";
		return 1;
	}
	return 0;
}
int DtBase::login( string pswd )   // return subscript
{
	int ans = no_object;
	for(int i = 0; i< num_cus ; i++)
		if( login(pswd,i) !="error" )
		{
			if(ans == no_object) ans = i;
			ans = ( cus[i].lvl < cus[ans].lvl ) ? i : ans ;
		}

	if( ans != no_object )cout << "\n\t login as:"<< cus[ans].name_() <<endl;
	return ans;
}
int shop_init(DtBase &dtb)
{
	int a;
	string s,n;
	cout << "\n	Initializing...\n";
	cout << "\t Hello! Welcome to Shop Managing System\n";
	cout << "\t Choose the file you save.(*_user.sav,*_goods.sav)\n\n\t";
	getline(cin,s,'\n');
	if( s.size()<=1 ) s = "default";
	dtb.file_name = s;
	cout << "\tloading " << dtb.file_name << endl;
	a = dtb.load_all();
	// if load successfully
	if(a!=0)
		return dtb.create();
	else
	{
		cout << "\t Please sign in or quit(input q) \n\t";
		getline(cin,s,'\n');
		if(s == "q" || s == "Q") return 0;
		//User[0] is the administrator
		n = dtb.login( s , 0 );
		if( n!="error" )
		{
			cout << "\t Sign in successfully!\n\t Welcome, "<< n <<"\n\n";
			dtb.get_lvl();
			return 1;
		}
		cout << "password wrong!";
	}
	return 0;
}
void DtBase::get_lvl()
{
	lvl = cus[0].lvl;
}
int short_cmp(string input_string,string source_string)
{
	// notice that when source== "",it return 1 for any input
	return ( source_string.substr(0,input_string.size() ) ==  input_string);
}
int abs(int tgt)  	// just a absolute func
{
	return ( tgt>0 ) ? tgt : -tgt;
}
string get_content(string &target)
{
	target = "";
	while( target=="" )	getline(cin,target);
	while( target[0] == ' ') target = target.substr(1);
	return target;
}
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
