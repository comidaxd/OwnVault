cmake_minimum_required(VERSION 3.15)
# Nombre y versión de nuestro proyecto
project(OmniVault VERSION 1.0)

# Usaremos el estándar moderno C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 1. Buscar las librerías instaladas en el sistema (MSYS2)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(nlohmann_json REQUIRED)

# 2. Definir dónde están los archivos de ImGui
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui)

# Recolectar todos los archivos .cpp de ImGui que necesitamos compilar
file(GLOB IMGUI_SOURCES
    ${IMGUI_DIR}/*.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# Recolectar NUESTROS archivos de código
file(GLOB_RECURSE APP_SOURCES "src/*.cpp")

# 3. Crear el ejecutable uniendo nuestro código y los archivos de ImGui
add_executable(${PROJECT_NAME} ${APP_SOURCES} ${IMGUI_SOURCES})

# 4. Decirle al compilador dónde encontrar los archivos de cabecera (.h)
target_include_directories(${PROJECT_NAME} PRIVATE
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

# 5. Vincular (Link) nuestro ejecutable con GLFW y OpenGL
target_link_libraries(${PROJECT_NAME} PRIVATE glfw OpenGL::GL nlohmann_json::nlohmann_json)