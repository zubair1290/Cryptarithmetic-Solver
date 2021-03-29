#include <iostream>
using namespace std;

bool process(unsigned short int permutation_number[], string word_list);
unsigned short int *permutation(unsigned short int combination_number[], unsigned short int total_unique_words, string word_list, int factorial_arr[], bool *isCorrect);

unsigned short int *permutation(unsigned short int combination_number[], unsigned short int total_unique_words, string word_list, int factorial_arr[], bool *isCorrect) {
    // cout << "len "<< total_unique_words << '\n';
    /*
    12345
    12354

    12534
    12543

    12453
    12435


    12345 x
    13245
    13254

    13524
    13542

    13452
    13425

    13245 x
    14325
    */
    unsigned short int *permutation_number;
    permutation_number = new unsigned short int[total_unique_words+1];
    for (int i=0; i<total_unique_words+1; i++)
        permutation_number[i] = combination_number[i];
    
    // for (int i=0; i<total_unique_words; i++)
    //     cout << permutation_number[i] << ' ';
    // cout << '\n';

    int st_num[total_unique_words+1] = {0};
    int many_permutation = factorial_arr[total_unique_words];
    // cout << many_permutation << '\n';
    while (st_num[total_unique_words-1] != many_permutation) {
        // angka pada st_num bertambah 1
        for (int k=0; k < total_unique_words; k++)
            st_num[k]++;
        // swap
        for (int k = 0; k < total_unique_words; k++) {
            // jika ada pada st_num angka yang tidak sama dengan 1 maka angka tsb dengan angka sebelumnya diswap pada permutation_number
            if (st_num[k] != 1) {
                char temp = permutation_number[k];
                permutation_number[k] = permutation_number[k-1];
                permutation_number[k-1] = temp;
                break;
            }
        }
        // string printSTR;
        // printSTR.resize(total_unique_words);
        // for (int i=0; i<total_unique_words; i++)
        //     printSTR[i] = word_list[permutation_number[i]];
        // std::cout << printSTR.data() << '\n';
        // std::cout << '\n';
        for (int i=0; i<total_unique_words; i++)
            std::cout << word_list[permutation_number[i]];
        std::cout << '\n';

        *isCorrect = process(permutation_number, word_list);
        if (*isCorrect) return permutation_number;
        /*
            Process
        */
        // for (int k = 0; k < total_unique_words+1; k++) 
        //     std::cout << st_num[k] << ' ';
        // std::cout << '\n';
        for (int i=total_unique_words-2; i>=0; i--) {
            if (st_num[i] == factorial_arr[i+1]) {
                for (int j = i; j >= 0; j--)
                    st_num[j] = 0;
            }
        }
    }
    /*
    1 1 1
    1 2 2
    1 1 3
    1 2 4
    1 1 5
    1 2 6
    */

    return permutation_number;
}

bool process(unsigned short int permutation_number[], string word_list) {
    
    return false;
}

int main() {
    // huruf yang ingin dikombinasi lalu dipermutasi
    string word_list = "0123456789";
    // std::cout << word_list.length() << '\n';

    // banyaknya huruf yang berbeda
    unsigned short int total_unique_words = 3;

    // kombinasi angka 
    unsigned short int len_combination_number = total_unique_words+1;
    unsigned short int combination_number[len_combination_number];
    // inisialisasi combination_number = {0, 1, ...}
    for (int i=0; i < total_unique_words; i++)
        combination_number[i] = i;
    // melakukan initialisasi nilai pada indeks terakhir sebesar panjangnya word_list untuk melakukan kombinasi total_unique_words dari 10 angka {0,1,2,3,4,5,6,7,8,9}
    combination_number[total_unique_words] = word_list.length();

    // list hasil permutasi dari 0 sampai 10
    int factorial_arr[len_combination_number+1];
    factorial_arr[0] = 1;
    for (int i=1; i<len_combination_number+1; i++)
        factorial_arr[i] = factorial_arr[i-1]*i;
    for (int i=0; i<len_combination_number+1; i++)
        std::cout << factorial_arr[i] << ' ';
    std::cout << '\n';

    // // digunakan untuk permutasi dari combination number
    unsigned short int *st;

    // kombinasi total_unique_words from 10 (combinatoric)
    int i = total_unique_words-1;

    // untuk mendeteksi apakah permutasinya benar atau tidak
    bool isCorrect = false;
    
    // for (int i=0; i<total_unique_words; i++)
    //     std::cout << word_list[combination_number[i]];
    // std::cout << '\n';

    // Melakukan kombinasi ambil sebanyak total_unique_words dari 9
    /*
    0123
    0124
    0125
    0126
    0127
    0128
    0129
    0134
    0135
    0136
    0137
    0138
    0139
    0145
    0146
    0147
    0148
    0149
    0156
    0157
    0158
    0159
    0167
    0168
    0169
    0178
    0179
    0189
    0234
    0235
    .
    .
    .
    */
    st = permutation(combination_number, total_unique_words, word_list, factorial_arr, &isCorrect);
    if (!isCorrect) {
        delete[] st;
        while (true) {
            if (combination_number[i] != combination_number[i+1]-1) {
                combination_number[i]++;
                for (int j=0; j<total_unique_words; j++)
                    std::cout << word_list[combination_number[j]];
                std::cout << '\n';
                st = permutation(combination_number, total_unique_words, word_list, factorial_arr, &isCorrect);
                if (!isCorrect) delete[] st;
                else break;
            } else
            if (i == 0) break;
            else
            if (combination_number[i] != combination_number[i-1]+1) {
                combination_number[i-1]++;
                do {
                    combination_number[i++] = combination_number[i-1]+1;
                } while (i < total_unique_words);
                i--;
                for (int j=0; j<total_unique_words; j++)
                    std::cout << word_list[combination_number[j]];
                std::cout << '\n';
                st = permutation(combination_number, total_unique_words, word_list, factorial_arr, &isCorrect);
                if (!isCorrect) delete[] st;
                else break;
            } else
            {
                i--;
            }
        }
    }

    std::cout << "Finished" << '\n';
    std::cout << isCorrect << '\n';
    std::cout << 's';


    return 0;
}