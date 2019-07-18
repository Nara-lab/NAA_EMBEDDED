#include <iostream>
using namespace std;

 
 typedef struct Node
 {
     int data;
     Node *next;
 };
 Node *head;
 void cre(int value)
 {
     Node *curr,*temp = (Node*)malloc(sizeof(Node));
     temp ->data = value;
     temp ->next = NULL;
     if(head == NULL)
     {
         head = temp;
         curr = temp;
     }
     else
     {
         curr ->next = temp;
         curr = temp;
     }
 }
 void rav()
 {
     Node *prev = NULL;
     Node*curr = head;
     Node*next = NULL;
     while(curr != NULL)
     {
         next = curr ->next;
         curr ->next = prev;
         prev = curr;
         curr = next;
     }
     head = prev;
 }
 void dis()
 {
     Node *temp = head;
     while(temp != NULL)
     {
       std::cout << temp ->data << std::endl;
         temp = temp ->next;
     }
 }
 int main()
 {
     for(int i = 0;i<10;i++)
     {
         cre(i);
     }
     rav();
     dis();
     return 0;
 }
