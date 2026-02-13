# Differential Cryptanalysis of DES 🔐

Implementation of the DES (Data Encryption Standard) algorithm in C++  
with a practical demonstration of **differential cryptanalysis** on the last round S-box.

---

## 📌 Project Overview

This project includes:

- Full implementation of DES encryption
- Key schedule generation
- S-box processing
- Differential distribution table construction
- Plaintext pair generation with controlled input differences
- Subkey recovery for S-box 1 (last round)
- Statistical analysis of attack success rate

The project demonstrates how differential cryptanalysis can partially recover
subkey bits of the final round in DES.

---

## 🧠 What is Implemented

### 🔹 DES Core
- Initial permutation (IP)
- Final permutation (IP⁻¹)
- Expansion permutation (E)
- 8 S-boxes
- P permutation
- 16-round Feistel structure
- Key schedule (PC-1, PC-2, left shifts)

### 🔹 Differential Cryptanalysis
- Differential distribution table construction
- Plaintext pair generation with fixed ΔP
- Ciphertext difference analysis
- Subkey candidate ranking
- Real key verification
- Success rate calculation

---

## 🛠 Technologies

- C++
- STL (vector, map, algorithm, bitset)
- Random generation (mt19937)
- Bitwise operations

---

## 📊 Example Output

- Encrypted ciphertext (HEX)
- Real last-round subkey bits
- Top key candidates
- Match statistics
- Attack success rate (%)

---

## 🎯 Educational Purpose

This project was developed as an educational demonstration of:

- Symmetric encryption internals
- Feistel network structure
- Practical cryptanalysis concepts
- Statistical key recovery techniques

---

⚠ Disclaimer

DES is cryptographically broken and should not be used in real systems.
This implementation is for educational and research purposes only.

---

👨‍💻 Author: Stanislau Chaiko
