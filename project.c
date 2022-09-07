//username:Admin
//pw: admin
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <conio.h>

int i,j,main_exit;
void menu();
void new_entry();
void edit();
void view_list();
void erase();
void see();
void closer();

struct date{
 int month,day,year;
};

struct details{
    char name[60];
    int age;
    char city[60];
    char mail_id[30];
    char room_no[8];
    char father_name[60];
    char hostel_name[6];
    int roll_no;
    struct date dob;
}add,upd,rem,sort,temp;

int check;    
int main(){
	pass();
	menu();
	return 0;
}

int pass(void){
    int a=0, i=0;
	char username[20], c=' ';
	char password[10];
	char uname[20] ="Admin";
	char pw[10]= "admin";
	
	do{
	system("cls");
	printf("\n *****************************************************************  ");
    printf("\n            	Please! You have to login for access                \n");
    printf("\n **************************  LOGIN PAGE  *************************\n");
    
    printf("\n                    You have %d attempts left.     \n",5-a);
    printf(" \n                         ENTER USERNAME: ");
	gets(username);
	printf(" \n                         ENTER PASSWORD: ");
	while(i<10){
	    password[i]=getch();  //takes the characters entered through getch() function
	    c=password[i];		  
	    if(c=='\r') break;
	    else
		printf("*");		 //prints *  for every character typed
	    i++;
	}
	password[i]='\0';
	i=0; 
	//comparing the string
	if(strcmp(username,uname)==0 && strcmp(password,pw)==0){
	printf("  \n\n\n                      WELCOME !!!! LOGIN IS SUCCESSFUL\n");
	printf("  \n                               ACCESS GRANTED         \n");
	system("PAUSE");
	break;
	}
	else
	{
		printf("\n\n                  SORRY !!!!  ACCESS DENIED     \n");
		printf("\n           Please re-enter your username and password.\n\n");
		 
		system("PAUSE");
		a++;
		
	}
} while(a<5);	
}

void menu()
{  
system("CLS");
    int choice;
    printf("\n\n\t\t\tHOSTEL ADMINISTRATION SYSTEM");
    printf("\n\n\n\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 WELCOME TO THE MAIN MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    printf("\n\n\t\t1>> Enter new Student's data\n\t\t2>> View all student details\n\t\t3>> Check the details of existing account\n\t\t4>> Removing existing account\n\t\t5>> Update student info\n\t\t6>> Exit\n\n\n\n\n\t\t Enter your choice:");
    scanf("%d",&choice);

    switch(choice){
	case 1:new_entry();
            break;
	case 2:view_list();
           break;
    case 3:see();
           break;
    case 4:erase();
           break;
    case 5:edit();
           break;
	case 6:closer();
          break;
    default:menu();
    }
}

//enter new students detail
void new_entry(){
	system("CLS");
    int choice;
    FILE *ptr;
    ptr=fopen("record.dat","a+");
    roll_no:
    printf("\t\t\t\xB2\xB2\xB2 ADD STUDENTS DATA  \xB2\xB2\xB2\xB2");
    printf("\nEnter your roll number:");
    scanf("%d",&check);
    while(fscanf(ptr,"%d %s %d/%d/%d %d %s %s %s %s %s\n",&add.roll_no, &add.name, &add.dob.month, &add.dob.day, &add.dob.year, &add.age, add.city, &add.mail_id, &add.father_name, &add.room_no, &add.hostel_name)!=EOF)
    {
        if (check==add.roll_no){
			printf("Students roll no. already in use!\n\n");
            goto roll_no;
        }
    }
    add.roll_no=check;
    printf("\nEnter the name:");
    scanf("%s",&add.name);
	int z=1;
	while(z!=0){
	int mm,dd,y;  
	printf("\nEnter the date of birth(mm/dd/yyyy):");
	scanf("%d/%d/%d",&mm,&dd,&y);
    if(y>=1900 && y<=9999)
	{
		if(mm>=1 && mm<=12)
		{
  			if(((dd>=1 && dd<=31) && (mm==1 || mm==3 || mm==5 || mm==7 || mm==8 || mm==10 || mm==12)) || ((dd>=1 && dd<=30)&&(mm==4 || mm==6 || mm==9 || mm==11)) || ((dd>=1 && dd<=28) && (mm==2)) || (dd==29 && mm==2 && (y%400==0 || (y%4==0 && y%100!=0))))
  			{
			add.dob.month=mm;
			add.dob.year=y;
			add.dob.day=dd;
   			}else{
			printf("Day is invalid.\n");
			continue;
			}
  		}else{
		printf("Month is not valid.\n");
		continue;
		}
	}else{
    printf("Year is not valid.\n");
	continue;
    }        
	z=0;
	}
    printf("\nEnter the age:");
    scanf("%d",&add.age);
    printf("\nEnter the city:");
    scanf("%s",&add.city);
    printf("\n Enter your email id :");
    scanf("%s",&add.mail_id);
    printf("\n Enter your parent's name:");
    scanf("%s",&add.father_name);
    printf("\n Enter your room no.:");
    scanf("%s",&add.room_no);
    printf("\n Enter your hostel name from ASA, ABA, CDC, DRA :");
    scanf("%s",&add.hostel_name);
    fprintf(ptr,"%d %s %d/%d/%d %d %s %s %s %s %s\n",add.roll_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.city, add.mail_id, add.father_name, add.room_no, add.hostel_name);
    fclose(ptr);
    printf("\nStudent added successfully!");
    add_invalid:
    printf("\n\n\n\t\tEnter 1 to go to the main menu and 0 to exit:");
    scanf("%d",&main_exit);
    if (main_exit==1)
        menu();
    else if(main_exit==0)
            closer();
    else
    {
        printf("\nInvalid!\a");
        goto add_invalid;
    }
}

//update student's data
 void edit(){
 	system("CLS");
     int choice,test=0;
     FILE *old,*newrec;
     old=fopen("record.dat","r");
     newrec=fopen("new.dat","w");

     printf("\nEnter the roll no. of the student whose info you want to change:");
     scanf("%d",&upd.roll_no);
     while(fscanf(old,"%d %s %d/%d/%d %d %s %s %s %s %s\n",&add.roll_no, add.name, &add.dob.month, &add.dob.day, &add.dob.year, &add.age, add.city, add.mail_id, add.father_name, &add.room_no, add.hostel_name)!=EOF)
     {
         if (add.roll_no==upd.roll_no){
		    test=1;
             printf("\nWhich information do you want to change?\n1.Room no.\n2.Hostel\n\nEnter your choice(1 for room no. and 2 for hostel ):");
             scanf("%d",&choice);
            
             if(choice==1)
                 {
 				printf("Enter the new room no.:");
                 scanf("%s",&upd.room_no);
                 fprintf(newrec,"%d %s %d/%d/%d %d %s %s %s %s %s\n",add.roll_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.city, add.mail_id, add.father_name, upd.room_no, add.hostel_name);
                 printf("Changes saved!");
                 }
             else if(choice==2)
                 {
                 printf("Enter the new hostel name from ASA, ABA, CDC, DRA :");
                 scanf("%s",&upd.hostel_name);
                 fprintf(newrec,"%d %s %d/%d/%d %d %s  %s %s %s %s\n",add.roll_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.city, add.mail_id, add.father_name, add.room_no, upd.hostel_name);
                 printf("Changes saved!");
                 }

         }
         else
             fprintf(newrec,"%d %s %d/%d/%d %d %s %s %s %s %s\n",add.roll_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.city, add.mail_id, add.father_name, add.room_no, add.hostel_name);
     }
     fclose(old);
     fclose(newrec);
     remove("record.dat");
     rename("new.dat","record.dat");

 	if(test!=1)
         printf("\nRecord not found!!\a\a\a");
    
     edit_invalid:
 		printf("\nEnter 0 to try again,1 to return to main menu and 2 to exit:");
         scanf("%d",&main_exit);  
         if (main_exit==1)
 			menu();
         else if (main_exit==2)
             closer();
         else if(main_exit==0)
             edit();
         else
         {
         	printf("\nInvalid!\a");
             goto edit_invalid;
         }
 }
 
//to see individual students detail
void see()
 {
 	system("CLS");
     int test=0;
     FILE *old;
     old=fopen("record.dat","r");
     printf("\nEnter the roll no. of the student whose info you want to see:");
     scanf("%d",&sort.roll_no);
     while(fscanf(old,"%d %s %d/%d/%d %d %s %s %s %s %s\n",&add.roll_no, add.name, &add.dob.month, &add.dob.day, &add.dob.year, &add.age, add.city, add.mail_id, add.father_name, &add.room_no, add.hostel_name)!=EOF)
     {
     	//test=1;
         if (add.roll_no==sort.roll_no)
         {  
		 test=1; 
            printf("\nROLL NO.:%d\nName:%s \nDOB:%d/%d/%d \nAge:%d \ncity:%s   \nE-Mail id:%s \nParent's name:%s \nRoom No:%s \nHostel:%s \n",add.roll_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.city, add.mail_id, add.father_name, add.room_no, add.hostel_name);
            
         }        
 }
    fclose(old);
 	if(test==0)
         printf("\nRecord not found!!\a\a\a\n");
     
    
     see_invalid:
 		printf("\nEnter 0 to try again,1 to return to main menu and 2 to exit:");
         scanf("%d",&main_exit);  
         if (main_exit==1)
 			menu();
         else if (main_exit==2)
             closer();
         else if(main_exit==0)
             see();
         else
         {
         	printf("\nInvalid!\a");
             goto see_invalid;
         }
 
}

//delete record of specific student
 void erase(){
 	system("CLS");
     FILE *old,*newrec;
     int test=0;
     old=fopen("record.dat","r");
     newrec=fopen("new.dat","w");
     printf("Enter the roll no. of student whose data you want to delete:");
     scanf("%d",&rem.roll_no);
     while (fscanf(old,"%d %s %d/%d/%d %d %s %s   %s %s %s\n",&add.roll_no, &add.name, &add.dob.month, &add.dob.day, &add.dob.year, &add.age, &add.city, &add.mail_id, &add.father_name, &add.room_no, &add.hostel_name)!=EOF)
    {
         if(add.roll_no!=rem.roll_no)
             fprintf(newrec,"%d %s %d/%d/%d %d %s %s %s %s %s\n",add.roll_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.city, add.mail_id, add.father_name, add.room_no, add.hostel_name);

         else{
		     test++;
             printf("\nRecord deleted successfully!\n");
             }
     }
     fclose(old);
     fclose(newrec);
     remove("record.dat");
     rename("new.dat","record.dat");
     if(test==0)
 	    printf("\nRecord not found!!\a\a\a");
     erase_invalid:
         printf("\nEnter 0 to try again,1 to return to main menu and 2 to exit:");
         scanf("%d",&main_exit);
         if (main_exit==1)
             menu();
         else if (main_exit==2)
             closer();
         else if(main_exit==0)
             erase();
         else
         {	
         	printf("\nInvalid!\a");
             goto erase_invalid;
 		}
 }



//display all details of student
 void view_list()
 {
 	system("CLS");
     FILE *view;
     view=fopen("record.dat","r");
     int test=0;
     while(fscanf(view,"%d %s %d/%d/%d %d %s %s %s  %s %s\n",&add.roll_no, &add.name, &add.dob.month, &add.dob.day, &add.dob.year, &add.age, &add.city, &add.mail_id, &add.father_name, &add.room_no, &add.hostel_name)!=EOF)
        {
        	test=1;
		printf("\nROLL NO.:%d\nName:%s \nDOB:%d/%d/%d \nAge:%d \ncity:%s   \nE-Mail id:%s \nParent's name:%s   \nRoom No:%s \nHostel:%s \n",add.roll_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.city, add.mail_id, add.father_name, add.room_no, add.hostel_name);
        }
     fclose(view);
     if (test==0)
         {   
             printf("\nNO RECORDS!!\n");
 		}
     view_list_invalid:
      printf("\n\nEnter 1 to go to the main menu and 0 to exit:");
         scanf("%d",&main_exit);
        
         if (main_exit==1)
             menu();
         else if(main_exit==0)
             closer();
         else
         {
             printf("\nInvalid!\a");
             goto view_list_invalid;
         }
 }

//exit function
void closer()
{
	system("CLS");
	char exit;
	exit:
	printf("\nDo you want to exit?? (y/n)\n");
	scanf("%s",&exit);
	switch(exit){
		case 'y':
		case 'Y':
			printf("Thank you for coordinating! Have a good time\n");
			break;
		case 'n':
		case 'N':
			menu();
			break;
		default:
			printf("You must choose an option!\n");
			goto exit;		
	}
}
