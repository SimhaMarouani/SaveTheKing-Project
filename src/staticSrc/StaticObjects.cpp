#include "staticInclude/StaticObjects.h"

void StaticObjects::DeleteObj()
{
	m_delete = true;
}

bool StaticObjects::needToDelete() const
{
	return m_delete; 
}