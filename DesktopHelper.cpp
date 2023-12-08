#include<iostream>
using namespace std;
#include"passwordNote.h"

static void showMainMenu()
{
	cout << "******************************************" << endl;
	cout << "***Welcome to use the desktop helper!   **" << endl;
	cout << "***0.Exit                       **" << endl;
	cout << "***1.PasswordNote                       **" << endl;
	cout << "******************************************" << endl;
}





int main()
{

	int choice = 0;
	while (true)
	{
		showMainMenu();
		cout << "Choose what you wanna do." << endl;
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
			bool judgePassword = true;
			while (judgePassword)
				{
					if (!p.mIsSetNotePassword)
					{
						p.setNotePassword();
					}
					p.showPasswordMenu();
					cout << "Choose what you wanna do." << endl;
					int choicePassword = -1;
					cin >> choicePassword;
					switch (choicePassword)
					{
					case 0:
						judgePassword=p.exitPassword();//退出密码本
						break;
					case 1:
							p.addPassword();//添加密码
						break;
					case 2:
						p.changePassword();//修改密码
						break;
					case 3:
						p.showPassword();//显示所有密码
						break;
					case 4:
						p.showSinglePassword();////根据网站、app名查找密码或根据账号查找密码
						break;
					case 5:
						p.deleteAllPassword();//删除所有密码
						break;
					case 6:
						p.deleteSinglePassword();//删除某个密码
						break;
					default:
						system("cls");
						continue;
					}
				}
			}
		default:
			system("cls");
			break;
		}
	}
	return 0;
}
