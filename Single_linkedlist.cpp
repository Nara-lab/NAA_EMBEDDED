typedef struct Node
{
  int data;
  Node *next;
};Node *head;
void ptr(Node *temp, int value)
{
  temp =(Node *)malloc(sizeof (Node)); //temp = new Node;
  temp->data =value;
  temp->next =NULL;
  head =temp;
  cout << temp->data<<"="<<head << std::endl;
}
int main()
{
  Node *node;
  for(int i =0;i<20;i++ )
   {
       ptr(node,i);
   }
  return 0;
}
