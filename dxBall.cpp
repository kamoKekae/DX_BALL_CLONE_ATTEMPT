#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "shapes.hpp"
#include <SFML/System.hpp>
#include <ctime>
#include <vector>


void drawObstacles(std::vector<obstacle>& obstacles, sf::RenderWindow& window){
    for(auto i : obstacles){
        window.draw(i);
    }
}

void fillObstacles(std::vector<obstacle> &obstacles){
    sf::Vector2<int> obsStartingPoint{400,30};
    sf::Vector2<int> obsStartingPoint1{365,30};
    sf::Vector2<int> obsStartingPoint2{435,30};
    sf::Vector2<int> obsStartingPoint3{470,30};
    sf::Vector2<int> obsStartingPoint4{330,30};
    sf::Vector2<int> obsStartingPoint5{295,30};
    
    
    for(int i =0;i<4;i++){
        const int width=35,height=35;
        obstacle myrect(obsStartingPoint.x,obsStartingPoint.y+height*i,width,height);
        myrect.setFillColor(sf::Color::Magenta);
        myrect.setOutlineThickness(-2);
        obstacles.push_back(myrect);
    }

    for(int i =0;i<4;i++){
        const int width=35,height=35;
        obstacle myrect(obsStartingPoint1.x,obsStartingPoint1.y+height*i,width,height);
        myrect.setFillColor(sf::Color::Magenta);
        myrect.setOutlineThickness(-2);
        obstacles.push_back(myrect);
    }

    for(int i =0;i<4;i++){
        const int width=35,height=35;
        obstacle myrect(obsStartingPoint2.x,obsStartingPoint2.y+height*i,width,height);
        myrect.setFillColor(sf::Color::Magenta);
        myrect.setOutlineThickness(-2);
        obstacles.push_back(myrect);
    }

    for(int i =0;i<4;i++){
        const int width=35,height=35;
        obstacle myrect(obsStartingPoint3.x,obsStartingPoint3.y+height*i,width,height);
        myrect.setFillColor(sf::Color::Magenta);
        myrect.setOutlineThickness(-2);
        obstacles.push_back(myrect);
    }

    for(int i =0;i<4;i++){
        const int width=35,height=35;
        obstacle myrect(obsStartingPoint4.x,obsStartingPoint4.y+height*i,width,height);
        myrect.setFillColor(sf::Color::Magenta);
        myrect.setOutlineThickness(-2);
        obstacles.push_back(myrect);
    }

    
    for(int i =0;i<4;i++){
        const int width=35,height=35;
        obstacle myrect(obsStartingPoint5.x,obsStartingPoint5.y+height*i,width,height);
        myrect.setFillColor(sf::Color::Magenta);
        myrect.setOutlineThickness(-2);
        obstacles.push_back(myrect);
    }
}

void drawGround(sf::RenderWindow &window,sf::Texture& picture){
    sf::Sprite sp(picture);
    sp.move(sf::Vector2f(1,1));
    sp.setColor(sf::Color::Cyan);
    window.draw(sp);
    return;
}

int main(){
    sf::RenderWindow window(sf::VideoMode(1024,768),"Kamo Window");

    if( !window.isOpen()){
        return EXIT_FAILURE;
    }
    
    sf::Texture picture;
    picture.loadFromFile("C:/Users/Kamogelo Kekae/Documents/fisiKs/ground (1).jpg");
    picture.setSmooth(true);
    
    
    std::vector<obstacle> obstacles;

    fillObstacles(obstacles);

   rectangle myrect(400,500,100,50);

   myrect.setFillColor(sf::Color::Black);
   myrect.setOutlineColor(sf::Color(30,40,230,255));
   myrect.setOutlineThickness(-3.f);

   circle myCircle(25,sf::Vector2f(200.f,500.f));
   myCircle.setFillColor(sf::Color::Blue);
   myCircle.setOutlineColor(sf::Color(80,80,80,15));
   myCircle.setOutlineThickness(2);
   myCircle.setOutlineColor(sf::Color::Black);


    while(window.isOpen()){
        sf::Event event;

        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
                exit(EXIT_SUCCESS);
            }
            else if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Left){
                    myrect.setPosition(myrect.getPosition().x - 15,myrect.getPosition().y);
                    if(myrect.getPosition().x >= 900){
                        myrect.setPosition(800,myrect.getPosition().y);
                    }
                    else if(myrect.getPosition().x<=0){
                        myrect.setPosition(0,myrect.getPosition().y);
                    }
                }
                
                    if(event.key.code == sf::Keyboard::Comma){
                        if(!obstacles.empty())
                            obstacles.pop_back();
                        std::cout<<"Hello\n";
                    }
                

                else if(event.key.code == sf::Keyboard::Right){
                    myrect.setPosition(myrect.getPosition().x + 15,myrect.getPosition().y);
                    if(myrect.getPosition().x +myrect.width== 900){
                        myrect.setPosition(900,myrect.getPosition().y);
                    }
                    else if(myrect.getPosition().x<=0){
                        myrect.setPosition(0,myrect.getPosition().y);
                    }
                }
            }
        }
        
        // Hardcoded Movement of circle

    
        collision(myCircle,myrect);
        collision(myCircle,myrect);


        for(auto obstacle : obstacles){
            obstacle.hasCollided(myCircle);
            if(obstacle.hasCollidedVar){
                myCircle.goingUp = false;
                std::cout<<"Collisions\a";
            }
        }

        bool circleState = myCircle.goingUp;
       
        
        if(myCircle.goingUp == true && myCircle.getPosition().y + myCircle.getRadius() >0){
            myCircle.setPosition(myCircle.getPosition().x,myCircle.getPosition().y -5);
        }

        else if(myCircle.getPosition().y == myrect.getPosition().y   ){
            myCircle.goingUp = true;
        }
        else{
            myCircle.setPosition(myCircle.getPosition().x ,myCircle.getPosition().y +5);
        }

        if(myCircle.getPosition().y ==0){
            myCircle.goingUp = false;
        }


        if (myCircle.goingRight == true && myCircle.getRadius() + myCircle.getPosition().x < 900){
            myCircle.setPosition(sf::Vector2f(myCircle.getPosition().x + 5,myCircle.getPosition().y));
        }
        else if(myCircle.getPosition().x + myCircle.getRadius()>= 768){
            myCircle.goingRight = false;
        }

        if(myCircle.goingRight == false && myCircle.getPosition().x + myCircle.getRadius()>0){
            myCircle.setPosition(sf::Vector2f(myCircle.getPosition().x -5,myCircle.getPosition().y));
        }
        else if(myCircle.getPosition().x + myCircle.getRadius() ==0){
            myCircle.goingRight = true;
        }

        // // sf::VertexArray lines(sf::LinesStrip,2);
        // lines[0].position = myCircle.getPosition();
        // lines[0].position.x+= myCircle.getRadius();
        // lines[0].position.y+= myCircle.getRadius();
        // lines[1].position = myrect.getPosition();

        window.clear(sf::Color::Black);

        drawGround(window,picture);

    
        window.draw(myrect);
        drawObstacles(obstacles,window);


        window.draw(myCircle);
                                // window.draw(lines);

        window.display();
        
        window.setFramerateLimit(60);
    }

    


}

