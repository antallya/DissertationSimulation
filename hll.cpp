#include <iostream>
#include "count/hll.h"
#include "count/hll_limits.h"

using libcount::HLL;

#include "classes/TestFile.hpp"
/**
 *
 * @param argc
 * @param argv 1. input filename 2. output filename
 * @return
 */
int main(int argc, char* argv[]) {
    TestFile testFile;
    testFile.open(argv[1]);
    std::ofstream resultCSV(argv[2],std::ios::app);
//    std::size_t maxPrecision = std::stoi(argv[3]);
    unsigned char* const beginHash= testFile.getHash(0);
    unsigned char* const endHash = testFile.getHash(testFile.getPopulationSize());
    const size_t hashBytes= testFile.getHashBytes();
    for(std::size_t currentPrecision = libcount::HLL_MIN_PRECISION; currentPrecision <= libcount::HLL_MAX_PRECISION; currentPrecision++){
        HLL* hll = HLL::Create(currentPrecision);
        for (unsigned char * currentHash = beginHash; currentHash < endHash; currentHash += hashBytes) {
            /*uint64_t number;
            std::memcpy(&number, currentHash, hashBytes);
            hll->Update(number);*/
            hll->Update(*reinterpret_cast<const uint64_t* const>(currentHash)); //no need to copy the hash
        }
        resultCSV<<hll->Estimate()<<',';
        delete hll;
    }
    resultCSV<<std::endl;
    resultCSV.close();
}