[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-2972f46106e565e64193e422d61a12cf1da4916b45550586e14ef0a7c637dd04.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=18000393)
# IB9JHO Lab: RAII implemenation of Vector<T> and piecewise function approximation

# Exercise 1: Implement Vector<T> 
Using manual memory management with new and delete use RAII concepts create a template class Vector<T> which can be used similiarly to std::Vector<T>
without leaving memory leaks or other issues such as dangling pointers and double-deletes.
Implement the following functions:
- Vector<T>() - constructor
- Vector<T>(size_t size) - constructor with size that initializes the Vector<T> with zeros
- Vector<T>(const Vector<T>& other) - copy constructor
- Vector<T>& operator=(const Vector<T>& other) - copy assignment operator
- T& operator[](size_t index) - subscript operator
- ~Vector<T>() - destructor

# Exercise 2: Add mathematical operations
Implement the following overloads for the Vector<T> class:
- Vector<T> operator+(const Vector<T>& other) - addition operator
- Vector<T> operator-(const Vector<T>& other) - subtraction operator
- Vector<T> operator*(T scalar) - scalar multiplication operator
- T dot(const Vector<T>& other) - dot product operator

# Exercise 3: Memory management utilities
- void resize(size_t size) - resize the underlying array of the Vector<T> and keep the existing elements that fit
- void push_back(T value) - add a new element to the end of the Vector<T> keeping the existing elements

# Exercise 4: Implement PiecewiseFunction
Using the provided piecewise_function.h and polynomial.h header files create the implementation in piecewise_function.cpp. The function should take sets of x,y points and create linear segments between them that can be evaluated at any x value. The idea is to create an approximation of any smooth function using a set of linear segments.

Implement the following functions:
- PiecewiseFunction(const std::vector<double>& x, const std::vector<double>& y) - constructor that takes x and y coordinates
- void fit() - creates linear fits between each pair of adjacent points and stores them in m_fit
- size_t find_x(double x) const - determines which segment contains the given x value
- double operator()(double x) const - evaluates the function at point x

Test your implementation by running test_piecewise_function from the test tab

# Exercise 5:
- Re-implement find_x using a binary search algorithm to improve performance for large arrays

# Submission
Once you have tested your solutions, submit your work by pushing your changes to the repository.
You can use the commit message "Submit assignment" or something similar.