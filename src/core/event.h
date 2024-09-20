#pragma once
#include <core/keycodes.h>

namespace ENGINE::CORE
{
    enum class EventType {
        RESIZE = 0,
        CURSOR_MOVE = 1,
        MOUSE_BUTTON = 2,
        KEY = 3
    };

    struct Event {
        EventType type; 

        union {
            struct { int width, height; } resizeData;  
            struct { double xPos, yPos, Dx, Dy; } cursorMoveData;  
            struct { int button, action, mods; } mouseButtonData; 
            struct { int key, scancode, action, mods; } keyData;  
        };

        Event(EventType eventType) : type(eventType) {}

        static Event CreateResizeEvent(int width, int height) {
            Event e(EventType::RESIZE);
            e.resizeData = { width, height };
            return e;
        }

        static Event CreateCursorMoveEvent(double xPos, double yPos, double dx, double dy) {
            Event e(EventType::CURSOR_MOVE);
            e.cursorMoveData = { xPos, yPos , dx, dy};
            return e;
        }

        static Event CreateMouseButtonEvent(int button, int action, int mods) {
            Event e(EventType::MOUSE_BUTTON);
            e.mouseButtonData = { button, action, mods };
            return e;
        }

        static Event CreateKeyEvent(int key, int scancode, int action, int mods) {
            Event e(EventType::KEY);
            e.keyData = { key, scancode, action, mods };
            return e;
        }
    };
}
