#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/ui/GeodeUI.hpp>

using namespace geode::prelude;
using namespace cocos2d;

namespace freehack {

static bool g_open = false;

struct Feature {
    const char* name;
    bool enabled = false;
};

static std::vector<Feature> features;

static void addFeature(std::vector<Feature>& out, const char* name) {
    out.push_back({name, false});
}

class FreeHackLayer final : public CCLayerColor {
protected:
    CCMenu* m_menu = nullptr;
    CCNode* m_panel = nullptr;

    bool init() {
        if (!CCLayerColor::initWithColor({0, 0, 0, 185})) return false;

        auto win = CCDirector::sharedDirector()->getWinSize();

        auto panel = CCLayerColor::create({12, 12, 15, 245});
        panel->setContentSize({win.width * .94f, win.height * .88f});
        panel->setPosition({
            (win.width - panel->getContentWidth()) / 2,
            (win.height - panel->getContentHeight()) / 2
        });
        m_panel = panel;
        addChild(panel);

        auto title = CCLabelBMFont::create("FreeHack", "bigFont.fnt");
        title->setScale(.65f);
        title->setPosition(panel->getContentWidth() / 2, panel->getContentHeight() - 22);
        panel->addChild(title);

        auto ver = CCLabelBMFont::create("v1.0  |  FreeHack", "chatFont.fnt");
        ver->setScale(.32f);
        ver->setPosition(panel->getContentWidth() - 55, panel->getContentHeight() - 20);
        panel->addChild(ver);

        auto close = CCMenuItemLabel::create(
            CCLabelBMFont::create("X", "bigFont.fnt"),
            this,
            menu_selector(FreeHackLayer::onClose)
        );
        close->setScale(.45f);
        close->setPosition(panel->getContentWidth() - 17, panel->getContentHeight() - 18);

        m_menu = CCMenu::create();
        m_menu->setPosition({0, 0});
        m_menu->addChild(close);
        panel->addChild(m_menu);

        buildColumns();
        setTouchEnabled(true);
        return true;
    }

    void addHeader(CCNode* parent, const char* text, float x, float y) {
        auto h = CCLabelBMFont::create(text, "goldFont.fnt");
        h->setScale(.42f);
        h->setPosition(x, y);
        parent->addChild(h);
    }

    void addOption(CCNode* parent, const char* text, float x, float& y, float step = 15.f) {
        auto item = CCMenuItemLabel::create(
            CCLabelBMFont::create(text, "chatFont.fnt"),
            this,
            menu_selector(FreeHackLayer::onOption)
        );
        item->setScale(.36f);
        item->setPosition(x, y);
        m_menu->addChild(item);
        y -= step;
    }

    void buildColumns() {
        const float W = m_panel->getContentWidth();
        const float H = m_panel->getContentHeight();

        // 8 compact columns, matching the reference layout.
        const float startX = 45.f;
        const float colW = (W - 90.f) / 8.f;

        struct Column {
            const char* title;
            std::vector<const char*> items;
        };

        std::vector<Column> cols = {
            {"Auto", {
                "Auto Update", "Language", "Contribute Translations",
                "Theme", "Rulesets", "Alt Hotkey", "Interface Scale",
                "Animations", "Screenshot"
            }},
            {"Bypass", {
                "Anti-Kick", "Challenge Level", "Keymaster", "Main Levels",
                "Music Customiser", "Slider Limit", "Text Length",
                "Treasure Room", "Unlock Icons", "Unlock Shops", "Unlock Vaults"
            }},
            {"Creator", {
                "Accurate Save", "Copy Hack", "Custom Object Bypass",
                "Default Song Bypass", "Editor Extension", "Free Scroll",
                "Hide UI", "Level Edit", "Multiple Editor Trails",
                "No C Mark", "Place Over", "Smooth Editor",
                "Toolbox Button Bypass", "Trigger Value Bypass", "Verify Hack"
            }},
            {"Cosmetic", {
                "Accurate Percentage", "Ball Rotation Bug", "Classic Particles",
                "Classic Pulse", "Classic Wave Trail", "Coin Shower",
                "Frozen Animations", "Hide Pause Menu", "Hide Player",
                "Icon Randomiser", "No Camera", "No Camera Zoom",
                "No Circle Effect", "No Dash Fire", "No Death Effect",
                "No Ghost Trail", "No Glow", "No Mirror", "No New Best Popup",
                "No Orb Ring", "No Particles", "No Portal Classic",
                "No Portal Lightning", "No Pulse", "No Respawn Flash",
                "No Robot Fire", "No Shaders", "No Shake", "No Spider Dash",
                "No Swing Fire", "No Trail", "No Wave Pulse", "No Wave Trail"
            }},
            {"Level", {
                "0% Practice Done", "Allow Pause Buffering",
                "All Modes Platformer", "Auto Clicker", "Auto Deafen",
                "Auto Kill", "Auto Music Sync", "Auto Pickup Coins",
                "Auto Song Download", "Click Between Frames", "Click Between Steps",
                "Click on Steps", "Checkpoint Limit Bypass", "Collect Coins in Practice",
                "Confirm Exit", "Confirm Full Reset", "Confirm Normal",
                "Confirm Practice", "Confirm Reset", "Force Platformer",
                "Frame Stepper", "Hitbox Multiplier", "Instant Complete",
                "Jumpscare", "Jump Hack", "Noclip", "Noclip Limits",
                "No Collision", "Pause During Complete", "Practice Bug Fix",
                "Practice Music", "Random Seed", "Replay Last Checkpoint",
                "Respawn Time", "Shipcopter", "Show Hitboxes", "Show Hitboxes on Death",
                "Show Hitboxes Trail", "Show Layout", "Show Trajectory",
                "Show Triggers", "Smart StartPos", "StartPos Switcher"
            }},
            {"Status", {
                "Field Formatting", "Font: Big Font", "Scale 1x",
                "Opacity 1x", "Hide Status", "Message", "Testmode",
                "Cheat Indicator", "FPS Counter", "CPS Counter",
                "Best Run", "Noclip Accuracy", "Noclip Deaths",
                "Attempts", "Jumps", "Percentage", "Level Time",
                "Session Time", "Clock", "Frame Counter", "Position",
                "Velocity", "Dead", "Replay State"
            }},
            {"Universal", {
                "Allow Low Volume", "Compact Lists", "Custom Background",
                "Fast Cheats", "Load Audio to Memory", "Lock Cursors",
                "Main Menu Play", "No Music Fade Out", "No Transition",
                "Pitch Shifter", "Three-Point Priority", "Transition Customiser",
                "Transparent Lists", "FPS Unlock", "Physics TPS", "Frame Extrapolation",
                "Vertical Sync", "Lock Delta", "Real Time", "Borderless Classic",
                "Fullscreen"
            }},
            {"Cheat Safety", {
                "Disable Cheats", "Auto Safe Mode", "Safe Mode",
                "Safe Mode Popup", "Hide Endscreen Cheats", "Hide Endscreen Extras",
                "Hide Menu Snow", "Hide Robux on Pause", "Hide Robux/Shortcuts"
            }}
        };

        for (size_t i = 0; i < cols.size(); ++i) {
            float x = startX + i * colW;
            addHeader(m_panel, cols[i].title, x, H - 54.f);

            float y = H - 76.f;
            for (auto name : cols[i].items) {
                addOption(m_panel, name, x, y);
                if (y < 20.f) break;
            }
        }

        // Bottom utility groups from the reference screenshot.
        addHeader(m_panel, "Display", 48.f, 17.f);
        addHeader(m_panel, "Utility", 185.f, 17.f);
        addHeader(m_panel, "Replay", W - 70.f, 17.f);

        auto hint = CCLabelBMFont::create("F6  Open FreeHack   |   Click an option to toggle", "chatFont.fnt");
        hint->setScale(.32f);
        hint->setPosition(W / 2.f, 17.f);
        m_panel->addChild(hint);
    }

    void onOption(CCObject* sender) {
        auto item = static_cast<CCMenuItemLabel*>(sender);
        auto label = static_cast<CCLabelBMFont*>(item->getLabel());
        if (!label) return;

        // Visual toggle: append/remove a check mark.
        std::string text = label->getString();
        if (text.rfind("[x] ", 0) == 0) {
            text.erase(0, 4);
        } else {
            text = "[x] " + text;
        }
        label->setString(text.c_str());
    }

    void onClose(CCObject*) {
        g_open = false;
        removeFromParentAndCleanup(true);
    }

public:
    static FreeHackLayer* create() {
        auto ret = new FreeHackLayer();
        if (ret && ret->init()) {
            ret->autorelease();
            return ret;
        }
        delete ret;
        return nullptr;
    }
};

class $modify(FreeHackMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        auto menu = CCMenu::create();
        menu->setPosition({0, 0});

        auto label = CCLabelBMFont::create("FREEHACK", "goldFont.fnt");
        label->setScale(.38f);

        auto button = CCMenuItemLabel::create(
            label,
            this,
            menu_selector(FreeHackMenuLayer::openFreeHack)
        );
        button->setPosition(35.f, 35.f);
        menu->addChild(button);

        this->addChild(menu, 1000);
        return true;
    }

    void openFreeHack(CCObject*) {
        if (g_open) return;
        g_open = true;

        auto layer = FreeHackLayer::create();
        if (layer) CCDirector::sharedDirector()->getRunningScene()->addChild(layer, 99999);
    }
};

} // namespace freehack
