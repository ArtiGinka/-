#include<iostream>
#include<string>
#include<vector>
#include<deque>
#include<algorithm>
#include<ctime>
#include<fstream>
constexpr auto FILEBILLNOTE = "BillNote.txt";
using namespace std;
//记账本，记录日常收入和开销，包括分门别类按照周期进行统计及展示；
/*
	功能：
	1、记录收入：+金额，时间，备注，编号
	2、记录支出：-金额，时间，备注，编号
	3、记录每次收入和支出的具体时间
	4、将账目按照收入和支出两种类别显示
	5、将账目按照年月日三个层次进行显示，并统计该时间段内总收入、总支出，结余；
*/

/*
	设计：
		记账本结构体：
		属性：
			金额mMoney，日期mDate，备注mTips，编号mNumBill，总数mTotalBill，总收入mInAll，总支出mOutAll，结余mRemain
		成员函数：
		0、退出
		1、输入账目
		2、删除账目明细条目（日期、收入、支出）
		3、查询账目明细条目（日期、收入、支出）
		4、修改账目明细条目
		6、财务统计（近一月、近三月、近一年）
*/

class BillNote
{
private:
	int mMoney;//金额
	string mDate;//日期
	string mTips;//备注
	int mNumBill=0;//编号
	static int mTotalBill;//总支出
	static int mInAll;//总收入
	static int mRemain;//结余
	static deque<BillNote>d;//deque容器用于存放账目
	bool mFileBillNoteIsEmpty;//判断账本文件是否为空
public:
	BillNote();//默认构造函数
	BillNote(int NumBill, int Money, string Date, string Tips);//含参构造函数
	void showBillNoteMenu();//记账本菜单
	void addBill() ;//输入账目
	void showAllBill() const;//显示所有账目
	void sortAllBill();//每次输入完之后对所有账单按照日期从近到远进行排序
	void deleteAllBill();//删除所有账目
	void showBill() const;//显示账目的函数
	void deleteSingleBill();//删除单个账目
	int findIndexBill();//查找账目在deque中的位置并返回
	void showBillByDate() const;//按日期显示账目
	bool findDate(const string& date)const; //查找日期是否存在
	void showBillInPeriod();//按周期进行展示账单
	void saveBillNote();//将账单保存到文件中
	void initialBillNote();//用文件内容初始化账单系统
};
