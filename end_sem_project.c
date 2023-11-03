#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>
#include<conio.h>

#define SIZE 10
#define MINES 15

//Variables used
char board[3][3];
const char PLAYER = 'X';
const char COMPUTER = 'O';

int i, j, height = 30, width = 30;
int gameover, score;
int x, y, fruitX, fruitY, flag;
int tailX[100], tailY[100];
int n;

char bord[SIZE][SIZE];
char displayBoard[SIZE][SIZE];
int minesPlaced = 0;

//Functions used
void resetBoard();
void printBoard();
int checkFreeSpaces();
void playerMove();
void computerMove();
char checkWinner();
void printWinner(char);

void setup();
void draw();
void input();
void logic();

void initializeBoard();
void placeMines();
void printBord();
int countAdjacentMines(int row, int col);
void revealCell(int row, int col);

int snakeWaterGun(char you, char comp);

//Function definitions
void resetBoard()
{
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            board[i][j] = ' ';
        }
    }
}

void printBoard()
{
    printf(" %c | %c | %c ",board[0][0],board[0][1],board[0][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ",board[1][0],board[1][1],board[1][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ",board[2][0],board[2][1],board[2][2]);
    printf("\n");
}

int checkFreeSpaces()
{
    int freeSpace = 9;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(board[i][j] != ' '){
                freeSpace--;
            }
        }
    }
    return freeSpace;
}

void playerMove()
{
    int x,y;
do
{
    printf("Enter Row (1-3) : ");
    scanf("%d",&x);
    x--;
    printf("Enter Column (1-3) : ");
    scanf("%d",&y);
    y--;
    if(board[x][y] != ' '){
        printf("Invalid move!\n");
    }
    else{
        board[x][y] = PLAYER;
        break;
    }
} while (board[x][y] != ' ');
}

void computerMove()
{
    srand(time(0));
    int x,y;
    if(checkFreeSpaces()>0){
        do
        {
            x = rand() % 3;
            y = rand() % 3;
        } while (board[x][y] != ' ');
        board[x][y] = COMPUTER;
    }
    else{
        printWinner(' ');
    }
}

char checkWinner()
{
    for(int i = 0; i < 3; i++){
        if(board[i][0]==board[i][1] && board[i][0]==board[i][2])
        {
            return board[i][0];
        }
    }
    for(int i = 0; i < 3; i++){
        if(board[0][i]==board[1][i] && board[0][i]==board[2][i])
        {
            return board[0][i];
        }
    }
    if(board[0][0]==board[1][1] && board[0][0]==board[2][2])
        {
            return board[0][0];
        }
    if(board[0][2]==board[1][1] && board[0][2]==board[2][0])
        {
            return board[0][2];
        }

    return ' ';

}

void printWinner(char winner)
{
    if(winner == PLAYER){
        printf("YOU WIN!");
    }
    else if(winner == COMPUTER){
        printf("YOU LOSE!");
    }
    else{
        printf("IT'S A DRAW!");
    }
}


void setup()
{
    gameover = 0;
    // Initial position of the snake
    x = height / 2;
    y = width / 2;

    label1:
        fruitX = rand() % 30;
        if (fruitX == 0)
            goto label1;

    label2:
        fruitY = rand() % 30;
        if (fruitY == 0)
            goto label2;

    score = 0;
}

void draw()
{
    system("cls");

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (i == 0 || i == width - 1
                || j == 0
                || j == height - 1) {
                printf("#");
            }
            else {
                if (i == x && j == y)
                    printf("O");
                else if (i == fruitX
                    && j == fruitY)
                    printf("*");
                else {
                    int k = 0;
                    for (int k = 0; k < n; k++) {
                        if (i == tailX[k] && j == tailY[k]) {
                            printf("o");
                            k = 1;
                        }
                    }
                    if (k == 0)
                        printf(" ");
                }
            }
        }
        printf("\n");
    }
    printf("Score = %d", score);
    printf("\n");
}

void input()
{
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            flag = 1;
            break;
        case 's':
            flag = 2;
            break;
        case 'd':
            flag = 3;
            break;
        case 'w':
            flag = 4;
            break;
        case 'x':
            gameover = 1;
            break;
        }
    }
}

void logic()
{
    
    switch (flag) {
    case 1:
        y--;
        break;
    case 2:
        x++;
        break;
    case 3:
        y++;
        break;
    case 4:
        x--;
        break;
    default:
        break;
    }

    if (x < 0 || x > height
        || y < 0 || y > width)
        gameover = 1;

    for (i = 0; i < n; i++) {
        if (tailX[i] == x
            && tailY[i] == y)
            gameover = 1;
    }

    if (x == fruitX && y == fruitY) {
    label3:
        fruitX = rand() % 20;
        if (fruitX == 0)
            goto label3;
    label4:
        fruitY = rand() % 20;
        if (fruitY == 0)
            goto label4;
        score += 10;
        n++;
    }
}

void initializeBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            bord[i][j] = '0';
            displayBoard[i][j] = '?';
        }
    }
}

void placeMines() {
    srand(time(NULL));
    while (minesPlaced < MINES) {
        int row = rand() % SIZE;
        int col = rand() % SIZE;
        if (bord[row][col] != 'X') {
            bord[row][col] = 'X';
            minesPlaced++;
        }
    }
}

void printBord() {
    printf("  ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", i);
    }
    printf("\n");

    for (int i = 0; i < SIZE; i++) {
        printf("%d ", i);
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", displayBoard[i][j]);
        }
        printf("\n");
    }
}

int countAdjacentMines(int row, int col) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int newRow = row + i;
            int newCol = col + j;
            if (newRow >= 0 && newRow < SIZE && newCol >= 0 && newCol < SIZE && bord[newRow][newCol] == 'X') {
                count++;
            }
        }
    }
    return count;
}

void revealCell(int row, int col) {
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE || displayBoard[row][col] != '?') {
        return;
    }

    displayBoard[row][col] = (bord[row][col] == 'X') ? 'X' : (countAdjacentMines(row, col) + '0');

    if (displayBoard[row][col] == '0') {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                revealCell(row + i, col + j);
            }
        }
    }
}

int snakeWaterGun(char you, char comp){
    // returns 1 if you win, -1 if you lose and 0 if draw
    if(you == comp){
        return 0;
    }
    

    if(you=='s' && comp=='g'){
        return -1;
    }
    else if(you=='g' && comp=='s'){
        return 1;
    }

    if(you=='s' && comp=='w'){
        return 1;
    }
    else if(you=='w' && comp=='s'){
        return -1;
    }

    if(you=='g' && comp=='w'){
        return -1;
    }
    else if(you=='w' && comp=='g'){
        return 1;
    }

}

//Driver code
int main(){
    int a;
    char winner = ' ';
    char response;
    int m, n;
    int row, col;
    int totalCells = SIZE * SIZE - MINES;
    char you, comp;

    printf("---GAME_BOX----");
    printf("\nAvailable games: ");
    printf("\n1. Tic Tac Toe\n2.Snake game\n3.Minesweeper\n4.Snake Water Gun");

    printf("\nGame to play (num) : ");
    scanf("%d",&a);

    switch (a)
    {
    case 1 :
        do
        {
            winner = ' ';
            response = ' ';

            resetBoard();
            
            while(winner == ' ' && checkFreeSpaces() != 0){
                printBoard();
                
                playerMove();
                winner = checkWinner();
                if(winner != ' ' || checkFreeSpaces() == 0){
                break;
                }
            
                computerMove();
                winner = checkWinner();
                if(winner != ' ' || checkFreeSpaces() == 0){
                break;
                }
            }
        
            printBoard();
            printWinner(winner);

            printf("\nWould you like to play again? (Y/N) : ");
            getchar();
            scanf("%c",&response);
            response = toupper(response);
        } while (response == 'Y');

        printf("Thanks for playing!");
        break;
    
    case 2 : 
        setup();

        while (!gameover) {

            draw();
            input();
            logic();
        }
        break;

    case 3 :
        initializeBoard();
        placeMines();

        printf("Welcome to Minesweeper!\n");
        while (1) {
            printBord();

            printf("Enter row and column (e.g., 0 1): ");
            scanf("%d %d", &row, &col);

            if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
                printf("Invalid input. Try again.\n");
                continue;
            }

            if (bord[row][col] == 'X') {
                printf("Game over! You hit a mine.\n");
                break;
            }

            revealCell(row, col);
            totalCells--;

            if (totalCells == 0) {
                printf("Congratulations! You win!\n");
                break;
            }
        }

        printBord();
        break;

    case 4 :
        srand(time(0));
        int number = rand()%100 + 1;

        if(number<33){
            comp = 's';
        }
        else if(number>33 && number<66){
            comp='w';
        }
        else{
            comp='g';
        }
        
        printf("Enter 's' for snake, 'w' for water and 'g' for gun\n");
        getchar();
        scanf("%c", &you);
        snakeWaterGun(you, comp);
        int result = snakeWaterGun(you, comp);
        if(result ==0){
            printf("Game draw!\n");
        }
        else if(result==1){
            printf("You win!\n");
        }
        else{
            printf("You Lose!\n");
        }
        printf("You chose %c and computer chose %c. ", you, comp);
        break;    
    
    default:
        printf("Invalid input!");
        break;
    }
    
    return 0;
}