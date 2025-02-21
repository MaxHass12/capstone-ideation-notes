# 1. Run `docker compose up` to start Apache Kafka.

# 2.1 Run `docker exec -it kafka_broker kafka-topics --create --topic test-topic --bootstrap-server localhost:9092 --partitions 1 --replication-factor 1` to create a "test topic"

# 2.2 Run `docker exec -it kafka_broker kafka-topics --list --bootstrap-server localhost:9092` to check the "test topic" or reference the "kafka broker"

# 3. `npm init`, `npm install kafkajs` (NODE_VERSION = 22.12.0)
