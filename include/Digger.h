#pragma once
#include "Location.h"

class Digger
{
public:
	Digger() = default;
	Digger(Location location);
	void set__Location(Location);
	Location getLocation();
	Location getOriginalLocation();
private:

	Location m_Location;
	Location m_OriginalLocation;
};
