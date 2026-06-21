# 🍝 Philosophers

> *"One or more philosophers sit at a round table. There is a large bowl of spaghetti in the middle of the table."*

A multithreading project from [42 School](https://42.fr) implementing the classic **Dining Philosophers Problem** using threads and mutexes.

---

## 📚 About

The **Dining Philosophers** problem is a classic computer science problem used to illustrate synchronization issues and techniques for resolving them.

Each philosopher sits at a round table with a fork between each pair of adjacent philosophers. To eat, a philosopher needs **two forks** (left and right). The challenge is to design a solution that avoids:

- 🔒 **Deadlock** — all philosophers are waiting indefinitely
- ⚡ **Race conditions** — unsynchronized access to shared resources
- 💀 **Data races** — concurrent reads/writes to shared memory

---

## 🧠 Rules

- Philosophers alternately **think**, **eat**, and **sleep**
- While eating, a philosopher holds two forks and cannot share them
- A philosopher **dies** if they haven't started eating within `time_to_die` milliseconds
- Philosophers do **not communicate** with each other
- The simulation stops when a philosopher dies **or** all philosophers have eaten `n` times

---

## 🚀 Usage

### Compilation

```bash
make
```

### Run

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Arguments

| Argument | Description |
|---|---|
| `number_of_philosophers` | Number of philosophers (and forks) at the table |
| `time_to_die` (ms) | Time before a philosopher dies if they haven't eaten |
| `time_to_eat` (ms) | Time it takes for a philosopher to eat |
| `time_to_sleep` (ms) | Time a philosopher spends sleeping |
| `[number_of_times_each_philosopher_must_eat]` | *(Optional)* Simulation ends when all philosophers have eaten this many times |

### Examples

```bash
# 5 philosophers, no one should die
./philo 5 800 200 200

# 4 philosophers, each must eat at least 7 times
./philo 4 410 200 200 7

# 1 philosopher — will always die (only one fork)
./philo 1 800 200 200
```

### Key Design Choices

- **One thread per philosopher** — each philosopher runs in its own POSIX thread (`pthread_create`)
- **One mutex per fork** — prevents two philosophers from grabbing the same fork simultaneously
- **Monitor thread** — a dedicated thread continuously checks if any philosopher has died or if the meal count has been reached
- **Even/odd staggering** — even-numbered philosophers start thinking briefly to reduce contention and avoid deadlock

---

## 🛡️ Avoiding Deadlock

A naive implementation where every philosopher picks up their left fork first leads to a deadlock. This project avoids it by:

1. Making **even-indexed** philosophers pick up the right fork first
2. Introducing a **small delay** at the start for even philosophers
3. Using a **monitor thread** to stop the simulation as soon as a death is detected

---

## 📊 Logs

Each action is printed in the following format:

```
[timestamp_in_ms] [philosopher_id] [action]
```

Possible actions:
```
X ms    Y has taken a fork
X ms    Y is eating
X ms    Y is sleeping
X ms    Y is thinking
X ms    Y died
```

> ⚠️ A message should not be displayed after a philosopher dies.

---

## ✅ Testing

```bash
# Should not die
./philo 5 800 200 200
./philo 4 410 200 200
./philo 100 800 200 200

# Should die
./philo 1 800 200 200
./philo 4 310 200 100

# Should stop after N meals
./philo 5 800 200 200 7
./philo 4 410 200 200 10
```

You can also use tools like **valgrind** (with `--tool=helgrind`) to check for data races:

```bash
valgrind --tool=helgrind ./philo 4 410 200 200
```

---

## 👤 Author

| GitHub |
|--------|
| [@maxalwis](https://github.com/maxalwis) |
