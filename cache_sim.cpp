#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <cmath>

struct CacheEntry {
    bool valid;
    unsigned int tag;
    CacheEntry() : valid(false), tag(0) {}
};

class CacheSimulator {
private:
    std::vector<CacheEntry> cache;
    unsigned int memSize;
    unsigned int cacheSize;
    unsigned int hits, misses;

    bool isPowerOfTwo(unsigned int n) {
        return n != 0 && (n & (n - 1)) == 0;
    }

public:
    CacheSimulator(unsigned int memSize, unsigned int cacheSize) 
        : memSize(memSize), cacheSize(cacheSize), hits(0), misses(0) {
        if (!isPowerOfTwo(memSize) || !isPowerOfTwo(cacheSize)) {
            throw std::invalid_argument("Memory and cache sizes must be powers of 2");
        }
        cache.resize(cacheSize);
    }

    void processMemoryAccess(unsigned int address) {
        unsigned int index = address % cacheSize;
        unsigned int tag = address / cacheSize;

        if (cache[index].valid && cache[index].tag == tag) {
            hits++;
        } else {
            misses++;
            cache[index].valid = true;
            cache[index].tag = tag;
        }
    }

    void simulate(const std::string& accessFilename) {
        std::ifstream file(accessFilename);
        unsigned int address;

        while (file >> address) {
            if (address >= memSize) {
                throw std::out_of_range("Address exceeds memory size");
            }
            processMemoryAccess(address);
        }

        file.close();
    }

    void reportResults(const std::string& outputFilename) {
        std::ofstream outFile(outputFilename);
        for (const auto& entry : cache) {
            outFile << entry.tag << " " << (entry.valid ? "Hit" : "Miss") << std::endl;
        }
        outFile << "Out of " << hits + misses << " memory accesses, there was a "
                << static_cast<float>(hits) / (hits + misses) * 100 << "% cache hit rate and a "
                << static_cast<float>(misses) / (hits + misses) * 100 << "% miss rate." << std::endl;

        outFile.close();
    }
};

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: ./cache_sim mem_size cache_size access_filename" << std::endl;
        return 1;
    }

    unsigned int memSize = std::stoi(argv[1]);
    unsigned int cacheSize = std::stoi(argv[2]);
    std::string accessFilename = argv[3];

    try {
        CacheSimulator simulator(memSize, cacheSize);
        simulator.simulate(accessFilename);
        simulator.reportResults("hitmiss-out.txt");
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}