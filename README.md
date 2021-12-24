#  Embedded Operating Systems Assignments

### This repository contains day wise assignments from cdac-hyderabad embedded operating   systems   class

*   **Day-1**

    proc file details and uname commands.

*   **Day-2**

    *   proc file details and uname commands on raspberrypi and gnu tools like makefile,objdump.

*   **Day-3**
    *   static and dynamic libraries, fork(process id's )
    *   Assignments
        *   create static and dynamic libraries

*   **Day-4**
    *   library call vs syscalls 
    *   Assignments
        *   copying file using system calls

*   **Processes**
    *   fork   
    *   InterProcessCommunication
        *   Pipes
        *   Named Pipes (mkfifo command)
        *   shared memories
        *   message queues

    *   Assignments
        *   Addition of two numbers  and printing result using pipes
        *   creating a shell(like bash shell) using fork and exec API's


*   **Threads**
    *   context switching(between processes)
    *   threads basics
    *   Assignments
        *   create two threads hello & bye

*   **synchronization**
    *   mutexes
        *   Fast Mutex(Futex)
        *   Recursive Mutex
        *   Adaptive Mutex
        *   ErrorCheck Mutex
    *   semaphores
        *   Binary Semaphores
            *   Mutual Exclusion Semaphores
            *   signalling
        *   Counting semaphores
        *   Barriers
        *   Assignments
            *   given 4 arrays of 2 integers which is a resource pool create following API's
            *   get_buffer api should give pointer to integer array which is available
            *   release_buffer  should release  integer array

*   **exam**
    *   4 question 4 folders.
    *   outer folder has Make file which can be used as shown below
    *   executables are created in problem folders

    *   exam_questions branch consists of 4 problems
        1. Open the file /usr/share/dictionary.txt in process P1 and send the strings starting with letter 'm' to process P2 using message queues. In process P2 find and print the length of string
        
            ```bash
            make prob1
            ```
            *   generates proc_sender,proc_receiver executables

        2. Open the file /usr/share/dictionary.txt in process P1 and send the strings starting with letter 'm' to process P2 using share memory. In process P2 find and print the length of string.
            ```bash
            make prob2
            ```
            *   generates consumer1,producer1 executables

            *   Few issues till now

                - [ ] Run the consumer executable first then producer1

                - [ ] consumer to close connection we have send "quit" but this is not working

        3. Open the file /usr/share/dictionary.txt in process P1 which is a parent. Create two child process using fork. Child 1 searches for a word from the top of the file and child 2 search from bottom of the file. The word is provided by parent Process. Whichever child finds it prints the message "Found"
            ```bash
            make prob3
            ```
            *   generates question3 executables

            *   Few issues till now

                - [ ]   Both of them are running until they find or exhaust

                - [ ]   And also reading data by pushing strings into array instead of file

        4. Open the file /usr/share/dictionary.txt in process P1 and send the strings starting with letter 'm' to process P2 using pipes. In process P2 find and print the length of string.
            ```bash
            make prob4
            ```
            *  generates process1,process2 executables

            *   Few issues till now

                - [ ] Few of the strings are missing

                

