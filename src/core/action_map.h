#pragma once
#include <string>
#include <unordered_map>
#include <unordered_set>

struct Action
{
	std::unordered_set<int> keys;
	bool prev_status = false;
	bool curr_status = false;
};

class ActionMap
{
public:
	void bindKey(const std::string& actionName, int key);
	bool isActionPressed(const std::string& actionName) const;
	bool isActionJustPressed(const std::string& actioNname) const;
	bool isActionJustReleased(const std::string& actionName) const;
	void update();

private:
	std::unordered_map<std::string, Action> m_Map;
};