const { Kafka } = require('kafkajs');

const kafka = new Kafka({
  clientId: 'my-producer',
  brokers: ['localhost:9092'], // Ensure this matches your Kafka setup
});

const producer = kafka.producer();

const produceMessage = async () => {
  try {
    await producer.connect();
    console.log('✅ Producer connected to Kafka');

    await producer.send({
      topic: 'test-topic',
      messages: [{ key: 'key1', value: 'Hello Kafka!' }],
    });

    console.log('📨 Message sent successfully');
  } catch (error) {
    console.error('❌ Error sending message:', error);
  } finally {
    await producer.disconnect();
    console.log('🔌 Producer disconnected');
  }
};

produceMessage();
