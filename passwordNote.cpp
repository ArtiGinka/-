#include<iostream>
#include<string>
#include"passwordNote.h"
using namespace std;
/*
	密码：
		属性：
			账号归属地name，账号account，密码password（私有），密码本密码（静态）
			行为：对外的密码接口
			成员函数：
				设置账号名、账号、密码(√)；显示所有账号密码（√）；修改账号密码;根据网站、app名查找密码或根据账号查找密码（√）；添加密码（√）；
				删除某条密码（√）；删除所有密码（√）；文件保存（√）；

*/
string Password::mNotePassword = "0";
int Password::mNum = 0;
vector<Password> Password::v(0);

//显示密码本菜单
void Password:: showPasswordMenu()
{
	cout << "**Welcome to ues the PasswordNote!" << endl;
	cout << "**Choose what you wanna to do:" << endl;
	cout << "**0:Exist the passwordnote." << endl;
	cout << "**1:Add a password." << endl;
	cout << "**2:Change a password." << endl;
	cout << "**3:Show all password." << endl;
	cout << "**4:Show a targer password." << endl;
	cout << "**5:Delete all password." << endl;
	cout << "**6:Delete a target password." << endl;
}

//默认构造函数
Password::Password()
{
	//情况一：文件不存在
	ifstream ifs;
	ifs.open(FILEPASSWORD, ios::in);//读文件
	if (!ifs.is_open())
	{
		//初始化属性
		mNum= 0;
		//初始化文件是否为空
		mFilePasswordIsEmpty= true;
		ifs.close();
		return;
	}
	//情况二：文件存在但是数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//初始化属性
		mNum = 0;
		//初始化文件是否为空
		mFilePasswordIsEmpty= true;
		ifs.close();
		return;
	}
	//情况三：文件存在且需要保存已有数据
	int num = this->getPasswordNum();
	mNum= num;
	cout << "The current password amount is:" << mNum << endl;
	//将文件中的数据存入vector容器
	this->initialPassword();
}

//有参构造函数
Password::Password(string name, string account, string password)
{
	this->mName = name;
	this->mAccount = account;
	this->mPassword = password;
}

//设置密码本密码
void Password::setNotePassword()
{
	cout << "Please set the password to your password note." << endl;
	string notePassword;
	cin >> notePassword;
	mNotePassword = notePassword;
	mIsSetNotePassword = true;
}

//设置账号
void Password::setAccount()
{
	string name;//设置账号属地
	cout << "Please enter the target website or app name:" << endl;
	cin >> name;
	this->v[mNum].mName = name;
	string account;//设置账号
	cout << "Please enter your account:" << endl;
	cin >> account;
	this->v[mNum].mAccount = account;
}

//设置密码
void Password::setPassword()
{
	cout << "Please enter the password correspond to the account you just enter:" << endl;
	string password;
	cin >> password;
	this->v[mNum].mPassword = password;
	system("cls");
}

//显示所有账号与密码
void Password::showPassword() const
{
	if (mFilePasswordIsEmpty)
	{
		cout << "Nothing here!" << endl;
	}
	else
	{
		while (true)
		{
			cout << "Please enter the password to check your password note." << endl;
			string temp;
			cin >> temp;
			if (temp == mNotePassword)
			{
				for (int i = 0; i < mNum; i++)
				{
					cout << "Website or App:\t" << this->v[i].mName << endl;
					cout << "Account:\t" << this->v[i].mAccount << endl;
					cout << "Password:\t" << this->v[i].mPassword << endl;
				}
				break;
			}
			else
			{
				cout << "Wrong!\nEnter 1 to try again or 2 to exit." << endl;
				int choice = 0;
				cin >> choice;
				if (choice == 1)
				{
					continue;
				}
				else
				{
					break;
				}
			}
		}
	}
	system("pause");
	system("cls");
}

//修改密码
void Password::changePassword()
{
	if (mFilePasswordIsEmpty)
	{
		cout << "Nothing here!" << endl;	
		system("pause");
		system("cls");
	}
	else
	{
		while (true)
		{
			cout << "Please enter the name of the target Website/app or account whose password you want to change:" << endl;
			int index = findIndex();
			if (index != -1)
			{
				cout << "Please enter the former password:" << endl;
				string formerPassword;
				cin >> formerPassword;
				if (formerPassword == this->v[index].mPassword)
				{
					cout << "Please enter the new password:" << endl;
					string newPassword;
					cin >> newPassword;
					this->v[index].mPassword = newPassword;
					cout << "Done!" << endl;
					system("pause");
					system("cls");
					return;
				}
				else
				{
					cout << "Password Wrong!" << endl;
					cout << "Enter 1 to try again,or enter 2 to exist." << endl;
					int num = 0;
					cin >> num;
					if (num == 1)
					{
						system("cls");
						continue;
					}
					else if (num == 2)
					{
						system("cls");
						return;
					}
					else
						system("cls");
					return;
				}
			}
			else
			{
				cout << "404,wanna try again?\nEnter \"1\" to try again or \"2\" to exist." << endl;
				int choice = 0;
				cin >> choice;
				if (choice == 1)
				{
					system("cls");
					continue;
				}
				else
				{
					system("cls");
					return;
				}
			}
		}
	}
}

//添加密码
void Password::addPassword()
{
	Password pass;
	v.push_back(pass);
	v[mNum].setAccount();
	v[mNum].setPassword();
	mNum++;
	//将密码保存到文件中
	this->savePassword();
	//文件不为空
	this->mFilePasswordIsEmpty= false;	
	cout << "Done!" << endl;
	system("pause");
	system("cls");
}

//根据网站、app名查找密码或根据账号查找密码
void Password::showSinglePassword()
{
	if (mFilePasswordIsEmpty)
	{
		cout << "Nothing here!" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		while (true)
		{
			cout << "Please enter the name of the target Website/app or account whose password you want to find:" << endl;
			int index = findIndex();
			if (index != -1)
			{
				cout << "Website or App:\t" << v[index].mName << endl;
				cout << "Account:\t" << v[index].mAccount << endl;
				cout << "Password:\t" << v[index].mPassword << endl;
				system("pause");
				system("cls");
				return;
			}
			else
			{
				cout << "404,wanna try again?\nEnter \"1\" to try again or \"2\" to exist." << endl;
				int choice = 0;
				cin >> choice;
				if (choice == 1)
				{
					system("cls");
					continue;
				}
				else
				{
					system("cls");
					return;
				}
			}
		}
	}
}

//删除某条密码
void Password::deleteSinglePassword()
{
	if (mFilePasswordIsEmpty)
	{
		cout << "Nothing here!" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		while (true)
		{
			cout << "Please enter the name of the target Website/app or account whose password you want to delete:" << endl;
			int index = findIndex();
			if (index != -1)
			{
				vector<Password>::iterator it = v.erase(v.begin() + index);
				mNum--;
				cout << "Done!" << endl;
				this->savePassword();//同步更新到文件中
				system("pause");
				system("cls");
				return;
			}
			else
			{
				cout << "404,wanna try again?\nEnter \"1\" to try again or \"2\" to exist." << endl;
				int choice = 0;
				cin >> choice;
				if (choice == 1)
				{
					system("cls");
					continue;
				}
				else
				{
					system("cls");
					return;
				}
			}
		}
	}
}

//删除所有密码
void Password::deleteAllPassword() 
{
	if (mFilePasswordIsEmpty)
	{
		cout << "Nothing here!" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "Are you sure?" << endl;
		cout << "Enter 1 to going on or 2 to exist." << endl;
		int temp = 0;
		cin >> temp;
		if (temp == 1)
		{
			v.clear();
			mNum = 0;
			cout << "Done!" << endl;
			this->savePassword();//同步更新到文件中
			mFilePasswordIsEmpty = true;
			system("pause");
			system("cls");
		}
		else
		{
			system("cls");
			return;
		}
	}
}

//查找密码是否存在并返回其在vector容器中的位置
int Password::findIndex()
{
	string target;
	cin >> target;
	for (int index=0;index<mNum;index++)
	{
		if ((v[index].mName == target) || (v[index].mAccount == target))
		{
			return index;
		}
		else
		{
			continue;
		}
	}
	return -1;
}

//统计文件中密码数目
int Password::getPasswordNum()
{
	ifstream ifs;
	ifs.open(FILEPASSWORD, ios::in);//打开文件
	string name, account, password;
	int num = 0;
	while (ifs >> name && ifs >> account && ifs >> password)
	{
		//统计现有密码数
		num++;
	}
	return num;
}

//利用已有文件初始化vector容器
void Password:: initialPassword()
{
	ifstream ifs;
	ifs.open(FILEPASSWORD, ios::in);
	string name, account, password;
	while (ifs >> name && ifs >> account && ifs >> password)
	{
		Password pass(name, account, password);
		v.push_back(pass);
	}
	mFilePasswordIsEmpty = false;
	ifs.close();//关闭文件
}

//退出密码本
bool Password::exitPassword()
{
	cout << "Thanks for using!" << endl;
	system("pause");
	system("cls");
	return false;
}

//将密码保存到文件中
void Password::savePassword()
{
	ofstream ofs;
	ofs.open(FILEPASSWORD, ios::out);//用输出方式打开文件——写文件

	for (int i = 0; i < this->mNum; i++)
	{
		ofs << v[i].mName << "\n" << v[i].mAccount << "\n" << v[i].mPassword<< endl;
	}
	ofs.close();
}
