#include <Exploit/Utils.hpp>
#include <Exploit/Globals.hpp>
#include <Communication/Communication.hpp>
#include <Exploit/TaskScheduler/TaskScheduler.hpp>
#include <Exploit/TpHandler.hpp>

#include <filesystem>
#include <windows.h>

void MainThread(HMODULE hModule)
{
    
    char appdata[MAX_PATH] = {};
    if (GetEnvironmentVariableA(OBF("APPDATA"), appdata, MAX_PATH) && appdata[0] != '\0')
        SharedVariables::workspace_folder = std::filesystem::path(appdata) / OBF("Nam") / OBF("workspace");
    else
        SharedVariables::workspace_folder = std::filesystem::path(OBF("workspace"));

    {
        std::error_code ec;
        if (!std::filesystem::exists(SharedVariables::workspace_folder, ec))
            std::filesystem::create_directories(SharedVariables::workspace_folder, ec);
    }

    Communication::Initialize();
  

    TpHandler::Initialize();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);
        
        std::thread(MainThread, hModule).detach();
    }

    return TRUE;
}
