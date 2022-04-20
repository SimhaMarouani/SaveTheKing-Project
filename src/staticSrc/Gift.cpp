#include "staticInclude/Gift.h"

bool Gift::isActive() const
{
	return m_active;
}

void Gift::needToActivate()
{
	m_active = true;
}