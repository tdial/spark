While virtually every computer science curriculum includes at least one course on network programming, many of us do not find reason to study the subject in great detail after graduating. 

In this series of posts, I'll walk through building **Spark**, a simple web server, from scratch. We'll start with some basics, make mistakes along the way, and hopefully end up with something presentable.

**Why bother?**

After all, there are numerous libraries and frameworks available for developing network servers: **libevent**, which has gained tremendous popularity in recent years, and **libuv** which sits at the core of Node.js. 

Within "The Set" you have a choice of *(at least two that I know of)*   
TCP frameworks: the **market data tcp** stack that sits at the core of much of news, and the **fire** framework which supports Linux FDSA and several other projects.

With all these options, what's the point of diving into the guts of how they work? Well, if you're like me, you just *like* network programming. But there's another reason:

**It's Fundamental**

With the advent of so-called "micro-services" architectures, we are now living in a world where virtually *all* programs are *network* programs. The days of monolithic processes that run in batch mode are coming to an end. A solid understanding of the fundamentals of socket programming is bound to be helpful in your FactSet Career.

**Network Server Lifecycle**

Before we even begin to serve web pages, we need to understand the lifecycle of a network server program.  Each of the steps an be summarized neatly with the associated system call that performs the described duty. 

Here's an explanation of the typical lifecycle of a network server, described using the actual names of the system calls used to perform the various tasks. (System calls are in **bold**.)

1. **socket()** - Create a socket
2. **bind()** - Bind the socket to a particular network port
3. **listen()** - Establish the socket as a listener, waiting for new client connections.
4. **accept()** - Accept new client connections as they arrive
5. **close()** - Close sockets when they are no longer being used.

**Code**

Due to the ambitious nature of the project and the amount of code that will be written, I'm hosting this on Github. Check out the link below to see the current state of the project.  Right now, we're simply creating a TCP listener socket, waiting for clients, and closing them immediately.  

https://github.com/tdial/spark

**Next Up:**

In Part 2, we'll flesh out more of the example and try to get Spark to serve a web page. We'll also start to talk about the different ways that one can approach handling requests concurrently.
