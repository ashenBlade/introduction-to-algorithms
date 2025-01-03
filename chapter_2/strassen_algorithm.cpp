#include <iostream>
#include <vector>
#include <memory>
#include <tuple>

using matrix_data = std::vector<std::vector<long>>;

class matrix {
private:
    matrix_data _data;
    int _size;

    matrix get_part(int start_row, int start_col, int size) const {
        matrix_data data = matrix_data(size);
        for (size_t i = 0; i < size; i++)
            data[i] = std::move(std::vector<long>(size));

        for (size_t i = 0; i < size; i++) {
            for (size_t j = 0; j < size; j++) {
                data[i][j] = _data[i + start_row][j + start_col];
            }
        }
        
        return matrix(std::move(data));
    }
    std::tuple<matrix, matrix, matrix, matrix> split() const {
        if (_size == 1) {
            throw std::runtime_error("can not split 1 sized matrix");
        }

        int half = _size / 2;
        auto a11 = get_part(0, 0, half);
        auto a12 = get_part(0, half, half);
        auto a21 = get_part(half, 0, half);
        auto a22 = get_part(half, half, half);
        return std::make_tuple(
            std::move(a11), std::move(a12), 
            std::move(a21), std::move(a22)
        );
    }
    static matrix from_parts(matrix &a11, matrix &a12, matrix &a21, matrix&a22) {
        if (!(a11._size == a12._size && a12._size == a21._size && a21._size == a22._size)) {
            throw std::runtime_error("matrices should be equal sizes");
        }

        int result_size = a11._size * 2;
        matrix_data result = matrix_data(result_size);
        for (size_t i = 0; i < result_size; i++)
            result[i] = std::vector<long>(result_size);

        int part_size = a11._size;
        // a11
        for (size_t i = 0; i < part_size; i++) {
            for (size_t j = 0; j < part_size; j++) {
                result[i][j] = a11._data[i][j];
            }
        }
        
        // a12
        for (size_t i = 0; i < part_size; i++) {
            for (size_t j = 0; j < part_size; j++) {
                result[i][j + part_size] = a12._data[i][j];
            }
        }

        // a21
        for (size_t i = 0; i < part_size; i++) {
            for (size_t j = 0; j < part_size; j++) {
                result[i + part_size][j] = a21._data[i][j];
            }
        }

        // a22
        for (size_t i = 0; i < part_size; i++) {
            for (size_t j = 0; j < part_size; j++) {
                result[i + part_size][j + part_size] = a22._data[i][j];
            }
        }

        return matrix(std::move(result));
    }
public:
    inline int size() const {
        return _size;
    }
    inline long get(int row, int col) const {
        return _data[row][col];
    }
    matrix add(const matrix &other) const {
        matrix_data result = matrix_data(other._size);
        for (size_t i = 0; i < other._size; i++)
            result[i] = std::move(std::vector<long>(other._size));

        for (size_t i = 0; i < other._size; i++)
            for (size_t j = 0; j < other._size; j++)
                result[i][j] = _data[i][j] + other._data[i][j];

        return matrix(std::move(result));
    };
    matrix operator+(const matrix &other) const {
        return add(other);
    }

    matrix multiply(const matrix &other) const {
        if (_size != other._size) {
            throw std::runtime_error("passed matrices should have equal sizes");
        }

        if (_size == 1) {
            matrix_data data = matrix_data(1);
            data[0] = std::move(std::vector<long>({_data[0][0] * other._data[0][0]}));
            return matrix(std::move(data));
        }

        auto [a11, a12, a21, a22] = split();
        auto [b11, b12, b21, b22] = other.split();

        auto s1 = b12 - b22;
        auto s2 = a11 + a12;
        auto s3 = a21 + a22;
        auto s4 = b21 - b11;
        auto s5 = a11 + a22;
        auto s6 = b11 + b22;
        auto s7 = a12 - a22;
        auto s8 = b21 + b22;
        auto s9 = a11 - a21;
        auto s10 = b11 + b12;

        auto p1 = a11 * s1;
        auto p2 = s2 * b22;
        auto p3 = s3 * b11;
        auto p4 = a22 * s4;
        auto p5 = s5 * s6;
        auto p6 = s7 * s8;
        auto p7 = s9 * s10;

        auto c11 = p5 + p4 - p2 + p6;
        auto c12 = p1 + p2;
        auto c21 = p3 + p4;
        auto c22 = p5 + p1 - p3 - p7;

        return matrix::from_parts(c11, c12, c21, c22);
    };
    matrix operator*(const matrix &other) const {
        return multiply(other);
    }

    matrix subtract(const matrix &other) const {
        // Preallocate memory
        matrix_data result = matrix_data(other._size);
        for (size_t i = 0; i < other._size; i++)
            result[i] = std::move(std::vector<long>(other._size));
    
        for (size_t i = 0; i < other._size; i++) {
            for (size_t j = 0; j < other._size; j++) {
                result[i][j] = _data[i][j] - other._data[i][j];
            }
        }

        return matrix(std::move(result));
    }
    matrix operator-(const matrix &other) const {
        return subtract(other);
    }

    matrix(matrix_data &&data): _data(std::move(data)), _size(_data.size()) { 
        if (_data.size() != _data[0].size()) {
            throw std::runtime_error("matrix should be square");
        }
    };

    /* Move ctor */
    matrix(matrix &&other) {
        _data = std::move(other._data);
        _size = other._size;
    }
    matrix &operator=(matrix &&other) {
        if (this == &other) {
            return *this;
        }

        _data = std::move(other._data);
        _size = other._size;
        return *this;
    }

    /* Copy ctor - deleted */
    matrix(const matrix &) = delete;
    matrix &operator=(const matrix &other) = delete;
};

int main(int argc, char const *argv[]) {
    matrix left = matrix({
        {1, 2, 3, 4},
        {1, 2, 3, 4},
        {1, 2, 3, 4},
        {1, 2, 3, 4},
    });
    matrix right = matrix({
        {4, 5, 6, 7},
        {4, 5, 6, 7},
        {4, 5, 6, 7},
        {4, 5, 6, 7},
    });
    matrix result = left * right;

    for (size_t i = 0; i < result.size(); i++) {
        std::cout << result.get(i, 0);
        for (size_t j = 1; j < result.size(); j++) {
            std::cout << ' ' << result.get(i, j);
        }
        
        std::cout << std::endl;
    }
    
    return 0;
}


