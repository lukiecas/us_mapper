#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <sys/socket.h>
#include <boost/asio.hpp>
#include <map>
#include<string>
std::map<int, std::list<int>> dots;
int i = 0;
void serialPortReader() {
    std::list<int> dotValues;
    boost::asio::io_service io;
    char c;
    std::string x;
    boost::asio::serial_port serial(io, "/dev/ttyACM0");
    
    serial.set_option(boost::asio::serial_port_base::baud_rate(9600));
    while(true) {
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
            int angleInt = std::stoi(angle);
            int distanceInt = std::stoi(distance);

            dotValues.push_back(angleInt);
            dotValues.push_back(distanceInt);

            dots.insert({i, dotValues});

            dotValues.clear();
            i += 1;
            x = "";
            

            
        } else {

            x = x + ch;
        }

    }
    
}
int main() {
    sf::RenderWindow window(
        sf::VideoMode(640, 480),
        "testing");
    sf::View view(sf::FloatRect(0, 0, 6400, 4800));
    float viewCenter_x = 6400 / 2;
    float viewCenter_y = 4800 / 2;
    sf::CircleShape circle(10);
    sf::RectangleShape rectangle(sf::Vector2f(200.f, 100.f));
    rectangle.setPosition(640.f / 2, + 480.f / 2);
    rectangle.setFillColor(sf::Color::Red);
    sf::Mouse mouse;
    sf::Vector2i mPos_old;
    sf::Keyboard keyboard;
    
    while(window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

        if (mouse.isButtonPressed(mouse.Left)) {
            float dMouseMovement_x = mouse.getPosition(window).x - mPos_old.x;
            float dMouseMovement_y = mouse.getPosition(window).y - mPos_old.y;
            viewCenter_x = viewCenter_x - dMouseMovement_x;
            viewCenter_y = viewCenter_y - dMouseMovement_y;
            view.setCenter(viewCenter_x, viewCenter_y);

        }
        if (mouse.isButtonPressed(mouse.Right)) {
            circle.setFillColor(sf::Color::Black);
        }
        if(keyboard.isKeyPressed(sf::Keyboard::A)) {
            view.setCenter(640.f / 2.f, 480.f / 2.f);
        }
        if(event.type == sf::Event::MouseWheelScrolled) {
            if (event.mouseWheelScroll.delta < 0) {
                view.zoom(1.1f);
            }
            if (event.mouseWheelScroll.delta > 0) {
                view.zoom(0.9f);
            }
        }
        
        
        if(mouse.isButtonPressed(mouse.Left) == 1) {
            std::cout << "Left mouse button has been clicked" << std::endl;
        }
        window.setView(view);
        for(int j = 0; j == i; j++) {
            
        }
        window.display();
        mPos_old = mouse.getPosition(window);
        }
    }

    return 0;
}