#include <asio.hpp>
#include <asio/buffer.hpp>

#include <chrono>
#include <thread>
#include <iostream>

using namespace std;
using namespace asio;

int main(int argc, char const *argv[])
{
    asio::error_code ec;
    // Create a "context" - essentially the platform specific interface
    asio::io_context context;

    // Generate an `address` to the IP, we wish to connect
    const auto ip = asio::ip::make_address("127.0.0.1", ec);   // by default, it makes the make_address_v6(), it that gives an error, it will return make_address_v4()
    const auto PORT = 3000;

    // Create an endpoint, to the IP , with the PORT to connect
    asio::ip::tcp::endpoint endpoint( ip, PORT );   //for most http connections, port number is 

    //Create a socket; The `context` provides the implementation details
    asio::ip::tcp::socket socket(context);
    socket.connect( endpoint, ec ); //this just `creates the connection between server and client`
        //this yet has not made even a single request to the server (nor the server receives anything from it)

    asio::mutable_buffer buffer;
    if( !ec ){
        if( socket.is_open() ){
            string request = 
                "GET / HTTP/1.1\r\n"
                "HOST: localhost\r\n"
                "Connection: close\r\n\r\n";

            cout << request <<endl;

            buffer = asio::buffer( request );
            socket.write_some(buffer, ec);

            std::this_thread::sleep_for(2s);
            auto bytes = socket.available();
            cout << bytes << "bytes available\n";


            vector<char> temp(bytes);
            auto read_buffer = asio::buffer(temp.data(), bytes);
            socket.read_some(read_buffer, ec);
        }
    }



    cout << endpoint << endl<< ip << endl << ec << endl<< ec.message() << socket.max_connections << endl ;

    return 0;
}
