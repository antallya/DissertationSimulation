#pragma once
#include <cstddef>
#include <vector>
#include <bitset>
namespace utilities::random{
//	std::vector<std::byte> randomBytes();
	void randomBytesToMemory(unsigned char* const location,const std::size_t& bytes);
    std::size_t randomToSize(const std::size_t& max);
}