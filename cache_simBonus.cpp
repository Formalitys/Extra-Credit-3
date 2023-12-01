#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <cmath>

class Cache {
public:
    Cache(int totalSize, int blockSize) : blockSize(blockSize) {
        numBlocks = totalSize / blockSize;
        for (int i = 0; i < numBlocks; ++i) {
            validBits.push_back(false);
            tags.push_back(-1); // -1 indicates an invalid tag.
        }
    }

    // Access the cache with a given address
    bool access(int address, int& missType) {
        int blockAddress = address / blockSize;
        int tag = blockAddress / numBlocks;
        int index = blockAddress % numBlocks;

        if (!validBits[index] || tags[index] != tag) {
            // Miss
            validBits[index] = true;
            tags[index] = tag;

            if (allAddresses.find(blockAddress) != allAddresses.end()) {
                // Capacity or conflict miss
                missType = (validBits[index] ? 2 : 3); // 2 for capacity, 3 for conflict
            } else {
                // Compulsory miss
                missType = 1;
            }
            allAddresses.insert(blockAddress);
            return false;
        }
        return true;
    }

private:
    int numBlocks;
    int blockSize;
    std::vector<bool> validBits;
    std::vector<int> tags;
    std::unordered_set<int> allAddresses; // Tracks all addresses for compulsory miss detection
};

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: ./cache_sim mem_size cache_size_L1 cache_size_L2\n";
        return 1;
    }

    int memSize = std::atoi(argv[1]);
    int cacheSizeL1 = std::atoi(argv[2]);
    int cacheSizeL2 = std::atoi(argv[3]);
    std::string accessFilename = "accesslist.txt"; // Fixed filename as per your requirement

    std::ifstream accessFile(accessFilename);
    if (!accessFile) {
        std::cerr << "Error opening access file.\n";
        return 1;
    }

    int blockSize = 4; // Assume a block size of 4 words (configurable)
    Cache L1(cacheSizeL1, blockSize);
    Cache L2(cacheSizeL2, blockSize);

    std::vector<int> accesses;
    int address;
    while (accessFile >> address) {
        accesses.push_back(address);
    }

    std::ofstream outFile("hitmiss-out.txt");
    int hits = 0, compulsoryMisses = 0, capacityMisses = 0, conflictMisses = 0;
    for (int addr : accesses) {
        int missType = 0;
        bool hitL1 = L1.access(addr, missType);

        if (!hitL1) {
            bool hitL2 = L2.access(addr, missType);
            outFile << addr << " " << (hitL2 ? "Hit" : "Miss") << std::endl;
            if (hitL2) hits++;

            switch (missType) {
                case 1: compulsoryMisses++; break;
                case 2: capacityMisses++; break;
                case 3: conflictMisses++; break;
            }
        } else {
            hits++;
            outFile << addr << " " << "Hit" << std::endl;
        }
    }

    int totalAccesses = accesses.size();
    std::cout << "Total Accesses: " << totalAccesses << "\n";
    std::cout << "Hits: " << hits << "\n";
    std::cout << "Misses: " << (totalAccesses - hits) << "\n";
    std::cout << "Compulsory Misses: " << compulsoryMisses << "\n";
    std::cout << "Capacity Misses: " << capacityMisses << "\n";
    std::cout << "Conflict Misses: " << conflictMisses << "\n";

    accessFile.close();
    outFile.close();
    return 0;
}
