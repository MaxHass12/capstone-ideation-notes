## 1. Tasks are sequential or not

- A **POSIX Thread** (or a Pthread) is a unit of execution within a process that follows the given POSIX standard for **multithreading**. It provides the API for creating, managing and synchronizing threads in a UNIX like system.

- A **thread** is the smallest unit of execution within a process. It has its own stack, but shares code, heap and global memory.

- **Multithreading** is the ability of a process to run multiple threads concurrently, enabling efficient parallel execution and resource sharing. For eg: A Web Browser uses multiple threads for Rendering web pages, downloading files in background, etc.

- Many programs require to do many things at once. Chat programs will need to read text and listen to user input at the same time, etc. Multithreading allows **several pieces of code to run in parallel**.

## 2. processes are not always the answer

- One way to make the computer do several things at once is through _processes_.

  - `fork()` creates a new **child process**
  - The child process is a duplicate of parent except for a unique process id.
  - `fork()` returns `0` in the child's process and child's pid in the parent process.
  - In a parent-child relationship, parent can `wait()` or `kill()` the child but apart from that child and parent runs independently of each other ie get their own stack and heap.
  - Since parent-child dont share memory, they communicate using `pipe()`, message queues, etc.

- Processes are not always the answer:

1. processes take time to create
2. processes dont share data easily as they are independent programs
3. plain difficult

## 3. simple processes do one thing at a time

- A major design principle of a program is do one thing and do it well. Simple processes do one thing only.

- One way to do multitasking with a simple process is to switch between tasks. But what if the operation is blocking.

## 4. use threads

- A multithreaded program is like a shop with several people working in it.

- All of the threads in a multithreaded program will have access to the same piece of memory. They will be able to read and write to same file and talk on the same network sockets.

## 5. thread safety

- Thread safety means that a piece of code can be safely executed from multiple threads concurrently without causing **race condition** or **data corruption**.

- **Race Condition** when multiple threads or processes access and modify shared data concurrently. Look out for multiple threads modifying the same variable ( Usually happens when the correct result depends on timing and interleaving of operations. )

- **Data Corruption** is when incorrect data is written due to a race condition (in this case)

- The above is solved by mutex, pure functions, etc.

## 6. locks

- `mutex` is a synchronization primitive that prevents multiple threads from accessing shared resource simultaneously.

How does it work?

1. A thread (thread-A) locks the mutex before accessing shared data.
2. Other threads trying to lock it must wait until it is unlocked.
3. thread-B unlocks the mutex after finishing its work.

Mutexes are sometimes called locks. These locks generally need to be global variables so that all threads can access them.

Even if the CPU has a single core, the OS will switch rapidly between the threads and make it appear that multiple things are running at once.

A condition of Deadlock can occur if 2 threads want both locks A and B. Thread 1 has lock A, and thread 2 has lock B - then they cant proceed.
