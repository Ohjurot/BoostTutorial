#include <boost/log/trivial.hpp>
#include <boost/asio.hpp>

int main()
{
    BOOST_LOG_TRIVIAL(error) << "Hello Boost!";

    boost::asio::io_context ctx;
}
