#include <vector>
#include <iostream>

inline void swap(std::vector<long> &elements, int i, int j) {
    long temp = elements[i];
    elements[i] = elements[j];
    elements[j] = temp;
}

int get_median(std::vector<long> &elements, int left, int right) {
    swap(elements, left + random() % (right - left + 1), right);
    int pivot = elements[right];
    int i = left - 1;
    for (size_t j = left; j < right; j++) {
        if (pivot < elements[j])
            continue;
        
        ++i;
        swap(elements, i, j);
    }
    swap(elements, i + 1, right);
    return i + 1;
}

long get_order_statistic(std::vector<long> &values, int i, int left, int right) {
    if (left == right) {
        return values[left];
    }
    
    int pivot = get_median(values, left, right);
    if (pivot == i) {
        return values[i];
    }

    if (pivot < i) {
        return get_order_statistic(values, i, pivot + 1, right);
    } else {
        return get_order_statistic(values, i, left, pivot - 1);
    }
}

long get_order_statistic(std::vector<long> &values, int i) {
    return get_order_statistic(values, i, 0, values.size() - 1);
}

int main(int argc, char const *argv[]) {
    std::vector<long> values = {5, 6, 2, 9, 1, 3, 4, 7};
    for (size_t i = 0; i < values.size(); i++) {
        srand(42);
        std::vector<long> other = std::vector<long>(values.cbegin(), values.cend());
        long statistic = get_order_statistic(other, i);
        std::cout << "[" << i << "] = " << statistic << std::endl;
    }
    return 0;
}
