const { Kafka } = require('kafkajs');

const kafka = new Kafka({
  clientId: 'consumer-2',
  brokers: ['localhost:9092', 'localhost:9093'],
});

const consumer = kafka.consumer({ groupId: 'group-high' });
const admin = kafka.admin();

const getPartitionBroker = async (partition) => {
  await admin.connect();
  const metadata = await admin.fetchTopicMetadata({
    topics: ['random-numbers'],
  });
  await admin.disconnect();

  const partitionInfo = metadata.topics[0].partitions.find(
    (p) => p.partitionId === partition
  );
  return partitionInfo ? partitionInfo.leader : 'Unknown';
};

const consumeMessages = async () => {
  await consumer.connect();
  await consumer.subscribe({ topic: 'random-numbers', fromBeginning: true });

  await consumer.run({
    eachMessage: async ({ topic, partition, message }) => {
      const value = parseFloat(message.value.toString());
      if (value >= 0.5) {
        const broker = await getPartitionBroker(partition);
        console.log(
          `${message.offset} | Consumer 2 received: ${value} | Partition: ${partition} | Broker: ${broker} |  Key: ${message.key}`
        );
      }
    },
  });
};

consumeMessages();
