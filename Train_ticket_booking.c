#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

/*********************************************************
                  Global Vaiables 
**********************************************************/
int trains[] = {1001,1002,1003,1004};
int seats[5][51];
double base_price[] = {500,500,500,500,500};
int pass_count[] = {0,0,0,0,0};
double total_price[] = {0,0,0,0,0};

struct node
{
      char name[100];
      int age;
      int train_no;
      int comp_no;
      int seat_no;
      double price;
      struct node *nex;
};

struct table
{
      struct node *p;
}t[5];

/*********************************************************
     function to Return Random Seat within a Range
**********************************************************/
int printRandoms(void) 
{ 
    int i, lower, upper, count; 
    lower = 1; upper = 50; count = 1;

    int num = (rand() % (upper - lower + 1)) + lower; 
        
    return num;
} 
  
/*********************************************************
     function to Return Dynamic Price of a Seat
**********************************************************/
double Dynamic_pricing(int t_no)
{
      if(pass_count[t_no] <= 5)
            return base_price[t_no];
      else if(pass_count[t_no] <= 10)
            return 1.1 * base_price[t_no];
      else if(pass_count[t_no] <= 15)
            return 1.2 * base_price[t_no];
      else if(pass_count[t_no] <= 15)
            return 1.3 * base_price[t_no];
      else if(pass_count[t_no] <= 15)
            return 1.4 * base_price[t_no];
      else
            return 1.5 * base_price[t_no];
      
}

/*********************************************************
     This Function is to List Some Basic Details
     such as Train Number, Number of Seats and price
**********************************************************/
void Show(void)
{
      system("cls");
      
      printf("\n=================================\n");
	printf("  List ofAvailable Trains Details ");
	printf("\n=================================");
      
      printf("\n\nS.No\tTrain.No\tAvailable Seats\t Base Price\n");
      printf("1\t%d\t\t %d\t\t %.2f\n",trains[0],50-pass_count[1],base_price[1]);
      for(int i=1;i<4;i++)
            printf("%d\t%d\t\t %d\t\t %.2f\n",i+1,trains[i],50-pass_count[i+1],base_price[i+1]);

      printf("\n\n\nPress Any Key to Return to Main Menu : ");
      getch();
}

/**********************************************************************
     This function is to show the Ticket after Every Reservation
**********************************************************************/
void display_ticket(int t_no, int num)
{
      struct node *temp = t[t_no].p;
      double price;
      printf("\n------------Your Ticket Details ----------------");
      for(int i=0;i<num;i++)
      {
            printf("\nName : %s  | Age : %d ",temp->name,temp->age);
            printf("\nTrain No : %d  | Comp_No : %d  | Seat_No : %d",temp->train_no,temp->comp_no,temp->seat_no);
            price = price + temp->price;
            temp = temp->nex;
      }
      total_price[t_no] = price;
      printf("\nTotal Amount : %.2f \n",price);
      printf("-------------------------------------------------");
}

/*********************************************************
            Function for Ticket Reservation
**********************************************************/
void Reserve(void)
{
      system("cls");
      printf("\n=================================\n");
	printf("             RESERVATION ");
	printf("\n=================================");

      int Train, flag = 0, Seat_No;
      printf("\nEnter the Train Number (Press '0' In Case you want available Trains List) : ");
      scanf("%d",&Train);
      if(0 == Train)
      {
            Show();
            printf("\nEnter the Train Number : ");
            scanf("%d",&Train);
      }      
      
      struct node *new_node = malloc(sizeof(struct node));
      new_node->nex = NULL;
      char nname[100];
      int age;
      int train_index = Train % 1000;
      int num_tickets;

      printf("---------------------------------------------");
      printf("\n\nEnter Your Name : "); 
      scanf("%s",&nname);
      printf("\nEnter Your Age : "); 
      scanf("%d",&age);
      printf("\nEnter the Number of Tickets : "); 
      scanf("%d",&num_tickets);
      new_node->age = age;
      strcpy(new_node->name, nname);     

      int run = 1;
      while(run)
      {
            Seat_No = printRandoms();
            if(seats[train_index][Seat_No] != 0)
            {
                  for(int j=Seat_No;j<num_tickets;j++)
                  {
                        if(seats[train_index][j] == 0)
                        {
                              flag = 1;
                              break;
                        }
                  }
            } 
            if(flag == 1)
                  continue;
            break;  
      }

      pass_count[train_index]++;
      if(t[train_index].p != NULL)
      {
            new_node->nex = t[train_index].p;
            t[train_index].p = new_node;
      }
      else
            t[train_index].p = new_node;
                  
      t[train_index].p->train_no = train_index + 1000;
      t[train_index].p->seat_no = Seat_No;
      t[train_index].p->comp_no = Seat_No / 10;
      seats[train_index][Seat_No] = 0;
      t[train_index].p->price = Dynamic_pricing(train_index);

      if(num_tickets > 1)
      {
            for(int j=1;j<num_tickets;j++)
            {
                  struct node *new = (struct node *)malloc(sizeof(struct node));
                  new->nex = NULL;
                  printf("\n\nEnter Your Name : ");
                  scanf("%s",&nname);
                  printf("\nEnter Your Age : ");
                  scanf("%d",&age);
                  new->age = age;
                  strcpy(new->name, nname);   
                  new->nex = t[train_index].p;
                  t[train_index].p = new;
                  seats[train_index][Seat_No + j] = 0;
                  t[train_index].p->train_no = train_index + 1000;
                  t[train_index].p->seat_no = Seat_No + j;
                  t[train_index].p->comp_no = (Seat_No + j) / 10;
                  t[train_index].p->price = Dynamic_pricing(train_index);

                  pass_count[train_index]++;
            }
      }
      display_ticket(train_index,num_tickets);

      printf("\n\n\nPress Any Key to Return to Main Menu : ");
      getch();
}

/*********************************************************
            Function for Ticket Cancellation
**********************************************************/
void Cancel(void)
{
      system("cls");
      printf("\n=================================\n");
	printf("            CANCELLATION ");
	printf("\n=================================");

      char nname[100];
      int t_no, s_no;
      printf("\n-------------------------------------------");
      printf("\nTicket Cancellation ");
      printf("\nEnter your Name : ");
      scanf("%s",&nname);
      printf("\nEnter your Train Number : ");
      scanf("%d",&t_no);
      //printf("\nEnter your Seat Number : ");
      //scanf("%d",&s_no);

      int train_index = t_no % 1000;
      struct node *temp = t[train_index].p;
      struct node *s = NULL;
      while(temp != NULL && !(strcmp(temp->name,nname) == 0 && temp->train_no == t_no))
      {
            s = temp;
            temp = temp->nex;
      }

      if(temp->train_no == t_no)
      {
            pass_count[train_index]--;
            printf("\n\nSuccessfully Cancelled");
            printf("\n\nAmount you Initially paid : %.2f",temp->price);
            printf("\nAmount Refunded : %.2f",temp->price * 0.75);
            total_price[train_index] = total_price[train_index] - (0.75 * temp->price);

            if(temp == t[train_index].p)
                  t[train_index].p = NULL;
            else if(temp->nex != NULL)
                  s->nex = temp->nex;
            else
                  s->nex = NULL;
            
            temp->nex = NULL;
      }

      printf("\n\n\nPress Any Key to Return to Main Menu : ");
      getch();
}

/*********************************************************
            Function to Provide Text Output
**********************************************************/
void In_Text(void)
{
      FILE *fptr;
      int t_no;
      
      system("cls");
      printf("\n========================================\n");
	printf("   Total Details About Particular Train ");
	printf("\n========================================");

      printf("\n\nEnter The Train Number : ");
      scanf("%d",&t_no);
      fptr = fopen("program.txt", "a");
      struct node *tt;
      tt = t[t_no%1000].p;
      fprintf(fptr,"\n\n\n\nReservation Details of %d So far : \n\n",t_no);
      fprintf(fptr,"%s","--------------------------------------------------------------\n");
      fprintf(fptr,"Number of Tickets Booked : %d\n",pass_count[t_no%1000]);
      fprintf(fptr,"Total Amount Gained Including Cancellation Charges : %.2f\n",total_price[t_no%1000]);
      fprintf(fptr,"%s","--------------------------------------------------------------\n");
      while(tt != NULL)
      {
            fprintf(fptr,"Name : %s\n",tt->name);
            fprintf(fptr,"Age : %d\n",tt->age);
            fprintf(fptr,"Train No : %d  |  Seat No : %d  | Comp No : %d\n",tt->train_no,tt->seat_no,tt->comp_no);
            fprintf(fptr,"Ticket Price : %.2f\n",tt->price);
            fprintf(fptr,"%s","-------------------------------------------------------------\n");
            tt = tt->nex;
      }
      fclose(fptr);
      printf("\n\n\nPress Any Key to Return to Main Menu : ");
      getch();
}

/*********************************************************
     Function to Initialize Seats with Seat Numbers
**********************************************************/
void Initialize_Seats(void)
{
      for(int i=1;i<5;i++)
      {
            t[i].p = NULL;
            for(int j=1;j<51;j++)
            {
                  seats[i][j] = j;
            }
      }
}

/*********************************************************
                  MAIN FUNCTION
**********************************************************/
int main()
{
      int choice;
      Initialize_Seats();
      system("cls");

      printf("\t\t=================================================\n");
	printf("\t\t|                                               |\n");
	printf("\t\t|        -----------------------------          |\n");
	printf("\t\t|           TRAIN TICKET RERS. SYSTEM           |\n");
	printf("\t\t|        -----------------------------          |\n");
	printf("\t\t|                                               |\n");
	printf("\t\t|                                               |\n");
	printf("\t\t=================================================\n\n\n");

      printf("Press Any key to Continue : ");
      getch();
      system("cls");
      int run = 1;
      while(run)
      {
            system("cls");
            printf("-----------------------------------------------------------");
            printf("\nPress 1 to view the Trains List \n");
            printf("Press 2 to Reserve a Ticket\n");
            printf("Press 3 to Cancel the Ticket\n");
            printf("Press 4 to Get the Booking details in the Text Format\n");
            printf("Press 5 to EXIT \n");
            printf("-----------------------------------------------------------");

            printf("\n\n\nEnter your choice : ");
            scanf("%d",&choice);

            switch(choice)
            {
                  case 1 :Show();
                        break;
                  
                  case 2:Reserve();
                        break;

                  case 3:Cancel();
                        break;
                  
                  case 4:In_Text();
                        break;

                  case 5:run = 0;
                        break;
            }
      }
      
}