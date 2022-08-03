#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <fstream>
#include <string>
#include <list>

// Number of caracters
#define SIZE_LIST 28

/**
 * @brief Compact Trie works as Spell Checker.
 * 
 */
class Trie {
private:
    
    /**
     * @brief Trie's node.
     * 
     */
    class Node {
    public:

        // List of pointers to nullptr or to another node
        Node *pointers[SIZE_LIST];
        
        // Boolean to check if the node is leaf
        bool isLeaf;

        // Only leaf nodes (isLeaf = True) have this content different than null
        std::string word;

        /**
         * @brief Default Node constructor.
         * 
         */
        Node() {

            // Set pointers list lenght iguals to SIZE_LIST and all positions pointing to nullptr.
            for (int i = 0; i < SIZE_LIST; i++) {
                pointers[i] = nullptr;
            }

            // Define node type
            this->isLeaf = false;
        }
        
        /**
         * @brief Leaf Node constructor.
         * 
         * @param word Word to store.
         */
        Node(std::string word) {

            // Set pointers list lenght iguals to SIZE_LIST and all positions pointing to nullptr.
            for (int i = 0; i < SIZE_LIST; i++) {
                pointers[i] = nullptr;
            }

            // Define node type
            this->isLeaf = true;

            this->word = word;
        }
    };

    Node *rootNode;
    void Insert(Node *auxNode, std::string &word, int &index);
    void VerifyWord(Node *auxNode, std::string &word, int &index);
    void ClearAll();
    void ClearAll(Node *auxNode);
    bool ManipulateString(std::string &word);
    int LetterLogic(std::string &word, int &index);
public:

    /**
     * @brief Trie constructor
     * 
     */
    Trie() {
        rootNode = nullptr;
    }

    /**
     * @brief Trie destructor
     * 
     */
    ~Trie() {
        ClearAll();
    }

    void Insert(std::string &word);
    void VerifyWord(std::string &word);
};

/**
 * @brief Insert a new word
 * 
 * @param word word to insert
 */
void Trie::Insert(std::string &word) {

    if (!ManipulateString(word)) {
        std::cout << "|" << word << "| not accepted !" << std::endl;
        return;
    }

    if (rootNode == nullptr) {
        rootNode = new Node(word);
    } else {
        int index = 0;
        Insert(rootNode, word, index);
    }
}

/**
 * @brief Insert a new word
 * 
 * @param auxNode Pointer to a Node
 * @param word Word to insert
 * @param index Help us to compare word and auxNode word
 */
void Trie::Insert(Node *auxNode, std::string &word, int &index) {
    int letter = LetterLogic(word, index);
    
    if (auxNode->pointers[letter] == nullptr) {
        if (auxNode->isLeaf) {

            int letterAuxNode = LetterLogic(auxNode->word, index);
            if (letter == letterAuxNode) {
                auxNode->pointers[letterAuxNode] = new Node(auxNode->word);
                auxNode->word.clear();
                auxNode->isLeaf = false;
                Insert(auxNode->pointers[letterAuxNode], word, ++index);
            } else {
                auxNode->pointers[letterAuxNode] = new Node(auxNode->word);
                auxNode->pointers[letter] = new Node(word);
                auxNode->word.clear();
                auxNode->isLeaf = false;
            }

        } else {
            auxNode->pointers[letter] = new Node(word);
        }
    } else {
        Insert(auxNode->pointers[letter], word, ++index);
    }
}

/**
 * @brief Check if the word passed by parameter exists.
 * 
 * @param word Word to check.
 */
void Trie::VerifyWord(std::string &word) {
    if (!ManipulateString(word)) {
        std::cout << "Sorry, we've faced some issue with the word: '" << word << "'. Try a word with only letters." << std::endl << std::endl;
        return;
    }

    if (rootNode != nullptr) {
        int index = 0;
        VerifyWord(rootNode, word, index);
    } else {
        std::cout << "OPS !! Without data. Something went wrong." << std::endl << std::endl;
    }
}

/**
 * @brief Check if the word passed by parameter exists.
 * 
 * @param auxNode Pointer to a Node
 * @param word Word to check
 * @param index Help us to compare word and auxNode word
 */
void Trie::VerifyWord(Node *auxNode, std::string &word, int &index) {
    if (!auxNode->isLeaf) {
        int letter = LetterLogic(word, index);
        if (auxNode->pointers[letter] != nullptr) {
            VerifyWord(auxNode->pointers[letter], word, ++index);
        } else {
            std::cout << "|"<< word << "| doesn't exist in our database" << std::endl << std::endl;
        }
    } else {
        if (auxNode->word != word) {
            std::cout << "|"<< word << "| doesn't exist in our database" << std::endl << std::endl;
        } else {
            std::cout << "|"<< word << "| exist" << std::endl << std::endl;
        }
    }
}

/**
 * @brief The method convert a lowercase letter in a integer. [a -> 0], [b -> 1] and so on.
 * For index out of range (the word that we are analysing ended) the value is SIZE_LIST - 1.
 * 
 * @param word Word that we are analysing
 * @param index The current index
 * @return 'Pointer Number'
 */
int Trie::LetterLogic(std::string &word, int &index) {
    return word.length() == index ? SIZE_LIST - 1 : (int)(word.at(index) - 97);
}

/**
 * @brief Clear all Trie data.
 * 
 */
void Trie::ClearAll() {
    if (rootNode != nullptr) {
        ClearAll(rootNode);
    }
}

/**
 * @brief Clear all Trie data.
 * 
 * @param auxNode Pointer to node
 */
void Trie::ClearAll(Node *auxNode) {
    if (!auxNode->isLeaf) {
        for (int i = 0; i < SIZE_LIST; i++) {
            bool isPointerToNode = auxNode->pointers[i] != nullptr;
            if (isPointerToNode) {
                ClearAll(auxNode->pointers[i]);
                auxNode->pointers[i] = nullptr;
            }
        }
    }
    delete auxNode;
}

/**
 * @brief Manipulate the string.
 * 
 * @param word Reference to word that need to be manipulated
 * @return True: Manipulation successfully done and False: Invalid character found
 */
bool Trie::ManipulateString(std::string &word) {
    for (int i = 0; i < word.size(); i++) {
        int letterASCII = (int)word[i];
        bool isUpperCase = letterASCII >= 65 && letterASCII <= 90;
        bool isLowerCase = letterASCII >= 97 && letterASCII <= 122;

        if (isUpperCase) {
            word[i] = (char)(letterASCII + 32);
        } else if (!isLowerCase) {
            return false;
        }
    }

    return true;
}

#endif