#include "Monster.h"
#include <iostream>
using std::cout;

Monster::Monster(Location location)
	:m_location(location), m_originalLocation(location), m_is_on_diamond(false)
{}


void Monster::setLocation(Location location)
{
	m_location = location;
}

Location Monster::getLocation()
{
	return m_location;
}

Location Monster::getOriginalLocation()
{
	return m_originalLocation;
}

void Monster::set_diamond(bool check)
{
	m_is_on_diamond = check;
}

bool Monster::get_diamond()
{
	return m_is_on_diamond;
}



