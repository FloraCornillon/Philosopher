# Philosophers

This project is part of the curriculum at 42 school. The goal is to understand and solve the classic concurrency problem known as the "Dining Philosophers", using threads and mutexes in C.

You can find the project subject [here](./en.subject.pdf).

## Skill Practice

- **Multithreading** with `pthread`  
- **Race condition** prevention using mutexes  
- **Thread synchronization** and safe data sharing  
- **Deadlock avoidance** strategies  
- **Precise timing** and resource handling  
- Robust **error handling** and input validation  
- Clean and maintainable **code structure**

## How to Use

Clone the repository and compile the project:

```bash
git clone git@github.com:FloraCornillon/Philosopher.git
cd Philosophers
make
```

Run the program with the required arguments:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

Example:

```bash
./philo 5 800 200 200
```

This will simulate 5 philosophers who die if they don't eat within 800ms, eat for 200ms, and sleep for 200ms.

> The optional last argument allows you to stop the simulation once all philosophers have eaten that number of times.

## Notes

- The implementation uses only **POSIX threads** and **mutexes**, no semaphores.  
- The program aims to be **precise and efficient**, even under strict timing constraints.  
- Developed with a focus on **correctness, performance**, and **code clarity**.