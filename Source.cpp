#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <chrono>

using namespace std;

class Card {
public:
    char symbol;
    bool isRevealed;
    bool isMatched;

    Card(char s) : symbol(s), isRevealed(false), isMatched(false) {}
};

class MemoryGame {
private:
    vector<vector<Card>> board;
    int size;
    int matchedPairs;

public:

    // Setters
	void setSize(int boardSize) {
		size = boardSize;
	}

	// Getters
	int getSize() const
	{
		return size;
	}

    MemoryGame(int boardSize) : size(boardSize), matchedPairs(0) {
        generateBoard();
    }

    void generateBoard() {
        vector<char> symbols;
        for (char c = 'A'; c < 'A' + (size * size) / 2; ++c) {
            symbols.push_back(c);
            symbols.push_back(c);
        }
        random_shuffle(symbols.begin(), symbols.end());

        int index = 0;
        board.resize(size, vector<Card>(size, Card(' ')));
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                board[i][j] = Card(symbols[index++]);
                
    }

    void printBoard(bool fullBoard = false) {
        cout << "   ";
        for (int j = 0; j < size; j++)
            cout << j+1 << " ";
        cout << "\n";

		if (fullBoard) {
            for (int i = 0; i < size; ++i) {
                cout << i+1 << "  ";
                for (int j = 0; j < size; ++j) {
                	cout << "\033[1;32m" << board[i][j].symbol << "\033[0m ";
                }
                cout << "\n";
            }
		}

		if (fullBoard) {
			cout << "\n";
			return;
		}

        for (int i = 0; i < size; ++i) {
            cout << i+1 << "  ";
            for (int j = 0; j < size; ++j) {
                if (board[i][j].isRevealed || board[i][j].isMatched)
                    cout << "\033[1;32m" << board[i][j].symbol << "\033[0m ";
                else
                    cout << "* ";
            }
            cout << "\n";
        }
    }

    bool isFinished() {
        return matchedPairs == (size * size) / 2;
    }

    void play() {
        while (!isFinished()) {
            printBoard();
            int x1, y1, x2, y2;

            while (true)
            {
                cout << "Введіть координати першої картки (x y): ";
                cin >> x1 >> y1;
				if (cin.fail()) {
					cout << "\033[031m Помилка! Будь ласка, введіть число.\033[0m\n";
					cin.clear();
					cin.ignore(1000, '\n');
				}
				if (x1 < 1 || x1 > size || y1 < 1 || y1 > size) {
					cout << "Некоректні координати. Спробуйте ще.\n";
					continue;
				}
				x1--; y1--;
				break;
            }
           

            if (!isValid(x1, y1)) {
                cout << "Некоректні координати. Спробуйте ще.\n";
                continue;
            }

            board[x1][y1].isRevealed = true;
            printBoard();

            cout << "Введіть координати другої картки (x y): ";
            while (true)
            {
				cin >> x2 >> y2;
				if (cin.fail()) {
					cout << "\033[031m Помилка! Будь ласка, введіть число.\033[0m\n";
					cin.clear();
					cin.ignore(1000, '\n');
				}
				if (x2-1 == x1 && y2-1 == y1) {
					cout << "Ви не можете вибрати ту ж саму картку. Спробуйте ще.\n";
					continue;
				}
				if (x2 < 1 || x2 > size || y2 < 1 || y2 > size) {
					cout << "Некоректні координати. Спробуйте ще.\n";
					continue;
				}
				x2--; y2--;
				break;
            }
            

            if (!isValid(x2, y2) || (x1 == x2 && y1 == y2)) {
                cout << "Некоректні координати. Спробуйте ще.\n";
                board[x1][y1].isRevealed = false;
                continue;
            }

            board[x2][y2].isRevealed = true;
            printBoard();

            if (board[x1][y1].symbol == board[x2][y2].symbol) {
                cout << "Пара знайдена!\n";
                board[x1][y1].isMatched = true;
                board[x2][y2].isMatched = true;
                matchedPairs++;
            }
            else {
                cout << "Не збіглося. Закриття через 2 секунди...\n";
                std::this_thread::sleep_for(std::chrono::seconds(2));
                board[x1][y1].isRevealed = false;
                board[x2][y2].isRevealed = false;
            }

            cout << "\n";
        }

        cout << "🎉 Вітаємо! Ви знайшли всі пари!\n";
    }

    bool isValid(int x, int y) {
        return x >= 0 && x < size && y >= 0 && y < size && !board[x][y].isMatched && !board[x][y].isRevealed;
    }


};


int main() {
    system("chcp 65001 > nul");
    srand(time(0));
	cout << "Ласкаво просимо до гри 'Memory'!\n";
	cout << "Грайте, щоб знайти всі пари карток!\n";
	cout << "Виберіть розмір дошки (2, 4, 6, 8): ";
	int boardSize;
    while (true)
    {
        cin >> boardSize;

        if (cin.fail()) {
            cout << "\033[031m Помилка! Будь ласка, введіть число.\033[0m\n";
            cin.clear(); 
            cin.ignore(1000, '\n');
        }


        if (boardSize != 2 && boardSize != 4 && boardSize != 6 && boardSize != 8) {
            cout << "Некоректний розмір дошки. Використовується розмір 4.\n";
            continue;
        }
        
        break;
    }
    MemoryGame game(boardSize);
	cout << "У вас " << (boardSize * boardSize) / 2 << " пар карток.\n";
	cout << "Гра починається...\n";
    std::this_thread::sleep_for(chrono::milliseconds(3000));
    cout << "У вас є 10 секунд на запам'ятовування: " << endl;
    game.printBoard(true);
    std::this_thread::sleep_for(chrono::milliseconds(1000));

    game.play();
    return 0;
}

