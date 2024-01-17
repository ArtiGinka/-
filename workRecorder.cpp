#include "workRecorder.h"
void clearScreen()
{
	system("cls");
}

void WorkRecord::displayRecord() const
{
    cout << "Date: " << date << "\n";
    cout << "Time: " << time << "\n";
    cout << "Location: " << location << "\n";
    cout << "Content: " << content << "\n";
    cout << "-----------------------------\n";
}

void WorkRecorder::showMenu()
{
    
    while (true)
    {
        static WorkRecorder workRecorder;
        clearScreen();
        cout << "Welcome to use the Work Record!" << endl;
        system("date/T");
        system("TIME /T");
        cout << "Menu:\n";
        cout << "1. Add Record\n";
        cout << "2. Display All Records\n";
        cout << "3. Modify Record\n";
        cout << "4. Delete Record\n";
        cout << "5. Tamato Clocks\n";
        cout << "6. Exit\n";
        int choice;
        cout << "Enter your choice (1-5): ";
        cin >> choice;

        switch (choice) {
        case 1:
            workRecorder.addRecord();
            break;
        case 2:
            workRecorder.displayAllRecords();
            break;
        case 3:
            workRecorder.modifyRecorder();
            break;
        case 4:
            workRecorder.deleteRecord();
            break;
        case 5:
            workRecorder.tomatoClock();
        case 6:
            // Save records to file before exiting the program
            workRecorder.saveToFile("work_records.txt");
            cout << "Exiting program.\n";
            return;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 5.\n";
            system("pause");
        }
    }

    return ;
    }


void WorkRecorder::addRecord()
{
    while (true)
    {
        string date, time, location, content;
        cout << "Enter date (YYYY-MM-DD): ";//日期格式范例
        cin >> date;
        if (!isValidDate(date)) {
            cout << "Invalid date format or value.\n";
            continue;
        }
        cout << "Enter time (HH:MM): ";
        cin >> time;
        if (!isValidTime(time)) {
            cout << "Invalid time format or value.\n";
            continue;
        }
        cout << "Enter location: ";
        cin >> location;
        cout << "Enter content: ";
        cin.ignore();  // 在使用getline之前清除缓冲区
        getline(cin, content);
        WorkRecord record(date, time, location, content);
        records.push_back(record);
        cout << "Done!\n";
        system("pause");
        return;
    }
}

void WorkRecorder::displayAllRecords() const
{
    if (records.empty()) {
        cout << "No records found.\n";
        system("pause");
        return;
    }

    cout << "---- All Work Records ----\n";
    for (const auto& record : records) {//范围for循环
        record.displayRecord();
    }
    system("pause");
}

void WorkRecorder::deleteRecord()
{
    int index;
    cout << "Enter the index of the record to delete: ";
    cin >> index;
    if (index >= 0 && index < records.size()) {
        records.erase(records.begin() + index-1);
        cout << "Record deleted successfully.\n";
        system("pause");
        return;
    }
    else {
        cout << "Invalid index. Record deletion failed.\n";
        system("pause");
        return;
    }
}

bool WorkRecorder::isValidDate(const string& date) const
{
    if (date.length() != 10) {
        return false;
    }

    int year = stoi(date.substr(0, 4));//将0-3转为数字便于比较
    int month = stoi(date.substr(5, 2));
    int day = stoi(date.substr(8, 2));

    if (month < 1 || month > 12) {
        return false;
    }

    if (day < 1 || day > 31) {
        return false;
    }

    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        return false;
    }

    if (month == 2) {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            if (day > 29) {
                return false;
            }
        }
        else {
            if (day > 28) {
                return false;
            }
        }
    }

    return true;
}

bool WorkRecorder::isValidTime(const string& time) const
{
    if (time.length() != 5) {
        return false;
    }

    int hour = stoi(time.substr(0, 2));
    int minute = stoi(time.substr(3, 2));

    if (hour < 0 || hour > 23 || minute < 0 || minute > 59) {
        return false;
    }

    return true;
}

void WorkRecorder::modifyRecorder()
{
    int index;
    cout << "Enter the index of the record to modify: ";
    cin >> index;
    if (index<0 || index>records.size())
    {
        cout << "Invalid index. Record modification failed.\n";
        system("pause");
        return;
    }
    string date, time, location, content;
    cout << "Enter new date (YYYY-MM-DD): ";
    cin >> date;
    if (!isValidDate(date)) {
        cout << "Invalid date format or value.\n";
        return;
    }
    cout << "Enter new time (HH:MM): ";
    cin >> time;
    if (!isValidTime(time)) {
        cout << "Invalid time format or value.\n";
        return;
    }
    cout << "Enter new location: ";
    cin >> location;
    cout << "Enter new content: ";
    cin.ignore();  // 清空缓冲区
    getline(cin, content);
    records[index] = WorkRecord(date, time, location, content);
    cout << "Record modified successfully.\n";
    system("pause");
    return;
}

void WorkRecorder::saveToFile(const string& filename) const
{
    ofstream file(filename);

    if (file.is_open()) {
        for (const auto& record : records) {
            file << record.getDate() << ","
                << record.getTime() << ","
                << record.getLocation() << ","
                << record.getContent() << "\n";
        }

        cout << "Records saved to file: " << filename << "\n";
    }
    else {
        cerr << "Unable to open file for writing: " << filename << "\n";
    }
}

void WorkRecorder::loadFromFile(const string& filename)
{
    ifstream file(filename);
    if (file.is_open()) {
        records.clear();  // Clear existing records

        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string date, time, location, content;

            getline(iss, date, ',');
            getline(iss, time, ',');
            getline(iss, location, ',');
            getline(iss, content);

            records.emplace_back(date, time, location, content);
        }

        cout << "Records loaded from file: " << filename << "\n";
    }
    else {
        cerr << "Unable to open file for reading: " << filename << "\n";
    }
}

void WorkRecorder::tomatoClock()
{
    int workTime = 0;
    int breakTime = 0;
    int  pomodoros = 0;//番茄钟轮数
    string name;
    cout << "Enter the name of your task:" << endl;
    cin >> name;
    cout << "Enter the time of your work time(by minutes like:\"25\"):" << endl;
    cin >> workTime;
    cout << "Enter the time of the break time(by minutes like:\"5\"):" << endl;
    cin >> breakTime;
    cout << "Enter the times of the pomodoros ( like \"1\" or \"2\"):" << endl;
    cin >> pomodoros;
    system("cls");
    for (int i = 0; i < pomodoros; i++) {
        cout << "Task:" << name << endl;
        cout << "Pomodoro " << i + 1 << " - Work Time\n";
        this_thread::sleep_for(std::chrono::minutes(workTime));
        cout << "Work Time Finished! Take a Break.\n";
        this_thread::sleep_for(std::chrono::minutes(breakTime));
        cout << "Break Time Finished!\n";
    }
    cout << "Perfect work!" << endl;
    system("pause");
}

