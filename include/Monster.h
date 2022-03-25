#pragma once

#include "Location.h"
#include <vector>

class Monster
{
public:
	Monster() = default;
	Monster(Location location);
	void setLocation(Location);
	Location getLocation();
	Location getOriginalLocation();
	void set_diamond(bool);
	bool get_diamond();
	

private:
	Location m_location;
	Location m_originalLocation;
	bool m_is_on_diamond;
	
};