#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<iomanip>
#include<cstdio>
using namespace std;

class Student
{
    int rollno,std;
    char name[40],grade;
    float phy,tot,chem,math,cs,eng,per;

    public:
        void calculate();           //To calculate grade of student
        void enterdata();           //To enter details of new student
        void display();             //To display details of student
        void add_student();         //To create new record of student
        void delete_record();       //To delete record of any student
        void modify_record();      //To modify record of existing student
        void display_all_record();  //To display record of all students
        void search_record();       //To search record of any student
        void display_class();       //To display result of any class
        void display_single();      //To display result of any student
        void single_report_card();  //Format to view report card of any students
        void main_menu();           //Main Menu
        void entry_edit_menu();     //Entry Edit Menu
        void result_menu();         //Result Menu
};Student s;

void Student::calculate()
{
    tot=(phy+chem+cs+eng+math);
    per=((phy+chem+cs+eng+math)/5);
    if(per>=90)
        grade='A';
    else if(per>=80)
        grade='B';
    else if(per>=65)
        grade='C';
    else if(per>=55)
        grade='D';
    else
        grade='F';
}

void Student::enterdata()
{
    cout<<"\nEnter Roll Number of a Stdent :";
    cin>>rollno;
    getchar();
    cout<<"\nEnter Name of a Stdent :";
    cin.getline(name,40);
    cout<<"\nEnter Standard of a Student :";
    cin>>std;
    getchar();
    cout<<"\nEnter marks in Physics :";
    cin>>phy;
    cout<<"\nEnter marks in Chemistry :";
    cin>>chem;
    cout<<"\nEnter marks in Math :";
    cin>>math;
    cout<<"\nEnter marks in English :";
    cin>>eng;
    cout<<"\nEnter marks in Computer Science :";
    cin>>cs;
    calculate();
}

void Student::display()
{
    cout<<"\nRoll Number of Student        :"<<rollno;
    cout<<"\nName of Student               :"<<name;
    cout<<"\nStandard of a Student         :"<<std;
    cout<<"\nMarks in Physics              :"<<phy;
    cout<<"\nMarks in Chemistry            :"<<chem;
    cout<<"\nMarks in Math                 :"<<math;
    cout<<"\nMarks in English              :"<<eng;
    cout<<"\nMarks in Computer Science     :"<<cs;
    cout<<"\nPercentage Obtained           :"<<per;
    cout<<"\nGrade of a Student            :"<<grade;
}

void Student::add_student()
{
    ofstream outfile;
    outfile.open("student.dat",ios::binary|ios::app);
    s.enterdata();
    outfile.write((char*)(&s),sizeof(Student));
    outfile.close();
    cout<<"\nRecord of New Student is created"<<endl;
    cin.ignore();
    cin.get();
}

void Student::delete_record()
{
    int roll,flag =0;
    ifstream infile;
    ofstream outfile;
    cout<<"\n Enter Roll Number of Student whose Record is to be Deleted :";
    cin>>roll;
    infile.open("student.dat",ios::binary|ios::in);
    outfile.open("temp.dat",ios::out);
    while(infile.read((char*)(&s),sizeof(Student)))
    {
        if(roll!=rollno)
            outfile.write((char*)(&s),sizeof(Student));
        else
            flag=1;
    }
    infile.close();
    outfile.close();
    remove("student.dat");
    rename("temp.dat","student.dat");
    if(flag==1)
        cout<<"\n\t RECORD SUCCESSFULLY DELETED ";
    else
        cout<<"\n\t RECORD DOESN'T EXIST";
    cin.ignore();
    cin.get();
    return ;
}

void Student::modify_record()
{
    fstream infile;
    int roll,flag=0;
    cout<<"\nEnter the Roll Number of Student to be Modified :";
    cin>>roll;
    infile.open("student.dat",ios::binary|ios::in|ios::out);
    while(infile.read((char*)(&s),sizeof(Student)) && flag==0)
    {
        if(roll==rollno)
            {
                s.enterdata();
                flag=1;
                long int pos = (-1*sizeof(Student));
                infile.seekp(pos,ios::cur);
                infile.write((char*)(&s),sizeof(Student));

            }
    }
    cout<<"\n\n\t RECORD SUCCESSFULLY MODIFIED!!!";
    infile.close();
    if(flag==0)
        cout<<"\n\n\t RECORD DOESN'T EXIST!!!";
    s.entry_edit_menu();
}


void Student::display_class()
{
    int sems,row=6,n=0;
    ifstream infile;
    infile.open("student.dat",ios::binary|ios::in);
    cout<<"\nEnter Class(1-12) :";
    cin>>sems;
    cout<<"\n\t\t ABCD INTERNATIONAL SCHOOL"<<endl;
    cout<<left<<setw(30)<<"Standard :"<<sems<<"\t\t Session : 20XX-XX"<<endl;
    cout<<"\n----------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<setw(10)<<"Roll No"<<setw(10)<<"Name"<<setw(10)<<""<<"Physics"<<setw(5)<<""<<"Chemistrty"<<setw(5)<<""<<"Maths"<<setw(5)<<""<<"English"<<setw(5)<<""<<"CSE"<<setw(5)<<""<<"Total Marks"<<setw(5)<<""<<"%age"<<setw(5)<<""<<"Grade"<<endl;
    cout<<"\n----------------------------------------------------------------------------------------------------------------------"<<endl;
    while(infile.read((char *)(&s),sizeof(Student)))
    {
        if(sems==std)
        {
            row=row+1;
            n++;
            if(row>=30)
            {
                cout<<"\n\n  Press any key to continue .......";
                cout<<"\n\t\t  ABCD INTERNATIONAL SCHOOL";
                cout<<"\n\t\t Standard :"<<sems<<"\t\t Session : 20XX-XX"<<endl;
                cout<<"\n----------------------------------------------------------------------------------------------------------------------"<<endl;
                cout<<setw(10)<<"Roll No"<<setw(10)<<"Name"<<setw(10)<<""<<"Physics"<<setw(5)<<""<<"Chemistrty"<<setw(5)<<""<<"Maths"<<setw(5)<<""<<"English"<<setw(5)<<""<<"CSE"<<setw(5)<<""<<"Total Marks"<<setw(5)<<""<<"%age"<<setw(5)<<""<<"Grade"<<endl;
                cout<<"\n----------------------------------------------------------------------------------------------------------------------"<<endl;
                row =6;
            }
            cout<<setw(10)<<rollno<<setw(10)<<name<<setw(10)<<""<<phy<<setw(10)<<""<<chem<<setw(10)<<""<<math<<setw(10)<<""<<eng<<setw(8)<<""<<cs<<setw(10)<<""<<tot<<setw(8)<<""<<per<<setw(7)<<""<<grade<<endl;
            cout<<"\n\n";
        }
    }
    infile.close();
    cout<<"\n----------------------------------------------------------------------------------------------------------------------"<<endl;
    cin.ignore();
    cin.get();
    return ;
}

void Student::single_report_card()
{
    cout<<"\n\t\t ABCD INTERNATIONAL  SCHOOL";
    cout<<"\n\t\t Session : 20XX-XX";
    cout<<"\n-------------------------------------------------------------------------------";
    cout<<"\n\n Roll Number :"<<rollno;
    cout<<"\n\n Name  :"<<name<<"\t\t Standard :"<<std;
    cout<<"\n\n-------------------------------------------------------------------------------";
    cout<<"\n Subject\tMarks Obtained\tMaximum Marks";
    cout<<"\n--------------------------------------------------------------------------------"<<endl;
    cout<<left<<setw(30)<<"Physics"<<phy<<setw(30)<<" /100"<<endl;
    cout<<left<<setw(30)<<"Chemistry"<<chem<<setw(30)<<" /100"<<endl;
    cout<<left<<setw(30)<<"Maths"<<math<<setw(30)<<" /100"<<endl;
    cout<<left<<setw(30)<<"English"<<eng<<setw(30)<<" /100"<<endl;
    cout<<left<<setw(30)<<"Computer Science"<<cs<<setw(30)<<" /100"<<endl;
    cout<<"\n-------------------------------------------------------------------------------";
    cout<<"\n Total Marks Obtained : "<<tot<<"\tPercentage : "<<per<<"\tGrade :"<<grade;
    cout<<"\n---------------------------------------------------------------------------------";
    return ;
}

void Student::display_single()
{
    int roll,flag =0;
    ifstream infile;
    infile.open("student.dat",ios::binary|ios::in);
    cout<<"\n Enter Roll No : ";
    cin>>roll;
    while(infile.read((char*)(&s),sizeof(Student))  && flag==0)
    {
        if(roll==rollno)
        {
            single_report_card();
            flag=1;
        }
        else
            flag=0;
    }
    infile.close();
    if(flag==0)
    cout<<"\n\t RECORD DOESN'T EXIST!!!";
    cin.ignore();
    cin.get();
    return ;
}

void Student::display_all_record()
{
    ifstream infile;
    infile.open("student.dat",ios::binary|ios::in);
    cout<<"\nRECORDS OF ALL STUDENT";
    while(infile.read((char*)(&s),sizeof(Student)))
    {
        s.display();
        cout<<"\n--------------------------------------------------------------------------------------------------------------------------\n";
    }
    infile.close();
    cin.ignore();
    cin.get();
}



void Student::search_record()
{
    ifstream infile;
    infile.open("student.dat",ios::binary|ios::in);
    int roll,flag=0;
    cout<<"\nEnter the Roll Number of Student to be searched :";
    cin>>roll;
    while(infile.read((char*)(&s),sizeof(Student)))
    {
        if(roll==rollno)
        {
            cout<<"\nSTUDENT RECORD"<<endl;
            cout<<"---------------------------------------------------"<<endl;
            s.display();
            flag=1;
        }
    }
    infile.close();
    if(flag==0)
        cout<<"\n\tRECORD DOESN'T EXIST";
    cin.ignore();
    cin.get();
}


void Student::result_menu()
{
    int ch;
    do
    {
        cout<<"\n\t\t--------RESULT   MENU--------\n\n";
        cout<<"\n1. To View Result of any Student"<<endl;
        cout<<"\n2. To View Result of any Class"<<endl;
        cout<<"\n3. To Go back to Main Menu"<<endl;
        cout<<"\nEnter your Choice : ";cin>>ch;
        switch(ch)
        {
            case 1:
                s.display_single();
                break;
            case 2:
                s.display_class();
                break;
            case 3:
                s.main_menu();
                break;
            default:
                cout<<"\n\tEnter Correct Choice!!!";
        }
    } while (ch!=3);
}

void Student::entry_edit_menu()
{
    int ch;
    do
    {
        cout<<"\n\t\t------ENTRY  /  EDIT   MENU------\n\n";
        cout<<"\n1. To Add New Student"<<endl;
        cout<<"\n2. To Display All Students Record"<<endl;
        cout<<"\n3. To Search Record of any Student"<<endl;
        cout<<"\n4. To Modify Student Record"<<endl;
        cout<<"\n5. To Delete Student Record"<<endl;
        cout<<"\n6. To Go back to Main Menu"<<endl;
        cout<<"\nEnter your Choice :";cin>>ch;
        switch(ch)
        {
            case 1:
                    s.add_student();
                    break;
            case 2:
                    s.display_all_record();
                    break;
            case 3:
                    s.search_record();
                    break;
            case 4:
                    s.modify_record();
                    break;
            case 5:
                    s.delete_record();
                    break;
            case 6:
                    s.main_menu();
                    break;
            default: cout<<"\n\tEnter Correct Choice"<<endl;
        }
    } while (ch!=6);
    return ;
}

void Student::main_menu()
{
    int ch;
    do
    {
        cout<<"\n\t\t--------------------WELCOME  TO  STUDENT  REPORT  CARD  HANDLING  SYSTEM--------------------------\n\n";
        cout<<"\n\t1. To Display Result"<<endl;
        cout<<"\n\t2. To Enter/Edit Student Details"<<endl;
        cout<<"\n\t3. To Exit"<<endl;
        cout<<"\n\tEnter your Choice : ";cin>>ch;
        switch(ch)
        {
            case 1:
                result_menu();
                break;
            case 2:
                entry_edit_menu();
                break;
            case 3:
                exit(0);
            default:
                cout<<"\n\tEnter Correct Choice";
        }
    }while(ch!=3);
    return ;
}
int main()
{
    s.main_menu();
    return 0;
}