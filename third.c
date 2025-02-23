#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
   int data;
   struct Node* next;
};

struct Node* createNode(int value){
   struct Node* newNode = malloc(sizeof(struct Node));
   newNode->data = value;
   newNode->next = NULL;
   return newNode;
}

void deleteNode (struct Node **head, int value){
   struct Node* temp = *head, *prev = NULL;
   if(temp != NULL && temp->data == value){
      *head = temp->next;
      free(temp);
      return;
   }
   while(temp != NULL && temp->data != value){
      prev = temp;
      temp = temp->next;
   }
   if(temp == NULL) 
      return;
   prev->next = temp->next;
   free(temp);
}

void printList(struct Node* head){
   if (head == NULL) 
      printf("EMPTY");
   else{
      while(head != NULL){
         printf("%d\t", head->data);
         head = head->next;
      }
   }
   printf("\n");
}

void insertNode (struct Node **head, int value){
   struct Node* newNode = createNode(value);
   if (*head == NULL){
      *head = newNode;
      return;
   }
   if (value < (*head)->data){
      newNode->next = *head;  //points new Node to previous head
      *head = newNode;
      return;
   }
   struct Node* temp = *head, *prev = NULL;
   if ((*head)->next == NULL) {
      (*head)->next = newNode;
      return;
   }
   while(temp != NULL && value >= temp->data){
      prev = temp;
      temp = temp->next;
   }
   //if(temp == NULL) 
    //  return;
   prev->next = newNode;
   newNode->next = temp;
   //free(temp);
   
}

int main(int argc, char** argv){
   //printf("hi");
   if(argc < 2) { //checks if there are 2 arguments!
      fprintf(stderr,"./first {text file}"); //prints messages to stderr. Primarily for error messages
      exit(1); //exits the program with a return code 1.
   }
   
   FILE *infile = fopen(argv[1], "r");
   if(infile == NULL){ //if fopen fails to open the file, it returns NULL
      fprintf(stderr,"%s failed to open\n",argv[1]);
      exit(1); //exits your program
   }
   char str[10];
   int num;
   struct Node* head = NULL;
   
   //while (infile != NULL){
   while ((fscanf(infile, "%s %d", str, &num)) == 2){
      //fscanf(infile, "%s %d", str, &num);
      if (str[0] == 'I'){
         insertNode(&head, num);
      }
      else if (str[0] == 'D'){
         deleteNode(&head, num);
      }
      else
         exit(1);
      
      printList(head);
      //print entire list
   }
   fclose(infile);
   
   // Free allocated memory
   while (head) {
      struct Node* temp = head;
      head = head->next;
      free(temp);
   }
}
