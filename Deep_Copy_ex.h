#include <iostream>
using namespace std;
 
 class Sample
 {
     int a,b,*d;
     public:
     Sample()
     {
         d = new int;
         std::cout << "constructor called" << std::endl;
     }
     Sample(Sample &s)
     {
         a = s.a;
         b = s.b;
         d = new int;
        *d = *s.d;
     }
    //  Sample & operator =(const Sample &i)
    //  {
    //      a = i.a;
    //      b = i.b;
    //      d = new int;
    //     *d = *i.d;
    //  }
     void getval(int x,int y,int z)
     {
         a= x;
         b = y;
         *d = z;
     }
    ~Sample()
    {
        delete d;
    }
     void print()
     {
         cout << a <<"\n" << b << "\n" << d << "\n";
     }
 };
int main()
{
 Sample s1;
     s1.getval(1,2,3);
       s1.print();
       Sample s2 = s1; // for deep copy(copy constructor will call)
//       s2 = s1;    // for deep copy (assignment operqater will call)
       s2.print();
    return 0;
}
