#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <random>
#include <windows.h>
#include <conio.h>
#define boardHeight 21
#define boardWidth 27

using namespace std;

string randomVoca();
void gotoXY(int x, int y);
void createBoard();
void printBoard();
void printUI();
void printVoca(string voca, char input);

int board[boardHeight][boardWidth] = { 0, };
int Life = 10;

int main()
{
    string voca = randomVoca();

    char input = ' ';
    //cout << randomVoca() << "\n";
    createBoard();

    while (true)
    {
        printBoard();
        printVoca(voca, input);
        
        gotoXY(4 * 2 + 1, boardHeight - 2);
        cout << " : ";
        cin >> input;
    }
    
    
    return 0;
}

string randomVoca()
{
    string temp;
    vector<string> voca;

    ifstream fin;
    fin.open("voca.txt");
    if (!fin.is_open())
    {
        cerr << "Could not open the csv voca file" << "\n";
        return 0;
    }

    int lineCount = 0;
    int vocaStart = 0;
    int vocaEnd = 0;
    int j = 0;
    int size = 0;

    while (getline(fin, temp)) // EOF 때 까지 읽음
    {
        for (int i = 0; i < temp.length(); i++)
        {
            if (temp[i] >= 'a' && temp[i] <= 'z')
            {
                if (vocaStart == 0)
                {
                    vocaStart = i;
                }
                vocaEnd = i;
            }
        }

        if (vocaStart && vocaEnd)
        {
            voca.push_back("");
            for (int i = vocaStart; i <= vocaEnd; i++)
            {
                //voca.push_back("");
                voca[j].push_back(temp[i]);
            }
        }
        //voca[단어장의 line 개수][단어 길이]
        vocaStart = 0;
        vocaEnd = 0;
        j++;
    }

    fin.close();

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, (int)voca.size() - 1); // 단어의 개수 범위에서 랜덤 index 생성

    return voca[dis(gen)];
}

void gotoXY(int x, int y)
{
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void createBoard()
{
    for (int i = 0; i < boardHeight; i++)
    {
        for (int j = 0; j < boardWidth; j++)
        {
            if (i == 0 || i == boardHeight - 1)
            {
                board[i][j] = 1;
            }

            if (j == 0 || j == boardWidth - 1)
            {
                board[i][j] = 1;
            }
        }
    }
}

void printBoard()
{
    for (int i = 0; i < boardHeight; i++)
    {
        gotoXY(0, 1 + i);
        for (int j = 0; j < boardWidth; j++)
        {
            if (board[i][j])
            {
                cout << "▧";
            }
            else
            {
                cout << "  ";
            }
        }
        cout << "\n";
    }

    printUI();
}

void printUI()
{
    gotoXY(2 * 2, 2);
    cout << "Life : ";
    for (int i = 0; i < Life; i++)
    {
        cout << "♥";
    }
    gotoXY(21 * 2, 2);
    cout << "Hang man";
    
    if (Life < 10)
    {
        gotoXY(11 * 2 + 1, 13);
        cout << "─┴─";
    }
    if (Life < 9)
    {
        for (int i = 0; i<7; i++)
        {
            gotoXY(12 * 2, 12-i);
            if (i == 6)
                cout << "┌";
            else
                cout << "│";
        }
    }
    if (Life < 8)
    {
        if (Life > 0)
        {
            gotoXY(12 * 2 + 1, 6);
            cout << "───────";
        }
        else // Life == 0
        {
            gotoXY(12 * 2 + 1, 6);
            cout << "──────┐";
            gotoXY(15 * 2 + 1, 7);
            cout << "│";
            gotoXY(6 * 2 + 1, boardHeight - 3);
            cout << "L O S E ! ! !";

        }
    }
    if (Life < 7)
    {
        gotoXY(15 * 2 + 1, 8);
        cout << "○";
    }
    if (Life < 6)
    {
        for (int i = 0; i < 2; i++)
        {
            gotoXY(15 * 2 + 1, 9 + i);
            cout << "┃";
        }
    }
    if (Life < 5)
    {
        gotoXY(15 * 2, 9);
        cout << "/";
    }
    if (Life < 4)
    {
        gotoXY(16 * 2 + 1, 9);
        cout << "＼";
    }
    if (Life < 3)
    {
        gotoXY(15 * 2, 11);
        cout << "/";
    }
    if (Life < 2)
    {
        gotoXY(16 * 2 + 1, 11);
        cout << "＼";
    }
}

void printVoca(string voca, char input)
{
    static vector<bool> isCorrect(voca.size(), 0);
    bool isFailure = true;
    bool win = true;

    for (int i = 0; i < voca.size(); i++) // input이 들어 왔을 때, input과 맞는 알파벳이 있는지 확인
    {
        if (input == voca[i])
        {
            isCorrect[i] = true;
            isFailure = false;
        }
    }

    if (isFailure)
    {
        Life--;
    }

    gotoXY(6 * 2 + 1, boardHeight - 4);

    for (int i = 0; i < voca.size(); i++)
    {
        if (isCorrect[i])
        {
            cout << voca[i] << "  ";
        }
        else
        {
            cout << "__  ";
        }
    }

    for (int i = 0; i < voca.size(); i++)
    {
        win &= isCorrect[i];
    }

    if (win)
    {
        gotoXY(6 * 2 + 1, boardHeight - 3);
        cout << "W i n ! ! !";
    }


}