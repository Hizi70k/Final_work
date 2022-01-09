#include "ShopSys.h"
#include<iostream>
#include<vector>
#include<conio.h>
using namespace std;

int interact(DtBase &sp);
int farewell(DtBase &sp);

int main(int argc, char** argv)
{
	int state;
	DtBase shop;
	state = shop_init(shop);
	while(state && cin)	//notice that maybe some noob can input ^Z
	{
		state = interact( shop );
		//system("pause");
	}
	farewell(shop);
	return 0;
}

int interact(DtBase &sp)
{
	char input;
	vector<int> b;
	string s;
	cout << "\n\t Operation Privilege:\t " << lv_name( sp.lvl ) << endl;
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
	if(sp.lvl <= 2){
		cout << "\t q :Change Customer Info" << endl;
		cout << "\t w :Change Goods Info" << endl;
		cout << "\t e :Delete a customer" << endl;
		cout << "\t r :Delete Goods" << endl;	
	}
	cout << "\n\t ~: Clear Screen" << endl;
	cout << "\t 0 :Save & Quit" << endl;
	input = getch();	
	if(sp.lvl == normal && input >= 56) input = '`';
	switch(input)
	{
		case '`':
			system("cls"); break;
		case '0':
			return 0; break;
		case '1':
			sp.print_cus();	break;
		case '2':
			sp.print_gds();	break;
		case '3':
			sp.add_cus(); break;
		case '4':
			sp.add_goods(); break;
		case '5':
			sp.user_buy();	break;
		case '6':
			sp.user_deposit();	break;
		case '7':
			cout << "\tInput the keyword or part of ID:";
			while( s.size()==0 )getline(cin,s);
			b = sp.query_cus(s);
			sp.print_cus( b );
			break;
		case '8':
			cout << "\tInput the keyword or part of ID:";
				while( s.size()==0 )getline(cin,s);
				b = sp.query_goods(s);
				sp.print_gds( b );
			break;
		case '9':
			sp.macro(); // fucking macroscope query
			break;	
		case 'q':
			sp.chg_cus_info();
			break;
		case 'w':
			sp.chg_gds_info();
			break;
		case 'e':
			sp.dlt_cus();	break;	
		case 'r':
			sp.dlt_goods();	break;	
	}
	return input;
}
int farewell(DtBase &sp)
{
	// for save and quit
	cout << "\n\t Saving.\n";
	sp.save_all();
	cout << "\t Looking forward to your next use\n";
	cout << "\t Goodbye!\n";
	return 0;
}

