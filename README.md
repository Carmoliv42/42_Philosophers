# 42 Philosophers (philo)

A small C implementation of the Dining Philosophers problem using pthreads and mutexes.

## Overview

This program simulates the classic concurrency problem "Dining Philosophers".
Each philosopher alternates between thinking, eating and sleeping. Forks are represented by mutexes. The program monitors philosophers for starvation and stops the simulation when a philosopher dies or when every philosopher has eaten the required number of times (if provided).

## Features

- Thread-per-philosopher implementation using `pthread`.
- Mutexes for forks, printing and meal/death control.
- Millisecond-precision timing and a responsive `smart_sleep` that checks for simulation end.
- Safe ordering when taking forks to avoid deadlocks.

## Files

- `main.c` - program entry, starts philosopher and monitor threads.
- `init.c` - initializes data structures and mutexes.
- `routine.c` - philosopher routine (think/eat/sleep).
- `actions.c` - fork-taking and eating logic.
- `monitor.c` - monitor thread that detects death or completion.
- `utils.c` - time helpers, printing, and smart sleeping.
- `philo.h` - shared types and function declarations.
- `Makefile` - build rules.

## Build

The project compiles with the included `Makefile`.

To build:

```sh
make
```

This produces an executable named `philo`.

To clean build artifacts:

```sh
make clean
make fclean   # removes the binary as well
```

## Usage

```sh
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philo_must_eat]
```

- `number_of_philosophers` (int): how many philosophers (and forks) to create.
- `time_to_die` (ms): if a philosopher doesn't start eating `time_to_die` ms after their last meal or the simulation start, they die.
- `time_to_eat` (ms): time a philosopher spends eating.
- `time_to_sleep` (ms): time a philosopher spends sleeping.
- `number_of_times_each_philo_must_eat` (optional int): when all philosophers have eaten at least this many times, the simulation stops.

Example:

```sh
./philo 5 800 200 200
./philo 4 410 200 200 3
```

## Output format

Each printed line has the form:

```
<timestamp_ms> <philosopher_id> <action>
```

Actions include:

- `has taken a fork` / `has taken a right fork` / `has taken a left fork`
- `is eating`
- `is sleeping`
- `is thinking`
- `died`

Timestamps are milliseconds since the simulation start.

## Behavior notes

- The implementation avoids simple deadlocks by ordering fork acquisition (the code selects which fork to lock first based on pointer comparison) and by staggering start times for even/odd philosophers.
- If only one philosopher is present, they will take the single fork and wait until they die (this is the expected behavior for the classic problem).
- The program exits with status `1` for invalid arguments or initialization failures, and `0` on normal termination.

## Requirements

- A POSIX-like system with `gcc`/`cc` and `make`.
- `pthread` support (the Makefile already adds `-pthread`).

## Author

Created by `carmoliv` (workspace: `Carmoliv42`).

If you want, I can update the README with examples of expected output for specific scenarios, add a license, or include notes about test cases used during development.
