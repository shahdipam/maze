#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <windows.h>
#include<dos.h>
#include<string.h>

int MAXSIZE;
struct cell
{
    int x,y;
    char display;
}maze[50][50];
struct cell current;


void generateMaze(int,int,int,int,char);
void display(int m,int n,char p);
void ClearScreen();
void updateScreen(char);
static int moves;
void delay(int ms)
{
    clock_t goal=ms+clock();
    while(goal>clock());
}
 
int main()
{

  
    int choice;
    char name[20];
    printf("Enter name\n");
    scanf("%s",name);
    
    
    printf("1.Easy\n2.Medium\n3.Hard\n");
      int n;
      scanf("%d",&n);
    
    switch(n)
    {
        case 1: MAXSIZE=15;break;
        case 2: MAXSIZE=25;break;
        case 3: MAXSIZE=35;break;
      

        default: printf("Invalid option\n");
                    exit(0);

    }
 char q;
 int a=169;
 current.display=name[0];

    for(int i=0;i<MAXSIZE;i++)
                {
                     maze[i][0].display='1'; 
                     maze[i][0].x=i;
                     maze[i][0].y=0;   //left wall
                     maze[i][MAXSIZE-1].display='1';
                     maze[i][MAXSIZE-1].x=i;
                     maze[i][MAXSIZE-1].y=MAXSIZE-1;    //right wall
                 }
                 for(int i=0;i<MAXSIZE;i++)
                {
                       maze[0][i].display='1';  
                       maze[0][i].x=0;
                       maze[0][i].y=i;   //top wall
                       maze[MAXSIZE-1][i].display='1';
                       maze[MAXSIZE-1][i].x=MAXSIZE-1;
                       maze[MAXSIZE-1][i].y=i;     //bottom wall
                 }
                 for(int i=1;i<=(MAXSIZE-2);i++)
                {
                      for(int j=1;j<=(MAXSIZE-2);j++)
                         {
                               maze[i][j].x=i;
                               maze[i][j].y=j;
                              maze[i][j].display='.';
                        }
                 }
     generateMaze(0,MAXSIZE-1,0,MAXSIZE-1,name[0]); 
       int w=clock();
     current.x=0;
     current.y=0;
    maze[0][0].display='.';
    maze[1][0].display='.';
    maze[1][1].display='.';
    maze[MAXSIZE-1][MAXSIZE-1].display='.';
    maze[MAXSIZE-2][MAXSIZE-1].display='.';
    maze[MAXSIZE-2][MAXSIZE-2].display='.';
    
    ClearScreen();
    for(;;)
    {
        ClearScreen();
       while(1)
       { 
        display(MAXSIZE,MAXSIZE,name[0]);
    
        q=getchar();
        if(q=='a'||q=='s'||q=='d'||q=='w')
            break;
        }
        
        updateScreen(q);
        ClearScreen();
      
        if(current.x==MAXSIZE-1 && current.y==MAXSIZE-1)
            break;
     }   
      int e=clock()-w;
     printf("Total moves:%d\n",moves );
     FILE *fp=fopen("highscore.txt","a");
     fprintf(fp,"%d\t\t%s\t\t%d\t\t%d\n",n,name,moves,e/1000);
     fclose(fp);
     printf("\nYOU WON !!!!!\a\n");
    
     printf("You took %d seconds\n",(e/1000) );
    return 0;
}
 
void generateMaze(int a,int m,int b,int n,char p)
{
    if((m-a)<=3 || (n-b)<=3)
    {
        return;
    }
 
    else
    {
      
        srand(time(0));
       
        int randomRow,randomColumn,count=0,p=0;
        
                 randomRow=rand()%(m-a-3) + 2+a;
       
        //printf("r\t%d\n",randomRow);
          
        randomColumn=rand()%(n-b-3)+2+b;
        
       // printf("c\t%d\n",randomColumn);
            
        for(int i=b+1;i<=n-1;i++)           //Printing row
        {
            if(maze[randomRow][i+1].display==' ' )
            {
                maze[randomRow][i].display='.';
                continue;
            }
            else if(maze[randomRow][i-1].display==' ')
            {
                maze[randomRow][i].display='.';
                continue;
            }
            else{
                 if((maze[randomRow][i-1].display=='.' || maze[randomRow][i+1].display=='.'))//||(i==n-1))
                        maze[randomRow][i].display='1';  //to display 1 for the wall
                 else if(i==n-1 && maze[randomRow][i+1].display=='1' && maze[randomRow][i-1].display=='1')
                        maze[randomRow][i].display='1';
                }
        }
        
        for(int j=a+1;j<=m-1;j++)               //to print columns
        {
            if(maze[j+1][randomColumn].display==' ')
            {
                maze[j][randomColumn].display='.';
                continue;
            }
            else if(maze[j-1][randomColumn].display==' ')
            {
                maze[j][randomColumn].display='.';
                continue;
            }
            else{
                 if((maze[j-1][randomColumn].display=='.' || maze[j+1][randomColumn].display=='.'))//||(j==m-1) )
                    maze[j][randomColumn].display='1';  //to display 1 for the wall
                else if(j==m-1 && maze[j+1][randomColumn].display=='1' && maze[j-1][randomColumn].display=='1')
                    maze[j][randomColumn].display='1';
                }
        }
        int count1=rand()%4+1;
        //printf("%d",count1);   //to decide which one wall wont have any hole
        int hole;
        switch(count1)
        {
            case 1: hole=(rand()%(randomRow-1-a))+1+a;
                    //printf("h1 top\t%d\n",hole);
                    if(maze[hole][randomColumn].display=='1')
                        maze[hole][randomColumn].display=' ';   //Top line will have a hole
                    
                    hole=rand()%(m-randomRow-1)+1+randomRow;
                   // printf("h2 bottom\t%d\n",hole);   
                    if(maze[hole][randomColumn].display=='1')                
                        maze[hole][randomColumn].display=' ';    //Bottom line will have a hole
                    
                    hole=rand()%(n-randomColumn-1)+1+randomColumn;
                   // printf("h3 right\t%d\n",hole); 
                    if(maze[randomRow][hole].display=='1')        
                        maze[randomRow][hole].display=' ';      //Right line will have a hole
                    
                    break;
            case 2: hole=rand()%(randomColumn-1-b)+1+b;  //Left line will have a hole
                   // printf("h1 left\t%d\n",hole);   
                    if(maze[randomRow][hole].display=='1')       
                        maze[randomRow][hole].display=' ';
                    
                    hole=rand()%(randomRow-1-a)+1+a;
                  //  printf("h2 top\t%d\n",hole);
                    if(maze[hole][randomColumn].display=='1')
                        maze[hole][randomColumn].display=' ';   //Top
                    
                    hole=rand()%(n-randomColumn-1)+1+randomColumn;
                   // printf("h3 right\t%d\n",hole);
                    if(maze[randomRow][hole].display=='1')
                        maze[randomRow][hole].display=' ';      //Right line will have a hole
                    
                    break;
             case 3:hole=rand()%(randomColumn-1-b)+1+b;  //Left line will have a hole
                   // printf("h1 left\t%d\n",hole);   
                    if(maze[randomRow][hole].display=='1')      
                        maze[randomRow][hole].display=' ';
                    
                    hole=rand()%(m-randomRow-1)+1+randomRow;
                   // printf("h2 bottom\t%d\n",hole);
                    if(maze[hole][randomColumn].display=='1')
                        maze[hole][randomColumn].display=' ';    //Bottom line will have a hole
                    
                    hole=rand()%(randomRow-1-a)+1+a;
                   // printf("h3 top\t%d\n",hole); 
                    if(maze[hole][randomColumn].display=='1')        
                        maze[hole][randomColumn].display=' ';   //Top
                    
                    break;
             case 4:hole=rand()%(randomColumn-1-b)+1+b;  //Left line will have a hole
                   // printf("h1 left\t%d\n",hole);
                    if(maze[randomRow][hole].display=='1')        
                        maze[randomRow][hole].display=' ';
                    
                    hole=rand()%(m-randomRow-1)+1+randomRow;
                   // printf("h2 bottom\t%d\n",hole);
                    if(maze[hole][randomColumn].display=='1')                  
                        maze[hole][randomColumn].display=' ';    //Bottom line will have a hole
                    
                    hole=rand()%(n-randomColumn-1)+1+randomColumn;
                   // printf("h3 right\t%d\n",hole); 
                    if(maze[randomRow][hole].display=='1')        
                        maze[randomRow][hole].display=' ';      //Right line will have a hole
                    
                    break;
        }
        
        
        delay(20);
        generateMaze(a,randomRow,b,randomColumn,p);
        generateMaze(a,randomRow,randomColumn,n,p);
        generateMaze(randomRow,m,b,randomColumn,p);
        generateMaze(randomRow,m,randomColumn,n,p);

    } 
}
 
void display(int m,int n,char p)
{
   // printf("Displaying!\n");
    int a=219;
    
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            
         if(i==current.x && j==current.y)
            {
                printf("%c ",p);
                continue;
            }
            else if(maze[i][j].display=='1')
                printf("%c%c",a,a);
            else if(maze[i][j].display==' ' || maze[i][j].display=='.')
            {
                printf("  ");
                continue;
            }
            else
           {         
            printf("%c ",maze[i][j].display);
            continue;
           }

        }
      
        fflush(stdout);
        printf("\n");
    }

    printf("\n\n\n");
}




void ClearScreen()
  {
  HANDLE                     hStdOut;
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  DWORD                      count;
  DWORD                      cellCount;
  COORD                      homeCoords = { 0, 0 };

  hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
  if (hStdOut == INVALID_HANDLE_VALUE) return;

  /* Get the number of cells in the current buffer */
  if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
  cellCount = csbi.dwSize.X *csbi.dwSize.Y;

  /* Fill the entire buffer with spaces */
  if (!FillConsoleOutputCharacter(
    hStdOut,
    (TCHAR) ' ',
    cellCount,
    homeCoords,
    &count
    )) return;

  /* Fill the entire buffer with the current colors and attributes */
  if (!FillConsoleOutputAttribute(
    hStdOut,
    csbi.wAttributes,
    cellCount,
    homeCoords,
    &count
    )) return;

  /* Move the cursor home */
  SetConsoleCursorPosition( hStdOut, homeCoords );
  }


  void updateScreen(char a)
  {
   // printf("UPDATING!\n");
    
    fflush(stdout);

    if(a=='a')
    {
        if(current.y-1<0)
            return;
        else if(maze[current.x][current.y-1].display=='1')
            return;
        else
           moves++; current.y=current.y-1;
    }
    else if(a=='w')
    {
        if(current.x-1<0)
            return;
        else if(maze[current.x-1][current.y].display=='1')
            return;
        else
            moves++;current.x=current.x-1;
    }
    else if(a=='d')
    {
        if(current.y+1>MAXSIZE-1)
            return;
        else if(maze[current.x][current.y+1].display=='1')
            return;
        else
            moves++;current.y=current.y+1;
    }
    else if(a=='s')
    {
        if(current.x+1>MAXSIZE-1)
            return;
        else if(maze[current.x+1][current.y].display=='1')
            return;
        else
           moves++; current.x=current.x+1;
    }
  }