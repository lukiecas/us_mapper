#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
int main() {
    sf::RenderWindow window(
        sf::VideoMode(640, 480),
        "testing");
    
    sf::View view(sf::FloatRect(0, 0, 640, 480));
    float viewCenter_x = 640 / 2;
    float viewCenter_y = 480 / 2;
    sf::CircleShape circle(200);
    sf::RectangleShape rectangle(sf::Vector2f(200.f, 100.f));
    rectangle.setPosition(640.f / 2, + 480.f / 2);
    rectangle.setFillColor(sf::Color::Red);
    circle.setFillColor(sf::Color::Red);
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
        
        
        if(mouse.isButtonPressed(mouse.Left) == 1) {
            std::cout << "Left mouse button has been clicked" << std::endl;
        }
        window.setView(view);
        window.clear();
        window.draw(rectangle);
        // window.draw(circle);
        window.display();
        mPos_old = mouse.getPosition(window);
        }
    }

    return 0;
}