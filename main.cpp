#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <iomanip>

#define size 4

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

struct position	//	structure of position, used for specifying the cursor position
{
	int x,y;
};

void gotoxy(position pos)
{	CursorPosition.X = pos.x; // Locates column
	CursorPosition.Y = pos.y; // Locates Row
	SetConsoleCursorPosition(console,CursorPosition); // Sets position for next thing to be printed
}

int get_score(int grid[size][size])
{
    int max=grid[0][0];
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            if(grid[i][j]>max)
                max=grid[i][j];
        }
    }
    return max;
}

void initial_seed(int grid[size][size])
{
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
            grid[i][j]=0;
    }
}

int randRange(int low, int high)
{
    high++;
    return (int)(rand() / (RAND_MAX / (double)(high - low))) + low;
}

bool is_filled(int grid[size][size])
{
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            if(grid[i][j]==0)
                return false;
        }
    }
    return true;
}

int new_seed(int grid[size][size])
{
    while(1)
    {
        int seed[10]={2,2,2,2,2,2,2,2,2,4};
        int rand_seed=randRange(0, 9);

        int rand_pos_i=randRange(0, 4);
        int rand_pos_j=randRange(0, 4);

        if(grid[rand_pos_i][rand_pos_j]==0)
        {
            grid[rand_pos_i][rand_pos_j]=seed[rand_seed];
            return 1;   //  success
        }

        else if(is_filled(grid))
            return 0;
    }

    return 0;   //  failure
}

void move_left(int grid[size][size])
{
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            if(grid[i][j]==grid[i][j+1])
            {
                grid[i][j]=(grid[i][j]*2);

                int k;
                for(k=j+1; k<(size-1); k++)
                    grid[i][k]=grid[i][k+1];
                grid[i][k]=0;
            }
        }
    }
}

void club_left(int grid[size][size])
{
    for(int i=0; i<size; i++)
    {
        for(int j=0, l=0; j<size, l<size; j++, l++)
        {
            if(grid[i][j]==0)
            {
                int k;
                for(k=j; k<(size-1); k++)
                    grid[i][k]=grid[i][k+1];
                grid[i][k]=0;
                j=(-1);
            }
        }
    }
}

void move_top(int grid[size][size])
{
    for(int j=0; j<size; j++)
    {
        for(int i=0; i<size; i++)
        {
            if(grid[i][j]==grid[i+1][j])
            {
                grid[i][j]=(grid[i][j]*2);

                int k;
                for(k=i+1; k<(size-1); k++)
                    grid[k][j]=grid[k+1][j];
                grid[k][j]=0;
            }
        }
    }
}

void club_top(int grid[size][size])
{
    for(int j=0; j<size; j++)
    {
        for(int i=0, l=0; i<size, l<size; i++, l++)
        {
            if(grid[i][j]==0)
            {
                int k;
                for(k=i; k<(size-1); k++)
                    grid[k][j]=grid[k+1][j];
                grid[k][j]=0;
                i=(-1);
            }
        }
    }
}

void move_bottom(int grid[size][size])
{
    for(int j=(size-1); j>=0; j--)
    {
        for(int i=(size-1); i>=0; i--)
        {
            if(grid[i][j]==grid[i-1][j])
            {
                grid[i][j]=(grid[i][j]*2);

                int k;
                for(k=i-1; k>0; k--)
                    grid[k][j]=grid[k-1][j];
                grid[k][j]=0;
            }
        }
    }
}

void club_bottom(int grid[size][size])
{
    for(int j=(size-1); j>=0; j--)
    {
        for(int i=(size-1), l=0; i>=0, l<size; i--, l++)
        {
            if(grid[i][j]==0)
            {
                int k;
                for(k=i; k>0; k--)
                    grid[k][j]=grid[k-1][j];
                grid[k][j]=0;
                i=size;
            }
        }
    }
}

void move_right(int grid[size][size])
{
    for(int i=(size-1); i>=0; i--)
    {
        for(int j=(size-1); j>=0; j--)
        {
            if(grid[i][j]==grid[i][j-1])
            {
                grid[i][j]=(grid[i][j]*2);

                int k;
                for(k=j-1; k>0; k--)
                    grid[i][k]=grid[i][k-1];
                grid[i][k]=0;
            }
        }
    }
}

void club_right(int grid[size][size])
{
    for(int i=(size-1); i>=0; i--)
    {
        for(int j=(size-1), l=0; j>=0, l<size; j--, l++)
        {
            if(grid[i][j]==0)
            {
                int k;
                for(k=j; k>0; k--)
                    grid[i][k]=grid[i][k-1];
                grid[i][k]=0;
                j=size;
            }
        }
    }
}

void print_grid(int grid[size][size], position &p)
{
    gotoxy(p);
    for(int k=0; k<29; k++)
        cout<<(char)178;

    for(int i=0; i<size; i++)
    {
        //cout<<endl<<(char)178;
        p.y++;  gotoxy(p);  cout<<(char)178;
        for(int j=0; j<size; j++)
            cout<<"      "<<(char)178;
        p.y++;  gotoxy(p);  cout<<(char)178;
        //cout<<endl<<(char)178;

        for(int j=0; j<size; j++)
        {
            if(grid[i][j]==0)
                cout<<setw(6)<<" "<<(char)178;
            else
                cout<<setw(5)<<grid[i][j]<<" "<<(char)178;
        }


        //cout<<endl<<(char)178;
        p.y++;  gotoxy(p);  cout<<(char)178;
        for(int j=0; j<size; j++)
            cout<<"      "<<(char)178;
        p.y++;  gotoxy(p);

        for(int k=0; k<29; k++)
        cout<<(char)178;
    }
    p.y+=2;
    gotoxy(p);
}

void copy_grid(int g1[size][size], int g2[size][size])  //  g2 being copied to g1
{
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            g1[i][j]=g2[i][j];
        }
    }
}

int game_over(int grid[size][size])
{
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            if(get_score(grid)==2048)
                return 0;   //  game over: WIN

            else if(grid[i][j]==0)
                return 1;   //  game not yet over
        }
    }

    int temp_right[size][size], temp_left[size][size], temp_top[size][size], temp_bottom[size][size];
    copy_grid(temp_right, grid);
    copy_grid(temp_left, grid);
    copy_grid(temp_top, grid);
    copy_grid(temp_bottom, grid);

    club_right(temp_right);
    move_right(temp_right);
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            if(get_score(temp_right)==2048)
                return 0;   //  game over: WIN

            else if(temp_right[i][j]==0)
                return 1;   //  game not yet over
        }
    }

    club_left(temp_left);
    move_left(temp_left);
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            if(get_score(temp_left)==2048)
                return 0;   //  game over: WIN

            else if(temp_left[i][j]==0)
                return 1;   //  game not yet over
        }
    }

    club_top(temp_top);
    move_top(temp_top);
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            if(get_score(temp_top)==2048)
                return 0;   //  game over: WIN

            else if(temp_top[i][j]==0)
                return 1;   //  game not yet over
        }
    }

    club_bottom(temp_bottom);
    move_bottom(temp_bottom);
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            if(get_score(temp_bottom)==2048)
                return 0;   //  game over: WIN

            else if(temp_bottom[i][j]==0)
                return 1;   //  game not yet over
        }
    }

    return 2;   //  game over: LOSE
}

int game_over_AI(int grid[size][size])
{
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            if(get_score(grid)==2048)
                return 0;   //  game over: WIN

            else if(grid[i][j]==0)
                return 1;   //  game not yet over
        }
    }

    int temp_right[size][size], temp_left[size][size], temp_top[size][size], temp_bottom[size][size];
    copy_grid(temp_right, grid);
    copy_grid(temp_left, grid);
    copy_grid(temp_top, grid);
    copy_grid(temp_bottom, grid);

    club_right(temp_right);
    move_right(temp_right);
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            //if(get_score(temp_right)==2048)
                //return 0;   //  game over: WIN

            if(temp_right[i][j]==0)
                return 1;
                //return 13;   //  game not yet over
        }
    }

    club_left(temp_left);
    move_left(temp_left);
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            //if(get_score(temp_left)==2048)
                //return 0;   //  game over: WIN

            if(temp_left[i][j]==0)
                return 1;
                //return 12;   //  game not yet over
        }
    }

    club_top(temp_top);
    move_top(temp_top);
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            //if(get_score(temp_top)==2048)
                //return 0;   //  game over: WIN

            if(temp_top[i][j]==0)
                return 1;
                //return 11;   //  game not yet over
        }
    }

    club_bottom(temp_bottom);
    move_bottom(temp_bottom);
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            //if(get_score(temp_bottom)==2048)
                //return 0;   //  game over: WIN

            if(temp_bottom[i][j]==0)
                return 1;
                //return 10;   //  game not yet over
        }
    }

    return 2;   //  game over: LOSE
}

void play()
{
    //int grid[size][size];

    //initial_seed(grid);

    int grid[size][size]={  {2,4,16,32},
                            {8,16,32,16},
                            {4,8,64,8},
                            {2,4,16,2}   };

    int moves = 0;

    while(1)
    {
        int i=new_seed(grid);
        int state=game_over(grid);

        position s, s2;
        s.x=2;
        s.y=2;
        s2=s;

        print_grid(grid, s);
        cout<<"Score: "<<get_score(grid);
        s.y++;  gotoxy(s);  cout<<"Moves: "<<moves;
        s.y++;  gotoxy(s);  cout<<"State: "<<state;

        switch(state)
        {
        case 0:
            s.y+=2;  gotoxy(s);  cout<<"CONGRATULATIONS! YOU REACHED 2048";
            return;
            break;

        case 1:
            break;

        case 2:
            s.y+=2;  gotoxy(s);  cout<<"GAME OVER! THE BOARD HAS BEEN FILLED";
            return;
            break;
        }

        system("pause>nul");

        if(GetAsyncKeyState(VK_DOWN) && 0x8000)
        {
            club_bottom(grid);
            move_bottom(grid);
            club_bottom(grid);
            //Sleep(1000);
            moves++;
            break;
        }

        else if(GetAsyncKeyState(VK_UP) && 0x8000)
        {
            club_top(grid);
            move_top(grid);
            club_top(grid);
            //Sleep(1000);
            moves++;
            break;
        }

        else if(GetAsyncKeyState(VK_LEFT) && 0x8000)
        {
            club_left(grid);
            move_left(grid);
            club_left(grid);
            //Sleep(1000);
            moves++;
            break;
        }

        else if(GetAsyncKeyState(VK_RIGHT) && 0x8000)
        {
            club_right(grid);
            move_right(grid);
            club_right(grid);
            //Sleep(1000);
            moves++;
            break;
        }
    }
}

int get0(int grid[size][size])
{
    int zero=0;
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            if(grid[i][j]==0)
                zero++;
        }
    }
    return zero;
}

int play_AI(int speed)
{
    int grid[size][size];
    initial_seed(grid);

    /*int grid[size][size]={  {2,4,16,32},
                            {8,16,32,16},
                            {4,8,64,8},
                            {2,4,16,2}   };*/

    int moves = 0;
    int move_id;
    /*  0   =   bottom
        1   =   top
        2   =   left
        3   =   right  */

    int i=0;
    while(1)
    {
        int state=game_over_AI(grid);
        int i=new_seed(grid);

        if(i==0)
            return 0;

        position s, s2;
        s.x=2;
        s.y=2;
        s2=s;

        print_grid(grid, s);
        cout<<"Score: "<<get_score(grid);
        s.y++;  gotoxy(s);  cout<<"Moves: "<<moves;
        s.y++;  gotoxy(s);  cout<<"State: "<<state;

        //int state=game_over_AI(grid);

        switch(state)
        {
        case 0:
            s.y+=2;  gotoxy(s);  cout<<"CONGRATULATIONS! YOU REACHED 2048";
            return 1;
            break;

        case 1:
            break;

        case 2:
            s.y+=2;  gotoxy(s);  cout<<"GAME OVER! THE BOARD HAS BEEN FILLED";
            return 1;
            break;
        }

        if(state==1) //  intel
        {
            move_id=randRange(0, 3);

            int temp_right[size][size], temp_left[size][size], temp_top[size][size], temp_bottom[size][size];
            copy_grid(temp_right, grid);
            copy_grid(temp_left, grid);
            copy_grid(temp_top, grid);
            copy_grid(temp_bottom, grid);

            club_right(temp_right);
            move_right(temp_right);

            club_left(temp_left);
            move_left(temp_left);

            club_top(temp_top);
            move_top(temp_top);

            club_bottom(temp_bottom);
            move_bottom(temp_bottom);

            int max1=get_score(grid);
            if(get_score(temp_right)>max1)
            {
                max1=get_score(temp_right);
                move_id=3;
            }
            if(get_score(temp_left)>max1)
            {
                max1=get_score(temp_left);
                move_id=2;
            }
            if(get_score(temp_top)>max1)
            {
                max1=get_score(temp_top);
                move_id=1;
            }
            if(get_score(temp_bottom)>max1)
            {
                max1=get_score(temp_bottom);
                move_id=0;
            }
            else if(max1=get_score(grid))
            {
                int max2=get0(grid);
                if(get0(temp_right)>max2)
                {
                    max2=get_score(temp_right);
                    move_id=3;
                }
                if(get0(temp_left)>max2)
                {
                    max2=get_score(temp_left);
                    move_id=2;
                }
                if(get0(temp_top)>max2)
                {
                    max2=get_score(temp_top);
                    move_id=1;
                }
                if(get0(temp_bottom)>max2)
                {
                    max2=get_score(temp_bottom);
                    move_id=0;
                }
            }
        }

        else
        {
            move_id=state-10;
        }

        switch(move_id)
        {
        case 0:
            {
                club_bottom(grid);
                move_bottom(grid);
                moves++;
                break;
                //continue;
            }

        case 1:
            {
                club_top(grid);
                move_top(grid);
                moves++;
                break;
                //continue;
            }

        case 2:
            {
                club_left(grid);
                move_left(grid);
                moves++;
                break;
                //continue;
            }

        case 3:
            {
                club_right(grid);
                move_right(grid);
                moves++;
                break;
                //continue;
            }
        }
        Sleep(speed);
        //system("cls");
    }
    return 1;
}


int main()
{
    srand((unsigned)time(NULL));

    int grid[size][size]={  {2,4,2,4},
                            {0,0,4,4},
                            {0,8,0,0},
                            {2,0,0,4096}   };

    //int i=play_AI(0);
    play();

    _getch();

    return 0;
}
