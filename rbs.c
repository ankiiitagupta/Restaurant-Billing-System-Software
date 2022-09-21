#include<stdio.h>
#include<string.h>
#include<stdlib.h>


struct items{
       char item[20];
       float price;
       int qty;
};

struct orders{
       char customer[50];
       char date[50];
       int numOfItems;
       struct items itm[50]; 
       
};

//functions to generate bills
void generatebillheader(char name[30], char date[30])
{   printf("\n\n");
       printf("\t\tABC Restaurant");
       printf("\n\t -------------------------");
       printf("\nDate:%s",date);
       printf("\nInvoice To: %s",name);
       printf("\n--------------------------------------------\n");
       printf("Items\t\t");
       printf("Qty\t\t");
       printf("Total\t\t");
       printf("\n--------------------------------------------\n\n");
}

void generatebillbody(char item[30], int qty, float price)
{   printf("%s\t\t",item);
       printf("%d\t\t",qty);
       printf("%.2f\t\t",qty* price);
       printf("\n");     
}



void generatebillfooter(float total)
{  printf("\n");
   float dis = 0.1* total;  //0.1 is 10% discount on total
   float nettotal = total - dis;
   float cgst = 0.09 * nettotal,sgst= 0.02* nettotal, grandtotal =nettotal + cgst + sgst;
   printf("--------------------------------------------------\n");
   printf("Sub Total\t\t\t%.2f",total);
   printf("\nDiscount @10%s\t\t\t%.2f","%",dis);
   printf("\n\t\t\t\t----------");
   printf("\nNet Total\t\t\t%.2f",nettotal);
   printf("\nCGST @9%s\t\t\t%.2f","%",cgst);
   printf("\nSGST @2%s\t\t\t%.2f","%",sgst);
   printf("\n---------------------------------------------");
   printf("\nGrand Total\t\t\t%.2f",grandtotal);
   printf("\n---------------------------------------------\n");
}


int every()
{   int opt, n;
    float total;
    struct orders ord;
    struct orders order;
    char saveBill = 'y', contflag='y';
    char name[50];
	    FILE *fp;
       
       //dashboard
     while(contflag =='y'){
       float total =0;
       int invoicefound=0;
    printf("\n\n\t================  SUNSHINE  DINER  ==================");
    printf("\nPlease select your preferred operation.");
    printf("\n\n1.Generate Invoice");
    printf("\n2.Show all Invoices");
    printf("\n3.Search Invoices");
    printf("\n4.Exit");
   
    printf("\n\nYour choice:\t");
    scanf("%d",&opt);
    printf("\nYou have chosen %d",opt);
    fgetc(stdin);
    switch(opt){
       case 1: 
              system("cls");
               printf("\nPlease enter the name of the customer:\t");
               fgets(ord.customer,50,stdin);
               ord.customer[strlen(ord.customer)-1]=0;
              // strcpy(ord.date,_DATE_);
               printf("\nPlease enter the number of items:\t");
               scanf("%d",&n);
               ord.numOfItems= n;
               int i;
               for( i=0;i<n;i++){
                     fgetc(stdin);
                     printf("\n\n");
                     printf("Please enter the item %d:\t",i+1);
                     fgets(ord.itm[i].item,20,stdin);
                     ord.itm[i].item[strlen(ord.itm[i].item)-1]= 0;
                     printf("Please enter the quantity:\t");
                     scanf("%d",&ord.itm[i].qty);
                     printf("Please enter the unit price:\t");
                     scanf("%f",&ord.itm[i].price);
                     total += ord.itm[i].qty * ord.itm[i].price;
                      }


               generatebillheader(ord.customer,ord.date);
               for(i=0;i<ord.numOfItems;i++){
                     generatebillbody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
               }

               generatebillfooter(total);
               
	        printf("\nDo you want to save the invoice[y/n]:\t");
		 scanf("%s",&saveBill);
			             
		if(saveBill == 'y'){
			fp = fopen("RestaurantBill.dat","a+");
			fwrite(&ord,sizeof(struct orders ),1,fp);
			if(fwrite != 0)
			 printf("\nSuccessfully saved");
		       else
		        printf("\nError saving");
			 fclose(fp);			         
               }
               break;


              case 2:
              system("\ncls");
              fp = fopen("RestaurantBill.dat","r");
              printf("\n   ****Your Previous Invoices****\n");
              while(fread(&order,sizeof(struct orders),1,fp)){
                     float tot= 0;
                  generatebillheader(order.customer, order.date);
                  int i;
                  for( i=0;i<order.numOfItems;i++){
                     generatebillbody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                     total += order.itm[i].qty* order.itm[i].price;
                 }
                  generatebillfooter(total);
               }
               fclose(fp);
               break;
       

       case 3:
       printf("\nEnter the name of the customer:\t");
       fgetc(stdin);
       fgets(name,50,stdin);
       name[strlen(name)-1]=0;
       system("\ncls");
               int numOfItems = n ;
              fp = fopen("RestaurantBill.dat","r");
              printf("\n   ****Invoice of %s****\n",name);
              while(fread(&order,sizeof(struct orders),1,fp)){
                     float tot= 0;
                     if(strcmp(order.customer, name)){
                       generatebillheader(order.customer, order.date);
                       int i;
                       for( i=0;i<order.numOfItems;i++){
                         generatebillbody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                         tot+= order.itm[i].qty * order.itm[i].price;
               }
               generatebillfooter(tot);
               invoicefound=1;
              }
                 
        }


        if(!invoicefound){
              printf("Sorry for the Invoice %s doesnot exist",name);
        }
               fclose(fp);
               break;
               
        case 4:
        printf("\n\n\n Bye Bye :) ");
        exit(1);
        break;


       default:
       printf("\nSorry invalid option :/");
       break;         
    }  


    printf("\n Do you want to perform other operation[y/n]:\t");
    scanf("%s",&contflag);
    }
        printf("\n\n");
        

    return 0;

}

int main()
{      int h;
       char *username, *password ;
       printf("\n\n\n\t\t\t\tEnter the Username: ");
       scanf("%s",&username);
       if(strcpy(username,"user")==0){
              printf("\t\t\t\t Enter password:\t");
              scanf("%s",&password);
              if(strcpy(password,"pass")==0)
             { printf("\n\n\t\tLogin Successful!!!");
             system("\ncls");
               every();
             }
              else
              {     printf("\n\n\t\t\tEnter 1 to login again or 0 to exit: ");
                     scanf("%d",&h);
               switch(h)
                     {
                            case 1: main(); break;
                            case 0: exit(1); 
                            default: printf("\n\t\tInvalid Option");break;
                     }
              }
       }
       return 0;
}
