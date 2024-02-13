#pragma once

// MCUI Library to help with basic menus to debug your client with

class MCUI_Debug
{
private:
    struct Window
    {
        Vector2<float> position;
        Vector2<float> size;
        std::string id;

        Window(Vector2<float> pos, Vector2<float> sz, std::string windowId)
            : position(pos), size(sz), id(windowId)
        {}
    };

    static std::vector<Window> windows;
    static Window* currentWindow; // Track the current window being set up

public:
    static void begin(Vector2<float> position, Vector2<float> size, std::string windowId)
    {
        windows.emplace_back(position, size, windowId);
        currentWindow = &windows.back();

        // Draw window background
        RenderUtil::fillRectangle(Vector4<float>(position.x, position.y,
            position.x + size.x,
            position.y + size.y),
            UIColor(0, 0, 0), 0.8f);
    }

    static void addButton(Vector2<float> buttonPosition, Vector2<float> buttonSize, std::string buttonText)
    {
        if (currentWindow)
        {
            Window& window = *currentWindow;

            // Draw button background
            RenderUtil::fillRectangle(Vector4<float>(window.position.x + buttonPosition.x,
                window.position.y + buttonPosition.y,
                window.position.x + buttonPosition.x + buttonSize.x,
                window.position.y + buttonPosition.y + buttonSize.y),
                UIColor(128, 128, 128), 1.0f);

            // Draw button text
            RenderUtil::drawString(Vector2<float>(window.position.x + buttonPosition.x + 5.0f,
                window.position.y + buttonPosition.y + 5.0f),
                new std::string(buttonText), UIColor(255, 255, 255), 12.0f, 1.0f, false);
        }
    }

    static void end()
    {
        currentWindow = nullptr;
    }

    static void stopDrawing()
    {
        windows = {};
    }
};

// Initialize static member variables
std::vector<MCUI_Debug::Window> MCUI_Debug::windows;
MCUI_Debug::Window* MCUI_Debug::currentWindow;