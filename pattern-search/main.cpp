#include <iostream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;
using namespace chrono;

// Naive Pattern Search
vector<int> naiveSearch(const string &text, const string &pattern) {
    vector<int> positions;
    int n = text.length(), m = pattern.length();
    for (int i = 0; i <= n - m; ++i) {
        int j = 0;
        while (j < m && text[i + j] == pattern[j])
            ++j;
        if (j == m)
            positions.push_back(i);
    }
    return positions;
}

// KMP Prefix Table
vector<int> buildLPS(const string &pattern) {
    int m = pattern.length();
    vector<int> lps(m, 0);
    int len = 0;
    for (int i = 1; i < m; ) {
        if (pattern[i] == pattern[len])
            lps[i++] = ++len;
        else if (len != 0)
            len = lps[len - 1];
        else
            lps[i++] = 0;
    }
    return lps;
}

// KMP Pattern Search
vector<int> KMPSearch(const string &text, const string &pattern) {
    vector<int> positions;
    int n = text.length(), m = pattern.length();
    vector<int> lps = buildLPS(pattern);
    int i = 0, j = 0;
    while (i < n) {
        if (pattern[j] == text[i]) {
            ++i; ++j;
        }
        if (j == m) {
            positions.push_back(i - j);
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            j = j != 0 ? lps[j - 1] : 0;
        }
    }
    return positions;
}

// Rabin-Karp Pattern Search
vector<int> rabinKarp(const string &text, const string &pattern, int prime = 101) {
    vector<int> positions;
    int n = text.length(), m = pattern.length();
    if (m > n) return positions;

    long long hashP = 0, hashT = 0, h = 1;
    int d = 256;

    for (int i = 0; i < m - 1; ++i)
        h = (h * d) % prime;

    for (int i = 0; i < m; ++i) {
        hashP = (d * hashP + pattern[i]) % prime;
        hashT = (d * hashT + text[i]) % prime;
    }

    for (int i = 0; i <= n - m; ++i) {
        if (hashP == hashT) {
            int j = 0;
            for (; j < m; ++j)
                if (text[i + j] != pattern[j]) break;
            if (j == m)
                positions.push_back(i);
        }
        if (i < n - m) {
            hashT = (d * (hashT - text[i] * h) + text[i + m]) % prime;
            if (hashT < 0) hashT += prime;
        }
    }
    return positions;
}

// Time and run each algorithm
void runAndBenchmark(const string &text, const string &pattern) {
    auto start = high_resolution_clock::now();
    auto resultNaive = naiveSearch(text, pattern);
    auto end = high_resolution_clock::now();
    auto timeNaive = duration_cast<microseconds>(end - start).count();

    start = high_resolution_clock::now();
    auto resultKMP = KMPSearch(text, pattern);
    end = high_resolution_clock::now();
    auto timeKMP = duration_cast<microseconds>(end - start).count();

    start = high_resolution_clock::now();
    auto resultRK = rabinKarp(text, pattern);
    end = high_resolution_clock::now();
    auto timeRK = duration_cast<microseconds>(end - start).count();

    cout << "\nResults:\n";
    cout << "Naive Matches: " << resultNaive.size() << " | Time: " << timeNaive << " μs\n";
    cout << "KMP Matches: " << resultKMP.size() << " | Time: " << timeKMP << " μs\n";
    cout << "Rabin-Karp: " << resultRK.size() << " | Time: " << timeRK << " μs\n";
}

int main() {
    string text, pattern;
    cout << "Enter the text:\n";
    getline(cin, text);
    cout << "Enter the pattern:\n";
    getline(cin, pattern);

    runAndBenchmark(text, pattern);
    return 0;
}
