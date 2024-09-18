#include <iostream>
#include <fstream>
#include <limits>
#include <algorithm>
#include <array>
#include <bit>
//#include <bitset>

#include "classes/TestFile.hpp"

inline bool getBit(const unsigned char byte, const unsigned char bit) {
    return (byte >> bit) & 1;
}
/**
 *
 * @param argc
 * @param argv 1. input testFile file 2. output csv file
 * @return
 */
int main(int argc, char* argv[]) {
	/*std::ifstream testFile(argv[1], std::ios::binary);
	if (!testFile.is_open()) {
		std::cerr << "File not found" << std::endl;
		return 1;
	}
	std::size_t hashes, hashBytes;
//	testFile >> hashes;
//	testFile >> hashBytes;
	std::string tempString;
	std::getline(testFile, tempString);
	hashes = std::stoi(tempString);
	std::getline(testFile, tempString);
	hashBytes = std::stoi(tempString);
	unsigned char hash[hashBytes];
	unsigned long long result[hashBytes];
	std::fill(result, result + hashBytes, 0);
	unsigned long long currentResult;
	for (std::size_t i = 0; i < hashes; ++i) {
		testFile.read(reinterpret_cast<char *>(hash), hashBytes);
		currentResult = 0;
		for (int j = hashBytes-1; j >=0 ; --j) {
			currentResult+= 8-std::popcount(hash[j]);
			result[j] += currentResult;
		}
	}
	testFile.getline(nullptr, std::numeric_limits<std::size_t >::max());
	std::getline(testFile, tempString);
	std::cout << std::endl << tempString << std::endl;
	std::getline(testFile, tempString);
	std::cout << tempString<<std::endl;
	for (std::size_t i = 0; i < hashBytes; ++i) {
		std::cout << '\t' << result[i];
	}
	testFile.close();*/
    TestFile testFile;
    testFile.open(argv[1]);
    std::ofstream resultCSV(argv[2],std::ios::app);
    const std::size_t population= testFile.getPopulationSize(), hashBytes=testFile.getHashBytes();
    const unsigned char * const hashEnd=testFile.getHash(population);
    unsigned long long total0s=0;
    for(std::size_t byte=0; byte<hashBytes; ++byte){
        for (char bit=7; bit>=0; --bit){
            for (unsigned char* hash=testFile.getHash(0); hash < hashEnd; hash+=hashBytes){
                total0s+=!getBit(hash[byte], bit);
            }
            resultCSV << static_cast<double>(total0s)/(population*(byte*8+(8-bit))) << ',';
        }
    }
    resultCSV<<std::endl;
    resultCSV.close();
	return 0;
}
