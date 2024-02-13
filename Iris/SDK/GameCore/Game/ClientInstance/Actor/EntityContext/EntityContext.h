#pragma once

#include "EntityId.h"

class EntityRegistry;

struct EntityContext
{
    EntityRegistry* registry;
    EntityId entityId;
};