#include <stdint.h>
#include <iostream>
#include <string>

class Binding
{
public:
    Binding()
    {
        path = "";
        trigger = 0;
        target = 0;
        type = 0;
        amount = 0.0f;
    }
    Binding(std::string path, int trigger, int mtype, int target, int type, float amount)
    {
        path = path;
        trigger = trigger;
        messageType = mtype;
        target = target;
        type = type;
        amount = amount;
    };
    void setTrigger(float trigger) { trigger = trigger; };
    void setMessageType(int mtype) { messageType = mtype; };
    void setPath(std::string path) { path = path; };
    void setTarget(float target) { target = target; };
    void setType(int type) { type = type; };
    void setAmount(float amount) { amount = amount; };
    int getTrigger() { return trigger; };
    int getMessageType() { return messageType; };
    std::string getPath() { return path; };
    int getTarget() { return target; };
    int getType() { return type; };
    float getAmount() { return amount; };
private:
    std::string path; //path for the binding
    int trigger; //Trigger note
    int messageType;
    int target; //Which property to target: 0=x, 1=y, 2=width, 3=heigt, 4=rotation, 5=size
    int type; //Type of change: 0=Set, 1=Scale
    float amount; //number to set to or scale by
};