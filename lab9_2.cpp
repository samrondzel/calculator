#include <string.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

//Algebraic formula for encryption: Ei = (Pi + Ki) mod 26

int main(void){
    char line[256];
    char key[] = "lemon";
    int keySize = strlen(key);
    printf("Enter the message to be encrypted: ");
    if(fgets(line, sizeof(line), stdin)!=NULL){
        int msgIndex = 0;
        int msgSize = 32;
        char* msg = (char*) malloc(msgSize);
        for(int i = 0; line[i]; i++){
            if(msgIndex>=msgSize){
                msgSize*=2;
                msg = (char*) realloc(msg, msgSize);
            }
            if(line[i]>=65 && line[i]<=90){
                line[i] = (line[i]+32);
            }
            msg[msgIndex++]=line[i];
        }
        msg = (char*) realloc(msg, msgIndex);
        msgSize = msgIndex-1;

        int i, j;
        char keyStream[msgSize], cipheredText[msgSize];

        for(i = 0, j = 0; i < msgSize; i++, j++){
            if(j == keySize)
                j = 0;
    
            keyStream[i] = key[j];
        }
    
        for(i = 0; i < msgSize; i++){
            if(msg[i]==' '){
                cipheredText[i]=' ';
            }else
                cipheredText[i] = ((msg[i] + keyStream[i]) % 26) + 'a';
        }
    
        cipheredText[i] = '\0';
        cout<<"Encrypted Message: "<<cipheredText<<endl;
    }
    
    return 1;
}