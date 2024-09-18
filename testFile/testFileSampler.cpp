#include <iostream>
//#include <fstream>
#include <algorithm>
#include <random>
#include <cstring>
#include "../classes/TestFile.hpp"

/**
 *
 * @param argc
 * @param argv 1. testFile 2. testFileSample 3. sampleSize
 * @return
 */
int main(int argc, char* argv[]) {
	TestFile population, sample;
	population.open(argv[1]);
    const std::size_t sampleSize=std::stoi(argv[3]);
    sample.initiate(sampleSize, population.getHashBytes());
	bool used[population.getPopulationSize()];
    std::fill(used,used+population.getPopulationSize()-1, false);
    std::mt19937 gen((std::random_device())()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> populationDistribution(0, population.getPopulationSize()-1);
    for (std::size_t i=0; i<sampleSize; ++i){
        std::size_t hashPosition;
        do{
            hashPosition=populationDistribution(gen);
        }while (used[hashPosition]);    //sample without replacement
        std::memcpy(sample.getHash(i), population.getHash(hashPosition), population.getHashBytes());
        used[hashPosition]= true;
    }
    sample.calculateStats();
    sample.write(argv[2]);

}