#include <iostream>
#include <fstream>
#include <unordered_set>
#include "Time.h"
using namespace std;
class Hash {
private:
    static int M;
    static int K;
public:
    size_t operator()  (const string str) const {
        unsigned long long sum = 0;
        unsigned long long multiplaying = 1;


        for (char symbol: str) {
            sum += symbol * multiplaying;
            multiplaying *= static_cast<unsigned long long>(K);
        }


        return sum % M;

    }
};
int Hash::M = 97;
int Hash::K = 128;




int main() {
    const string path_to_write_1 = "Result.txt";
    const string path_elems = "IconicElements.txt";
    int k = 128;
    int m = 97;

    unordered_set<string, Hash> hash;
    ifstream read_file("dostoevsky.txt");
    Time timer(path_to_write_1);;
    string buffer;
    timer.start();
    read_file >> buffer;
    while (!read_file.eof()) {
        hash.insert(buffer);
        read_file >> buffer;
    }
    read_file.close();
    timer.end();
    timer.log("unordered_set", "read", "K, M", 0);
    timer.reset();

    timer.start();
    hash.find("место");
    timer.end();
    timer.log("unordered_set", "read", "K, M", 0);
    timer.reset();

    ofstream write(path_elems);
    write << "hash; elems" << endl;
    for (int  i = 0; i < m; i++) {
        write << i << ";" << hash.bucket_size(i) << endl;
    }
    write.close();
    return 0;

}