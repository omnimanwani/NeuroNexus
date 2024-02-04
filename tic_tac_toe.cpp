#include <iostream>
#include <vector>

using namespace std;

void initialize_board(vector<vector<char>> &board)
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
    }
}

void display_board(const vector<vector<char>> &board)
{
    cout << "-------------\n";
    for (int i = 0; i < 3; ++i)
    {
        cout << "| ";
        for (int j = 0; j < 3; j++)
            cout << board[i][j] << " | ";
        cout << "\n-------------\n";
    }
}

bool play_chance(vector<vector<char>> &board, char player, int position)
{
    if (position < 1 || position > 9)
        return false;

    int row = (position - 1) / 3;
    int col = (position - 1) % 3;

    if (board[row][col] != ' ')
        return false;

    board[row][col] = player;
    return true;
}

bool check_for_win(const vector<vector<char>> &board, char player)
{
    for (int i = 0; i < 3; i++)
    {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player))
            return true;
    }

    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player))
        return true;

    return false;
}

bool check_for_draw(const vector<vector<char>> &board)
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
                return false;
        }
    }
    return true;
}

char switch_player(char curr)
{
    return (curr == 'X') ? 'O' : 'X';
}

bool play_again()
{
    char choice;
    cout << "Do you want to play again? (y/n): ";
    cin >> choice;
    return (choice == 'y' || choice == 'Y');
}

int main()
{
    vector<vector<char>> board(3, vector<char>(3, ' '));
    char curr = 'X';

    do
    {
        initialize_board(board);
        bool won = false;
        bool draw = false;
        cout << "\n\n--POSITIONS--\n";    
        cout << "-------------\n";
        int k = 1;

        for (int i = 0; i < 3; ++i)
        {
            cout << "| ";
            for (int j = 0; j < 3; j++)
                cout << k++ << " | ";
            cout << "\n-------------\n";
        }

        do
        {
            if(k++!=10)
                display_board(board);
            int position;
            cout << "Player " << curr << ", enter your move (position 1-9): ";
            cin >> position;

            if (play_chance(board, curr, position))
            {
                won = check_for_win(board, curr);
                draw = check_for_draw(board);
                curr = switch_player(curr);
            }
            else
                cout << "Invalid move. Try again.\n";

        } while (!won && !draw);

        display_board(board);

        if (won)
            cout << "Player " << switch_player(curr) << " wins!\n";
        else
            cout << "It's a draw!\n";

    } while (play_again());

    cout << "Thanks for playing!\n";

    return 0;
}