#include <vector>
#include <iostream>

inline void swap(std::vector<long> &elements, int i, int j) {
    long temp = elements[i];
    elements[i] = elements[j];
    elements[j] = temp;
}

constexpr int bucket_size = 5;

void sort_part(std::vector<long> &data, int start, int end) {
    /* Insertion sort */
    for (int i = start; i < end; i++) {
        long cur = data[i];
        for (int inner = i - 1; inner >= 0; inner--) {
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

int partition(std::vector<long> &values, int left, int right, int pivot) {
    swap(values, pivot, right);

    pivot = values[right];
    int i = left - 1;
    for (size_t j = left; j <= right; j++) {
        if (pivot <= values[j])
            continue;
        
        ++i;
        swap(values, i, j);
    }
    swap(values, i + 1, right);
    return i + 1;
}


int get_median(std::vector<long> &values, int left, int right) {
    int start = left;
    int end = left + bucket_size;
    while (end < right) {
        sort_part(values, start, end);
        start += bucket_size;
        end += bucket_size;
    }

    // Отсортировать оставшееся
    sort_part(values, start, right);


    /* Находим медиану медиан */
    int count = right - left + 1;
    if (bucket_size <= count) {
        if (count % bucket_size == 0) {
            /* Все группы по 5 элементов */
            return left + ((count / bucket_size) / 2) * 5 + bucket_size / 2;
        } else {
            /* Есть последняя неполная группа */
            return left + (((count / bucket_size) / 2) * 5) + bucket_size / 2;
        }
    } else {
        /* Нет полных групп */
        return left + count / 2;
    }
}

long get_order_statistic(std::vector<long> &values, int i, int left, int right) {
    if (left == right) {
        return values[left];
    }

    int median = get_median(values, left, right);
    int pivot = partition(values, left, right, median);
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
