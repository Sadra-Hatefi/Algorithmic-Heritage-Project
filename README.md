# Recursive Bitonic Sort (C++20)

## Files

- `sort_buffer.hpp`: Contains SortBuffer class used to contain the array elements.
- `bitonic_sort.hpp`: Declares `void sort(SortBuffer&, heritage::SortMetrics&)`.
- `bitonic_sort.cpp`: Recursive bitonic sort, recursive merge, and padding.
- `main.cpp`: Handles user input, calls the sorting function, and displays the sorted array and metrics.
- `ADS_metrics.hpp`: Metrics header supplied for the project.

## Build

**Standard build:**

```bash
g++ -std=c++20 -O2 -Wall -Wextra -Werror main.cpp bitonic_sort.cpp -o bitonic_sort
```

**AddressSanitizer build:**

```bash
g++ -std=c++20 -O1 -g -Wall -Wextra -Werror -fsanitize=address -fno-omit-frame-pointer main.cpp bitonic_sort.cpp -o bitonic_sort_asan
```

## Run

**Standard build:**

Linux/macOS:
```bash
./bitonic_sort
```

Windows (MinGW):
```powershell
.\bitonic_sort.exe
```

**AddressSanitizer build:**

Linux/macOS:
```bash
./bitonic_sort_asan
```

Windows (MinGW):
```powershell
.\bitonic_sort_asan.exe
```


Enter a positive array size, followed by that many integers.

## Metrics

- `comparisons`: Total number of comparisons performed by compare-and-swap.
- `element_swaps`: Swaps performed by compare-and-swap.
- `buffer_moves`: Assignments into or out of the temporary padded array.
- `alloc_count`: The number of temporary heap allocations made by `sort`.
- `peak_aux_bytes`: Temporary padded-array capacity in bytes.
- `elapsed_us`: Elapsed time measured by `heritage::ScopedTimer`.


