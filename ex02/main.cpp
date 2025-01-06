#include <iostream>
#include <vector>
#include <deque>
#include <cstdlib>
#include <ctime>
#include <climits> // For INT_MAX
#include <list>
#include "PmergeMe.hpp"
#define DEBUG_LINE() std::cerr << "Reached line " << __LINE__ << std::endl;

unsigned long jacobsthal(unsigned long i) {
    static std::vector<unsigned long> buf; 
    for (std::size_t k; (k = buf.size()) <= i;) {
        if (k == 0) {
            buf.push_back(0); 
        } else if (k == 1) {
            buf.push_back(1); 
        } else {
            unsigned long tmp;
            if (__builtin_mul_overflow(2, buf[k - 2], &tmp) || 
                __builtin_add_overflow(tmp, buf[k - 1], &tmp)) {
                throw std::overflow_error("jacobsthal");
            }
            buf.push_back(tmp);
        }
    }
    return buf[i];
}
//J(n) = 2 * J(n-2) + J(n-1)
void printData(const std::vector<Node> &data) {
    for (size_t i = 0; i < data.size(); ++i) {
        std::cout << data[i].getTypical();
        if (i != data.size() - 1)
            std::cout << " ";
    }
    std::cout << std::endl;
}

void sort(std::vector<Node> &data)
{
    if (data.size() == 1)
        return;
    printData(data);
    //でばぐ
     std::vector<Node> large, small;
    large.reserve(data.size() / 2);
    small.reserve(data.size() / 2 + data.size() % 2);
    for (std::vector<Node>::iterator it = data.begin(); it != data.end(); ++it)
    {
        DEBUG_LINE();
        std::vector<Node>::iterator pre = it;
        pre++;
        if (pre == data.end())
        {
            small.push_back(Node(&(*pre)));
            break;
        }
        if (*pre < *it)
        {
            small.push_back(Node(&(*pre)));
            large.push_back(Node(&(*it)));
        }
        else
        {
            small.push_back(Node(&(*it)));
            large.push_back(Node(&(*pre)));
        }
    }
    DEBUG_LINE();
    sort(large);
}

void mergeInsertSortVector(std::vector<int> &data) {
    std::vector<Node> large, small;
    large.reserve(data.size() / 2);
    small.reserve(data.size() / 2 + data.size() % 2);
    for (std::vector<int>::iterator it = data.begin(); it != data.end(); ++it)
    {
       DEBUG_LINE();
        std::vector<int>::iterator pre = it;
        pre++;
        if (pre == data.end())
        {
            small.push_back(Node(&(*pre)));
            break;
        }
        if (*pre < *it)
        {
            small.push_back(Node(&(*pre)));
            large.push_back(Node(&(*it)));
        }
        else
        {
            small.push_back(Node(&(*it)));
            large.push_back(Node(&(*pre)));
        }
    }
    sort(large);
}


int main(int argc, char** argv) {
    std::vector<int> vec;
    // std::list<int> list;

    if(argc <= 1)
        return 0;
    for (int i = 1; i < argc; ++i)
    {
        char* end;
        long num = std::strtol(argv[i], &end, 10);

        if (*end != '\0' || num <= 0 || num > INT_MAX)
        {
            std::cerr << "Error: Invalid integer value (non-positive or overflow): " << argv[i] << "\n";
            return 1;
        }

        vec.push_back(static_cast<int>(num));
        // list.push_back(static_cast<int>(num));
    }

    std::cout << "Before: ";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        std::cout << vec[i] << " ";
    }
    std::cout << "\n";

    clock_t startVec = clock();
    
    mergeInsertSortVector(vec);
    clock_t endVec = clock();
    double timeVec = static_cast<double>(endVec - startVec) / CLOCKS_PER_SEC * 1000000; // Microseconds
    //CLOCKS_PER_SECは1秒間に進むプロセッサのクロック数
    // clock_t startDeq = clock();
    // mergeInsertmergeInsertSortVectorDeque(list);
    // clock_t endDeq = clock();
    // double timeDeq = static_cast<double>(endDeq - startDeq) / CLOCKS_PER_SEC * 1000000; // Microseconds

    std::cout << "After: ";
    for (size_t i = 0; i < vec.size(); ++i) 
    {
        std::cout << vec[i] << " ";
    }
    std::cout << "\n";

    std::cout << "Time to process a range of " << vec.size() << " elements with std::vector: " << timeVec << " us\n";
    // std::cout << "Time to process a range of " << deq.size() << " elements with std::deque: " << timeDeq << " us\n";

    return 0;
}
