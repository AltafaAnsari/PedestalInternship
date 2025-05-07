#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdio>

using namespace std;

string FILENAME = "students.csv";

struct Student
{
    string name;
    int rollNumber;
    float marks;
    string grade;
};

void addStudent()
{
    Student s;
    ofstream file;
    file.open(FILENAME, ios::app);

    cout << "Enter Name >> ";
    cin >> s.name;
    file << s.name << ",";

    cout << "Enter Roll Number >> ";
    cin >> s.rollNumber;
    file << s.rollNumber << ",";

    cout << "Enter Marks >> ";
    cin >> s.marks;
    file << s.marks << ",";

    cout << "Enter Grade >> ";
    cin.ignore();
    cin >> s.grade;
    file << s.grade << endl;

    file.close();
}

vector<Student> getStudents()
{
    ifstream file(FILENAME);
    string line;
    vector<Student> s;
    getline(file, line);

    while (getline(file, line))
    {
        stringstream ss(line);
        string name, rollNumber, mark, grade;

        getline(ss, name, ',');
        getline(ss, rollNumber, ',');
        getline(ss, mark, ',');
        getline(ss, grade, ',');

        int rollNum = stoi(rollNumber);
        float marks = stof(mark);

        s.push_back({name, rollNum, marks, grade});
    }
    file.close();
    return s;
}

Student getStudentByRollNumber(vector<Student> students, int rollNumber)
{
    for (int i = 0; i < students.size(); i++)
    {
        if (students[i].rollNumber == rollNumber)
            return students[i];
    }
}

void updateStudent(int rollNumber)
{
    vector<Student> students = getStudents();
    ofstream file(FILENAME);
    file << "Name,RollNumber,Marks,Grade" << endl;
    int choice;

    cout << "-----------------------------------------------" << endl;
    cout << "1) Update Name" << endl;
    cout << "2) Update Marks" << endl;
    cout << "3) Update Grade" << endl;

    for (int i = 0; i < students.size(); i++)
    {
        Student s = students[i];
        if (rollNumber == s.rollNumber)
        {
            cout << "Enter your choice >> ";
            cin >> choice;

            switch (choice)
            {
            case 1:
            {
                string name;
                cout << "Enter new name >> ";
                cin >> name;
                s.name = name;
                break;
            }

            case 3:
            {
                string grade;
                cout << "Enter new grade >> ";
                cin >> grade;
                s.grade = grade;
                break;
            }

            case 2:
            {
                float marks;
                cout << "Enter new marks >> ";
                cin >> marks;
                s.marks = marks;
                break;
            }

            default:
                break;
            }
        }
        file << s.name << "," << s.rollNumber << "," << s.marks << "," << s.grade << endl;
    }
    file.close();
}

void deleteStudent(vector<Student> students, int rollNumber)
{
    for (int i = 0; i < students.size(); i++)
    {
        if (students[i].rollNumber == rollNumber)
        {
            remove("student[i]");
            return;
        }
    }
}

void sortStudents()
{
    vector<Student> students = getStudents();
    int choice;
    cout << "1) Sort By Marks\n2) Sort By Name" << endl;
    cout << "Enter your choice > ";
    cin >> choice;

    sort(students.begin(), students.end(), [choice](const Student &a, const Student &b)
         {
        if(choice == 1)
            return a.marks > b.marks;
        else
            return a.name < b.name; });
    ofstream file(FILENAME);
    file << "Name,RollNumber,Marks,Grade\n";

    for (int i = 0; i < students.size(); i++)
    {
        Student s = students[i];
        file << s.name << "," << s.rollNumber << "," << s.marks << "," << s.grade << endl;
    }
    file.close();
}

int main()
{
    int choice;

    
    cout << "-----------------------------------------------" << endl;
    cout << "1) To add details of a student." << endl;
    cout << "2) To view details of all students." << endl;
    cout << "3) To search a student by roll number." << endl;
    cout << "4) To update details of a student." << endl;
    cout << "5) To delete details of a student." << endl;
    cout << "6) To sort student's details by marks or by name." << endl;

    cout << "Choose a prefered choice." << endl;
    cin>>choice;

    switch(choice)
    {
        case 1:
        {
            addStudent();
        }
        case 2:
        {
            getStudents();
        }
        case 3:
        {
            vector<Student> students;
            int roll;
            cout<<"Enter the roll number of student to check the details: "<<endl;
            cin>>roll;
            getStudentByRollNumber(students, roll);
        }
        case 4:
        {
            int roll;
            cout<<"Enter roll number to update details of a student: "<<endl;
            cin>>roll;

            updateStudent(roll);
        }
        case 5:
        {
            vector<Student> students;
            int roll;
            cout<<"Enter the roll number to delete details of a student: "<<endl;
            cin>>roll;

            deleteStudent(students, roll);
        }
        case 6:
        {
             sortStudents();
        }
        default:
        {
            cout<<"Invalid Choice.\n";
            break;
        }
    }

    return 0;
}
