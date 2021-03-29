#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;

void process(int permutation_number[]);
void permutation(int combination_numbers[]);
void permutate(int **combination_numbers, int permutation_numbers[], int idx, int number_lists[], int len_number_lists);
int pow(int num, int n);

string words[15];  // kumpulan kata
int len_words = 0;  // banyaknya kata
string unique_letters;  // list unique character
string first_letters;   // Kumpulan kata pertama
string result_string;   // kumpulan permutasi yang merupakan solusi
int number_of_results = 0;  // banyaknya solusi
int count_test = 0; // hitung banyaknya test
int total_test = 0;  // jumlah total tes yang dilakukan sebelum menemukan solusi yang benar

int main() {
    string r_words[16];

    {   // Read File
        string r_line;
        ifstream read_file("../test/test.txt");
        // membaca file per baris
        while(getline(read_file, r_line))
            r_words[len_words++] = r_line;
        read_file.close();
    }

    // mulai menghitung 
    auto start = chrono::high_resolution_clock::now();
    // memasukkan file yang sudah diread ke dalam words dengan menghapus spasi
    for (int i = 0; i < len_words; i++) {
        int j = 0, index_copy = 0; 
        while (r_words[i].at(j++) == ' ')
            index_copy++;
        words[i] = &r_words[i].at(index_copy);
    }

    // menghilangkan karakter '+' pada kata di operand terakhir
    for (int i=0; i < words[len_words-3].length(); i++) {
        if (words[len_words-3].at(i) == '+') {
            while (i < words[len_words-3].length()-1) {
                words[len_words-3].at(i) = words[len_words-3].at(i+1);
                i++;
            }
            words[len_words-3].pop_back();
            break;
        }
    }

    words[len_words-2] = words[len_words-1];
    words[len_words-1][0] = '\0';
    len_words--;
    
    for (int i=0;i < len_words; i++) {
        // huruf pertama pada kata bukan bernilai nol
        {
            int j=0;
            for (;j<first_letters.length(); j++)
                if (first_letters.at(j) == words[i][0]) break;
            if (j == first_letters.length()) 
                first_letters.push_back(words[i].at(0));
        }
        // mengumpulkan huruf yang unik
        for (int j = 0; j < words[i].length(); j++) {
            int count_c = 0;
            for (; count_c < unique_letters.size(); count_c++)
                if (unique_letters.at(count_c) == words[i].at(j)) break;
            if (count_c == unique_letters.size())
                unique_letters.push_back(words[i].at(j));
        }
    }

    // kombinasi angka 
    int combination_numbers[unique_letters.length()+1];

    // inisialisasi combination_numbers = {0, 1, ...}
    for (int i=0; i < unique_letters.length(); i++)
        combination_numbers[i] = i;

    // melakukan initialisasi nilai pada indeks terakhir sebesar 10
    combination_numbers[unique_letters.length()] = 10;
    // kombinasi dimulai dari index terakhir
    int i = unique_letters.length()-1;

    permutation(combination_numbers);
    while (true) {
        if (combination_numbers[i] != combination_numbers[i+1]-1) {
            combination_numbers[i]++;
            permutation(combination_numbers);
        } else
        if (i == 0) break;
        else
        if (combination_numbers[i] != combination_numbers[i-1]+1) {
            combination_numbers[i-1]++;
            do {
                combination_numbers[i++] = combination_numbers[i-1]+1;
            } while (i < unique_letters.length());
            i--;
            permutation(combination_numbers);
        } else
        {
            i--;
        }
    }

    // ============ print r_words ============
    std::cout << "Input File:\n";
    for (int j=0; j < len_words+1; j++)
        std::cout << r_words[j] << '\n';
    cout << '\n';

    // ============ print solusi ============
    cout << "Ada " << number_of_results << " solusi yang mungkin: \n";
    for (int i=0; i < number_of_results; i++) {
        cout << "Solusi ke-" << i+1 << ":\n";
        string num_words_print[len_words+1];
        for (int j=0; j < len_words+1; j++)
            num_words_print[j] = r_words[j];

        for (int j = 0; j < unique_letters.length(); j++) {
            for (int k = 0; k < len_words+1; k++) {
                for (int l = 0; l < r_words[k].length(); l++) {
                    if (r_words[k].at(l) == unique_letters.at(j))
                        num_words_print[k].at(l) = result_string.at(j +i*unique_letters.length()+i);
                }
            }
        }

        for (int j=0; j < len_words+1; j++)
            std::cout << num_words_print[j] << '\n';
        
        for (int j=0; j < unique_letters.length()-1; j++)
            std::cout << unique_letters.at(j) << " = " << result_string.at(j +i*unique_letters.length()+i) << ", ";
        std::cout << unique_letters.at(unique_letters.length()-1) << " = " << result_string.at(unique_letters.length()-1 +i*unique_letters.length()+i) << "\n\n"; 
    }
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

    // ============ total tes ============ 
    cout << "total test yang dilakukan untuk menemukan solusi: " << total_test << " kali\n";
    // ============ waktu ============  
    std::cout << "Time taken: " << duration.count()/1000000.0 << " seconds" << endl; 
    return 0;
}

void permutation(int combination_numbers[]) {
    int permutation_numbers[unique_letters.length()];
    permutate(&combination_numbers, permutation_numbers, 0, combination_numbers, unique_letters.length());
}

void permutate(int **combination_numbers, int permutation_numbers[], int idx, int number_lists[], int len_number_lists) {
    if (len_number_lists == 0) process(permutation_numbers);
    else
    {
        for (int i=0; i < len_number_lists; i++) {
            // copy number_lists to number_lists_new except element index i
            int number_lists_new[len_number_lists-1];
            for (int j = 0; j < i; j++)
                number_lists_new[j] = number_lists[j];
            for (int j = i+1; j < len_number_lists; j++)
                number_lists_new[j-1] = number_lists[j]; 

            // skip first_letter == 0
            bool is_in_first_letters = false;
            if (number_lists[i] == 0) {
                for (int j = 0; j < first_letters.length(); j++) {
                    if (first_letters.at(j) == unique_letters.at(idx)) {
                        is_in_first_letters = true;
                        break;
                    }
                }
            }
            if (is_in_first_letters) continue;

            permutation_numbers[idx] = number_lists[i];
            permutate(combination_numbers, permutation_numbers, idx+1, number_lists_new, len_number_lists-1);
        }
    }
}


void process(int permutation_number[]) {
    count_test++;
    // substitusi angka
    int num_words[len_words] = {0};
    for (int i = 0; i < unique_letters.length(); i++) {
        for (int j = 0; j < len_words; j++) {
            for (int k = 0; k < words[j].length(); k++) {
                if (words[j].at(k) == unique_letters.at(i))
                    num_words[j] += permutation_number[i]*pow(10, words[j].length()-1 -k);
            }
        }
    }

    // penjumlahan
    int result = 0;
    for (int i=0; i < len_words-1; i++)
        result += num_words[i];

    // Jika sama maka solusinya dimasukkan ke dalam result
    if (result == num_words[len_words-1]){
        for (int i = 0; i < unique_letters.length(); i++)
            result_string.push_back(permutation_number[i] + '0');
        result_string.push_back(' ');
        number_of_results++;
        if (number_of_results == 1) total_test = count_test;
    }
}

int pow(int num, int n) {
    // syarat: n >= 0
    int result = 1;
    for (int i=0; i<n; i++) result *= num;
    return result;
}