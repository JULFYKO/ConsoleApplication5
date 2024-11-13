#include <iostream>
#include <cstring>
using std::cout;
using std::endl;
class Vector {
private:
    int* data;
    size_t size;
    size_t capacity;

    void resize(size_t newCapacity) {
        int* newData = new int[newCapacity];
        for (size_t i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    Vector() : data(nullptr), size(0), capacity(0) {}

    ~Vector() {
        delete[] data;
    }

    Vector operator+(const Vector& other) const {
        Vector result;
        result.resize(size + other.size);
        for (size_t i = 0; i < size; ++i) {
            result.data[result.size++] = data[i];
        }
        for (size_t i = 0; i < other.size; ++i) {
            result.data[result.size++] = other.data[i];
        }
        return result;
    }

    Vector operator-(const Vector& other) const {
        Vector result;
        for (size_t i = 0; i < size; ++i) {
            bool flag = true;
            for (size_t j = 0; j < other.size; ++j) {
                if (data[i] == other.data[j]) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                result.pushBack(data[i]);
            }
        }
        return result;
    }

    Vector operator*(const size_t& n) const {
        Vector result;
        result.resize(size);
        for (size_t i = 0; i < size; ++i) {
            result.data[i] = data[i] * static_cast<int>(n);
        }
        result.size = size;
        return result;
    }

    explicit operator int() const {
        int sum = 0;
        for (size_t i = 0; i < size; ++i) {
            sum += data[i];
        }
        return sum;
    }

    explicit operator char* () const {
        size_t strSize = size * 3 + 1;
        char* result = new char[strSize];
        char* ptr = result;
        for (size_t i = 0; i < size; ++i) {
            int len = sprintf_s(ptr, strSize - (ptr - result), "%d ", data[i]);
            ptr += len;
        }
        result[strSize - 1] = '\0';
        return result;
    }

    void pushBack(const int& value) {
        if (size == capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        data[size++] = value;
    }

    void pushFront(const int& value) {
        if (size == capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        for (size_t i = size; i > 0; --i) {
            data[i] = data[i - 1];
        }
        data[0] = value;
        ++size;
    }

    void insert(const int& value, const size_t& index) {
        if (index > size) return;
        if (size == capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        for (size_t i = size; i > index; --i) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        ++size;
    }

    void popBack() {
        if (size > 0) --size;
    }

    void popFront() {
        if (size > 0) {
            for (size_t i = 0; i < size - 1; ++i) {
                data[i] = data[i + 1];
            }
            --size;
        }
    }

    void remove(const size_t& index) {
        if (index >= size) return;
        for (size_t i = index; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }
        --size;
    }

    int find(const int& value) const {
        for (size_t i = 0; i < size; ++i) {
            if (data[i] == value) return static_cast<int>(i);
        }
        return -1;
    }

    void print() const {
        for (size_t i = 0; i < size; ++i) {
            cout << data[i] << ' ';
        }
        cout << endl;
    }
};

int main() {
    int arrValues[] = { 2, 8, 5, 1, 10, 5, 9, 9, 3, 5 };
    int spliceValues[] = { 5, 1, 10, 22, 33, 44 };

    Vector arr, splice;
    for (int val : arrValues) arr.pushBack(val);
    for (int val : spliceValues) splice.pushBack(val);

    Vector combined = arr + splice;
    Vector unique = arr - splice;
    Vector multiplied = arr * 3;

    cout << "Combined: "; combined.print();
    cout << "Unique in arr: "; unique.print();
    cout << "Multiplied by 3: "; multiplied.print();

    int sum = static_cast<int>(arr);
    cout << "Sum of elements in arr: " << sum << endl;

    char* arrAsString = static_cast<char*>(arr);
    cout << "Elements of arr as string: " << arrAsString << endl;
    delete[] arrAsString;

    return 0;
}
