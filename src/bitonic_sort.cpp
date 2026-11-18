
// Headers and Libraries

#include "bitonic_sort.hpp"

#include <climits> // Provides INT_MAX
#include <cstddef> // Provides std::size_t
#include <limits> // Provides information about nermic limits, such as the maximum value of std::size_t
#include <stdexcept> // Provides std::length_error
#include <utility> // Provides std::swap

// We define the heritage namespace

namespace heritage {

/* We define an anonymous namespace inside the heritage namespace, elements within this namespace
  are only accessible from within the bitonic_sort.cpp file (the functions inside are only internal helper functions)*/
namespace {

    void compare_and_swap(int* values,
                          std::size_t first,
                          std::size_t second,
                          bool is_ascending,
                          SortMetrics& metrics) {
        ++metrics.comparisons;

        const bool out_of_order =
            is_ascending ? (values[first] > values[second])
                         : (values[first] < values[second]);

        if (out_of_order) {
            std::swap(values[first], values[second]);
            ++metrics.element_swaps;
        }
    }

    /* This function is equivalent to the comparator component which was discussed in REPORT.md, it takes
        the list of numbers, indices for two values, compares the two values, and decides to swap them 
        based on the sorting condition(ascending or descending). Updating the metrics values accordingly */

    void bitonic_merge(int* values,
                       std::size_t low, // Index indicating where the current section of the array starts
                       std::size_t count, // Number of elements in the current section
                       bool is_ascending,
                       SortMetrics& metrics) {
        if (count <= 1) {
            return;
        } // Base case of the recursion, an array of length 1 is trivially sorted

        const std::size_t half = count / 2; // Divide the current section in half

        // Compare corresponding elements in the two halves.
        for (std::size_t i = low; i < low + half; ++i) {
            compare_and_swap(values, i, i + half, is_ascending, metrics);
        } // Compare the corresponding elements in the two halves

        // Recursively run the bitonic merger for each half.
        bitonic_merge(values, low, half, is_ascending, metrics);
        bitonic_merge(values, low + half, half, is_ascending, metrics);
    }

    void bitonic_sort(int* values,
                      std::size_t low, // Index indicating where the current section of the array starts
                      std::size_t count, // Number of elements in the current section
                      bool is_ascending,
                      SortMetrics& metrics) {
        if (count <= 1) {
            return;
        } // Base case of the recursion, an array of length 1 is trivially sorted

        const std::size_t half = count / 2;

        /* Construct a bitonic sequence by sorting the first half in ascending order and the second half
        in descending order, this is equivalent to sorting both parts in ascending order and then reversing the second part*/
        bitonic_sort(values, low, half, true, metrics);
        bitonic_sort(values, low + half, half, false, metrics);

        // Run the bitonic merger to sort in the required order.
        bitonic_merge(values, low, count, is_ascending, metrics);
    }

    std::size_t next_power_of_two(std::size_t value) {
        std::size_t result = 1;
        const std::size_t max_size = std::numeric_limits<std::size_t>::max();

        while (result < value) {
            if (result > max_size / 2) { // Making sure result doesn't exceed the limit of size_t after multiplying by 2
                throw std::length_error(
                    "Input is too large to pad to a power of two");
            }
            result *= 2;
        }

        if (result > max_size / sizeof(int)) {
            throw std::length_error("Padded array size is too large");
        }
        /* Making sure that the byte size of the array (given by result * sizeof(int)) is representable by size_t
            this is a safety check to make sure int* padded = new int[padded_size]; could handle the size safely*/

        return result;
    } // We initialize the integer result to 1 and keep multiplying it by two until it is greater than the input value

}

void sort(SortBuffer& buf, SortMetrics& metrics) {
    metrics.reset();
    ScopedTimer timer(metrics.elapsed_us); // Start measuring execution time and store it in metrics.elapsed_us

    const std::size_t original_size = buf.size(); // Store the size of the buffer in original_size

    if (original_size < 2) {
        return;
    } // An array of size 0 or 1 is trivially sorted

    const std::size_t padded_size = next_power_of_two(original_size);

    // If the size is already a power of two, there is no need for padding, we sort immediately
    if (padded_size == original_size) {
        bitonic_sort(
            buf.begin(), 0, original_size, true, metrics);
        return;
    }

    // Otherwise, we allocate a temporary array of size padded_size and fill the remaining positions with a dummy element (INT_MAX)
    int* padded = new int[padded_size];
    ++metrics.alloc_count; // Increment the allocation count in the metrics
    metrics.peak_aux_bytes = padded_size * sizeof(int); // Account for how many bytes the temporary array occupies

    for (std::size_t i = 0; i < original_size; ++i) {
        padded[i] = buf.begin()[i];
        ++metrics.buffer_moves;
    } // Copy the the elements from the original array

    for (std::size_t i = original_size; i < padded_size; ++i) {
        padded[i] = INT_MAX;
        ++metrics.buffer_moves;
    } // Fill in the remaining positions with dummy elements (INT_MAX)

    bitonic_sort(padded, 0, padded_size, true, metrics); // Sort the temporary array

    for (std::size_t i = 0; i < original_size; ++i) {
        buf.begin()[i] = padded[i];
        ++metrics.buffer_moves;
    } // Copy only the non-dummy elements of the temporary array back in the original array (this is equivalent to removing the dummy elements from the temporary array before copying it back into the original array)

    delete[] padded;
    // Finally, we deallocate the temporary array
}

}
