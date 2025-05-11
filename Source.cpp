// 1 
// Memory Game in C++

//#include <iostream>
//#include <vector>
//#include <algorithm>
//#include <ctime>
//#include <cstdlib>
//#include <thread>
//#include <chrono>
//
//using namespace std;
//
//class Card {
//public:
//    char symbol;
//    bool isRevealed;
//    bool isMatched;
//
//    Card(char s) : symbol(s), isRevealed(false), isMatched(false) {}
//};
//
//class MemoryGame {
//private:
//    vector<vector<Card>> board;
//    int size;
//    int matchedPairs;
//
//public:
//
//    // Setters
//	void setSize(int boardSize) {
//		size = boardSize;
//	}
//
//	// Getters
//	int getSize() const
//	{
//		return size;
//	}
//
//    MemoryGame(int boardSize) : size(boardSize), matchedPairs(0) {
//        generateBoard();
//    }
//
//    void generateBoard() {
//        vector<char> symbols;
//        for (char c = 'A'; c < 'A' + (size * size) / 2; ++c) {
//            symbols.push_back(c);
//            symbols.push_back(c);
//        }
//        random_shuffle(symbols.begin(), symbols.end());
//
//        int index = 0;
//        board.resize(size, vector<Card>(size, Card(' ')));
//        for (int i = 0; i < size; ++i)
//            for (int j = 0; j < size; ++j)
//                board[i][j] = Card(symbols[index++]);
//                
//    }
//
//    void printBoard(bool fullBoard = false) {
//        cout << "   ";
//        for (int j = 0; j < size; j++)
//            cout << j+1 << " ";
//        cout << "\n";
//
//		if (fullBoard) {
//            for (int i = 0; i < size; ++i) {
//                cout << i+1 << "  ";
//                for (int j = 0; j < size; ++j) {
//                	cout << "\033[1;32m" << board[i][j].symbol << "\033[0m ";
//                }
//                cout << "\n";
//            }
//		}
//
//		if (fullBoard) {
//			cout << "\n";
//			return;
//		}
//
//        for (int i = 0; i < size; ++i) {
//            cout << i+1 << "  ";
//            for (int j = 0; j < size; ++j) {
//                if (board[i][j].isRevealed || board[i][j].isMatched)
//                    cout << "\033[1;32m" << board[i][j].symbol << "\033[0m ";
//                else
//                    cout << "* ";
//            }
//            cout << "\n";
//        }
//    }
//
//    bool isFinished() {
//        return matchedPairs == (size * size) / 2;
//    }
//
//    void play() {
//        while (!isFinished()) {
//            printBoard();
//            int x1, y1, x2, y2;
//
//            while (true)
//            {
//                cout << "Введіть координати першої картки (x y): ";
//                cin >> x1 >> y1;
//				if (cin.fail()) {
//					cout << "\033[031m Помилка! Будь ласка, введіть число.\033[0m\n";
//					cin.clear();
//					cin.ignore(1000, '\n');
//				}
//				if (x1 < 1 || x1 > size || y1 < 1 || y1 > size) {
//					cout << "Некоректні координати. Спробуйте ще.\n";
//					continue;
//				}
//				x1--; y1--;
//				break;
//            }
//           
//
//            if (!isValid(x1, y1)) {
//                cout << "Некоректні координати. Спробуйте ще.\n";
//                continue;
//            }
//
//            board[x1][y1].isRevealed = true;
//            printBoard();
//
//            cout << "Введіть координати другої картки (x y): ";
//            while (true)
//            {
//				cin >> x2 >> y2;
//				if (cin.fail()) {
//					cout << "\033[031m Помилка! Будь ласка, введіть число.\033[0m\n";
//					cin.clear();
//					cin.ignore(1000, '\n');
//				}
//				if (x2-1 == x1 && y2-1 == y1) {
//					cout << "Ви не можете вибрати ту ж саму картку. Спробуйте ще.\n";
//					continue;
//				}
//				if (x2 < 1 || x2 > size || y2 < 1 || y2 > size) {
//					cout << "Некоректні координати. Спробуйте ще.\n";
//					continue;
//				}
//				x2--; y2--;
//				break;
//            }
//            
//
//            if (!isValid(x2, y2) || (x1 == x2 && y1 == y2)) {
//                cout << "Некоректні координати. Спробуйте ще.\n";
//                board[x1][y1].isRevealed = false;
//                continue;
//            }
//
//            board[x2][y2].isRevealed = true;
//            printBoard();
//
//            if (board[x1][y1].symbol == board[x2][y2].symbol) {
//                cout << "Пара знайдена!\n";
//                board[x1][y1].isMatched = true;
//                board[x2][y2].isMatched = true;
//                matchedPairs++;
//            }
//            else {
//                cout << "Не збіглося. Закриття через 2 секунди...\n";
//                std::this_thread::sleep_for(std::chrono::seconds(2));
//                board[x1][y1].isRevealed = false;
//                board[x2][y2].isRevealed = false;
//            }
//
//            cout << "\n";
//        }
//
//        cout << "🎉 Вітаємо! Ви знайшли всі пари!\n";
//    }
//
//    bool isValid(int x, int y) {
//        return x >= 0 && x < size && y >= 0 && y < size && !board[x][y].isMatched && !board[x][y].isRevealed;
//    }
//
//
//};
//
//
//int main() {
//    system("chcp 65001 > nul");
//    srand(time(0));
//	cout << "Ласкаво просимо до гри 'Memory'!\n";
//	cout << "Грайте, щоб знайти всі пари карток!\n";
//	cout << "Виберіть розмір дошки (2, 4, 6, 8): ";
//	int boardSize;
//    while (true)
//    {
//        cin >> boardSize;
//
//        if (cin.fail()) {
//            cout << "\033[031m Помилка! Будь ласка, введіть число.\033[0m\n";
//            cin.clear(); 
//            cin.ignore(1000, '\n');
//        }
//
//
//        if (boardSize != 2 && boardSize != 4 && boardSize != 6 && boardSize != 8) {
//            cout << "Некоректний розмір дошки. Використовується розмір 4.\n";
//            continue;
//        }
//        
//        break;
//    }
//    MemoryGame game(boardSize);
//	cout << "У вас " << (boardSize * boardSize) / 2 << " пар карток.\n";
//	cout << "Гра починається...\n";
//    std::this_thread::sleep_for(chrono::milliseconds(3000));
//    cout << "У вас є 10 секунд на запам'ятовування: " << endl;
//    game.printBoard(true);
//    std::this_thread::sleep_for(chrono::milliseconds(1000));
//
//    game.play();
//    return 0;
//}


// 2
//

//#include <iostream>
//#include <vector>
//#include <string>
//#include <thread>
//#include <mutex>
//#include <condition_variable>
//#include <random>
//#include <ctime>
//#include <algorithm>
//
//using namespace std;
//


#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <random>
#include <map>
#include <ctime>
#include <unordered_map>
#include <algorithm>
#include <cctype>

using namespace std;

vector<string> ukrainian = {
    "яблуко", "собака", "кіт", "будинок", "машина", "вікно", "стілець", "стіл", "ручка", "книга",
    "молоко", "вода", "хліб", "м'ясо", "риба", "чай", "кава", "цукор", "сіль", "масло",
    "мама", "тато", "брат", "сестра", "дитина", "школа", "учень", "вчитель", "дошка", "зошит",
    "робота", "магазин", "місто", "село", "двері", "телефон", "ноутбук", "дерево", "квітка", "сонце",
    "місяць", "зірка", "небо", "дощ", "сніг", "вітер", "тепло", "холод", "весна", "літо",
    "осінь", "зима", "бігати", "ходити", "плавати", "летіти", "сидіти", "стояти", "читати", "писати",
    "говорити", "слухати", "бачити", "думати", "любити", "ненавидіти", "їсти", "пити", "спати", "вставати",
    "добрий", "поганий", "великий", "малий", "новий", "старий", "гарячий", "холодний", "швидкий", "повільний",
    "розумний", "дурний", "красивий", "потворний", "веселий", "сумний", "легкий", "важкий", "чистий", "брудний",
    "червоний", "жовтий", "зелений", "синій", "білий", "чорний", "сірий", "коричневий", "оранжевий", "рожевий",
    "один", "два", "три", "чотири", "п’ять", "шість", "сім", "вісім", "дев’ять", "десять",
    "понеділок", "вівторок", "середа", "четвер", "п’ятниця", "субота", "неділя", "день", "ніч", "ранок",
    "вечір", "сьогодні", "завтра", "вчора", "час", "рік", "місяць", "тиждень", "година", "хвилина",
    "секунда", "дорога", "вулиця", "площа", "море", "річка", "гора", "ліс", "парк", "пляж"
};

vector<string> french = {
    "pomme", "chien", "chat", "maison", "voiture", "fenêtre", "chaise", "table", "stylo", "livre",
    "lait", "eau", "pain", "viande", "poisson", "thé", "café", "sucre", "sel", "beurre",
    "maman", "papa", "frère", "sœur", "enfant", "école", "élève", "professeur", "tableau", "cahier",
    "travail", "magasin", "ville", "village", "porte", "téléphone", "ordinateur", "arbre", "fleur", "soleil",
    "lune", "étoile", "ciel", "pluie", "neige", "vent", "chaleur", "froid", "printemps", "été",
    "automne", "hiver", "courir", "marcher", "nager", "voler", "s’asseoir", "se tenir", "lire", "écrire",
    "parler", "écouter", "voir", "penser", "aimer", "détester", "manger", "boire", "dormir", "se lever",
    "bon", "mauvais", "grand", "petit", "nouveau", "vieux", "chaud", "froid", "rapide", "lent",
    "intelligent", "stupide", "beau", "laid", "joyeux", "triste", "facile", "difficile", "propre", "sale",
    "rouge", "jaune", "vert", "bleu", "blanc", "noir", "gris", "marron", "orange", "rose",
    "un", "deux", "trois", "quatre", "cinq", "six", "sept", "huit", "neuf", "dix",
    "lundi", "mardi", "mercredi", "jeudi", "vendredi", "samedi", "dimanche", "jour", "nuit", "matin",
    "soir", "aujourd’hui", "demain", "hier", "temps", "année", "mois", "semaine", "heure", "minute",
    "seconde", "route", "rue", "place", "mer", "rivière", "montagne", "forêt", "parc", "plage"
};

vector<string> english = {
    "apple", "dog", "cat", "house", "car", "window", "chair", "table", "pen", "book",
    "milk", "water", "bread", "meat", "fish", "tea", "coffee", "sugar", "salt", "butter",
    "mom", "dad", "brother", "sister", "child", "school", "student", "teacher", "board", "notebook",
    "work", "store", "city", "village", "door", "phone", "laptop", "tree", "flower", "sun",
    "moon", "star", "sky", "rain", "snow", "wind", "warmth", "cold", "spring", "summer",
    "autumn", "winter", "run", "walk", "swim", "fly", "sit", "stand", "read", "write",
    "speak", "listen", "see", "think", "love", "hate", "eat", "drink", "sleep", "wake up",
    "good", "bad", "big", "small", "new", "old", "hot", "cold", "fast", "slow",
    "smart", "stupid", "beautiful", "ugly", "happy", "sad", "easy", "hard", "clean", "dirty",
    "red", "yellow", "green", "blue", "white", "black", "gray", "brown", "orange", "pink",
    "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten",
    "monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday", "day", "night", "morning",
    "evening", "today", "tomorrow", "yesterday", "time", "year", "month", "week", "hour", "minute",
    "second", "road", "street", "square", "sea", "river", "mountain", "forest", "park", "beach"
};


int getRandomIndex(int size) {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> dis(0, size - 1);
    return dis(gen);
}

string strip(const string& s) {
    auto start = find_if_not(s.begin(), s.end(), ::isspace);
    auto end = find_if_not(s.rbegin(), s.rend(), ::isspace).base();
    return (start < end) ? string(start, end) : "";
}

string toLower(const string& s) {
    string result = s;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

string convertString(string& str) {
	return strip(toLower(str));
}

class MistakeManager {
public:
    map<string, int> mistakes;

    void addMistake(const string& word) {
        mistakes[word]++;
    }

    void showMistakes() {
        cout << "\nНеправильні відповіді:\n";
        for (const auto& [word, count] : mistakes) {
            cout << word << " — " << count << " раз(ів)\n";
        }
    }
};

class WordTrainer {
    vector<string>& from;
    vector<string>& to;
    MistakeManager& mistakeManager;

public:
    WordTrainer(vector<string>& fromLang, vector<string>& toLang, MistakeManager& mm)
        : from(fromLang), to(toLang), mistakeManager(mm) {
    }

    void startTraining(int rounds = 5) {
        for (int i = 0; i < rounds; ++i) {
            int idx = getRandomIndex(from.size());
            string answer;
            cout << "Перекладіть слово: " << from[idx] << " → ";
            getline(cin, answer);
            if (convertString(answer) == to[idx]) {
                cout << "✔  Правильно!\n";
            }
            else {
                cout << "✖  Неправильно. Правильна відповідь: " << to[idx] << "\n";
                mistakeManager.addMistake(from[idx]);
            }
        }
    }
};

class GameEngine {
    MistakeManager mistakeManager;
	WordTrainer trainer;

public:
	GameEngine(WordTrainer& word_trainer) : trainer(word_trainer) {
	}
    void run() {
        trainer.startTraining();
        mistakeManager.showMistakes();
    }
};

int main() {
    system("chcp 65001 > nul");
    MistakeManager mistakeManager;

    unordered_map<string, unique_ptr<WordTrainer>> trainers;

    trainers["ukrainian-french"] = make_unique<WordTrainer>(ukrainian, french, mistakeManager);
    trainers["french-ukrainian"] = make_unique<WordTrainer>(french, ukrainian, mistakeManager);
    trainers["ukrainian-english"] = make_unique<WordTrainer>(ukrainian, english, mistakeManager);
    trainers["english-ukrainian"] = make_unique<WordTrainer>(english, ukrainian, mistakeManager);
    trainers["french-english"] = make_unique<WordTrainer>(french, english, mistakeManager);
    trainers["english-french"] = make_unique<WordTrainer>(english, french, mistakeManager);

    GameEngine game(*trainers["ukrainian-english"]);


    thread gameThread(&GameEngine::run, &game);
    gameThread.join();
    return 0;
}

