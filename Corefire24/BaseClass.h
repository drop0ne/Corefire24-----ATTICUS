#pragma once
#ifndef BASECLASS_H
#define BASECLASS_H

#include "MyEnum.h"
#include "My Standard Includes.h"

namespace cfc {
#undef max
    // NumberGenerator
    class NumberGenerator {
    private:
        std::random_device rd;
        std::mt19937_64 generator;
    public:
        NumberGenerator();
        ~NumberGenerator();
        int getRandomNumber(const int min, const int max);
    };

    // CFC_coreComponents
    class CoreComponents {
    protected:
        HANDLE console_HWND;
        COORD topLeft;
    public:
        CoreComponents();
        inline virtual void clearScreen();
        inline virtual void pause();
        inline virtual void pause(std::string& pauseMessage);
		inline virtual void pause(const std::string& pauseMessage, const int textColor);
        inline virtual void print(const std::string& data);
        inline virtual void print(const std::string& data, const bool& use_std_endl);
        inline virtual void print(const std::string& data, const int set_text_color, const bool& use_std_endl);
        inline virtual void print(const std::string& data, const int set_text_color);
        inline virtual void print(const double& data, int numberColor);
        inline virtual void print(const std::string& string1, const double& data1,
            const std::string& string2, int& textColor, int& numberColor);
        inline virtual void print(const std::string& string1, const int& textColor1,
            const std::string& string2, const int& textColor2,
            const std::string& string3, const int& textColor3,
            const std::string& string4, const int& textColor4);
        inline virtual void setScreenColor(const char* screenTextColor);
        inline virtual void setTextColor(const int intConsolColorDOS);
        inline virtual void overrideConsoleColors(eConsoleTextColor foreground, eConsoleTextColor background);
        inline virtual void clearInputStream();
        inline virtual void extractInputStream();
        inline virtual void sleepTimer(int time);
    private:
        bool check_IF_validCommand(const char* command);
    };

    // ESCkeyButton
    class ESCkey_ProgramExit {
    public:
        ESCkey_ProgramExit();
        ~ESCkey_ProgramExit();

        std::jthread escThread;

        void isESCkeyPressed(std::stop_token stopToken) const;
        protected:
        std::atomic<bool> exitRequested_var;
    };

    // CoreFireCode_MainFunction
    class Startscreen : public CoreComponents, public NumberGenerator, public ESCkey_ProgramExit
    {
    protected:
    private:
        int mainMenu_totalParameters;
        std::vector<int> mainMenuParameterCurentState;
        std::vector<int> mainMenu_defaultParameterState;
        std::vector<bool> FLAGS_theme;

    public:
        Startscreen();
        void errorMessage();
        int mainMenuLogic();
        void setMainMenuState(const std::vector<int> newState);
        const std::vector<int>& getMainMenuState() const;
        const std::vector<int>& getMainMenuDefaultState() const;
        void generateMainMenu(const std::vector<int>& stateData);
        void setThemeFlag(const int themeFlag_ID);
        auto check_if_ExitRequested() const -> bool;
        void menuTheme(int eNUM_theme);
    };

} // namespace cfc_core
#endif // BASECLASS_H