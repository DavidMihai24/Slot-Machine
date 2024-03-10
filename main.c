#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

/*

A 7 K 7 7
7 A A A T
A 7 K Q Q

- 7 K 7 7
7 - - - T
A 7 K Q Q

A 7 K 7 7
7 - - - T
- 7 K Q Q

*/

//dreapta sus i = i - 1, j = j + 1
//dreapta     i = i    , j = j + 1
//dreapta jos i = i + 1, j = j + 1

const char simboluri[]    = {'A','7','K','Q','C','0','3'};
const float multipliers[] = { 2 , 10, 3 , 4 , 6 ,1.5, 5 };
const int lenSimboluri = 7;

char** pacanea;
int linii, coloane = 5;

void afisarePacanea(){
    for(int i = 0; i < linii; i++){
        for(int j = 0; j < coloane; j++){
            printf("%c ",pacanea[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/*

0,0 -> 1,1 -> 1,2 -> 1,3

- - A 7 7
7 K K K T
A 7 K Q Q
*/

void cautareCombinatie(int i, int j, int nr, int* total){
    nr++;
    if(j + 1 == coloane){ //conditie de oprire (suntem pe ultimul caracter al unei combinatii)
        if(nr < 3)
            nr = 0;
        else{
            char c = pacanea[i][j];
            pacanea[i][j] = '-';
            afisarePacanea();
            pacanea[i][j] = c;
        }
        (*total) += nr;
        return;
    }
    bool terminatCombinatie = true;
    if(i - 1 >= 0 && pacanea[i][j] == pacanea[i-1][j+1]){ //sus
        char c = pacanea[i][j];
        pacanea[i][j] = '-';
        cautareCombinatie(i - 1, j + 1, nr, total);
        pacanea[i][j] = c;
        terminatCombinatie = false;
    }
    if(pacanea[i][j] == pacanea[i][j+1]){ //dreapta
        char c = pacanea[i][j];
        pacanea[i][j] = '-';
        cautareCombinatie(i, j + 1, nr, total);
        pacanea[i][j] = c;
        terminatCombinatie = false;
    }
    if(i + 1 < linii && pacanea[i][j] == pacanea[i+1][j+1]){ //jos
        char c = pacanea[i][j];
        pacanea[i][j] = '-';
        cautareCombinatie(i + 1, j + 1, nr, total);
        pacanea[i][j] = c;
        terminatCombinatie = false;
    }
    if(terminatCombinatie == true) { //conditie de oprire (suntem pe ultimul caracter al unei combinatii)
        if(nr < 3)
            nr = 0;
        else{
            char c = pacanea[i][j];
            pacanea[i][j] = '-';
            afisarePacanea();
            pacanea[i][j] = c;
        }
        (*total) += nr;
        return;
    }
}

void joc(float* balanta, float miza){
    if(miza > *balanta){
        printf("Nu ai destui bani, nu joci responsabil!\n");
        return;
    }
    *balanta -= miza;
    int i,j;
    for(i = 0; i < linii; i++){
        for(j = 0; j < coloane; j++){
            pacanea[i][j] = simboluri[rand() % 7];
        }
    }
    afisarePacanea();
    float castig = 0;
    int total;

    total = 0;
    cautareCombinatie(0,0,0,&total);
    for(i = 0; i < lenSimboluri; i++){
        if(simboluri[i] == pacanea[0][0])
            break;
    }
    castig = castig + total * multipliers[i] * miza;

    total = 0;
    cautareCombinatie(1,0,0,&total);
    for(i = 0; i < lenSimboluri; i++){
        if(simboluri[i] == pacanea[1][0])
            break;
    }
    castig = castig + total * multipliers[i] * miza;

    total = 0;
    cautareCombinatie(2,0,0,&total);
    for(i = 0; i < lenSimboluri; i++){
        if(simboluri[i] == pacanea[2][0])
            break;
    }
    castig = castig + total * multipliers[i] * miza;
    *balanta += castig;

    printf("Ai castigat %f! Joaca responsabil\n",castig); //afisam castigul pentru fiecare joc

}

int main()
{
    printf("Multipliers:\n");
    for(int i = 0; i < lenSimboluri; i++){
        printf("%c -> %f x\n",simboluri[i],multipliers[i]);
    }

    srand(time(NULL));

    char c;

    float balanta, miza;

    printf("De cate linii sa fie pacaneaua?\n");
    scanf("%d",&linii);
    scanf("%c",&c); //citim enter
    pacanea = (char**)malloc(linii * sizeof(char*));
    for (int i = 0; i < linii; i++)
        pacanea[i] = (char*)malloc(coloane * sizeof(char));

    printf("Introdu balanta\n");
    scanf("%f",&balanta);
    scanf("%c",&c); //citim enter

    bool running = true;

    printf("Seteaza miza si incepe sa joci\n");
    scanf("%f",&miza);
    scanf("%c",&c); //citim enter

    while(running){

        printf("Balanta: %f\nMiza curenta: %f\n",balanta,miza); //facem balanta si miza sa se vada la fiecare rotire

        joc(&balanta,miza);

        printf("Noua balanta: %f\n",balanta); //afisam si noua balanta, dupa joc

        printf("Apasa q pentru a iesi\n");
        printf("Apasa s pentru a schimba miza\n");
        printf("Apasa enter pentru a continua cu aceeasi miza\n");

        scanf("%c",&c);

        if(c == 'q'){
            running = false;
            scanf("%c",&c); //citim enter sa nu ramana necitit
            printf("Ma bucur ca te-ai distrat. Te mai asteptam. Joaca responsabil!\n");
        }
        else if(c == 's'){
            scanf("%c",&c); //citim enter
            printf("Introdu miza\n");
            scanf("%f",&miza); ///
            scanf("%c",&c); //citim enter
        }
        else if(c == '\n')
            printf("Continuam. Joaca responsabil!\n");

        if(balanta == 0){
            running = false;
            printf("Nu ai jucat responsabil, dar noi tot ne-am facut banii. Va mai asteptam. GGEZ\n");
        }
    }

    return 0;
}