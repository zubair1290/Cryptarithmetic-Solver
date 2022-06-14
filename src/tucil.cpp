#include <iostream>
#include <fstream>
#include <chrono>
#include <cstring>

void process(int permutation_number[]);
void permutation(int combination_numbers[]);
void permutate(int **combination_numbers, int permutation_numbers[], int idx, int number_lists[], int len_number_lists);
int pow(int num, int n);

class Words {
public:
    char el[15*30];
    short int len_row[15];
    short int len_words = 0;  // banyaknya kata

    char &at(int i, int j) {
        return this->el[i*30+j];
    }

};

class Letters {
public:
    char el[26];
    short int len;
    char &operator[](int idx) {
        return this->el[idx];
    }
};

Words words;
Letters unique_letters;  // list unique character
Letters first_letters;   // Kumpulan kata pertama
std::string result_string;   // kumpulan permutasi yang merupakan solusi
int number_of_results = 0;  // banyaknya solusi
int count_test = 0; // hitung banyaknya test
int total_test = 0;  // jumlah total tes yang dilakukan sebelum menemukan solusi yang benar

int main() {
    std::string r_words[16];

    {   // Read File
        // std::string r_line;
        std::ifstream read_file("../test/test.txt");
        // membaca file per baris
        while(std::getline(read_file, r_words[words.len_words])) { words.len_words++; };
        read_file.close();
    }

    // mulai menghitung 
    auto start = std::chrono::high_resolution_clock::now();
    // memasukkan file yang sudah diread ke dalam words dengan menghapus spasi
    for (int i = 0; i < words.len_words; i++) {
        int index_copy = 0; 
        while (r_words[i][index_copy] == ' ') { index_copy++; }
        strcpy(&words.at(i, 0), &r_words[i][index_copy]);
        words.len_row[i] = r_words[i].length()-index_copy;
    }

    for (int i=0; i < words.len_row[words.len_words-3]; i++) {
        if (words.at(words.len_words-3, i) == '+') {
            while (i < words.len_row[words.len_words-3]-1) {
                words.at(words.len_words-3, i) = words.at(words.len_words-3, i+1);
                i++;
            }

            words.at(words.len_words-3, (words.len_row[words.len_words-3]--)-1) = '\0';
            break;
        }
    }

    strcpy(&words.at(words.len_words-2, 0), &words.at(words.len_words-1, 0));
    words.len_row[words.len_words-2] = words.len_row[words.len_words-1];
    words.at(words.len_words-1, 0) = '\0';
    words.len_row[(words.len_words--)-1] = 0;
    
    for (int i=0; i < words.len_words; i++) {
        // huruf pertama pada kata bukan bernilai nol
        {
            int j=0;
            // for (;j < first_letters.length(); j++)
            //     if (first_letters.at(j) == words.at(i, 0)) break;
            // if (j == first_letters.length()) 
            //     first_letters.push_back(words.at(i, 0));
            for (;j < first_letters.len; j++)
                if (first_letters.el[j] == words.at(i, 0)) break;
            if (j == first_letters.len) 
                first_letters.el[first_letters.len++] = words.at(i, 0);
        }
        // mengumpulkan huruf yang unik
        for (int j = 0; j < words.len_row[i]; j++) {
            int count_c = 0;
            // for (; count_c < unique_letters.size(); count_c++)
            //     if (unique_letters.at(count_c) == words.at(i,j)) break;
            // if (count_c == unique_letters.size())
            //     unique_letters.push_back(words.at(i, j));
            for (; count_c < unique_letters.len; count_c++)
                if (unique_letters.el[count_c] == words.at(i,j)) break;
            if (count_c == unique_letters.len)
                unique_letters.el[unique_letters.len++] = words.at(i, j);
        }
    }

    // kombinasi angka 
    // int combination_numbers[unique_letters.len+1];
    int combination_numbers[27];

    // inisialisasi combination_numbers = {0, 1, ...}
    // for (int i=0; i < unique_letters.length(); i++)
    for (int i=0; i < unique_letters.len; i++)
        combination_numbers[i] = i;

    // melakukan initialisasi nilai pada indeks terakhir sebesar 10
    combination_numbers[unique_letters.len] = 10;
    // kombinasi dimulai dari index terakhir
    int i = unique_letters.len-1;

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
            } while (i < unique_letters.len);
            i--;
            permutation(combination_numbers);
        } else
        {
            i--;
        }
    }

    // ============ print r_words ============
    std::cout << "Input File:\n";
    for (int j=0; j < words.len_words+1; j++)
        std::cout << r_words[j] << '\n';
    std::cout << '\n';

    // ============ print solusi ============
    std::cout << "Ada " << number_of_results << " solusi yang mungkin: \n";
    for (int i=0; i < number_of_results; i++) {
        std::cout << "Solusi ke-" << i+1 << ":\n";
        // std::string num_words_print[words.len_words+1];
        std::string num_words_print[17];
        for (int j=0; j < words.len_words+1; j++)
            num_words_print[j] = r_words[j];

        for (int j = 0; j < unique_letters.len; j++) {
            for (int k = 0; k < words.len_words+1; k++) {
                int len_r_words_k = r_words[k].length();
                for (int l = 0; l < len_r_words_k; l++) {
                    if (r_words[k][l] == unique_letters.el[j])
                        num_words_print[k].at(l) = result_string.at(j +i*unique_letters.len+i);
                }
            }
        }

        for (int j=0; j < words.len_words+1; j++)
            std::cout << num_words_print[j] << '\n';
        
        for (int j=0; j < unique_letters.len-1; j++)
            std::cout << unique_letters.el[j] << " = " << result_string.at(j +i*unique_letters.len+i) << ", ";
        std::cout << unique_letters.el[unique_letters.len-1] << " = " << result_string.at(unique_letters.len-1 +i*unique_letters.len+i) << "\n\n"; 

        // delete[] num_words_print;
    }

    // // ============ print r_words ============
    // std::string printString;
    // // std::cout << "Input File:\n";
    // printString += "Input File:\n";
    // // for (int j=0; j < words.len_words+1; j++)
    // //     std::cout << r_words[j] << '\n';
    // for (int j=0; j < words.len_words+1; j++) {
    //     printString += r_words[j];
    //     printString += '\n';
    // }
    // // std::cout << '\n';
    // printString += '\n';

    // // ============ print solusi ============
    // printString += "Ada "; 
    // printString += number_of_results+'0'; 
    // printString += " solusi yang mungkin: \n";
    // // std::cout << "Ada " << number_of_results << " solusi yang mungkin: \n";
    // for (int i=0; i < number_of_results; i++) {
    //     // std::cout << "Solusi ke-" << i+1 << ":\n";
    //     printString += "Solusi ke-";
    //     printString += i+1+'0'; 
    //     printString += ":\n";

    //     std::string num_words_print[words.len_words+1];
    //     for (int j=0; j < words.len_words+1; j++)
    //         num_words_print[j] = r_words[j];

    //     for (int j = 0; j < unique_letters.len; j++) {
    //         for (int k = 0; k < words.len_words+1; k++) {
    //             // int len_r_words_k = strlen(r_words[k]);
    //             int len_r_words_k = r_words[k].length();
    //             for (int l = 0; l < len_r_words_k; l++) {
    //                 if (r_words[k][l] == unique_letters.el[j])
    //                     num_words_print[k].at(l) = result_string.at(j +i*unique_letters.len+i);
    //             }
    //         }
    //     }

    //     for (int j=0; j < words.len_words+1; j++) {
    //         printString += num_words_print[j];
    //         printString += '\n';
    //         // std::cout << num_words_print[j] << '\n';
    //     }

    //     for (int j=0; j < unique_letters.len-1; j++) {
    //         printString += unique_letters.el[j];
    //         printString += " = ";
    //         printString += result_string.at(j +i*unique_letters.len+i);
    //         printString += ", ";
    //         // std::cout << unique_letters.el[j) << " = " << result_string.at(j +i*unique_letters.len+i) << ", ";
    //     }
    //     printString += unique_letters.el[unique_letters.len-1];
    //     printString += " = ";
    //     printString += result_string.at(unique_letters.len-1 +i*unique_letters.len+i);
    //     printString += "\n\n";
    //     // std::cout << unique_letters.at(unique_letters.len-1) << " = " << result_string.at(unique_letters.len-1 +i*unique_letters.len+i) << "\n\n"; 
    // }
    // std::cout << printString;
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    // ============ total tes ============ 
    std::cout << "total test yang dilakukan untuk menemukan solusi: " << total_test << " kali\n";
    // ============ waktu ============  
    std::cout << "Time taken: " << duration.count()/1000000.0 << " seconds" << std::endl; 
    return 0;
}

void permutation(int combination_numbers[]) {
    // int permutation_numbers[unique_letters.len];
    int permutation_numbers[26];
    permutate(&combination_numbers, permutation_numbers, 0, combination_numbers, unique_letters.len);
}

void permutate(int **combination_numbers, int permutation_numbers[], int idx, int number_lists[], int len_number_lists) {
    if (len_number_lists == 0) process(permutation_numbers);
    else {
        for (int i=0; i < len_number_lists; i++) {
            
            // skip first_letter == 0
            bool is_in_first_letters = false;
            if (number_lists[i] == 0) {
                for (int j = 0; j < first_letters.len; j++) {
                    if (first_letters.el[j] == unique_letters.el[idx]) {
                        is_in_first_letters = true;
                        break;
                    }
                }
            }
            if (is_in_first_letters) continue;

            // copy number_lists to number_lists_new except element index i
            // int number_lists_new[len_number_lists-1];
            // std::copy_n(number_lists, i, number_lists_new);
            // std::copy_n(number_lists+i+1, len_number_lists-(i+1), number_lists_new+i);
            // for (int j=0; j < len_number_lists-1; j++) {
            //     if (j < i)
            //         number_lists_new[j] = number_lists[j];
            //     else
            //         number_lists_new[j] = number_lists[j+1]; 
            // }

            // copy number_lists to number_lists_new except element index i
            int number_lists_new[27];
            for (int j = 0; j < i; j++)
                number_lists_new[j] = number_lists[j];
            for (int j = i+1; j < len_number_lists; j++)
                number_lists_new[j-1] = number_lists[j]; 

            permutation_numbers[idx] = number_lists[i];
            permutate(combination_numbers, permutation_numbers, idx+1, number_lists_new, len_number_lists-1);
        }
    }
}


void process(int permutation_number[]) {
    count_test++;
    // substitusi angka
    // int num_words[words.len_words] = {0};
    int num_words[15] = {0};
    for (int i = 0; i < unique_letters.len; i++) {
        for (int j = 0; j < words.len_words; j++) {
            for (int k = 0; k < words.len_row[j]; k++) {
                if (words.at(j, k) == unique_letters.el[i])
                    num_words[j] += permutation_number[i]*pow(10, words.len_row[j]-1 -k);
            }
        }
    }

    // penjumlahan
    int result = 0;
    for (int i = 0; i < words.len_words-1; i++)
        result += num_words[i];

    // Jika sama maka solusinya dimasukkan ke dalam result
    if (result == num_words[words.len_words-1]){
        for (int i = 0; i < unique_letters.len; i++)
            result_string.push_back(permutation_number[i] + '0');
        result_string.push_back(' ');
        number_of_results++;
        if (number_of_results == 1) total_test = count_test;
    }
}

int pow(int num, int n) {
    // syarat: n >= 0
    int result = 1;
    for (int i=0; i < n; i++) result *= num;
    return result;
}