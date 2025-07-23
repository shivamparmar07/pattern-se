# 🔍 Pattern Search Engine

A C++ application that implements and compares three classic string matching algorithms — **Naive**, **Knuth-Morris-Pratt (KMP)**, and **Rabin-Karp** — for finding occurrences of a pattern within a given text.

This project benchmarks each algorithm in terms of **match positions** and **execution time**, helping understand the strengths and weaknesses of each method.

---

## 📌 Features

- Pattern search using:
  - ✅ Naive Algorithm
  - ✅ KMP (Knuth-Morris-Pratt)
  - ✅ Rabin-Karp (Rolling Hash)
- Execution time comparison using `chrono`
- Works on large paragraphs and patterns
- Clean CLI interface

---

## 📸 Sample Output

Enter the text:
ababcabcabababd
Enter the pattern:
ababd

Results:
Naive Matches: 1 | Time: 47 μs
KMP Matches: 1 | Time: 19 μs
Rabin-Karp: 1 | Time: 25 μs


---

## 🧠 Algorithms Explained

### 🔹 Naive Search
Checks the pattern at every position of the text.
- Time: O(n × m)
- Simple, but slow for large inputs.

### 🔹 KMP Search
Uses a **prefix table (LPS array)** to avoid redundant comparisons.
- Time: O(n + m)
- Great for real-time search applications.

### 🔹 Rabin-Karp
Uses a **rolling hash** function to find potential matches quickly.
- Time: O(n + m) average, O(n × m) worst case
- Useful when matching multiple patterns or files.

---

## 🚀 Getting Started

### 🧱 Prerequisites
- C++ compiler (`g++`, `clang++`, etc.)
- C++11 or above

### 🛠️ Build & Run

```bash
g++ -std=c++11 main.cpp -o pattern-search
./pattern-search
```
