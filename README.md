# Multi-Threaded Large File Processor

## Description
This application processes a large file containing integer numbers using multiple threads.
Each thread processes a separate section of the file, extracts unique numbers, and stores them in a global set.

## Algorithm

### Divide the File into Sections
- Get the total file size using `seekg()` and `tellg()`.
- Divide the file into equal sections based on the number of threads.
- Each thread is assigned a specific byte range.

### Start Multiple Threads
- Spawn threads and assign each one a `start_position` and `end_position` in the file.
- Each thread uses `seekg(start_position)` to jump to its section.

### Ensure Thread-Safe Reading
- Each thread reads its section **number by number**.
- If a thread **lands in the middle of a number**, it adjusts its start position to the **next valid number**.

### Extract Unique Numbers from Each Section
- Each thread maintains a **local set** for unique numbers in its section.
- If the number is already in the **local set**, it is ignored.

### Update the Global Unique Number Set (Thread-Safe)
- Each thread **locks a `std::mutex`** before updating the **global set**.
- It inserts numbers from the **local set** into the **global set**.

### Join Threads and Print Results
- Wait for all threads to finish (`join()`).
- Print the final **unique number list** from the global set.

## Usage
### **Build the Application** 
```sh
mkdir build && cd build
cmake ..
make
```

### **Run the Application** 
```sh
./large_file_processor <filename>

```
