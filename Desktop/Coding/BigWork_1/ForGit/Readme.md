# MIKU's ShopSystem Readme.md
- Manager : Sun Jianyao
- Coding : Hu Zhengtao ， Zhou JiaChen 
- This program is for the final work of C++ learning courses.
#### Thanks
    Thanks to Mr.Zhou's persistent work, he give us the first version and framework of the program
    Thanks to Mr.Hu's for his reconstruction of coding, and he write this readme.md
    Thanks to Mr.Sun for his writing lab report
#### Why it is named after Hatsune Miku?
When the first vision completed, Mr. Sun Jianyao came to my Domitory and ask for a name for it.
Then he saw a Miku doll( called Fuwafuwa, short as Fufu ) and a Miku model, then, he point at it and happliy said, let us name our project after this cute doll 

### 1. Introduction
    This program is a simulation of daily Shop Managing System,
    Through it, the manager can conveniently manage the user and the goods

### 2. Install 
    1. Required machine configuration
        Any Computer with 64-bit Windows OS
        A available keyboard
    2.install
        Just double click the shop.exe or open the cmd input " ~/shop" , ~ is where the shop.exe stays
        Or you can compile the source code 
        Source: (You can get it from https://github.com/Hizi70k/Final_work/tree/master/Desktop/cpp/BigWork_1/ForGit)

<<<<<<< HEAD
        |Objected Oriented   | Procedure Oriented
        |--------------------|--------------------
        |ShopSys.h           | null
        |ShopSys.cpp         | null
        |Shop.cpp            | main.cpp
=======
| Objected Oriented   | Procedure Oriented|
|---|---
| ShopSys.h           | null              |
| ShopSys.cpp         | null              |
| Shop.cpp            | main.cpp          |
>>>>>>> b62cde3c35eedc5d162b4be23f0720b6e28db47f

## 3. Operation Instruction
    Just do what you want as the program shows you

### Features
    1. When inputting the goods' price or Users' wealth, only integer can be accepted
        It's FEATURE! Not a BUG!
    2. The Boss(Chief) and manager have the same Privilege , aiming to show that every labour are equal
    3. You can not have negative price or negative storage for goods, 
        and you can not have negative wealth customers,every negative input will turn into a positive one.
        
        BUT you can have nagative wealth for Chief and Managers!(rofl) 

## 4.Functions 
    0. When the save file doesn't exist, create one as the database
    1. Add a customer
    2. Add a goods
    3. User purchase
    4. User deposit
    5. Print all Customers
    6. Print all Goods
    7. Query Customer Infomation (By name part or ID)
    8. Query Goods Infomation (By name part or ID)
    9. Macroscope Query (To show the live customer and deleted customers' quantity )
    10. Delete specific Customer
    11. Delete spectific Goods
    12. Auto Saving when close the program

## 5. Functions in codes
###    Independent func
    1. int abs( int);
        return the absolute value of parameter int
    2. string encrypt(string);
        return a string encrypted by xor
    3. const string lv_name(int level);
        return the name of level (such as *Chief*, *Manager* or *Customer* );
    4. string get_content(string &);
        return string& which has contents (string& will be changed )
    5. int short_cmp( string input, string source ); 
        when input is part of the source starting at 0, return 1, else return 0
####        Notice : When source is a void string ,return 1 whatever the input 
###    Interface of classes
    1. Class DtBase
        private:	
            int num_cus,num_gds,dlt_;
           	User *cus;	    Goods *gds;
            // cus[0] is the default user using it, so check idendity is necessary
            int Get_Target_Customer(); // return subscript when only one can accept the condition
            int Get_Target_Goods();	
            int login( string );	// p = password ,return subscript of the User 
            string login(string p ,int sub_user);	// p = password ,return name of the User
            int manager_login();	//return 1 when log in as manager
            // return who has the top privilege when many has same pswd
        public:
            int lvl ;
            string file_name;

            //These below give a interface to class User and class Goods
            void add_cus();
            void dlt_cus();	
            void add_goods();
            void dlt_goods(); // delete goods
            void chg_cus_info();
            void chg_gds_info();
            void user_buy();
            void user_deposit();  
            int cash_stat(int level_);
            int create();
            int save_all();
            int load_all();
            // Functions below will return all the possible subscript list when has multiple answers
            vector<int> query_cus(string);
            vector<int> query_goods(string);
            // print the target , void = print all
            void print_cus(void);
            void print_gds(void);
            void print_cus( vector<int> ); // print the list by subscript
            void print_gds( vector<int> );
            void print_cus( int N ){	print_cus( vector<int> (1,N) );	}
            void print_gds( int N ){	print_gds( vector<int> (1,N) );	}

            void macro(void);
             //macroscope to show the quantity of live users and others

           


