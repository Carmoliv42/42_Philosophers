*This project has been created as part of the 42 curriculum by `carmoliv`.*

# 42 Philosophers

## Description

This project is a simple C version of the classic Dining Philosophers problem.

Each philosopher runs in its own thread and keeps thinking, eating, and sleeping.
Forks are protected with mutexes, and a monitor thread checks if someone dies or if the simulation can stop because every philosopher ate enough times.

## Instructions

### Compilation

```sh
make
```

This builds the `philo` executable.

### Cleaning

```sh
make clean
make fclean
```

### Execution

```sh
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [must_eat]
```

Example:

```sh
./philo 5 800 200 200
./philo 4 410 200 200 3
```

### Arguments

- `number_of_philosophers`: how many philosophers are in the simulation.
- `time_to_die`: time in milliseconds before a philosopher dies without eating.
- `time_to_eat`: time in milliseconds spent eating.
- `time_to_sleep`: time in milliseconds spent sleeping.
- `must_eat` (optional): stop when every philosopher has eaten this many times.

## Resources

### References

- The Dining Philosophers problem
- Youtube videos philosophers dinner
- Mutex and thread basics in C

### AI usage

AI was used as a learning and development support tool throughout this project.
Understanding new concepts — AI was used to help understand mutex functions and their practical application in multithreaded programming, including how to properly use pthread_mutex_lock, pthread_mutex_unlock.
Simultaneous testing — AI assisted in designing and running concurrent test scenarios to validate thread behavior.