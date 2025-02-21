const { Kafka } = require('kafkajs');

const kafka = new Kafka({
  clientId: 'my-consumer',
  brokers: ['localhost:9092'], // Ensure this matches your Kafka setup
});

const consumer = kafka.consumer({ groupId: 'test-group' });

const consumeMessages = async () => {
  try {
    await consumer.connect();
    console.log('✅ Consumer connected to Kafka');

    await consumer.subscribe({ topic: 'test-topic', fromBeginning: true });

    await consumer.run({
      eachMessage: async ({ topic, partition, message }) => {
        console.log(`📩 Received message from ${topic} [${partition}]:`, {
          key: message.key ? message.key.toString() : null,
          value: message.value.toString(),
        });
      },
    });
  } catch (error) {
    console.error('❌ Error in consumer:', error);
  }
};

consumeMessages();
