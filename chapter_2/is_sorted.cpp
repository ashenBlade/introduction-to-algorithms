#include <iostream>

int main(int argc, char const *argv[])
{
    long size;
    std::cin >> size;
    long prev;
    std::cin >> prev;
    for (long i = 1; i < size; ++i) {
        long cur;
        std::cin >> cur;
        if (cur < prev) {
            std::cout << "Detected invalid sorted sequence at " << i << std::endl;
            return 1;
        }
        prev = cur;
    }
    return 0;
}
