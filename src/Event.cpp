//
// Created by huan on 3/7/17.
//

#include "Event.h"

using namespace std;

Event::Event() {
    eventType = NONE_EVENT_TYPE;
}

Event::Event(EventType type) {
    eventType = type;
}

ostream &operator<<(std::ostream &os, const Event &event) {
    os << event.eventStr[event.eventType];
}