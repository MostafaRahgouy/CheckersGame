#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <string>

#define SIZE 10
#define MAX_SIZE 20

using namespace std;


typedef struct checkers_game{
                     int statuse;
                     int home_number;
                     string leftchild;
                     string rightchild;
                     int leftchild_takhmin;
                     int rightchild_takhmin;
                    };
struct checkers_game ai_player[MAX_SIZE] , user_player[MAX_SIZE];
int game_top = 20 , master_top = 20;

typedef struct sort_h{
                   int value;
                   int place;
                   string leftright;
                    };
struct sort_h array_h[2*MAX_SIZE]; // , hoshmand_move;

void sort_array_h(int ); //sort h

char arr[SIZE][SIZE];
//char arr_2[SIZE][SIZE];

void board(string ); // tabe rasme jadval
void setboard();    // shomaregozari jadval


void stack_game_updater(char [][SIZE] ,string , int ); // tabe update state
void stack_bigen(); // megdare avaliye dadan be stack ha


void input(int *, int *); // gereftane dot ostad
int move_master(int , int ); // harakate dot ostad



int win_player();
void mojaz(int , string  *, string *);
void takhmin(int , int , int * );
int hoshmand(int , string , int , int);
void findij(int ,int *, int *);

void move_game(int , string);


void takhmin_master(int, int ,int *);
void mojaz_master(char [][SIZE] , int , string *, string *);
void stack_game_updater_hoshmand(char [][SIZE]);


int main()
{
    setboard();
    int endgame = 100 , dot1 , dot2 , move_num = 0;
    string player1 = "MASTER" , player2 = "GAME" , bigen = "MASTER";
    while(true)
    {
        board(bigen);
        if(bigen == player1)
        {
            input(&dot1 , &dot2);
            move_num = move_master(dot1 , dot2);
        }
        if(bigen == player2)
        {
            int counter = 0;
            int max_h_1 = 0 , max_h_2 = 0 , index1 = 0 , index2 = 0;
            stack_game_updater(arr,player2 , 1);
            stack_game_updater_hoshmand(arr);
            for(int i = 0 ; i < game_top ; i++)
            {
                cout << i << " -- " <<  ai_player[i].home_number << "  " << ai_player[i].statuse << "  "
                     << ai_player[i].leftchild << "   " << ai_player[i].rightchild << "  "
                     << ai_player[i].leftchild_takhmin << "  " << ai_player[i].rightchild_takhmin << endl;
            }

            for(int i = 0 ; i < game_top ; i ++)
            {
                if(ai_player[i].statuse == 1)
                {
                    if(ai_player[i].leftchild_takhmin > 0)
                    {
                        array_h[counter].value = ai_player[i].leftchild_takhmin;
                        array_h[counter].leftright = "l";
                        array_h[counter].place = i;
                        counter ++;
                    }
                    if(ai_player[i].rightchild_takhmin > 0)
                    {
                         array_h[counter].value = ai_player[i].rightchild_takhmin;
                         array_h[counter].leftright = "r";
                         array_h[counter].place = i;
                         counter ++;
                    }
                }
            }
            sort_array_h(counter);
            cout << "----------------------------------------" << endl;
            cout << "place \t leftright \t value " << endl;
            for(int i = 0 ; i < counter ; i ++)
                cout << array_h[i].place << "\t" << array_h[i].leftright << "\t" <<  array_h[i].value << endl;

            int hoshmand_move1 , hoshmand_move2;
            cout << "mohre aval " << endl << endl;
            int p1 ,pp1, p3 , pp3 ;
            string p2 , pp2;
            p1 = array_h[1].place;
            pp1 = array_h[0].place;
            p2 = array_h[1].leftright;
            pp2 = array_h[0].leftright;
            p3 = array_h[1].value ;
            pp3 = array_h[0].value;
            if(pp3 >= p3 )
            {
                move_game(pp1 , pp2);
            }
            else
            {
            cout << array_h[0].place << "   "  << array_h[0].leftright  << "  " <<  array_h[0].value << endl;
            hoshmand_move1 = hoshmand(pp1 , pp2 , pp3, 1);
            cout << "mohre dovom " << endl << endl;


            cout << p1 << "  " << p2 << "   " << p3 << endl;
            hoshmand_move2 = hoshmand(p1,p2 , p3 , 2);

            cout << p1 << "  " << p2 << "   " << p3 << endl;
            cout << hoshmand_move1 << " , " << hoshmand_move2 << endl;

            if(hoshmand_move1 >= hoshmand_move2)
                move_game(pp1 , pp2);
            else
                move_game(p1, p2);

            }

        }
        if(bigen == player1 )
            bigen = player2;
        else
            bigen = player1;

        if(move_num == 1 && bigen == player1)
        {
            bigen = player1;
        }
        getch();
    }
    getch();
    return 0;
}


void move_game(int index_1 , string leftrigh_1 )
{
    int dot , row , col;
    dot = ai_player[index_1].home_number;
    if(leftrigh_1 == "l")
    {
        if(ai_player[index_1].leftchild == "t")
        {
            master_top --;
            findij(dot, &row , &col);
            arr[row][col] = ' ';
            dot += 9;
            findij(dot, &row , &col);
            arr[row][col] = ' ';
            dot += 9;
            findij(dot, &row , &col);
            arr[row][col] = '@';
        }
        if(ai_player[index_1].leftchild == "m")
        {
            findij(dot, &row , &col);
            arr[row][col] = ' ';
            dot += 9;
            findij(dot, &row , &col);
            arr[row][col] = '@';
        }
    }
    if(leftrigh_1 == "r")
    {
        if(ai_player[index_1].rightchild == "t")
        {
            master_top --;
            findij(dot, &row , &col);
            arr[row][col] = ' ';
            dot += 11;
            findij(dot, &row , &col);
            arr[row][col] = ' ';
            dot += 11;
            findij(dot, &row , &col);
            arr[row][col] = '@';
        }
        if(ai_player[index_1].rightchild == "m")
        {
            findij(dot, &row , &col);
            arr[row][col] = ' ';
            dot += 11;
            findij(dot, &row , &col);
            arr[row][col] = '@';
        }
    }
}


void findij(int dot ,int *row, int *col)  //checked
{
    int home_num = 0;
    for(int i = 0 ; i < SIZE ; i ++)
    {
        for(int j = 0 ; j < SIZE ; j ++)
        {
            home_num ++;
            if(dot == home_num)
            {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}


int hoshmand(int index_1 , string leftright_1 , int h_1 , int order)  // checked
{
    int h, row , col;
    char arr_2[SIZE][SIZE];
    for(int i = 0 ; i < SIZE ; i ++)
    {
        for(int j = 0 ; j < SIZE ; j ++)
        {
            arr_2[i][j] = arr[i][j];
        }
    }
    h = h_1;

    cout << "h shoro = " << h << endl;
    int dot =  ai_player[index_1].home_number;
    if(order == 2)
    {
        dot =  ai_player[index_1 - 1].home_number;
    }
    cout << "shomare stacke == " << index_1 << endl;
    cout << "mohre entekhab shoode : " << dot << endl;

    stack_game_updater(arr_2 ,"hoshmand " , 2);
    stack_game_updater_hoshmand(arr_2 );

    if(leftright_1 == "l")
    {
        if(ai_player[index_1].leftchild == "m")
        {
            findij(dot,&row, &col);
            arr_2[row][col] = ' ';
            dot += 9;
            findij(dot,&row, &col);
            arr_2[row][col] = '@';
        }
        if(ai_player[index_1].leftchild == "t")
        {
            findij(dot,&row, &col);
            arr_2[row][col] = ' ';
            dot += 9;
            findij(dot,&row, &col);
            arr_2[row][col] = ' ';
            dot += 9;
            findij(dot,&row, &col);
            arr_2[row][col] = '@';
        }
    }
    if(leftright_1 == "r")
    {
        if(ai_player[index_1].rightchild == "m")
        {
            findij(dot,&row, &col);
            arr_2[row][col] = ' ';
            dot += 11;
            findij(dot,&row, &col);
            arr_2[row][col] = '@';
        }
        if(ai_player[index_1].rightchild == "t")
        {
            findij(dot,&row, &col);
            arr_2[row][col] = ' ';
            dot += 11;
            findij(dot,&row, &col);
            arr_2[row][col] = ' ';
            dot += 11;
            findij(dot,&row, &col);
            arr_2[row][col] = '@';
        }
    }
    stack_game_updater_hoshmand(arr_2);
    stack_game_updater(arr_2 , "hoshmand", 2);
    cout << "h ma bade avalin harakat = " << h << endl;
    cout << dot << "   " <<  row << "  " << col << "   " << arr_2[row][col] << endl;


    stack_game_updater_hoshmand(arr_2);

    for(int i = 0 ; i < master_top ; i++)
    {
        cout << i << " -- " <<  user_player[i].home_number << "  " << user_player[i].statuse << "  "
            << user_player[i].leftchild << "   " << user_player[i].rightchild << "  "
            << user_player[i].leftchild_takhmin << "  " << user_player[i].rightchild_takhmin << endl;
    }

    int counter = 0;
    for(int i = 0 ; i < master_top ; i ++)
    {
        if(user_player[i].statuse == 1)
        {
            if(user_player[i].leftchild_takhmin > 0)
            {
                array_h[counter].value = user_player[i].leftchild_takhmin;
                array_h[counter].leftright = "l";
                array_h[counter].place = i;
                counter ++;
            }
            if(user_player[i].rightchild_takhmin > 0)
            {
                array_h[counter].value = user_player[i].rightchild_takhmin;
                array_h[counter].leftright = "r";
                array_h[counter].place = i;
                counter ++;
            }
        }
    }
    sort_array_h(counter);
    cout << "----------------------------------------" << endl;
    cout << "place \t leftright \t value " << endl;
    for(int i = 0 ; i < counter ; i ++)
        cout << array_h[i].place << "\t" << array_h[i].leftright << "\t" <<  array_h[i].value << endl;

    int index_2 = array_h[0].place;
    int dot2 = user_player[index_2].home_number;
    cout << "dot ostad gabl az haraakt= " << dot2 << endl;
    string leftright_2 = array_h[0].leftright;
    if(leftright_2 == "l")
    {
        if(user_player[index_2].leftchild == "m")
        {
            findij(dot2 , &row , &col);
            arr_2[row][col] = ' ';
            dot2 -= 11;
            findij(dot2 , &row , &col);
            arr_2[row][col] = '#';
        }
        if(user_player[index_2].leftchild == "t")
        {
            h --;
            findij(dot2 , &row , &col);
            arr_2[row][col] = ' ';

            dot2 -= 11;
            findij(dot2 , &row , &col);
            arr_2[row][col] = ' ';
            dot2 -= 11;
            findij(dot2 , &row , &col);
            arr_2[row][col] = '#';
        }
    }
    else
    {
        if(user_player[index_2].rightchild == "m")
        {
            findij(dot2 , &row , &col);
            arr_2[row][col] = ' ';
            dot2 -= 9;
            findij(dot2 , &row , &col);
            arr_2[row][col] = '#';
        }
        if(user_player[index_2].rightchild == "t")
        {
            h --;
            findij(dot2 , &row , &col);
            arr_2[row][col] = ' ';

            dot2 -= 9;
            findij(dot2 , &row , &col);
            arr_2[row][col] = ' ';
            dot2 -= 9;
            findij(dot2 , &row , &col);
            arr_2[row][col] = '#';
        }
    }

    cout << "dot ostad bad az haraakt= " << dot2 << "   dote ma  = " << dot << endl;
    cout << "vaziate khoneye 51 " << endl;

    stack_game_updater_hoshmand(arr_2);
    stack_game_updater(arr_2 , "hoshmand", 2);

    for(int i = 0 ; i < game_top ; i ++)
    {
        if(ai_player[i].home_number == dot)
        {
            if(ai_player[i].leftchild_takhmin <= ai_player[i].rightchild_takhmin)
            {
                h += ai_player[i].leftchild_takhmin;
                break;
            }
            else
            {
                h += ai_player[i].rightchild_takhmin;
                break;
            }
        }
    }
    return h;
}



/*int hoshmand(int index_1, string leftrigh_1 , int h_1)
{
    int h, row , col;
    for(int i = 0 ; i < SIZE ; i ++)
    {
        for(int j = 0 ; j < SIZE ; j ++)
        {
            arr_2[i][j] = arr[i][j];
        }
    }
    h = 0;
    cout << "h shoro = " << h << endl;

    int dot =  ai_player[index_1].home_number;
    cout << "shomare stacke == " << index_1 << endl;
    cout << "mohre entekhab shoode : " << dot << endl;
     stack_game_updater(arr_2 ,"hoshmand " , 2);
    if(leftrigh_1 == "l")
    {
        dot = ai_player[index_1].home_number;
        findij(dot, &row, &col);
        if(ai_player[index_1].leftchild == "t")
        {

            arr_2[row][col] = ' ';
            dot += 9;
            findij(dot, &row, &col);
            arr_2[row][col] = ' ';
            dot += 9;
            findij(dot, &row, &col);
            arr_2[row][col] = '@';
        }
        if(ai_player[index_1].leftchild == "m")
        {
            dot = ai_player[index_1].home_number;
            findij(dot, &row, &col);
            arr_2[col][row] = ' ';
            dot += 9;
            findij(dot, &row, &col);
            arr_2[row][col] = '@';
        }
    }
    else
    //if(leftrigh_1 == "r")
    {

        dot = ai_player[index_1].home_number;
        findij(dot, &row, &col);
        if(ai_player[index_1].rightchild == "t")
        {
            arr_2[row][col] = ' ';
            dot += 11;
            findij(dot, &row, &col);
            arr_2[row][col] = ' ';
            dot += 11;
            findij(dot, &row, &col);
            arr_2[row][col] = '@';
        }
        if(ai_player[index_1].rightchild == "m")
        {
            dot = ai_player[index_1].home_number;
            findij(dot, &row, &col);
            arr_2[row][col] = ' ';
            dot += 11;
            findij(dot, &row, &col);
            arr_2[row][col] = '@';
        }
    }
    cout << "dot bad az avalin harakat = " << dot << endl;
    stack_game_updater(arr_2 ,"hoshmand" , 2);

    int counter = 0;
    for(int i = 0 ; i < game_top ; i ++)
    {
        if(ai_player[i].statuse == 1)
        {
            if(ai_player[i].leftchild_takhmin > 0)
            {
                array_h[counter].value = ai_player[i].leftchild_takhmin;
                array_h[counter].leftright = "l";
                array_h[counter].place = i;
                counter ++;
            }
            if(ai_player[i].rightchild_takhmin > 0)
            {
                array_h[counter].value = ai_player[i].rightchild_takhmin;
                array_h[counter].leftright = "r";
                array_h[counter].place = i;
                counter ++;
            }
       }
    }
    int home , new_dot;
    for(int i = 0 ; i < counter ; i ++)
    {
        home = array_h[i].place;
        new_dot = ai_player[home].home_number;
        if(new_dot == dot && array_h[i].leftright == leftrigh_1)
        {
            h += array_h[i].value;
            break;
        }
    }
    cout << "new dot takhmin (to takhmin mohasebeshode ) = " << new_dot << endl;
    cout << " home (andise on nogte ) = "<< home << endl;

    cout << "h harakate aval ma = " << h << endl;

    stack_game_updater_hoshmand(arr_2);
    counter = 0;
    for(int i = 0 ; i < master_top ; i ++)
    {
        if(user_player[i].statuse == 1)
        {
            array_h[counter].value = user_player[i].leftchild_takhmin;
            array_h[counter].leftright = "l";
            array_h[counter].place = i;
            counter ++;
            array_h[counter].value = user_player[i].rightchild_takhmin;
            array_h[counter].leftright = "r";
            array_h[counter].place = i;
            counter ++;
        }
    }
    sort_array_h(counter);
    int index_m = array_h[0].place;
    dot = user_player[index_m].home_number;
    cout << "dot ostad (avalin moshre ostad )  = " << dot << endl;
    if(array_h[0].leftright == "l")
    {
        string leftchild_m = user_player[index_m].leftchild;
        if(user_player[index_m].leftchild == "t")
        {
            dot = user_player[index_m].home_number;
            findij(dot, &row, &col);
            arr_2[row][col] = ' ';
            dot -= 11;
            findij(dot, &row, &col);
            arr_2[row][col] = ' ';
            dot -= 11;
            findij(dot, &row, &col);
            arr_2[row][col] = '#';
        }
        if(user_player[index_m].leftchild == "m")
        {
            dot = user_player[index_m].home_number;
            findij(dot, &row, &col);
            arr_2[row][col] = ' ';
            dot -= 11;
            findij(dot, &row, &col);
            arr_2[row][col] = '#';
        }

    }
    else
    //if(array_h[0].leftright == "r")
    {
       // int index_m = user_player[index_m].home_number;
        if(user_player[index_m].rightchild == "t")
        {
             dot = user_player[index_m].home_number;
            findij(dot, &row, &col);
            arr_2[row][col] = ' ';
            dot -= 9;
            findij(dot, &row, &col);
            arr_2[row][col] = ' ';
            dot -= 9;
            findij(dot, &row, &col);
            arr_2[row][col] = '#';
        }
        if(user_player[index_m].rightchild == "m")
        {
            dot = user_player[index_m].home_number;
            findij(dot, &row, &col);
            arr_2[row][col] = ' ';
            dot -= 9;
            findij(dot, &row, &col);
            arr_2[row][col] = '#';
        }
    }


    cout << "dot ostad bad harakat = " << dot << endl;
    stack_game_updater(arr_2 ,"hoshmand" , 2);


    if(ai_player[home].leftchild_takhmin >= ai_player[home].rightchild_takhmin )
        h += ai_player[home].leftchild_takhmin;
    else
        h += ai_player[home].rightchild_takhmin;

    cout << "h bad az harakate ostad " << h << endl;
    return  h;
}
*/


void mojaz(int home , string *left_child , string *right_child)   // checked
{
    int home_num = 0 , i , j;
    for(int row = 0 ; row < SIZE ; row ++)
    {
        for(int col = 0 ; col < SIZE ; col ++)
        {
            home_num ++;
            if(home_num == home)
            {
                i = row;
                j = col;
                break;
                break;
            }
        }
    }
    if(j == 0 )
        *left_child = "f";
    if(j == 9)
        *right_child = "f";
    if(j != 0 && arr[i + 1][j - 1] == '@')
        *left_child = "f";

    if(j != 9 && arr[i + 1][j + 1] == '@')
        *right_child = "f";

    if( arr[i + 1][j - 1] == ' ' && j != 0)
         *left_child = "m" ;

    if(arr[i + 1][j + 1] == ' ' && j != 9)
          *right_child = "m" ;


    if(j < 8)
    {
        if(arr[i + 1][j + 1] == '#' && arr[i + 2][j + 2] == ' ')
            *right_child = "t" ;
    }
    if(j > 1)
    {
        if(arr[i + 1][j - 1] == '#' && arr[i + 2][j - 2] == ' ')
            *left_child = "t" ;
    }
}

int win_player()
{
    /*if(game_top == 0)
    {
        system("cls");
        cout << "\n\n\n\n\n\t\t1-M S T E R    W I N " << endl;
        return 1;
    }
    if(master_top == 0)
    {
    //    system("cls");
        cout << "\n\n\n\n\n\t\t2-G A M E   O V E R " << endl;
        return 1;
    }*/
    int check_game = 0 , check_master = 0;
    for(int i = 0 ; i < game_top ; i ++)
    {
        if(ai_player[i].statuse == 1)
        {
            check_game = 1;
            break;
        }
    }
    for(int i = 0 ; i < master_top ; i ++)
    {
        if(user_player[i].statuse == 1)
        {
            check_master = 1;
            break;
        }
    }
    if(check_game == 0 && check_master == 1)
    {
        system("cls");
        cout << "\n\n\n\n\n\t\t3-M S T E R    W I N " << endl;
        return 1;
    }
    if(check_game == 1 && check_master == 0)
    {
        system("cls");
        cout << "\n\n\n\n\n\t\t4-G A M E   O V E R " << endl;
        return 1;
    }
    if(check_game == 0 && check_master == 0)
    {
        system("cls");
        cout << "\n\n\n\n\n\t\t5-G A M E    O N     K N O W N " << endl;
        return 1;
    }
    return 0;
}


void sort_array_h(int counter)  // checked
{
    for(int i = counter - 1 ; i >= 0 ; i --)
    {
        for(int j = 0 ; j < i ; j ++)
        {
            if(array_h[j].value < array_h[j + 1].value)
            {
                int temp1 = array_h[j].place;
                int temp2 = array_h[j].value;
                string temp3 = array_h[j].leftright;
                array_h[j].place = array_h[j + 1].place;
                array_h[j].value = array_h[j + 1].value;
                array_h[j].leftright = array_h[j + 1].leftright;
                array_h[j + 1].place = temp1;
                array_h[j + 1].value = temp2;
                array_h[j + 1].leftright = temp3;
            }
        }
    }
}


void board(string player)  // checked
{
    cout << "                                  " << player << endl;
    cout << "                             GOLABI Checkers Game                              " << endl << endl;
    cout << " ______________________________________________________________________________" << endl;;
    cout << "|       |       |       |       |       |       |       |       |       |      |";
    cout << "|       |       |       |       |       |       |       |       |       |      |";
    cout << "|   " << arr[0][0] << "   |   " << arr[0][1] << "   |   " << arr[0][2]
         << "   |   " << arr[0][3] << "   |   " << arr[0][4] << "   |   " << arr[0][5]
         << "   |    " << arr[0][6] << "  |   " << arr[0][7] << "   |   " << arr[0][8]
         << "   |   " << arr[0][9] << "  |";
    cout << "|       |       |       |       |       |       |       |       |       |      |";
    cout << "|___1___|___2___|___3___|___4___|___5___|___6___|___7___|___8___|___9___|__10__|";
    cout << "|       |       |       |       |       |       |       |       |       |      |";
    cout << "|       |       |       |       |       |       |       |       |       |      |";
    cout << "|   " << arr[1][0] << "   |   " << arr[1][1] << "   |   " << arr[1][2]
         << "   |   " << arr[1][3] << "   |   " << arr[1][4] << "   |   " << arr[1][5]
         << "   |    " << arr[1][6] << "  |   " << arr[1][7] << "   |   " << arr[1][8]
         << "   |   " << arr[1][9] << "  |";
    cout << "|       |       |       |       |       |       |       |       |       |      |";
    cout << "|___11__|___12__|___13__|___14__|___15__|___16__|___17__|___18__|___19__|__20__|";
    cout << "|       |       |       |       |       |       |       |       |       |      |";
    cout << "|       |       |       |       |       |       |       |       |       |      |";
    cout << "|   " << arr[2][0] << "   |   " << arr[2][1] << "   |   " << arr[2][2]
         << "   |   " << arr[2][3] << "   |   " << arr[2][4] << "   |   " << arr[2][5]
         << "   |    " << arr[2][6] << "  |   " << arr[2][7] << "   |   " << arr[2][8]
         << "   |   " << arr[2][9] << "  |";
    cout << "|       |       |       |       |       |       |       |       |       |      |";
    cout << "|___21__|___22__|___23__|___24__|___25__|___26__|___27__|___28__|___29__|__30__|";
    cout << "|       |       |       |       |       |       |       |       |       |      |";
    cout << "|       |       |       |       |       |       |       |       |       |      |";
    cout << "|   " << arr[3][0] << "   |   " << arr[3][1] << "   |   " << arr[3][2]
         << "   |   " << arr[3][3] << "   |   " << arr[3][4] << "   |   " << arr[3][5]
         << "   |    " << arr[3][6] << "  |   " << arr[3][7] << "   |   " << arr[3][8]
         << "   |   " << arr[3][9] << "  |";
    cout << "|       |       |       |       |       |       |       |       |       |      |";
    cout << "|___31__|___32__|___33__|___34__|___35__|___36__|___37__|___38__|___39__|__40__|";
    cout << "|       |       |       |       |       |       |       |       |       |      |";
    cout << "|       |       |       |       |       |       |       |       |       |      |";
    cout << "|   " << arr[4][0] << "   |   " << arr[4][1] << "   |   " << arr[4][2]
         << "   |   " << arr[4][3] << "   |   " << arr[4][4] << "   |   " << arr[4][5]
         << "   |    " << arr[4][6] << "  |   " << arr[4][7] << "   |   " << arr[4][8]
         << "   |   "  << arr[4][9] << "  |";
    cout << "|       |       |       |       |       |       |       |       |       |      |";
    cout << "|___41__|___42__|___43__|___44__|___45__|___46__|___47__|___48__|___49__|__50__|";
    cout << "|       |       |       |       |       |       |       |       |       |      |";
    cout << "|       |       |       |       |       |       |       |       |       |      |";
    cout << "|   " << arr[5][0] << "   |   " << arr[5][1] << "   |   " << arr[5][2]
         << "   |   " << arr[5][3] << "   |   " << arr[5][4] << "   |   " << arr[5][5]
         << "   |    " << arr[5][6] << "  |   " << arr[5][7] << "   |   " << arr[5][8]
         << "   |   " << arr[5][9] << "  |";
    cout << "|       |       |       |       |       |       |       |       |       |      |";
    cout << "|___51__|___52__|___53__|___54__|___55__|___56__|___57__|___58__|___59__|__60__|";
    cout << "|       |       |       |       |       |       |       |       |       |      |";
    cout << "|       |       |       |       |       |       |       |       |       |      |";
    cout << "|   " << arr[6][0] << "   |   " << arr[6][1] << "   |   " << arr[6][2]
         << "   |   " << arr[6][3] << "   |   " << arr[6][4] << "   |   " << arr[6][5]
         << "   |    " << arr[6][6] << "  |   " << arr[6][7] << "   |   " << arr[6][8]
         << "   |   " << arr[6][9] << "  |";
    cout << "|       |       |       |       |       |       |       |       |       |      |";
    cout << "|___61__|___62__|___63__|___64__|___65__|___66__|___67__|___68__|___69__|__70__|";
    cout << "|       |       |       |       |       |       |       |       |       |      |";
    cout << "|       |       |       |       |       |       |       |       |       |      |";
    cout << "|   " << arr[7][0] << "   |   " << arr[7][1] << "   |   " << arr[7][2]
         << "   |   " << arr[7][3] << "   |   " << arr[7][4] << "   |   " << arr[7][5]
         << "   |    " << arr[7][6] << "  |   " << arr[7][7] << "   |   " << arr[7][8]
         << "   |   "  << arr[7][9] << "  |";
    cout << "|       |       |       |       |       |       |       |       |       |      |";
    cout << "|___71__|___72__|___73__|___74__|___75__|___76__|___77__|___78__|___79__|__80__|";
    cout << "|       |       |       |       |       |       |       |       |       |      |";
    cout << "|       |       |       |       |       |       |       |       |       |      |";
    cout << "|   " << arr[8][0] << "   |   " << arr[8][1] << "   |   " << arr[8][2]
         << "   |   " << arr[8][3] << "   |   " << arr[8][4] << "   |   " << arr[8][5]
         << "   |    " << arr[8][6] << "  |   " << arr[8][7] << "   |   " << arr[8][8]
         << "   |   " << arr[8][9] << "  |";
    cout << "|       |       |       |       |       |       |       |       |       |      |";
    cout << "|___81__|___82__|___83__|___84__|___85__|___86__|___87__|___88__|___89__|__90__|";
    cout << "|       |       |       |       |       |       |       |       |       |      |";
    cout << "|       |       |       |       |       |       |       |       |       |      |";
    cout << "|   " << arr[9][0] << "   |   " << arr[9][1] << "   |   " << arr[9][2]
         << "   |   " << arr[9][3] << "   |   " << arr[9][4] << "   |   " << arr[9][5]
         << "   |    " << arr[9][6] << "  |   " << arr[9][7] << "   |   " << arr[9][8]
         << "   |   " << arr[9][9] << "  |";
    cout << "|       |       |       |       |       |       |       |       |       |      |";
    cout << "|___91__|___92__|___93__|___94__|___95__|___96__|___97__|___98__|___99__|__100_|";
}


void setboard()   // checked
{
    for(int i = 0 ; i < SIZE ; i ++)
        for(int j = 0 ; j < SIZE ; j ++)
             arr[i][j] = ' ';
    for(int i = 0 ; i < 4 ; i ++ )
    {
        int j = 0;
        if(i%2 == 0)
            j ++;
        for( ; j < SIZE ; j +=2)
            arr[i][j] = '@';
    }

    for(int i = 6 ; i < SIZE ; i ++ )
    {
        int j = 0;
        if(i%2 == 0)
            j ++;
        for( ; j < SIZE ; j +=2)
            arr[i][j] = '#';
    }
}


void input(int *firstplace , int *secondplace)   // checked
{
    cout << "Enter a First Place ?";
    cin >> *firstplace;
    cout << "Enter a Second Place ?";
    cin >> *secondplace;
}


int move_master(int FirstPlace , int SecondPlace)   // checked
{
    int row1 , col1 , row2 , col2;
    string leftchild , rightchild;

    findij(FirstPlace , &row1 , &col1);
    findij(SecondPlace , &row2 , &col2);

    int sum = FirstPlace - SecondPlace;

    if(sum > 12)
    {
        game_top --;
        arr[row1][col1] = ' ';
        if(sum < 20)
        {
            arr[row1 - 1][col1 - 1] = ' ';
        }
        else
            arr[row1 - 1][col1 + 1] = ' ';

        arr[row2][col2] = '#';

        mojaz_master(arr , SecondPlace , &leftchild , &rightchild);
        if(leftchild == "t" || rightchild == "t")
        {
            return 1; // baraye jayezehe
        }
    }
    else
    {
        arr[row1][col1] = ' ';
        arr[row2][col2] = '#';
    }
    return 5;
}


void takhmin(int dot, int order, int *child_takhmin  ) //  checked
{
   string new_left_child , new_right_child;
    if(order == 1)
    {
        *child_takhmin = 1;
    }
    if(order == 2)
    {
        *child_takhmin = 2;
    }
    if(order == 3)
    {
        *child_takhmin = 1;
    }
    if(order == 4)
    {
        *child_takhmin = 2;
    }

    if(order == 2)
    {
        mojaz(dot + 18 , &new_left_child , &new_right_child);
        if(new_left_child == "t" || new_right_child == "t")
        {
            *child_takhmin = 3;
        }
    }
    if(order == 4)
    {
        mojaz(dot + 22 , &new_left_child , &new_right_child);
        if(new_left_child == "t" || new_right_child == "t")
        {
            *child_takhmin = 3;
        }
    }
}

void stack_game_updater(char array_ha[][SIZE] , string player , int order)  // checked
{
   int home_num = 0 , counter1 = 0 , counter = 0 , num;
    string left_child , right_child;
    int left_child_takhmin , right_child_takhmin;
    for(int i = 0 ; i < SIZE ; i ++)
    {
        for(int j = 0 ; j < SIZE ; j ++)
        {
            home_num ++;
            if(array_ha[i][j] == '@')//if( array_ha[i][j] != ' ' )
            {
                mojaz(home_num , &left_child , &right_child);
                if(left_child == "m")
                    takhmin(home_num , 1 , &left_child_takhmin );//, &right_child_takhmin);
                if(left_child == "t")
                    takhmin(home_num , 2 , &left_child_takhmin ); //, &right_child_takhmin);
                if(right_child == "m" )
                    takhmin(home_num , 3 , &right_child_takhmin); // &left_child_takhmin ,
                if(right_child == "t" )
                    takhmin(home_num , 4 , &right_child_takhmin); //  &left_child_takhmin ,

                if(left_child == "f" && right_child == "f")
                {
                    num = 0;
                    left_child_takhmin = -1;
                    right_child_takhmin = -1;
                }
                if(left_child == "f")
                    left_child_takhmin = -1;
                if(right_child == "f")
                    right_child_takhmin = -1;
                if(left_child == "m" || right_child == "m")
                    num = 1;
                //if(array_ha[i][j] == '@')
                //{
                     ai_player[counter].statuse = num;
                     ai_player[counter].home_number = home_num;
                     ai_player[counter].leftchild = left_child;
                     ai_player[counter].rightchild = right_child;
                     ai_player[counter].leftchild_takhmin = left_child_takhmin;
                     ai_player[counter].rightchild_takhmin = right_child_takhmin;

                     counter ++;
               /* }
               if(array_ha[i][j] == '#')
               {
                   user_player[counter1].statuse = num;
                   user_player[counter1].home_number = home_num;
                   user_player[counter1].leftchild = left_child;
                   user_player[counter1].rightchild = right_child;
                   user_player[counter1].leftchild_takhmin = left_child_takhmin;
                   user_player[counter1].rightchild_takhmin = right_child_takhmin;

                   counter1 ++;
               }*/

            }
        }
    }
    if(order == 1)
    {
        if(player == "MASTER")
            master_top = counter1;
        if(player == "GAME")
            game_top = counter;
    }

}


void stack_bigen()  //checked
{
    for(int i = 0 ; i < MAX_SIZE ; i ++)
    {
        ai_player[i].statuse = 8;
        ai_player[i].home_number = 0;
        ai_player[i].leftchild = ' ';
        ai_player[i].rightchild = ' ';
        ai_player[i].leftchild_takhmin = 0;
        ai_player[i].rightchild_takhmin = 0;

        user_player[i].statuse = 8;
        user_player[i].home_number = 0;
        user_player[i].leftchild = ' ';
        user_player[i].rightchild = ' ';
        user_player[i].leftchild_takhmin = 0;
        user_player[i].rightchild_takhmin = 0;
    }
}


void stack_game_updater_hoshmand(char array_ha[][SIZE])  // checked
{
    int home_num = 0 , counter1 = 0 , counter = 0 , num;
    string left_child , right_child;
    int left_child_takhmin , right_child_takhmin;
    for(int i = 0 ; i < SIZE ; i ++)
    {
        for(int j = 0 ; j < SIZE ; j ++)
        {
            home_num ++;
            if( array_ha[i][j] == '#' )
            {
                mojaz_master(array_ha , home_num , &left_child , &right_child);
                if(left_child == "m")
                    takhmin_master(home_num , 1 , &left_child_takhmin );//, &right_child_takhmin);
                if(left_child == "t")
                    takhmin_master(home_num , 2 , &left_child_takhmin ); //, &right_child_takhmin);
                if(right_child == "m" )
                    takhmin_master(home_num , 3 , &right_child_takhmin); // &left_child_takhmin ,
                if(right_child == "t" )
                    takhmin_master(home_num , 4 , &right_child_takhmin); //  &left_child_takhmin ,

                if(left_child == "f" && right_child == "f")
                {
                    num = 0;
                    left_child_takhmin = -1;
                    right_child_takhmin = -1;
                }
                if(left_child == "f")
                    left_child_takhmin = -1;
                if(right_child == "f")
                    right_child_takhmin = -1;
                if(left_child == "m" || right_child == "m")
                    num = 1;

                   user_player[counter1].statuse = num;
                   user_player[counter1].home_number = home_num;
                   user_player[counter1].leftchild = left_child;
                   user_player[counter1].rightchild = right_child;
                   user_player[counter1].leftchild_takhmin = left_child_takhmin;
                   user_player[counter1].rightchild_takhmin = right_child_takhmin;
                   counter1 ++;
            }
        }
    }
}
void mojaz_master(char arr_2[][SIZE] ,int home , string *left_child , string *right_child) // checked
{
    int home_num = 0 , i , j;
    for(int row = 0 ; row < SIZE ; row ++)
    {
        for(int col = 0 ; col < SIZE ; col ++)
        {
            home_num ++;
            if(home_num == home)
            {
                i = row;
                j = col;
                break;
                break;
            }
        }
    }
    if(j == 0 )
        *left_child = "f";
    if(j == 9)
        *right_child = "f";
    if(j != 0 && arr_2[i - 1][j - 1] == '#')
        *left_child = "f";

    if(j != 9 && arr_2[i - 1][j + 1] == '#')
        *right_child = "f";

    if( arr_2[i - 1][j - 1] == ' ' && j != 0)
         *left_child = "m" ;

    if(arr_2[i - 1][j + 1] == ' ' && j != 9)
          *right_child = "m" ;


    if(j < 8)
    {
        if(arr_2[i - 1][j + 1] == '@' && arr_2[i - 2][j + 2] == ' ')
            *right_child = "t" ;
    }
    if(j > 1)
    {
        if(arr_2[i - 1][j - 1] == '@' && arr_2[i - 2][j - 2] == ' ')
            *left_child = "t" ;
    }
}

void takhmin_master(int dot, int order , int  *child_takhmin)   //checked
{
    string new_left_child , new_right_child;
    if(order == 1)
    {
        *child_takhmin = 1;
    }
    if(order == 2)
    {
        *child_takhmin = 2;
    }
    if(order == 3)
    {
        *child_takhmin = 1;
    }
    if(order == 4)
    {
        *child_takhmin = 2;
    }

    if(order == 2)
    {
        mojaz(dot - 22 , &new_left_child , &new_right_child);
        if(new_left_child == "t" || new_right_child == "t")
        {
            *child_takhmin = 3;
        }
    }
    if(order == 4)
    {
        mojaz(dot - 18 , &new_left_child , &new_right_child);
        if(new_left_child == "t" || new_right_child == "t")
        {
            *child_takhmin = 3;
        }
    }
}

/*
            for(int i = 0 ; i < game_top ; i ++)
            {
                if(ai_player[i].statuse == 1)
                {
                    if(ai_player[i].leftchild_takhmin > 0)
                    {
                        array_h[counter].value = ai_player[i].leftchild_takhmin;
                        array_h[counter].leftright = "l";
                        array_h[counter].place = i;
                        counter ++;
                    }
                    if(ai_player[i].rightchild_takhmin > 0)
                    {
                         array_h[counter].value = ai_player[i].rightchild_takhmin;
                         array_h[counter].leftright = "r";
                         array_h[counter].place = i;
                         counter ++;
                    }
                }
            }
*/


