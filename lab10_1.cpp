#include <iostream>
#include <stdlib.h>
using namespace std;

class EmptyStackError{
    public:
        void failureReason(){
            cout<<"Stack is empty. Cannot pop from it";
        }
};

bool isOperator(char* line, int index){
    bool isOperatorBool = false;
    if(line[index]=='+' || line[index]=='*' || line[index]=='/')
        isOperatorBool = true;
    else if(line[index]=='-' && (line[index+1]==' ' || line[index+1]==10))
        isOperatorBool = true;
    
    return isOperatorBool;
}

class StackType{
    public:
        void setInt(int num_a){
            number_i = num_a;
            isFloat = false;
        }
        void setFloat(float num_a){
            number_f = num_a;
            isFloat = true;
        }

        int getInt(){
            return number_i;
        }
        
        float getFloat(){
            return number_f;
        }

        float getIsFloat(){
            return isFloat;
        }

        friend ostream& operator<<(ostream& cout, StackType& stInstance);
    private:
        union{
            int number_i;
            float number_f;
        };
        float isFloat;
};

ostream& operator<<(ostream& cout, StackType& stInstance){
    if(stInstance.isFloat)
        printf("%.2f", stInstance.number_f);
    else  
        printf("%i", stInstance.number_i);
    return cout;
}

template<typename T>
class Stack{
    public:
        Stack(int numOfElements_a){
            numOfElements = numOfElements_a;
            stack = (T*) malloc(sizeof(T)*numOfElements);
            stackPointer = 0;
        }

        bool isEmpty(){
            return stackPointer<=0;
        }

        bool isFull(){
            return stackPointer>=numOfElements;
        }

        void push(T elem){
            if(isFull()){
                numOfElements*=2;
                stack = (T*) realloc(stack, sizeof(T)*numOfElements);
            }
            stack[stackPointer++] = elem;
        }

        T pop(){
            try{
                if(isEmpty())
                    throw EmptyStackError();
                else
                    return stack[--stackPointer];
            }catch(EmptyStackError ex){
                ex.failureReason();
            }
        }

        void showStack(){
            for(int i = stackPointer-1; i>=0; i--){
                cout<<stack[i]<<endl;
            }
        }
    private:
        T* stack;
        int stackPointer;
        int numOfElements;
};

int main(void){
    char line[256];
    Stack<StackType> stack(10);
    printf("Enter the desired calculation in the reverse Polish notation: ");
    if(fgets(line,sizeof(line),stdin)!=NULL){
        for(int i = 0; line[i] && line[i]!=10;i++){
            int number = 0;
            float number_f = 0.0;
            bool isFloat = false;
            bool isNegative = false;
            int degreeAfterDot = 1;
            if(!isOperator(line,i)){
                while(line[i]!=10 && line[i]!=' '){
                    if (line[i]=='-'){
                        isNegative = true;
                        i++;
                    }
                    if (line[i]=='.'){
                        isFloat = true;
                        number_f = number;
                        i++;
                    }
                    float temp = line[i]-48;
                    if(!isFloat){     
                        number*=10;
                        number+=temp;
                    }else{
                        for(int k = 0; k<degreeAfterDot; k++)
                            temp*=0.1;
                        degreeAfterDot++;
                        number_f+=temp;
                    }
                    i++;
                }
                if(isNegative && isFloat)
                    number_f = -number_f;
                if(isNegative && !isFloat)
                    number = -number;
                StackType stackElement;
                if(isFloat)
                    stackElement.setFloat(number_f);
                else
                    stackElement.setInt(number);
                stack.push(stackElement);
            }
            else{
                if(line[i]=='+'){
                    StackType num2 = stack.pop();
                    StackType num1 = stack.pop();
                    float num2_f = 0.0, num1_f = 0.0, sum_f = 0.0;
                    int num2_i = 0, num1_i = 0, sum_i = 0;
                    StackType stackElement;
                    if(num2.getIsFloat()){
                        num2_f = num2.getFloat();
                        if(num1.getIsFloat()){
                            num1_f = num1.getFloat();
                            sum_f = num1_f + num2_f;
                        }else{
                            num1_i = num1.getInt();
                            sum_f = num1_i + num2_f;
                        }
                        stackElement.setFloat(sum_f);
                    }else{
                        num2_i = num2.getInt(); 
                        if(num1.getIsFloat()){
                            num1_f = num1.getFloat();
                            sum_f = num1_f + num2_i;
                            stackElement.setFloat(sum_f);
                        }else{
                            num1_i = num1.getInt();
                            sum_i = num1_i + num2_i;
                            stackElement.setInt(sum_i);
                        }
                    }
                    stack.push(stackElement);
                }else if(line[i]=='-'){
                    StackType num2 = stack.pop();
                    StackType num1 = stack.pop();
                    float num2_f = 0.0, num1_f = 0.0, dif_f = 0.0;
                    int num2_i = 0, num1_i = 0, dif_i = 0;
                    StackType stackElement;
                    if(num2.getIsFloat()){
                        num2_f = num2.getFloat();
                        if(num1.getIsFloat()){
                            num1_f = num1.getFloat();
                            dif_f = num1_f - num2_f;
                        }else{
                            num1_i = num1.getInt();
                            dif_f = num1_i - num2_f;
                        }
                        stackElement.setFloat(dif_f);
                    }else{
                        num2_i = num2.getInt(); 
                        if(num1.getIsFloat()){
                            num1_f = num1.getFloat();
                            dif_f = num1_f - num2_i;
                            stackElement.setFloat(dif_f);
                        }else{
                            num1_i = num1.getInt();
                            dif_i = num1_i - num2_i;
                            stackElement.setInt(dif_i);
                        }
                        
                    }
                    stack.push(stackElement);
                }else if(line[i]=='*'){
                    StackType num2 = stack.pop();
                    StackType num1 = stack.pop();
                    float num2_f = 0.0, num1_f = 0.0, mul_f = 0.0;
                    int num2_i = 0, num1_i = 0, mul_i = 0;
                    StackType stackElement;
                    if(num2.getIsFloat()){
                        num2_f = num2.getFloat();
                        if(num1.getIsFloat()){
                            num1_f = num1.getFloat();
                            mul_f = num1_f * num2_f;
                        }else{
                            num1_i = num1.getInt();
                            mul_f = num1_i * num2_f;
                        }
                        stackElement.setFloat(mul_f);
                    }else{
                        num2_i = num2.getInt(); 
                        if(num1.getIsFloat()){
                            num1_f = num1.getFloat();
                            mul_f = num1_f * num2_i;
                            stackElement.setFloat(mul_f);
                        }else{
                            num1_i = num1.getInt();
                            mul_i = num1_i * num2_i;
                            stackElement.setInt(mul_i);
                        }
                        
                    }
                    stack.push(stackElement);
                }else if(line[i]=='/'){
                    StackType num2 = stack.pop();
                    StackType num1 = stack.pop();
                    float num2_f = 0.0, num1_f = 0.0, div_f = 0.0;
                    int num2_i = 0, num1_i = 0, div_i = 0;
                    StackType stackElement;
                    if(num2.getIsFloat()){
                        num2_f = num2.getFloat();
                        if(num1.getIsFloat()){
                            num1_f = num1.getFloat();
                            div_f = num1_f / num2_f;
                        }else{
                            num1_i = num1.getInt();
                            div_f = num1_i / num2_f;
                        }
                        stackElement.setFloat(div_f);
                    }else{
                        num2_i = num2.getInt(); 
                        if(num1.getIsFloat()){
                            num1_f = num1.getFloat();
                            div_f = num1_f / num2_i;
                            stackElement.setFloat(div_f);
                        }else{
                            num1_i = num1.getInt();
                            div_i = num1_i / num2_i;
                            stackElement.setInt(div_i);
                        }   
                    }
                    stack.push(stackElement);
                }
                i++;
            }
        }
        stack.showStack();
    }
    return 1;
}

//10 2.5 2 * / -5 + -1 *