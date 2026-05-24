Description

This project is about players using a shared PlayStation console. It uses multithreading in C to make it work.

It is divided into two parts:

Exercise 1**: Making and running threads at the time without controlling them

Exercise 2**: Controlling threads using semaphores so only some players can use the PlayStation

---

Exercise 1

- We make 16 threads for this:

8 Threads for Football players

4 Threads for Super Mario players

4 Threads for Need for Speed players

- Each thread does these things:

Prints a message saying it is waiting

Waits for 1 to 3 seconds

Prints a message saying it is done

---

Exercise 2

- Threads are like players competing to use the shared PlayStation

- There are some rules:

One game can be played at a time

Many players can play if they play the same game

We can only have so many players for each game:

. Football can have 4 players

. Super Mario can have 2 players

. Need for Speed can have 1 player

- We use semaphores to control the threads:

`Mutex` helps protect the things we are sharing

`Ps` controls who can use the PlayStation

`F_sem` `sm_sem` `nfs_sem` limit how many players can play each game

---

Compilation

```bash

gcc main.c exercise1/ex1.c exercise2/ex2.c -o, tp -lpthread

```