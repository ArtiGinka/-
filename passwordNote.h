#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
constexpr auto FILEPASSWORD = "PasswordNote.txt";
using namespace std;
/*
	密码：
		属性：
			账号归属地name，账号account，密码password（私有），密码本密码（静态）,存储密码的vector数组
			行为：对外的密码接口
			成员函数：
				设置账号名、账号、密码；显示所有账号密码；修改账号密码;根据网站、app名查找密码或根据账号查找密码；添加密码；删除某条密码；删除所有密码；
*/
class Password
{
private:
	string mName;
	string mAccount;
	string mPassword;
	static string mNotePassword;//查看所有密码所需的前置密码
	static vector<Password>v;
	static int mNum;//密码本中密码的数量
	bool mFilePasswordIsEmpty;//判断密码本文件是否为空
public:
	bool mIsSetNotePassword=false;//前置密码是否设置
	string getName() { return this->mName; }
	string getAccount() { return this->mAccount; }
	string getPassword() { return this->mPassword; }
	Password();//默认构造函数
	Password(string name, string account, string password);//有参构造函数
	void showPasswordMenu();//显示密码本菜单
	void setNotePassword();//设置密码本密码
	void setAccount();//设置账号
	void setPassword();//设置密码
	void showPassword() const;//显示账号与密码
	void changePassword();//修改密码
	void showSinglePassword();//根据网站、app名查找密码或根据账号查找密码
	void addPassword();//添加密码
	void deleteSinglePassword();//删除某条密码
	void deleteAllPassword();//删除所有密码
	int findIndex();//查找密码是否存在并返回其在vector容器中的位置
	int getPasswordNum();//统计文件中密码数目
	void initialPassword();//利用已有文件初始化vector容器
	bool exitPassword();//退出密码本
	void savePassword();//将密码保存到文件中
};

