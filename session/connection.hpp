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
            socket_.read_some(boost::asio::buffer(buf), std::bind(&connection::read_handler, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
        }
    }

private:

    boost::asio::ip::tcp::socket socket_;
    struct read_buf {
        void resize() {
            data = (unsigned char*)std::realloc((void*)data, size * 2);
            size *= 2
        }

        unsigned char* data;
        std::size_t vernier;
        size_t size; 
    }
};

} // namespace myrpc
} // namespace session

#endif
