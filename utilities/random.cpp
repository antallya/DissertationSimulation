#include "random.hpp"
#include <random>

//extern std::size_t bitstringBytes;
std::mt19937 gen((std::random_device())()); //Standard mersenne_twister_engine seeded with rd()
std::uniform_int_distribution<> byteDistribution(0, 255);    //one byte unsigned
//std::vector<std::byte> utilities::random::randomBytes(){
//	std::vector<std::byte> bytes(bitstringBytes);
//	for(std::size_t i = 0; i < bitstringBytes; ++i){
//		bytes[i] = static_cast<std::byte>(byteDistribution(gen));
//	}
//	return bytes;
//}

void utilities::random::randomBytesToMemory(unsigned char* const location, const std::size_t& bytes) {
	for(unsigned char* currentByte=location; currentByte < location + bytes; ++currentByte){
		*currentByte=byteDistribution(gen);
	}
}

std::size_t utilities::random::randomToSize(const size_t &max) {
    std::uniform_int_distribution<> toSizeDistribution(0, max);
    return toSizeDistribution(gen);
}
