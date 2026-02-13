#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <map>
#include <algorithm>
#include <random>
#include <iomanip>
using namespace std;

// Таблицы (оставлены без изменений)
int P_1[64] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25
};

int P[32] = {
    16, 7, 20, 21, 29, 12, 28, 17,
    1, 15, 23, 26, 5, 18, 31, 10,
    2, 8, 24, 14, 32, 27, 3, 9,
    19, 13, 30, 6, 22, 11, 4, 25
};

int IP[64] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

int E[48] = {
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1
};

int PC_1[56] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4
};

int PC_2[48] = {
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

int s[8][4][16] = {
    {
        {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
        {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
        {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
        {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
    },
    {
        {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
        {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
        {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
        {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
    },
    {
        {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
        {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
        {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
        {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
    },
    {
        {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
        {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
        {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
        {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
    },
    {
        {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
        {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
        {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
        {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
    },
    {
        {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
        {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
        {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
        {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
    },
    {
        {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
        {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
        {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
        {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
    },
    {
        {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
        {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
        {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
        {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
    }
};

// Функции перевода
string Hex_to_Bin(char c) {
    return bitset<4>(stoi(string(1, c), nullptr, 16)).to_string();
}

char Bin_to_Hex(string b) {
    return "0123456789ABCDEF"[bitset<4>(b).to_ulong()];
}

// Левый сдвиг
void left_shift(string& s, int n) {
    s = s.substr(n) + s.substr(0, n);
}

// Основной алгоритм DES
string DES_encrypt(string text_hex, string key_hex) {
    // Преобразование hex → bin
    string text_bin, key_bin;
    for (char c : text_hex) text_bin += Hex_to_Bin(c);
    for (char c : key_hex) key_bin += Hex_to_Bin(c);

    // Начальная перестановка
    string perm_text(64, '0');
    for (int i = 0; i < 64; i++) perm_text[i] = text_bin[IP[i] - 1];

    // Генерация ключей
    string perm_key(56, '0');
    for (int i = 0; i < 56; i++) perm_key[i] = key_bin[PC_1[i] - 1];
    string C = perm_key.substr(0, 28), D = perm_key.substr(28, 28);
    vector<string> round_keys;
    for (int round : {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1}) {
        left_shift(C, round); left_shift(D, round);
        string CD = C + D;
        string subkey(48, '0');
        for (int i = 0; i < 48; i++) subkey[i] = CD[PC_2[i] - 1];
        round_keys.push_back(subkey);
    }

    // Раунды
    string L = perm_text.substr(0, 32), R = perm_text.substr(32, 32);
    for (int i = 0; i < 16; i++) {
        string expanded(48, '0');
        for (int j = 0; j < 48; j++) expanded[j] = R[E[j] - 1];
        string xored(48, '0');
        for (int j = 0; j < 48; j++) xored[j] = ((expanded[j] - '0') ^ (round_keys[i][j] - '0')) + '0';

        string sbox_output;
        for (int b = 0; b < 8; b++) {
            string block = xored.substr(b * 6, 6);
            int row = stoi(block.substr(0, 1) + block.substr(5, 1), nullptr, 2);
            int col = stoi(block.substr(1, 4), nullptr, 2);
            sbox_output += bitset<4>(s[b][row][col]).to_string();
        }

        string permuted(32, '0');
        for (int j = 0; j < 32; j++) permuted[j] = sbox_output[P[j] - 1];
        string newR(32, '0');
        for (int j = 0; j < 32; j++) newR[j] = ((permuted[j] - '0') ^ (L[j] - '0')) + '0';
        L = R;
        R = newR;
    }

    // Обратный порядок и финальная перестановка
    string preoutput = R + L;
    string final_output(64, '0');
    for (int i = 0; i < 64; i++) final_output[i] = preoutput[P_1[i] - 1];

    // Перевод в HEX
    string hex_result;
    for (int i = 0; i < 64; i += 4)
        hex_result += Bin_to_Hex(final_output.substr(i, 4));

    return hex_result;
}

class DifferentialCryptanalysis {
private:
    vector<map<pair<int, int>, int>> sbox_diff_tables;

    void build_differential_tables() {
        sbox_diff_tables.resize(8);

        for (int sbox = 0; sbox < 8; sbox++) {
            for (int input_diff = 0; input_diff < 64; input_diff++) {
                map<int, int> output_counts;

                for (int input = 0; input < 64; input++) {
                    int output1 = s[sbox][((input >> 4) & 0x2) | (input & 0x1)]
                        [(input >> 1) & 0xF];
                    int output2 = s[sbox][(((input ^ input_diff) >> 4) & 0x2) |
                        ((input ^ input_diff) & 0x1)]
                        [((input ^ input_diff) >> 1) & 0xF];
                    int output_diff = output1 ^ output2;
                    output_counts[output_diff]++;
                }

                int max_count = 0;
                int best_output_diff = 0;
                for (const auto& item : output_counts) {
                    if (item.second > max_count) {
                        max_count = item.second;
                        best_output_diff = item.first;
                    }
                }

                sbox_diff_tables[sbox][{input_diff, best_output_diff}] = max_count;
            }
        }
    }

public:
    DifferentialCryptanalysis() {
        build_differential_tables();
    }
    // Генерирует пары (P, P') с заданной разницей ΔP
    vector<pair<string, string>> generate_plaintext_pairs(const string& input_diff_hex, int num_pairs) {
        string input_diff_bin;
        for (char c : input_diff_hex) input_diff_bin += Hex_to_Bin(c);

        vector<pair<string, string>> pairs;
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, 15);

        for (int i = 0; i < num_pairs; i++) {
            string plaintext1;
            for (int j = 0; j < 16; j++) {
                plaintext1 += "0123456789ABCDEF"[dis(gen)];
            }

            string plaintext1_bin;
            for (char c : plaintext1) plaintext1_bin += Hex_to_Bin(c);

            string plaintext2_bin;
            for (int j = 0; j < 64; j++) {
                plaintext2_bin += ((plaintext1_bin[j] - '0') ^ (input_diff_bin[j] - '0')) + '0';
            }

            string plaintext2;
            for (int j = 0; j < 64; j += 4) {
                plaintext2 += Bin_to_Hex(plaintext2_bin.substr(j, 4));
            }

            pairs.emplace_back(plaintext1, plaintext2);
        }

        return pairs;
    }

    vector<int> recover_subkey_bits(const vector<pair<string, string>>& plaintext_pairs,
        const vector<pair<string, string>>& ciphertext_pairs) {
        // Целевой S-box (0 = S-box 1)
        const int target_sbox = 0;

        // Вектор для подсчета совпадений по всем возможным ключам (6 бит => 64 варианта)
        vector<int> possible_keys(64, 0);

        // Обрабатываем каждую пару открытых/шифрованных текстов
        for (size_t i = 0; i < plaintext_pairs.size(); i++) {
            // Получаем пары текстов
            const string& p1 = plaintext_pairs[i].first;
            const string& p2 = plaintext_pairs[i].second;
            const string& c1 = ciphertext_pairs[i].first;
            const string& c2 = ciphertext_pairs[i].second;

            // Конвертируем шифртексты из HEX в бинарный формат
            string c1_bin, c2_bin;
            for (char c : c1) c1_bin += Hex_to_Bin(c);
            for (char c : c2) c2_bin += Hex_to_Bin(c);

            // Отменяем финальную перестановку IP⁻¹ (используем обратную перестановку P_1)
            string c1_perm(64, '0');
            string c2_perm(64, '0');
            for (int j = 0; j < 64; j++) {
                c1_perm[P_1[j] - 1] = c1_bin[j];
                c2_perm[P_1[j] - 1] = c2_bin[j];
            }

            // Разделяем на левые и правые части (структура Фейстеля)
            // R16 - правые 32 бита после последнего раунда
            string R16_1 = c1_perm.substr(32, 32);
            string L16_1 = c1_perm.substr(0, 32);
            string R16_2 = c2_perm.substr(32, 32);
            string L16_2 = c2_perm.substr(0, 32);

            // L15 = R16 (по структуре Фейстеля)
            string L15_1 = R16_1;
            string L15_2 = R16_2;

            // Вычисляем R15 = L16 ⊕ F(R16, K16)
            string R15_1(32, '0');
            string R15_2(32, '0');
            for (int j = 0; j < 32; j++) {
                R15_1[j] = ((L16_1[j] - '0') ^ (L15_1[j] - '0')) + '0';
                R15_2[j] = ((L16_2[j] - '0') ^ (L15_2[j] - '0')) + '0';
            }

            // Применяем расширяющую перестановку E к R15 (32->48 бит)
            string ER15_1(48, '0');
            string ER15_2(48, '0');
            for (int j = 0; j < 48; j++) {
                ER15_1[j] = R15_1[E[j] - 1];
                ER15_2[j] = R15_2[E[j] - 1];
            }

            // Извлекаем входную разницу для целевого S-box (6 бит)
            string in_diff = ER15_1.substr(target_sbox * 6, 6);
            // Извлекаем ожидаемую выходную разницу (4 бита)
            string out_diff_bits = R16_1.substr(target_sbox * 4, 4);

            // Перебираем все 64 возможных варианта ключа (6 бит)
            for (int key_guess = 0; key_guess < 64; key_guess++) {
                // Получаем входы S-box после XOR с ключом
                int input1 = stoi(ER15_1.substr(target_sbox * 6, 6), nullptr, 2);
                int input2 = stoi(ER15_2.substr(target_sbox * 6, 6), nullptr, 2);

                // Применяем кандидата ключа
                int sbox_input1 = input1 ^ key_guess;
                int sbox_input2 = input2 ^ key_guess;

                // Вычисляем выходы S-box (4 бита)
                int output1 = s[target_sbox][((sbox_input1 >> 4) & 0x2) | (sbox_input1 & 0x1)]
                    [(sbox_input1 >> 1) & 0xF];
                int output2 = s[target_sbox][((sbox_input2 >> 4) & 0x2) | (sbox_input2 & 0x1)]
                    [(sbox_input2 >> 1) & 0xF];

                // Вычисляем реальную выходную разницу
                int actual_out_diff = output1 ^ output2;
                // Ожидаемая разница из шифртекста
                int expected_out_diff = stoi(out_diff_bits, nullptr, 2);

                // Если разницы совпали, увеличиваем счетчик для этого ключа
                if (actual_out_diff == expected_out_diff) {
                    possible_keys[key_guess]++;
                }
            }
        }

        vector<int> best_keys;
        int max_count = *max_element(possible_keys.begin(), possible_keys.end());

        for (int i = 0; i < 64; i++) {
            if (possible_keys[i] == max_count) {
                best_keys.push_back(i);
            }
        }

        return best_keys;
    }

    string recover_key_with_verification(const string& input_diff_hex, int num_pairs, const string& real_key_hex) {
        // Конвертируем реальный ключ в бинарный формат
        string real_key_bin;
        for (char c : real_key_hex) real_key_bin += Hex_to_Bin(c);

        // Получаем реальный подключ последнего раунда
        string perm_key(56, '0');
        for (int i = 0; i < 56; i++) perm_key[i] = real_key_bin[PC_1[i] - 1];

        string C = perm_key.substr(0, 28), D = perm_key.substr(28, 28);
        vector<string> round_keys;

        // Генерируем все 16 подключей
        for (int round : {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1}) {
            left_shift(C, round);
            left_shift(D, round);
            string CD = C + D;
            string subkey(48, '0');
            for (int i = 0; i < 48; i++) subkey[i] = CD[PC_2[i] - 1];
            round_keys.push_back(subkey);
        }

        // Берем подключ последнего раунда (16-й)
        string last_round_key = round_keys[15];

        // Извлекаем биты для S-box 1 (биты 1-6)
        string sbox1_key_bits = last_round_key.substr(0, 6);
        int real_sbox1_key = stoi(sbox1_key_bits, nullptr, 2);

        // Генерируем пары текстов и выполняем атаку
        auto plaintext_pairs = generate_plaintext_pairs(input_diff_hex, num_pairs);
        vector<pair<string, string>> ciphertext_pairs;

        for (const auto& pair : plaintext_pairs) {
            ciphertext_pairs.emplace_back(
                DES_encrypt(pair.first, real_key_hex),
                DES_encrypt(pair.second, real_key_hex)
            );
        }

        auto recovered_keys = recover_subkey_bits(plaintext_pairs, ciphertext_pairs);

        // Формируем результат
        string result = "Реальный ключ для S-box 1: " + to_string(real_sbox1_key) + " (";
        result += sbox1_key_bits + ")\n";

        result += "Восстановленные кандидаты: ";
        for (int key : recovered_keys) {
            bitset<6> bits(key);
            result += to_string(key) + " (" + bits.to_string() + "), ";
        }

        // Проверяем, есть ли реальный ключ среди кандидатов
        bool found = false;
        for (int key : recovered_keys) {
            if (key == real_sbox1_key) {
                found = true;
                break;
            }
        }

        result += "\nРеальный ключ " + string(found ? "найден" : "не найден") + " среди кандидатов";

        return result;
    }

    void print_analysis_details(const vector<pair<string, string>>& plaintext_pairs,
        const vector<pair<string, string>>& ciphertext_pairs,
        const string& real_key_hex) {
        // 1. Выводим информацию о реальном ключе
        cout << "=== АНАЛИЗ КЛЮЧА ===" << endl;
        cout << "Реальный ключ (hex): " << real_key_hex << endl;

        string real_key_bin;
        for (char c : real_key_hex) real_key_bin += Hex_to_Bin(c);
        cout << "Реальный ключ (bin): " << real_key_bin << endl;

        // 2. Выводим информацию о парах текстов
        cout << "\n=== АНАЛИЗ ПАР ТЕКСТОВ ===" << endl;
        cout << "Всего пар: " << plaintext_pairs.size() << endl;

        for (size_t i = 0; i < min(plaintext_pairs.size(), static_cast<size_t>(3)); i++) {
            cout << "Пара #" << i + 1 << ":\n";
            cout << "  Открытый текст 1: " << plaintext_pairs[i].first
                << " (" << hex_to_bin_str(plaintext_pairs[i].first) << ")\n";
            cout << "  Открытый текст 2: " << plaintext_pairs[i].second
                << " (" << hex_to_bin_str(plaintext_pairs[i].second) << ")\n";
            cout << "  Разница: " << get_xor_diff(plaintext_pairs[i].first, plaintext_pairs[i].second) << endl;
            cout << "  Шифртекст 1: " << ciphertext_pairs[i].first << endl;
            cout << "  Шифртекст 2: " << ciphertext_pairs[i].second << endl;
            cout << "  Разница шифртекстов: " << get_xor_diff(ciphertext_pairs[i].first, ciphertext_pairs[i].second) << endl;
        }

        // 3. Анализ S-box 1
        analyze_sbox1(plaintext_pairs, ciphertext_pairs, real_key_hex);
    }

private:
    string hex_to_bin_str(const string& hex) {
        string bin;
        for (char c : hex) bin += Hex_to_Bin(c);
        return bin;
    }

    string get_xor_diff(const string& a, const string& b) {
        string bin_a = hex_to_bin_str(a);
        string bin_b = hex_to_bin_str(b);
        string diff;
        for (size_t i = 0; i < bin_a.size(); i++) {
            diff += ((bin_a[i] - '0') ^ (bin_b[i] - '0')) ? '1' : '0';
        }
        return diff;
    }

    void analyze_sbox1(const vector<pair<string, string>>& plaintext_pairs,
        const vector<pair<string, string>>& ciphertext_pairs,
        const string& real_key_hex) {
        const int target_sbox = 0;
        vector<int> possible_keys(64, 0);
        map<int, vector<int>> key_stats;

        cout << "\n=== ПОДРОБНЫЙ АНАЛИЗ S-BOX 1 ===" << endl;

        // Получаем реальный подключ для S-box 1
        string real_key_bin;
        for (char c : real_key_hex) real_key_bin += Hex_to_Bin(c);

        string perm_key(56, '0');
        for (int i = 0; i < 56; i++) perm_key[i] = real_key_bin[PC_1[i] - 1];

        string C = perm_key.substr(0, 28), D = perm_key.substr(28, 28);
        vector<string> round_keys;

        for (int round : {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1}) {
            left_shift(C, round); left_shift(D, round);
            string CD = C + D;
            string subkey(48, '0');
            for (int i = 0; i < 48; i++) subkey[i] = CD[PC_2[i] - 1];
            round_keys.push_back(subkey);
        }

        string last_round_key = round_keys[15];
        string real_sbox1_key_bits = last_round_key.substr(0, 6);
        int real_sbox1_key = stoi(real_sbox1_key_bits, nullptr, 2);

        cout << "Реальный подключ для S-box 1: " << real_sbox1_key
            << " (bin: " << real_sbox1_key_bits << ")" << endl;

        // Анализируем каждую пару
        for (size_t i = 0; i < plaintext_pairs.size(); i++) {
            const string& c1 = ciphertext_pairs[i].first;
            const string& c2 = ciphertext_pairs[i].second;

            string c1_bin, c2_bin;
            for (char c : c1) c1_bin += Hex_to_Bin(c);
            for (char c : c2) c2_bin += Hex_to_Bin(c);

            // Отменяем финальную перестановку
            string c1_perm(64, '0');
            string c2_perm(64, '0');
            for (int j = 0; j < 64; j++) {
                c1_perm[P_1[j] - 1] = c1_bin[j];
                c2_perm[P_1[j] - 1] = c2_bin[j];
            }

            string R16_1 = c1_perm.substr(32, 32);
            string L16_1 = c1_perm.substr(0, 32);
            string R16_2 = c2_perm.substr(32, 32);
            string L16_2 = c2_perm.substr(0, 32);

            // Вычисляем R15 и L15
            string L15_1 = R16_1;
            string L15_2 = R16_2;

            string R15_1(32, '0');
            string R15_2(32, '0');
            for (int j = 0; j < 32; j++) {
                R15_1[j] = ((L16_1[j] - '0') ^ (L15_1[j] - '0')) + '0';
                R15_2[j] = ((L16_2[j] - '0') ^ (L15_2[j] - '0')) + '0';
            }

            // Расширяем R15
            string ER15_1(48, '0');
            string ER15_2(48, '0');
            for (int j = 0; j < 48; j++) {
                ER15_1[j] = R15_1[E[j] - 1];
                ER15_2[j] = R15_2[E[j] - 1];
            }

            // Получаем входную разницу для S-box 1
            string in_diff = ER15_1.substr(target_sbox * 6, 6);
            string out_diff_bits = R16_1.substr(target_sbox * 4, 4);
            int expected_out_diff = stoi(out_diff_bits, nullptr, 2);

            // Проверяем все возможные ключи
            for (int key_guess = 0; key_guess < 64; key_guess++) {
                int input1 = stoi(ER15_1.substr(target_sbox * 6, 6), nullptr, 2);
                int input2 = stoi(ER15_2.substr(target_sbox * 6, 6), nullptr, 2);

                int sbox_input1 = input1 ^ key_guess;
                int sbox_input2 = input2 ^ key_guess;

                int output1 = s[target_sbox][((sbox_input1 >> 4) & 0x2) | (sbox_input1 & 0x1)]
                    [(sbox_input1 >> 1) & 0xF];
                int output2 = s[target_sbox][((sbox_input2 >> 4) & 0x2) | (sbox_input2 & 0x1)]
                    [(sbox_input2 >> 1) & 0xF];

                int actual_out_diff = output1 ^ output2;

                if (actual_out_diff == expected_out_diff) {
                    possible_keys[key_guess]++;
                    key_stats[key_guess].push_back(i);
                }
            }
        }

        // Выводим топ-5 кандидатов
        cout << "\nТОП-5 кандидатов для ключа S-box 1:" << endl;
        vector<pair<int, int>> key_counts;
        for (int i = 0; i < 64; i++) {
            key_counts.emplace_back(i, possible_keys[i]);
        }

        sort(key_counts.begin(), key_counts.end(),
            [](const pair<int, int>& a, const pair<int, int>& b) {
                return a.second > b.second;
            });

        for (int i = 0; i < 5; i++) {
            cout << i + 1 << ". Ключ " << key_counts[i].first
                << " (bin: " << bitset<6>(key_counts[i].first).to_string() << ")"
                << " - совпадений: " << key_counts[i].second;

            if (key_counts[i].first == real_sbox1_key) {
                cout << " <-- РЕАЛЬНЫЙ КЛЮЧ";
            }
            cout << endl;
        }

        // Дополнительная статистика
        cout << "\nДОПОЛНИТЕЛЬНАЯ СТАТИСТИКА:" << endl;
        cout << "Всего пар, поддерживающих реальный ключ: "
            << possible_keys[real_sbox1_key] << "/" << plaintext_pairs.size() << endl;

        double success_rate = static_cast<double>(possible_keys[real_sbox1_key]) / plaintext_pairs.size();
        cout << "Успешность атаки: " << fixed << setprecision(2) << success_rate * 100 << "%" << endl;
    }
};

// Пример использования
int main() {
    setlocale(LC_ALL, "Russian");
    string plaintext = "0123456789ABCDEF";
    string real_key = "133457799BBCDFF1";

    string encrypted = DES_encrypt(plaintext, real_key);
    cout << "Encrypted (HEX): " << encrypted << endl;

    DifferentialCryptanalysis dc;
    string input_diff = "4008000004000000";
    int num_pairs = 1000;

    string result = dc.recover_key_with_verification(input_diff, num_pairs, real_key);
    cout << result << endl;

    auto plaintext_pairs = dc.generate_plaintext_pairs(input_diff, num_pairs);

    // Шифруем пары
    vector<pair<string, string>> ciphertext_pairs;
    for (const auto& pair : plaintext_pairs) {
        ciphertext_pairs.emplace_back(
            DES_encrypt(pair.first, real_key),
            DES_encrypt(pair.second, real_key)
        );
    }

    // Выводим подробный анализ
    dc.print_analysis_details(plaintext_pairs, ciphertext_pairs, real_key);
    return 0;
}
