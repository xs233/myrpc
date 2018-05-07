#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include "session/connection.hpp"

using boost::asio::ip::tcp;

namespace server {

class server {
public:
    server(boost::asio::io_service& io_service) : acceptor_(io_service) {}
    ~server() {}

private:
    tcp::acceptor acceptor_;

};

} // namespace server

#endif