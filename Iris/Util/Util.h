#pragma once
#include <filesystem>
#include <fstream>
#include "Render/Image/GifUtil.h"
#include "Render/Image/PngUtil.h"

class Util {
public:

    static inline bool leftClick, leftDown, rightClick, rightDown, middleClick, middleDown;

    inline static void createConsole()
    {
        HWND consoleWnd = GetConsoleWindow();
        if (!consoleWnd)
        {
            AllocConsole();

            freopen_s(&f, "CONOUT$", "w", stdout);
            freopen_s(&f, "CONIN$", "r", stdin);
            SetConsoleTitleA("Iris");
        }
        else
        {
            ShowWindow(GetConsoleWindow(), SW_SHOW);
        }
    }

    inline static void closeConsole()
    {
        ShowWindow(GetConsoleWindow(), SW_HIDE);
        clearConsole();
    }

    inline static void clearConsole()
    {
        system("cls");
    }

    // Directory stuff
    inline static std::string getRoamingStatePath()
    {
        return (getenv("AppData") + (std::string)"\\..\\Local\\Packages\\Microsoft.MinecraftUWP_8wekyb3d8bbwe\\RoamingState\\");
    }

    inline static std::string getClientPath()
    {
        return getRoamingStatePath() + "Iris\\";
    }

    inline static bool doesClientPathExist(const std::string& path)
    {
        return std::filesystem::exists(path);
    }

    inline static void createPath(const std::string& path)
    {
        std::filesystem::create_directory(path);
    }

    inline static void deletePath(const std::string& path)
    {
        std::filesystem::remove(path);
    }

    static void storeFromBase64(std::string name, std::string base64, std::string path)
    {
        std::string completePath = getClientPath() + path;
        std::ofstream image(completePath + (std::string)name, std::ios_base::out | std::ios_base::binary);
        std::string in = (std::string)base64;
        std::string out;
        Base64Util::decode(in, out);
        image << out << "\n";
        image.close();
    }

    static void downloadFile(std::string name, std::string url, std::string path)
    {

        std::string filePath = Util::getClientPath() + path;
        filePath += name;

        HINTERNET webH = InternetOpenA("Mozilla/5.0", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, NULL);
        HINTERNET urlFile;
        if (webH)
            urlFile = InternetOpenUrlA(webH, url.c_str(), NULL, NULL, NULL, NULL);
        else
            return;

        if (urlFile)
        {
            std::ofstream outputFile(filePath, std::ios::binary);
            if (outputFile.is_open())
            {
                char buffer[2000];
                DWORD bytesRead;
                do
                {
                    InternetReadFile(urlFile, buffer, 2000, &bytesRead);
                    outputFile.write(buffer, bytesRead);
                    memset(buffer, 0, 2000);
                } while
                    (bytesRead);

                outputFile.close();
                InternetCloseHandle(webH);
                InternetCloseHandle(urlFile);

                return;
            }
            else
            {
                InternetCloseHandle(webH);
                InternetCloseHandle(urlFile);
                return;
            }
        }
        else
        {
            InternetCloseHandle(webH);
            return;
        }
    };

    static void initClientFiles()
    {
        if (!doesClientPathExist(getClientPath()))
            createPath(getClientPath());

        if (!doesClientPathExist(getClientPath() + "Assets\\"))
            createPath(getClientPath() + "Assets\\");

        if (!doesClientPathExist(getClientPath() + "Assets\\Sequences\\"))
            createPath(getClientPath() + "Assets\\Sequences\\");

        if (!doesClientPathExist(getClientPath() + "Configurations\\"))
            createPath(getClientPath() + "Configurations\\");

        downloadFile("mainMenuBackground.png", "https://cdn.discordapp.com/attachments/1110298531723489290/1110605653963198524/backgroun.png", "Assets\\");
        
        downloadFile("circle.png", "https://cdn.discordapp.com/attachments/1063222999429427280/1091606980570910730/circle.png", "Assets\\");
        downloadFile("texel.png", "https://cdn.discordapp.com/attachments/1063222999429427280/1091606980319256607/texel.png", "Assets\\");
        downloadFile("bottom.png", "https://cdn.discordapp.com/attachments/939977409049018388/1096800566346264576/bottom.png", "Assets\\");
        downloadFile("clickBackground.png", "https://cdn.discordapp.com/attachments/1063222999429427280/1102212843408994396/clickgui-overlay.png", "Assets\\");
        downloadFile("innershadow.png", "https://cdn.discordapp.com/attachments/1063222999429427280/1102212822420701295/innershadow.png", "Assets\\");
    }

    static void initGifs(const std::string& fileName, const std::string& filePath, const std::string& outputDir)
    {
        static std::vector<std::string> textures;
        static bool hasInit = false;
        static std::chrono::steady_clock::time_point lastRender;

        lastRender = std::chrono::high_resolution_clock::now();
        textures.clear();

        gd_GIF* gif = gd_open_gif(filePath.c_str());
        if (!gif)
        {
            return;
        }

        unsigned char* buffer = (unsigned char*)malloc(gif->width * gif->height * 3);
        unsigned char* rgbaBuffer = (unsigned char*)malloc(gif->width * gif->height * 4);
        int num = 0;
        while (gd_get_frame(gif))
        {
            gd_render_frame(gif, (uint8_t*)buffer);
            num++;
            if (num == 1)
            {
                continue;
            }
            size_t off = 0;
            for (int y = 0; y < gif->height; y++)
            {
                for (int x = 0; x < gif->width; x++)
                {
                    auto newOff = 4 * (y * gif->width + x);
                    if (gd_is_bgcolor(gif, &buffer[off]))
                    {
                        rgbaBuffer[newOff] = 0;
                        rgbaBuffer[newOff + 1] = 0;
                        rgbaBuffer[newOff + 2] = 0;
                        rgbaBuffer[newOff + 3] = 0;
                    }
                    else
                    {
                        rgbaBuffer[newOff] = buffer[off];
                        rgbaBuffer[newOff + 1] = buffer[off + 1];
                        rgbaBuffer[newOff + 2] = buffer[off + 2];
                        rgbaBuffer[newOff + 3] = 255;
                    }
                    off += 3;
                }
            }

            char name[30];
            sprintf_s(name, "%s%d", fileName.c_str(), num);
            std::string path = outputDir + "\\";
            std::string filePath = path + name + ".png";
            if (!(std::filesystem::exists(filePath)))
            {
                FILE* fp;
                errno_t err = fopen_s(&fp, filePath.c_str(), "wb");
                svpng(fp, gif->width, gif->height, rgbaBuffer, true);
                fclose(fp);
            }
            textures.push_back(std::string(name));
        }

        free(buffer);
        free(rgbaBuffer);
        gd_close_gif(gif);
        hasInit = true;
    }

    static void onMouseClick(int key, bool isDown)
    {
        switch (key)
        {
        case 1:
            leftClick = isDown;
            leftDown = isDown ? true : leftDown;
            break;
        case 2:
            rightClick = isDown;
            rightDown = isDown ? true : rightDown;
            break;
        case 3:
            middleClick = isDown;
            middleDown = isDown ? true : middleDown;
            break;
        }
    }

    static bool invalidChar(char c) {
        return !(c >= 0 && *reinterpret_cast<unsigned char*>(&c) < 128);
    }

    static std::string sanitizeName(std::string name)
    {
        std::string out;
        bool wasValid = true;
        for (char c : name) {
            bool isValid = !invalidChar(c);
            if (wasValid) {
                if (!isValid) {
                    wasValid = false;
                }
                else {
                    out += c;
                }
            }
            else {
                wasValid = isValid;
            }
        }
        return out;
    }

    static bool setClipboardText(const std::string& text) 
    {
        if (!OpenClipboard(NULL))
            return false;

        if (!EmptyClipboard()) 
        {
            CloseClipboard();
            return false;
        }

        size_t textSize = (text.length() + 1) * sizeof(char);
        HGLOBAL hClipboardData = GlobalAlloc(GMEM_MOVEABLE, textSize);
        if (!hClipboardData) 
        {
            CloseClipboard();
            return false;
        }

        char* pClipboardData = static_cast<char*>(GlobalLock(hClipboardData));
        if (pClipboardData == NULL) 
        {
            GlobalFree(hClipboardData);
            CloseClipboard();
            return false;
        }

        memcpy(pClipboardData, text.c_str(), textSize);

        GlobalUnlock(hClipboardData);

        if (SetClipboardData(CF_TEXT, hClipboardData) == NULL) 
        {
            GlobalFree(hClipboardData);
            CloseClipboard();
            return false;
        }

        CloseClipboard();
        return true;
    }

private:
    static inline FILE* f;

    /*std::ifstream infile(getClientPath() + "input.txt");
        std::ofstream outfile(getClientPath() + "output.txt");
        std::string line;
        int count = 0;
        while (std::getline(infile, line)) {
            for (int i = 0; i < line.length(); i += 2000) {
                std::string substr = line.substr(i, 2000);
                outfile.write(substr.c_str(), substr.length());
                outfile << "\" + (std::string) \"";
                count += substr.length();
            }
        }*/
};
