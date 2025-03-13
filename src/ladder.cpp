#include "ladder.h"
#include <cstdlib>
#include <algorithm>
#include <cctype>

using namespace std;

string to_lower(string& s){
    for (auto &c : s)c = tolower(c);
    return s;
}

void error(string word1, string word2, string msg) {
    cerr << "Start: " << word1 << "End: " << word2 << " " << msg << "\n";
    exit(1); 
}

bool edit_distance_within(const string& str1, const string& str2, int d) {
    int n = str1.size(), m = str2.size();

    if (abs(n - m) > 1) return 0;
    int i = 0, j = 0, edits = 0;
    while (i < n && j < m) {
        if(str1[i] != str2[j]) {
            if (++edits > d) return 0;
            if (n == m){
                i++; j++;
            }
            else if (n < m) j++;
            else i++;
        }
        else {
            i++;
            j++;
        }
    }

    return edits + (n - i) + (m - j) <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return(edit_distance_within(word1, word2, 1));
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> vis;
    vis.insert(begin_word);
    while (!ladder_queue.empty()) {
        auto ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();

        for (const string& word : word_list) {
            if (is_adjacent(last_word, word)) {
                if (!vis.count(word)) {
                    vis.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if (word == end_word) return new_ladder;
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    return {};
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);
    string word;
    while (file >> word) word_list.insert(to_lower(word));
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) cout << "No word ladder found\n";
    for (int i = 0; i < ladder.size(); i++) cout << ladder[i] << " "; 
    cout << "\n";
}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "/home/ychao13/ICS46/ics-46-hw-9-twleochao/src/words.txt");
    string start, end;
    cout << "Enter start word: ";
    cin >> start;
    cout << "Enter end word: ";
    cin >> end;

    start = to_lower(start);
    end = to_lower(end);

    if(start == end) error(start, end, "start and end cannot be the same word");
    if (!word_list.count(end)) error(start, end, "end not in word list");
    auto ladder = generate_word_ladder(start, end, word_list);
    print_word_ladder(ladder);
}