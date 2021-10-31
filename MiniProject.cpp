#include <iostream>  //main header file for C++
#include<fstream>    //header file for file handling
#include<iomanip>    //I/O manipulator library
#include<cctype>     //contains function toupper() used to set account type
#include<vector>     //used to make dynamic list of type and amount of transactions
using namespace std;
const float rate_of_interest=7.5;


class account{     //class to hold all object functions and variables
private:
  int acno;        //account holder's account number
  char name[50];     //account holder's name
  double deposit;   //balance in account
  char type;        //type of account savings/current
  char address[50];   //account holder's address
public:
	void create_account();     //to collect information while creating account
  void show_account() const; //to show account holder's name and account number
  void showbal() const;  //to show balance in account
  void modify();    //to modify account details
	void dep(double);  //to deposit an amount in the account
	void draw(int);    //to withdraw from account
	void report() const;  //to show account details
	int retacno() const;  //to return account number
	double retdeposit() const;  //to return account balance
	char rettype() const;  //to return account type
  void retaddress() const;  //to return address
  void retname() const;  //to return name
  vector <double> trans;  //vector to store transaction amounts
  vector <char> flag;  //vector to store type of transaction deposit(D)/withdraw(W)

};
void account::create_account(){
	cout<<"\nEnter Account No. : ";
	cin>>acno;
	cout<<"\nEnter the Name of the Account holder : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nEnter Type of the Account (C/S) : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nEnter The Initial amount : ";
	cin>>deposit;
	cout<<"\nEnter address  ";
  cin.ignore();
  cin.getline(address,50);
}
void account::show_account() const{
	cout<<"\nAccount Holder Name : "<<name;
  cout<<"\nAccount No. : "<<acno;
}
void account::showbal() const{
  cout<<"\n Balance is: "<<deposit;
}
void account::modify()
{
	cout<<"\nAccount No. : "<<acno;
	cout<<"\nModify name, Enter new name : ";
	cin.ignore();
	cin>>name;
	cout<<"\n\t\t\tModify ype of Account, Enter new account type C/S : ";
	cin>>type;
	type=toupper(type);
	cout<<"\n\t\t\tModify balance amount, Enter new balance : ";
	cin>>deposit;
}
void account::dep(double x){
	deposit+=x;
}
void account::draw(int x){
	deposit-=x;
}
void account::report() const{
	cout<<acno<<setw(10)<<" "<<name<<setw(6)<<" "<<type<<setw(6)<<"   "<<deposit<<setw(6)<<"         "<<address<<endl;
}
int account::retacno() const{
	return acno;
}
double account::retdeposit() const{
	return deposit;
}
char account::rettype() const{
	return type;
}
void account::retaddress() const{
  cout<<"Address is: \n"<<address;
}
void account::retname() const{
  cout<<"\n Name is:  \n"<<name;
} 


//***************functions reated to file operations*******************

void write_account();  //to write an object's details to text file.

void display_sp(int);  //calls showbal function to deisplay details from the text file.

void modify_account(int); //uses modify() function to modify details from the text file.

void delete_account(int); //deletes details of an account from the text file.

void display_all();  //shows all the accounts present with some details from the text file.

void deposit_withdraw(int, int); //adds or subtracts from account balance. First argument is the account number. Second argument is to specify the transaction type.

void check(int);  //checks whteher a specified account exists or not in the text file.

void rename(int); //returns the name of the account holder from the text file.

void readdress(int); //returns address of the account holder from the text file.

void retrans(int);  //shows the transactions of a specific account.

void interest(int); //checks whether an account holder is eligible for interest or not. If found eligible adds the interest to the balance.



int main(){
  char ch;
	int num;
  do{
    cout<<"\n*****Welcome to the Bank Management System*****\n\n\n";
    cout<<"\nPress 1 to add account  ";
		cout<<"\nPress 2 to deposit  ";
		cout<<"\nPress 3 to withdraw  ";
		cout<<"\nPress c to check whether acccount exists or not  ";
		cout<<"\nPress 5 to see the name of account holder  ";
    cout<<"\nPress 6 to see the address of account holder  ";
    cout<<"\nPress 7 to see the balance of account holder  ";
    cout<<"\nPress 8 to delete the account  ";
		cout<<"\nPress 9 to modify an account  ";
    cout<<"\nPress 0 to show list all account details  ";
    cout<<"\nPress t to show list of transactions of an account  ";
    cout<<"\nPress i to check interest   ";
		cout<<"\nPress e to exit   \n\n";
		cin>>ch;
    switch(ch){
      case '1':
        write_account();
        break;
      case '2':
        cout<<"\nEnter The account No. : ";
        cin>>num;
			  deposit_withdraw(num, 1);
			  break; 
      case '3':
        cout<<"\nEnter The account No. : "; cin>>num;
        deposit_withdraw(num, 2);
        break;  
      case 'c':
        cout<<"\nenter account no :";cin>>num;
        check(num);
        break;
      case '5':
        cout<<"\nEnter account number :";cin>>num;
        rename(num);
        break;
      case '6':
        cout<<"\nEnter account number:  ";cin>>num;
        readdress(num);
        break;
      case '7':
        cout<<"\nEnter The account No. : "; 
        cin>>num;
		  	display_sp(num);     
        break; 
      case '8':
        cout<<"\nEnter The account No. : "; 
        cin>>num;
        delete_account(num);
        break;
      case '9':
      cout<<"\nEnter The account No. : "; 
        cin>>num;
        modify_account(num);
        break;
      case '0':
        display_all();
        break;
      case 't':
        cout<<"\nEnter account number : ";
        cin>>num;
        retrans(num);
        break;
      case 'i':
        cout<<"Enter account number : ";
        cin>>num;
        interest(num);
        break;  
      case 'e':
        break;
      default :cout<<"\n";  
    }
    cin.ignore();
		cin.get();

  }while(ch!='e');
	return 0;
}
void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.txt",ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
  cout<<"Account has been created ";

}



void deposit_withdraw(int n, int option)
{
	int amt;
  bool found=false;
	account ac;
	fstream File;
	File.open("account.txt",ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not open.";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"\nEnter The amount to be deposited  :";
				cin>>amt;
        ac.flag.push_back('D');
        ac.trans.push_back(amt);
				ac.dep(amt);
			}
			if(option==2)
			{
				cout<<"\nEnter The amount to be withdraw  :";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if(bal<0)
					cout<<"Insufficient balance";
				else
          ac.flag.push_back('W');
          ac.trans.push_back(amt);
					ac.draw(amt);
			}
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\nBalance Updated";
      found=true;
	  }
    }
	File.close();
  if(found==false)
		cout<<"\nRecord Not Found ";
}


void display_sp(int n)
{
	account ac;
  bool flag=false;
	ifstream inFile;
	inFile.open("account.txt",ios::binary);
	if(!inFile)
	{
		cout<<"File could not open.";
		return;
	}
  while(inFile.read(reinterpret_cast<char *> (&ac),sizeof(account)))
	{
		if(ac.retacno()==n)
		{
			ac.showbal();
      flag=true;
		}
	}
	inFile.close();
  if(flag==false)
		cout<<"\nAccount number does not exist";
}


void check(int n){
  account ac;
	ifstream inFile;
	inFile.open("account.txt",ios::binary);
  while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()==n){
      cout<<"Account exists";
    }
    else cout<<"Account does not exist";
}
inFile.close();
}

void rename(int n){
  bool flag=false;
  account ac;
  ifstream inFile;
	inFile.open("account.txt",ios::binary);
  while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account))){
    if(ac.retacno()==n) {
      ac.retname();
      flag=true;
    }
  }
  inFile.close();
  if(flag==false)
		cout<<"\nAccount number does not exist";
}

void readdress(int n){
  bool flag=0;
  account ac;
  ifstream inFile;
  inFile.open("account.txt",ios::binary);
  while(inFile.read(reinterpret_cast<char *>
  (&ac),sizeof(account))){
    if(ac.retacno()==n){
      ac.retaddress();
      flag=true;
    }
  }
  inFile.close();
  if(flag==false)
		cout<<"\nAccount number does not exist";
}


void delete_account(int n)
{
  bool flag=0;
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.txt",ios::binary);
	outFile.open("Temp.txt",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
      flag=true;
		}
	}
    inFile.close();
	outFile.close();
	remove("account.txt");
	rename("Temp.txt","account.txt");
	cout<<"\n Account deleted  ";
  if(flag==false)
		cout<<"\nAccount number does not exist";
}

void modify_account(int n)
{
	bool found=false;
  account ac;
	fstream File;
  File.open("account.txt",ios::binary|ios::in|ios::out);
	while(!File.eof())
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			cout<<"\nEnter The New Details of account";
			ac.modify();
			int pos=(-1)*static_cast<int>(sizeof(account));
			File.seekp(pos,ios::cur); 
		    File.write(reinterpret_cast<char *> (&ac), sizeof(account));
		    cout<<"\nAccount Updated   ";
        found=true;
		  }
	}
	File.close();
  if(found==false)
		cout<<"\nRecord Not Found ";
}

void display_all()
{
  bool flag=false;
	account ac;
	ifstream inFile;
	inFile.open("account.txt",ios::binary);
	cout<<"A/c no.      NAME      Type    Balance   Address \n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		ac.report();
    flag=true;
	}
	inFile.close();
  if(flag==false)
		cout<<"\nAccount number does not exist";
}

void retrans(int v){
  bool flag=false;
  account ac;
	fstream File;
  File.open("account.txt",ios::binary|ios::in|ios::out);
  if(!File)
	{
		cout<<"File could not open.";
		return;
	}
	while(!File.eof())
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==v){
      for(int i=0;i<ac.flag.size();i++){
        if(ac.flag[i]=='D'){
          cout<<"\n Amount deposited: "<<ac.trans[i]<<"\n";
        }
        else cout<<"\n Amount withdrawn: "<<ac.trans[i]<<"\n";
        flag=true;
    }
  }
}File.close();
if(flag==false)
		cout<<"\nAccount number does not exist";

}

void interest(int y){
  int amt;
	account ac;
	fstream File;
	File.open("account.txt",ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not open.";
		return;
	}
  File.read(reinterpret_cast<char *> (&ac), sizeof(account));
  char s;
  double interest;
		if(ac.retacno()==y){
      cout<<"Have you withdrawn any amount within the last month? (Y/N) ";
      cin>>s;
      s=toupper(s);
      if(s=='Y'){
        cout<<"\nCongratulations!!!  You are eligible for an interest of 7.5%  \n"; 
        interest=ac.retdeposit()*(rate_of_interest/100);
        ac.dep(interest);
      int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
      }
      else return;
    }
    File.close();
}