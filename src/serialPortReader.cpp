#include <iostream>
#include <boost/asio.hpp>
#include <list>
#include<string>
int serialPortReader() {
    boost::asio::io_service io;
    char c;
    std::string x;
    bool f = true;
    boost::asio::serial_port serial(io, "/dev/ttyACM0");
    
    serial.set_option(boost::asio::serial_port_base::baud_rate(9600));
    while(f) {
        boost::asio::read(serial, boost::asio::buffer(&c, 1));
        // std::cout << c;
        std::string ch(1, c);
        if(c == '\n') {
            
            x = x + ch;
            
            std::string angle = x.substr(0, x.find(','));
            int characterAmount = x.length() - 1 - x.find('\n');
            std::string distance = x.substr(x.find(',') + 1, characterAmount - 1);

            std::cout << "angle: " << angle << std::endl;
            std::cout << "distance:" << distance << std::endl;
            
            x = "";
            f = false;

            
        } else {

            x = x + ch;
        }

    }
    return 0;
}