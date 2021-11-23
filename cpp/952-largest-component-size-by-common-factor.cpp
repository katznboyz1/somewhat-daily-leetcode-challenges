/*
    https://leetcode.com/problems/largest-component-size-by-common-factor/ (Hard)

    You are given an integer array of unique positive integers nums. Consider the following graph:
    There are nums.length nodes, labeled nums[0] to nums[nums.length - 1],
    There is an undirected edge between nums[i] and nums[j] if nums[i] and nums[j] share a common factor greater than 1.
    Return the size of the largest connected component in the graph.
*/

#include <vector>
#include <random>
#include <iostream>
#include <string>

using namespace std;

vector<int> generateNums(int nums_size) {
    
    std::random_device rand;
    std::mt19937 gen(rand());
    std::uniform_int_distribution<> distr(0, nums_size);

    vector<int> nums;

    for (int i = 0; i < nums_size; i++) {

        nums.push_back(distr(rand));
    }

    return nums;
}

int greatestCommonFactor(int num1, int num2) {

    int max;
    int min;

    if (num1 > num2) {max = num1; min = num2;} else {max = num2; min = num1;}

    int maxgcf;

    for (int i = 1; i < max; i++) {

        if ((maxgcf > min)) {

            break;

        } else if ((max % i == 0) && (min % i == 0)) {

            maxgcf = i;
        }
    }

    return maxgcf;
}

void printAllRelationships(vector<int> numsPointers[], const int NUMS_SIZE) {

    for (int i = 0; i < NUMS_SIZE; i++) {

        std::cout << "Index " << std::to_string(i) << " has " << std::to_string(numsPointers[i].size()) << " relationships: ";

        for (int j = 0; j < numsPointers[i].size(); j++) {

            std::cout << std::to_string(numsPointers[i][j]) << ", ";
        }

        std::cout << endl;
    }
}

int main() {

    const int NUMS_SIZE = 20; //2 * pow(10, 4);
    const vector<int> NUMS_ORIGINAL = generateNums(NUMS_SIZE);

    vector<int>* numsPointers = new vector<int>[NUMS_SIZE];
    int* numsPointersConnections = new int[NUMS_SIZE];

    // create the node connections
    for (int i = 0; i < NUMS_SIZE; i++) {

        for (int j = 0; j < NUMS_SIZE; j++) {

            if (greatestCommonFactor(i, j) > 1) {

                numsPointers[i].push_back(j);
                numsPointers[j].push_back(i);
            }
        }
    }

    int maxPointerConnections = 0;

    // find the size of the node connections
    for (int i = 0; i < NUMS_SIZE; i++) {

        numsPointersConnections[i] = 0;

        for (int j = 0; j < NUMS_SIZE; j++) {

            for (int k = 0; k < numsPointers[j].size(); k++) {

                if (numsPointers[j][k] == i) {

                    numsPointersConnections[i]++;

                    if (numsPointersConnections[i] > maxPointerConnections) maxPointerConnections = numsPointersConnections[i];
                }
            }
        }
    }

    printAllRelationships(numsPointers, NUMS_SIZE);

    std::cout << std::to_string(maxPointerConnections) << endl;

    return 0;
}