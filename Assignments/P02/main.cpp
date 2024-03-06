#include "json.hpp"
#include <conio.h>
#include "termcolor.hpp"
#include "timer.hpp"
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>
#include <time.h>
#include <vector>
#include <windows.h>

using namespace std;

using json = nlohmann::json;

void saveWords(json j) {
    ofstream fout;
    fout.open("dictionary.txt");

    for (auto& element : j.items()) {
        std::string key = element.key();
        fout << key << "\n";
    }
}

void search(string x, vector<string>& words) {

    Timer A;   // create a timer
    A.Start(); // start it

    // Load your JSON object as shown in previous examples
    std::string filePath = "dictionary.json";
    std::ifstream fileStream(filePath);
    std::string partialKey = " ";
    json myJson;
    if (fileStream.is_open()) {
        fileStream >> myJson;
        fileStream.close();
    }
    else {
        std::cerr << "Failed to open file: " << filePath << std::endl;
    }

    A.End(); // end the current timer
    printf("Nanoseconds: %.17f\n", (double)A.NanoSeconds() / 1000000000);

    // The substring you are looking for in the keys
        partialKey = x;

    // Iterate over all key-value pairs
    for (auto& element : myJson.items()) {
        std::string key = element.key();

        // Check if the key contains the partialKey substring
        if (key.find(partialKey) == 0) { //std::string::npos
            // Found a match, do something with it
            words.push_back(key);
        }
    }
}

int main() {
    char k;
    string key;
    string word = "";
    vector<string> words;
    vector<string> nuWords;
    Timer T;
    int loc;
    cout << "Press 'Z' to exit" << endl << endl;

    while ((k = _getch()) != 'Z') {
        T.Start(); // start it
        // Tests for a backspace and if pressed deletes
       // last letter from "word".
        if ((int)k == 8) {
            if (word.size() > 0) {
                word = word.substr(0, word.size() - 1);
            }
        }
        else {
            // Make sure a letter was pressed and only letter
            if (!isalpha(k)) {
                cout << termcolor::on_bright_red << termcolor::bright_white << "Letters only!" << termcolor::reset << endl;
                Sleep(1);
                continue;
            }

            // We know its a letter, lets make sure its lowercase.
            // Any letter with ascii value < 97 is capital so we
            // lower it.
            if ((int)k < 97) {
                k += 32;
            }
            word += k; // append char to word
        }

        // Find any animals in the array that partially match
        // our substr word
        if(word.size()>=3){ search(word, words); }

        if ((int)k != 32) { // if k is not a space print it
            key = to_string(k);
            T.End();
            // Getting the correct precision to print out in c++ is not
            // straight forward. Strings and precision output are convoluted
            // at best. And drive you crazy at worst

            system("CLS");

            string pbp = "Play By Play";

            string message = "User is typing keys, building a search string with every key stroke:" + word;

            cout << termcolor::underline << termcolor::bold << termcolor::bright_cyan << pbp << termcolor::reset << endl
                << endl;
            cout << termcolor::bright_magenta << message << termcolor::reset << endl;
            // line = new string(screenWidth(),' ');
            cout << termcolor::underline << termcolor::bold << termcolor::bright_cyan << "GETCH WORD LOOKUP" << termcolor::reset << endl;
            cout << termcolor::green << termcolor::bold << "   Seconds:\t\t" << termcolor::reset << termcolor::yellow << printf("%.17f", (double)T.NanoSeconds() / 1000000000)
                << termcolor::reset << endl;
            cout << termcolor::green << termcolor::bold << "   KeyPressed: \t\t" << termcolor::yellow;
            if (int(k) == 127) {
                cout << "del";
            }
            else {
                cout << k;
            }
            cout << " = " << (int)k << termcolor::reset << endl;
            cout << termcolor::green << termcolor::bold << "   Current Substr: \t" << termcolor::reset << termcolor::red << word << termcolor::reset << endl;
            cout << endl;
            cout << termcolor::underline << termcolor::bold << termcolor::bright_cyan << termcolor::reset << endl;

            cout << termcolor::green;
            // This prints out all found matches
            if (word.size() >= 3) {
                for (int i = 0; i < 10 || i < word.size(); i++) {
                    // find the substring in the word
                    loc = words[i].find(word);
                    // if its found
                    if (loc != string::npos) {
                        // print one letter at a time turning on red or green
                        //  depending on if the matching subtring is being printed
                        cout << termcolor::bold;
                        for (int j = 0; j < words[i].size(); j++) {
                            // if we are printing the substring turn it red
                            if (j >= loc && j <= loc + word.size() - 1) {
                                cout << termcolor::red;
                            }
                            else {
                                cout << termcolor::blue;
                            }
                            cout << words[i][j];
                        }
                        cout << termcolor::blue;
                    }
                    cout << " ";
                }
                cout << termcolor::reset << endl
                    << endl;
                words.clear();
            }
        }
    }

        return 0;
    }
