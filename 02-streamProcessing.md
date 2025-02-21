# 1. Apache Kafka

It is a **distributed event store** and **stream processing platform**.

**Distributed** nature of Kafka comes from the fact that it is a cluster of servers (called brokers) instead of a monolith.

Producer sends events to Kafka > Kafka stores the events durably > Consumers pulls event from Kafka > Consumer processes the events

It is used for:

1. Event-driven Architecture : Enables microservices to communicate asynchronously via event streams.
2. Real-Time Data Pipelines : Acts as a buffer between data producers (logs, IoT devices) and consumers (eg database analytics)
3. Message Queuing and Pub/Sub : Provides durable messaging with high availability, similar to traditional message brokers.
4. Log Aggregation : Collects and processes logs in a distrbuted system.
5. Monitoring and Metrics Processing
6. Fraud Detection and Security Analytics
7. Streamings Analytics

# 2. Kafka Architecture

Major components of Kafka Architecture are **Broker** and **Partition**

Logical Concepts through which messages are ordered, categorized and delievered are **Topic** and **Offset**.

## How everything works together

1. Producers sends messages with a **topic** (general identifier) and a key (unique identifer)
2. That message is send to a **partition** uniquely determined by the message's key. Only 1 message with a given key can exist.
3. A partition is assigned to a **broker** (unless a broker fails or a reassignment happens). This assignment happens at the start and does not change at runtime unless configured.
4. Each message is assigned a unique **offset** within its partition.
5. Consumer reads these messages with all the metadata.

## 2.1 Kafka Topic

A **topic** is a logical name given for a stream of messages in Kafka. They help categorize messages in Kafka. Producers and consumers can send and listen to multiple topics

## 2.2 Partition

A **partition** is the fundamental unit in Kafka allows Kafka to scale horizontally.

Producers can send messages to different partitions and consumers can read from multiple consumers providing parallelism.

Messages inside a partition are **stricly ordered**. Kafka does not guarantee order cross **partitions**.

## 2.3 Kafka Broker

Kafka Broker is a server in "Kafka Cluster" that receives, stores and serves message.

A Kafka Cluster consists of multiple brokers to ensure redundancy, fault tolerance and load balancing.

When we say partition is assigned to a broker, we mean that particular is broker is the leader for that partitions. Other brokers maintain copy of all the data in the leader-follower replications strategy.

[ASIDE: Broakers communicate with Apache Zookeeper to manage leader elections and configurations ]

## 2.4 Offset

Offset are sequential numbers assigned to messages within a partition. Consumers track offsets to know which messages they have already processed.

# 3. Key Features of Kafka

Kafka does not have a fixed queue size like traditional message queues. Its capacity depends on disk, memory, network config and broker config.

## 3.1 Parition Based Scalability

Each partition acts as a separate log and can handle message independently.

Each producer can send message to different partition and multiple consumers can read from multiple partitions in parallel.

More paritions increase concurrency as multiple consumers can read in parallel.

Note that adding more brokers does not automatically provide scalability. Say we have 3 partition but 5 brokers, then Kafka wont use the extra brokers until we increase the partitions.

## 3.2 Broker provide Redundancy

Each partition has 1 Leader Replica that resides on a single broker and multiple follower replicas on different broker.

Brokers in Kafka provide redundancy, fault tolerance and load distribution rather than scalability.

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

Since Kafka allows multiple consumers to read the same message, Kafka does not delete messages after consumer reads. Instead messages are delete based on the retention policy ie a configured duration. This means high storage requirements.

Quick ballpark calculation:

Say we retain message for 7 days. We have 10 partitions, with each partition replicated across 3 followers - then kafka stores 3 times the data.

Assume we produce 1KB message @ 100,000 message per second.

- `Per second: 100,000 * 1KB = 100 MB`
- `Per hour: 100MB * 3600 = 360GB`
- `Per day: 360GB * 24 = 8.64TB`
- `With replication factor 3: 8.64TB * 3 = 25.92TB/day`

Companies have to provide massive SSD for Kafka.

Also Kafka needs at least 8GB Ram per broker, not unusual to have 32GB plus RAM per broker.

## 4.3 Message ordering only guaranteed in partition

If a topic has multiple partitions, consumers can receive events out of order.

## 4.4 Not a True Global pub / sub

- No Built In Cross-Region Replication. Kafka does not automatically replicated data across Geographically Distributed Data Centers.

- Partitioning limits Global Ordering. Messages are ordered within a partition, not globally across the entire topic. In a strict true global pub/sub system (ie Google Pub/Sub), messages are strictly ordered across distributed regions.

- Kafka Consumers must poll for new messages, rather than having messages pushed to them in real time. True pub/sub system (Redis Stream) push messages to subscribers when they arrive. Kafka is not strict real time.

- Kafka routes messages based on topic keys, but does not support complex routing (eg fanout, wildcard processing, or per-message filtering ). True pub/sub systems allow message filtering and directed event routing to specific consumer.

- Kafka excels in high-throughput event streaming but struggles with real-time message delievery across global consumers.

## 4.5 No Built In Message Processing

Kafka is just a message broker. Message processing is done by consumers.

## 4.6 Not Ideal For Small Messages and Low Throughput

In short, Kafka works well for Event Driven Architecture but not so if the requirements are multi-region, real-time and fine-grained event delievery
