#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include<sstream>
#include <chrono>
#include <thread>
using namespace std;
void clearScreen();

class WorkRecord {
private:
    string date;
    string time;
    string location;
    string content;

public:
    WorkRecord(const string& date, const string& time, const string& location, const string& content)
        : date(date), time(time), location(location), content(content) {}//构造函数
    void displayRecord() const;//显示单独的
    //get方法
    string getDate() const { return date; }
    string getTime() const { return time; }
    string getLocation() const { return location; }
    string getContent() const { return content; }
};

class WorkRecorder {
private:
    vector<WorkRecord> records;

public:
    void showMenu();//显示菜单
    void addRecord();//添加
    void displayAllRecords() const;//显示全部
    void deleteRecord();//删除
    bool isValidDate(const string& date) const;//日期是否合法
    bool isValidTime(const string& time) const;//时间是否合法
    void modifyRecorder();//修改记录
    void saveToFile(const string& filename) const;//文件保存
    void loadFromFile(const string& filename);//文件读取
    void tomatoClock();//番茄时钟
};


