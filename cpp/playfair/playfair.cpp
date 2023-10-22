#include "playfair.h"

vector<string> matrix(string& letter, vector<string>& key, int& columns) {
    vector<string> matrix((letter.size() + key.size() * columns) / columns);

    for (uint16_t line = 0; line < key.size(); line++) matrix[line] = key[line];

    for (uint16_t line = 0; line < matrix.size(); line++) {
        if (line < key.size() && matrix[line] == key[line]) continue;
        string symbol;
        for (uint16_t j = 0; j < columns; j++) {
            symbol.push_back(letter[0]);
            letter.erase(0, 1);
        }
        matrix[line] = symbol;
    }

    return matrix;
}

void delCheck(string& letter, string& text, vector<string>& Key, string& character, int& columns) {
    int8_t del = letter.size() - (letter.size() / columns) * columns;

    if (del != character.size()) throw runtime_error("Only " + to_string(del) + " letter can be deleted");

    for (char symbolChar : character) {
        for (string& line : Key) {
            for (char& symbolKey : line) {
                if (symbolChar == symbolKey) throw runtime_error(string("The symbol \"") + symbolChar + "\" is contained in the key");
            }
        }
    }

    for (char symbolChar : character) {
        for (char symbolText : text) if (symbolChar == symbolText || symbolChar == 'X') throw runtime_error(string("The symbol \"") + symbolChar + "\" is contained in the text");
        for (uint16_t symbolLet = 0; symbolLet < letter.size(); symbolLet++) {
            if (letter[symbolLet] == symbolChar) letter.erase(symbolLet, 1);
        }
    }
}

vector<string> sort(string& letter, string& text, string& key, string& character, int& columns) {

    if (columns == 0) columns = sqrt(letter.size());
    else if (columns > sqrt(letter.size())) throw runtime_error("Maximum columns " + to_string(static_cast<int>(sqrt(letter.size()))) + " for this alphabet");

    for (uint16_t i = 0; i < key.size(); i++) {
        for (uint16_t j = i + 1; j < key.size(); j++) {
            if (key[i] == key[j]) key.erase(j, 1);
        }
    }

    vector<string> Key;
    string doubleKey;
    uint16_t numIterations = key.size() / columns + 1;
    for (uint16_t iteration = 0; iteration < numIterations; iteration++) {
        for (uint16_t j = 0; j < columns; j++) {
            if (key.size() < columns) {
                bool check = true;
                for (string& line : Key) {
                    for (char& symbol : line) {
                        if (symbol == letter[j]) {
                            check = false;
                            break;
                        }
                    }
                }
                if (check) key.push_back(letter[j]);
            }
            doubleKey += key[j];
        }
        key.erase(0, columns);
        Key.push_back(doubleKey);
        doubleKey = "";
        if (key == "" || key[0] == ' ') break;
    }

    for (string& line : Key) {
        for (char& symbolKey : line) {
            for (uint16_t symbolLet = 0; symbolLet < letter.size(); symbolLet++) {
                if (symbolKey == letter[symbolLet]) {
                    letter.erase(symbolLet, 1);
                    break;
                }
                else if (symbolLet == letter.size() - 1) throw runtime_error(string("The \"") + symbolKey + "\" character of the key does not match the alphabet");
            }
        }
    }

    delCheck(letter, text, Key, character, columns);

    return matrix(letter, Key, columns);

}

void coordinates(vector<string>& matrix, string& text, uint16_t& oneSymbol, uint16_t& twoSymbol, uint8_t& finalOneX, uint8_t& finalOneY, uint8_t& finalTwoX, uint8_t& finalTwoY) {
    uint8_t oneX = 0, oneY = 0;
    uint8_t twoX = 0, twoY = 0;
    bool oneContains = false;
    bool twoContains = false;
    for (string& line : matrix) {
        for (char& symbol : line) {
            if (text[oneSymbol] == symbol) {
                if (!oneContains) {
                    finalOneX = oneX;
                    finalOneY = oneY;
                    oneContains = true;
                }
            }
            if (text[twoSymbol] == symbol) {
                if (!twoContains) {
                    finalTwoX = twoX;
                    finalTwoY = twoY;
                    twoContains = true;
                }
            }
            oneX++;
            twoX++;
        }
        if (oneContains == true && twoContains == true) break;
        oneY++;
        twoY++;
        oneX = 0;
        twoX = 0;
    }
}

void textCheck(string& text, string& letter) {
    for (char& symbolText : text) {
        for (uint16_t symbolLet = 0; symbolLet < letter.size(); symbolLet++) {
            if (symbolText == letter[symbolLet]) break;
            else if (symbolLet == letter.size() - 1) throw runtime_error(string("The \"") + symbolText + "\" character of the text does not correspond to the alphabet");
        }
    }

    for (uint16_t oneSymbol = 0, twoSymbol = 1; twoSymbol < text.size(); oneSymbol += 2, twoSymbol += 2) {
        if (text[oneSymbol] == text[twoSymbol]) text.insert(twoSymbol, "X");
    }

    if (text.size() % 2 != 0) text.push_back('X');
}

string encryption(string letter, string key, string text, string character, int columns, bool code, bool file) {
    try {
        if (letter == "") letter = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]^_`abcdefghijklmnopqrstuvwxyz{|}~";
        if (key == "") key = "D*G-KaPd";
        textCheck(text, letter);
        vector<string> matrix = sort(letter, text, key, character, columns);
        string encryption;
        for (uint16_t oneSymbol = 0, twoSymbol = 1; twoSymbol < text.size(); oneSymbol += 2, twoSymbol += 2) {
            uint8_t oneX = 0, oneY = 0;
            uint8_t twoX = 0, twoY = 0;
            coordinates(matrix, text, oneSymbol, twoSymbol, oneX, oneY, twoX, twoY);
            if (code == 0) {
                if (oneY == twoY) {
                    if (oneX + 1 == columns) encryption.push_back(matrix[oneY][0]);
                    else encryption.push_back(matrix[oneY][oneX + 1]);
                    if (twoX + 1 == columns) encryption.push_back(matrix[twoY][0]);
                    else encryption.push_back(matrix[twoY][twoX + 1]);
                }
                else if (oneX == twoX) {
                    if (oneY + 1 == matrix.size()) encryption.push_back(matrix[0][oneX]);
                    else encryption.push_back(matrix[oneY + 1][oneX]);
                    if (twoY + 1 == matrix.size()) encryption.push_back(matrix[0][twoX]);
                    else encryption.push_back(matrix[twoY + 1][twoX]);
                }
                else {
                    encryption.push_back(matrix[oneY][twoX]);
                    encryption.push_back(matrix[twoY][oneX]);
                }
            }
            else {
                if (oneY == twoY) {
                    if (oneX == 0) encryption.push_back(matrix[oneY][columns - 1]);
                    else encryption.push_back(matrix[oneY][oneX - 1]);
                    if (twoX == 0) encryption.push_back(matrix[twoY][columns - 1]);
                    else encryption.push_back(matrix[twoY][twoX - 1]);
                }
                else if (oneX == twoX) {
                    if (oneY == 0) encryption.push_back(matrix[matrix.size() - 1][oneX]);
                    else encryption.push_back(matrix[oneY - 1][oneX]);
                    if (twoY == 0) encryption.push_back(matrix[matrix.size() - 1][twoX]);
                    else encryption.push_back(matrix[twoY - 1][twoX]);
                }
                else {
                    encryption.push_back(matrix[oneY][twoX]);
                    encryption.push_back(matrix[twoY][oneX]);
                }
            }
        }
        if (code == 1) {
            for (uint16_t line = 0; line < encryption.size(); line++) {
                if (encryption[line] == 'X' && (encryption[line - 1] == encryption[line + 1] || encryption[line + 1] == '\0')) encryption.erase(line, 1);
            }
        }
        if (file == 1) {
            ofstream file("Playfair.txt", ios::app);
            if (file.is_open()) {
                if (code == 0) file << "Зашифрованный текст: " << encryption << endl;
                else file << "Расшифрованный текст: " << encryption << endl;
                file.close();
                cout << "Writing to the file was successful." << endl;
            }
            else throw runtime_error("File opening error.");
        }
        return encryption;
    }
    catch (const exception& e) {
        cout << "ERROR: " << e.what() << endl;
        return string("ERROR: ") + e.what();
    }
}