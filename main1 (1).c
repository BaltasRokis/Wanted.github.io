#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

FILE *html;
FILE *css;
void drawTableMain();
void drawTableSecondary(char table[][20], int columnSize, int num);
void logic(char table[][20], int csize);
int getUserInput(); ///0=ENTER; 1=UP; 2=DOWN; 3=LEFT; 4=RIGHT
void popup();
void getCode();
void openTable();

int choice[9]={0, 0, 0, 0, 0, 0, 0, 0, 0};
int arraySize[9]={8, 6, 5, 5, 7, 4, 7, 7, 6};
int cursorPlacement[9]={0, 0, 0, 0, 0, 0, 0, 0, 0};
int drawingTable = 0; ///0-9, 0 - main table; 1-9 - secondary tables;
int cursor = 0; ///current location

///Tables with names:
char YN[2][5]={{"YES"}, {"NO"}};
char mainTable[8][20] = {{"Eyes"},{"Eyebrows"}, {"Ears"}, {"Lips"}, {"Noses"}, {"Face shapes"}, {"Hair styles"}, {"Extras"}};

char eyesTable[6][20] = {{"Elongated"}, {"Round"}, {"Dripping"}, {"Psycho"}, {"Sun"}, {"Full makeup"}};
char browsTable[5][20] = {{"Average"}, {"Thick"}, {"Unibrow"}, {"Round thin"}, {"Short"}};
char earsTable[5][20] = {{"Small"}, {"Long"}, {"Elf"}, {"Fishy"}, {"Big earring"}};
char lipsTable[7][20] = {{"Average"}, {"Full"}, {"Pouty"}, {"Thin"}, {"Creepy"}, {"Open"}, {"Line"}};
char noseTable[4][20] = {{"Round"}, {"Penis"}, {"Triangle"}, {"Pig"}};
char faceTable[7][20] = {{"Round"}, {"Rectangular"}, {"Square"}, {"Long round"}, {"Triangle"}, {"Anime"}, {"Peanut"}};
char hairTable[7][20] = {{"Curly"}, {"Space buns"}, {"Locks"}, {"Short"}, {"Fluffy"}, {"Old man"}, {"Bush"}};
char extrasTable[6][20]= {{"Septum"}, {"Freckles"}, {"Bridge"}, {"Cat whiskers"}, {"Tattoo"}, {"Nothing"}};

void drawTableMain()
{
    system("cls");
    printf("=============\n");
    for(int i=0; i<8; i++)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

        if(cursorPlacement[0]==i)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
            printf("%s\n", mainTable[i]);
        }
        else
        {
            printf("%s\n", mainTable[i]);
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    }
    printf("=============\n\n");
    printf("up\t- ARROW_UP\ndown\t- ARROW_DOWN\nselect\t- ENTER or ARROW_RIGHT\nend\t- ARROW_LEFT");
}
void drawTableSecondary(char table[][20], int columnSize, int num)
{
    system("cls");
    printf("=============\n");
    printf("%s:\n", mainTable[cursorPlacement[0]]);

    for(int i=0; i<columnSize; i++)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

        if(choice[num]==i)
        {
            printf("[x]");
        }
        else
        {
            printf("[ ]");
        }

        if(cursorPlacement[num]==i)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
        }

        printf("%s\n", table[i]);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    }

    printf("=============\n\n");
    printf("up\t- ARROW_UP\ndown\t- ARROW_DOWN\nselect\t- ENTER or ARROW_RIGHT\nback\t- ARROW_LEFT");
}

void logic(char table[][20], int csize)
{
    int num = cursorPlacement[0]+1;
    int exit=1;
    while(exit)
    {
        drawTableSecondary(table, csize, num);
        switch(getUserInput())
        {
            case 0:
                choice[num]=cursorPlacement[num];
                break;
            case 1:
                if(cursorPlacement[num]>0)
                {
                    cursorPlacement[num]--;
                }
                break;
            case 2:
                if(cursorPlacement[num]<arraySize[num]-1)
                {
                    cursorPlacement[num]++;
                }
                break;
            case 3:
                exit=0;
                break;
            case 4:
                choice[num]=cursorPlacement[num];
                break;
            break;
        }
    }
}
int getUserInput() ///0=ENTER; 1=UP; 2=DOWN; 3=LEFT; 4=RIGHT
{
    char ch, ch1=0xE0;
    while(1)
    {
        ch=getch();
        if (ch=='\r')      ///JEIGU PASPAUSTA ENTER
        {
            return 0;
        }

        else if (ch==ch1) ///JEIGU PASPAUSTA RODYKLE
        {
            ch=getch();
            switch(ch)
            {
                case 'H':
                    return 1;
                    break;
                case 'P':
                    return 2;
                    break;
                case 'M':
                    return 4;
                    break;
                case 'K':
                    return 3;
                    break;
                default:
                    break;
            }
        }
    }
}

void popup()
{
    int pcursor=0;
    int exit = 1;
    while(exit)
    {
        system("cls");
        printf("DO YOU WANT TO FINISH THE BUILDING PROCESS?\n");
        for(int i=0; i<2; i++)
        {
            if(pcursor==i)
            {
                printf(">");
            }
            else
            {
                printf(" ");
            }

            printf("%s\n", YN[i]);
        }

        switch(getUserInput())
        {
            case 0:
                if(pcursor==0)
                {
                    getCode();
                }
                else
                {
                    exit = 0;
                }
                break;
            case 1:
                if(pcursor>0)
                    {
                        pcursor--;
                    }
                break;
            case 2:
                if(pcursor<1)
                {
                    pcursor++;
                }
                break;
        }
    }
}

void getCode()
{
    html = fopen("index.html", "w");
    css = fopen("index.css", "w");

    fprintf(html, "<!DOCTYPE html>\n <html lang=\"en\" dir=\"ltr\">\n  <head>\n    <meta charset=\"utf-8\">\n    <title>Wanted</title>\n    <link rel=\"stylesheet\" href=\"index.css\">\n  </head>\n  \n<body>\n   <div class=\"background-image\">\n\n    <img src=\"backgrounds/Poster_done.png\" class=\"poster-image\">\n\n    <img src=\"Veidas/%d.png\" class=\"traits-image\" >\n    <img src=\"Ausys/%d.png\" class=\"traits-image\">\n    <img src=\"Akys/%d.png\" class=\"traits-image\">\n    <img src=\"Antakiai/%d.png\" class=\"traits-image\">\n    <img src=\"Nosys/%d.png\" class=\"traits-image\">\n    <img src=\"Lupos/%d.png\" class=\"traits-image\">\n    <img src=\"Plaukai/%d.1.png\" class=\"traits-image\">\n    <img src=\"Plaukai/%d.2.png\" class=\"backhair-image\">\n    <img src=\"Extras/%d.png\" class=\"traits-image\">\n\n   </div>\n</body>", choice[6], choice[3], choice[1], choice[2], choice[5], choice[4], choice[7], choice[7], choice[8]);
    fprintf(css, "*{\n  margin: 0;\n  padding: 0;\n}\nhtml{\n    scroll-behavior: smooth;\n}\n.background-image {\n  background-image: url(\"backgrounds/lentos.png\");\n  background-size: cover;\n  background-repeat: no-repeat;\n  z-index: 0;\n  height: 100vh;\n  margin: 0;\n  padding: 0;\n  position: relative;\n}\n.poster-image{\n  position: absolute;\n  top:50%%;\n  left: 50%%;\n  transform: translate(-50%%, -50%%);\n  z-index: 1;\n  height:98%%;\n}\n.backhair-image{\n  z-index: 2;\n  position: absolute;\n  top: 50%%;\n  left: 50%%;\n  transform: translate(-50%%, -46%%);\n  height:60%%;\n}\n\n.traits-image{\n  z-index: 3;\n  position: absolute;\n  top: 50%%;\n  left: 50%%;\n  transform: translate(-50%%, -46%%);\n  height:60%%;\n}");
    
    printf("HTML and CSS created, check the folder\n");
    exit(1);
}

void openTable()
{
    switch(cursorPlacement[0])
    {
        case 0:
            logic(eyesTable, 6);
            break;
        case 1:
            logic(browsTable, 5);
            break;
        case 2:
            logic(earsTable, 5);
            break;
        case 3:
            logic(lipsTable, 7);
            break;
        case 4:
            logic(noseTable, 4);
            break;
        case 5:
            logic(faceTable, 7);
            break;
        case 6:
            logic(hairTable, 7);
            break;
        case 7:
            logic(extrasTable, 6);
        break;
    }
}

int main()
{
    while(1)
    {
        drawTableMain();
        switch(getUserInput())
        {
            case 0:                                             ///KEISTI GREITAI PADARYT KAD SWITCH SITAS BUTU VOIDE AAAAAAAA
                openTable();
                break;                              ///KEISTI GREITAI PADARYT KAD SWITCH SITAS BUTU VOIDE AAAAAAAA

            case 1:
                if(cursorPlacement[0]>0)
                {
                    cursorPlacement[0]--;
                }
                break;
            case 2:
                if(cursorPlacement[0]<arraySize[0]-1)
                {
                    cursorPlacement[0]++;
                }
                break;
            case 3:
                popup();
                break;
            case 4:                                 ///KEISTI GREITAI PADARYT KAD SWITCH SITAS BUTU VOIDE AAAAAAAA
                openTable();
                break;
            default:
                printf("\n\nDefault error\n\n");
                break;
        }
    }

    return 0;
}
