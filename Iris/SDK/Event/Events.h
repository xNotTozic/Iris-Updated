#pragma once

// bro this is SO MESYSS

enum EventType
{
    LerpMotion,
    ViewBobTick,
    ContainerTick,
    GetPickRange,
    _Keyboard,
    ActorTick,
    Mouse,
    MouseScroll,
    Update,
    LayerUpdate,
    BeforeUpdate,
    ImGUIRender,
    Hurtcam,
    PlaceBlock,
    ContinuePlaceBlock,
    StopPlaceBlock,
    GameModeTick,
    PacketSending,
    UpdateTick,
    PreUpdateTick,
};

class Event
{
public:
    virtual EventType getType() const = 0;
    bool* cancelled;
};

// include game events
#include "Events/LerpMotionEvent.h"
#include "Events/ViewBobTickEvent.h"
#include "Events/ContainerTickEvent.h"
#include "Events/GetPickRangeEvent.h"
#include "Events/KeyboardEvent.h"
#include "Events/ActorTick.h"
#include "Events/MouseEvent.h"
#include "Events/MouseScrollEvent.h"
#include "Events/UpdateEvent.h"
#include "Events/LayerUpdateEvent.h"
#include "Events/BeforeUpdateEvent.h"
#include "Events/HurtcamEvent.h"
#include "Events/BlockPlaceEvent.h"
#include "Events/BlockStopPlaceEvent.h"
#include "Events/BlockContinuePlaceEvent.h"
#include "Events/GameModeTickEvent.h"
#include "Events/PacketSendingEvent.h"
#include "Events/ImGUIRenderEvent.h"
#include "Events/onUpdateEvent.h"

// event utils
template<typename EventT>
void DispatchEvent(EventT* event)
{
    for (auto& module : modules)
    {
        if (g_isRunning)
        {
            if (module->isEnabled() or module->getCallWhenDisabled())
            {
                module->onEvent(event);
            }
        }
    }
}