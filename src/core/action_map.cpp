#include "action_map.h"

#include <core/input.h>

void ActionMap::bindKey(const std::string& actionName, int key)
{
	m_Map[actionName].keys.insert(key);
}

void ActionMap::update()
{
	for(auto& [actionName, action] : m_Map) {
		bool pressed = false;
		for(int key : action.keys) {
			if(Input::isKeyPressed(key))
			{
				pressed = true;
				break;
			}
		}

		action.prev_status = action.curr_status;
		action.curr_status = pressed;
	}
}

bool ActionMap::isActionPressed(const std::string& actionName) const
{
	auto it = m_Map.find(actionName);
    if (it != m_Map.end()) {
        return it->second.curr_status;
    }
    return false;
}

bool ActionMap::isActionJustPressed(const std::string& actionName) const
{
	auto it = m_Map.find(actionName);
    if (it != m_Map.end()) {
        const Action& action = it->second;
        return action.curr_status && !action.prev_status;
    }
    return false;
}
bool ActionMap::isActionJustReleased(const std::string& actionName) const
{
	auto it = m_Map.find(actionName);
    if (it != m_Map.end()) {
        const Action& action = it->second;
        return !action.curr_status && action.prev_status;
    }
    return false;
}