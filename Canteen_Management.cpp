//**********************************************************************
// HEADER FILE USED
//**********************************************************************
#include<iostream.h>
#include<conio.h>
#include<process.h>
#include<fstream.h>
#include<stdio.h>
//*********************************************************************
// CLASS USED
//**********************************************************************
class product
{
int serial_code;
char name[50];
float cost,qty;
public:
void new_product()
{
cout<<"\n\tPlease Enter The Serial Code Of The Product: ";
cin>>serial_code;
cout<<"\n\tPlease Enter The Name Of The Product: ";
gets(name);
cout<<"\n\tPlease Enter The Cost Of The Product: ";
cin>>cost;
}
void show_product()
{
cout<<"\n\tThe Serial Code Of The Product Is : "<<serial_code;
cout<<"\n\tThe Name Of The Product: ";
puts(name);
cout<<"\n\tThe Price Of The Product Is: ";
cout<<cost;
}
int retserial_code()
{
return serial_code;
}
float retcost()
{
return cost;
}
char*retname()
{
return name;
}
};//END OF CLASS
//**********************************************************************
// GLOBAL DECLARATION FOR STREAM OBJECT
//**********************************************************************
fstream fp;
product pr;
//**********************************************************************
// FUNCTION TO WRITE IN THE FILE
//**********************************************************************
void write_product()
{
fp.open("canteen.dat",ios::app);
pr.new_product();
fp.write((char*)&pr,sizeof(product));
fp.close();
cout<<"\n\tTHE PRODUCT HAS BEEN ADDED";
getch();
}
//**********************************************************************
// FUNCTION TO READ ALL RECORDS FROM FILE
//**********************************************************************
void display_all()
{
clrscr();
cout<<"\n\n\n\t\tDISPLAY ALL RECORD\n\n\n\t\t";
fp.open("canteen.dat",ios::in);
while(fp.read((char*)&pr,sizeof(product)))
{
pr.show_product();
cout<<"\n\n\n===========================================================\n";
getch();
}
fp.close();
getch();
}
//**********************************************************************
// FUNCTION TO READ SPECIFIC RECORD FROM THE FILE
//**********************************************************************
void display_sp(int n)
{
int flag=0;
fp.open("canteen.dat",ios::in);
while(fp.read((char*)&pr,sizeof(product)))
{
if(pr.retserial_code()==n)
{
clrscr();
pr.show_product();
flag=1;
}
}
fp.close();
if(flag==0)
cout<<"\n\n\t\t\tSORRY!!!RECORD NOT EXIST";
getch();
}
//**********************************************************************
// FUNCTION TO MODIFY RECORD OF THE FILE
//**********************************************************************
void modify_product()
{ int no,found=0;
clrscr();
cout<<"\n\n\t\tPlease Enter The Serial Code Of Product";
cin>>no;
fp.open("canteen.dat",ios::in|ios::out);
while(fp.read((char*)&pr,sizeof(product))&&found==0)
{
if(pr.retserial_code()==no)
{
pr.show_product();
cout<<"\n\n\t\tPlease Enter The New Details of Product";
pr.new_product();
int pos=-1*sizeof(pr);
fp.seekp(pos,ios::cur);
fp.write((char*)&pr,sizeof(product));
cout<<"\n\n\n\t\t\t Record Updated Sucessfully";
found=1;
getch();
}
}
fp.close();
if(found==0)
cout<<"\n\n\t\t\t SORRY!!! RECORD NOT FOUND ";
getch();
}
//**********************************************************************
// FUNCTION TO DELETE A PRODUCT
//**********************************************************************
void delete_product()
{
int no;
clrscr();
cout<<"\n\n\n\n\t\tDELETE PRODUCT";
cout<<"\n\nPlease Enter The Product No. Of The Product You Want To Delete ";
cin>>no;
fp.open("canteen.dat",ios::in|ios::app);
fstream fp2;
fp2.open("temp.dat",ios::out);
fp.seekg(0,ios::beg);
while(fp.read((char*)&pr,sizeof(product)))
{
if(pr.retserial_code()!=no)
{
fp2.write((char*)&pr,sizeof(product));
}
}
fp2.close();
fp.close();
remove("canteen.dat");
rename("temp.dat","canteen.dat");
cout<<"\n\n\n\t\tRECORD DELETED SUCCESSFULLY...";
getch();
}
//**********************************************************************
// FUNCTION TO DISPLAY THE PRICE LIST
//**********************************************************************
void menu()
{
clrscr();
fp.open("canteen.dat",ios::in);
if(!fp)
{
cout<<"\n\n\t\tERROR!!!FILE COULD NOT BE OPEN\n\n\n\nFIRST ADD A PRODUCT";
cout<<"\n\n\n\t\tPROGRAM IS CLOSING....";
getch();
exit(0);
}
cout<<"\n\n\t\t\t\tPRODUCT MENU\n\n";
cout<<"\n\t===============================================================\n";
cout<<"\t\tSERIAL CODE\tNAME\t\t\tCost";
cout<<"\n\t===============================================================\n";
while(fp.read((char*)&pr,sizeof(product)))
{cout<<"\t\t\t"<<pr.retserial_code()<<"\t"<<pr.retname()<<"\t\t\t"<<pr.retcost()<<endl;
}
fp.close();
}
//**********************************************************************
// FUNCTION TO PLACE ORDER AND MAKE A BILL
//**********************************************************************
void place_order()
{
int order_arr[50],c=0;
float amt,quan[50],total=0;
char ch='Y';
menu();
cout<<"\n\t==============================================================";
cout<<"\n\n\t\t\t\tPLACE YOUR ORDER";
cout<<"\n\t==============================================================";
do
{
cout<<"\n\n\t\tEnter The Serial Code Of The Product:";
cin>>order_arr[c];
cout<<"\n\t\tEnter the Quantity";
cin>>quan[c];
c++;
cout<<"\n\t\tDo You Want To Order More Products?(y/n):";
cin>>ch;
}
while(ch=='y'||ch=='Y');
cout<<"\n\n\t****************************BILL****************************\n" ;
for(int x=0;x<=c;x++)
{
fp.open("canteen.dat",ios::in);
while(!fp.eof())
{
fp.read((char*)&pr,sizeof(product));
if(pr.retserial_code()==order_arr[x])
{
amt=pr.retcost()*quan[x];
cout<<"\n\tProduct Number:"<<order_arr[x]<<"\n\tProduct name:"<<pr.retname()<<"\n\tQuantity:"<<quan[x]<<"\nCost:"<<pr.retcost();
total=total+amt;
}
}
fp.close();
}
cout<<"\n\n\t\t\t\t\tTOTAL="<<total;
cout<<"\n\n\n\nTHANKYOU FOR PLACING THE ORDER";
getch();
}
//**********************************************************************
// ADMINISTRATION MENU FUNCTION
//***********************************************************************
void admin_menu()
{
clrscr();
int ch2;
cout<<"\n________________________________";
cout<<"\n\n\n\tADMINISTRATOR MENU";
cout<<"\n________________________________";
cout<<"\n\n\t1. ADD PRODUCT ";
cout<<"\n\n\t2. DISPLAY ALL PRODUCt ";
cout<<"\n\n\t3. PRODUCT DETAILS ";
cout<<"\n\n\t4. MODIFY PRODUCT ";
cout<<"\n\n\t5. DELETE PRODUCT ";
cout<<"\n\n\t6. VIEW PRODUCT MENU ";
cout<<"\n\n\t7. BACK TO MAIN MENU ";
cout<<"\n\n\n\t\tPlease enter your choice 1-7";
cin>>ch2;
switch(ch2)
{
case 1:clrscr();
write_product();
break;
case 2:display_all();
break;
case 3:int num;
clrscr();
cout<<"\n\n\t\tEnter The Serial Code";
cin>>num;
display_sp(num);
break;
case 4:modify_product();
break;
case 5:delete_product();
break;
case 6:menu();
getch();
case 7: break;
default: cout<<"\a";
admin_menu();
}
}
//**********************************************************************
// THE MAIN FUNCTION
//**********************************************************************
void main()
{ clrscr();
int no,password=0;
int ch;
do
{
clrscr();
cout<<"\n\n\n*******************************CANTEEN MANAGEMENT*******************************";
cout<<"\n\n\n\t\t\t\t MAIN MENU ";
cout<<"\n\n\t1. CUSTOMER";
cout<<"\n\n\t2. ADMINISTRATOR MENU";
cout<<"\n\n\t3. EXIT";
cout<<"\n\n\t\t\tPlease Select Your Option(1-3)";
cin>>ch;
switch(ch)
{
case 1:clrscr();
place_order();
getch();
break;
case 2:cout<<"\tENTER THE PASSWORD TO USE AS A ADMIN";
cin>>password;
if(password!=9)
cout<<"\n\tPASSWORD INCORRECT\nPLEASE LOGIN AS A COSTUMER";
else
admin_menu();
break;
case 3:cout<<"\n\n\t THANKYOU VISIT AGAIN...";
cout<<"\n\n\t MADE BY: mansi garg";
cout<<"\n\n\t SCHOOL: S.B.V.M";
getch();
exit(0);
default: cout<<"\n WRONG CHOICE ENTER VALID CHOICE";
}
}
while(ch!=4);
getch();
}
//**********************************************************************
// END OF THE PROJECT
//**********************************************************************

