#include <iostream>
#include <fstream>
#include <cstddef>
#include <bit>
#include <ranges>

#include <cstring>
//#include <atomic>

//#include "../utilities/random.hpp"
#include "../classes/TestFile.hpp"

std::size_t bitstringBytes;

/**
 *
 * @param argc
 * @param argv 1. filename 2. bitstring number 3. bitstring size 4. duplicate every nth hash
 * @return
 */
int main(int argc, char* argv[]) {
	const std::size_t bitstring_number = std::stoi(argv[2]);
	bitstringBytes = std::stoi(argv[3]);
    TestFile testFile;
    testFile.populateRandomly(bitstring_number, bitstringBytes,std::stoi(argv[4]));
    testFile.write(argv[1]);
//	std::size_t total0 = 0, biggestLeftRight0 = 0;
//	std::cout << argv[1]<< '\t' <<bitstring_number<< '\t'<<bitstringBytes << std::endl;
//	std::ofstream testFile(argv[1], std::ios::binary);
//	testFile<<bitstring_number<<'\n'<<bitstringBytes<<'\n';
//	for(std::size_t i = 0; i < bitstring_number; ++i) {
//		std::vector<std::byte> bytes = utilities::random::randomBytes();
//		testFile.write(reinterpret_cast<const char *>(bytes.data()), bytes.size());
//		bool keepLookingFor0 = true;
//		std::size_t currentRightLeft0 = 0;
//		for (const std::byte &byte : bytes| std::views::reverse) {
//			total0 += std::popcount((unsigned char)byte);
//			if(keepLookingFor0){
//				const int zeros= std::countr_zero((unsigned char)byte);
//				if(zeros != 8)
//					keepLookingFor0 = false;
//				currentRightLeft0 += zeros;
//			}
//		}
//		if(currentRightLeft0 > biggestLeftRight0)
//			biggestLeftRight0 = currentRightLeft0;
//	}
//	testFile<<'\n'<<biggestLeftRight0<<'\n'<<total0;
//	testFile.close();
	return 0;
}
