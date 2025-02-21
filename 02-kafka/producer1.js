const { Kafka } = require('kafkajs');

const kafka = new Kafka({
  clientId: 'producer-1',
  brokers: ['localhost:9092', 'localhost:9093'],
});

const producer = kafka.producer();
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

const produceMessages = async () => {
  await producer.connect();
  console.log('✅ Producer 1 connected');

  const sendMessage = async () => {
    const value = Math.floor(Math.random() * 1000) / 1000;

    // Send message and get partition
    const [response] = await producer.send({
      topic: 'random-numbers',
      messages: [{ key: `p1 ${value}`, value: value.toString() }],
    });

    // Fetch broker (leader of partition)
    const broker = await getPartitionBroker(response.partition);

    console.log(
      `📤 Producer 1 sent: ${value} | Partition: ${response.partition} | Broker: ${broker}`
    );

    // Schedule next message at a random interval
    const delay = Math.floor(Math.random() * 1500) + 500;
    setTimeout(sendMessage, delay);
  };

  sendMessage();
};

produceMessages();
