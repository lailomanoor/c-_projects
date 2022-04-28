#include <iostream>
#include <stdlib.h>
using namespace std;

class tictactoe
{
    int arr[3][3];   // keeps track of which player has placed a move at each poition
    char disp[3][3]; // only meant for display. shows the position number if no move placed there, or O or X if move has been placed

public:
    tictactoe()
    {
        int k = 1;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++, k++)
            {
                arr[i][j] = 0;
                disp[i][j] = k + 48; // converting from int to char
            }
        }
    }
    void display()
    {
        cout << "  " << disp[0][0] << "  |  " << disp[0][1] << "  |  " << disp[0][2] << "  " << endl;
        cout << "-----|-----|-----" << endl;
        cout << "  " << disp[1][0] << "  |  " << disp[1][1] << "  |  " << disp[1][2] << "  " << endl;
        cout << "-----|-----|-----" << endl;
        cout << "  " << disp[2][0] << "  |  " << disp[2][1] << "  |  " << disp[2][2] << "  " << endl;
    }

    void move(int player, int opt)
    {
        char ch;
        if (player == 1)
            ch = 'X';
        else if (player == 2)
            ch = 'O';

        switch (opt)
        {
        case 1:
            arr[0][0] = player;
            disp[0][0] = ch;
            break;
        case 2:
            arr[0][1] = player;
            disp[0][1] = ch;
            break;
        case 3:
            arr[0][2] = player;
            disp[0][2] = ch;
            break;
        case 4:
            arr[1][0] = player;
            disp[1][0] = ch;
            break;
        case 5:
            arr[1][1] = player;
            disp[1][1] = ch;
            break;
        case 6:
            arr[1][2] = player;
            disp[1][2] = ch;
            break;
        case 7:
            arr[2][0] = player;
            disp[2][0] = ch;
            break;
        case 8:
            arr[2][1] = player;
            disp[2][1] = ch;
            break;
        case 9:
            arr[2][2] = player;
            disp[2][2] = ch;
            break;
        }
    }

    int istaken(int opt) // returns 0 if a certain position is empty
    {
        switch (opt)
        {
        case 1:
            return arr[0][0];
            break;
        case 2:
            return arr[0][1];
            break;
        case 3:
            return arr[0][2];
            break;
        case 4:
            return arr[1][0];
            break;
        case 5:
            return arr[1][1];
            break;
        case 6:
            return arr[1][2];
            break;
        case 7:
            return arr[2][0];
            break;
        case 8:
            return arr[2][1];
            break;
        case 9:
            return arr[2][2];
            break;
        }
    }

    void player1()
    {
        int opt;

        while (1)
        {
            cout << "PLAYER 1: enter your option\n";
            cin >> opt;

            if (opt > 9 || opt < 1)
                cout << "enter valid option\n";
            else if (!istaken(opt))
            {
                move(1, opt); // places move at position entered by user for player 1
                break;
            }
            else
                cout << "choose an empty space\n";
        }
    }

    void player2()
    {
        int opt;
        while (1)
        {
            cout << "PLAYER 2: enter your option\n";
            cin >> opt;

            if (opt > 9 || opt < 1)
                cout << "enter valid option\n";
            else if (!istaken(opt))
            {
                move(2, opt); // places move at positon entered by user for player 2
                break;
            }
            else
                cout << "choose an empty space\n";
        }
    }

    int iswon()
    {
        for (int i = 0; i < 3; i++)
        {
            if (arr[0][i] == arr[1][i] && arr[1][i] == arr[2][i] && arr[0][i] != 0) // checks vertical lines
            {
                cout << "\n\nPLAYER " << arr[0][i] << " WINS THE GAME\n";
                return arr[0][i];
            }
            else if (arr[i][0] == arr[i][1] && arr[i][1] == arr[i][2] && arr[i][0] != 0) // cehcks horizontal lines
            {
                cout << "\n\nPLAYER " << arr[i][0] << " WINS THE GAME\n";
                return arr[i][0];
            }
        }

        if (arr[0][0] == arr[1][1] && arr[1][1] == arr[2][2] && arr[0][0] != 0) // checks first diagnol
        {
            cout << "\n\nPLAYER " << arr[0][0] << " WINS THE GAME\n";
            return arr[0][0];
        }

        if (arr[0][2] == arr[1][1] && arr[1][1] == arr[2][0] && arr[1][1] != 0) // checks second diagnol
        {
            cout << "\n\nPLAYER " << arr[1][1] << " WINS THE GAME\n";
            return arr[1][1];
        }

        return 0;
    }

    bool isdraw()
    {
        if (!iswon()) //  can only be draw if no one has won the game yet
        {
            int count = 0;
            for (int i = 1; i <= 9; i++)
                if (istaken(i))
                    count++;

            if (count == 9) // if all positions are filled
            {
                cout << "GAME OVER. DRAW\n";
                return 1;
            }
            else
                return 0;
        }

        return 0;
    }

    void play()
    {
        cout << "\n\nPLAYER 1: X\nPLAYER 2: O\n\n";

        while (1)
        {
            display();
            player1();

            if (iswon() || isdraw())
                break;

            display();
            player2();

            if (iswon() || isdraw())
                break;
        }

        display();
    }
};

int main()
{
    tictactoe game;
    game.play();

    system("pause");

    return 0;
}
