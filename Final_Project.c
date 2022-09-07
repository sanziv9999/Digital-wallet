#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#define ENTER 13
#define TAB 9
#define BCKSPC 8

struct info{
char logid[40];
char logpw[40];
char fname[30];
char lname[30];
};

struct bal{
	float balance;
	float amount;
}tot;
char id[20],pw[20];

int login();
int signup();
int menu();
int topup();
int pay();
int bank();
int bill();
int logout();
int exitmenu();

int main()
{
system("cls");
printf("\n\t\t\tDigital wallet\n");
printf("\n\t\t==========================================\n");
int log;
printf("\t\t1.Login\n\t\t2.Signup\n\t\t3.Exit ");
printf("\n\t\t==========================================\n");
printf("\n\t\tselect your option:");
scanf("%d",&log);
system("cls");
switch(log){
case 1:
login();
break;
case 2:
signup();
case 3:
goto end;
break;
}
end:
return 0;
}

void takepassword(char pwd[50]){
	int i;
	char ch;
	while(1){
		ch = getch();
		if(ch == ENTER || ch == TAB){
			pwd[i] = '\0';
			break;
		}else if(ch == BCKSPC){
			if(i>0){
				i--;
				printf("\b \b");
			}
		}else{
			pwd[i++] = ch;
			printf("* \b");
		}
	}
}
login(){
	FILE *fp;

	struct info user;

	fp=fopen("signup.txt","rb+");
	if(fp==NULL)
    {
        printf("\"File not found\"");
        exit(0);
		}
	printf("\n\t\t==========================================\n");
	printf("\n\t\t\t\tLOGIN\n");
	printf("\n\t\t==========================================\n");
	printf("\n\n");
	printf("\t\tEnter your id:");
	scanf("%s",&id);
	printf("\t\tEnter your password:");
	takepassword(pw);
	while(fread(&user, sizeof(user),1,fp)){
		if(strcmp(id,user.logid)==0 && strcmp(pw,user.logpw)==0){
			printf("\n\n\t\tLogin successful !\n\n"); 
			// balance=0.0;
			printf("\t\tPress any key to continue...");
			getch();
			system("cls");
			menu();
		}
		else{
			printf("\n\n\t\tYour id doesntmatch\n\n");
			printf("\t\tpress any key to continue....");
			getch();
			system("cls");
			login();
		}
		}
	fclose(fp);
}

signup(){
FILE *fp;
struct info user;
fp=fopen("signup.txt","w");
char otp[6];

printf("\n\t\t==========================================\n");
printf("\n\t\t\t\tSIGN-UP\n");
printf("\n\t\t==========================================\n");
printf("\n\n");
printf("\t\tEnter your first name: ");
scanf("%s",user.fname);
printf("\t\tEnter your last name: ");
scanf("%s",user.lname);
//fprintf(fptr,"fname=%s\nlname=%s\n",fname,lname);
// fclose(fptr);
logid:
printf("\t\tEnter your mobile number:");
scanf("%s",user.logid);
if(strcmp(user.logid,id)==0){
printf("\n\t\tSorry the user is already registered\nPlease try with the another number\n");
printf("press any key to continue");
getch();
system("cls");
signup();
}
else{
if(user.logid[10]!='\0'|| user.logid[9]=='\0' ||user.logid[8]=='\0')
{
printf("\n\t\tInvalid mobile number\n");
getch();
system("cls");
goto logid;
}
else{
goto logpw;}
logpw:
printf("\t\tEnter 4 digit pin:");
scanf("%s",&user.logpw);
if(user.logpw[4]!='\0'||user.logpw[3]=='\0' || user.logpw[2]=='\0'){
printf("\n\t\tInvalid password\nPlease press any key to try again...");
getch();
goto logpw;
}
else{
otp:
printf("\n\t\tWe have sent you an otp in your mobile number.\n\t\tPlease enter it for confirmation.\n\n");
printf("\t\totp: ");
scanf("%s",&otp);
if(strcmp(otp,"1234")==0){
fwrite(&user,sizeof(user),1,fp);
fclose(fp);

printf("\t\tPress any key too continue...");
getch();
system("cls");
login();
}
else{
printf("\t\tSorry wrong otp.Please try again\n");
goto otp;
}
} }
return 0;
}

int menu()
{
FILE *fp,*fp1;
struct info user;
fp1=fopen("signup.txt","rb+");
fp=fopen("balance.txt","r");
int option;
fscanf(fp,"%f",&tot.balance);
printf("\n\t\t\t\tDigital wallet\n");
while(fread(&user, sizeof(user),1, fp1)){
	printf("\t\t\t\tWelcome %s",user.fname);}
printf("\n\t\t==========================================\n");
printf("\n\n\t\t\tYour balance is RS.%.1f\n",tot.balance);
printf("\n\t\t==========================================\n");
printf("\t\t1.Load Wallet\n\t\t2.Send Money\n\t\t3.Bank Transfer\n\t\t4.Bill Payment\n\t\t5.Transaction history\n\t\t6.logout");
printf("\n\t\t==========================================\n");
printf("\t\tPlease select your option:");
scanf("%d",&option);
printf("\t\tPress any key to continue...");
getch();
system("cls");
switch(option){
case 1:
topup();
break;
case 2:
pay();
break;
case 3:
bank();
break;
case 4:
bill();
break;
case 5:
history();
break;
case 6:
logout();
break;
}
fclose(fp);
fclose(fp1);
return 0;
}

int topup(){

FILE *fp1,*fp2;
fp1=fopen("history.txt","a+");
fp2=fopen("balance.txt","w");
char destid[30];
struct info user;
	printf("\n\t\t==========================================\n");
	printf("\n\t\t\t\tLOAD WALLET\n");
	printf("\n\t\t==========================================\n");
	printf("\n\n");
printf("\n\t\tNote: Please make sure that to use this \n\t\tfeature your bank account and the wallet id\n\t\tshould be connected using the same mobile number\n\n");
destid:
printf("\n\n\t\tEnter the bank acount number : ");
scanf("%s",&destid);
if(destid[16]!='\0'||destid[15]=='\0'||destid[14]=='\0'){
printf("\t\tInvalid account number.Please enter a valid account\n");
goto destid;
}
else{
printf("\n\t\tEnter the amount:");
scanf("%f",&tot.amount);
printf("\n\n\t\tTo verify the transaction we have sent \n\t\tyou otp on your mobile number\n\t\tPlease enter to verify :\n\n");
int otp;
otp:
printf("\t\totp:");
scanf("%d",&otp);
if(otp==1111){
tot.balance=tot.balance+tot.amount;
fprintf(fp2,"%.f",tot.balance);
system("cls");
printf("\t\tYou have received Rs.%f from account number %s",tot.amount,destid);
fprintf(fp1,"You have received Rs.%f from account number %s\n",tot.amount,destid);
fprintf(fp1,"--------------------------------------------------------------------------\n");
fclose(fp1);
fclose(fp2);
getch();
printf("\t\tPress any key too continue...");
system("cls");
exitmenu();
}
else{
printf("\t\tSorry wrong otp.Please try again\n");
goto otp;
}
}
}

int pay(){
int p;
FILE *fp1,*fp2;
fp1=fopen("history.txt","a+");
fp2=fopen("balance.txt","w");
char destacc[30];
struct info user;
	printf("\n\t\t==========================================\n");
	printf("\n\t\t\t\tSEND MONEY\n");
	printf("\n\t\t==========================================\n");
	printf("\n\n");
destacc:
printf("\t\tEnter wallet id of destination account:");
scanf("%s",&destacc);
if(destacc[10]!='\0'|| destacc[9]=='\0' ||destacc[8]=='\0'){
printf("\n\t\tPlease enter a valid id\n\n");
goto destacc;}
else{
char pin[30];
amount:
printf("\t\tPlease enter the amount you want to transfer:");
scanf("%f",&tot.amount);
if(tot.amount<=tot.balance){
pin:
printf("\t\tPlease enter your pin:");
takepassword(pin);
system("cls");
if(strcmp(pw,pin)==0){
tot.balance=tot.balance-tot.amount;
fprintf(fp2,"%.f",tot.balance);
system("cls");
printf("\t\tYou have sent Rs.%f to %s\n\n",tot.amount,destacc);
fprintf(fp1,"You have sent Rs.%f to %s\n",tot.amount,destacc);
fprintf(fp1,"--------------------------------------------------------------------------\n");
fclose(fp1);
fclose(fp2);
getch();
system("cls");
exitmenu();
}
else{
printf("\t\tPlease enter the correct pin\n");
goto pin;
}
}
else{
printf("\t\tSorry you dont have sufficent balance.\n");
printf("\t\tWhat do you want to do ?\n\t\t1.Top-up\n\t\t2.Re-enter amount \n");
printf("\t\tYour choice: ");
scanf("%d",&p);
	switch(p){
	case 1:
	system("cls");
	topup();
	break;
	case 2:	
	goto amount;
	break;}
}

}
}

int bank(){
struct info user;
FILE *fp1,*fp2;
fp1=fopen("history.txt","a+");
fp2=fopen("balance.txt","w");
char destid[30];
int p;
	printf("\n\t\t==========================================\n");
	printf("\n\t\t\t\tBANK DEPOSIT\n");
	printf("\n\t\t==========================================\n");
	printf("\n\n");
destid:
printf("\n\n\t\tEnter bank account number :");
scanf("%s",destid);
if(destid[16]!='\0'|| destid[15]=='\0' ||
destid[14]=='\0'){
printf("\n\t\tPlease enter a valid account number\n\n");
goto destid;}
else{
char pin[30];
amount:
printf("\n\t\tPlease enter the amount you want to transfer:");
scanf("%f",&tot.amount);
if(tot.amount<=tot.balance){
pin:
printf("\n\t\tPlease enter your pin:");
takepassword(pin);
if(strcmp(pw,pin)==0){
tot.balance=tot.balance-tot.amount;
fprintf(fp2,"%.f",tot.balance);
system("cls");
printf("\t\tYou have deposited Rs.%f to bank account %s\n",tot.amount,destid);
fprintf(fp1,"You have deposited Rs.%f to bank account %s\n",tot.amount,destid);
fprintf(fp1,"--------------------------------------------------------------------------\n");
fclose(fp1);
fclose(fp2);
getch();
exitmenu();
}
else{
printf("\n\t\tPlease enter the correct pin\n");
goto pin;
}
}
else{
printf("\t\tSorry you dont have sufficent balance.\n");
printf("\t\tRe-enter amount \n");
goto amount;
}
}
}


int logout(){
int logout;
	printf("\n\t\t==========================================\n");
	printf("\n\t\t\t\tLOGOUT\n");
	printf("\n\t\t==========================================\n");
	printf("\n\n");
logout:
printf("\t\tDo you want to logout?\n\n\t\t1.Yes\t\t2.No\n");
scanf("%d",&logout);
system("cls");
switch(logout){
case 1:
main();
break;
case 2:
menu();
break;
default:
printf("\n\t\tSorry wrong input.");
logout;
}
}

int bill(){
FILE *fp1,*fp2;
fp1=fopen("history.txt","a+");
fp2=fopen("balance.txt","w");
int bill,uid,p;
char btype[30],pin[30];

	printf("\n\t\t==========================================\n");
	printf("\n\t\t\t\tBILL PAYMENT\n");
	printf("\n\t\t==========================================\n");
	printf("\n\n");
bill:
printf("\n\t\tWhich bill you want to pay?\n\n\t\t1.Water bill\n\t\t2.Electricity bill\n\t\t3.Internet bill\n");

printf("\t\tPlease enter your choice:");
scanf("%d",&bill);
system("cls");
switch(bill){
case 1:
strcpy(btype,"Water");
goto pay;
break;
case 2:
strcpy(btype,"Electricity");
goto pay;
break;
case 3:
strcpy(btype,"Internet");
goto pay;
break;
default:
printf("\n\t\tWrong input.\n Pleae try again");
goto bill;
}
pay:
printf("\n\t\tEnter your user id:");
scanf("%d",&uid);
amount:
printf("\n\t\tEnter amount:");
scanf("%f",&tot.amount);
if(tot.amount<=tot.balance){
pin:
printf("\n\t\tPlease enter your pin:");
takepassword(pin);
if(strcmp(pw,pin)==0){
tot.balance=tot.balance-tot.amount;
fprintf(fp2,"%.f",tot.balance);
system("cls");
printf("\n\n\t\t%s bill of Rs.%f has been paid.",btype,tot.amount);
fprintf(fp1,"%s bill of Rs.%f has been paid.\n",btype,tot.amount);
fprintf(fp1,"--------------------------------------------------------------------------\n");
fclose(fp1);
fclose(fp2);
getch();
exitmenu();
}
else{
printf("\n\n\t\tPlease enter the correct pin\n");
goto pin;
}
}
else{
printf("\t\tSorry you dont have sufficent balance.\n");
printf("\t\tWhat do you want to do ?\n\t\t1.Top-up\n\t\t2.Re-enter amount \n");
printf("\t\tYour choice: ");
scanf("%d",&p);
	switch(p){
	case 1:
	system("cls");
	topup();
	break;
	case 2:	
	goto amount;
	break;}
}
}
history(){
	FILE *fp;
	fp=fopen("history.txt","r");
		printf("\n\t\t==========================================\n");
	printf("\n\t\t\t    TRANSACTION HISTORY\n");
	printf("\n\t\t==========================================\n");
	printf("\n\n");
	char a[200];
	while(!feof(fp)){
		fgets(a,150,fp);
		puts(a);
		
	}
	
	exitmenu();
	fclose(fp);
}

int exitmenu(){
int exit;
exitmenu:
printf("\n\n\t\t1.Home\n\t\t2.Exit\n");
scanf("\t\t%d",&exit);
system("cls");
switch(exit){
case 1:
menu();
break;
case 2:
goto end;
break;
}
end:
	printf("\t\t\t\t\t\t\tThank you \1 ");
	getch();
	
return 0;
}

