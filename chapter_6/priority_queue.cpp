#include <iostream>
#include <vector>
#include <tuple>
#include <assert.h>

class priority_queue {
private:
    std::vector<long> _elements;
    int _heap_size;

    inline int left_child(int parent) {
        return parent * 2 + 1;
    }

    inline int right_child(int parent) {
        return parent * 2 + 2;
    }

    inline int parent(int child) {
        return (child - 1) / 2;
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
    void sort() {
        build_max_heap();
        for (size_t i = _elements.size() - 1; i > 0; i--) {
            swap(0, i);
            --_heap_size;
            max_heapify(0);
        }
    }

public:
    priority_queue(): _elements(std::vector<long>()), _heap_size(0) { }

    int size() {
        return _heap_size;
    }

    int insert(long key) {
        int index = _heap_size++;
        _elements.push_back(key);
        while (0 < index && _elements[parent(index)] < _elements[index]) {
            swap(index, parent(index));
            index = parent(index);
        }
        return _heap_size - 1;
    }

    void increase(int index, long key) {
        if (_heap_size < index)
            throw std::runtime_error("index больше heap_size");
        
        if (key < _elements[index])
            throw std::runtime_error("уменьшение ключа не поддерживается");
        
        _elements[index] = key;
        while (0 < index && _elements[parent(index)] < _elements[index]) {
            swap(index, parent(index));
            index = parent(index);
        }
    }

    int pop() {
        if (_heap_size == 0)
            throw std::runtime_error("очередь пуста");
        
        int top = _elements[0];
        --_heap_size;
        _elements[0] = _elements[_heap_size];
        max_heapify(0);
        return top;
    }
};

int main(int argc, char const *argv[]) {
    priority_queue queue;
    for (const auto elem : {1, 2, 3, 4}) {
        queue.insert(elem);
    }

    queue.increase(2, 10);

    while (queue.size() > 0) {
        std::cout << queue.pop() << " ";
    }

    return 0;
}
