#include <iostream>
#include <stdlib.h>
using namespace std;

class Student{
    public:
        Student(char* firstName_a, char* familyName_a, char* studentId_a, int yearOfStudy_a):
            firstName(firstName_a), familyName(familyName_a), studentId(studentId_a), yearOfStudy(yearOfStudy_a){}

        char* getFirstName(){
            return firstName;
        }
        char* getFamilyName(){
            return familyName;
        } 
        char* getStudentId(){
            return studentId;
        }   
        int getYearOfStudy(){
            return yearOfStudy;
        }
    private:
        char* firstName;
        char* familyName;
        char* studentId;
        int yearOfStudy;
};

class StudentIdLessZeroException{
    public:
        char* getReason(){
            return "StudentId cannot be less than 0\n";
        }
};

class YearOfStudyLessZeroException{
    public:
        char* getReason(){
            return "YearOfStudy cannot be less than 0\n";
        }
};

class YearOfStudyGreaterSixException{
    public:
        char* getReason(){
            return "YearOfStudy cannot be greater than 6\n";
        }
};


int main(void){
    int firstNameSize = 16;
    int firstNameIndex = 0;
    char* firstName = (char*) malloc(firstNameSize);
    int familyNameSize = 16;
    int familyNameIndex = 0;
    char* familyName = (char*) malloc(familyNameSize);
    int studentIdSize = 16;
    int studentIdIndex = 0;
    char* studentId = (char*) malloc(familyNameSize);
    int yearOfStudy;
    char line[256];
    Student* stud = NULL;
    printf("Enter the values for a student: (name, surname, id, yearOfStudy) ");
    try{
        if(fgets(line, sizeof(line), stdin)!=NULL){
            int i = 0;
            for(int k = 0; k<4; k++, i++){
                while(line[i]!=',' && line[i]!='\n'){
                    if(k==0){
                        if(firstNameIndex>=firstNameSize){
                            firstNameSize*=2;
                            firstName = (char*) realloc(firstName, firstNameSize);
                        }
                        firstName[firstNameIndex++] = line[i];
                    }else if(k==1){
                        if(familyNameIndex>=familyNameSize){
                            familyNameSize*=2;
                            firstName = (char*) realloc(firstName, familyNameSize);
                        }
                        familyName[familyNameIndex++] = line[i];
                    }else if(k==2){
                        if(line[i]=='-'){
                            throw StudentIdLessZeroException();
                        }
                        if(studentIdIndex>=studentIdSize){
                            studentIdSize*=2;
                            firstName = (char*) realloc(firstName, studentIdSize);
                        }
                        studentId[studentIdIndex++] = line[i];
                    }else if(k==3){
                        if(line[i]=='-' || (line[i]-48)==0){
                            throw YearOfStudyLessZeroException();
                        }else if( (line[i]-48)>=6 || (line[i+1]-48)>=0 ){
                            throw YearOfStudyGreaterSixException();
                        }
                        yearOfStudy = (line[i]-48);
                    }
                    i++;
                }
            }

            firstName = (char*) realloc(firstName, firstNameIndex);
            familyName = (char*) realloc(familyName, familyNameIndex);
            studentId = (char*) realloc(studentId, studentIdIndex);

            /* if(studentId[0]=='-'){
                throw StudentIdLessZeroException();
            } *//* else if(yearOfStudy<=0){
                throw YearOfStudyLessZeroException();
            }else if(yearOfStudy>6){
                throw YearOfStudyGreaterSixException();
            } */
            stud = new Student(firstName, familyName, studentId, yearOfStudy);
            cout<<"Student's name: "<<(*stud).getFamilyName()<<" "<<(*stud).getFirstName()<<"\n"
                <<"With StudentId: "<<(*stud).getStudentId()<<"\n"
                <<"Year of study: "<<(*stud).getYearOfStudy()<<endl;
        }
    }catch(StudentIdLessZeroException ex){
        cout<<ex.getReason()<<endl;
    }catch(YearOfStudyLessZeroException ex){
        cout<<ex.getReason()<<endl;
    }catch(YearOfStudyGreaterSixException ex){
        cout<<ex.getReason()<<endl;
    }
    
    return 1;
}
