#include <iostream>

using namespace std;

void test();

class Account{
    static int num;
    public:
        Account(){
            cout<<"Account constructor is called to create the "<<++Account::num<<"th object"<<endl;
        }
        ~Account(){
            cout<<"Account destructor is called to destroy the "<<Account::num--<<"th object"<<endl;
        }
};

int Account::num = 0;

int main(void){
    test();
    return 1;
}

void test(){
    Account* ac1 = new Account();
    delete ac1;
}