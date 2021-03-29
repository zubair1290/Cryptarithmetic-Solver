#include <iostream>
#include <fstream>
using namespace std;

int main() {
    string r_words[100];
    string words[100];
    int count_words = 0;
    string line_text;
    ifstream ReadFile("text.txt");
    while(getline(ReadFile, line_text)) {
        // line_text.copy(words[count_words], line_text.length(), 0);
        r_words[count_words++] = line_text;

        // words[count_words++][line_text.length()] = '\0';
    }

    for (int i=0; i<count_words; i++) {
        int j = 0, index_copy = 0; 
        while (r_words[i].at(j) == ' ') {
            index_copy++;
            j++;
        }
        char buff[30];
        cout << index_copy << '\n';
        int len_words = r_words[i].length()-index_copy;
        r_words[i].copy(buff, len_words, index_copy);
        buff[len_words] = '\0';
        words[i] = buff;
    }

    for (int i=0; i<10; i++)
        std::cout << words[i] << '\n';

    return 0;
}