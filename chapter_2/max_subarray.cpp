#include <iostream>
#include <vector>
#include <limits.h>

struct interval {
    int left;
    int right;
    long sum;

    interval(int left, int right, long sum): left(left), right(right), sum(sum) { };

    interval(interval &&other) {
        left = other.left;
        right = other.right;
        sum = other.sum;
    };

    interval &operator=(interval &&other) {
        if (this == &other) {
            return *this;
        }

        right = other.right;
        left = other.left;
        sum = other.sum;
        return *this;
    };
};

interval find_max_subarray_intersection(std::vector<long> &data, int left, int mid, int right) {
    int max_left_index = -1;
    long max_left_sum = LONG_MIN;
    long sum = 0;
    for (int i = mid; left <= i; --i) {
        long value = data[i];
        sum += value;
        if (max_left_sum < sum) {
            max_left_sum = sum;
            max_left_index = i;
        }
    }

    sum = 0;
    int max_right_index = -1;
    long max_right_sum = LONG_MIN;
    for (int i = mid + 1; i <= right; ++i) {
        long value = data[i];
        sum += value;
        if (max_right_sum < sum) {
            max_right_sum = sum;
            max_right_index = i;
        }
    }

    return interval(max_left_index, max_right_index, max_right_sum + max_left_sum);
}

interval find_max_subarray(std::vector<long> &data, int left, int right) {
    if (left == right) {
        return interval(left, right, data[left]);
    }

    int mid = left + (right - left) / 2;
    interval max_left = find_max_subarray(data, left, mid);
    interval max_right = find_max_subarray(data, mid + 1, right);
    interval max_intersect = find_max_subarray_intersection(data, left, mid, right);

    if (max_left.sum <= max_intersect.sum && max_right.sum <= max_intersect.sum) {
        return max_intersect;
    }

    if (max_left.sum <= max_right.sum && max_intersect.sum <= max_right.sum) {
        return max_right;
    }

    return max_left;
}

interval find_max_subarray(std::vector<long> &data) {
    if (data.size() == 0) {
        return interval(-1, -1, 0);
    }

    if (data.size() == 1) {
        return interval(0, 0, data[0]);
    }

    std::vector<long> deltas = std::vector<long>(data.size());

    long prev = data[0];
    for (int i = 1; i < data.size(); ++i) {
        long cur = data[i];
        deltas[i] = cur - prev;
        prev = cur;
    }
    deltas[0] = 0;

    return find_max_subarray(deltas, 0, deltas.size() - 1);
}

int main(int argc, char const *argv[])
{
    // Пример из книги
    std::vector<long> data = {100, 113, 110, 85, 105, 102, 86, 63, 81, 101, 94, 106, 101, 79, 94, 90, 97};

    auto max = find_max_subarray(data);

    std::cout << "Max: " << max.sum << "\nLeft: " << max.left - 1 << "\nRight: " << max.right << "\n";
    return 0;
}
