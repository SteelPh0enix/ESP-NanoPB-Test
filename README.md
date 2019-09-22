# Simple ESP8266 test with Protocol Buffers using [nanopb](https://github.com/nanopb/nanopb) library

This is a basic example on how to use ESP8266 with Arduino framework and protocol buffers.

## Running/testing this program

This example is **protobuf server**. I've included [client script](test/scripts/client.py) written in Python 3 inside [`test/scripts`](test/scripts) directory. Everything should be pretty self-explanatory.

## Warnings and important notices

* If you want to have static-size and simple to parse structures, make sure to use (nanopb).max_size property in message fields. For example, take a look at [test.proto](proto/test.proto)

* Make sure you are following nanopb guide on *"how to generate `*.c`/`*.h` files"*. I'll shorten it quickly: **If you are using protoc from google protobuf release (which is my preferred method), make sure to include nanopb protoc plugin path in protoc command**. In my case, it was `protoc --plugin=protoc-gen-nanopb="E:/nanopb-0.3.9.3/generator/protoc-gen-nanopb.bat" --nanopb_out=.  test.proto` but, of course, your command might be different. Remember to use `protoc-gen-nanopb` on Linux, and `protoc-gen-nanopb.bat` on Windows.

So, basically, if something is wrong - consult nanopb docs.