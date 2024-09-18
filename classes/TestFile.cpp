#include "TestFile.hpp"
#include "../utilities/random.hpp"
#include <ranges>
#include <limits>
#include <unordered_set>
//#include <cstring>

void TestFile::open(const std::string& filename) {
    std::ifstream testFile(filename);
    if (!testFile.is_open()) {
        throw std::runtime_error("File not found");
    }
    std::string tempString;
    std::getline(testFile, tempString);
    populationSize = std::stoi(tempString);
    std::getline(testFile, tempString);
    hashBytes = std::stoi(tempString);
    reallocateHashes();
    for (std::size_t i = 0; i < populationSize; ++i) {
        testFile.read(reinterpret_cast<char *>(getHash(i)), hashBytes);
    }
	testFile.getline(nullptr, std::numeric_limits<std::size_t >::max());
	std::getline(testFile, tempString);
    biggestLeftRight0=std::stoi(tempString);
	std::getline(testFile, tempString);
	total0=std::stoi(tempString);
    std::getline(testFile,tempString);
    uniquePopulationSize=std::stoi(tempString);
    testFile.close();
}

void TestFile::initiate(const std::size_t &population, const std::size_t &bytes) {
	populationSize=population;
	hashBytes=bytes;
	reallocateHashes();
	uniquePopulationSize=0;total0=0;biggestLeftRight0=0;
}

//std::size_t TestFile::operator()(const unsigned char* hash) const{
//    std::size_t result = 0;
//    for (std::size_t i = 0; i < hashBytes; ++i) {
//        result = result * 31 + hash[i];
//    }
//    return result;
//}
//bool TestFile::operator()(const unsigned char* lhs, const unsigned char* rhs) const{
//    return std::memcmp(lhs, rhs, hashBytes) == 0;
//}


void TestFile::populateRandomly(const std::size_t& population, const std::size_t& bytes, const std::size_t& duplicatesEvery) {
	initiate(population, bytes);
    std::unordered_set<unsigned char*, decltype(hashHash), decltype(hashEqual)> hashSet(populationSize, hashHash, hashEqual);
	for(std::size_t i=0; i < populationSize; ++i) {
		unsigned char* currentHash= getHash(i);
        if(duplicatesEvery!=0&&!hashSet.empty()&&i%duplicatesEvery==0){
            auto randomDuplicateHash = hashSet.begin();
            const std::size_t randomIndexTo = utilities::random::randomToSize(hashSet.size()-1);
            for(std::size_t randomIndex=0; randomIndex<randomIndexTo;++randomIndex)
                ++randomDuplicateHash;
            std::memcpy(currentHash, *randomDuplicateHash, hashBytes);
        }else{
		    utilities::random::randomBytesToMemory(currentHash, hashBytes);
            hashSet.insert(currentHash);
//            if (hashSet.insert(currentHash).second)
//                ++uniquePopulationSize;
        }

        bool keepLookingFor0 = true;
		std::size_t currentLeftRight0 = 0;
		for (unsigned char* currentByte=currentHash;currentByte<currentHash+hashBytes; ++currentByte) {//iterate generated hash bytes
			total0 += 8-std::popcount(*currentByte);
			if(keepLookingFor0){
				const int zeros= std::countl_zero(*currentByte);
				if(zeros != 8)
					keepLookingFor0 = false;
                currentLeftRight0 += zeros;
			}
		}
		if(currentLeftRight0 > biggestLeftRight0)
            biggestLeftRight0 = currentLeftRight0;
	}
    uniquePopulationSize=hashSet.size();
}

void TestFile::calculateStats() {
    total0=0;biggestLeftRight0=0;
//    std::unordered_set<unsigned char*, TestFile, TestFile> hashSet(populationSize);
    std::unordered_set<unsigned char*, decltype(hashHash), decltype(hashEqual)> hashSet(populationSize, hashHash, hashEqual);

    for (unsigned char* currentHash = hashes; currentHash < hashes + (populationSize * hashBytes); currentHash+= hashBytes) {
        bool keepLookingFor0 = true;
        std::size_t currentLeftRight0 = 0;
        hashSet.insert(currentHash);
//        if (hashSet.insert(currentHash).second)
//            ++uniquePopulationSize;
        for (unsigned char* currentByte=currentHash;currentByte<currentHash+hashBytes; ++currentByte) {//iterate generated hash bytes
            total0 += 8-std::popcount(*currentByte);
            if (keepLookingFor0) {
                const int zeros = std::countl_zero(*currentByte);
                if (zeros != 8)
                    keepLookingFor0 = false;
                currentLeftRight0 += zeros;
            }
        }
        if (currentLeftRight0 > biggestLeftRight0)
            biggestLeftRight0 = currentLeftRight0;
    }
    uniquePopulationSize=hashSet.size();
}

void TestFile::write(const std::string &filename) const{
	std::ofstream testFile(filename, std::ios::binary);
	testFile<<populationSize<<'\n'<<hashBytes<<'\n';
	for(unsigned char * currentHash= hashes; currentHash < hashes+(populationSize*hashBytes); currentHash+=hashBytes) {
		testFile.write(reinterpret_cast<const char *>(currentHash), hashBytes);
	}
	testFile << '\n' << biggestLeftRight0 << '\n' << total0<<'\n'<<uniquePopulationSize;
	testFile.close();
}

TestFile::~TestFile() {
    delete[] hashes;
}
std::size_t TestFile::getPopulationSize() const {return populationSize;}

std::size_t TestFile::getHashBytes() const {return hashBytes;}

void TestFile::reallocateHashes() {
	if (hashes)
		delete[] hashes;
	hashes= new unsigned char[hashBytes*populationSize];
}

unsigned char *TestFile::getHash(const std::size_t &index) {return hashes + index * hashBytes;}
