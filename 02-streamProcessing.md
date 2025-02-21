# 1. Apache Kafka

- It is a **distributed event streaming platform** for high-throughput, fault tolerant and scalable real-time data analysis.

It is used for:

1. Event-driven Architecture : Enables microservices to communicate asynchronously via event streams.
2. Real-Time Data Pipelines : Acts as a buffer between data producers (logs, IoT devices) and consumers (eg database analytics)
3. Message Queuing and Pub/Sub : Provides durable messaging with high availability, similar to traditional message brokers.
4. Log Aggregation : Collects and processes logs in a distrbuted system.
5. Monitoring and Metrics Processing
6. Fraud Detection and Security Analytics
7. Streamings Analytics

- Distributed nature of Kafka comes from the fact that it is a cluster of server (called brokers) which register different topics (event types) and divide different topics into partitions which belong to a broker.

# 2.

## 2.1 Kafka Broker

Kafka Broker is a server in "Kafka Cluster" that receives, stores and serves message.

A Kafka Cluster consists of multiple brokers to ensure scalability, fault tolerance and load balancing.

Each Cluster can handle multiple **topics** and their **partitions**.

[ Broakers communicate with Apache Zookeeper to manage leader elections and configurations ]

## 2.2 Kafka Topic

A **topic** is a logical name given for a stream of messages in Kafka. They help categorize messages in Kafka. Producers and consumers can send and listen to multiple topics.

## 2.3 Partition

A **partition** is a subdivision of a **topic** which allows Kafka to scale horizontally. Partitions are distributed across broakers for load balancing and fault tolerance

Messages inside a partition are **stricly ordered**. Kafka does not guarantee order cross **partitions**.

## 2.4 Offset

- Offset are sequential numbers assigned to messages within a partition. Consumers track offsets to know which messages they have already processed.

## How everything works together

1. Producers sends messages with a topic.
2. That message is send to a partition uniquely determined by the message's key. Only 1 message with a given key can exist.
3. A partition is stored in a unique broker (unless a broker fails or a reassignment happens)
4. Each message is assigned a unique offset within its partition
5. Consumer reads these messages with all the metadata.

# 3. Key Features of Kafka

Kafka does not have a fixed queue size like traditional message queues. Its capacity depends on disk, memory, network config and broker config.

## 3.1 Parition Based Scalability

Each partition acts as a separate log and can handle message independently. More paritions increase concurrency as multiple consumers can read in paralle.

## 3.2 Message Retention and Log Segments

Kafka does not block producers when consumers lag.

Messages are retained based on time (eg 7 days) or size (10 GB per partition). Messages are NOT deleted on consumer reads.

If storage is exhausted, old messages are deleted.

## 3.3 Broker and Cluster Limits

A single broker can handle hundreds of thousands of messages per second with SSD

## So, when is Kafka Full?

Basically when the physical limits (storage, etc) of the host machine is reached.

# 4. Drawbacks of Kafka

## 4.1 Complexity in Setup and Maintenance

Requires careful broker, partition and replication configuration. Requires tuning in case of high throughput.

## 4.2 High Resource Consumption

Since Kafka allows multiple consumers to read the same message, Kafka does not delete messages after consumer reads. Instead messages are delete based on the retention policy ie a configured duration.
