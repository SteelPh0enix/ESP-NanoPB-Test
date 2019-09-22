#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <pb_decode.h>
#include <test.pb.h>
#include <cstdint>

constexpr std::uint16_t SERVER_PORT{42069};
constexpr std::size_t PROTOBUF_BUFFER_SIZE{128};

std::uint8_t protobufBuffer[PROTOBUF_BUFFER_SIZE]{};

WiFiServer server(SERVER_PORT);
WiFiClient client{};

void setup() {
  Serial.begin(115200);
  Serial.println();

  WiFi.begin("Piekarnia", "#72759802#");

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print('.');
  }
  Serial.println();

  server.begin();
  Serial.print("TCP Server started at ");
  Serial.print(WiFi.localIP());
  Serial.print(":");
  Serial.println(SERVER_PORT);
}

void loop() {
  client = server.available();
  if (client) {
    client.setTimeout(100);
    while (client.connected()) {
      if (client.available()) {
        client.readBytes(protobufBuffer, PROTOBUF_BUFFER_SIZE);

        Info message = Info_init_zero;
        auto input_stream =
            pb_istream_from_buffer(protobufBuffer, PROTOBUF_BUFFER_SIZE);
        auto status = pb_decode(&input_stream, Info_fields, &message);
        if (!status) {
          Serial.println("Decoding message has failed!");
        } else {
          Serial.print("[Message]<");
          Serial.print(message.type);
          Serial.print(">: ");
          Serial.println(message.data);
        }
      }
    }
  }
}