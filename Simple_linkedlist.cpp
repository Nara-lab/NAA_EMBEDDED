typedef struct Node
{
    int data;
    Node *next;
};
Node *head;
void add_list(int value)
{
    Node *curret,*temp = new Node;
    temp->data = value;
    temp ->next = NULL;
      if(head == NULL)
      {
       head = temp;
       curret = temp;   // cout<<curret << " = " << curret->data << endl;
      }
      else
      {
          curret ->next = temp;
          curret = temp;//  cout<<curret << " = " << curret->data <<endl;
      }
}
void print()
{
    Node *temp = head;
    while(temp != NULL)
    {
        cout << temp->data <<endl;
        temp = temp -> next;
    }
}

int main()
{
    for(int i = 1; i <= 20 ; i++)
    {
    add_list(i);
    }
    print();

return 0;
}
