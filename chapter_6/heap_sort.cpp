#include <iostream>
#include <vector>
#include <assert.h>

class priority_queue {
private:
    std::vector<long> &_elements;
    int _heap_size;

    inline int left_child(int parent) {
        return parent * 2 + 1;
    }

    inline int right_child(int parent) {
        return parent * 2 + 2;
    }

    inline void swap(int l, int r) {
        long temp = _elements[l];
        _elements[l] = _elements[r];
        _elements[r] = temp;
    }
    
    void max_heapify(int index) {
        int left = left_child(index);
        int right = right_child(index);

        long value = _elements[index];
        int largest = index;
        if (left < _heap_size && value < _elements[left]) {
            largest = left;
            value = _elements[left];
        }

        if (right < _heap_size && value < _elements[right]) {
            largest = right;
        }

        if (largest == index)
            return;

        swap(largest, index);
        max_heapify(largest);
    }
    void build_max_heap() {
        for (int i = _elements.size() / 2; i >= 0; i--) {
            max_heapify(i);
        }
    }

public:
    priority_queue(std::vector<long> &elements): _elements(elements), _heap_size(elements.size()) { }
    void sort() {
        build_max_heap();
        for (size_t i = _elements.size() - 1; i > 0; i--) {
            swap(0, i);
            --_heap_size;
            max_heapify(0);
        }
    }
};

void sort(std::vector<long> &elements) {
    priority_queue h {elements};
    h.sort();
}

std::vector<long> generate_values(int max) {
    std::vector<long> values;
    srand(time(NULL));
    for (size_t i = 0; i < max; i++) {
        values.push_back(random());
    }
    return values;
}

int main(int argc, char const *argv[]) {
    std::vector<long> values = generate_values(10);
    sort(values);

    for (size_t i = 0; i < values.size(); i++) {
        std::cout << values[i] << " ";
    }

    long prev = values[0];
    for (size_t i = 1; i < values.size(); i++)
    {
        long cur = values[i];
        if (cur < prev) {
            std::cout << std::endl << "error on " << i << " " << prev << " " << cur << std::endl;
            return 1;
        }
        prev = cur;
    }

    return 0;
}
