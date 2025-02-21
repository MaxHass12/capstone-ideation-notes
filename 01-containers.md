# 1. What are Containers

- Containers are **OS Level Abstraction** unlike VMs which are **hardware level abstraction**.

- Unlike VM which run an entire copy of the OS, containers share the Linux Kernel with the Host.

- As users, we can treat the container as a seperate isolated copy of an OS in which we can run our own programs isolated from other other programs in the system.

- Containers provide an efficient way to run isolated applications without the full overhead of the VM.

[ASIDE For Linux Nerds: Containers are mostly just an assembly of various Linux security features, like virtual file system, virtual network interfaces, chroots, virtual memory tricks, and the like, that together give the appearance of virtualization.
🤯

If anyone understands any of it then please let me know.]

# 2. Use Case

- Containers encapsulate the application and **all its dependencies** into a **single isolated passage**. As a result they are perfect for solving **dependency hell** - application working on one system and not on another. "Works On My Container" issue is impossible.

- As containers are relatively lightweight, compared to VMs, they are very easy to scale, enabling the software inside to run identically. Hence, ideal for a multitenant architecture to run multiple instances on a single VM.

- Ideal for running an automated task in a standardized setup like build system, dev environment, CI CD.

# 3. Docker

The most popular containerization technology is Docker.

## 3.1 Image and Container

Two related and confusing concepts in Docker are Image and Container.

**Image** is an immmutable file made of the software, dependencies and "OS" required to run it. An Image can be made in one system, then shipped to other system.

A **Container** is a runtime instance of image. We can think that image is a program, whereas container is a process running from that program which can be run identically in any system.

## 3.2 Docker Architecture

Docker is a set of products which allow us to manage images and containers.

Docker runs on the familiar client-server architecture with an RESTful API. It has

1. **Docker Daemon** is the background process which is responsible for running and managing container.

2. **Docker CLI** gives us the ability gives instructions to the `dockerd` via CLI. For eg `docker ps` lists all the containers.

3. **Docker API** The Docker CLI transaltes the commands in the familiar RESTful Requests and send them to the `dockerd` via HTTP.

   - Here `dockerd` acts as the server and Docker CLI acts as the client.

   - For eg In MacOS, `docker ps` is equivalent to the command `curl --unix-socket /var/run/docker.sock http://localhost/containers/json`.

   - Note that the above command is over HTTP but not over TCP. `--unix-socket /var/run/docker.sock` flag instructs `curl` to communicate via **Docker Unix Socket** instead of TCP network request.

   - `http://localhost/containers/json` this is the HTTP endpoint to list all containers.

# 4. Utilizing Docker API for building PAAS

Since Docker CLI to `dockerd` communication happens via RESTful APIs, a Docker CLI can as well conect to a **remote** Docker host.

This is how _Mothership_ used a custom Docker client to manage multiple app containers on a remote host.

# 5. Docker Orchestration
