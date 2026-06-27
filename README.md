# 42 Philosophers

This is my version of the classic Dining Philosophers project.

## What it does

The program creates one thread for each philosopher. They keep thinking, eating, and sleeping until someone dies or until every philosopher eats enough times, if that last argument is given.

Forks are handled with mutexes, and there is also a monitor thread that checks if a philosopher died.

## Build

```sh
make
```

This creates the `philo` executable.

To clean the project:

```sh
make clean
make fclean
```

## Run

```sh
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [must_eat]
```

Example:

```sh
./philo 5 800 200 200
./philo 4 410 200 200 3
```

## Arguments

- `number_of_philosophers`: how many philosophers there are.
- `time_to_die`: time in ms before a philosopher dies without eating.
- `time_to_eat`: time in ms spent eating.
- `time_to_sleep`: time in ms spent sleeping.
- `must_eat` (optional): stop when all philosophers have eaten this many times.

## Project files

- `main.c` - starts everything.
- `init.c` - sets up the data and mutexes.
- `routine.c` - philosopher loop.
- `actions.c` - eating and fork handling.
- `monitor.c` - checks for death and finish.
- `utils.c` - time and print helpers.
- `philo.h` - shared structs and prototypes.
- `Makefile` - build rules.

## Output

Lines look like this:

```text
<time> <philosopher_id> <action>
```

Example actions:

- `has taken a fork(right/lefth)`
- `is eating`
- `is sleeping`
- `is thinking`
- `died`

## Notes

- The code tries to avoid deadlocks by locking forks in a fixed order.
- If there is only one philosopher, they will take one fork and eventually die.
- The project uses `pthread`, so it needs a system with threads support.

Made by `carmoliv`.
