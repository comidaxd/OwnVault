# OwnVault
Un gestor de fragmentos de información rápido, ligero y moderno, construido en C++17. OmniVault actúa como un "Cerebro Digital" local, permitiendo a los desarrolladores guardar, organizar y editar fragmentos de código, enlaces y notas en tiempo real.

## Características
* Interfaz gráfica oscura y limpia basada en Dear ImGui.
* Los datos se guardan automáticamente en formato JSON
* Permite categorizar los fragmentos por tipo (Texto, Código, Enlace).

## Tecnologías utilizadas
* Lenguaje: C++17
* Sistema de construcción: CMake
* GUI: Dear ImGui + GLFW + OpenGL3
* Serialización: nlohmann/json

## Como compilar (Windows)
Este proyecto está configurado para compilarse usando el ecosistema MSYS2 (MinGW-w64 UCRT).

### Requisitos previos
1. Instalar [MSYS2](https://www.msys2.org/).
2. Instalar el compilador y herramientas desde la terminal de MSYS2:
- pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake 
    - pacman -S mingw-w64-ucrt-x86_64-ninja mingw-w64-ucrt-x86_64-glfw 
    - pacman -S mingw-w64-ucrt-x86_64-nlohmann-json
### Construcción
1. Clona el repositorio.
2. Abre el proyecto en Visual Studio Code.
3. Utiliza la extensión CMake Tools para configurar y compilar el proyecto.
4. El ejecutable se generará en el directorio build/ .

Desarrollado como proyecto de practica.\
Se harán mejoras al proyecto.
