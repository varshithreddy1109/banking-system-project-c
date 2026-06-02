#include <stdio.h>
#include <stdlib.h>
int pinnchoice=0;
int accountnumberorder=100001;

struct node
{
    int accountnumber; 
    char name[100];
    int dob;
    int pin;
    int balance;
    struct node *next;
};
struct node *temp=NULL;
struct node *hashing[101]={NULL};

void hash(struct node *createnode)
{
       int i=createnode->accountnumber % 101;
       if(hashing[i] == NULL)
       {
          hashing[i]=createnode;
       }    
       else
       {
          struct node *temp;
          temp=hashing[i];
          while(temp->next != NULL)
          {
            temp=temp->next;
          }
          temp->next=createnode;
       }
}

int createpin(struct node *createnode)
{
    int i;
    for(i=1;i<=3;i++)
    {
    int temppin;
    printf("ENTER A NEW 4 DIGIT PIN: ");
    scanf("%d", &temppin);
    if(temppin>=1000 && temppin <=9999)
    {
    createnode->pin=temppin;
    return 10;
    }
    else
    {
        printf("INVALID PIN. THE PIN SHOULD BE ONLY HAVING 4 DIGITS PLEASE ENTER AGAIN");
        printf("You only have %d chances left",i);
    }
   }
 
    printf("ACCOUNT IS NOT CREATED SUCCESSFULLY PLEASE CREATE AGAIN!!!");
    return 22;
   
}

void details(struct node *account)
{
    printf("NAME: %s\nACCOUNT NUMBER: %d\nBALANCE:%d",account->name,account->accountnumber,account->balance);
}
void newaccount()
{
    struct node *createnode;
    createnode=(struct node*)malloc(sizeof(struct node));
    createnode->accountnumber=accountnumberorder;
    accountnumberorder++;
    printf("Enter your name:");
    scanf("%99s", &createnode->name);
    printf("Enter your date of birth in this format if your date of birth is DD-MM-YYYY then enter DDMMYYYY: ");
    scanf("%d", &createnode->dob);
    createnode->balance=0;
    createnode->next=NULL;
    int x=createpin(createnode);
    if(x==10)
    {
    hash(createnode);
    printf("Your Details are:\n");
    details(createnode);
    printf("\nNOW YOU CAN LOGIN SAFELY");
    }
    else{
        free(createnode);
    }
    

}

struct node *findaccount(int acc)
{
      int i= acc % 101;
      struct node *temp;
      temp=hashing[i];
      while(temp != NULL && temp->accountnumber != acc)
      {
        temp=temp->next;
      }
      return temp;
}
void addamount(struct node *account)
{
     printf("Enter the amount to be added in ₹");
     int x;
     scanf("%d", &x);
     account->balance=account->balance + x;
   
}


void withdrawamount(struct node *account)
{
     printf("Enter the amount to be withdrawn in ₹");
     int x;
     scanf("%d", &x);
     if(x <= account->balance)
     {
      account->balance=account->balance - x;
     }
     else
     {
        printf("NOT SUFFiCICENT BALANCE");
     }
     
}


void viewbalance(struct node *account)
{
      printf("YOUR BALANCE IS :₹%d",account->balance);
     
}

void resetpin(struct node *account)
{
    int x;
    printf("Enter YOUR DOB IN THE FORMAT DDMMYYYY");
    scanf("%d", &x);
    if(account->dob == x)
    {
        createpin(account);
    }
    else{
        printf("WRONG DATE OF BIRTH PLEASE TRY AGAIN");
    }
}

void list(struct node *account)
{
    int x=1;
    while(x!=0)
    {
     printf("Enter\n1.Add amount\n2.Withdraw amount\n3.change pin\n4.View balance\n0.Exit");
          scanf("%d", &x);
          switch(x)
           {
              case 1:addamount(account);
                     break;
              case 2:withdrawamount(account);
                     break;
              case 3:resetpin(account);
                     
                     break;
              case 4:viewbalance(account);
                       break;
              case 0:break;
              default:printf("INVALID CHOICE PLEASE TRY AGAIN!!!");
           }
           printf("\n");
        }
           printf("THANK YOU FOR USING OUR BANKING SYSTEM");
}

void login()
{
    int x=1,acc;
    int pinn;
    printf("Enter your account number:");
    scanf("%d", &acc);
    struct node *account;
    account=findaccount(acc);
    if(account != NULL)
    {
      printf("Enter\n1.TO ENTER YOUR PIN\n2.RESET YOUR PIN");
      scanf("%d", &pinnchoice);
      if(pinnchoice==1)
      {
        printf("Enter your 4 digit pin");
        scanf("%d", &pinn);
      if(account->pin==pinn)
      {
          list(account);
      }
      else
      {
        printf("Invalidpin please try again!!!");
        printf("\nTHANK YOU");
      }
    }
    else
    {
        resetpin(account);
        
    }
    }
    else
    {
        printf("ACCOUNT NUMBER IS NOT VALID PLEASE TRY AGAIN");
    }
}


int main()
{
    int x=1;
    while(x !=0)
    {
    printf("Enter\n1.LOGIN\n2.CREATE NEW ACCOUNT\n0.Exit");
    scanf("%d", &x);
    switch(x)
    {
        case 1:login();
               break;
        case 2:newaccount();
               break;
        case 0:break;
        default: printf("INVALID INPUT\nTHANKYOU");
                break;
    }
    printf("\n");
    }
}