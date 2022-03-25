#include "Digger.h"


Digger::Digger(Location location)

	: m_Location(location), m_OriginalLocation(location) 
{}


//-----------------------------------------------------------------------------

void Digger::set__Location(Location location)
{
	m_Location = location;
}

Location Digger::getLocation()
{
	return m_Location;
}

Location Digger::getOriginalLocation()
{
	return m_OriginalLocation;
}
