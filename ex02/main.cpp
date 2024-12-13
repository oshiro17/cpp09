#include <iostream>
#include <vector>
#include <deque>
#include <cstdlib>
#include <ctime>
#include <climits> // For INT_MAX
#include <list>
#include "PmergeMe.hpp"

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



void mergeInsertSortVector(std::vector<int> &data) {
    if (data.size() < 2)
        return;

    // Node ベースのデータ構造を作成
    std::vector<Node> large, small;
    large.reserve(data.size() / 2);
    small.reserve(data.size() / 2 + data.size() % 2);

    for (std::vector<int>::iterator it = data.begin(); it != data.end();) {
        std::vector<int>::iterator pre = it++;
        if (it == data.end()) {
            small.emplace_back(&*pre);
            break;
        }
        bool isLess = *pre < *it;
        large.emplace_back(isLess ? &*it : &*pre);
        small.emplace_back(isLess ? &*pre : &*it);
        large.back().push(&small.back());
    }
    mergeInsertSortVector(data); 

    std::vector<Node> tmp;
    tmp.reserve(data.size());

    bool finished = false;
    std::vector<Node>::iterator it = large.begin();

    tmp.push_back(*it->pop());
    tmp.push_back(*it++);
    for (std::size_t n = 1; !finished; ++n) {
        for (std::size_t j = 2 * jacobsthal(n); j > 0; --j) {
            if (it == large.end()) {
                if (data.size() % 2) {
                    Node &node = small.back();
                    tmp.insert(std::lower_bound(tmp.begin(), tmp.end(), node), node);
                }
                finished = true;
                break;
            }
            tmp.push_back(*it++);
        }

        for (std::vector<Node>::reverse_iterator jt = tmp.rbegin(); jt != tmp.rend();) {
            if (jt->hasPair()) {
                Node &node = *jt->pop();
                tmp.insert(std::lower_bound(tmp.begin(), --jt.base(), node), node);
            } else {
                ++jt;
            }
        }
    }

    std::vector<int> res;
    res.reserve(data.size());
    for (std::vector<Node>::iterator it = tmp.begin(); it != tmp.end(); ++it) {
        int *value = nullptr; 
        it->getValue(value);

        if (value) { 
            res.push_back(*value);
        } else {
            std::cerr << "Error: Null pointer encountered in Node.getValue()\n";
        }
    }

    data.swap(res);
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
