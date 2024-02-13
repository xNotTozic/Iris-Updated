#pragma once

class ClickGUIManager
{
public:
    static std::vector<Module*> getModulesInCategory(const std::string& category, const std::vector<Module*>& modules) {
        std::vector<Module*> mods;
        std::copy_if(modules.begin(), modules.end(), std::back_inserter(mods), [category](Module* mod) { return mod->getCategory() == category; });
        return mods;
    }

    static void ImRotateStart()
    {
        rotation_start_index = ImGui::GetBackgroundDrawList()->VtxBuffer.Size;
    }

    static inline int rotation_start_index;

    static ImVec2 ImRotationCenter()
    {
        ImVec2 l(FLT_MAX, FLT_MAX), u(-FLT_MAX, -FLT_MAX);

        const auto& buf = ImGui::GetBackgroundDrawList()->VtxBuffer;
        for (int i = rotation_start_index; i < buf.Size; i++)
            l = ImMin(l, buf[i].pos), u = ImMax(u, buf[i].pos);

        return ImVec2((l.x + u.x) / 2, (l.y + u.y) / 2);
    }
    static void ImRotateEnd(float rad, ImVec2 center = ImRotationCenter())
    {
        rad += PI * 0.5f;
        float s = sin(rad), c = cos(rad);
        center = ImRotate(center, s, c) - center;

        auto& buf = ImGui::GetBackgroundDrawList()->VtxBuffer;

        for (int i = rotation_start_index; i < buf.Size; i++)
            buf[i].pos = ImRotate(buf[i].pos, s, c) - center;
    }

    static inline bool isBinding = false;

    static float getEaseAnim(EasingUtil ease, int mode) {
        switch (mode) {
        case 0: return ease.easeOutExpo(); break;
        case 1: return getModuleByName("clickgui")->isEnabled() ? ease.easeOutElastic() : ease.easeOutBack(); break;
        }
    }
};
