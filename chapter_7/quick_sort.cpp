#include <vector>
#include <iostream>

inline void swap(std::vector<long> &elements, int i, int j) {
    long temp = elements[i];
    elements[i] = elements[j];
    elements[j] = temp;
}

int get_median(std::vector<long> &elements, int left, int right) {
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

void qsort(std::vector<long> &elements, int left, int right) {
    if (right <= left)
        return;

    int p = get_median(elements, left, right);
    qsort(elements, left, p - 1);
    qsort(elements, p + 1, right);
}

void qsort(std::vector<long> &elements) {
    qsort(elements, 0, elements.size() - 1);
}

int main(int argc, const char **argv) {
    std::vector<long> values = {1, 4, 5, 2, 7};
    qsort(values);

    for (auto &&i : values) {
        std::cout << i << " ";
    }
    
    return 0;
}