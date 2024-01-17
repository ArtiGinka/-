#pragma once
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<iomanip>//用于设置输入占位操作，使课程表更具可视性
#include<algorithm>
#include<tchar.h>
#include<Windows.h>
using namespace std;
//2. 课程备忘录，记录上课的课表，课程提醒，作业ddl提醒，以及其他课程学习相关事务的管理；
/*
	功能实现：
		1、课表表格形式呈现（单独实现）:显示课表，添加课程信息（包含是否合法等），修改课程信息，删除课程(√)//////未实现的功能和未解决的问题：中文乱码问题，未实现按照周一到周日的时间和每天从早到晚的时间进行排序；
		2、自动提醒明天课程
		3、作业备忘录（提前两天）
		4、作业ddl提醒
		5、网课通道(记录网课，查看网课，跳转到网课地址，修改网课地址，删除网课)（名称，地址）
		6、考试备忘录及考试提醒（提前一周、提前三天、提前一天）
*/
constexpr auto FILECURRICULUM = "Curriculum.txt";
constexpr auto FILEHOMEWORK = "Homework.txt";
constexpr auto FILEONLINECOURSE = "OnlineCourse.txt";
//课程表
class Curriculum
{
private:
	string mCourseDate;//课程日期：周一至周日
	string mCourseTime;//课程时间：第一至十三节
	string mCourseName;//课程名称
	string mCourseLocation;//课程地点
	static vector<Curriculum>v;//记录所有的课程
public:	
	
	Curriculum();//默认构造函数
	Curriculum(string courseDate, string CourseTime, string CourseName, string CourseLocation);//含参构造函数
	void showMenuCourseTable();//课程表菜单
	void showCurriculum();//显示课表
	void addCurriculum();//添加课程
	void changeCurriculm();//修改课程信息
	void deleteCurriculm();//删除课程
	void saveCurriculum();//将课程信息保存到文件中
	void initialCurriculum();//打开时用文件内容初始化课表
	vector<Curriculum>& getV() { return v; }//课程数组的对外接口
	string& getCourseDate() { return mCourseDate; }//课程星期对外接口
	string& getCourseName() { return mCourseName; }
	string& getCourseTime() { return mCourseTime; }
	string& getCourseLocation() { return mCourseLocation; }
};

///////////////////////////////////////////////////////////////////////////////////////////////////
//作业
class Homework
{
private:
	int mYear;
	int mMonth;
	int mDay;
	string mName;
	string mTips;
	static vector<Homework>v;//用于存储作业
public:
	int& getHomeworkYear() { return mYear; }
	int& getHomeworkMonth() { return mMonth; }
	int& getHomeworkDay() { return mDay; }
	string& getHomeworkName() { return mName; }
	string& getTips() { return mTips; }
	vector<Homework>& getV() { return v; }//作业数组的对外接口
	Homework();//默认构造函数
	Homework(int year,int month,int day,string name,string tips):mYear(year),mMonth(month),mDay(day),mName(name),mTips(tips){}//含参构造函数
	void showMenuHomework();//作业菜单
	void addHomework();//添加作业
	void deleteHomework();//删除作业
	void homeworkReminding();//提醒作业（提前三天）
	void homeworkDDL();//作业ddl提醒（提前一天）
	void showHomework();//显示作业
	void saveHomework();//将作业保存到文件中
	void initialHomework();//使用文件初始化作业
};
///////////////////////////////////////////////////////////////////////////////////////////////////
//网课
class OnlineCourse
{
private:
	wstring mName;
	wstring mUrl;
	static vector<OnlineCourse>v;
public:
	OnlineCourse();//默认构造函数
	OnlineCourse(wstring name,wstring url):mName(name),mUrl(url){}//含参构造函数
	void showMenuOnline();//菜单
	void addOnlineCourse();//添加网课
	void checkOnlineCourse();//显示网课
	void goOnlineCourse();//进入网课网页
	void deleteOnlineCourse();//删除网课
	void initialOnlineCourse();//文件初始化
	void saveOnlineCourse();//文件流写入
};




///////////////////////////////////////////////////////////////////////////////////////////////////
//课程备忘录
class CourseNote
{
private:
	Curriculum c;
	Homework h;
	OnlineCourse o;
public:
	void showMenuCourseNote();//显示菜单
	void remindTakeCourse();//提醒上课
	void showCourseRemindUsing(vector<Curriculum>::iterator temp);//提醒上课功能需要用到的显示函数体的封装

};

