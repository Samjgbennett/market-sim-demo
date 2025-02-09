#pragma once
#include <cstddef>
#include <stdexcept>
#include <algorithm>

template <typename T>
class Vector
{
private:
    T *data;
    size_t capacity;

public:
    // Constructors and destructor
    Vector() : data(nullptr), capacity(0) {}

    explicit Vector(size_t size) : capacity(size)
    {
        // allocate enough memory for 'size' T's
        data = new T[size]();
    }

    Vector(const Vector &other) : capacity(other.capacity)
    {
        if (capacity > 0)
        {
            // allocate new memory
            data = new T[capacity];
            // copy over data
            std::copy(other.data, other.data + capacity, data);
        }
        else {
            data = nullptr;
        }
    }

    Vector &operator=(const Vector &other)
    {
        // deal with self-assignment
        if (&other == this)
            return *this;

        // data can't be reused
        if (other.capacity != capacity)
        {
            // clean up lhs vector
            delete[] data;
            data = nullptr;
            // set capacity correctly
            capacity = other.capacity;
            data = new T[capacity]();
        }

        std::copy(other.data, other.data + capacity, data);

        return *this;
    }

    ~Vector()
    {
        // de allocate all memory
        delete[] data;
    }

    // Accessors
    T &operator[](size_t index)
    {
        return data[index];
    }

    const T &operator[](size_t index) const
    {
        return data[index];
    }

    size_t size() const
    {
        return capacity;
    }

    // Arithmetic operations
    Vector operator+(const Vector &other) const
    {
        Vector result(capacity);

        for (size_t i = 0; i < capacity; ++i)
        {
            result[i] = other[i] + data[i];
        }
        return result;
    }

    Vector operator-(const Vector &other) const
    {
        Vector result(capacity);

        for (size_t i = 0; i < capacity; ++i)
        {
            result[i] = data[i] - other[i];
        }

        return result;
    }

    Vector operator*(const T &scalar) const
    {
        Vector result(capacity);

        for (size_t i = 0; i < capacity; ++i)
        {
            result[i] = scalar * data[i];
        }

        return result;
    }

    T dot(const Vector &other) const
    {
        T result = T();

        for (size_t i = 0; i < capacity; ++i)
        {
            result += data[i] * other[i];
        }
        return result;
    }

    // Modifiers
    void resize(size_t size)
    {
        if (size == capacity)
            return;

        T *newData = size > 0 ? new T[size]() : nullptr;

        // Copy existing elements
        std::copy(data, data + std::min(size, capacity), newData);

        delete[] data;
        data = newData;
        capacity = size;
    }

    void push_back(const T &value)
    {
        T* new_data = new T[capacity + 1];
        std::copy(data, data + capacity, new_data);
        new_data[capacity] = value;
        delete[] data;
        data = new_data;
        capacity = capacity + 1;
    }

    friend std::ostream& operator<<(std::ostream &os, const Vector &v)
    {
        os << "[";
        for (size_t i = 0; i < v.capacity; ++i)
        {
            os << v.data[i];
            if (i < v.capacity - 1)
            {
                os << ", ";
            }
        }
        os << "]";
        return os;
    }
};