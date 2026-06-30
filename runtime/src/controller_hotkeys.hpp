#pragma once

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <string>

namespace meccha
{
    struct HotkeyBinding
    {
        UINT vk{VK_F10};
        UINT modifiers{0};
    };

    struct OverlayHotkeyState
    {
        bool paint_requested{false};
        bool source_pick_requested{false};
    };

    auto parse_hotkey_binding(const std::string& text) -> HotkeyBinding;
    auto hotkey_to_string(const HotkeyBinding& binding) -> std::string;
    auto hotkey_backend_json(const HotkeyBinding& binding, bool registered) -> std::string;
    auto try_capture_hotkey_from_message(const MSG& msg, HotkeyBinding& out, std::string& error, bool& cancel) -> bool;

    class OverlayHotkeys
    {
    public:
        OverlayHotkeys(HotkeyBinding paint, HotkeyBinding source_pick);
        ~OverlayHotkeys();

        auto set_paint_hotkey(HotkeyBinding paint, std::string* error = nullptr) -> bool;
        auto set_source_pick_hotkey(HotkeyBinding source_pick, std::string* error = nullptr) -> bool;
        auto backend_json() const -> std::string;
        auto paint_binding() const -> HotkeyBinding { return paint_; }
        auto source_pick_binding() const -> HotkeyBinding { return source_pick_; }
        auto paint_registered() const -> bool { return paint_registered_; }
        auto source_pick_registered() const -> bool { return source_pick_registered_; }
        void handle_message(const MSG& msg, OverlayHotkeyState& state) const;
        void poll_fallback(OverlayHotkeyState& state);

    private:
        void unregister_paint();
        void unregister_source_pick();

        HotkeyBinding paint_{};
        HotkeyBinding source_pick_{VK_F9, 0};
        bool paint_registered_{false};
        bool source_pick_registered_{false};
        bool paint_down_{false};
        bool source_pick_down_{false};
    };
}
