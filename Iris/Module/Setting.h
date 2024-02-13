#pragma once

enum class SettingType { BOOL, SLIDER, ENUM, 
};

class Setting {
public:
    std::string name;
    std::string description;
    SettingType type;
    void* value = nullptr;
    float min = 0.0f;
    float max = 0.0f;
    std::vector<std::string> enumValues;
    int* iterator = nullptr;
    bool render = true;

    // not sure if this is necessary
    ~Setting() 
    {
        if (type == SettingType::ENUM) 
        {
            delete iterator;
        }

        else if (value) 
        {
            delete value;
            value = nullptr;
        }
    }

    Setting(const std::string& name, const std::string& description, float* value, float min, float max)
        : name(name), description(description), type(SettingType::SLIDER), value(value), min(min), max(max) {}

    Setting(const std::string& name, const std::string& description, const std::vector<std::string>& enumValues, int* iterator)
        : name(name), description(description), type(SettingType::ENUM), enumValues(enumValues), iterator(iterator) {}

    Setting(const std::string& name, const std::string& description, void* state)
        : name(name), description(description), type(SettingType::BOOL), value (state) {}

    std::string getName() const { return name; }
    std::string getDescription() const { return description; }
    SettingType getType() const { return type; }
    float getMin() const { return min; }
    float getMax() const { return max; }
    void* getValue() { return value; }
    std::vector<std::string> getEnumValues() const { return enumValues; }
    int* getIterator() const { return iterator; }

    //had to do dis sorry :/
    float sliderEase = 0;
    float boolScale = 0;
    bool isDragging = false;

    bool enumExtended = false;
    float enumSlide = 0;
};
