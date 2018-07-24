#include<iostream>
#include<ctime>
#include<unistd.h>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<stdio.h>
using namespace std;

  int grid[4][4],back[4][4],timer=250000;
  char control;
  bool _move=false,QuickMode=false,blocked=false,win=false;

  int random_val(int);
  void GridBackup();
  void Input();
  void GridMovement();
  void TileSpawn();
  void DeathScreen();
  void Instructions();
  void CheckWin();
  void WinScreen();
  void GridDraw();
  void GridSpawn();
  void DeathCheck();

int main()
{
    srand(time(NULL));
    GridSpawn();
    return 0;
}

int random_val(int x)
{

    int index;
    index=rand()%x;
    return index;
}

void GridSpawn()
{
  int i,j,m,n;
    for(i=0;i<4;i++)
        for(j=0;j<4;j++)
            grid[i][j]=0;

    i=random_val(4);
    j=random_val(4);

        grid[i][j]=2;
redo2:    m=random_val(4);
    n=random_val(4);
    if (m==i&&n==j)
        if (m==n)
            goto redo2;
        else
            grid[n][m]=2;
    else
        grid[m][n]=2;
    GridBackup();
    GridDraw();
    Input();
}

void GridDraw()
{
    system("clear");

        cout<<"\n  ---2048--- \t\t\t \n\n\t\n";

                for(int i=0;i<4;i++)
                {
                cout<<"       |";

                    for(int j=0;j<4;j++)
                    {
                        if(grid[i][j])
                            printf("%5d|",grid[i][j]);
                        else
                            printf("%5c|",' ');
                    }

                cout<<endl;
                }
        cout << "\n\n Controls: \t\t\t\t R - Restart\t U - Undo\n\tW\t\t\t\t H - Help\t Q - Quit\n    A   S   D\n\t\t\tNote: Keep Caps Lock off. \n\nTIP: Use m to toggle Quick Mode.\n\t\t\t\t     ";

}

void GridBackup()
{
        for(int i=0;i<4;i++)
            for(int j=0;j<4;j++)
            back[i][j]=grid[i][j];
}

void undo()
{
    for(int i=0;i<4;i++)
            for(int j=0;j<4;j++)
            grid[i][j]=back[i][j];
    GridDraw();
    Input();
}

void Input()
{
  CheckWin();
  system("stty raw");
  cin>>control;
  system("stty cooked");
    if (control=='u')
        undo();
    else if (control=='q')
    {
        system("clear");
        exit(0);
    }
    else if (control=='h')
        Instructions();
    else if (control=='r')
        GridSpawn();
    else if (control=='m')
    {
        if (QuickMode)
        {
            QuickMode=false;
            timer=250000;
            GridDraw();
            Input();
        }
        else
        {
            QuickMode=true;
            timer=0;
            GridDraw();
            Input();
        }
    }
    else
        GridMovement();

}

void GridMovement()
{
    GridBackup();
    _move=false;
    switch (control)
    {
        case 'w':
            for(int i=0;i<4;i++)
                for(int j=0;j<4;j++)
                    if(!grid[j][i])
                        for(int k=j+1;k<4;k++)
                            if(grid[k][i])
                            {
                                grid[j][i]=grid[k][i];
                                grid[k][i]=0;
                                _move=true;
                                break;
                            }
            for(int i=0;i<4;i++)
                for(int j=0;j<3;j++)
                    if(grid[j][i]&&grid[j][i]==grid[j+1][i])
                    {
                        grid[j][i]+=grid[j+1][i];
                        grid[j+1][i]=0;
                        _move=true;
                    }

            break;
        case 's':
            for(int i=0;i<4;i++)
                for(int j=3;j>=0;j--)
                    if(!grid[j][i])
                        for(int k=j-1;k>=0;k--)
                            if(grid[k][i])
                            {
                                grid[j][i]=grid[k][i];
                                grid[k][i]=0;
                                _move=true;
                                break;
                            }
            for(int i=0;i<4;i++)
                for(int j=3;j>0;j--)
                    if(grid[j][i]&&grid[j][i]==grid[j-1][i])
                    {
                        grid[j][i]+=grid[j-1][i];
                        grid[j-1][i]=0;
                        _move=true;
                    }
            break;
        case 'a':
            for(int i=0;i<4;i++)
                for(int j=0;j<4;j++)
                    if(!grid[i][j])
                        for(int k=j+1;k<4;k++)
                            if(grid[i][k])
                            {
                                grid[i][j]=grid[i][k];
                                grid[i][k]=0;
                                _move=true;
                                break;
                            }
            for(int i=0;i<4;i++)
                for(int j=0;j<3;j++)
                    if(grid[i][j]&&grid[i][j]==grid[i][j+1])
                    {
                        grid[i][j]+=grid[i][j+1];
                        grid[i][j+1]=0;
                        _move=true;
                    }
            break;
        case 'd':
            for(int i=0;i<4;i++)
                for(int j=3;j>=0;j--)
                if(!grid[i][j])
                    for(int k=j-1;k>=0;k--)
                        if(grid[i][k])
                        {
                            grid[i][j]=grid[i][k];
                            grid[i][k]=0;
                            _move=true;
                            break;
                        }
            for(int i=0;i<4;i++)
                for(int j=3;j>0;j--)
                    if(grid[i][j]&&grid[i][j]==grid[i][j-1])
                    {
                        grid[i][j]+=grid[i][j-1];
                        grid[i][j-1]=0;
                        _move=true;
                    }
            break;
    }
    GridDraw();
    DeathCheck();
    if (_move)
    {
        CheckWin();
        usleep(timer);
        TileSpawn();
        GridDraw();
        Input();

    }
    else
    Input();
}

void CheckWin()
{
    if (!win)
    {
        for (int i=0;i<4;i++)
        for (int j=0;j<4;j++)
        {
            if (grid[i][j]==2048)
            {
                win=true;
                WinScreen();
            }
            else return;
        }
    }
    else return;
}

void TileSpawn()
{

   restart:
        int i=0,j=0,m;
        int val[5]={2,2,2,2,4};
        i=random_val(4);
        j=random_val(4);
        if (!grid[i][j])
        {
            m=rand()%5;
            grid[i][j]=val[m];
            GridDraw();
            Input();
        }
        else
            goto restart;

}

void Instructions()
{
system("clear");
cout << "\t\t\t     -----Help Page-----\n";
cout << "2048 is perhaps one of the most addictive mathematical puzzle games. \nFor starters, it is played on a 4 × 4 game board which begins with an initial\nconfiguration of two tiles, of value 2 each, placed at arbitrary locations\non the grid.\n\n\t\t\tHow to play:\n Use W for up, A for left, D for right and S for down to move the tiles.\nEach move shifts all tiles on the grid in the direction chosen. If two\nadjacent tiles have the same value, they combine, and the single resulting\ntile after the combination will be the sum. Following the player’s move,\na tile of value 2 or 4 will be generated at a random position on the board.\nThe goal of the game is to combine equally-valued tiles to reach the 2048\ntile without getting stuck.\n\nYou can use U to undo to your last move, R to restart the game, Q to quit\n and H to come to this page anytime.\nNote: Methods to accept inputs in this game do not function well with\nCaptial Characters. Please keep Caps Lock OFF. :) \nUse M to have the computer spawn tiles faster\n\nPress any key to continue...\n\n\t\t\t\t\tDeveloped by AgentFabulous";
    system("stty raw");
    cin.get();
        system("stty cooked");
    GridDraw();
    Input();
}

void WinScreen()
{
    system("clear");
    cout<<"\n\n\n\n\n\n\t\t\t\t YOU WON!!\n\n";
    sleep(3);
    cout << "\n\t\t\tGAME OVER\n\n\n\nPress c to continue playing or any other key to continue...\n";
    system("stty raw");
    cin.get(control);
        system("stty cooked");
    if (control=='c')
    {
        GridDraw();
        Input();
    }
    else
    {
        system("clear");
        exit(0);
    }
}

void DeathScreen()
{
    cout << "\n\n\n\n\t\t\tGAME OVER\n\n\n\nPress r to restart or any other key to quit...\n";
    system("stty raw");
    cin.get(control);
        system("stty cooked");
    switch(control)
    {
        case 'r': GridSpawn();
            break;
        default: system("clear");
            exit (0);
            break;
    }
}

void DeathCheck()
{
    for (int i=0;i<4;i++)
        for (int j=0;j<4;j++)
        {
            if (grid[i][j]==0)
            {
                blocked=false;
                return;
            }
            else
            {
                blocked=true;
                continue;
            }
        }
    if (blocked)
    {
        if ((grid[0][0]==grid[1][0])||(grid[0][0]==grid[0][1])||(grid[0][1]==grid[1][1])||(grid[0][1]==grid[0][2])||(grid[0][2]==grid[1][2])||(grid[0][2]==grid[0][3])||(grid[0][3]==grid[1][3])||(grid[1][0]==grid[1][1])||(grid[1][0]==grid[2][0])||(grid[1][1]==grid[1][2])||(grid[1][1]==grid[2][1])||(grid[1][2]==grid[1][3])||(grid[1][2]==grid[2][2])||(grid[1][3]==grid[2][3])||(grid[2][0]==grid[2][1])||(grid[2][0]==grid[3][0])||(grid[2][1]==grid[2][2])||(grid[2][1]==grid[3][1])||(grid[2][2]==grid[2][3])||(grid[2][2]==grid[3][2])||(grid[2][3]==grid[3][3])||(grid[3][0]==grid[3][1])||(grid[3][1]==grid[3][2])||(grid[3][2]==grid[3][3]))
        {
            GridDraw();
            Input();
        }
        else DeathScreen();
    }
}
