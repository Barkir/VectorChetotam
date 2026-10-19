#pragma once

#include "CommonClass.hh"
#include <memory>
#include <list>

// Event
struct Event;

// Application
class App; // singleton


// Object
class AObject
{
private:
    FRect _rect;
    std::list< std::unique_ptr<AObject>> _children;
    AObject * _parent;

public:
    // Common
    void setParent(AObject * new_parent);
    AObject * getParent() const;
    std::list< std::unique_ptr<AObject>> getChildren();

    // Logic
    virtual bool processEvent(const Event & event) = 0;
    virtual void run() = 0;

    // Render
    virtual void render() = 0; // use App

}; // class AObject
