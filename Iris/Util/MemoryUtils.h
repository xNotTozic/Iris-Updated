#pragma once
#include <vector>
#include <type_traits>

template <typename F>
auto IIFE(F f) { return f(); }

template <class T>
struct remove_cvref {
    typedef std::remove_cv_t<std::remove_reference_t<T>> type;
};

template <class T>
using remove_cvref_t = typename remove_cvref<T>::type;

template <typename Ret, typename Type>
Ret& direct_access(Type* type, size_t offset) {
    union {
        size_t raw;
        Type* source;
        Ret* target;
    } u;
    u.source = type;
    u.raw += offset;
    return *u.target;
}

#define AS_FIELD(type, name, fn) __declspec(property(get = fn, put = set##name)) type name
#define DEF_FIELD_RW(type, name) __declspec(property(get = get##name, put = set##name)) type name

#define FAKE_FIELD(type, name)       \
	AS_FIELD(type, name, get##name); \
	type get##name()

#define BUILD_ACCESS(ptr, type, name, offset)                           \
	AS_FIELD(type, name, get##name);                                    \
	type get##name() const { return direct_access<type>(ptr, offset); } \
	void set##name(type v) const { direct_access<type>(ptr, offset) = v; }

#define CLASS_FIELD(type, name, offset)                                  \
	AS_FIELD(type, name, get##name);                                     \
	type get##name() const { return direct_access<type>(this, offset); } \
	void set##name(type v) const { direct_access<type>(this, offset) = v; }

bool Float_TryParse(float& target, std::string str)
{
    std::stringstream ss(str);

    if (ss >> target)
    {
        return true;
    }

    return false;
}

void empty() {}

template <typename R, typename... Args>
R CallFunc(void* func, Args... args)
{
    return ((R(*)(Args...))func)(args...);
}

bool ends_with(const std::string& str, const std::string& suffix) {
    if (suffix.length() > str.length()) {
        return false;
    }
    return str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0;
}

template <unsigned int IIdx, typename TRet, typename... TArgs>
static inline auto CallVFunc(void* thisptr, TArgs... argList) -> TRet {
    using Fn = TRet(__thiscall*)(void*, decltype(argList)...);
    return (*static_cast<Fn**>(thisptr))[IIdx](thisptr, argList...);
}

static inline void nopBytes(void* dst, unsigned int size) {
    DWORD oldprotect;
    VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
    memset(dst, 0x90, size);
    VirtualProtect(dst, size, oldprotect, &oldprotect);
};

static inline void copyBytes(void* src, void* dst, unsigned int size) {
    DWORD oldprotect;
    VirtualProtect(src, size, PAGE_EXECUTE_READWRITE, &oldprotect);
    memcpy(dst, src, size);
    VirtualProtect(src, size, oldprotect, &oldprotect);
};

static void setFloat(void* dst, float src) {
    DWORD oldprotect;
    VirtualProtect(dst, sizeof(float), PAGE_EXECUTE_READWRITE, &oldprotect);

    auto addr = reinterpret_cast<float*>(dst);
    *addr = src;

    VirtualProtect(dst, sizeof(float), oldprotect, &oldprotect);
}

static inline void patchBytes(void* dst, void* src, unsigned int size) {
    DWORD oldprotect;
    VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
    memcpy(dst, src, size);
    VirtualProtect(dst, size, oldprotect, &oldprotect);
};

template <typename T> // not related to memory LOL
std::string combine(T t)
{
    std::stringstream ss;
    ss << t;
    return ss.str();
}

template <typename T, typename... Args> // not related to memory LOL
std::string combine(T t, Args... args)
{
    std::stringstream ss;
    ss << t << combine(args...);
    return ss.str();
}

void Unprotect(void* dst, unsigned int size) {
    DWORD oldprotect;
    VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
}

static const uintptr_t range_start = reinterpret_cast<uintptr_t>(GetModuleHandleA("Minecraft.Windows.exe"));

template <typename T>
bool HookFunction(void* pTarget, T pDetour, void* pOriginal, const char* sigId)
{
    static bool initialized = false;
    if (!initialized)
    {
        initialized = true;
        if (MH_Initialize() != MH_OK)
        {
            _logf(combine("Failed to initialize MinHook", "\n").c_str());
            g_isRunning = false;
            return false;
        }
    }

    if (MH_CreateHook(pTarget, pDetour, (LPVOID*)pOriginal) != MH_OK)
    {
        _logf(combine("[", pTarget, ", ", sigId, "] Failed to create hook", "\n").c_str());
        return false;
    }

    if (MH_EnableHook(pTarget) != MH_OK)
    {
        _logf(combine("[", pTarget, ", ", sigId, "] Failed to enable hook", "\n").c_str());
        return false;
    }

    std::stringstream ss;
    ss << "Minecraft.Windows.exe+" << std::hex << (uintptr_t)pTarget - range_start;

    _logf(combine("[", ss.str().c_str(), ", ", sigId, "] Successfully Enabled hook", "\n").c_str());

    return true;
}

static void* findMultiLvlPtr(uintptr_t baseAddr, std::vector<unsigned int> offsets) {
    uintptr_t addr = baseAddr;

    for (int I = 0; I < offsets.size(); I++)
    {
        addr = *(uintptr_t*)(addr);

        if ((uintptr_t*)(addr) == nullptr)
        {
            return reinterpret_cast<void*>(addr);
        }

        addr += offsets[I];
    };

    return reinterpret_cast<void*>(addr);
};

#define INRANGE(x, a, b) (x >= a && x <= b)
#define GET_BYTE(x) ((GET_BITS(x[0]) << 4) | GET_BITS(x[1]))
#define GET_BITS(x) (INRANGE((x & (~0x20)), 'A', 'F') ? ((x & (~0x20)) - 'A' + 0xa) : (INRANGE(x, '0', '9') ? (x - '0') : 0))

static void* findSig(const char* sig)
{
    const char* pattern = sig;
    uintptr_t first_match = 0;
    static MODULEINFO mi_mod_info;
    static bool init = false;
    if (!init)
    {
        init = true;
        GetModuleInformation(GetCurrentProcess(), reinterpret_cast<HMODULE>(range_start), &mi_mod_info, sizeof(MODULEINFO));
    }
    static const uintptr_t range_end = range_start + mi_mod_info.SizeOfImage;

    BYTE pat_byte = GET_BYTE(pattern);
    const char* old_pat = pattern;

    for (uintptr_t p_cur = range_start + 0x100000; p_cur < range_end; p_cur++) // eevrything we use is over 0x100000 so we can just skip that part of memory
    {
        if (!*pattern)
        {
            return reinterpret_cast<void*>(first_match);
        }

        while (*(PBYTE)pattern == ' ')
        {
            pattern++;
        }

        if (!*pattern)
        {
            return reinterpret_cast<void*>(first_match);
        }

        if (old_pat != pattern)
        {
            old_pat = pattern;
            if (*(PBYTE)pattern != '\?') {
                pat_byte = GET_BYTE(pattern);
            }
        }

        if (*(PBYTE)pattern == '\?' || *(BYTE*)p_cur == pat_byte)
        {
            if (!first_match)
            {
                first_match = p_cur;
            }

            if (!pattern[2])
            {
                return reinterpret_cast<void*>(first_match);
            }

            pattern += 2;
        }
        else
        {
            pattern = sig;
            first_match = 0;
        }
    }
    return 0;
}

static void** getVtableFromSig(const char* sig, int offset)
{
    void* sigAddr = findSig(sig);
    int32_t sigOffset = *(int32_t*)((uintptr_t)sigAddr + offset);
    return (void**)((uintptr_t)sigAddr + sigOffset + offset + sizeof(offset));
}

static uintptr_t GetXRef(void* addr)
{
    uintptr_t offset = reinterpret_cast<uintptr_t>(addr);

    uint8_t opcode = *reinterpret_cast<uint8_t*>(addr);

    switch (opcode)
    {
    case 0x80:
        offset += *reinterpret_cast<int*>(offset + 2) + 2; // skip to offset field
        offset += 5; // include address size + second field byte
        break;

    default:
        return 0x0;
    }

    return offset;
}

static void* findOffset(const char* sig, const char* offsetId)
{
    void* result = findSig(sig);

    if (result != nullptr)
    {
        std::stringstream ss;
        ss << "Minecraft.Windows.exe+" << std::hex << (uintptr_t)result - range_start;

        _logf(combine("[", ss.str().c_str(), ", ", offsetId, "] Successfully found", "\r\n").c_str());
    }
    else
    {
        _logf(combine("[", result, ", ", offsetId, "] Failure finding sig", "\r\n").c_str());

        g_fullyUpdated = false;
        return &empty;
    }

    return result;
}