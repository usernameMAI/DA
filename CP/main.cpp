#include <iostream>
#include <vector>
#include <string>


using namespace std;


const char END = 'E';


struct LZ77Triples {
    int shift;
    int size;
    char character;
};


ostream& operator << (ostream &os, const LZ77Triples &triple) {
    os << triple.shift << ' ' << triple.size;
    os << ' ' << triple.character;
    return os;
}


string decoder(vector<LZ77Triples>& triples) {
    string buffer;
    for (LZ77Triples &triple: triples) {
        int position = int(buffer.size()) - triple.shift;
        for (int i = 0; i < triple.size; ++i) {
            buffer += buffer[position + i];
        }
        if (triple.character != ' ') {
            buffer += triple.character;
        }
    }
    return buffer;
}


vector<LZ77Triples> encoder(string& text) {
    vector<LZ77Triples> triples;
    int border = 0;
    while (border < text.size()) {
        int max_shift = 0;
        int max_size = 0;
        char next_character = text[border];
        for (int i = 0; i < border; ++i) {
            if (text[i] == text[border]) {
                int current_shift = border - i;
                int current_size = 1;
                char current_next_character = text[border + 1];
                for (int j = 1; j + i < text.size() and text[i + j] == text[border + j]; ++j) {
                    ++current_size;
                    current_next_character = text[border + current_size];
                }
                if (current_size >= max_size) {
                    max_shift = current_shift;
                    max_size = current_size;
                    next_character = (border + max_size == text.size()) ? ' ' : current_next_character;
                }
            }
        }
        triples.push_back({max_shift, max_size, next_character});
        border += max_size + 1;
    }
    return triples;
}


int main() {
    string command;
    cin >> command;
    if (command == "compress") {
        string text;
        cin >> text;
        vector<LZ77Triples> triples = encoder(text);
        for (LZ77Triples &triple: triples) {
            cout << triple << endl;
        }
    } else if (command == "decompress") {
        vector<LZ77Triples> triples;
        int shift;
        int size;
        char next_character;
        while (cin >> shift >> size) {
            if (cin >> next_character) {
                triples.push_back({shift, size, next_character});
            } else {
                triples.push_back({shift, size, ' '});
            }
        }
        cout << decoder(triples) << endl;
    }
}
