#pragma once
#include <string>
#include <fstream>
#include <functional>
#include <cstring>

class TestFile {
private:
    std::size_t populationSize, uniquePopulationSize, hashBytes, total0, biggestLeftRight0;
	inline void reallocateHashes();
    unsigned char* hashes= nullptr;

    const std::function<std::size_t(const unsigned char*)> hashHash=[&](const unsigned char* hash) -> std::size_t {
        std::size_t result = 0;
        for (std::size_t i = 0; i < hashBytes; ++i) {
            result = result * 31 + hash[i];
        }
        return result;
    };
    const std::function<bool(const unsigned char*, const unsigned char*)> hashEqual=[&](const unsigned char* lhs, const unsigned char* rhs) -> bool {
        return std::memcmp(lhs, rhs, hashBytes) == 0;
    };
public:
    std::size_t operator()(const unsigned char* hash) const;
    bool operator()(const unsigned char* lhs, const unsigned char* rhs) const;
//    std::size_t hashHash(const unsigned char* hash) const;
//    bool hashEquality(const unsigned char* lhs, const unsigned char* rhs) const;
//    TestFile();
    ~TestFile();
	/**
	 * open testFile
	 * @param filename
	 */
	void open(const std::string& filename);
	/**
	 * initiate instance
	 * @param population number of hashes
	 * @param bytes how big each hash is
	 */
	void initiate(const std::size_t& population, const std::size_t& bytes);
	/**
	 * initiate and populate TestFile instance with random bytes
	 * @param population  number of hashes
	 * @param bytes how big each hash is
	 * @param duplicatesEvery how often to duplicate a hash. One in every duplicatesEvery hashes
	 */
	void populateRandomly(const std::size_t& population, const std::size_t& bytes, const std::size_t& duplicatesEvery=0);
	/**
	 * write out testFile instance to file
	 * @param filename
	 */
	void write(const std::string& filename) const;
	/**
	 * for size use getHashBytes()
	 * @warning no error checking done
	 * @param index
	 * @return pointer to hash
	 */
	inline unsigned char* getHash(const std::size_t& index);
	/**
	 *
	 * @return number of hashes
	 */
    std::size_t getPopulationSize() const;
	/**
	 *
	 * @return size of hash in bytes
	 */
    std::size_t getHashBytes() const;

    void calculateStats();
};
