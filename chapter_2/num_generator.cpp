#include <iostream>
#include <random>

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        std::cout << "Pass number of digits as first argument";
        return 1;
    }
    char *end;
    long size = std::strtol(argv[1], &end, 10);
    srand(time(NULL));

    std::cout << size << "\n";
    while (0 < size) {
        std::cout << rand() << "\n";
        --size;
    }

    return 0;
}
