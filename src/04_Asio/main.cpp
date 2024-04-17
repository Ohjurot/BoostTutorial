#include <boost/asio.hpp>

#include <string>
#include <string_view>
#include <iostream>

const boost::asio::ip::udp::endpoint SERVER_ENDPOINT
(
    boost::asio::ip::address::from_string("127.0.0.1"),
    5000
);

void Server()
{
    using namespace boost::asio;
    
    io_context ctx;

    ip::udp::socket serverSocket(ctx, SERVER_ENDPOINT);

    char data[1024];
    serverSocket.async_receive(
        buffer(data, 1024), 
        [&](std::error_code ec, size_t bytesRecived)
        {
            if (!ec && bytesRecived > 0)
            {
                std::cout << "RCV: " << std::string_view(data, bytesRecived) << std::endl;
            }
            else
            {
                std::cout << "ERROR! " << ec.message()  << std::endl;
            }
        }
    );

    ctx.run();
}

void Client()
{
    using namespace boost::asio;

    io_context ctx;

    ip::udp::socket clientSocket(ctx, ip::udp::endpoint(ip::udp::v4(), 0));

    std::string message = "Hello World!";
    clientSocket.async_send_to(
        buffer(message.data(), message.size()), SERVER_ENDPOINT,
        [](std::error_code ec, size_t sendBytes)
        {
            if (!ec && sendBytes > 0)
            {
                std::cout << sendBytes << " Bytes send successfully!" << std::endl;
            }
            else
            {
                std::cout << "ERROR! " << ec.message() << std::endl;
            }
        }
    );

    ctx.run();
}

int main(int argc, char** argv)
{
    if (argc == 2)
    {
        std::string appName = argv[1];
        if (appName == "server")
        {
            Server();
            return 0;
        }
        else if (appName == "client")
        {
            Client();
            return 0;
        }
    }

    std::cout << "Usage: 04_Asio [server/client]" << std::endl;
}
