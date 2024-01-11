#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void print_board(char board[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << "|";
            if (board[i][j] == 'x') {
                cout << " X ";
            } else if (board[i][j] == 'o') {
                cout << " O ";
            } else {
                cout << "   ";
            }
        }
        cout << "|" << endl;
        if (i < 2) {
            cout << "-------------" << endl;
        }
    }
}

bool is_board_full(char board[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

bool check_win(char board[3][3], char player) {
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
            return true;
        }
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) {
            return true;
        }
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
        return true;
    }
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
        return true;
    }
    return false;
}

void get_player_move(char board[3][3], int& row, int& col, char player) {
    int move;
    cout << "Player " << player << ", enter position (1-9): ";
    cin >> move;
    if (move >= 1 && move <= 9) {
        row = (move - 1) / 3;
        col = (move - 1) % 3;
    } else {
        cout << "Invalid move. Try again." << endl;
        get_player_move(board, row, col, player);
    }
}

void get_ai_move(char board[3][3], int& row, int& col) {
    cout << "AI is making a move..." << endl;
    do {
        row = rand() % 3;
        col = rand() % 3;
    } while (board[row][col] != ' ');
}

bool ask_to_continue() {
    char choice;
    cout << "Do you want to continue (y/n)? ";
    cin >> choice;
    return (choice == 'y' || choice == 'Y');
}

void clear_screen_alternative() {
    system("clear || cls");
}

int main() {
    int choice;
    bool welcomePrinted = false;

    do {
        if (!welcomePrinted) {
            cout << "\t\t\t\tHello everyone     " << endl;
            cout << "\t\t\t ****************************" << endl;
            cout << endl << endl;
            cout << "\t\t\t     WELCOME TO TIC TAC TOE   " << endl;
            cout << "\t\t\t ****************************** " << endl;

            welcomePrinted = true;
        }

        cout << endl;
        cout << "Enter your choice:" << endl;
        cout << "1 for Single Player" << endl;
        cout << "2 for Multiplayer" << endl;
        cout << "3 to exit the game" << endl;
        cout << "Enter here: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
                char current_player;
                int row, col;
                bool game_over;
                int player_x_wins = 0;
                int player_o_wins = 0;

                srand(time(0));

                do {
                    current_player = 'x';
                    game_over = false;

                    while (!game_over) {
                        print_board(board);
                        if (is_board_full(board)) {
                            cout << "The board is full! It's a draw." << endl;
                            break;
                        }

                        if (current_player == 'x') {
                            get_player_move(board, row, col, current_player);
                        } else {
                            get_ai_move(board, row, col);
                        }

                        if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
                            board[row][col] = current_player;

                            if (check_win(board, current_player)) {
                                clear_screen_alternative();
                                print_board(board);
                                cout << "Player " << current_player << " wins!" << endl;
                                if (current_player == 'x') {
                                    player_x_wins++;
                                } else {
                                    player_o_wins++;
                                }
                                cout << "\n\nFinal Score - Player X: " << player_x_wins << " | Player O: " << player_o_wins << endl;
                                game_over = !ask_to_continue();
                                if (!game_over) {
                                    for (int i = 0; i < 3; ++i) {
                                        for (int j = 0; j < 3; ++j) {
                                            board[i][j] = ' ';
                                        }
                                    }
                                }
                            } else {
                                if (current_player == 'x') {
                                    current_player = 'o';
                                } else {
                                    current_player = 'x';
                                }
                            }
                        } else {
                            cout << "Invalid move. Try again." << endl;
                        }
                    }

                } while (!game_over);

                break;
            }
            case 2: {
                char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
                char current_player;
                int row, col;
                bool game_over;
                int player_x_wins = 0;
                int player_o_wins = 0;

                do {
                    current_player = 'x';
                    game_over = false;

                    while (!game_over) {
                        for (int i = 0; i < 3; ++i) {
                            for (int j = 0; j < 3; ++j) {
                                cout << "|";
                                cout << (board[i][j] == ' ' ? '_' : board[i][j]);
                            }
                            cout << "|" << endl;
                            cout << "___" << endl;
                        }

                        if (current_player == 'x') {
                            get_player_move(board, row, col, current_player);
                        } else {
                            get_player_move(board, row, col, current_player);
                        }

                        if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
                            board[row][col] = current_player;

                            if ((board[0][0] == current_player && board[1][1] == current_player && board[2][2] == current_player) ||
                                (board[0][2] == current_player && board[1][1] == current_player && board[2][0] == current_player) ||
                                (board[row][0] == current_player && board[row][1] == current_player && board[row][2] == current_player) ||
                                (board[0][col] == current_player && board[1][col] == current_player && board[2][col] == current_player)) {
                                clear_screen_alternative();
                                cout << "Player " << current_player << " wins!" << endl;
                                game_over = !ask_to_continue();
                                if (!game_over) {
                                    for (int i = 0; i < 3; ++i) {
                                        for (int j = 0; j < 3; ++j) {
                                            board[i][j] = ' ';
                                        }
                                    }
                                }
                            } else {
                                current_player = (current_player == 'x') ? 'o' : 'x';
                                bool is_draw = true;
                                for (int i = 0; i < 3; ++i) {
                                    for (int j = 0; j < 3; ++j) {
                                        if (board[i][j] == ' ') {
                                            is_draw = false;
                                            break;
                                        }
                                    }
                                    if (!is_draw) {
                                        break;
                                    }
                                }
                                if (is_draw) {
                                    cout << "It's a draw! You both played well; You should try once again " << endl;
                                    game_over = !ask_to_continue();
                                    if (!game_over) {
                                        clear_screen_alternative();
                                        for (int i = 0; i < 3; ++i) {
                                            for (int j = 0; j < 3; ++j) {
                                                board[i][j] = ' ';
                                            }
                                        }
                                    }
                                }
                            }
                        } else {
                            cout << "Invalid move. The position is already taken. Try again." << endl;
                        }
                    }

                } while (!game_over);

                break;
            }
            case 3: {
                cout << "You exit the game." << endl;
                cout << "Goodbye, have a good day!" << endl;
                break;
            }
            default:
                cout << "Invalid choice. Enter valid choice." << endl;
        }
    } while (choice != 3);

    return 0;
}
