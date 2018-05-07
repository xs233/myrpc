#ifndef __CONNECTION_HPP__
#define __CONNECTION_HPP__

#include <array>
#include <functional>
#include <boost/asio.hpp>

namespace myrpc {
namespace session {

class connection : public std::enable_shared_from_this<connection> {
public:
    connection(boost::asio::io_service& io_service) : socket_(io_service) {}
    ~connection() {}
    void read() {
        while (true) {
            std::array<char*, 1024> buf;
            socket_.async_read_some(boost::asio::buffer(buf), std::bind(&connection::read_handler, enable_shared_from_this(), std::placeholders::_1, std::placeholders::_2));
        }
    }

private:
    void read_handler(const boost::system::error_code& ec, std::size_t bytes_transferred) {

    }

    boost::asio::ip::tcp::socket socket_;
};

} // namespace myrpc
} // namespace session

#endif
