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
