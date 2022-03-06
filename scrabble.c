#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util/print_board.h"
#include "util/scrabble.h"

void task1(char game_board[15][15]){
    char STR[50],word[110][50];
    char NRlines[110],ycord[110],xcord[110],dcord[110];
    int valNRlines;
    char *Y,*X,*D,*W;
    char delims[] = " \n";

    fgets(NRlines, sizeof(NRlines), stdin);
    valNRlines = strtol(NRlines, NULL, 10);
 
    for(int i=0;i<valNRlines;i++){
        fgets(STR, sizeof(STR), stdin);
        X = strtok(STR, delims);
        xcord[i] = strtol(X, NULL, 10);
        Y = strtok(NULL, delims);
        ycord[i] = strtol(Y,NULL, 10);
        D = strtok(NULL, delims);
        dcord[i] = strtol(D, NULL, 10);
        W = strtok(NULL, delims);
        memcpy(word[i], W, strlen(W)+1);
    }

    for(int i=0;i<valNRlines;i++){

        int CORDX,CORDY,len;
        CORDY = ycord[i];
        CORDX = xcord[i];
        len = strlen(word[i]);

        if(dcord[i] == 0){
            for(int j=0;j<len;j++){
                game_board[CORDX][CORDY+j] = word[i][j];
            }
        }
        else if(dcord[i] == 1){
            for(int j=0;j<len;j++){
                game_board[CORDX+j][CORDY] = word[i][j];
            }
        }
    }
    print_board(game_board);
}

void task2(){
    int score[]={1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10};
    char STR[50],word[110][50];
    char NRlines[110];
    int valNRlines; 
    char *Y,*X,*D,*W;
    char delims[]=" \n";

    fgets(NRlines, sizeof(NRlines), stdin);
    valNRlines = strtol(NRlines, NULL, 10);

    for(int i=0;i<valNRlines;i++){
        fgets(STR, sizeof(STR), stdin);
        X = strtok(STR, delims);
        Y = strtok(NULL, delims);
        D = strtok(NULL, delims);
        W = strtok(NULL, delims);
        memcpy(word[i], W, strlen(W)+1);
    }

    int scoreplayer1 = 0,scoreplayer2 = 0;

    for(int i=0;i<valNRlines;i++){

        int index = 0,len;
        len = strlen(word[i]);

        for(int j=0;j<len;j++){
            index = word[i][j] - 'A';
            if(i%2 == 0){
                scoreplayer1 += score[index]; 
            }
            else if(i%2 == 1){
                scoreplayer2 += score[index]; 
            }
        }
    }
    printf("Player 1: %d Points\n",scoreplayer1);
    printf("Player 2: %d Points",scoreplayer2);
}

int RaisedPower(int base, int exponent){
    int result = 1;
    while (exponent){
        if (exponent & 1)result *= base;
        exponent >>= 1;
        base *= base;
    }
    return result;
}

int CalculateScorePlayer1(int scoreplayer1,int XXexists,
int YYexists,int contXX,int contYY,int scoreplayer1word){

    if(XXexists == 1 && YYexists == 0){
        scoreplayer1 += scoreplayer1word*RaisedPower(2,contXX);
    }
    else if(XXexists == 0 && YYexists == 1){
        scoreplayer1 += scoreplayer1word*RaisedPower(3,contYY);
    }
    else if(XXexists == 1 && YYexists == 1){ 
        scoreplayer1 += 
        scoreplayer1word*RaisedPower(2,contXX)*RaisedPower(3,contYY);
    }
    else if(XXexists == 0 && YYexists == 0){
        scoreplayer1 += scoreplayer1word;
    }   

    return scoreplayer1;
}

int CalculateScorePlayer2(int scoreplayer2, int XXexists,
int YYexists,int contXX,int contYY,int scoreplayer2word){

    if(XXexists == 1 && YYexists == 0){
        scoreplayer2 += scoreplayer2word*RaisedPower(2,contXX);
    }
    else if(XXexists == 0 && YYexists == 1){
        scoreplayer2 += scoreplayer2word*RaisedPower(3,contYY);
    }
    else if(XXexists == 1 && YYexists == 1){ 
        scoreplayer2 += 
        scoreplayer2word*RaisedPower(2,contXX)*RaisedPower(3,contYY);
    }
    else if(XXexists == 0 && YYexists == 0){
        scoreplayer2 += scoreplayer2word;
    }   

    return scoreplayer2;
}

void task3(){
    int  score[]={1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10};
    char STR[50],word[110][50],NRlines[110];
    int valNRlines; 
    char bonusXX[5],bonusYY[5],ycord[110],xcord[110],dcord[110];
    char *Y,*X,*D,*W,delims[]=" \n";

    fgets(bonusXX, sizeof(bonusXX), stdin);
    bonusXX[strlen(bonusXX) - 1] = '\0';

    fgets(bonusYY, sizeof(bonusYY), stdin);
    bonusYY[strlen(bonusYY) - 1] = '\0';

    fgets(NRlines, sizeof(NRlines), stdin);
    valNRlines = strtol(NRlines, NULL, 10);

    for(int i=0;i<valNRlines;i++){
        fgets(STR,sizeof(STR),stdin);
        X = strtok(STR,delims);
        xcord[i] = strtol(X,NULL,10);
        Y = strtok(NULL,delims);
        ycord[i] = strtol(Y,NULL,10);
        D = strtok(NULL,delims);
        dcord[i] = strtol(D,NULL,10);
        W = strtok(NULL,delims);
        memcpy(word[i], W, strlen(W)+1);
    }

   int scoreplayer1 = 0,scoreplayer2 = 0;

    for(int i=0;i<valNRlines;i++){

        int contXX = 0,contYY = 0,XXexists = 0,YYexists = 0;
        int index=0,len,CORDX,CORDY;
        len = strlen(word[i]);

        if(strstr(word[i],bonusXX)!=NULL)XXexists = 1;
        if((word[i][len-2] == bonusYY[0]) && 
        (word[i][len-1] == bonusYY[1]))YYexists = 1;

        CORDY = ycord[i]; CORDX = xcord[i];

        if(dcord[i] == 0){
            for(int j=0;j<len;j++){
                if(bonus_board[CORDX][CORDY+j] == 1)contXX += 1;
                else if(bonus_board[CORDX][CORDY+j] == 2)contYY += 1;
            }
        }
        else if(dcord[i]==1){
            for(int j=0;j<len;j++){
                if(bonus_board[CORDX+j][CORDY] == 1)contXX+=1;
                else if(bonus_board[CORDX+j][CORDY] == 2)contYY+=1;
            }
        }

        int scoreplayer1word = 0,scoreplayer2word = 0;

        for(int j=0;j<len;j++){
            index = word[i][j] - 'A';
            if(i%2 == 0){
                scoreplayer1word += score[index]; 
            }
            else if(i%2 == 1){
                scoreplayer2word += score[index]; 
            }
        }
        scoreplayer1 = CalculateScorePlayer1(scoreplayer1,XXexists,
        YYexists,contXX,contYY,scoreplayer1word);
        scoreplayer2 = CalculateScorePlayer2(scoreplayer2,XXexists,
        YYexists,contXX,contYY,scoreplayer2word);
    }
    printf("Player 1: %d Points\n",scoreplayer1);
    printf("Player 2: %d Points",scoreplayer2);
}

void task4(char game_board[15][15]){
    char STR[50],wordsplayed[110][50],NRlines[110];
    int valNRlines;  
    char *Y,*X,*D,*W,bonusXX[5],bonusYY[5];
    char ycord[110],xcord[110],dcord[110];
    char delims[] = " \n";

    fgets(bonusXX, sizeof(bonusXX), stdin);
    fgets(bonusYY, sizeof(bonusYY), stdin);
    fgets(NRlines, sizeof(NRlines), stdin);
    valNRlines = strtol(NRlines, NULL, 10);

    for(int i=0;i<valNRlines;i++){
        fgets(STR,sizeof(STR), stdin);
        X = strtok(STR, delims);
        xcord[i] = strtol(X, NULL, 10);
        Y = strtok(NULL, delims);
        ycord[i] = strtol(Y, NULL, 10);
        D = strtok(NULL, delims);
        dcord[i] = strtol(D, NULL, 10);
        W = strtok(NULL, delims);
        memcpy(wordsplayed[i], W, strlen(W)+1);
    }

    for(int i=0;i<valNRlines;i++){
        int CORDX,CORDY,len;
        CORDY = ycord[i];
        CORDX = xcord[i];
        len = strlen(wordsplayed[i]);

        if(dcord[i] == 0){
            for(int j=0;j<len;j++){
                game_board[CORDX][CORDY+j] = wordsplayed[i][j];
            }
        }
        else if(dcord[i] == 1){
            for(int j=0;j<len;j++){
                game_board[CORDX+j][CORDY] = wordsplayed[i][j];
            }
        }
    }

    for(int i=0;i<100;i++){
        int len = strlen(words[i]);
        int checkUSE = 0,STOP = 0;

        for(int j=0;j<valNRlines;j++){
            if(strcmp(words[i],wordsplayed[j]) == 0)checkUSE = 1 ;
        }

        if(checkUSE == 0){

            for(int j=0;j<15;j++){
                
                for(int k=0;k<15;k++){
                    int stopORIZ = 0, stopVERT = 0;

                    if(game_board[j][k] == words[i][0]){

                        if((game_board[j][k+1] == '.') && 
                        ((14-k) >= (len-1))){
                     
                            for(int m=2;m<len;m++){
                                if(game_board[j][k+m] != '.'){
                                    stopORIZ = 1;
                                    break;
                                }
                            }
                            if(stopORIZ == 0){
                                for(int m=0;m<len;m++){
                                    game_board[j][k+m] = words[i][m];
                                }
                                STOP = 1;
                            }
                        }
                        else if((game_board[j+1][k] == '.') && 
                        ((14-j) >= (len-1))){
                        
                            for(int m=2;m<len;m++){
                                if(game_board[j+m][k] != '.'){
                                    stopVERT = 1;
                                    break;
                                }
                            }
                            if(stopVERT == 0){
                                for(int m=0;m<len;m++){
                                    game_board[j+m][k] = words[i][m];
                                }
                                STOP = 1;
                            } 
                        }
                    }
                    if(STOP == 1)break;
                }
                if(STOP == 1)break;
            }
        }
        if(STOP == 1)break;
    }
   print_board(game_board);
}

int wordscore(char wordToVerify[],int CORDX, 
int CORDY,int directie,char bonusXX[5],char bonusYY[5]){
    int score[] = {1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10};
    int contXX = 0,contYY = 0,XXexists = 0,YYexists = 0;
    int index = 0,wordscore=0;
    int len = strlen(wordToVerify);

    if(strstr(wordToVerify, bonusXX)!=NULL)XXexists = 1;
    if((wordToVerify[len-2] == bonusYY[0]) && 
    (wordToVerify[len-1] == bonusYY[1]))YYexists = 1;

    if(directie == 1){
        for(int i=0;i<len;i++){
            if(bonus_board[CORDX][CORDY+i] == 1)contXX += 1;
            else if(bonus_board[CORDX][CORDY+i] == 2)contYY += 1;
        }
    }
    else if(directie == 2){
        for(int i=0;i<len;i++){
            if(bonus_board[CORDX+i][CORDY] == 1)contXX += 1;
            else if(bonus_board[CORDX+i][CORDY] == 2)contYY += 1;
        }
    }

    for(int i=0;i<len;i++){

        index = wordToVerify[i] - 'A';
        wordscore += score[index]; 
    }

    if(XXexists == 1 && YYexists == 0){
        wordscore += wordscore*RaisedPower(2,contXX);
    }
    else if(XXexists == 0 && YYexists == 1){
        wordscore += wordscore*RaisedPower(3,contYY);
    }
    else if(XXexists == 1 && YYexists == 1){ 
        wordscore = wordscore*RaisedPower(2,contXX)*RaisedPower(3,contYY);
    } 

    return wordscore;
}

void PlaceWords(int valNRlines,char ycord[110],char xcord[110],
char dcord[110],char game_board[15][15],char wordsplayed[110][50]){

    for(int i=0;i<valNRlines;i++){
        int CORDX,CORDY,len;
        CORDY = ycord[i];
        CORDX = xcord[i];
        len = strlen(wordsplayed[i]);

        if(dcord[i] == 0){
            for(int j=0;j<len;j++){
                game_board[CORDX][CORDY+j] = wordsplayed[i][j];
            }
        }
        else if(dcord[i] == 1){
            for(int j=0;j<len;j++){
                game_board[CORDX+j][CORDY] = wordsplayed[i][j];
            }
        }
    }

}

void task5(char game_board[15][15]){
    int score[] = {1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10};
    char STR[50],wordsplayed[110][50],NRlines[110];
    int valNRlines;  
    char *Y,*X,*D,*W,delims[] = " \n";
    char bonusXX[5],bonusYY[5],ycord[110],xcord[110],dcord[110];
    int scoreplayer1 = 0,scoreplayer2 = 0;

    fgets(bonusXX, sizeof(bonusXX), stdin);
    bonusXX[strlen(bonusXX) - 1] = '\0';
    fgets(bonusYY, sizeof(bonusYY), stdin);
    bonusYY[strlen(bonusYY) - 1] = '\0';
    fgets(NRlines, sizeof(NRlines), stdin);
    valNRlines = strtol(NRlines, NULL, 10);

    for(int i=0;i<valNRlines;i++){
        fgets(STR, sizeof(STR), stdin);
        X = strtok(STR, delims);
        xcord[i] = strtol(X, NULL, 10);
        Y = strtok(NULL, delims);
        ycord[i] = strtol(Y, NULL, 10);
        D = strtok(NULL, delims);
        dcord[i] = strtol(D, NULL, 10);
        W = strtok(NULL, delims);
        memcpy(wordsplayed[i], W, strlen(W)+1);
    }

    for(int i=0;i<valNRlines;i++){
        int contXX = 0,contYY = 0,XXexists = 0,YYexists = 0;
        int index = 0,len,CORDX,CORDY;
        len = strlen(wordsplayed[i]);

        if(strstr(wordsplayed[i], bonusXX)!=NULL)XXexists = 1;
        if((wordsplayed[i][len-2] == bonusYY[0]) && 
        (wordsplayed[i][len-1] == bonusYY[1]))YYexists = 1;

        CORDY = ycord[i]; CORDX = xcord[i];

        if(dcord[i] == 0){
            for(int j=0;j<len;j++){
                if(bonus_board[CORDX][CORDY+j] == 1)contXX += 1;
                else if(bonus_board[CORDX][CORDY+j] == 2)contYY += 1;
            }
        }
        else if(dcord[i] == 1){
            for(int j=0;j<len;j++){
                if(bonus_board[CORDX+j][CORDY] == 1)contXX += 1;
                else if(bonus_board[CORDX+j][CORDY] == 2)contYY += 1;
            }
        }

        int scoreplayer1word = 0,scoreplayer2word = 0;

        for(int j=0;j<len;j++){
            index = wordsplayed[i][j] - 'A';
            if(i%2 == 0){
                scoreplayer1word += score[index]; 
            }
            else if(i%2 == 1){
                scoreplayer2word += score[index]; 
            }
        }
        scoreplayer1 = CalculateScorePlayer1(scoreplayer1,XXexists,
        YYexists,contXX,contYY,scoreplayer1word);
        scoreplayer2 = CalculateScorePlayer2(scoreplayer2,XXexists,
        YYexists,contXX,contYY,scoreplayer2word);
    }

    PlaceWords(valNRlines,ycord,xcord,dcord,game_board,wordsplayed);

    for(int i=0;i<100;i++){
        int len = strlen(words[i]);
        int checkUSE = 0,STOP =0;
        char wordToVerify[20];                    
        strcpy(wordToVerify,words[i]);

        for(int j=0;j<valNRlines;j++){
            if(strcmp(words[i],wordsplayed[j])==0)checkUSE = 1 ;
        }

        if(checkUSE == 0){
            for(int j=0;j<15;j++){
                for(int k=0;k<15;k++){
                    int stopORIZ = 0, stopVERT = 0;
                    int proceedORIZ = 0,proceedVERT = 0;
                    int winningscore = 0;

                    if(game_board[j][k] == words[i][0]){
                        int directie;

                        if((game_board[j][k+1] == '.') && ((14-k) >= (len-1))){
                            directie = 1;
                     
                            for(int m=2;m<len;m++){
                                if(game_board[j][k+m] != '.'){
                                    stopORIZ = 1;
                                    break;
                                }
                            }
                            if(stopORIZ == 0){
                                winningscore = wordscore(wordToVerify, 
                                j,k,directie,bonusXX,bonusYY);

                                if((scoreplayer2 + winningscore) 
                                >= scoreplayer1 )proceedORIZ = 1;
                            }
                            if(proceedORIZ == 1){
                                for(int m=0;m<len;m++){
                                    game_board[j][k+m] = words[i][m];
                                }
                                STOP = 1;
                            }
                        }
                        else if((game_board[j+1][k] == '.') 
                        && ((14-j) >= (len-1))){
                            directie = 2;
                        
                            for(int m=2;m<len;m++){
                                if(game_board[j+m][k] != '.'){
                                    stopVERT = 1;
                                    break;
                                }
                            }
                            if(stopVERT == 0){
                                winningscore = wordscore(wordToVerify, 
                                j,k,directie,bonusXX,bonusYY);

                                if((scoreplayer2 + winningscore) 
                                >= scoreplayer1 )proceedVERT = 1;
                            }
                            if(proceedVERT == 1){
                                for(int m=0;m<len;m++){
                                    game_board[j+m][k] = words[i][m];
                                }
                                STOP = 1;
                            } 
                        }
                    }
                    if(STOP == 1)break;
                }
                if(STOP == 1)break;
            }
        }
        if(STOP == 1)break;
    }
   print_board(game_board);
}

int main(){
    char game_board[15][15];
    char task[10];
    int Valtask;
   
    fgets(task,sizeof(task),stdin);
    Valtask = strtol(task,NULL,10);

    for(int i=0;i<15;i++){
        for(int j=0;j<15;j++){
            game_board[i][j]= '.'; 
        }
    }

    switch(Valtask){
        case 0:
            print_board(game_board);
            break;
        case 1:
            task1(game_board);
            break;
        case 2:
            task2();
            break;
        case 3:
            task3();
            break;
        case 4:
            task4(game_board);
            break;
        case 5:
            task5(game_board);
            break;
    }
  
    return 0;
}