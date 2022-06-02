#pragma once
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <array>
#include <iostream>
#include <cmath>
#include <limits>
#include <algorithm>

/** File for extending SFML Graphics Primitives into Physics enabled
 * TODO -- Implement the actualy physics
 * Inherits every method and functionality of sf::RectangleShape
 * */

#define g 9.782


// Extends RectangleShape
class rectangle:public sf::RectangleShape{

public:
  // Physical Quantitiies
    int width = 100;
    int height= 50;

    // 
    std::pair<float,float> rectTopLeft = std::make_pair(this->getPosition().x ,500);
    std::pair<int,int> rectMidLeft = std::make_pair(this->getPosition().x , 500 + this->height/2);
    std::pair<int,int> rectTopRight= std::make_pair(this->getPosition().x+ this->width , 500);
    std::pair<int,int> rectMidRight = std::make_pair(this->getPosition().x+ this->width , 500 + height/2);

    float mass;
    float velocity;
    float acceleration;

    // Top left and up coordinates and dimensions
    rectangle(){}
    rectangle(int x, int y, int width,int height){
        this->setPosition(sf::Vector2f(x,y));
        this->setSize(sf::Vector2f(width,height));
        this->width = width;
        this->height = height;
    }

    rectangle(sf::Vector2f coords, sf::Vector2f extent,std::array<float,3> physicalQuants = {0.f,0.f,0.f}){
        this->setPosition(coords);
        this->setSize(extent);

        this -> mass  = physicalQuants.at(0);
        this -> velocity  = physicalQuants.at(1);
        this -> acceleration  = physicalQuants.at(2);
       
    }

};

// Extends Circle Class

class circle : public sf::CircleShape{
public:
    float mass;
    float velocity;
    float acceleration;
    bool goingUp =false;
    bool goingRight = true;

    circle(int radius, sf::Vector2f centre,std::array<float,3> physicalQuants = {0.f,0.f,0.f}){
        this->setRadius(radius);
        this->setPosition(centre);
        this -> mass  = physicalQuants.at(0);
        this -> velocity  = physicalQuants.at(1);
        this -> acceleration  = physicalQuants.at(2);
        
    }
};

class obstacle: public  rectangle{
    public:
    obstacle(int x, int y, int width,int height){
        this->setPosition(sf::Vector2f(x,y));
        this->setSize(sf::Vector2f(width,height));
        this->width = width;
        this->height = height;
    }
        bool hasCollidedVar = false;



        bool hasCollided(circle& myCircle){
            if (this->getPosition().y + this->height == myCircle.getPosition().y  && myCircle.goingUp == true && myCircle.getPosition().x == this->getPosition().x){
                std::cout<<"Collision Between objects\n";
                hasCollidedVar = true;
                myCircle.goingUp = false;
            }
        }
};

// Specialised Distance Function that checks for collisions between circle and top of Rectangle
bool distanceIsMin(circle& Ball,rectangle& Box){
    
    int distance =800;
    int s = distance;

    /// Check for possible X value overlaps;

    if ( Ball.getPosition().x < Box.getPosition().x + Box.width  && Ball.getPosition().x + Ball.getRadius()- Box.getPosition().x >= 0){
        for (int i=Box.getPosition().x;i<Box.getPosition().x + Box.width;i++ ){
            float xD = pow(i - Ball.getPosition().x,2);
            float xY = pow(Box.getPosition().y - Ball.getPosition().y,2);
            bool touching =  sqrt(xD + xY)  - Ball.getRadius()< Ball.getRadius() ? true : false;
            if(touching){
                return touching;
            }
        }
    }
    else{
        return false;
        }
    
}

// General Distance Formula

float Distance(std::pair<float,float>& pointOnRect,std::pair<float,float>& circleCentre){
    float dY = pow(circleCentre.second - pointOnRect.second,2);
    float dX = pow(circleCentre.first - pointOnRect.first,2);
    return sqrt(dY + dX);
}

void collision(circle& Ball,rectangle& Box){  
 std::pair<float,float> circleCentre = std::make_pair(Ball.getPosition().x + Ball.getRadius(),Ball.getPosition().y + Ball.getRadius() );

    auto p = std::make_pair(Box.getPosition().x,Box.getPosition().y);
  
    if(Distance(p, circleCentre) == Ball.getRadius() ){
        std::cout<<"Hit Top Left\n\a";
        Ball.goingRight = false;
        Ball.goingUp = true;
    }
       
    else if(Distance(p, circleCentre ) == Ball.getRadius()){
        p = std::make_pair(Box.getPosition().x,Box.getPosition().y + Box.height/2);
        Ball.goingRight = false;
    }


    if (distanceIsMin(Ball,Box)){
        if(Distance(Box.rectTopLeft, circleCentre) == 0)
            std::cout<<"ColissionTop\n";
        Ball.goingUp = true;
    }
       
    p = std::make_pair(Box.getPosition().x + Box.width,Box.getPosition().y );

    if(Distance(p, circleCentre) == Ball.getRadius() + 5 ){
    std::cout<<"Hit Top right\n\a";
    Ball.goingRight = true;
    Ball.goingUp = true;
    }




    // Implement collision Detector for the four special points
 
   
    
}

 

// void obsCollision(circle& Ball,rectangle& Box){

//     std::pair<int,int> rectBottomleft = std::make_pair(Box.getPosition().x + Box.height,Box.getPosition().y + Box.width);
//     std::pair<int,int> rectBottomRight = std::make_pair(rectBottomleft.first,rectBottomleft.first + Box.width);
    
//     if (distanceIsMin(Ball,Box)){
//         std::cout<<"Colission\n";
//         Ball.goingUp = false;
//         std::cout<<Ball.goingUp<<std::endl;
//     }

    
// }