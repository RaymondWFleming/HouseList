/**********************
*  Raymond Fleming    *
*  House Data         *
*  Linked List        *
***********************/


#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//linked list structure holding information about a house
struct node
{
 	   char name[20];
 	   char address[20];
 	   char sqft[20];
 	   char bed[20];
 	   char bath[20];
 	   
 	   struct node *next;
};


//-------------------------------------------------------------------------------------------------------------------------------------------


void *displayHouse(struct node *list)           //function to display contents of linked list, skips trying to print and reports empty list if node passed is null
{
      struct node *tempHouse;
      tempHouse=malloc(sizeof(struct node));
      tempHouse=list;
      
      system("cls");
      
      if(tempHouse!=NULL)                       //checking for empty list
      {
         printf("\n\n\n -------------------------------------------------------------------------  \n");
         printf("|      Name       |        Address       |    Sqft.  |   Beds   |  Baths  |");
         
         do
         {
    
            printf("\n -------------------------------------------------------------------------  \n");
            printf("| %15s | %20s |  %6s   |",tempHouse->name,tempHouse->address,tempHouse->sqft);
            printf("   %3s    |  %3s    |",tempHouse->bed,tempHouse->bath);
            
            if (tempHouse->next!=NULL)          //checking to make sure a node won't be assigned to null
               tempHouse=tempHouse->next;
               
         }while(tempHouse->next!=NULL);
         
         printf("\n -------------------------------------------------------------------------  \n");  //printing out last line
         printf("| %15s | %20s |  %6s   |",tempHouse->name,tempHouse->address,tempHouse->sqft);
         printf("   %3s    |  %3s    |",tempHouse->bed,tempHouse->bath);
         
         printf("\n -------------------------------------------------------------------------  \n\n\n   ");
      }
      
      else
         printf("\n\n  The list is empty...\n\n    ");
         
      system("pause");
}


//-------------------------------------------------------------------------------------------------------------------------------------------


struct node *addHouse(struct node *list,char dataString[100],int file)  //file parameter indicates where function was called from
{
       
      struct node *newNode;
 	      newNode=malloc(sizeof(struct node));
         
 	   char name[20];
 	   char address[20];
 	   char sqft[20];
 	   char bed[20];
 	   char bath[20];
 	   char inputString[100];
 	   int i=0,c=0,d=0,e=0,f=0;
     
      fflush(stdin);                                              //flush stdin for fgets
      system("cls");       
             
 	   if (file==0) //checking to see if function was called from menu() or readFile()
      {
         printf("\n\n  Enter the name, address, square feet, bedrooms, and bathrooms,\n each separated by and ended with a semicolon: ");
         fgets(inputString,100,stdin);                           //get input string to tokenize
      }
      else
         strcpy(inputString,dataString);  //copying parameter string into input string for tokenizing
      
      while(inputString[i]!=';')          //tokenizing string with ; for delimiter
      {
         name[i]=inputString[i];          
         i++;
      }
      name[i]='\0';                      //appending null to index of semicolon
      i++;
        
      while(inputString[i]!=';')  
      {
         address[c]=inputString[i];
         i++;
         c++;
      }
      address[c]='\0';
      i++;
        
      while(inputString[i]!=';')
      {
         sqft[d]=inputString[i];
         i++;
         d++;
      }
      sqft[d]='\0';
      i++;
        
      while(inputString[i]!=';')
      {
         bed[e]=inputString[i];
         i++;
         e++;
      }
      bed[e]='\0';
      i++;
        
      while((inputString[i]!=';'))
      {
         bath[f]=inputString[i];
         i++;
         f++;
      }
      bath[f]='\0';
        
      strcpy(newNode->name,name);                //copying tokenized and null terminated strings into node
      strcpy(newNode->address,address);
      strcpy(newNode->sqft,sqft);
      strcpy(newNode->bed,bed);
      strcpy(newNode->bath,bath);

      newNode->next=list;                        //adding node to list
      list=newNode;
 
      return (list);                             //returning top node
}


//-------------------------------------------------------------------------------------------------------------------------------------------


struct node *readFiles(struct node *list) //function to read a list of houses into the linked list struct
{    
     char fileName[20];
     FILE *readFile;
     char inputString[100];
     
     struct node *tempHouse;
     tempHouse=malloc(sizeof(struct node));
     
     char name[20];
     char address[20];
     char sqft[20];
     char bed[20];
     char bath[20];  
     
     system("cls");
     printf("\n\n  What is the name of the file to open? ");
     scanf(" %s",fileName);
     readFile=fopen(fileName,"r");

     while(feof(readFile)==0)                                //adding nodes line by line until end of file
     {       
        fgets(inputString,100,readFile);
        
        tempHouse=list;
        list=addHouse(list,inputString,1);
        list->next=tempHouse;
     } 

     close(readFile);
     return (list);
}


//-------------------------------------------------------------------------------------------------------------------------------------------


struct node *searchHouse (struct node *list,int menu)    //function to find a specific node by owner's name in the list, then return it
{                                                        //menu parameter lets function know where it was called from
      struct node *tempHouse;
         tempHouse=malloc(sizeof(struct node));
         tempHouse=list;
     
      char name[20];
      char inputName[20];
      int i=0;
      
      system("cls");
      
      if (list!=NULL)                                    //check for empty list
      {
         if (menu==1)  //called from menu()
            printf("\n\n  What is the owner's name of the house\n  to find, followed by a semicolon?  ");
         else         //called from deleteHouse()...changeHouse() asks its own questions
            printf("\n\n  What is the owner's name of the house\n  to delete, followed by a semicolon? ");    
     
         fflush(stdin);  //flush stdin to get correct data input with fgets
         fgets(inputName,20,stdin);
         
         system("cls");
         
         while(inputName[i]!=';')  //tokenizing string using semicolons
         {
            name[i]=inputName[i];
            i++;                        
         }
         name[i]='\0';            //null terminating string name at index of semicolon
         
         if (strcmp(tempHouse->name,name)==0)  //checks first node in list against search string
         {
               if (menu==1)
               {  
                  printf("\n\n  House Found: \n\n     Name: %s  Address: %s",tempHouse->name,tempHouse->address);
                  printf("  Sqft: %s  Bedrooms: %s  Baths: %s\n\n\n     ",tempHouse->sqft,tempHouse->bed,tempHouse->bath);
                  system("pause");
                  
                  return(NULL);    
               }
               
               else if (menu==0)      
                  return(NULL);
               
               else if (menu==2)
                  return list;
         }
         else
         {
            while(tempHouse->next!=NULL)    //checks all other nodes against search string
            {
               if (strcmp(tempHouse->next->name,name)==0)
               { 
                  if (menu==1)              //let user know what house was found
                  {  
                     printf("\n\n  House Found: \n\n     Name: %s  Address: %s",tempHouse->next->name,tempHouse->next->address);
                     printf("  Sqft: %s  Bedrooms: %s  Baths: %s\n\n\n     ",tempHouse->next->sqft,tempHouse->next->bed,tempHouse->next->bath);
                     system("pause");
                     
                     return(tempHouse->next);    
                  }
                  
                  else if (menu==0)
                     return(tempHouse);     //return previous node to deleteHouse()
                     
                  else if (menu==2)         //return exact found node to changeHouse()
                     return (tempHouse->next);
               }       
            tempHouse=tempHouse->next;
            }                 
         }
     
        printf("\n\n Search failed, house not found\n");
     }
     else
        printf("\n\n  The list is empty...\n\n    ");
         
     system("pause");
}


//-------------------------------------------------------------------------------------------------------------------------------------------



struct node *deleteHouse(struct node *list)  //searches for a house using searchHouse function (empty list handling performed in searchHouse function)
{                                            //then deletes returned node.  If returned node is null, then it deletes the top node
      struct node *prev;
         prev=malloc(sizeof(struct node));
         prev=NULL;
     
      prev=searchHouse(list,0);             //call searchHouse() with menu option 0 to return previous node once found
      
      if (prev==NULL)                       //if the top node is returned, return the next node from top as top
         return list->next;
         
      else                               
      {
         if (prev->next->next==NULL)        //deleting bottom of list
            prev->next=NULL;
         else
            prev->next=prev->next->next;    //normal delete, skip a node with next->next
      }
      return list;  
}


//-------------------------------------------------------------------------------------------------------------------------------------------



struct node *changeHouse(struct node *list) //locate and change something about the data of a house
{
      struct node *changeNode;
         changeNode=malloc(sizeof(struct node));
       
      int i=0;
      char inputBed[20];
      char inputBath[20];
      char bed[20];
      char bath[20];
       
      system("cls");
      fflush(stdin);
      
      changeNode=searchHouse(list,2);   //searching for node to change, passing menu parameter 2 (indicating changeHouse()
      
      printf("\n\n  How many bedrooms should the new house have,\n  followed by semicolon? ");
      fgets(inputBed,20,stdin);
  
      while(inputBed[i]!=';')  //tokenizing string using semicolon as delimiter
      {
         bed[i]=inputBed[i];
         i++;                        
      }
      bed[i]='\0';             //appending string to have null character at index of semicolon
      i=0;
      
      system("cls"); 
      fflush(stdin);
      
      printf("\n\n  How many bathrooms should the new house have,\n  followed by semicolon? ");
      fgets(inputBath,20,stdin);
  
      while(inputBath[i]!=';')
      {
         bath[i]=inputBath[i];
         i++;                        
      }
      bath[i]='\0'; 
      
      strcpy(changeNode->bed,bed);   //copy new bed string into node
      strcpy(changeNode->bath,bath); //copy new bath string into node
       
      return list;      
}


//-------------------------------------------------------------------------------------------------------------------------------------------


int menu() //display the main menu
{
      int choice=0;
      system("cls");
      printf("\n\n\n     -------------------------------\n");
      printf("    |  1. Read a File               |\n");
      printf("     -------------------------------\n");
      printf("    |  2. Add a House               |\n");
      printf("     -------------------------------\n");
      printf("    |  3. Delete a House            |\n");
      printf("     -------------------------------\n");
      printf("    |  4. Display a list of Homes   |\n");
      printf("     -------------------------------\n");
      printf("    |  5. Search for a House        |\n");
      printf("     -------------------------------\n");
      printf("    |  6. Change data of a House    |\n");
      printf("     -------------------------------\n");
      printf("    |  7. Exit                      |\n");
      printf("     -------------------------------\n");
     
      printf("\n    Please enter your choice:  ");
      scanf("%d",&choice);
      return(choice);
}


//-------------------------------------------------------------------------------------------------------------------------------------------



int main(void)
{
 	   struct node *first;
 	      first=NULL;
 	
 	   int choice = 0;

 	   while (choice!=7)
 	   {
         choice=menu();
 	      switch (choice)
         {
            case 1: first=readFiles(first); break;
            case 2: first=addHouse(first,NULL,0); break;
            case 3: first=deleteHouse(first); break;
            case 4: displayHouse(first); break;
            case 5: searchHouse(first,1); break;
            case 6: first=changeHouse(first); break;
            case 7: return(1);
         }
      }
 	
 	   system("PAUSE");
      return 0;
}
