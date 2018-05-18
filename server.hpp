#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include "session/connection.hpp"

using boost::asio::ip::tcp;

namespace server {

class server {
public:
    server(boost::asio::io_service& io_service, int port) : acceptor_(io_service, tcp::endpoint(tcp::v4(), port)) {}
    ~server() {}
    void start() {
        auto new_connection = connection::create(acceptor_.get_executor().context());
        acceptor_.async_accept(new_connection->socket(), std::bind(&server::accept_handler, this, new_connection, std::placeholders::_1));
    }

private:
    void accept_handler(std::shared_ptr<tcp_connection> new_connection, const boost::system::error_code& error) {
        if (error) {
            throw boost::system::system_error(error);
         } else {
            new_connection->read();
        }
        start();
    }

    tcp::acceptor acceptor_;

};

} // namespace server

#endif