#include <iostream>
#include <vector>
#include <deque>
#include <cstdlib>
#include <ctime>
#include <climits> // For INT_MAX
#include <vector>
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
// void printData(const std::vector<Node> &data) {
//     for (size_t i = 0; i < data.size(); ++i) {
//         std::cout << data[i].getTypical();
//         if (i != data.size() - 1)
//             std::cout << " ";
//     }
//     std::cout << std::endl;
// }

void sort(std::vector<int> &data)
{
    if(data.size() <= 1)
        return;
    std::vector<int> large;
    int smallArr[(data.size() / 2) + (data.size() % 2)];
    std::vector<Node*> nodes;
    int i = 0;
for (std::vector<int>::iterator it = data.begin(); it != data.end(); )
{
    std::vector<int>::iterator pre = it + 1;
    if (pre == data.end()) {
        // 奇数個の最後の1つが余った場合、smallに入れる
        smallArr[i] = *it;
        i++;
        break; // ループ終了
    }

    // ここで 2つ1組の比較
    if (*pre < *it)
    {
        // small = *pre, large = *it
        smallArr[i] = *pre;
        large.push_back(*it);

        // Nodeを作り、pop先として smallArr[i] のアドレスを設定
        Node* newNode = new Node(*it);
        newNode->pop = &smallArr[i];

        nodes.push_back(newNode);
    }
    else
    {
        // small = *it, large = *pre
        smallArr[i] = *it;
        large.push_back(*pre);

        Node* newNode = new Node(*pre);
        newNode->pop = &smallArr[i];

        nodes.push_back(newNode);
    }

    i++;
    it += 2; // ペアを1つ消費
}

    // sort(large);
    std::vector<int> tmp;
    tmp.reserve(data.size());
    std::vector<int>::iterator it_large = large.begin();
    bool flag = true;
    for (std::size_t n = 1; flag; n++)
    {
        std::size_t j = 2 * jacobsthal(n);
        std::size_t i = 0;

        while(i < j)
        {
            if (it_large == large.end())
                break;
            tmp.push_back(*it_large);
            std::cout<<"__"<<*it_large<<std::endl;
            i++;
            it_large++;
        }
        if (i != j)
            j = i;
        if (i == 0 && data.size() % 2 != 0)
        {
            DEBUG_LINE();
            tmp.push_back(smallArr[data.size() / 2]);
        }
        if(i == 0)
            break;
        i = 0;
        while(i < j && flag)
        {
            it_large--; 
            Node* targetNode = nullptr;
            for (Node* node : nodes)
            {
                if (node->n == *it_large) 
                {
                    targetNode = node;
                    break;
                }
            }
            if (targetNode == nullptr)
            {
                flag = false;
                break;
            }
            tmp.push_back(*(targetNode->pop));
                // std::cout<<"__"<<*targetNode->pop<<std::endl;
            i++;
        }
        it_large += j;

    }
        for (size_t i = 0; i < tmp.size(); ++i)
    {
        std::cout << tmp[i] << " ";
    }
    data.swap(tmp);
}


int main(int argc, char** argv) {
    std::vector<int> vec;
    // std::vector<int> vector;

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
        // vector.push_back(static_cast<int>(num));
    }

    std::cout << "Before: ";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        std::cout << vec[i] << " ";
    }
    std::cout << "\n";

    clock_t startVec = clock();
    
    sort(vec);
    clock_t endVec = clock();
    double timeVec = static_cast<double>(endVec - startVec) / CLOCKS_PER_SEC * 1000000; // Microseconds
    //CLOCKS_PER_SECは1秒間に進むプロセッサのクロック数
    // clock_t startDeq = clock();
    // mergeInsertmergeInsertSortVectorDeque(vector);
    // clock_t endDeq = clock();
    // double timeDeq = static_cast<double>(endDeq - startDeq) / CLOCKS_PER_SEC * 1000000; // Microseconds

    // std::cout << "After: ";
    // for (size_t i = 0; i < vec.size(); ++i) 
    // {
    //     std::cout << vec[i] << " ";
    // }
    std::cout << "\n";

    std::cout << "Time to process a range of " << vec.size() << " elements with std::vector: " << timeVec << " us\n";
    // std::cout << "Time to process a range of " << deq.size() << " elements with std::deque: " << timeDeq << " us\n";

    return 0;
}
