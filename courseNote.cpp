#include "courseNote.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*   课程表     */
vector<Curriculum>Curriculum::v(0);
//默认构造函数
Curriculum::Curriculum()
{
	//情况一：文件不存在
	ifstream ifs;
	ifs.open(FILECURRICULUM, ios::in);//读文件
	if (!ifs.is_open())
	{
		ifs.close();
		return;
	}
	//情况二：文件存在但是数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		ifs.close();
		return;
	}
	//情况三：文件存在且需要保存已有数据
	//将文件中的数据存入vector容器
	initialCurriculum();
}

//含参构造函数
Curriculum::Curriculum(string courseDate, string courseTime, string courseName, string courseLocation)
{
	mCourseDate = courseDate;
	mCourseTime = courseTime;
	mCourseName = courseName;
	mCourseLocation = courseLocation;
}

//课程表菜单
void Curriculum::showMenuCourseTable()
{
	while (true)
	{ 
		system("cls");
		cout << "Welcome to use the CourseTable!" << endl;
		system("date/T");
		system("TIME /T");
		cout << string(60, '*') << endl;
		cout << string(10, '*') <<std::left<<setw(40)<<"Welcome to use the course table! qwq" << std::left << string(10, '*') << endl;
		cout << string(10,'*') << std::left << setw(40) << "0.Exist" <<std::left<< string(10, '*') << endl;
		cout << string(10, '*') << std::left << setw(40) << "1.Add your course" << std::left<<string(10, '*')<< endl;
		cout << string(10, '*') << std::left << setw(40) << "2.Check your course" << std::left << string(10, '*')<< endl;
		cout << string(10, '*') << std::left << setw(40) << "3.Delete your course" << std::left << string(10, '*')<< endl;
		cout << string(10, '*') << std::left << setw(40) << "4.Change your course" << std::left << string(10, '*')<< endl;
		cout << string(60, '*') << endl;
		int choice = -1;
		cin >> choice;
		if (choice == 0)
			return;
		else if (choice == 1)
			addCurriculum();
		else if (choice == 2)
			showCurriculum();
		else if (choice == 3)
			deleteCurriculm();
		else if (choice == 4)
			changeCurriculm();
	}
}

//显示课程
void Curriculum::showCurriculum()
{
	cout << "Curriculum：" << endl;
	cout <<string(70,'-') << endl;
	cout <<std::left<<setw(20)<<"Name"<<std::left<<setw(30)<<"TIME"<<std::left<<setw(20)<<"LOCATION" << endl;
	cout << string(70, '-') << endl;
	for (vector<Curriculum>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << std::left << setw(20) << it->mCourseName 
			<< std::left << setw(10) << it->mCourseDate <<std::left<<setw(20)<< it->mCourseTime 
			<< std::left << setw(20) << it->mCourseLocation << endl;
	}
	system("pause");
}

bool dateIsStandard(string& date);
//添加课程
void Curriculum::addCurriculum()
{
	Curriculum courseTable("0", "0", "0", "0");
	cout << "Please enter the information of the course:" << endl;
	cout << "WeekDays(\"Monday,Tuesday...\"):";
	cin >> courseTable.mCourseDate;
	bool temp=dateIsStandard(courseTable.mCourseDate);
	if (temp == false)
	{
		cout << "Wrong Time!" << endl;
		system("pause");
		return;
	}
	cout << "Time（\"8:00--9:35\"）:" << endl;
	cin >> courseTable.mCourseTime;
	cout << "Name(\"Programing-D\"):" << endl;
	cin >> courseTable.mCourseName;
	cout << "Location:（\"Area-First-6-106 \"）" << endl;
	cin >> courseTable.mCourseLocation;
	v.push_back(courseTable);
	cout << "Done!" << endl;
	saveCurriculum();
	system("pause");
	return;
}

//删除课程
void Curriculum::deleteCurriculm()
{
	cout << "Please enter the name of the course you wanna to delete!(You'd better never take it again)" << endl;
	string name;
	cin >> name;
	for (vector<Curriculum>::iterator it = v.begin(); it != v.end(); it++)
	{
		if (it->mCourseName == name)
		{
			v.erase(it);
			saveCurriculum();
			cout << "Done!" << endl;
			system("pause");
			return;
		}
	}
	cout << "404 NOT FOUND!" << endl;
	system("pause");
	return;
}

//修改课程信息
void Curriculum::changeCurriculm()
{
	cout<< "Please enter the name of the course you wanna to change!(Make it right,please!)" << endl;
	string formerName;
	cin >> formerName;
	for (vector<Curriculum>::iterator it = v.begin(); it != v.end(); it++)
	{
		if (it->mCourseName == formerName)
		{
			cout << "New Date:(Former:" << it->mCourseDate << ")";
			string newDate;
			cin >> newDate;
			bool temp = dateIsStandard(newDate);
			if (temp == false)
			{
				cout << "Wrong Time!" << endl;
				system("pause");
				return;
			}
			it->mCourseDate = newDate;
			cout << "New Time:(Former:" << it->mCourseTime << ")";
			string newTime;
			cin >> newTime;
			it->mCourseTime = newTime;
			cout << "New Location:(Former:" << it->mCourseLocation << ")";
			string newLocation;
			cin >> newLocation;
			it->mCourseDate = newLocation;
			saveCurriculum();
			cout << "Done" << endl;
			system("pause");
			return;
		}
	}
	cout << "404 NOT FOUND!" << endl;
	system("pause");
	return;
}

//将课程信息保存到文件中
void Curriculum::saveCurriculum()
{
	ofstream ofs;
	ofs.open(FILECURRICULUM, ios::out);//用输出方式打开文件——写文件

	for (int i = 0; i < v.size(); i++)
	{
		ofs << v[i].mCourseDate << "\t" << v[i].mCourseTime << "\t" << v[i].mCourseName <<"\t" 
			<<v[i].mCourseLocation<< endl;
	}
	ofs.close();
}


//使用文件中的数据初始化课程表
void Curriculum::initialCurriculum()
{
	v.clear();
	ifstream ifs;
	ifs.open(FILECURRICULUM, ios::in);
	string date, time, name, location;
	while (ifs >> date&&ifs>>time&&ifs>>name&&ifs>>location)
	{
		Curriculum coursetable(date,time,name,location);
		v.push_back(coursetable);
	}
	ifs.close();//关闭文件

}



//检查日期输入是否合法
bool dateIsStandard(string& date)
{
	if (date == "Monday" || date == "Tuesday" || date == "Wednesday" || date == "Thursday" || date == "Friday" || date == "Saturday" || date == "Sunday")
		return true;
	else
		return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*自动提醒明天课程*/

void CourseNote::remindTakeCourse()
{		
	struct tm t;   //tm结构指针
	time_t now;  //声明time_t类型变量
	time(&now);      //获取系统日期和时间
	localtime_s(&t, &now);   //获取当地日期和时间

		cout << "The courses tomorrow are as follows:" << endl;
		cout << std::left << setw(20) << "Name" << std::left << setw(30) << "TIME" << std::left << setw(20) << "LOCATION" << endl;

		for (vector<Curriculum>::iterator it = c.getV().begin(); it != c.getV().end(); it++)
		{
			switch (t.tm_wday)
			{
			case 0://周日
				if (it->getCourseDate() == "Monday")
					showCourseRemindUsing(it);
				break;
			case 1://周一
				if (it->getCourseDate() == "Tuesday")
					showCourseRemindUsing(it);
				break;
			case 2:
				if (it->getCourseDate() == "Wednesday")
					showCourseRemindUsing(it);
				break;
			case 3:
				if (it->getCourseDate() == "Thursday")
					showCourseRemindUsing(it);
				break;
			case 4:
				if (it->getCourseDate() == "Friday")
					showCourseRemindUsing(it);
				break;
			case 5:
				if (it->getCourseDate() == "Saturday")
					showCourseRemindUsing(it);
				break;
			case 6:
				if (it->getCourseDate() == "Sunday")
					showCourseRemindUsing(it);
				break;
			default:
				break;
			}
		}
}









//提醒上课功能需要用到的显示函数体的封装
void CourseNote::showCourseRemindUsing(vector<Curriculum>::iterator temp)
{
	cout << std::left << setw(20) << temp->getCourseName()
		<< std::left << setw(10) << temp->getCourseDate() <<setw(20)<< temp->getCourseTime()
		<< std::left << setw(20) << temp->getCourseLocation()<< endl;
}





/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*作业备忘录*/
vector<Homework> Homework::v(0);
//默认构造函数
Homework::Homework()
{
	//情况一：文件不存在
	ifstream ifs;
	ifs.open(FILEHOMEWORK, ios::in);//读文件
	if (!ifs.is_open())
	{
		ifs.close();
		return;
	}
	//情况二：文件存在但是数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		ifs.close();
		return;
	}
	//情况三：文件存在且需要保存已有数据
	//将文件中的数据存入vector容器
	initialHomework();
}



//将作业保存到文件中
void Homework ::saveHomework()
{
	ofstream ofs;
	ofs.open(FILEHOMEWORK, ios::out);//用输出方式打开文件——写文件

	for (int i = 0; i < v.size(); i++)
	{
		ofs << v[i].mYear <<"\t" << v[i].mMonth <<"\t" << v[i].mDay << "\t" << v[i].mName << "\t" << v[i].mTips << endl;
	}
	ofs.close();
}

//使用文件中的数据初始化作业
void Homework ::initialHomework()
{
	ifstream ifs;
	ifs.open(FILEHOMEWORK, ios::in);
	int year;
	int month;
	int day;
	string name;
	string tips;
	while (ifs >> year && ifs >>month && ifs >> day && ifs >> name&&ifs>>tips)
	{
		Homework  homework(year,month,day,name,tips);
		v.push_back(homework);
	}
	ifs.close();//关闭文件

}

//显示作业菜单
void Homework ::showMenuHomework()
{
	while (true)
	{
		system("cls");
		cout << "Welcome to use the Homework!" << endl;
		system("date/T");
		system("TIME /T");
		if (v.size() != 0)
		{
			homeworkReminding();
			homeworkDDL();
		}
		cout << string(60, '*') << endl;
		cout << string(10, '*') << std::left << setw(40) << "Your Homework!!! QAQ" << std::left << string(10, '*') << endl;
		cout << string(10, '*') << std::left << setw(40) << "0.Exist" << std::left << string(10, '*') << endl;
		cout << string(10, '*') << std::left << setw(40) << "1.Add your homework" << std::left << string(10, '*') << endl;
		cout << string(10, '*') << std::left << setw(40) << "2.Check your homework" << std::left << string(10, '*') << endl;
		cout << string(10, '*') << std::left << setw(40) << "3.Delete your homework" << std::left << string(10, '*') << endl;
		cout << string(60, '*') << endl;
		int choice = -1;
		cin >> choice;
		if (choice == 0)
			return;
		else if (choice == 1)//添加作业
			addHomework();
		else if (choice == 2)//显示作业
			showHomework();
		else if (choice == 3)//删除作业
			deleteHomework();
	}
}

//添加作业
void Homework ::addHomework()
{
	Homework  p(0, 0, 0, "0", "0");
	cout << "Homework Name(\"Programing-D-Video-164-277\"):";
	cin >> p.mName;
	cout << "Time:" << endl;
	cout << "Year(\"2023\"):";
	cin >> p.mYear;
	cout << "Month(\"1\"):";
	cin >> p.mMonth;
	cout << "Day(\"1\")";
	cin >> p.mDay;
	cout << "Tips(\"Taping-by-yourself!\"):";
	cin >> p.mTips;
	v.push_back(p);
	saveHomework();
	cout << "Done!" << endl;
	system("pause");
}

//显示作业
void Homework ::showHomework()
{
	cout << "Your homework are as follows:" << endl;
	for (vector<Homework >::iterator iter = v.begin(); iter != v.end(); iter++)
	{
		cout << "Name:" << iter->mName << "\tDate:" <<
			iter->mYear <<"." << iter->mMonth <<"." << iter->mDay << "\tTips:" << iter->mTips << endl;
	}
	system("pause");
}

//删除作业
void Homework ::deleteHomework()
{
	cout << "Name of your homework:" << endl;
	string name;
	cin >> name;
	for (vector<Homework >::iterator iter = v.begin(); iter != v.end(); iter++)
	{
		if (iter->mName == name)
		{
			v.erase(iter);
			cout << "Done!" << endl;
			system("pause");
			return;
		}
	}
	cout << "Nothing here!" << endl;
	system("pause");
	return;
}

//自动提醒作业（提前三天）
void Homework ::homeworkReminding()
{
	cout << "Three days to submit:" << endl;
	struct tm t;   //tm结构指针
	time_t now;  //声明time_t类型变量
	time(&now);      //获取系统日期和时间
	localtime_s(&t, &now);   //获取当地日期和时间
	for (vector<Homework >::iterator iter = v.begin(); iter != v.end(); iter++)
	{
		if ((iter->mYear==(t.tm_year+1900))&&(iter->mMonth==(t.tm_mon+1))&&(iter->mDay-t.tm_mday==3))
			cout << "Name:" << iter->mName << "\tDate:" <<
			iter->mYear << iter->mMonth << iter->mDay << "\tTips:" << iter->mTips << endl;
	}
}

//ddl!!!!
void Homework ::homeworkDDL()
{
	cout << "Tomorrow to submit!!!" << endl;
	cout << "ddl as folows:" << endl;
	struct tm t;   //tm结构指针
	time_t now;  //声明time_t类型变量
	time(&now);      //获取系统日期和时间
	localtime_s(&t, &now);   //获取当地日期和时间
	for (vector<Homework >::iterator iter = v.begin(); iter != v.end(); iter++)
	{
		if ((iter->mYear == (t.tm_year + 1900)) && (iter->mMonth == (t.tm_mon + 1)) && (iter->mDay - t.tm_mday == 1))
			cout << "Name:" << iter->mName << "\tDate:" <<
			iter->mYear << iter->mMonth << iter->mDay << "\tTips:" << iter->mTips << endl;
	}
}





/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//网课
vector<OnlineCourse> OnlineCourse::v(0);
//默认构造
OnlineCourse::OnlineCourse()
{
	//情况一：文件不存在
	ifstream ifs;
	ifs.open(FILEONLINECOURSE, ios::in);//读文件
	if (!ifs.is_open())
	{
		ifs.close();
		return;
	}
	//情况二：文件存在但是数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		ifs.close();
		return;
	}
	//情况三：文件存在且需要保存已有数据
	//将文件中的数据存入vector容器
	initialOnlineCourse();
}


//文件初始化
void OnlineCourse::initialOnlineCourse()
{
	wifstream ifs;
	ifs.open(FILEONLINECOURSE,ios::in);
	wstring name;
	wstring url;
	while (ifs >> name&&ifs>>url)
	{
		OnlineCourse onlinecourse (name, url);
		OnlineCourse::v.push_back(onlinecourse);
	}
	ifs.close();//关闭文件
}

//文件流写入 
void OnlineCourse::saveOnlineCourse()
{
	wofstream ofs;
	ofs.open(FILEONLINECOURSE, ios::out);//用输出方式打开文件——写文件

	for (int i = 0; i < v.size(); i++)
	{
		ofs << v[i].mName << "\t"
		<< v[i].mUrl << endl;
	}
	ofs.close();
}

//菜单
void OnlineCourse::showMenuOnline()
{

	while (true)
	{
		system("cls");
		cout << "Welcome to use the Online Course!" << endl;
		system("date/T");
		system("TIME /T");
		cout << string(60, '*') << endl;
		cout << string(10, '*') << std::left << setw(40) << "Online Courses:" << std::left << string(10, '*') << endl;
		cout << string(10, '*') << std::left << setw(40) << "0.Exist" << std::left << string(10, '*') << endl;
		cout << string(10, '*') << std::left << setw(40) << "1.Add your course" << std::left << string(10, '*') << endl;
		cout << string(10, '*') << std::left << setw(40) << "2.Check your course" << std::left << string(10, '*') << endl;
		cout << string(10, '*') << std::left << setw(40) << "3.Delete your course" << std::left << string(10, '*') << endl;
		cout << string(60, '*') << endl;
		int choice = -1;
		cin >> choice;
		if (choice == 0)
			return;
		else if (choice == 1)//添加作业
			addOnlineCourse();
		else if (choice == 2)//显示作业
			checkOnlineCourse();
		else if (choice == 3)//删除作业
			deleteOnlineCourse();
	}
}

//添加
void OnlineCourse::addOnlineCourse()
{
	OnlineCourse online(L"0",L"https://www.bilibili.com/");
	cout << "Name:";
	wcin >> online.mName;
	cout << "URL:";
	wcin >> online.mUrl;
	OnlineCourse::v.push_back(online);
	saveOnlineCourse();
	cout << "Done!" << endl;
	system("pause");
	return;
}

//显示
void OnlineCourse::checkOnlineCourse()
{
	if (v.size() == 0)
	{
		cout << "Nothing here!" << endl;
		system("pause");
		return;
	}
	for (vector<OnlineCourse>::iterator it = v.begin(); it != v.end(); it++)
	{
		wcout << "Name:" << it->mName << "\t";
		wcout << "URL:" << it->mUrl << endl;
	}	
	cout << "You can enter 1 to the browser or \"0\" to exit." << endl;
	int choice = -1;
	cin >> choice;
	if (choice != 1)
		return;
	else
		goOnlineCourse();
}

//跳转
void OnlineCourse::goOnlineCourse()
{
	cout << "Please enter the name of the website:" << endl;
	wstring name;
	wcin >> name;
	for (vector<OnlineCourse>::iterator it = v.begin(); it != v.end(); it++)
	{
		if (it->mName == name)
		{
			ShellExecute(nullptr, _T("open"), it->mUrl.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
			return;
		}
	}
	cout << "Nothing here!" << endl;
	system("pause");
	return;
}

//删除
void OnlineCourse::deleteOnlineCourse()
{
	if (v.size() == 0)
	{
		cout << "Nothing here!" << endl;
		system("pause");
		return;
	}
	cout << "Enter the name:" << endl;
	wstring name;
	wcin >> name;
	for (vector<OnlineCourse>::iterator it = v.begin(); it != v.end(); it++)
	{
		if (it->mName == name)
		{
			v.erase(it);
			saveOnlineCourse();
			cout << "Done!" << endl;
			system("pause");
			return;
		}

	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//课程备忘录
//显示菜单
void CourseNote::showMenuCourseNote()
{
	do
	{
		system("cls");
		cout << "Welcome to use the Course Note" << endl;
		system("date/T");
		system("TIME /T");
		if (c.getV().size() != 0)
		{
			remindTakeCourse();
		}
		if (h.getV().size() != 0)
		{
			cout << "Homework to submit" << endl;
			h.homeworkReminding();
			h.homeworkDDL();
		}
		cout << string(65, '*') << endl;
		cout <<setw(10)<<std::left<<string(10,'*')<< "Welcome to use  the course note!!!!" << setw(20) << std::right<< string(10, '*') << endl;
		cout << setw(10) << std::left << string(10, '*') << "0.Exist" << setw(48) << std::right << string(10, '*') << endl;
		cout << setw(10) << std::left << string(10, '*') << "1.Course Table" << setw(41) << std::right << string(10, '*') << endl;
		cout << setw(10) << std::left << string(10, '*') << "2.Homework    " << setw(41) << std::right << string(10, '*') << endl;
		cout << setw(10) << std::left << string(10, '*') << "3.Online Course    " << setw(41) << std::right << string(10, '*') << endl;
		cout << string(65, '*') << endl;
		int choice = -1;
		cin >> choice;
		switch (choice)
		{
		case 0:
			return;
		case 1://课程表
			c.showMenuCourseTable();
			break;
		case 2://作业
			h.showMenuHomework();
			break;
		case 3://网课
			o.showMenuOnline();
			break;
		default:
			cout << "404" << endl;
			break;
		}
	} while (true);
}

