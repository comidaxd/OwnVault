#pragma once
#include <GLFW/glfw3.h>
#include "ui/main_window.h"

class App{
public:
    App();
    ~App();

    void Run();

private:
    void Init();
    void CleanUp();

    GLFWwindow* window;
    UI::MainWindow mainWindowUI;

};

