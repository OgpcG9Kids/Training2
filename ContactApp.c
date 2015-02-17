#include "stdio.h"
#include "stdlib.h"
#include "string.h"
/* our own variable
inputs: none
outputs none
*/
  struct Contact
  {
      char FirstName[50];
      char LastName[50];
      char Email[50];
  };

  struct Contact PersonContacts[100];
  int CurrentNumberofContacts;
  char ContactFileName[100];
/*
print menu
inputs:none
outputs:none
*/
  void PrintMenu()
  {
    printf("Please enter: Print(p), Find(f), Add(a), Quit(q): ");
  }

  char AskUserMainCommand()
  {
    char command;
    command = getchar();
    return command;
  }

  char* AskUserForFirstName()
  {
    char name[100];
    char *pointerToName;
    
    printf("\nPlease enter first name:");
    scanf("%s",name);
    
    pointerToName = malloc( strlen(name) + 1 );
    strcpy(pointerToName, name);
    
    return pointerToName;
  }
/*
ask for updating a contact
inputs:firstname
outputs:int
*/
  int AskWhetherToUpdateOrNot(char* firstName)
  {
    char command;
    
    printf("'%s' exists, do you want to update it( y to update )?",firstName);
    command = getchar();
    if( command == 'y' || command == 'Y' )
    {
        return 1;
    }
    return 0;
  }
  //messages
  void PrintExitMessage()
  {
    printf("\n\tThank you for using our app!");
  }

  void PrintError()
  {
    printf("please enter valid command.\n");
  }
  
  void PrintNoUserFound(char* firstName)
  {
    printf("\t%s not found\n",firstName);
  }

  void PrintSuccessfulAddMessage()
  {
    printf("\tContact has been added successfully.\n");
  }
  
  void PrintContactFileError()
  {
     printf("%s could not be opened",ContactFileName);
  }
  
  void PrintNotAddedMessage()
  {
      printf("\n\t Contact has not been added.\n");
  }
  /*
  printing contacts
  inputs:contactindex
  outputs:none
  */
  void PrintContactAtIndex(int contactIndex)
  {
    printf("%20s %20s %20s\n","firstName","lastName","Email"); 
    printf("%20s %20s %20s\n","=========","========","====="); 
    printf("%20s %20s %20s\n",PersonContacts[contactIndex].FirstName ,PersonContacts[contactIndex].LastName , PersonContacts[contactIndex].Email);
    printf("\n");
  }
  
  void PrintUpdatedMessage(char* firstName)
  {
    printf("\n\t'%s' has been updated.\n",firstName);
  }
  /*
  loading contacts
  inputs: none
  outputs:int
  */
  int LoadContacts()
  {
        char firstName[50];
        char lastName[50];
        char email[50];
        int  numberofItemsReadFromFile;
        FILE* fp;
        
        CurrentNumberofContacts = 0;

        fp = fopen(ContactFileName,"r");
        if( fp == NULL )
        {
            PrintContactFileError();
            return 0;
        }
        
        while( numberofItemsReadFromFile == fscanf(fp,"%s %s %s\n",firstName,lastName,email) == 3)
        {
          strcpy( PersonContacts[CurrentNumberofContacts].FirstName,firstName);
          strcpy( PersonContacts[CurrentNumberofContacts].LastName,lastName);
          strcpy( PersonContacts[CurrentNumberofContacts].Email,email);
          CurrentNumberofContacts++;
        }
        
        fclose(fp);
        return 1;
  }
/*
printing contacts
inputs: none
outputs: none
*/
  void PrintContacts()
  {
      int i;
      
      printf("\n\n");
      printf("%20s %20s %20s\n","FirstName", "LastName", "Email");
      printf("%20s %20s %20s\n","---------", "--------", "----");
      for(i=0; i<CurrentNumberofContacts; i++)
      {
          printf("%20s %20s %20s\n",PersonContacts[i].FirstName, PersonContacts[i].LastName, PersonContacts[i].Email);
      }
      printf("\n");
  }

  int GetContactIndex( char* firstName )
  {
    int contactBlockIndex = 0;
    
    for( contactBlockIndex=0;  contactBlockIndex<CurrentNumberofContacts;  contactBlockIndex++)
    {
        if( strcmp(PersonContacts[ contactBlockIndex].FirstName,firstName) == 0 )
        {
            return  contactBlockIndex;
        }
    }
    return -1;
  }
/*
finding and printing contacts
inputs:none
outputs:none
*/
  void FindAndPrintContact()
  {
      int foundIndex;
      char *pointerToFirstName;
      
      pointerToFirstName = AskUserForFirstName();
      foundIndex = GetContactIndex(pointerToFirstName);
      if( foundIndex == -1 )
      {
          PrintNoUserFound(pointerToFirstName);
      }
      else
      {
          PrintContactAtIndex(foundIndex);
      }
      free(pointerToFirstName);
  }
  //adding contacts
  void AddContactToMemory(char* firstName, char* lastName, char* email)
  {
      strcpy( PersonContacts[CurrentNumberofContacts].FirstName,firstName);
      strcpy( PersonContacts[CurrentNumberofContacts].LastName,lastName);
      strcpy( PersonContacts[CurrentNumberofContacts].Email,email);
      
      CurrentNumberofContacts++;
  }
  
  void AddContactToFile(char* firstName, char* lastName, char* email)
  {
    FILE* fp;
    fp = fopen(ContactFileName,"a");
    if( fp == NULL )
    {
        PrintContactFileError();
        return;
    }
    
    fprintf(fp,"%s %s %s\n",firstName, lastName, email);
    fclose(fp);
  }
 //updating contacts 
  void UpdateContactInMemory(char* firstName, char* lastName, char* email)
  {
    int existingContactBlockIndex;
    
    existingContactBlockIndex = GetContactIndex(firstName);
    if( existingContactBlockIndex  == -1 )
    {
        return;
    }
    
    strcpy(PersonContacts[existingContactBlockIndex].FirstName,firstName);
    strcpy(PersonContacts[existingContactBlockIndex].LastName,lastName);
    strcpy(PersonContacts[existingContactBlockIndex].Email,email);
  }
  
  void UpdateContactInFile(char* firstName, char* lastName, char* email)
  {
    FILE* fp;
    int i;
    
    fp = fopen(ContactFileName,"w");
    if( fp == NULL )
    {
        PrintContactFileError();
        return;
    }
    
    for(i=0; i<CurrentNumberofContacts; i++)
    {
      fprintf(fp,"%s %s %s\n",PersonContacts[i].FirstName,PersonContacts[i].LastName, PersonContacts[i].Email);
    }
    
    fclose(fp);
  } 
  

  void AskAndAddContact()
  {
      char firstName[50];
      char lastName[50];
      char email[50];
      int existingContactBlockIndex;
      
      printf("\n\tEnter firstname lastname email:");
      scanf("%s %s %s",firstName,lastName,email);
      
      existingContactBlockIndex = GetContactIndex(firstName);
      
      if( existingContactBlockIndex == -1 )
      {
          AddContactToMemory(firstName,lastName,email);
          AddContactToFile(firstName,lastName,email);
          PrintSuccessfulAddMessage();
      }
      else
      {
          if( AskWhetherToUpdateOrNot(firstName) )
          {
              UpdateContactInMemory(firstName,lastName,email);
              UpdateContactInFile(firstName,lastName,email);
              PrintUpdatedMessage(firstName);
          }
          else
          {
              PrintNotAddedMessage();
          }
      }
  }
  
  
  int main()
  {
    char command;
    
    strcpy(ContactFileName,"contact.txt");
    if( !LoadContacts() )
    {
    
    }
    
    PrintContacts();
    do
    {
      PrintMenu();
      command = AskUserMainCommand();
      if( command == 'q' )
      {
        PrintExitMessage();
        break;
      }
      switch(command)
      {
        case 'a':
              AskAndAddContact();
              break;
        case 'f':
              FindAndPrintContact();
              break;
        case 'p': 
              PrintContacts();
              break;
        default:
              PrintError();
              break;
      }
      
    }while(1);
  }