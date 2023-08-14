# LinkedList-in-C

A linked list is a linear data structure composed of nodes where each node contains a value and a pointer to its next node. This particular way of managing information allows it to be stored in non-contiguous memory addresses, avoiding the need to restructure all the information to be stored linearly in memory.

Each node stores a certain value and a pointer to the memory address of its next node.

This repository will consist of recreating the different linked lists that exist:
  - Simply linked lists.
  - Double linked lists.
  - Circular lists.
  - Double circular lists.

Following this order the lists will be recreated.

The instructions for testing the lists will be the same for all lists.
Each list will contain three files:
  - main.c
  - linkedList.c
  - linkedList.h
The name of the files can change depending on the name of the linked list.

With these files in your possession, all you need to do is compile these files in C using the following command:
```c
gcc main.c -o linkedList
```

To run it you will need the following command:
```c
./linkedList
```
Simply linked list
![Imagen de ejemplo](images/SingleLinkedList.png)
