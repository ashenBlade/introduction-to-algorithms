#include <vector>
#include <iostream>
#include <algorithm>

void sort(std::vector<long> &values) {
    long max = *std::max_element(values.cbegin(), values.cend());
    std::vector<long> counts = std::vector<long>(max + 1, 0);
    std::vector<long> sorted = std::vector<long>(values.size(), 0);

    for (int i = 0; i < values.size(); i++) {
        counts[values[i]]++;
    }

    for (int i = 1; i < counts.size(); i++) {
        counts[i] += counts[i - 1];
    }

    for (int i = values.size() - 1; i >= 0; i--) {
        long value = values[i];
        sorted[counts[value]] = value;
        counts[value]--;
    }

    values.swap(sorted);
}

int main(int argc, const char** argv) {
    std::vector<long> values = {2, 5, 3, 0, 2, 3, 0, 3};
    sort(values);
    for (size_t i = 0; i < values.size(); i++) {
        std::cout << values[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}
