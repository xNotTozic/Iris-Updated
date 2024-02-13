#pragma once

class TimeUtil {
private:
    static inline std::unordered_map<std::string, std::chrono::high_resolution_clock::time_point> timerMap;
public:
    inline static long long getCurrentMs()
    {
        auto now = std::chrono::system_clock::now();
        auto nanos = std::chrono::time_point_cast<std::chrono::nanoseconds>(now);
        return nanos.time_since_epoch().count() / 1000000;
    }

    inline static bool hasTimeElapsed(std::string timerName, float ms, bool reset)
    {
        if (timerMap.find(timerName) == timerMap.end())
        {
            timerMap.insert({ timerName,std::chrono::high_resolution_clock::now() });
        }
        auto entry = timerMap.find(timerName);
        if (std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - entry->second).count() / 1000000.F >= ms)
        {
            if (reset) entry->second = std::chrono::high_resolution_clock::now();
            return true;
        }
        return false;
    }

    inline static bool resetTime(std::string timerName)
    {
        auto entry = timerMap.find(timerName);
        entry->second = std::chrono::high_resolution_clock::now();
        return true;
    }
};
