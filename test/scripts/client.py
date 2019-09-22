import test_pb2
import sys
import socket

ESP_IP = "192.168.1.107"
ESP_PORT = 42069


def create_message(msg_type: int, msg_data: str) -> str:
    message = test_pb2.Info()
    message.type = msg_type
    message.data = msg_data
    return message.SerializeToString()


def send_message(msg_data: str) -> None:
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as esp_sock:
        esp_sock.connect((ESP_IP, ESP_PORT))
        esp_sock.send(msg_data)


if __name__ == '__main__':
    message_data = str()
    message_type = 0

    if len(sys.argv) == 2:
        message_data = sys.argv[1]
    elif len(sys.argv) == 3:
        message_data = sys.argv[1]
        try:
            message_type = int(sys.argv[2])
        except ValueError:
            print("Error: message type has to be number")
            exit(2)
    else:
        print("Usage: {0} message [type]".format(sys.argv[0]))
        exit(1)

    send_message(create_message(message_type, message_data))
