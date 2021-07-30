1. Open the file /usr/share/dictionary in process P1 and send the strings starting with letter 'm' to process P2 using message queues. In process P2 find and print the length of string. 


Algorithm
- 1. Open the said file using the **open** system call or **fopen** library call in process P1
- 2. Create a message queue in the Process P1
- 3. Read the file content line by line => if word starts with 'm' call **mq_send** with the given word

- 4. In the Process P2 Create a message queue with same attributes and name
- 5. Here call **mq_receive** repeatedly and print the output and its length as received inside a buffer