#include <iostream>
#include <vector>
#include <deque>
#include <cstdlib>
#include <ctime>
#include <climits> // For INT_MAX

void mergeInsertSortVector(std::vector<int>& vec)
{
    for (size_t i = 0; i < vec.size() - 1; ++i)
    {
        for (size_t j = 0; j < vec.size() - i - 1; ++j)
        {
            if (vec[j] > vec[j + 1])
            {
                std::swap(vec[j], vec[j + 1]);
            }
        }
    }
}

void mergeInsertSortDeque(std::deque<int>& deq) {
    for (size_t i = 0; i < deq.size() - 1; ++i)
    {
        for (size_t j = 0; j < deq.size() - i - 1; ++j)
        {
            if (deq[j] > deq[j + 1])
            {
                std::swap(deq[j], deq[j + 1]);
            }
        }
    }
}

int main(int argc, char** argv) {
    std::vector<int> vec;
    std::deque<int> deq;

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
        deq.push_back(static_cast<int>(num));
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
    clock_t startDeq = clock();
    mergeInsertSortDeque(deq);
    clock_t endDeq = clock();
    double timeDeq = static_cast<double>(endDeq - startDeq) / CLOCKS_PER_SEC * 1000000; // Microseconds

    std::cout << "After: ";
    for (size_t i = 0; i < vec.size(); ++i) 
    {
        std::cout << vec[i] << " ";
    }
    std::cout << "\n";

    std::cout << "Time to process a range of " << vec.size() << " elements with std::vector: " << timeVec << " us\n";
    std::cout << "Time to process a range of " << deq.size() << " elements with std::deque: " << timeDeq << " us\n";

    return 0;
}
