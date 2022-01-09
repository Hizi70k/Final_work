#ifndef ShopSys_
#define Shopsys_

#include<string>
#include<cstring>
#include<vector>

using namespace std;
enum level{boss=1,manager,normal};

class User;
class Goods;
class DtBase{
private:	
	int num_cus,num_gds,dlt_;
	User *cus;	
	Goods *gds;
	// cus[0] is the default user using it, so check idendity is necessary
	int Get_Target_Customer(); // return subscript
	int Get_Target_Goods();	
	int save_cus();
	int load_cus();
	int save_gds();
	int load_gds();	
	int login( string );	// p = password ,return subscript of the User 
	int manager_login();	//return 1 when log as manager
	// return who has the top privilege when many has same pswd
public:
	DtBase(){	num_cus=0,num_gds=0;dlt_=0;	}
	int lvl ;
	string file_name;
	//These below give a interface to operate class User and class Goods
	void add_cus();
	void dlt_cus();			
	void add_goods();
	void dlt_goods(); // delete goods
	void chg_cus_info();
	void chg_gds_info();
	void user_buy();
	void user_deposit();
    // Functions below will return all the possible substript list when has multiple answers	
	vector<int> query_cus(string);
	vector<int> query_goods(string);
 	// print the list or single one feat. subscript, void = print all
	void print_cus(void);
	void print_gds(void);
	void print_cus( vector<int> );
	void print_gds( vector<int> );
	void print_cus( int N ){	print_cus( vector<int> (1,N) );	}
	void print_gds( int N ){	print_gds( vector<int> (1,N) );	}
	
	void macro(void);
	int cash_stat(int level_);
	
	string login(string,int);	// p = password ,return name of the User
	void get_lvl();
	int save_all(){		return save_cus() + save_gds(); }
	int load_all(){		return load_cus() + load_gds();	}

	int create();								
};

class User
{
private:
	string name,phone;
	string encrypt_pswd;
	int wealth;
	static int name_num;
public:
	User();	
	~User();
	int lvl = normal;
	int ID;
	string name_()	{ return name;			}
	string pswd()	{ return encrypt_pswd;	}
	void purchase_(Goods& , int&);
	void deposit_(int cash)	{ wealth = wealth + cash;	}
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
	friend int DtBase::cash_stat(int level_);
	
	void load_(ifstream &f_);	
	void save_(ofstream &f_);
};

class Goods{
private:	
	string name;
	int price,storage;
	static int name_num;
public:	
	Goods();
	~Goods();	
	int ID;
	int add_();
	int sum_(int);
	int sold(int num_);
	void chg_info();
	string name_(){return name;}
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
ostream& operator<<(ostream&, User& pt );
ostream& operator<<(ostream&, Goods& pt);

int shop_init(DtBase &);

int abs(int);
string encrypt(string);
string lv_name(int);
string get_content(string&); // get a non_void string
int short_cmp(string,string);

#endif
