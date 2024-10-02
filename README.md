# Heuristic Tuning of the Bucket Parameter in HyperLogLog (HLL) Algorithm

## Overview
This repository contains the code, data, and analysis for my dissertation on tuning the bucket parameter in the HyperLogLog (HLL) algorithm. The objective of this research is to propose a heuristic for optimizing the number of buckets used for cardinality estimation in the HLL algorithm, thereby improving its accuracy and memory efficiency. Additionally, this project introduces a novel structure for the HLL algorithm to facilitate tuning.

## Motivation
The exponential growth of big data has necessitated approximate algorithms like HLL, which efficiently estimate the cardinality of large data streams. However, the accuracy and memory efficiency of the HLL algorithm is highly dependent on the bucket parameter $k$ (which determines the number of buckets m=2km=2k). This repository presents a heuristic for tuning kk based on analyzing the distribution of zeros in hash values.

## Methodology

### Data Collection:
- Simulated a large dataset of 10,000 hash values with 5,001 unique entries to represent a typical stream of data. From this set, multiple smaller samples were extracted (sizes: 5, 10, 100, 500, 750, and 1,000) to evaluate the behavior of the algorithm across varying conditions.

### Heuristic Definition:
The heuristic is based on comparing the empirical proportion of zeros at different bit positions of the hash values with the expected binomial distribution Binomial(n,1/2). The optimal number of buckets is determined by identifying the point where the empirical proportion aligns with the theoretical binomial proportion, indicating that the hash values are uniformly distributed across the buckets.

### Algorithmic Changes:
- Modified the original HLL structure to assign both the bucket index and leading zero counts using the first kk bits of the hash, improving consistency and ensuring the bucket allocation aligns with the zero distribution.
- The HLL is tested across a range of kk-values, and its performance is evaluated based on how well the resulting estimates align with the actual cardinality of the sample set.

### Evaluation:
- Generated visualizations showing the relationship between the empirical proportion of zeros and the theoretical binomial distribution.
- Compared the HLL estimates for different values of kk to actual unique counts, identifying the point where the HLL achieves its lowest estimation error.

### Conclusion:
- The proposed heuristic identifies the optimal number of buckets by ensuring uniform distribution of hash values, improving both accuracy and memory efficiency.


### Building this project
1. install libraries
2. build
```bash
mkdir build
cd buld
cmake ..
make
```
# Libraries Used
[libcount](https://github.com/dialtr/libcount)
