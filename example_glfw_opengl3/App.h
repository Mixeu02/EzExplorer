#pragma once

#include <iostream>
#include <filesystem>
#include <windows.h>

#include <imgui.h>

class App
{
public:
    App();
    virtual ~App();

    void RenderUI();

private:
    std::string currentPath;
    std::string nextPath;

    void RefreshListing(bool goBack);

};
