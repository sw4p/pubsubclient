/*
 Basic MQTT example

 This sketch demonstrates the basic capabilities of the library.
 It connects to an MQTT server then:
  - publishes "hello world" to the topic "outTopic"
  - subscribes to the topic "inTopic", printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary

 It will reconnect to the server if the connection is lost using a blocking
 reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
 achieve the same result without blocking the main loop.
 
*/
#include <PubSubClient.h>
#include <SoftwareSerial.h>

// Update these with values suitable for your network.
const char server[] = "server_name";
uint16_t port = 8080;

SoftwareSerial mySerial(8, 7);  // Rx | Tx
GSM_Client gsmClient(mySerial);
PubSubClient client(gsmClient);

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("arduinoClient")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("test","hello world");
      // ... and resubscribe
     // client.subscribe("test");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

//byte publish_str[] = {0x30, 0x10, 0x00, 0x04, 0x74, 0x65, 0x73, 0x74, 0x68, 0x65, 0x6C, 0x6C, 0x6F, 0x77, 0x6F, 0x72, 0x6C, 0x64, 0x1A};
void setup()
{
  Serial.begin(9600);
  delay(1000);
  mySerial.begin(9600);
  delay(1000);
  client.setServer(server, port);
//  client.setCallback(callback);
  client.disconnect();
  if (!client.connected()) {
    client.connect("client_id", "user_name", "password");
      //Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("topic","payload");
//      gsmClient.write(publish_str, sizeof(publish_str));
      // ... and resubscribe
     // client.subscribe("test");
  }

  // Allow the hardware to sort itself out
  delay(1500);
}

void loop()
{
  //client.loop();
}