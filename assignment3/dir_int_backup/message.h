
#include <iostream>
using namespace std;


#ifndef MESSAGE
#define MESSAGE

class message
{
    public:
        message();
        message(int);
        message(const message &);
        ~message();

        void copy(const message &);

        bool operator < (const message &)const;
        bool operator > (const message &)const;
        bool operator == (const message &)const;
        bool operator != (const message &)const;
        bool operator >= (const message &)const;
        bool operator <= (const message &)const;

        bool operator < (const message *)const;
        bool operator > (const message *)const;
        bool operator == (const message *)const;
        bool operator != (const message *)const;
        bool operator >= (const message *)const;
        bool operator <= (const message *)const;

        message & operator = (const message &);

        friend ostream & operator << (ostream & out, const message & msg); 
    protected:
        int data;
};

#endif
