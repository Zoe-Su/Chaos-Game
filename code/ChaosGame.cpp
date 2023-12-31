// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
    // Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game!!", Style::Default);

    vector<Vector2f> vertices;
    vector<Vector2f> points;

    // Load font
    Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        cout << "Error loading font";
    }   

    // Setup text object
    Text text;
    text.setFont(font);
    text.setString("Click four dots to make a square. Click for a fifth dot to start the chaos game!!");

	while (window.isOpen())
	{
        /*
		****************************************
		Handle the players input
		****************************************
		*/
        Event event;
		while (window.pollEvent(event))
		{
            if (event.type == Event::Closed)
            {
				// Quit the game when the window is closed
				window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "the left button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                    if(vertices.size() < 4)
                    {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                    else if(points.size() == 0)
                    {
                        ///fourth click
                        ///push back to points vector
                        points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                }
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
        /*
		****************************************
		Update
		****************************************
		*/

        if(points.size() > 0)
        {
            ///generate more point(s)
            ///select random vertex
            ///calculate midpoint between random vertex and the last point in the vector
            ///push back the newly generated coord.
            srand(time(0));
            Vector2f currentVertex;
            for (int i = 0; i < 2000; i++)
            {
                int randomPos = rand() % vertices.size();
                Vector2f randomVertex = vertices[randomPos];
                if (randomVertex != currentVertex)
                {
                Vector2f midpoint((randomVertex.x + points.back().x)/2, (randomVertex.y + points.back().y)/2);
                points.push_back(midpoint);
                currentVertex = randomVertex;
                }
            }
        }

        /*
		****************************************
		Draw
		****************************************
		*/
        window.clear();

        // Display text object
        window.draw(text);
        for(int i = 0; i < vertices.size(); i++)
        {
            RectangleShape rect(Vector2f(10,10));
            rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
            rect.setFillColor(Color::Blue);
            window.draw(rect);
        }

        // Draw all points
        for (int i = 0; i < points.size(); i++)
        {
            if (i%2 ==1){
            CircleShape point(2);
            point.setPosition(points[i]);
            point.setFillColor(Color::Blue);
            window.draw(point);
            }
            else {
            CircleShape point(2);
            point.setPosition(points[i]);
            point.setFillColor(Color::White);
            window.draw(point);
            }
        }
        window.display();
    }
}