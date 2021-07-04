#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
// game state
bool gameOver;
// width of the game
const int width = 20;
const int height = 20;
// defines basic integer variables
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
// states the direction of the snake using 'dir'
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirecton dir;
// is called once when the game starts in the main() function
void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}
// draws the game
void Draw()
{
    // clears the game
    system("cls"); 
    // prints the top wall
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
    // prints the side walls
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#";
            // prints the snake's head
            if (i == y && j == x)
                cout << "O";
            // prints the fruit
            else if (i == fruitY && j == fruitX)
                cout << "F";
            else
            {
                bool print = false;
                // prints the snakes 'tails'
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }
            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }
    // prints the bottom wall
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
    cout << "Score:" << score << endl;
}
/* for input purposes changes the value of 'dir' when 
a, d, w and s is pressed and when x is pressed ends the game */
void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}
// makes the 'tails' follow the head of the snake
void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    // switch's the direction of the snake by decrementing and incrementing the x and y values
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
    // ends the game when the snake collides with a wall
    //if (x > width || x < 0 || y > height || y < 0)
    //  gameOver = true;
    // makes the snake appear on the opposite wall when colliding with a wall
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;

    // if any of the 'tails' are in the same position as the head of the snake the game ends
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    /* if the head of the snake is in the same position as the fruit, the fruit is placed in a 
    random new position within the width and height and the number of 'tails' is incremented */
    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}
/* the main function and calls the setup function and other functions whilst 
the game is not over and calls the sleep method slow down the snake */
int main()
{
    Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep(10); //sleep(10);
    }
    return 0;
}