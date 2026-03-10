#include "app.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>

static void glfw_error_callback(int error, const char* description) {
    std::cerr << "Error de GLFW " << error << ": " << description << std::endl;
}

//Estilos
void SetupModernStyle(){
    ImGuiStyle& style = ImGui::GetStyle();
    //Redondear bordes
    style.WindowRounding = 8.0f;
    style.FrameRounding = 6.0f;
    style.PopupRounding = 6.0f;
    style.ScrollbarRounding = 6.0f;
    style.GrabRounding = 6.0f;
    style.ChildRounding = 6.0f;
    //Espaciados
    style.WindowPadding = ImVec2(12, 12);
    style.FramePadding = ImVec2(8, 6);
    style.ItemSpacing = ImVec2(8, 8);
    //Color modo oscuro
    ImVec4* colors = style.Colors;
    colors[ImGuiCol_WindowBg]       = ImVec4(0.10f, 0.11f, 0.13f, 1.00f);
    colors[ImGuiCol_ChildBg]        = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
    colors[ImGuiCol_FrameBg]        = ImVec4(0.18f, 0.20f, 0.25f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.27f, 0.33f, 1.00f);
    colors[ImGuiCol_FrameBgActive]  = ImVec4(0.30f, 0.34f, 0.41f, 1.00f);
    //Color botones principales
    colors[ImGuiCol_Button]         = ImVec4(0.20f, 0.40f, 0.80f, 1.00f);
    colors[ImGuiCol_ButtonHovered]  = ImVec4(0.25f, 0.50f, 0.95f, 1.00f);
    colors[ImGuiCol_ButtonActive]   = ImVec4(0.15f, 0.30f, 0.60f, 1.00f);
    
    colors[ImGuiCol_Header]         = ImVec4(0.20f, 0.40f, 0.80f, 0.50f);
    colors[ImGuiCol_HeaderHovered]  = ImVec4(0.25f, 0.50f, 0.95f, 0.80f);
    colors[ImGuiCol_HeaderActive]   = ImVec4(0.20f, 0.40f, 0.80f, 1.00f);
    
    colors[ImGuiCol_Separator]      = ImVec4(0.25f, 0.25f, 0.30f, 1.00f);
}

App::App() : window(nullptr){
    Init();
}

App::~App() {
    CleanUp();
}

void App::Init(){
    glfwSetErrorCallback(glfw_error_callback);
    if(!glfwInit()) exit(1);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    window = glfwCreateWindow(1280, 720, "OmniVault", nullptr, nullptr);
    if (window == nullptr) exit(1);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    //Carga Fuente
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.Fonts->AddFontFromFileTTF("../assets/fonts/fuente.ttf", 18.0f);
    
    SetupModernStyle();

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

void App::CleanUp(){
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    if (window) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

void App::Run(){
    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Llamamos a nuestra interfaz para que se dibuje
        mainWindowUI.Render();

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        
        glClearColor(0.10f, 0.11f, 0.13f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

}