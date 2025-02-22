- Concurrency is employed to design atomic units of work that can be executed independently from one another, enabling them to be executed at same time.

- In order to receive computational time in the CPU, threads rely on **OS scheduler**. It decided which process or thread runs next.

- In the common Ruby, threads enable concurrency but do not run in parallel because of Global Interpretor Lock (GIL).

- Due to GIL, only 1 thread executes Ruby bytecode. However, the impact of this varies depending on whether the time is **I/O-bound** or **CPU-bound**.

- An I/O bound task is one where program spends most of the time waiting for external resources like File I/O, Network Request, Database Requests, etc.

  - When a thread performs a I/O action, the GIL is released.
  - While one thread is waiting for I/O to complete, another thread can execute.
  - This allows Ruby to efficiently concurrently handle I/O-bound task.

- A CPU-bound task is one where program spends most of its time performing computations and needs continuous 'CPU cycles' like complex mathematical calculations, image processing, and Data compression.

  - For CPU-bound tasks even if we create multiple threads, only 1 thread can run at a time. CPU-bound tasks still execute serially, offering no performance gain.
  - [A CPU cycle is smallest unit of time in which a CPU can process an instruction]

- In multithreading, thread safety issues arise. There can be race conditions if multiple threads are reading and writing from the same variable. In the context of Workerholic, jobs should be thread-safe. If there is no guarantee that jobs are not thread safe, then we should only use 1 worker.

- Concurrency alone is good enough for IO bound jobs. How do we maximize processing throughput for CPU bound jobs ?

- Parallelism refers to true multitasking - ie multiple cores handling different tasks in parallel. While in Concurrency, multitasking can be achieved by a single core switching context.

- One way to achieve parallelism is by running multiple processes in parallel.
