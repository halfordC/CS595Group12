#pragma once
#include "JuceHeader.h"
#include <stdio.h>

//==============================================================================


class MidiModule :
    private juce::MidiInputCallback
{
public:
    MidiModule()
        //:startTime(juce::Time::getMillisecondCounterHiRes() * 0.001)
    {
        //this should be a seperate function, public. 

        // find the first enabled device and use that by default
        
        for (auto input : midiInputs)
        {
            if (deviceManager.isMidiInputDeviceEnabled(input.identifier))
            {
                setMidiInput(midiInputs.indexOf(input));
                break;
            }
        }
    }

    ~MidiModule() override
    {
        deviceManager.removeMidiInputDeviceCallback(juce::MidiInput::getAvailableDevices()[currentInputIndex].identifier, this);
        
    }

    void getMidiDeviceNames(std::vector< std::string> *inArray) //fills input vector with availible midi devices.
    {
        midiInputs = juce::MidiInput::getAvailableDevices();
        if (midiInputs.size() == 0)
        {
            std::cout << "No devices detected" << std::endl;
            return;
        }

        for (int i = 0; i < midiInputs.size(); i++) //loop through all availible devices
        {
            inArray->push_back(midiInputs[i].name.toStdString());
        }


    }

    void connectToMidiDevice(std::string deviceName) 
    {
        if (midiInputs.size()==0) 
        {
            return;
        }
        for (int i = 0; i < midiInputs.size(); i++) 
        {
            if (deviceName.compare(midiInputs[i].name.toStdString())==0) 
            {
                //connect to that device here. 
                setMidiInput(i);
                std::cout << deviceName + " connected!" << std::endl;

                return;


            }
        }
        std::cout << "Input Midi device is not connected" << std::endl;
    }

    bool hasNewMidiMessage() 
    {
        return newMessageFlag;
    }

    void messagesParsed() 
    {
        newMessageFlag = false;
        //we also need to clear our midiBuffer at this time. 
        midiBuffer.clear();
    }

    std::string printMessage(const juce::MidiMessage& m)
    {
        if (m.isNoteOn())           return "Note on " + juce::MidiMessage::getMidiNoteName(m.getNoteNumber(), true, true, 3).toStdString();
        if (m.isNoteOff())          return "Note off " + juce::MidiMessage::getMidiNoteName(m.getNoteNumber(), true, true, 3).toStdString();
        if (m.isProgramChange())    return "Program change " + juce::String(m.getProgramChangeNumber()).toStdString();

        if (m.isController())
        {
            juce::String name(juce::MidiMessage::getControllerName(m.getControllerNumber()));

            if (name.isEmpty())
                name = "[" + juce::String(m.getControllerNumber()) + "]";

            return "Controller " + name.toStdString() + ": " + juce::String(m.getControllerValue()).toStdString();
        }


    }

    
    std::vector<juce::MidiMessage> getMidiBuffer()
    {
        return midiBuffer;
    }

    bool isConnected() 
    {
        auto list = juce::MidiInput::getAvailableDevices();

        for (int i = 0; i < list.size(); i++) 
        {
            if (deviceManager.isMidiInputDeviceEnabled(list[i].identifier)) 
            {
                return true;
            }
            
        }
        return false;

        
    }

private:


    /** Starts listening to a MIDI input device, enabling it if necessary. */
    void setMidiInput(int index)
    {
        //When we make getting input a function, we won't need this to be in here. 
        auto list = juce::MidiInput::getAvailableDevices();

        deviceManager.removeMidiInputDeviceCallback(list[lastInputIndex].identifier, this);

        auto newInput = list[index];

        if (!deviceManager.isMidiInputDeviceEnabled(newInput.identifier))
            deviceManager.setMidiInputDeviceEnabled(newInput.identifier, true);

        deviceManager.addMidiInputDeviceCallback(newInput.identifier, this);
        
        lastInputIndex = index;
    }

    // These methods handle callbacks from the midi device
    void handleIncomingMidiMessage(juce::MidiInput* source, const juce::MidiMessage& message) override
    {
        if (message.isNoteOn() || message.isNoteOff() || message.isController() || message.isProgramChange()) 
        {
            midiBuffer.push_back(message);
            newMessageFlag = true;
        }
         //this scoped variable is probably a good thing. Not sure if I need it right now though. 
        //const juce::ScopedValueSetter<bool> scopedInputFlag(isAddingFromMidiInput, true);
        //postMessageToList(message, source->getName());
    }

    //==============================================================================
    juce::AudioDeviceManager deviceManager;           
    int currentInputIndex = 0;
    int lastInputIndex = 0;                           
    bool isAddingFromMidiInput = false;  
    juce::Array<juce::MidiDeviceInfo> midiInputs;
    std::vector<juce::MidiMessage> midiBuffer;
    bool newMessageFlag;

    double startTime;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MidiModule)
};