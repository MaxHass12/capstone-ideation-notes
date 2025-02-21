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

ASIDE: For a PAAS, provisioning a new VPS for each new app would be a significant waste of resource. Hence - Heroku, Render, Fly all use a multitenant PAAS architecture.

# 5. Docker Orchestration

Now, if we are running multiple app containers (2 app instances, 1 web server, 1 DB, 1 web server, 1 cache, etc) we need to coordinate them.

If all the docker containers are running on a single instance then we can coordinate them through the `docker compose` tool.

However, if the docker instances are running on multiple hosts then we need either **Docker Swarm** or **Kubernetes** to coordinate them

# 5.1 Docker Swarm

It is built into docker. It turns a pool of Docker hosts into a single virtual host. Its ideal for small user case (2-3 hosts for a hobby project)

# 5.2 Kubernetes

It is the default way of orchestrating containers in a large multi-host container.

The most common way to use K8 is by using a managed service by a cloud provider such as Google Kubernetes Engine or Amazon Elastic Kubernetes Services.

# 6. Docker Networking

Since Docker containers are isolated OS abstractions, they can only communicated through a network.

- `docker network ls` will give the list of all docker networks.

- `docker inspect <network_name>` gives the detail about a given docker network.

# 6.1 Default Bridge Network

This is the default network that the Docker creates when we install Docker.

We can think of this as a default internal Docker network (a virtual LAN) within which containers can communicate with each other but a container, by default, can not communicated with the outside network.

External network access requires **Port Mapping**

For example, the command `docker run -d --name mycontainer -p 8080:80 nginx` maps `8080` on the host to `80` on the container.

[Aside: A bridge network operates at level 2 ie transfers data through the physical MAC addresses rather than IP address. In a bridge network, a **network bridge** maintains a **MAC address table** and forwards packets accordingly. (In contrast, in the level 3 router based networking in which router consults the ARP table)]

# 6.2 Named Bridge Network

Same as the default Bridge Network, except that instead of Docker creating it be default - developers have to explicitly create it.

Also, within the named bridge network inter-container communication can happen by container's name instead of IP.

# 6.3 Host Network

In this the container binds directly the host's IP. Hence, there is no need to publish ports with `-p`.

The command `docker run -d --name mycontainer --network host nginx` listens directly on the host.

Inter container communication also happens via the host network.

# 6.4 Overlay Network

- An Overlay network is created to communicate between containers on multiple hosts in a Docker Swarm.

- Did not dig deep into it.

# Edamame Case Study

- Used K8 to orchestrate load testing of a server serving both HTTP and WebSocket protocol.
