#include<iostream>
#include<map>
#include<fstream>
#include<iterator>
#include<string>
#include<sstream>
#include<vector>
using namespace std;

class member {
	private:
		string user_id;
		int password;
		int acc_no;
		int balance;
		vector <string> statement;

	public:
		member(){}
		void get_statement();
		string get_id() {
			return user_id;
		}
		int get_password() {
			return password;
		}
		void deposit(int);
		void change_pass();
		void check_bal();
		void money_tran();
		void withdrawl(int);
		void update(string);
		int load(string str);
};

void member::get_statement() {
	cout << "Mini Statement" << endl;
	for (int i = 0; i < this->statement.size(); i++) {
		cout << this->statement[i] << endl;
	}
}

 void member::check_bal(void) {
	 cout << "Balance remaining : " << this->balance << endl;
}
 
 void member::withdrawl(int w) {
	 
	 if (w <= this->balance) {
		 this->balance = this->balance - w;
		 string s = '-' + to_string(w);
		 this->statement.insert(statement.begin(),s);
		 this->statement.resize(5);
	 }
	 else {
		 cout << "Not enough balance.. Try again!!" << endl;
	 }
 }

 void member::deposit(int a) {
	 
	 this->balance += a;
	 string s = '+' + to_string(a);
	 this->statement.insert(statement.begin(), s);
	 this->statement.resize(5);
 }

 void member::change_pass() {
	 int oldp, newp, cofp;
	 int trial = 2;
	 A:cout << "Enter old password : ";
	 cin >> oldp;
	 if (oldp == this->password) {
		B: cout << endl << "Enter new password : ";
		 cin >> newp;
		 cout << endl << "Confirm new password : ";
		 cin >> cofp;
		 if (newp == cofp) {
			 this->password = newp;
			 cout << "Successfull" << endl;
			 return;
		 }
		 else {
			 cout << "Password not matched..Try Again" << endl;
			 goto B;
		 }
	 }
	 else {
		 if (trial == 0) {
			 cout << "Max attempts reached" << endl;
			 return;
		 }
		 cout << "Wrong password .. Try Again" << endl;
		 trial--;
		 goto A;
	 }

 }

 void member::update(string file) {
	 fstream f; 
	 
	 f.open(file + ".txt",ios::trunc | ios::in | ios::out);
	 f << this->acc_no << endl;
	 f << this->user_id<< endl;
	 f << this->password<< endl;
	 f << this->balance << endl;

	 for (int i = 0; i < statement.size(); i++) {
		 f << this->statement[i]<<" ";
	 }
	 f.close();
 }

 void member::money_tran() {
	 cout << "Enter the account number : ";
	 string s;
	 int b = 1;
	 cin >> s;
	 member n;
	 while (b == n.load(s)) {
		 cout << "Enter the account number : ";
		 cin >> s;
	 }
	 int a;
	 cout << "Enter the amount : ";
	 cin >> a;
	 cout << endl;
	 this->withdrawl(a);
	 n.deposit(a);
	 n.update(s);
	
 }

 int  member::load(string str) {
	 fstream f;
	 //f.open(str + ".txt", ios::in);
	 f.open(str + ".txt", ios::out | ios::in);
	 if (f.peek() == std::ifstream::traits_type::eof()) {
		 system("CLS");
		 cout << "Account doesn't exist.. Try again!!" << endl;
		 return 1;
	 }

	 string s; int a;
	 int t = 5;
	 f >> s;
	 a = stoi(s);
	 this->acc_no = a;
	 f >> s;
	 this->user_id = s;
	 f >> s;
	 a = stoi(s);
	 this->password = a;
	 f >> s;
	 a = stoi(s);
	 this->balance = a;
	 while (t--) {
		 f >> s;
		 this->statement.push_back(s);
	 }
	 f.close();
	 return 0;
 }

 int main() {
	 int acc, pass,a=1;
	 string str, user;
	 cout << "Enter acc no : ";
	 cin >> str;
	 member m;
	 while (a == m.load(str)) {
		 cout << "Enter acc no : ";
		 cin >> str;
	 }
	 cout << "Enter user id : ";
	 cin >> user;
	 cout << endl << "Enter password : ";
	 cin >> pass;
	 if (user == m.get_id() && pass == m.get_password()) {
		 int choice = 0;
		 while (choice != 7) {
			 system("CLS");
			 cout << "Enter your choice" << endl;
			 cout << "1. Change password" << endl;
			 cout << "2. Deposit money" << endl;
			 cout << "3. Withdraw money" << endl;
			 cout << "4. Check Balance" << endl;
			 cout << "5. Mini Statement" << endl;
			 cout << "6. Money Transfer" << endl;
			 cout << "7. Exit" << endl;
			 cin >> choice;
			 switch (choice) {
			 case 1:
				 m.change_pass();
				 break;
			 case 2:
				 int a;
				 cout << "Enter the amount : ";
				 cin >> a;
				 cout << endl;
				 m.deposit(a);
				 cout << "Transaction successfull" << endl;
				 m.check_bal();
				 break;
			 case 3:
				 int w;
				 cout << "Enter the amount : ";
				 cin >> w;
				 cout << endl;
				 m.withdrawl(w);
				 cout << "Transaction successfull" << endl;
				 m.check_bal();
				 break;
			 case 4:
				 m.check_bal();
				 break;
			 case 5:
				 m.get_statement();
				 break;
			 case 6:
				 m.money_tran();
				 cout << "Transaction successfull" << endl;
				 m.check_bal();
				 break;
			 case 7:
				 m.update(str);
				 break;
			 default:
				 cout << "Enter a valid choice!!" << endl;
			 }
			 system("pause");

		 }
	 }
	 else {
		 cout << "User id or password didn't match" << endl;
	 }

	 system("pause");
 }
 