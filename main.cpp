#include "src/Trie.h";

void getAndInsertTrieData(Trie &trie);
void clearTerminal();
bool programOptions();
void readWord(Trie &trie);

int main() {
    Trie trie;
    clearTerminal();
    getAndInsertTrieData(trie);
    clearTerminal();

    bool choice;

    do {
        choice = programOptions();

        if (choice) {
            readWord(trie);
        }

    } while (choice);


    return 0;
}

/**
 * @brief Get data from a file and insert those data in a Trie object
 * 
 * @param trie Reference to the Trie object
 */
void getAndInsertTrieData(Trie &trie) {
    int choice;

    do {
        std::cout << " --- Options --- " << std::endl;
        std::cout << " (2) - English Words." << std::endl;
        std::cout << " (1) - Portuguese Words." << std::endl;
        std::cout << " (0) - Exit." << std::endl;
        std::cout << " Your choice: ";
        std::cin >> choice;
    } while(choice < 0 && choice > 2);

    if (choice == 0)
        exit(0);

    std::string fileName = choice == 2 ? "englishWordsMIT" : "portugueseWordsWithoutSpecialCharacters";
    std::string filePath = "data/" + fileName + ".txt";

    std::ifstream file(filePath);

    if (file.is_open()) {
        std::string lineData;
        
        while (getline(file, lineData))
            trie.Insert(lineData);
        
        file.close();
    } else {
        std::cout << "ERROR ! Can't open the file" << std::endl;
        exit(1);
    }
}

/**
 * @brief Clears the terminal window
 * 
 */
void clearTerminal() {
    #if defined(_WIN32)
        system("cls");
    #elif defined(__linux__)
        system("clear");
    #elif defined(__APPLE__)
        system("clear");
    #endif
}

/**
 * @brief Options for user
 * 
 * @return True if choice equals 1 and False if choice equals 0 
 */
bool programOptions() {
    int choice;
    do {
        std::cout << " --- Options --- " << std::endl;
        std::cout << " Press (1) to verify a word." << std::endl;
        std::cout << " Press (0) to exit." << std::endl;
        std::cout << " Your choice: ";
        std::cin >> choice;
    } while(choice != 0 && choice != 1);

    clearTerminal();

    return choice;
}

/**
 * @brief Get user input
 * 
 * @param trie Reference to the Trie object
 */
void readWord(Trie &trie) {
    std::string word;

    std::cout << "Look for a word: ";
    std::cin >> word;

    trie.VerifyWord(word);
}
