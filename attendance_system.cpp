#include <limits>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <cstring>
using namespace std;
class student {
    string password, rollno, attendance;
    int totalPresent = 0, totalClasses = 0, recordFound = 0;

public:
    int login()//Student Login
    {
        ifstream read;
        string usrn, passwd;
        read.open("db.txt");//db.txt contains username and password for each student
        cout << "\nEnter rollno " << endl;
        cin >> usrn;
        cout << "Enter password " << endl;
        cin >> passwd;
        if (read) {
            string username, temppassword;

            while (getline(read, username)) {

                getline(read, temppassword);
                if (usrn == username && passwd == temppassword) {//verifying student credentials
                    rollno = username;
                    password = passwd;
                    recordFound = 1;
                    break;
                }
            }
        }
        cout << "Recordfound " << recordFound << endl;
        return recordFound;
    }
    void Register()
    {
        cout << "\n ----- Form to Register Student ---- \n";
        cout << "\n Enter rollno : ";
        cin >> rollno;

        cout << "\n Enter password : ";
        cin >> password;
        //check if record already exist..
        ifstream read;
        read.open("db.txt");//to check whether username already exists or not

        if (read) {
            int recordFound = 0;
            string line;
            while (getline(read, line)) {
                if (line == rollno) {
                    recordFound = 1;
                    break;
                }
            }
            if (recordFound == 1) {
                cout << "\n Username already Register. Please choose another username ";
                getchar();
                getchar();

                read.close();
            }
        }
        read.close();

        ofstream out;
        out.open("db.txt", ios::app);//adding username and password to the db file for the new registration
        out << rollno << "\n" << password << "\n";
        out.close();

        ofstream out1;//creating text file of each student
        string temp = rollno + ".txt";
        out1.open(temp.c_str());
        out1 << rollno << "\n";
        out1 << password << "\n";
        out1.close();

        cout << "\n Student Registered Successfully !!\n";
    }
    string returnId()
    {
        return rollno;
    }
    void updateAttendance()//function to update the attendance
    {
        int date, month, year;
        int i, n, k, a, c;
        int z[20];
        try {
            cout << ">>ENTER ANY KEY TO GIVE THE DATE... " << endl;
            cin >> i;

            while (i) {
                cout << "->Enter DATE/MONTH/YEAR: " << endl;
                cin >> date >> month >> year;
                cout << endl;
                if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
                    if (date > 31 || date == 0) {
                        c = 0;
                    }
                    else {
                        c = 1;
                    }
                }
                if (month == 4 || month == 6 || month == 9 || month == 11) {
                    if (date > 30 || date == 0) {
                        c = 0;
                    }
                    else {
                        c = 1;
                    }
                }
                if (month == 2) {
                    if (date > 29 || date == 0) {
                        c = 0;
                    }
                    else {
                        c = 1;
                    }
                }
                if (month > 12) {
                    c = 0;
                }
                if (month == 0 || year == 0) {
                    c = 0;
                }
                switch (c) //gives if the given date is correct or not and update
                {
                case 0:
                    cout << "Please enter::VALID DATE::" << endl
                         << endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                case 1:
                    cout << ">>ENTER NUMBER OF PERIODS IN THE DAY...(max periods=7): ";
                    cin >> n;
                    cout << endl;
                    for (k = 1; k < n + 1; k++) {
                        cout << "->ENTER '1' IF PRESENT ELSE '0' TO UPDATE THE STATUS OF PERIOD " << k << " :";
                        cin >> a;
                        if (a == 1) {
                            totalPresent++;
                            totalClasses++;
                            z[k] = 1;
                            cout << "   ......................................................................" << endl
                                 << endl;
                            cout << "                         :::UPDATED AS PRESENT:::" << endl
                                 << endl;
                            cout << "   ......................................................................" << endl
                                 << endl;
                        }
                        else {
                            totalClasses++;
                            z[k] = 0;
                            cout << "   ......................................................................" << endl
                                 << endl;
                            cout << "                          :::UPDATED AS ABSENT:::" << endl
                                 << endl;
                            cout << "   ......................................................................" << endl
                                 << endl;
                        }
                    }
                    cout << endl;

                    cout << "                    ::::::ATTENDANCE OF THE DAY IS UPDATED AS:::::" << endl;
                    attendance = attendance + "                    ::::::ATTENDANCE OF THE DAY IS UPDATED AS:::::" + "\n";

                    for (k = 1; k < n + 1; k++) {
                        cout << "__________";
                        attendance = attendance + "__________";
                    }
                    cout << endl
                         << endl;
                    attendance = attendance + "\n\n";

                    cout << "DD/MM/YY    ";
                    attendance = attendance + "DD/MM/YY    ";
                    for (k = 1; k < n + 1; k++) {
                        cout << "p" << k << "    ";
                        attendance = attendance + "p" + to_string(k) + "    ";
                    }
                    cout << endl
                         << endl;
                    attendance = attendance + "\n\n";

                    cout << date << "/" << month << "/" << year << "   ";
                    attendance = attendance + to_string(date) + "/" + to_string(month) + "/" + to_string(year) + "   ";
                    for (k = 1; k < n + 1; k++) {
                        if (z[k] == 1) {
                            cout << "P"
                                 << "     ";
                            attendance = attendance + "P     ";
                        }
                        else {
                            cout << "A"
                                 << "     ";
                            attendance = attendance + "A     ";
                        }
                    }
                    cout << endl
                         << endl;
                    attendance = attendance + "\n\n";

                    for (k = 1; k < n + 1; k++) {
                        cout << "__________";
                        attendance = attendance + "__________";
                    }
                    cout << endl;
                    attendance = attendance + "\n";
                    cout << endl;
                    attendance = attendance + "\n";
                    cout << ">>ENTER 1 TO TO UPDATE ANOTHER DAY ELSE 0  :";
                    cin >> i;
                    cout << endl;
                    break;
                default: //To exit
                    exit(0);
                }
            }
        }
        catch (...) {//Exception handling
            cout << "Sorry wrong input" << endl;
        }
    }
    void read(ifstream* in) { in->read((char*)this, sizeof(student)); }
    void write(ofstream* out) { out->write((char*)this, sizeof(student)); }
    friend std::ostream& operator<<(std::ostream& os, const student& s)
    {
        const size_t attendanceSize = s.attendance.size();

        os << attendanceSize;
        os.write(s.attendance.data(), attendanceSize);
        os << s.totalPresent;
        os << "\n";
        os << s.totalClasses;
        return os;
    }
    friend std::istream& operator>>(std::istream& is, student& s)
    {
        size_t nameSize = 0, attendanceSize = 0, rollSize = 0;
        size_t tempAttendanceSize = 0;
        string tempAttendance, att;
        int counter = 0, tp = 0, tc = 0;

        is >> attendanceSize;

        s.attendance.resize(attendanceSize);
        is.read(&s.attendance[0], attendanceSize);

        is >> s.totalPresent;
        is >> s.totalClasses;

        s.print();

        return is;
    }
    void print()
    {
        cout << rollno << endl;
        cout << attendance;
        cout << "Total classes " << totalClasses << endl;
        cout << "Total Present " << totalPresent << endl;
    }
    void printrollname()
    {
        cout << rollno << endl;
    }
};

class Teacher {   //Teacher class
    string username = "Teacher", password = "Teacher@001";
    int check = 0;

public:
    Teacher()
    {
        login();
    }
    void login()//Teacher Login
    {
        string tempusername, tempTeacherpass;
        cout << "Enter Teacher username" << endl;
        cin >> tempusername;
        cout << "Enter Teacher password" << endl;
        cin >> tempTeacherpass;
        if (username == tempusername && password == tempTeacherpass) {
            check = 1;
        }

        if (check == 1) {
            menu();
        }
        else {
            cout << "Wrong credentials" << endl;
        }
    }
    void menu()
    {
        cout << "\n 1 Register a Student";
        cout << "\n 2 update the attendance for all students";
        cout << "\n 3 Update attendance for a specific student";
        cout << "\n 0. Go Back <- \n";
        int choice, goBack = 0;

        cout << "\n Enter you choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            registerStudent();
            break;
        case 2:
            updateattendance();
            break;
        case 3:
            updatespecific();
            break;
        case 0:
            goBack = 1;
        default:
            cout << "\n Invalid choice. Enter again ";
            getchar();
        }
    }
    void registerStudent()
    {
        student s;
        s.Register();
    }
    void updatespecific() //to update attendance for specific student
    {
        string rollno;
        cout << "Enter roll number of student" << endl;
        cin >> rollno;
        student s1;
        string temp = rollno + ".txt";
        std::ifstream in(temp.c_str(), ios::in | ios::binary);
        in >> s1;
        cout << "Enter attendance for roll number " << rollno << endl;

        s1.updateAttendance();
        std::ofstream ofs;
        ofs.open(temp.c_str(), std::ofstream::out | std::ofstream::trunc);
        ofs.close();
        std::ofstream out(temp.c_str(), ios::out | ios::binary);
        out << s1;
        // store the object to file
        out.close();
    }
    void updateattendance()//to update attendance for each registerd student
    {
        ifstream read;
        read.open("db.txt");

        if (read) {
            string username, password;

            while (getline(read, username)) {
                getline(read, password);
                student s1;
                string temp = username + ".txt";
                std::ifstream in(temp.c_str(), ios::in | ios::binary);
                in >> s1;
                cout << "Enter attendance for roll number " << username << endl;

                s1.updateAttendance();
                std::ofstream ofs;
                ofs.open(temp.c_str(), std::ofstream::out | std::ofstream::trunc);
                ofs.close();
                std::ofstream out(temp.c_str(), ios::out | ios::binary);
                out << s1;
                // store the object to file
                out.close();
            }
        }
    }
};

int main()
{
    while (1) {
        system("clear");
        cout << "\n\t\tMenu" << endl;
        cout << "1. Student Login" << endl;
        cout << "2. Teacher Login" << endl;
        cout << "\nPress anything else to Exit" << endl
             << "-->";
        int choice;
        cin >> choice;
        if (choice == 1) {
            system("clear");
            student s;
            if (s.login()) {
                system("clear");
                string id = s.returnId();
                string temp = id + ".txt";

                std::ifstream in(temp.c_str(), ios::in | ios::binary);
                in >> s;
                cout<<"\n\nPress any key to return to menu"<<endl;
                string tempch;
                cin>>tempch;
            }
            else {
                cout << "Wrong credentials" << endl;
            }
        }
        else if (choice == 2) {
            system("clear");
            Teacher a;
        }
        else {
            break;
        }
    }

    return 0;
}

