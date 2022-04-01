#include <bits/stdc++.h>
#define ALPHABET_SIZE 26
// #define int unsigned int

using namespace std;

int main()
{
    int n, maxlen = 0;

    cin >> n;
    vector<string> words(n);
    for (int i = 0; i < n; i+=1)
    {
        cin >> words[i];
        maxlen = max(maxlen, (int) words[i].length());
    }
    sort(words.begin(), words.end());
    cout <<  " maxlen: " << maxlen << "\n";
    
    int hashmap[ALPHABET_SIZE][maxlen];
    bool used_positions[maxlen];

    memset(hashmap, 0, sizeof(hashmap));
    memset(used_positions, false, sizeof(used_positions));

    for (int i = 0; i < n; i+=1)
    {
        int l = words[i].length();
        int last_modified = 0;

        // fill hash map with ones if the given cell is not initialized,
        // which occurs when its value is 0
        for (int j = 0; j < l; j+=1)
        {
            int c = (int) (words[i][j] - 'A');
            if (hashmap[c][j] == 0)
            {
                hashmap[c][j] = 1;
                last_modified = j;
            }
        }

        // compute the index in the hash table for the current word
        int index = 1;
        for (int j = 0; j < l; j+=1)
        {
            int c = (int) (words[i][j] - 'A');
            index = (hashmap[c][j] * index) % n;
        }

        // if the index hasn't been used, then we left as it is
        if (! used_positions[index])
        {
            used_positions[index] = true;
            continue;
        }

        // otherwise, there occurred a collision, which we will try
        // to eliminate by backtracking our last decision, which was
        // the value we set to the a non-initialized cell

        // recompute index, but do not include the last modified cell,
        index = 1;
        for (int j = 0; j < l; j+=1)
        {
            if (j == last_modified) continue;
            int c = (int) (words[i][j] - 'A');
            index = (hashmap[c][j] * index) % n;
        }

        // we did not include the last modified cell in the computation
        // of index, which means THIS
        for (int ii = 1; ii <= ALPHABET_SIZE; ii+=1) {
            int cc = (ii * index) % n;
            if (! used_positions[cc]) {
                int j = (int) (words[i][last_modified] - 'A');
                hashmap[j][last_modified] = ii;
                used_positions[cc] = true;
                break;
            }
        }
    }

    for (int jj = 0; jj < ALPHABET_SIZE; jj+=1) {
        cout << (char) ('A' + jj) << " ";
    }
    cout << "\n";
    for (int ii = 0; ii < maxlen; ii+=1) {
        for (int jj = 0; jj < ALPHABET_SIZE; jj+=1) {
            cout << hashmap[jj][ii] << " ";
        }
        cout << "\n";
    }
    cout << "\n";

    for (auto word : words)
    {
        int index = 1;
        int l = (int) word.length();
        for (int j = 0; j < l; j+=1)
        {
            int c = (int) (word[j] - 'A');
            index = (hashmap[c][j] * index) % n;
        }
        cout << word << "  " << index << "\n";
    }

    return 0;
}
