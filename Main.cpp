#include<iostream>
using namespace std;
#include"passwordNote.h"
#include"billNote.h"
#include"courseNote.h"
#include"workRecorder.h"

static void showMainMenu()
{
	cout << "***************************************************************" << endl;
	cout << "**           Choose what you wanna do!                       **" << endl;
	cout << "**               1.PasswordNote                              **" << endl;
	cout << "**               2.Bill Note                                 **" << endl;
	cout << "**               3.Course Note                               **" << endl;
	cout << "**               4.Work Recorder                             **" << endl;
	cout << "*****************0.Exist***************************************" << endl;
}
bool isRegisted = false;
class  User
{
private:
	string mName;
	string mAccount;
	string mPassword;
public:
	User() 
	{
		string name;
		string account;
		string password;
		ifstream ifs("User.txt", ios::in);
		if (ifs >> name >> account >> password)
			isRegisted = true;
	}
	User(string name,string account,string password):mName(name),mAccount(account),mPassword(password){}
	void regist();
	void logIn() const;
};
void User::regist()
{
		cout << "There is no account here, please regist" << endl;
		cout << "User Name:";
		cin >> mName;
		cout<< "Account:";
		cin >> mAccount;
		cout << "Password:";
		cin >> mPassword;
		ofstream ofs("User.txt", ios::out);
		ofs << mName<<"\t"<<mAccount << "\t" << mPassword;
		cout << "Done!" << endl;
		system("pause");
		return;
}

void User::logIn() const
{
	string name;
	string account;
	string password;

	ifstream ifs("User.txt", ios::in);
	if (!(ifs >> name >> account >> password))
	{
		cout << "No account found. Please register first." << endl;
		return;
	}

	User administrator(name, account, password);

	while (true)
	{
		string uPassword;
		cout << "User Name: " << administrator.mName << endl;
		cout << "Account: " << administrator.mAccount << endl;
		cout << "Enter Password: ";
		cin >> uPassword;

		if (uPassword == administrator.mPassword)
		{
			cout << "Log In Successful!" << endl;
			system("pause");
			return;
		}
		else
		{
			cout << "Password Wrong!" << endl << "1 to try again or 2 to exit" << endl;
			int choice = -1;
			cin >> choice;
			if (choice != 1)
				exit(0);
		}
	}
}




int main()
{
	setlocale(LC_ALL, "chs");
	User u;
	if (isRegisted == false)
		u.regist();
	else
		u.logIn();
	int choice = 0;
	while (true)
	{
		system("cls");
		cout << "Welcome to use the Desktop Helper!" << endl;
		system("date/T");
		system("TIME /T");
		showMainMenu();
		cin >> choice;
		switch (choice)
		{
		case 0:
			cout << "Thanks for using!" << endl;
			exit(0);
		case 1:
			{
			system("cls");
			Password p;
					p.showPasswordMenu();
					break;
			}
		case 2:
		{
			system("cls");
			BillNote b;
				b.showBillNoteMenu();
				break;
		}
		case 3:
		{
			system("cls");
			CourseNote course;
			course.showMenuCourseNote();
			break;
		}
		case 4:
		{
			system("cls");
			WorkRecorder w;
			w.showMenu();
		}
		default:
		system("cls");
		break;
		}
	}
	return 0;
}
