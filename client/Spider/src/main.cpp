#include <SDKDDKVer.h>
#include <iostream>
#include <windows.h>
#include <string>
#include "Core/Spider.hpp"
#include "Exception/SpiderException.hpp"

void    Stealth()
{
    HWND Stealth;

    AllocConsole();
    Stealth = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(Stealth,0);
}

int main(int argc, const char * const *argv)
{
    try {
        Stealth();

        Spider::Core::Spider	spider;

        spider.run(argc, argv);
    }
    catch (Spider::SpiderException &exception) {
        std::cerr << exception.what() << std::endl;
    }
    return (EXIT_SUCCESS);
}
