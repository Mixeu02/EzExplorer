#include "App.h"

namespace fs = std::filesystem;

App::App()
{
    this->currentPath = "D:\\";
    this->RefreshListing(false);
}

App::~App()
{

}

void App::RefreshListing(bool back)
{
    ImGui::NewLine();

    ImGui::Text("Folders:");
    ImGui::Separator();

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8.0f, -2.0f));


    for (const auto& entry : fs::directory_iterator(this->currentPath))
    {
        if (entry.is_directory())
        {
            std::string dirName = entry.path().string();
            dirName.erase(0, dirName.find_last_of("\\") + 1);

            ImVec2 textSize = ImGui::CalcTextSize(dirName.c_str());
            ImVec2 buttonSize = ImVec2(textSize.x + 20, textSize.y + 8);

            // Image here

            ImVec2 p = ImGui::GetCursorScreenPos();
            ImGui::GetWindowDrawList()->AddRect(p, ImVec2(p.x + buttonSize.x, p.y + buttonSize.y), ImGui::ColorConvertFloat4ToU32(ImVec4(1.0f, 1.0f, 1.0f, 1.0f)));

            if (ImGui::InvisibleButton(dirName.c_str(), buttonSize))
            {
                if (back)
                {
                    std::string parentPath = entry.path().string().substr(0, entry.path().string().find_last_of("/\\"));
                    this->currentPath = parentPath;
                }
                else
                {
                    this->currentPath = entry.path().string() + "\\\\";
                    this->RefreshListing(false);
                }
            }

            ImGui::SameLine();
            ImGui::SetCursorPosX(12);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 4);
            ImGui::TextUnformatted(dirName.c_str());
            ImGui::NewLine();
        }
    }

    ImGui::PopStyleVar();

    ImGui::NewLine();

    ImGui::Text("Files:");
    ImGui::Separator();

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8.0f, -2.0f));

    for (const auto& entry : fs::directory_iterator(this->currentPath))
    {
        if (entry.is_regular_file())
        {
            std::string dirName = entry.path().string();
            dirName.erase(0, dirName.find_last_of("\\") + 1);

            ImVec2 textSize = ImGui::CalcTextSize(dirName.c_str());
            ImVec2 buttonSize = ImVec2(textSize.x + 20, textSize.y + 8);

            ImVec2 p = ImGui::GetCursorScreenPos();
            ImGui::GetWindowDrawList()->AddRect(p, ImVec2(p.x + buttonSize.x, p.y + buttonSize.y), ImGui::ColorConvertFloat4ToU32(ImVec4(1.0f, 1.0f, 1.0f, 1.0f)));

            if (ImGui::InvisibleButton(dirName.c_str(), buttonSize))
            {
                std::string filePath = entry.path().string();
                ShellExecute(0, 0, filePath.c_str(), 0, 0, SW_SHOW);
            }

            ImGui::SameLine();
            ImGui::SetCursorPosX(12);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 4);
            ImGui::TextUnformatted(dirName.c_str());
            ImGui::NewLine();
        }
    }

    ImGui::PopStyleVar();
}

void App::RenderUI()
{
    ImGuiIO& io = ImGui::GetIO();

    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
    ImGui::SetNextWindowSize(io.DisplaySize, ImGuiCond_Always);

    ImGui::Begin("EzExplorer", nullptr,
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoTitleBar
    );

    if (ImGui::Button("Back"))
    {
        this->RefreshListing(true);
    }

    ImGui::End();
}
