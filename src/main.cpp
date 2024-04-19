#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <sys/socket.h>
#include <boost/asio.hpp>
#include <map>
#include <string>
#include <cmath>
#include <vector>
#include <thread>
float viewCenter_x = 640.f / 2.f;
float viewCenter_y = 480.f / 2.f;
std::list<sf::CircleShape> circles;
sf::RenderWindow window(
        sf::VideoMode(640, 480),
        "testing");
sf::View view(sf::FloatRect(0, 0, 640, 480));

void serialPortReader() {
    boost::asio::io_service io;
    char c;
    std::string x;
    boost::asio::serial_port serial(io, "/dev/ttyACM0");
    window.setView(view);

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
            
            
            int angleInt = std::stoi(angle);
            int distanceInt = std::stoi(distance);
            float angleRad = angleInt * (M_PI / 180);
            float distanceX = distanceInt * std::cos(angleRad);
            float distanceY = distanceInt * std::sin(angleRad);
            std::cout << "(" << viewCenter_x + distanceX << ";" << viewCenter_y + distanceY << ")" << std::endl;
            
            sf::CircleShape circle(1);
            circle.setPosition(viewCenter_x + distanceX, viewCenter_y + distanceY);
            if(circles.size() == 200) {
                circles.pop_front();
            }
            if(distanceInt < 450) {
                circles.push_back(circle);
            }
            
            x = "";
            

            
        } else {

            x = x + ch;
        }

    }
    
}
int main() {
    std::thread myThread(serialPortReader);
    window.setView(view);

    sf::RectangleShape rectangle(sf::Vector2f(200.f, 100.f));
    sf::Mouse mouse;
    sf::Vector2i mPos_old;
    sf::Keyboard keyboard;
    sf::CircleShape sonar(1);
    sonar.setFillColor(sf::Color::Red);
    sonar.setPosition(viewCenter_x, viewCenter_y);
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
        window.clear();
        window.setView(view);

        window.draw(sonar);
        for(sf::CircleShape circle : circles){
            window.draw(circle);
        }
        window.display();
        mPos_old = mouse.getPosition(window);
        }
    }

    return 0;
}