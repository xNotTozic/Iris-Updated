#pragma once

// encryption and decryption macro using XOR
#define XOR(input) \
    [](const std::string& str, const std::string& k) -> std::string { \
        std::string result; \
        for (size_t i = 0; i < str.size(); ++i) { \
            result += str[i] ^ k[i % k.size()]; \
        } \
        return result; \
    }(input, "srxfiqXyeemi")

class HWIDUitl {
protected:
    inline static std::string getCPUSerial() {
        std::string cpuSerialNum = "";
        HKEY hKey;
        if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hKey) != ERROR_SUCCESS) throw std::runtime_error("Failed to open registry key");
        DWORD size = 0;
        if (RegQueryValueEx(hKey, "ProcessorNameString", NULL, NULL, NULL, &size) != ERROR_SUCCESS || size == 0) throw std::runtime_error("Failed to read CPU serial number from registry");
        std::vector<char> buffer(size);
        if (RegQueryValueEx(hKey, "ProcessorNameString", NULL, NULL, reinterpret_cast<LPBYTE>(&buffer[0]), &size) != ERROR_SUCCESS) throw std::runtime_error("Failed to read CPU serial number from registry");
        cpuSerialNum = std::string(buffer.begin(), buffer.end());
        RegCloseKey(hKey);
        return cpuSerialNum;
    }

    inline static std::string getOS() {
        std::string osVersion = "";
        OSVERSIONINFOEX versionInfo;
        versionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
        ULONGLONG condition_mask = 0;
        VER_SET_CONDITION(condition_mask, VER_MAJORVERSION, VER_GREATER_EQUAL);
        VER_SET_CONDITION(condition_mask, VER_MINORVERSION, VER_GREATER_EQUAL);
        if (!VerifyVersionInfo(&versionInfo, VER_MAJORVERSION | VER_MINORVERSION, condition_mask)) throw std::runtime_error("Failed to get OS version information");
        osVersion = std::to_string(versionInfo.dwMajorVersion) + "." + std::to_string(versionInfo.dwMinorVersion);
        return osVersion;
    }

public:
    inline static std::string getUsername()
    {
        char username[UNLEN + 1];
        DWORD username_len = UNLEN + 1;

        GetUserName(username, &username_len);

        return std::string(username);
    }

    inline static std::string generateFingerprint() {
        std::string fingerprint = "";
        fingerprint = getCPUSerial() + "_" + getOS();
        return XOR(fingerprint);
    }
};
