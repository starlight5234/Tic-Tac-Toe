#include <graphics.h>
#include <iostream.h>
#include <stdlib.h>
#include <conio.h>

struct Move{
    int row, col;
};

char AI = 'x', player = 'o';

int max(int num1, int num2);
int min(int num1, int num2);

int minimax(char board[3][3], int depth, int isMax);
int isMovesLeft(char board[3][3]);
int evaluate(char board[3][3]);
int SelectType();

Move findBestMove(char board[3][3]);

void ClearHeader();
void ExitMenu();
void HelpPage();
void TicTacToe(int isComp);

void main(){
    
    int driver=DETECT,mode;
    initgraph(&driver,&mode,"C:\\tc\\bgi");
    
menu_start:
    ClearHeader();

    outtextxy(225, 10, "Tic Tac Toe");
    outtextxy(10, 120, "1. Play Game");
    outtextxy(10, 160,"2. Rules & Help");
    outtextxy(10, 200, "3. Exit");

menu_input:
    int menu_choice = getch();
    // ASCII Moment
    menu_choice = menu_choice - 48;

    switch(menu_choice){
        case 1:
            TicTacToe(SelectType());
            break;
        case 2:
            HelpPage();
            break;
        case 3:
            ExitMenu();
            break;
        default:
            goto menu_input;
    }
}


// Minimax Algo Start

/**
 * Find maximum between two numbers.
 */
int max(int num1, int num2){
    return num1 > num2 ? num1 : num2;
}

/*
 * Find minimum between two numbers.
 */
int min(int num1, int num2){
    return num1 < num2 ? num1 : num2;
}

// This function returns 1 if there are moves
// remaining on the board. It returns 0 if
// there are no moves left to play.
int isMovesLeft(char board[3][3]){
    for (int i = 0; i<3; i++)
        for (int j = 0; j<3; j++)
            if (board[i][j]=='_')
                return 1;
    return 0;
}

int evaluate(char board[3][3]){
    // Checking for Rows for X or O victory.
    for (int row = 0; row<3; row++)
    {
        if (board[row][0]==board[row][1] &&
            board[row][1]==board[row][2])
        {
            if (board[row][0] == AI)
                return +10;
            else if (board[row][0] == player)
                return -10;
        }
    }
 
    // Checking for Columns for X or O victory.
    for (int col = 0; col<3; col++)
    {
        if (board[0][col]==board[1][col] &&
            board[1][col]==board[2][col])
        {
            if (board[0][col] == AI)
                return +10;
            else if (board[0][col] == player)
                return -10;
        }
    }
 
    // Checking for Diagonals for X or O victory.
    if (board[0][0]==board[1][1] && board[1][1]==board[2][2])
    {
        if (board[0][0] == AI)
            return +10;
        else if (board[0][0] == player)
            return -10;
    }
 
    if (board[0][2]==board[1][1] && board[1][1]==board[2][0])
    {
        if (board[0][2] == AI)
            return +10;
        else if (board[0][2] == player)
            return -10;
    }
 
    // Else if none of them have won then return 0
    return 0;
}

// This is the minimax function. It considers all
// the possible ways the game can go and returns
// the value of the board
int minimax(char board[3][3], int depth, int isMax){
    int score = evaluate(board);
 
    // If Maximizer has won the game return his/her
    // evaluated score
    if (score == +10)
        return score;
 
    // If Minimizer has won the game return his/her
    // evaluated score
    if (score == -10)
        return score;
 
    // If there are no more moves and no winner then
    // it is a tie
    if (isMovesLeft(board) == 0)
        return 0;
 
    // If this maximizer's move
    if (isMax){
        int bestScore = -10000;
 
        // Traverse all cells
        for (int i = 0; i<3; i++)
        {
            for (int j = 0; j<3; j++)
            {
                // Check if cell is empty
                if (board[i][j]=='_')
                {
                    // Make the move
                    board[i][j] = AI;
 
                    // Call minimax recursively and choose
                    // the maximum value
                    int best = minimax(board, depth+1, 0);
                    
                    bestScore = max(best, bestScore);

                    // Undo the move
                    board[i][j] = '_';
                }
            }
        }
        return bestScore;
    }
 
    // If this minimizer's move
    else{
        int bestScore = 10000;
 
        // Traverse all cells
        for (int i = 0; i<3; i++)
        {
            for (int j = 0; j<3; j++)
            {
                // Check if cell is empty
                if (board[i][j]=='_')
                {
                    // Make the move
                    board[i][j] = player ;
 
                    // Call minimax recursively and choose
                    // the minimum value
                    int best = minimax(board, depth+1, 1);
                    
                    bestScore = min(best, bestScore);
 
                    // Undo the move
                    board[i][j] = '_';
                }
            }
        }
        return bestScore;
    }
}

// This will return the best possible move for the player
Move findBestMove(char board[3][3]){
    int bestVal = -1000;
    Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;
 
    // Traverse all cells, evaluate minimax function for
    // all empty cells. And return the cell with optimal
    // value.
    for (int i = 0; i<3; i++)
    {
        for (int j = 0; j<3; j++)
        {
            // Check if cell is empty
            if (board[i][j]=='_'){
                // Make the move
                board[i][j] = AI;
 
                // compute evaluation function for this
                // move.
                int moveVal = minimax(board, 0, 0);
 
                // Undo the move
                board[i][j] = '_';
 
                // If the value of the current move is
                // more than the best value, then update
                // best/
                if (moveVal > bestVal){
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }
 
    //gotoxy(63,20);
    //cout << bestMove.row << " " << bestMove.col;
 
    return bestMove;
}

// Minimax Algorithm End


void ClearHeader(){
    // Clear screen
    cleardevice();
    setbkcolor(BLACK);
    setcolor(CYAN);
    settextstyle(7,0,4);

}

void ExitMenu(){
    
    ClearHeader();

    setcolor(YELLOW);
	// creating circle and fill it with
	// yellow color using floodfill.
	circle(300, 100, 40);
	setfillstyle(SOLID_FILL, YELLOW);
	floodfill(300, 100, YELLOW);

	// Set color of background to black
	setcolor(BLACK);
	setfillstyle(SOLID_FILL, BLACK);

	// Use fill ellipse for creating eyes
	fillellipse(310, 85, 2, 8);
	fillellipse(290, 85, 2, 8);

	// Use ellipse for creating mouth
	ellipse(300, 100, 205, 335, 20, 11);
	ellipse(300, 100, 205, 335, 20, 12);
	ellipse(300, 100, 205, 335, 20, 13);

    //gotoxy(30,12);
    setcolor(CYAN);
    outtextxy(150, 160, "Thanks for playing.");
    getch();
    closegraph();
    exit(0);
}

void HelpPage(){
        
    ClearHeader();    
    
    outtextxy(150, 40, "Rules for TicTacToe");
    
    settextstyle(3,0,1);
    //gotoxy(5,10);
    outtextxy(10, 120, "1. The game is played on a grid that's 3 squares by 3 squares.");
    outtextxy(10, 160, "2. You are O, your friend (or the computer in this case) is X.");
    outtextxy(10, 200, "3. Players take turns putting their marks in empty squares.");
    outtextxy(10, 240, "4. The first player to get 3 of her marks in a pattern");
    outtextxy(10, 260, "   of up, down, across, or diagonally is the winner.");
    outtextxy(10, 300, "5. When all 9 squares are full, the game is over. If no");
    outtextxy(10, 320, "   player has 3 marks in a row, the game ends in a tie.");
    
    getch();
    main();

}


int SelectType(){
selection:
    ClearHeader();
    outtextxy(225, 10, "Tic Tac Toe");

    outtextxy(10, 120, "1. Player vs Player");
    outtextxy(10, 160, "2. Player vs Computer");
    outtextxy(10, 200, "3. Main Menu");

    int select_type = getch();
    // ASCII Moment
    select_type = select_type - 48;

    switch(select_type){
        case 1:
            return 0;
        case 2:
            goes_first:
                ClearHeader();
                outtextxy(225, 10, "Tic Tac Toe");

                outtextxy(10, 120, "1. Computer goes first   ");
                outtextxy(10, 160, "2. Player goes first ");
                outtextxy(10, 200, "3. Go Back     ");
                
                int who_first = getch();
                // ASCII Moment
                who_first = who_first - 48;
            
                if(who_first == 1){
                    AI = 'o', player = 'x';
                    return 1;
                }else if(who_first == 2){
                    AI = 'x', player = 'o';
                    return 2;
                }else if(who_first == 3){
                    
                    goto selection;
                }else{
                    goto goes_first;
                }
        case 3:
            main();
        default:
            goto selection;
    }

}

void TicTacToe(int isComp){
    start:
        /*
         * Define an 2D Array with blank _ values
         * These values will be overwritten with player's x/o for
         * pattern scanning
         */
        char board[3][3]={'_','_','_','_','_','_','_','_','_'};

        int player_num, play_choice, game_end=0;
        char choice;
        static int NoOfStarts=0,NoOfDraws=0,score[2]={0,0};
        NoOfStarts++;

        // Clear the header
        ClearHeader();

        // Init position on axis
        int x,y;
        
        // # Table lines
        setcolor(WHITE);
        line(100,200,400,200);
        line(100,300,400,300);
        line(200,100,200,400);
        line(300,100,300,400);

        // Some useful info
        gotoxy(30,2);
        cout<< "Tic Tac Toe Game " << NoOfStarts;
        gotoxy(14,5);
        cout << "Enter Box no.(from 1 to 9)";
        gotoxy(14,7);
        cout << "1";
        gotoxy(28,7);
        cout << "2";
        gotoxy(40,7);
        cout << "3";
        gotoxy(14,14);
        cout << "4";
        gotoxy(28,14);
        cout << "5";
        gotoxy(40,14);
        cout << "6";
        gotoxy(14,21);
        cout << "7";
        gotoxy(28,21);
        cout << "8";
        gotoxy(40,21);
        cout << "9";
	    gotoxy(55,7);
	    cout <<"--Scoreboard--";
        gotoxy(55,8);
        cout << "Player 1: " << score[0];
        gotoxy(55,9);
        cout << "Player 2: " << score[1];
        gotoxy(55,11);
        cout << "No of matches drawn: " << NoOfDraws;
        gotoxy(55,22);
        cout << "Result:";
                    
        for(int i=0;i<=2;i++){
            for(int j=0;j<=2;j++){
                    
                        
                input:
                    gotoxy(14,4);
                    player_num=((i+j)%2+1);
                    cout << "Turn of: Player " << player_num;
                    
                    
                    if(isComp == player_num){
                            Move bestMove = findBestMove(board);
                            x = bestMove.row;
                            y = bestMove.col;
                            goto eval_drawing_board;
                    }else{

                        play_choice=getch();
                        // ASCII Moment ( -1 for sanity in if else)
                        play_choice=play_choice - 48 - 1;

                        /*
                         * 0 1 2
                         * 3 4 5
                         * 6 7 8
                         */
                        // Take input again if number entered is not between 1-9
                        switch(play_choice){
                            case 0: 
                                x=0; y=0;
                                break;
                            case 1: 
                                x=1; y=0;
                                break;
                            case 2: 
                                x=2; y=0;
                                break;
                            case 3: 
                                x=0; y=1;
                                break;
                            case 4: 
                                x=1; y=1;
                                break;
                            case 5: 
                                x=2; y=1;
                                break;
                            case 6: 
                                x=0; y=2;
                                break;
                            case 7: 
                                x=1; y=2;
                                break;
                            case 8: 
                                x=2; y=2;
                                break;
                            default:
                                goto input;
                            }
                    }

                eval_drawing_board:
                    // If the position is already filled by some player
                    // take input again for the same player
                    if((board[x][y] == 'o') || (board[x][y] == 'x')){
                        goto input;
                    }

                    // If the position is not filled by player then fill it
                    else if((board[x][y] != 'o') && (board[x][y] != 'x')){

                        // Draw O for player 1
                        if(player_num == 1){
                            circle(100*x+150,100*y+150,30);
                        }

                        // Draw X for player 2
                        if(player_num == 2){
                            /*  line - /  */
                            line(x*100+125,y*100+125,x*100+185,y*100+185);
                            /*  line - \  */
                            line(x*100+125,y*100+185,x*100+185,y*100+125);
                        }

                        // Register array position of current players turn
                        if(player_num == 1){
                            board[x][y] = 'o';
                        }else if(player_num == 2){
                            board[x][y] = 'x';
                        }
                    }

                    // Some generic patterns of victory in 2D Array format
                    game_end = evaluate(board);

                    if(game_end == +10){
                        gotoxy(63,22);
                        cout<<"Player 2 wins";
                        score[player_num-1]++;
                        goto rematch;
                    }else if(game_end == -10){
                        gotoxy(63,22);
                        cout<<"Player 1 wins";
                        score[player_num-1]++;
                        goto rematch;
                    }

                    // Draw the match if no patterns match and all spaces are filled
                    if((isMovesLeft(board) == 0) && (game_end == 0)){
                        gotoxy(63,22);
                        cout<<"Match Drawn";
                        NoOfDraws++;
                        goto rematch;
                    }
            }
        }

    rematch:
        // Confirm choice
        gotoxy(55,24);
        cout << "Play again? [Y/N]";
        choice=getch();
        if((choice == 'y') || (choice == 'Y')){
            goto start;
        }else if((choice == 'n') || (choice == 'N')){
            goto exit;
        }else{
            goto rematch;
        }

    exit:
        ClearHeader();
        cout << "The final score is as follows.\n";
        cout << "Player 1 won " << score[0] << " times.\nPlayer 2 won " << score[1] << " times.\n";
        cout << "Exit to main menu? [Y/N]\n";

    exit_choice:
        char ExitChoice;
        ExitChoice = getch();
        if((ExitChoice == 'y') || (ExitChoice == 'Y')){
            main();
        }else if((ExitChoice == 'n') || (ExitChoice == 'N')){
            ExitMenu();
        }else{
            goto exit_choice;
        }
        
    
}