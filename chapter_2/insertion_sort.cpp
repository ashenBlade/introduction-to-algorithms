#include <iostream>
#include <vector>

void insertion_sort(std::vector<long> &data) {
    for (size_t i = 1; i < data.size(); i++) {
        long cur = data[i];
        for (size_t inner = i - 1; inner >= 0; inner--) {
            if (cur < data[inner]) {
                long temp = data[inner];
                data[inner] = cur;
                data[inner + 1] = temp;
            } else {
                break;
            }
        }
    }
}

int main(int argc, const char **argv) {
    long size;
    std::vector<long> numbers;
    std::cin >> size;
    while (0 < size) {
        long num;
        std::cin >> num;
        numbers.push_back(num);
        --size;
    }
    insertion_sort(numbers);
    for (const long num: numbers) {
        std::cout << num << "\n";
    }
    return 0;
}