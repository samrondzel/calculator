#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// size from 2 to 20
void drawTriangle(int size){
    int i =1;
    while(i<=size){
        int k = i;
        while(k!=0){
            printf("X");
            k--;
        }
        printf("\n");
        i++;
    }
}

// size from 2 to 20
void drawSquare(int size){
    int i = 1;
    while(i<=size){
        printf("X");
        i++;
    }
    printf("\n");
    i = size-2;
    while(i!=0){
        printf("X");
        int k = size-2;
        while(k!=0){
            printf(" ");
            k--;
        }
        printf("X\n");
        i--;
    }
    i = 1;
    while(i<=size){
        printf("X");
        i++;
    }
    printf("\n");
}

// size from 1 to 20
void drawPyramid(int size){
    int i = 1;
    int amount = 1;
    int maxAmount = 1;
    while(i<=size){
        maxAmount+=2;
        i++;
    }
    i = 1;
    while(i<=size){
        int spacesN = (maxAmount-amount)/2 - 1;
        int j;
        for(j = 0; j<spacesN; j++){
            printf(" ");
        }
        for(j = 0; j<amount;j++){
            printf("X");
        }
        for(j = 0; j<spacesN; j++){
            printf(" ");
        }
        printf("\n");
        amount+=2;
        i++;
    }
}

// size from 1 to 20
void drawChristmasTree(int size){

    int layer = 1;
    int maxAmount = 1;
    while(layer<=size){
        maxAmount+=2;
        layer++;
    }
    layer = 1;
    while(layer<=size){
        int i = 1;
        int elementsLayer = 1;
        while(i<=layer){
            int spacesN = (maxAmount-elementsLayer)/2 - 1;
            int j;
            for(j = 0; j<spacesN; j++){
                printf(" ");
            }
            for(j = 0; j<elementsLayer;j++){
                printf("X");
            }
            for(j = 0; j<spacesN; j++){
                printf(" ");
            }
            printf("\n");
            i++;
            elementsLayer+=2;
        }
        layer++;
    }
}

// size from 2 to 20
void drawFigureX(int size){
}

// size from 2 to 20
void drawFigureY(int size){
}

// size from 3 to 20
void drawFigureZ(int size){
}

// size from 2 to 20
void drawFigureW(int size){
}

bool isCommand(const string command,const char *mnemonic){
	return command==mnemonic;
}

int main(){
	string line;
	string command;
	int value;
	cout << "START" << endl;
	while(true){
//		cin.getline(line, MAXLINE);
		getline(cin,line);
		std::stringstream stream(line);
		stream >> command;
		if(line=="" || command[0]=='#')
		{
			// ignore empty line and comment
			continue;
		}

		// copy line on output with exclamation mark
		cout << "!" << line << endl;;

		// change to uppercase
		command[0]=toupper(command[0]);
		command[1]=toupper(command[1]);

		if(isCommand(command,"HA")){
			cout << "END OF EXECUTION" << endl;
			break;
		}

		// read next argument, one int value
		stream >> value;

		if(isCommand(command,"TR"))
		{
			drawTriangle(value);
			continue;
		}
		if(isCommand(command,"SQ"))
		{
			drawSquare(value);
			continue;
		}
		if(isCommand(command,"PY"))
		{
			drawPyramid(value);
			continue;
		}
		if(isCommand(command,"CT"))
		{
			drawChristmasTree(value);
			continue;
		}
		if(isCommand(command,"FX"))
		{
			drawFigureX(value);
			continue;
		}
		if(isCommand(command,"FY"))
		{
			drawFigureY(value);
			continue;
		}
		if(isCommand(command,"FZ"))
		{
			drawFigureZ(value);
			continue;
		}
		if(isCommand(command,"FW"))
		{
			drawFigureW(value);
			continue;
		}

		cout << "wrong argument in test: " << command << endl;
	}

}
