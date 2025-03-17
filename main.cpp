#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <mutex>
#include <thread>

const int NUM_THREADS = 4;

std::unordered_set<int> globalUniqueNumbers;
std::mutex mtx;

void processFileSection(const std::string &filename, std::streampos start, std::streampos end) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "Error opening file: " << filename << std::endl;
        return;
    }

    if (start != 0) {
        char prev_char;
        file.seekg(start - static_cast<std::streamoff>(1), std::ios::beg);
        file.get(prev_char);

        if (isdigit(prev_char)) {
            char ch;
            while (file.get(ch) && isdigit(ch));
        }
    }

    file.seekg(start);
    std::unordered_set<int> localUniqueNumbers;
    int num;

    while (file.tellg() < end && file >> num) {
        localUniqueNumbers.insert(num);
    }

    std::lock_guard<std::mutex> lock(mtx);
    globalUniqueNumbers.insert(localUniqueNumbers.begin(), localUniqueNumbers.end());
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    std::string filename = argv[1];

    std::ifstream file(filename, std::ios::ate);
    if (!file) {
        std::cout << "Error opening file: " << filename << std::endl;
        return 1;
    }

    std::streampos fileSize = file.tellg();
    file.close();
    
    std::vector<std::thread> threads;
    std::streampos chunkSize = fileSize / NUM_THREADS;

    for (int i = 0; i < NUM_THREADS; ++i) {
        std::streampos start = i * chunkSize;
        std::streampos end = (i == NUM_THREADS - 1) ? fileSize : start + chunkSize;
        threads.emplace_back(processFileSection, filename, start, end);
    }

    for (auto &t : threads) {
        t.join();
    }

    std::cout << "Unique Numbers:\n";
    for (int num : globalUniqueNumbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
