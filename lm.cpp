#include<iostream>
#include<fstream>
#include<conio.h>
#include<stdio.h>
#include<windows.h>
#include<string>
#include<iomanip>
#include<windows.h>

using namespace std; 

class book
{   public:
	int bno;
	char bname[50];
	char aname[20];
    bool issuestatus;

     book(){
        issuestatus= false;
    }
};
class student
{ public:
    int admno;
    char name[20];
    int bookissued=0;

};
void lmd(){
            system("cls");
    cout<<"**********************************************************************************\n                  LIBRARY MANAGEMENT SYSTEM          by: Vishal Kumar Jha CSE(K)\n**********************************************************************************\n";

}

int main(){
int pass,bid,stid,sid,found,found2,flag;
student st;
book bk;
lmd();
int x;
fstream fp,fp1,fp2;
while(x!=4){ lmd();
    cout<<"1.ISSUE/RETURN BOOK\n2.BOOK/STUDENT QUERY\n3.ADMIN\n4.EXIT\nENTER CHOICE : ";
    cin>>x;

    switch(x){
        case 1:
         while(x!=3){
            lmd();
            cout<<"1.ISSUE BOOK\n2.RETURN BOOK\n0.BACK\nENTER CHOICE : ";
            cin>>x;
            switch(x){
                case 1:
                 lmd();
                 cout<<"ENTER STUDENT ADMISSION NO : ";
                 cin>>stid;
                 found=found2=0;
                 fp.open("student.dat",ios::in|ios::out);
                 while(fp.read((char*)&st,sizeof(st)))
                 {
                  if(st.admno==stid){
                    st.bookissued+=1;
                 int pos=-1*sizeof(st);
                 fp.seekp(pos,ios::cur);
                 fp.write((char*)&st,sizeof(st));
                 found=1;}
                 }
                   if(found==1){
                 cout<<"ENTER BOOK NO : ";
                  cin>>bid;
                 fp1.open("book.dat",ios::in|ios::out);
                 while(fp1.read((char*)&bk,sizeof(bk))){
                    if(bk.bno==bid){
                      if(bk.issuestatus==false){
                        found2=1;
                      bk.issuestatus=true;
                      int pos=-1*sizeof(bk);
                     fp1.seekp(pos,ios::cur);
                     fp1.write((char*)&bk,sizeof(bk));}
                    }
                    
                 }
                 if(found2==0){
                 cout<<"BOOK ALREADY ISSUED\n0.BACK\n ENTER CHOICE :  ";
                 fflush (stdin);
                 cin>>x;
                 break;}
                 }
                 else{
                 cout<<"\n\tSTUDENT NOT FOUND. . . . ";
                 getch();
                 break;}
                 fp.close();
                 fp1.close();
                 cout<<"\n\tBOOK ISSUED SUCCESFULLY . . . .\n";
                 getch();
                 break;
                case 2:
                          lmd();
                 cout<<"ENTER STUDENT ADMISSION NO : ";
                 cin>>stid;
                 found=0;
                 fp.open("student.dat",ios::in|ios::out);
                 while(fp.read((char*)&st,sizeof(st)))
                 {
                  if(st.admno==stid){
                    st.bookissued-=1;
                 int pos=-1*sizeof(st);
                 fp.seekp(pos,ios::cur);
                 fp.write((char*)&st,sizeof(st));
                 found=1;}
                 }
                   if(found==1){
                 cout<<"ENTER BOOK NO : ";
                  cin>>bid;
                 fp1.open("book.dat",ios::in|ios::out);
                 while(fp1.read((char*)&bk,sizeof(bk))){
                    if(bk.bno==bid){
                      bk.issuestatus=false;
                      int pos=-1*sizeof(bk);
                     fp1.seekp(pos,ios::cur);
                     fp1.write((char*)&bk,sizeof(bk));
                    }
                    
                 }
                 }
                 else{
                 cout<<"\n\tSTUDENT NOT FOUND. . . .\n";
                 getch();
                 break;}
                 lmd();
                 cout<<"\n\tBOOK RETURNED . . . .\n";
                 fp.close();
                 fp1.close();
                 getch();
                 break;
                default:
                break;

            }
          break;
        case 2:
         while(x!=0){
           lmd();
           cout<<"1.Student record\n2.Find Book by Author\n0.Back\nENTER CHOICE : ";
           cin>>x;
           switch(x){
             case 1:
               lmd();
               cout<<"Enter Admission no : ";
               cin>>sid;
               fp.open("student.dat",ios::in);
               fp.seekg(0,ios::beg);
               while(fp.read((char*)&st,sizeof(st))){
                if(st.admno==sid){
                 cout<<"================================================================\n";
                 cout<<"\tAdmission No."<<setw(10)<<"Name"<<setw(20)<<"Books Issued\n";
                 cout<<"================================================================\n";
                cout<<"\t"<<st.admno<<setw(20)<<st.name<<setw(10)<<st.bookissued<<endl;
                }
               }
               getch();
              case 2:
               char bn[20];
               lmd();
               cout<<"Enter author : ";
               fflush (stdin);
                cin.getline(bn,sizeof(bn));
               fp.open("book.dat",ios::in);
               fp.seekg(0,ios::beg);
               found=0;
                cout<<"======================================================================================\n";
                 cout<<"Book Number"<<setw(20)<<"Book Name"<<setw(20)<<"Author"<<setw(30)<<"Issue Status\n";
                 cout<<"=====================================================================================\n";

               while(fp.read((char*)&bk,sizeof(bk))){
                if(strcmpi(bk.aname,bn)==0){
               
               cout<<bk.bno<<setw(30)<<bk.bname<<setw(20)<<bk.aname;
               if(bk.issuestatus==0)
                    cout<<setw(30)<<"AVAILABLE\n";
                    else
                    cout<<setw(30)<<"NOT AVAILABLE\n";
                    found=1;
                }
               }
               if(found==0){
                 cout<<"\n\tBOOK NOT FOUND. . . .";
                 getch();
                 break;
               }
               getch();
              break;
              default:
              break;
           }

         }
        
        break;
        case 3: lmd();
         cout<<"ENTER PASSWORD : ";
         cin>>pass;
         if(pass==1710){
         while(x!=0){
        lmd();
         cout<<"1.ADD STUDENT\n2.SHOW ALL STUDENT\n3.ADD BOOK\n4.SHOW ALL BOOKS\n5.DELETE STUDENT RECORD\n6.REMOVE BOOK\n0.BACK\nENTER CHOICE : ";
         cin>>x;
         switch(x){
            case 1:
            lmd();
              cout<<"ENTER STUDENT ADMISSION NO : ";
              cin>>st.admno;
             cout<<"\nEnter The Name of The Student ";
             fflush (stdin);
             gets(st.name);
             fp.open("student.dat",ios::app);
             fp.write((char*)&st,sizeof(st));
             fp.close();
             cout<<"\n\tStudent Added.....";
             getch();
             break;
            case 2:
                fp.open("student.dat",ios::in);
               lmd();
                  cout<<"\n\n\t\tSTUDENT LIST\n\n";
             cout<<"================================================================\n";
             cout<<"\tAdmission No."<<setw(10)<<"Name"<<setw(20)<<"Books Issued\n";
              cout<<"================================================================\n";

               while(fp.read((char*)&st,sizeof(student)))
             {
               cout<<"\t"<<st.admno<<setw(20)<<st.name<<setw(10)<<st.bookissued<<endl;
                
             }
         
             fp.close();
               getch();
               break;
            case 3:
            lmd();
             fp.open("book.dat",ios::out|ios::app);
              cout<<"\nEnter The book no.";
                cin>>bk.bno;
             cout<<"\n\nEnter The Name of The Book ";
              cin.ignore();
             cin.getline(bk.bname,sizeof(bk.bname));
              cout<<"\nEnter The Author's Name ";
             cin.getline(bk.aname ,sizeof(bk.aname));
             fp.write((char*)&bk,sizeof(bk));
             fp.close();
             cout<<"\n\tBook Added . . . .";
             getch();
            break;
            case 4:
              fp.open("book.dat",ios::in);
              lmd();
              cout<<"\n\n\t\tBook LIST\n\n";
                cout<<"======================================================================================\n";
                 cout<<"Book Number"<<setw(20)<<"Book Name"<<setw(20)<<"Author"<<setw(30)<<"Issue Status\n";
                 cout<<"=====================================================================================\n";
                 int nl;
                  while(fp.read((char*)&bk,sizeof(bk))){
                      nl=strlen(bk.bname);
                    cout<<bk.bno<<setw(30)<<bk.bname<<setw(20)<<bk.aname;
                    if(bk.issuestatus==0)
                    cout<<setw(30)<<"AVAILABLE\n";
                    else
                    cout<<setw(30)<<"NOT AVAILABLE\n";
                  }
                   fp.close();
                   getch();
            break;
            case 5:   
             lmd();
             cout<<"\n\nEnter The admission no. of the Student You Want To Delete : ";
              cin>>sid;
              fp.open("student.dat",ios::in);
              fp2.open("Temp.dat",ios::out);
              fp.seekg(0,ios::beg);
              while(fp.read((char*)&st,sizeof(student)))
             {
             if(st.admno!=sid)
               fp2.write((char*)&st,sizeof(student));
                 else
               flag=1;
                }
        
               fp2.close();
                    fp.close();
                 remove("student.dat");
                rename("Temp.dat","student.dat");
                  if(flag==1)
                cout<<"\n\tRecord Deleted ..";
                 else
              cout<<"\n\tRecord not found";
              getch();
            break;
            case 6:
             lmd();
             cout<<"\nEnter The Book no. of the Book You Want To Delete : ";
               cin>>bid;
               fp.open("book.dat",ios::in);
               fp2.open("Temp.dat",ios::out);
              fp.seekg(0,ios::beg);
             while(fp.read((char*)&bk,sizeof(book)))
             {
             if(bk.bno!=bid)  
                {
               fp2.write((char*)&bk,sizeof(book));
                }
                }
        
               fp2.close();
                 fp.close();
                 remove("book.dat");
                 rename("Temp.dat","book.dat");
                   cout<<"\tBook Removed....";
                  getch();
            break;
            default:
            break;
                
         }
        }}
        else{
          cout<<"\n\tWRONG PASSWORD !";
          getch();
          break;
        }
        break;
        default:
         return 0;
        break;
    }

}
}
}