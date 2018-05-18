#ifndef __CONNECTION_HPP__
#define __CONNECTION_HPP__

#include <functional>
#include <boost/asio.hpp>

namespace myrpc {
namespace session {

class connection : public std::enable_shared_from_this<connection> {
public:
    connection(boost::asio::io_service& io_service) : socket_(io_service) {}
    ~connection() {}
    boost::asio::ip::tcp::socket& socket() { return socket_; }
    static std::shared_ptr<connection> create(boost::asio::io_service& io_service) {
        return std::shared_ptr<connection>(new connection(io_service));
    }

    void read() {
        boost::system::error_code error;
        std::size_t len = socket_.read_some(boost::asio::buffer(&header_len_), error);
        if (error) {
            throw boost::system::system_error(error);
        } else {
            read_buf_.alloc_data(header_len_);
            while (true) {
                len = socket_.read_some(boost::asio::buffer(read_buf_.data + read_buf_.vernier), error);
                if (error) {
                    throw boost::system::system_error(error);
                } else {
                    read_buf_.vernier += len;
                    if (read_buf_.vernier == header_len_) {
                        break;
                    }
                }
            }
            // TODO: parse
            
        }
    }

private:
    // Define data buffer for socket read.
    struct read_buf {
        read_buf() : data(nullptr), vernier(0) {}
        ~read_buf() { delete[] data; }
        void alloc_data(std::size_t len) {
            data = new unsigned char[len];
        }

        unsigned char* data;
        std::size_t vernier;

    };

    std::size_t header_len_;
    boost::asio::ip::tcp::socket socket_;
    read_buf read_buf_;

};

} // namespace myrpc
} // namespace session

#endif
