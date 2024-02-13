#pragma once

#include "Setting.h"

class Module
{
public:
    Module(const std::string& name, const std::string& category, const std::string& description, __int32 keybind = 0x7, bool enabled = false) :
        name_(name),
        category_(category),
        description_(description),
        enabled_(enabled),
        keybind_(keybind),
        visible_(true)
    {
        //addBool("IngameOnly", "Can use keybind in menus", &ingameOnly);
        addBool("Drawn", "Draw in the arraylist", &visible_);
    }

    virtual ~Module() {}

    // Util stuff
    void IngameOnly()
    {
        requiresIngame = true;
    }

    void RemoveFromClickgui()
    {
        exists = false;
    }

    void RemoveFromArraylist()
    {
        visible_ = false;
    }

    void MenuToggle()
    {
        ingameOnly = false;
    }

    void RemoveNotifications()
    {
        showNotifications = false;
    }

    // Get the name of the module
    std::string getName() const
    {
        return name_;
    }
    
    std::string getDescription() const
    {
        return description_;
    }

    // Get the category of the module
    std::string getCategory() const
    {
        return category_;
    }

    // Get the keybind of the module
    int getKeybind()
    {
        return keybind_;
    }

    bool getCallWhenDisabled()
    {
        return callWhenDisabled;
    }

    // Get the enabled state of the module
    bool isEnabled() const
    {
        return enabled_;
    }

    // Get the visible state of the module
    bool isVisible() const
    {
        return visible_;
    }

    const std::vector<Setting*> getSettings() const 
    {
        return settings_;
    }

    // Set the keybind of the module
    void setKeybind(__int32 keybind)
    {
        keybind_ = keybind;
    }

    // Set the enabled state of the module
    void setEnabled(bool enabled)
    {
        enabled_ = enabled;
    }

    // Set the visible state of the module
    void setVisible(bool visible)
    {
        visible_ = visible;
    }

    // Toggle the enabled state of the module (Includes events)
    void toggle()
    {
        enabled_ = !enabled_;
        enabled_ ? onEnabled() : onDisabled();

        if (showNotifications)
        {
            Game::Core::noti.addNotification("Module:", name_ + " was " + std::string(enabled_ ? "enabled" : "disabled"), 1.5f);
        }
    }

    void addSlider(const std::string name, const std::string description, float* value, float min, float max)
    {
        settings_.emplace_back(new Setting(name, description, value, min, max));
    }

    void addBool(const std::string name, const std::string description, bool* state)
    {
        settings_.emplace_back(new Setting(name, description, state));
    }

    void addEnum(const std::string name, const std::string description, std::vector<std::string> enums, int* iterator)
    {
        settings_.emplace_back(new Setting(name, description, enums, iterator));
    }

    virtual std::string getModeName()
    {
        std::ostringstream oss;
        bool firstEnum = false;
        for (auto set : settings_) 
        {
            if (set->getType() == SettingType::ENUM && set->getEnumValues().size() > 0 && set->getEnumValues()[0].size() > 0) 
            {
                if (!firstEnum) 
                {
                    oss << " " << set->getEnumValues()[*set->getIterator()];
                    firstEnum = true;
                }
            }
        }
        return oss.str();
    }

    virtual void onEnabled() {};
    virtual void onDisabled() {};

    // util events
    virtual void onEvent(class GetPickRangeEvent* event) {};
    virtual void onEvent(class LerpMotionEvent* event) {};
    virtual void onEvent(class ActorTickEvent* event) {};

    // frame events
    virtual void onEvent(class HurtcamEvent* event) {};
    virtual void onEvent(class ViewBobTickEvent* event) {};
    virtual void onEvent(class ContainerTickEvent* event) {};
    virtual void onEvent(class UpdateEvent* event) {};
    virtual void onEvent(class UpdateTickEvent* event) {};
    virtual void onEvent(class PreUpdateTickEvent* event) {};
    virtual void onEvent(class LayerUpdateEvent* event) {};
    virtual void onEvent(class BeforeUpdateEvent* event) {};
    virtual void onEvent(class ImGUIRenderEvent* event) {};
    virtual void onEvent(class NiggaTickEvent* event) {};

    // block events
    virtual void onEvent(class BlockPlaceEvent* event) {}; // cant believe you need 3 events to cancel placing blocks
    virtual void onEvent(class BlockStopPlaceEvent* event) {};
    virtual void onEvent(class BlockContinuePlaceEvent* event) {};
    virtual void onEvent(class GameModeTickEvent* event) {};

    // network events
    virtual void onEvent(class PacketSendingEvent* event) {};

    // key events
    virtual void onEvent(class KeyboardEvent* event) {};
    virtual void onEvent(class MouseEvent* event) {};
    virtual void onEvent(class MouseScrollEvent* event) {};

    float animPercentage = 0.f;
    Vector2<float> location = Vector2<float>();
    Vector2<float> size = Vector2<float>();
    Vector2<float> pos = Vector2<float>();
    bool showSettings = false;
    float cAnim = 0;
    float cFade = 0;
    float cScale = 0;

    // extra settings
    bool ingameOnly = true;
    bool showNotifications = true;
    bool exists = true;
    bool requiresIngame = false;
    bool callWhenDisabled = false;

protected:
    std::vector<Setting*> settings_;
    std::string name_;
    std::string description_;
    std::string category_;
    __int32 keybind_;
    bool enabled_;
    bool visible_;
};