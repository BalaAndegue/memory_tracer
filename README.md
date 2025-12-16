# 📊 Memory Access Pattern Tracer

A C-based memory access profiling tool that tracks and analyzes memory access patterns in real-time. This tool helps understand how different access patterns affect memory performance and locality.

## 🎯 Features

- **Real-time Memory Access Tracking**: Monitors every memory access within allocated pages
- **Multiple Access Patterns**: Implements sequential, random, and spatial locality patterns
- **Page-Level Granularity**: Tracks access at 4KB page boundaries
- **CSV Data Export**: Saves access statistics for analysis in external tools
- **Lightweight Overhead**: Minimal performance impact on traced applications

## 📁 Project Structure

```
memory_tracer/
├── main.c                    # Main tracer implementation
├── memory_access_data.csv    # Generated access data (after execution)
├── bin/
│   └── Debug/
│       └── memory_tracer     # Compiled executable
├── obj/
│   └── Debug/
│       └── main.o           # Compiled object file
├── memory_tracer.cbp        # Code::Blocks project file
├── memory_tracer.depend     # Project dependencies
└── README.md               # This documentation
```

## 🏗️ Architecture

### Data Structures
```c
typedef struct {
    unsigned long page_number;  // Page identifier
    int count;                  // Access counter
} page_access_t;
```

### Configuration Constants
- `PAGE_SIZE`: 4096 bytes (standard system page size)
- `NUM_PAGES`: 256 (1MB of tracked memory)
- `MAX_ACCESSES`: 10000 maximum tracked accesses

## 🚀 Getting Started

### Prerequisites
```bash
# Ubuntu/Debian
sudo apt-get install build-essential

# macOS
xcode-select --install
```

### Compilation
```bash
# Using GCC
gcc -o memory_tracer main.c -Wall -Wextra

# Using Code::Blocks
# Open memory_tracer.cbp and build
```

### Execution
```bash
./bin/Debug/memory_tracer
```

## 📖 API Reference

### `void init_page_counter()`
Initializes the page access tracking structure with zero counts.

### `void record_page_access(void* address)`
Records a memory access to the specified address.
- Calculates page number from address
- Increments access counter for that page

### `void save_access_data(const char* filename)`
Exports access statistics to CSV format.
- Creates file with `page_number,access_count` columns
- Includes all tracked pages

## 🧪 Access Patterns

### 1. Sequential Pattern
```c
void sequential_access_pattern(int* buffer, int size);
```
- Accesses memory in linear order
- Ideal for prefetching optimization
- Represents array traversal

### 2. Random Pattern
```c
void random_access_pattern(int* buffer, int size);
```
- Accesses random memory locations
- Simulates hash table or unpredictable access
- Worst-case for cache performance

### 3. Spatial Locality Pattern
```c
void spatial_locality_pattern(int* buffer, int size);
```
- Accesses small clusters of nearby addresses
- Represents common access patterns in real applications
- Good cache utilization

## 📊 Output Format

The tool generates `memory_access_data.csv` with:
```csv
page_number,access_count
0,124
1,98
2,156
...
```

## 🧠 Example Usage

```c
#include <stdio.h>
#include "tracer.h"

int main() {
    // Initialize tracing system
    init_page_counter();
    
    // Allocate memory to trace
    int* buffer = malloc(NUM_PAGES * PAGE_SIZE);
    
    // Test different patterns
    sequential_access_pattern(buffer, buffer_size);
    random_access_pattern(buffer, buffer_size);
    
    // Save results
    save_access_data("access_patterns.csv");
    
    // Cleanup
    free(buffer);
    
    return 0;
}
```

## 📈 Analysis Examples

### Visualizing Results with Python
```python
import pandas as pd
import matplotlib.pyplot as plt

# Load data
data = pd.read_csv('memory_access_data.csv')

# Plot access distribution
plt.figure(figsize=(10, 6))
plt.bar(data['page_number'], data['access_count'])
plt.xlabel('Page Number')
plt.ylabel('Access Count')
plt.title('Memory Access Distribution')
plt.savefig('access_heatmap.png')
```

### Statistical Analysis
```python
# Calculate statistics
print(f"Total accesses: {data['access_count'].sum()}")
print(f"Average accesses per page: {data['access_count'].mean():.2f}")
print(f"Most accessed page: {data['access_count'].idxmax()}")
print(f"Access standard deviation: {data['access_count'].std():.2f}")
```

## 🔬 Technical Details

### Page Calculation
```c
unsigned long page_num = (unsigned long)address / PAGE_SIZE;
```
- Uses integer division to determine page number
- Works with any pointer type

### Memory Overhead
- Tracking structure: 256 pages × 16 bytes = 4KB
- Minimal runtime overhead for recording

### Performance Impact
- `record_page_access()`: O(1) complexity
- No system calls during normal operation
- Suitable for production profiling

## 🧪 Testing Scenarios

### Test 1: Baseline Performance
```bash
time ./memory_tracer
```
Measures total execution time with all patterns.

### Test 2: Pattern Comparison
```c
// Run only specific patterns
sequential_access_pattern(buffer, buffer_size);
// Comment out others for comparison
```

### Test 3: Custom Workloads
```c
void custom_pattern(int* buffer, int size) {
    // Implement specific access pattern
    for (int i = 0; i < size; i += stride) {
        buffer[i] = compute_value(i);
        record_page_access(&buffer[i]);
    }
}
```

## 📚 Learning Applications

### Computer Architecture Education
- Demonstrates cache line principles
- Shows spatial vs temporal locality
- Illustrates page boundary effects

### Performance Optimization
- Identify hot pages in applications
- Optimize data structure layout
- Improve cache utilization

### System Programming
- Understand virtual memory mechanics
- Learn about page tables and TLB
- Study memory hierarchy effects

## 🔧 Extending the Project

### Additional Features
1. **Temporal Tracking**: Add timestamps to access records
2. **Thread Awareness**: Support multi-threaded tracing
3. **Real-time Visualization**: Display heatmap during execution
4. **Pattern Detection**: Automatically identify access patterns
5. **Performance Counters**: Integrate with hardware performance monitors

### Integration Possibilities
- Link with existing applications via LD_PRELOAD
- Create library version for easy inclusion
- Add support for different page sizes
- Implement circular buffer for streaming data

## 🐛 Known Limitations

- Fixed page count (256 pages = 1MB)
- No support for multi-threaded applications
- Basic CSV output format
- No real-time visualization
- Memory overhead proportional to tracked pages

## 📊 Performance Considerations

### Optimization Tips
1. Use compiler optimizations: `-O2` or `-O3`
2. Consider sampling instead of full tracing
3. Use bit arrays for dense access patterns
4. Implement circular buffer for streaming

### Memory Usage
- Static allocation: 4KB for tracking structure
- Dynamic allocation: 1MB test buffer
- Total: ~1MB + overhead

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch
3. Add tests for new functionality
4. Submit a pull request

## 📄 License

Educational use - See LICENSE for details

## 👨‍💻 Author

**Bala Andegue**
- GitHub: [BalaAndegue](https://github.com/BalaAndegue)
- Project: [Memory Tracer](https://github.com/BalaAndegue/memory_tracer)

## 📚 Further Reading

- "Computer Architecture: A Quantitative Approach" by Hennessy and Patterson
- "Understanding the Linux Virtual Memory Manager" by Mel Gorman
- Intel 64 and IA-32 Architectures Optimization Reference Manual

---

**Educational Tool**: This tracer is designed for learning and experimentation. For production profiling, consider using dedicated tools like `perf`, `valgrind`, or Intel VTune.