#include<iostream>
#include<fstream>
#include<string.h>
 
 using namespace std;

 class Date
 {
private:
    int dd;
    int mm;
    int yy;
    void rectifyDate()
    {
        if(dd >10)
        {
            dd -=30;
            mm++;
        }
        if (mm>12)
        {
            mm -=12;
            yy++;
        }
    }
    public:
        Date()
        {
            dd=1;
            mm=1;
            yy=2018;
        }
        void setDate()
        {
            cout<<"Enter Date: ";
            cin>>dd;
            cout<<"Enter Month: ";
            cin>>mm;
            cout<<"Enter Year: ";
            cin>>yy;
        }
        void setDate(Date temp)
        {
            dd = temp.dd + 15;
            mm = temp.mm;
            yy = temp.yy;
            rectifyDate(); 
        }
        void showDate()
        {
            cout<<dd<<"/"<<mm<<"/"<<yy;
        }
 };
 class Menu
 {
     private:
     public:
        void mainMenu();
        void studentMenu();
        void bookMenu();
        void issueBook();
        void returnBook();
 };
 void Menu :: mainMenu()
 {
     cout<<"*********MAIN MENU********"<<endl<<endl;
     cout<<"1.STUDENT MENU\n2. BOOK MENU\n3. ISSUE BOOK\n4. RETURN BOOK\n";
     cout<<"5. EXIT"<<endl;
 }

 void Menu :: studentMenu()
 {
     cout<<"*******STUDENT MENU*********"<<endl<<endl;
     cout<<"1. NEW ENTRY\n2. MODIFY ENTRY\n3. SEARCH ENTRY\n4.DELETE ENTRY"<<endl;
     cout<<"5. VIEW STUDENT DETAILS\n6.GO BACK TO PREVIOUS MENU"<<endl;
 }
 void Menu ::bookMenu()
 {
     cout<<"*********BOOK MENU*********"<<endl<<endl;
     cout<<"1. NEW ENTRY\n2. MODIFY ENTRY\n3. SEARCH ENTRY\n4.DELETE ENTRY"<<endl;
     cout<<"5. VIEW ALL BOOK DETAILS\n6.GO BACK TO PREVIOUS MENU"<<endl;
 }
 class BookData
 {
     public:
        char title[30];
        char author[30];
        char publisher[30];
        int status;
        float price;
        int issuedRollNo;
        Date issueDate;
        Date returnDate;
        BookData()
        {
            status = 0;
            issuedRollNo = -9999;
        }
 };
 class StudentData
 {
     public:
        int rollNo;
        char name[30];
        char address[50];
        char branch[5];
        int status;
        char bookTitle[30];
        StudentData()
        {
            status = 0;
        }
 };
 class Book
 {
public: 
    void inputDetails();
    void modifyDetails();
    void searchDetails();
    void deleteDetails();
    void viewAllBookDetail();
 };

 void Book :: inputDetails()
 {
    fstream ofp;
    ofp.open("bookDatabase.dat",ios :: out | ios :: binary | ios :: app);

    if(!ofp)
    {
        cerr<<"unable to open file"<<endl;
        return;
    }

    BookData book;
    cout<<"enter book title: ";
    cin>>book.title;
    cout<<"enter author's name : ";
    cin>>book.author;
    cout<<"enter book publisher :";
    cin>>book.publisher;
    cout<<"enter book price: ";
    cin>>book.price;

    ofp.write((char*)&book,sizeof(BookData));
    ofp.close();
 }

 void Book :: modifyDetails()
 {
     fstream file;
     file.open("bookDatabase.dat", ios :: binary | ios:: in | ios::out | ios ::ate);

     if(!file)
     {
        cout<<"unable to open file"<<endl;
        return;
     }
     file.seekg(0,ios :: beg);

     BookData book;
     char title[25];

     cout<<"enter book title of the book you want to modify: ";
     cin>>title;

     while(file.read((char*)&book, sizeof(BookData)))
     {
        if(strcmp(book.title, title) ==0)
        {
            int position =(-1)*sizeof(BookData);
            file.seekp(position, ios :: cur);

            cout<<"enter new book tilte : ";
            cin>>book.title;
            cout<<"enter new author's name : ";
            cin>>book.author;
            cout<<"enter new book publisher: ";
            cin>>book.publisher;
            cout<<"enter new book price: ";
            cin>>book.price;

            cout<<"Record updated";
            cin.get();
            cin.get();
            return;
        }
     }
     cout<<"Book not found!!";
     cin.get();
     cin.get();
     return;
 }
 void Book :: searchDetails()
 {
    fstream file;
    file.open("bookDatabase.dat",ios ::in | ios :: binary);

    if(!file)
    {
        cout<<"unable to open file!"<<endl;
        cin.get();
        cin.get();
        return;
    }

    BookData book;
    char title[30];

    cout<<"enter book title of the book you want to modify: ";
    cin>>title;

    while(file.read((char*)&book,sizeof(BookData)))
    {
        if (strcmp(book.title, title) == 0)
        {
          cout<<"Book title: "<<book.title<<endl;
          cout<<"Book author: "<<book.author<<endl;
          cout<<"Book publisher: "<<book.publisher<<endl;
          cout<<"Book price: "<<book.price<<endl;
          if (book.status == 1)
          {
              cout<<"Issued status: "<<book.issuedRollNo<<endl;
              cout<<"Issued date: ";
              book.issueDate.showDate();
              cout<<endl<<"Return Date: ";
              book.returnDate.showDate();
              cout<<endl;
          }
          else
          {
            cout<<"Isssued status: None"<<endl;
          }
          cin.get();
          cin.get();
          return;
        }
    }
    cout<<"Book not found"<<endl;
    cin.get();
    cin.get();
    return;
 }
 void Book :: deleteDetails()
 {
   fstream file,temp;
   file.open("bookDatabase.dat", ios :: binary | ios :: in);
   temp.open("temp.dat", ios:: binary | ios :: out);

   char title[25];
   BookData book;
   int flag =0;
    
    cout<<"enter book title to remove: ";
    cin>>title;

    while (file.read((char*)&book, sizeof(BookData)))
    {
        if (strcmp(book.title, title) == 0)
        {
            flag++;
            continue;
        }

        temp.write((char*)&book, sizeof(BookData));
    }

    file.close();
    temp.close();
    remove("bookDatabase.dat");
    rename("temp.dat","bookDatabase.dat");

    if (flag == 1)
       cout<<"Record Deleted"<<endl;
    else 
       cout<<"Record not found"<<endl;
    cin.get();
    cin.get();
    return;
 }
 void Book :: viewAllBookDetail()
 {
  fstream file;
  file.open("bookDatabase.dat", ios :: binary | ios :: in);

  BookData book;
  int choice = 1;
 
  while(file.read((char*)&book, sizeof(BookData))&& choice)
  {
    system("cls");
    cout<<"Book tilte: "<<book.title<<endl;
    cout<<"Book author:"<<book.author<<endl;
    cout<<"Book publisher:"<<book.publisher<<endl;
    cout<<"Book price:"<<book.price<<endl;
    if (book.status == 1)
    {
        cout<<"Issued status: "<<book.issuedRollNo<<endl;
        cout<<"Issued date:";
        book.issueDate.showDate();
        cout<<endl<<"Return Date: ";
        book.returnDate.showDate();
    }
    else
    {
        cout<<"issued status: None"<<endl;
    }

    cout<<"Press 1 to view the next book else press 0: ";
    cin>>choice;
  }
  cin.get();
  cin.get();
  return;
 }

 class Student
 {
public:
    void inputDetails();
    void modifyDetails();
    void searchDetails();
    void deleteDetails();
    void viewAllstudentDetail();
 };

 void Student :: inputDetails()
 {
    fstream ofp;
    ofp.open("studentDatabase.dat", ios :: out | ios:: app | ios :: binary);

    if(!ofp)
    {
        cerr<<"Unable to open file"<<endl;
        return;
    }

    StudentData student;
    cout<<"enter student's roll no :";
    cin>>student.rollNo;
    cout<<"enter student's name: ";
    cin>>student.name;
    cout<<"enter student;s address :";
    cin>>student.address;
    cout<<"enter student's branch:";
    cin>>student.branch;

    cout<<"record added to database!";
    
    ofp.write((char*)&student, sizeof(StudentData));
    ofp.close();
 }

 void Student :: modifyDetails()
 {
    fstream fp;
    fp.open("studentDAtabase.dat",ios :: binary | ios::in | ios::out | ios::ate);

    if(!fp)
    {
        cerr<<"unable to open file!"<<endl;
        return;
    }

    fp.seekg(0, ios :: beg);

    int target ;
    cout<<"enter student's roll no. to modify :";
    cin>>target;

    StudentData student;

    while (fp.read((char*)&student, sizeof(student)))
    {
        if (target == student.rollNo)
        {
            int position = (-1)* sizeof(StudentData);
            fp.seekp(position, ios :: cur);

            cout<<"enter student's new roll no. :";
            cin>>student.rollNo;
            cout<<"enter student's new name: ";
            cin>>student.name;
            cout<<"enter student's new address:";
            cin>>student.address;
            cout<<"enter student's new branch :";
            cin>>student.branch;

            fp.write((char*)&student, sizeof(StudentData));
            fp.close();

            cout<<"record updated"<<endl;

            return;
        }
    }
    cout<<"roll no. not found!"<<endl;
    return;
 }

 void Student :: searchDetails()
 {
    fstream ifp;
    ifp.open("studentDatabase.dat", ios :: in | ios :: binary);

    if(!ifp)
    {
        cerr<<"unable to open file!"<<endl;
        return;
    }

    int target;
    cout<<"enter roll no. to search: ";
    cin>>target;

    StudentData student;
    
    while(ifp.read((char*)&student, sizeof(student)))
    {
        if (target == student.rollNo)
        {
            cout<<"record found!"<<endl;
            cout<<"student's name:"<<student.name<<endl;
            cout<<"student's roll no. :"<<student.rollNo<<endl;
            cout<<"student's branch:"<<student.branch<<endl;
            cout<<"student's address:"<<student.address<<endl;

            if(student.status == 1)
            {
                cout<<"Issued book name is :"<<student.bookTitle<<endl;
            }
            else
            {
                cout<<"no book is issued for this roll no."<<endl;
            }

            cin.get();
            cin.get();
            return;
        }
    }
    cout<<"record not found!"<<endl;
    return;
 }
 void Student ::viewAllstudentDetail()
 {
    system("cls");
    fstream ifp;
    ifp.open("studentDatabase.dat", ios :: in | ios :: binary);

    if (!ifp)
    {
        cerr<<"unable to open file!"<<endl;
        return;
    }
    StudentData student;
    int choice = 1;

    while (ifp.read((char*)&student, sizeof(student)) && choice)
    {
        system("cls");
        cout<<"student's name: "<<student.name<<endl;
        cout<<"student's roll no. :"<<student.rollNo<<endl;
        cout<<"student's branch :"<<student.branch<<endl;
        cout<<"student's address :"<<student.address<<endl<<endl;

        if (student.status == 1)
        {
            cout<<"Issued book name is :"<<student.bookTitle<<endl;
        }
        else
        {
            cout<<"no book is issued for this roll no."<<endl;
        }
        cout<<"to view next student press 1 else press 0";
        cin>>choice;
    }
    return;
 }
 void Student :: deleteDetails()
 {
    fstream file;
    file.open("studentDatabase.dat", ios :: in | ios :: binary);
    fstream temp;
    temp.open("temp.dat", ios :: out | ios :: binary);

    StudentData student;
    int target;
    int flag = 0;

    cout<<"enter roll no. to delete data: ";
    cin>>target;

    while(file.read((char*)&student, sizeof(student)))
    {
        if (student.rollNo == target)
        {
            flag++;
            continue;
        }
        temp.write((char*)&student, sizeof(Student));
    }
    file.close();
    temp.close();
    remove("studentDatabase.dat");
    rename("temp.dat","studentDatabase.dat");

    if(flag==1)
        cout<<"record deleted"<<endl;
    else 
        cout<<"roll no. not found"<<endl;

    cin.get();
    cin.get();

    return;
 }

 void Menu :: issueBook()
 {
    fstream sp, bp;
    sp.open("studentDatabase.dat", ios :: in | ios :: out | ios :: ate | ios :: binary);
    bp.open("bookDatabase.dat", ios :: in | ios:: out | ios:: ate | ios :: binary);
    bp.seekg(0, ios :: beg);
    sp.seekg(0, ios :: beg);

    int rollNo, flagS = 0, flagB = 0, position;
    char title[30];
    StudentData student;
    BookData book;

    cout<<"enter student's roll no to issue book:";
    cin>>rollNo;

    while (sp.read((char*)&student, sizeof(StudentData)))
    {
        if(student.rollNo == rollNo)
        {
            position = (-1)*sizeof(StudentData);
            sp.seekp(position, ios :: cur);
            flagS++;
            break;
        }
    }
    if (flagS != 1)
    {
        cout<<"record not found!"<<endl;
        cin.get();
        cin.get();
        sp.close();
        bp.close();
        return;
    }

    cout<<"enter book title you want to issue:";
    cin>>title;

    while (bp.read((char*)&book, sizeof(BookData)))
    {
        if(strcmp(book.title,title)== 0)
        {
            position = (-1)*sizeof(BookData);
            bp.seekp(position, ios :: cur);
            flagB++;
            break;
        }
    }
    if (flagB != 1)
    {
        cout<<"record not found!"<<endl;
        cin.get();
        cin.get();
        sp.close();
        bp.close();
        return;
    }

    if(student.status != 1 && book.status != 1)
    {
        strcpy(student.bookTitle, title);
        student.status = 1;
        book.status = 1;
        book.issuedRollNo = student.rollNo;
        book.issueDate.setDate();
        book.returnDate.setDate(book.issueDate);
        sp.write((char*)&student, sizeof(StudentData));
        sp.write((char*)&book, sizeof(BookData));
        sp.close();
        bp.close();
    }
    else
    {
        if (student.status == 1)
        {
            cout<<"student's account is already full!"<<endl;
            cin.get();
            cin.get();
            sp.close();
            bp.close();
            return;
        }
        else
        {
            cout<<"book is already issued!"<<endl;
            cin.get();
            cin.get();
            sp.close();
            bp.close();
            return;
    
        }
    }
 }
 void Menu :: returnBook()
 {
   

   fstream sp, bp;
   sp.open("studentDatabase.dat", ios :: in | ios :: out | ios :: ate | ios :: binary);
   bp.open("bookDatabase.dat", ios :: in | ios :: out | ios :: ate | ios :: binary);
   bp.seekg(0, ios :: beg);
   sp.seekg(0, ios :: beg);

   int rollNo, flagS = 0, flagB=0, position;
   char title[30];
   StudentData student;
   BookData book;

   cout<<"enter student's roll no to return book: ";
   cin>>rollNo;
   
   while(sp.read((char*)&student, sizeof(StudentData)))
   {
       if(student.rollNo == rollNo)
       {
        position = (-1)*sizeof(StudentData);
        sp.seekp(position, ios :: cur);
        flagS++;
        break;
       }
   }
   if(flagS !=1)
   {
       cout<<"record not found!"<<endl;
       cin.get();
       cin.get();
       sp.close();
       bp.close();
       return ;
   }
   while(bp.read((char*)&book,sizeof(BookData)))
   {
      if(strcmp(book.title, student.bookTitle)==0)
      {
          position = (-1)*sizeof(BookData);
          bp.seekp(position, ios:: cur);
          flagB++;
          break;
      }
   }
   if(student.status==1 && book.status==1)
   {
       cout<<"Record not found !!"<<endl;
       cin.get();
       cin.get();
       sp.close();
       bp.close();
       return ;
   }
   if(student.status==1 && book.status==1)
   {
       student.status=0;
       book.status=0;
       book.issuedRollNo=-9999;
       sp.write((char *)&student, sizeof(StudentData));
       bp.write((char *)&book,sizeof(BookData));
       sp.close();
       bp.close();
   }
   else{
       if(student.status == 0)
       {
           cout<<"Student's account is already full!"<<endl;
           cin.get();
           cin.get();
           sp.close();
           bp.close();
           return ;
       }
       else{
           cout<<"Book is already issued"<<endl;
           cin.get();
           cin.get();
           sp.close();
           bp.close();
           return ;
       }
   }
 }
 int main()
 {
     Menu menu;
     int quit=0;
     char choice[3];
     while(!quit)
     {
        
         menu.mainMenu();
         cout<<"Please enter your choice "<<endl;
         cin>>choice;
         switch(atoi(choice))
         {
             case 1:{
                 system("cls");
                 menu.studentMenu();
                 cout<<"Please Enter your choice  "<<endl;
                 cin>>choice;
                 Student s1;
                 switch(atoi(choice))
                 {
                    case 1:
                      s1.inputDetails();
                      break;
                    case 2:
                      s1.modifyDetails();
                      break;
                    case 3:
                      s1.searchDetails();
                      break;
                    case 4:
                      s1.deleteDetails();
                        break;
                    case 5:
                      s1.viewAllstudentDetail();
                      break;
                    case 6:
                      break;
                    default:
                      cout<<"Wrong Input recieved  "<<endl;
                 }
                 break;
             }
             case 2:
               {
                   system("cls");
                   menu.bookMenu();
                   cout<<"Please Enter your choice "<<endl;
                   cin>>choice;
                   Book b1;
                   switch(atoi(choice))
                   {
                       case 1: b1.inputDetails();
                            break;
                        case 2:
                            b1.modifyDetails();
                      break;
                    case 3:
                      b1.searchDetails();
                      break;
                    case 4:
                      b1.deleteDetails();
                        break;
                    case 5:
                      b1.viewAllBookDetail();
                      break;
                    case 6:
                      break;
                    default:
                      cout<<"Wrong Input recieved  "<<endl;
                 }
                 break;
             }
             case 3: 
               menu.issueBook();
               break;
             case 4:
               menu.returnBook();
                 break;
             case 5:
               quit++;
                 break;
             default:
               cerr<<"Please Enter correct input  "<<endl;
                 cin>>choice;
               }
         }
         return 0;
     }