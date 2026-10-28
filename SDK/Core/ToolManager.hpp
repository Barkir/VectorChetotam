#ifndef TOOLMANAGER_HPP
#define TOOLMANAGER_HPP

#include <unordered_map>
#include <memory>
#include <string>

#include "SDK/Interfaces/IUnknown.hpp"
#include "SDK/Interfaces/ITool.hpp"

// forward-declaration
class Event;

// for now ToolManager doesn't own a tool
// so it doesn't track its lifetime
// that's why there could be some issues when the plugin is unloaded
// and the tool is still being used (nullptr reference)
// TODO: find a proper way how to track this
// or maybe DGAF

class ToolManager {
public: // constructors && destructors
    ToolManager() = default;
    // delete copy && move semantics
    // cuz application core owns it
    ToolManager(ToolManager&&) = delete;
    ToolManager& operator=(const ToolManager&) = delete;
    ToolManager& operator=(ToolManager&&) = delete;

    void registerTool(const IID& id, ITool* tool) {
        if (!tool) return;
        if (tools_.find(id) != tools_.end()) return;
        
        tools_.emplace(id, tool);
    }
    bool unregisterTool(const IID& id) {
        auto it = tools_.find(id);
        if (it == tools_.end())
            return false;

        auto tool = it->second;
        if (active_tool_ == tool) {
            active_tool_->deactivate();
            active_tool_ = nullptr;
        }
        tools_.erase(it);
    }

public: // getters && setters
    bool setActiveTool(const IID& id);
    ITool* getActiveTool() const { return active_tool_; }
    bool processEvent(const Event& event) {
        if (active_tool_) {
            return active_tool_->processEvent(event);
        }
        return false;
    }

private:
    std::unordered_map<IID, ITool*> tools_;
    ITool* active_tool_ = nullptr;
};

#endif