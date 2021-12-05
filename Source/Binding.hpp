#pragma once
#include <stdint.h>
#include <iostream>
#include <string>

class Binding
{
public:
    Binding(std::string pathIn, float sx, float sy, int triggerIn, int mtype, int targetIn, int typeIn, float amountIn)
    {
        startX = sx;
        startY = sy;
        path = pathIn;
        trigger = triggerIn;
        messageType = mtype;
        target = targetIn;
        type = typeIn;
        amount = amountIn;
    };
    void setTrigger(float trigger) { trigger = trigger; };
    void setStartX(int x) { startX = x; };
    void setStartY(int y) { startY = y; };
    void setMessageType(int mtype) { messageType = mtype; };
    void setPath(std::string path) { path = path; };
    void setTarget(float target) { target = target; };
    void setType(int type) { type = type; };
    void setAmount(float amount) { amount = amount; };
    int getTrigger() { return trigger; };
    float getStartX() { return startX; };
    float getStartY() { return startY; };
    int getMessageType() { return messageType; };
    std::string getPath() { return path; };
    int getTarget() { return target; };
    int getType() { return type; };
    float getAmount() { return amount; };
private:
    std::string path; //path for the binding
    float startX; //start x position for the sprite
    float startY; //start y position for the sprite
    int trigger; //Trigger note
    int messageType; //message type for the binding: 0 = off, 1 = on, 2 = CC
    int target; //Which property to target: 0=x, 1=y, 2=width, 3=heigt, 4=rotation, 5=size
    int type; //Type of change: 0=Set, 1=Scale
    float amount; //number to set to or scale by
};