// Headers and Libraries

#include "bitonic_sort.hpp"

#include <cstddef>   // Provides std::size_t
#include <exception> // Provides std::exception
#include <iostream>  // Provides std::cin, std::cout and std::cerr

int main() {
    std::size_t n = 0; // Initialize the array size

    std::cout << "Enter array size: ";

    if (!(std::cin >> n) || n == 0) {
        std::cerr << "Invalid array size.\n";
        return 1;
    } // Receiving the array size as input and making sure it's a positive integer

    try {
        SortBuffer buffer(n); // Create the buffer of size n

        std::cout << "Enter " << n << " elements:\n";

        for (std::size_t i = 0; i < n; ++i) {
            if (!(std::cin >> buffer.begin()[i])) {
                std::cerr << "Invalid array element.\n";
                return 1;
            }
        } // Reading the array elements from user input and validating that each is a valid integer within the range of int

        heritage::SortMetrics metrics; // Create a metrics object (to record and display the benchmarks)

        heritage::sort(buffer, metrics);

        // After sorting the array, we output the sorted array, followed by the metrics:
        std::cout << "Sorted array: ";

        for (const int value : buffer) {
            std::cout << value << ' ';
        }

        std::cout << '\n';

        metrics.print();

    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    } // If any exception happens during the procedure, we catch it and we show a description of the exception

    return 0;
}