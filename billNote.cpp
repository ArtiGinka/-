#include<iostream>
#include"billNote.h"

//bool BillNote::exitBillNote()
//{
//	cout << "Thanks for using!" << endl;
//	system("pause");
//	system("cls");
//	return false;
//}
deque<BillNote> BillNote::d(0);
//创建记账本菜单
void BillNote::showBillNoteMenu()
{
	while (true)
	{
		system("cls");
		cout << "The bill\'s numbers in the note is:" << this->d.size() << endl;
		cout << "**Welcome to ues the BillNote!" << endl;
		system("date/T");
		system("TIME/T");
		cout << "*****************************************************************" << endl;
		cout << "**           Choose what you wanna do!                         **" << endl;
		cout << "**               1.Add a bill                                  **" << endl;
		cout << "**               2.Delete a bill                               **" << endl;
		cout << "**               3.Delete all bill                             **" << endl;
		cout << "**               4.Show bill by date                           **" << endl;
		cout << "**               5.Show all bill                               **" << endl;
		cout << "**               6.Check bill in a period                      **" << endl;
		cout << "*****************0.Exit BillNote*********************************" << endl;
		int choiceBillNote = -1;
		cin >> choiceBillNote;
		switch (choiceBillNote)
		{
		case 0:
			return;
		case 1:
			this->addBill();
			break;
		case 2:
			this->deleteSingleBill();
			break;
		case 3:
			this->deleteAllBill();
			break;
		case 4:
			this->showBillByDate();
			break;
		case 5:
			this->showAllBill();
			break;
		case 6:
			this->showBillInPeriod();
			break;
		default:
			break;
		}
	}
}

//默认构造函数
BillNote::BillNote()
{
	//情况一：文件不存在
	ifstream ifs;
	ifs.open(FILEBILLNOTE, ios::in);//读文件
	if (!ifs.is_open())
	{
		//初始化文件是否为空
		mFileBillNoteIsEmpty= true;
		ifs.close();
		return;
	}
	//情况二：文件存在但是数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//初始化属性
		//初始化文件是否为空
		mFileBillNoteIsEmpty= true;
		ifs.close();
		return;
	}
	//情况三：文件存在且需要保存已有数据
	//将文件中的数据存入vector容器
	this->initialBillNote();
}

//含参构造函数
BillNote::BillNote(int NumBill, int Money, string Date, string Tips)
{
	this->mNumBill = NumBill;
	this->mMoney = Money;
	this->mDate = Date;
	this->mTips = Tips;
}


bool judgeDateStandard(string& date);
//输入账目
void BillNote::addBill()
{
	//BillNote bill;
	cout << "Please enter the Date of the bill\nYou may enter like this:\"20230902\"" << endl;
	cin >> this->mDate;
	//设置时间输入是否合法
	bool DateOk = judgeDateStandard(mDate);
	if (DateOk)
	{
		cout << "Please enter the Number of the bill(including\"+\"and\"-\")" << endl;
		cin >> this->mMoney;
		cout << "Please enter the Tips to the bill:(You are not welcomed to use \"blank\"key)" << endl;
		cin.ignore();
		getline(cin, this->mTips);
		this->mNumBill++;
		this->d.push_back(*this);
		this->sortAllBill();
		for (int i = 0; i < this->d.size(); i++)
		{
			this->d[i].mNumBill = i + 1;
		}
		cout << "Done!" << endl;
		this->mFileBillNoteIsEmpty = false;
		this->saveBillNote();
		system("pause");
		return;
	}
	else
	{
		cout << "Wrong Time!" << endl;
		system("pause");
		return;
	}

}

//每次输入完之后对所有账单按照日期从近到远进行排序
void BillNote::sortAllBill()
{
	for (int i = 0; i < this->d.size(); i++)
	{
		int index = i;
		for (int j = i + 1; j < this->d.size(); j++)
		{
			if (this->d[i].mDate < this->d[j].mDate)
			{
				index = j;
			}
		}
		if (index != i)
		{
			BillNote temp(0, 0, "0", "0");
			temp.mMoney = d[i].mMoney;
			d[i].mMoney = d[index].mMoney;
			d[index].mMoney = temp.mMoney;//金额交换

			temp.mDate = d[i].mDate;
			d[i].mDate = d[index].mDate;
			d[index].mDate = temp.mDate;//日期交换

			temp.mTips = d[i].mTips;
			d[i].mTips = d[index].mTips;
			d[index].mTips = temp.mTips;//备注交换

			//temp.mNumBill = d[i].mNumBill;
			//d[i].mNumBill = d[index].mNumBill;
			//d[index].mNumBill = temp.mNumBill;//编号交换
		}
	}
}

//删除所有账目
void BillNote::deleteAllBill()
{
	if (this->mFileBillNoteIsEmpty)
	{
		cout << "Nothing here!" << endl;
		system("pause");
		return;
	}
	cout << "Are you sure?\nEnter 1 to continue or 2 to exit." << endl;
	int choice = 0;
	cin >> choice;
	if (choice == 1)
	{
		this->d.clear();
		cout << "Done!" << endl;
		system("pause");
		this->saveBillNote();
		return;
	}
	else
	{
		return;
	}
}

//显示账目的函数
void BillNote::showBill() const
{
	cout << "Num:" << this->mNumBill << "\t";
	cout << "Money:" << this->mMoney << "\t";
	cout << "Date:" << this->mDate << "\t";
	cout << "Tips:" << this->mTips << "\t" << endl;
}

//删除某个账目
void BillNote::deleteSingleBill()
{
	if (this->mFileBillNoteIsEmpty)
	{
		cout << "Nothing here!" << endl;
		system("pause");
		return;
	}
	while (true)
	{
		cout << "Please enter the date of the bill:" << endl;
		string date;
		cin >> date;
		bool judgeDateExit = false;
		for (int i = 0; i < this->d.size(); i++)
		{
			if (date == d[i].mDate)
			{
				d[i].showBill();	
				judgeDateExit = true;
			}
			else
			{
				continue;
			}
		}
		if (judgeDateExit = true)
		{
			cout << "Choose which one you wanna to delete by Number:" << endl;
			int index = this->findIndexBill();
			if (index!=-1)
			{
				deque<BillNote>::iterator it = this->d.erase(d.begin() + index);
				for (int i = index; i < d.size(); i++)
				{
					d[i].mNumBill -= 1;
				}
				cout << "Done!" << endl;
				this->saveBillNote();
				system("pause");
				return;
			}
			else
			{
				cout << "404,try again?\nEnter 1 to try again or 2 to exit:" << endl;
				int choice;
				cin >> choice;
				if (choice == 1)
				{
					continue;
				}
				else
				{
					return;
				}
			}
		}
	}
}

//按日期显示账目
void BillNote::showBillByDate() const 
{
	if (this->mFileBillNoteIsEmpty)
	{
		cout << "Nothing here!" << endl;
		system("pause");
		return;
	}
	cout << "Please enter the date:" << endl;
	string date;
	cin >> date;
	bool DateOk=judgeDateStandard(date);
	if (DateOk==false)
	{
		cout << "Wrong Time!" << endl;
		system("pause");
		return;
	}
	bool DateExist = this->findDate(date);
	if (!DateExist)
	{
		cout << "404 NOT FOUND!" << endl;
		system("pause");	
		return;
	}
	for (int i = 0; i < this->d.size(); i++)
	{
		if (d[i].mDate == date)
		{
			d[i].showBill();
		}
		else
		{
			continue;
		}
	}
	system("pause");
	return;
}

//查找账目在deque中的位置并返回
int BillNote::findIndexBill()
{
	int target;
	cin >> target;
	for (int index = 0; index < d.size(); index++)
	{
		if (d[index].mNumBill == target)
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

//显示所有账目
void BillNote::showAllBill() const
{
	if (this->mFileBillNoteIsEmpty)
	{
		cout << "Nothing here!" << endl;
		system("pause");
		return;
	}
	for (int i = 0; i < this->d.size(); i++)
	{
		d[i].showBill();
	}
	system("pause");
}


//检查日期输入是否合法函数
bool judgeDateStandard(string &date) 
{
	int length= date.length() ;
	//长度是否符合
	bool judge1 = (length == 8);
	if (judge1 == false)
	{
		return false;
	}	
	string year = date.substr(0, 4);
	string month = date.substr(4, 2);
	string day = date.substr(6, 2);
	//年时间是否符合
	string yearMin = "2000";
	bool judge2 = (year >= yearMin);
	//月时间是否符合
	string monthMin = "01";
	string monthMax = "12";
	bool judge3 =( (month >= monthMin) && (month<= monthMax));
	//日时间是否符合
	string dayMin = "01";
	string dayMax = "31";
	bool judge4 = ((day >= dayMin) && (day<= dayMax));
	if((judge1==0)||(judge2==0)||(judge3==0)||(judge4==0))
	{
		return false;
	}
	else 
	{
		return true;
	}
}

//查找日期是否存在
bool BillNote:: findDate(const string& date) const
{
	bool judge = true;
	for (int i = 0; i < this->d.size(); i++)
	{
		if (date == d[i].mDate)
		{
			judge = true;
			return judge;
		}
		else
		{
			judge = false;
		}
	}
	return judge;
}

//显示某一年的账目，包括总收入总支出，结余
//void BillNote::showBillByOneYear()
//{
//	//分别用于记录收入支出结余
//	int sumIn = 0;
//	int sumOut = 0;
//	int sum = 0;
//	cout << "Please enter the year:" << endl;
//	//判断输入的年份是否合法
//	string targetYear;
//	cin >> targetYear;
//	string year = "2000";
//	bool DateOk = ((targetYear.length() == 4) && (targetYear >= year));
//	if (!DateOk)
//	{
//		cout << "Wrong Time!" << endl;
//		system("pause");
//		return;
//	}
//	//判断输入的年份是否存在
//	bool DateExist = false;
//	for (int i = 0; i < this->d.size(); i++)
//	{
//		if (targetYear == this->d[i].mDate.substr(0, 4))
//		{
//			DateExist = true;
//			break;
//		}
//	}
//	if (DateExist==false)
//	{
//		cout << "404 NOT FOUND!" << endl;
//		system("pause");
//		return;
//	}
//	//分别进行统计
//	for (int i = 0; i < this->d.size(); i++)
//	{
//		if (d[i].mDate.substr(0,4) == targetYear)
//		{
//			d[i].showBill();
//			if (d[i].mMoney >= 0)
//			{
//				sumIn += d[i].mMoney;
//			}
//			else
//			{
//				sumOut += d[i].mMoney;
//			}
//		}
//		else
//		{
//			continue;
//		}
//	}
//	sum = sumIn + sumOut;
//	cout << "Income:" << sumIn << "\tOutcome:" << sumOut << endl;
//	cout << "Remaining:" << sum << endl;
//	system("pause");
//	return;
//}



//按周期进行展示账单
void BillNote::showBillInPeriod()
{
	if (this->mFileBillNoteIsEmpty)
	{
		cout << "Nothing here!" << endl;
		system("pause");
		return;
	}
	//分别用于记录收入支出结余
	int sumIn = 0;
	int sumOut = 0;
	int sum = 0;
	cout << "Please enter the period:\nYou may enter like this:20230501_20230531" << endl;
	//判断输入的日期是否合法
	string date1;
	cin >>date1;
	string date2;
	cin >> date2;
	bool DateOk = (judgeDateStandard(date1) && judgeDateStandard(date2));
	if (!DateOk)
	{
		cout << "Wrong Time!" << endl;
		system("pause");
		return;
	}
	//让date1成为小日期
	if (date1 > date2)
	{
		string temp = date2;
		date2 = date1;
		date1 = temp;
	}
	//判断输入的年份是否存在
	bool DateExist = (this->findDate(date1) && this->findDate(date2));
	if (DateExist==false )
	{
		cout << "404 NOT FOUND!" << endl;
		system("pause");
		return;
	}
	//分别进行统计
	//先获得两个日期的编号
	//date1(小日期)
	int num1=0;//大数
	for (int i = this->d.size()-1; i >=0; i--)
	{
		if (date1 == d[i].mDate)
		{
			num1 = d[i].mNumBill;
			break;
		}
	}
	//date2(大日期)
	int num2 = 0;//小数
	for (int i = 0; i < this->d.size(); i++)
	{
		if (date2 == d[i].mDate)
		{
			num2 = d[i].mNumBill;
			break;
		}
	}
	for (int i = num2; ((i >= num2) && (i <= num1)); i++)
	{
		int k = i - 1;
		if (this->d[k].mMoney >= 0)
		{
			sumIn += this->d[k].mMoney;
		}
		else
		{
			sumOut += this->d[k].mMoney;
		}
	}
	sum = sumIn + sumOut;
	cout << "Income:" << sumIn << "\tOutcome:" << sumOut << endl;
	cout << "Remaining:" << sum << endl;
	system("pause");
	return;
}

//用文件内容初始化账单系统
void BillNote:: initialBillNote()
{
	ifstream ifs;
	ifs.open(FILEBILLNOTE, ios::in);
	int num,money;
	string date, tips;
	while (ifs >> num && ifs >> money && ifs >> date&&ifs>>tips)
	{
		BillNote bill(num,money,date,tips);
		this->d.push_back(bill);
	}
	mFileBillNoteIsEmpty= false;
	ifs.close();//关闭文件
}

//将账单保存到文件中
void BillNote::saveBillNote()
{
	ofstream ofs;
	ofs.open(FILEBILLNOTE, ios::out);//用输出方式打开文件——写文件
	for (int i = 0; i < this->d.size(); i++)
	{
		ofs << this->d[i].mNumBill << "\t" << this->d[i].mMoney << "\t" << this->d[i].mDate <<"\t"<<this->d[i].mTips<< endl;
	}
	ofs.close();
}