#include "Component.h"

Component::Component(Entity* owner, ComponentTypeID typeID) : _owner{ owner }, _typeID{ typeID }, _enabled{ true }
{
}
