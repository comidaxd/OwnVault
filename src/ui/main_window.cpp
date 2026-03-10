#include "main_window.h"
#include "imgui.h"
#include <string.h>
#include <fstream>//Sirve para leer archivos del disco
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace UI{

    MainWindow::MainWindow(){
        input_title_buffer.resize(128, '\0');
        input_content_buffer.resize(1024 * 16, '\0');

        //Cargamos los datos guardados
        LoadFromFile();
        
        if(items.empty()){
            items.push_back({"Bienvenido a tu Vault", "Este es tu primer fragmento. Editalo!", "Texto"});
        }
    }

    MainWindow::~MainWindow(){
        SaveToFile();//Al cerrar guardamos automaticamente...
    }

    void MainWindow::SaveToFile(){
        json j_array = json::array();

        for(const auto& item: items){
            json j_item;
            j_item["title"] = item.title;
            j_item["content"] = item.content;
            j_item["type"] = item.type;
            j_array.push_back(j_item);
        }

        std::ofstream file("omnivault_data.json");
        if(file.is_open()){
            file<<j_array.dump(4);
            file.close();

            show_save_message = true;
            save_message_timer = 120;
        }
        else{
            std::cerr<<"Error: No se pudo abrir el archivo para guardar."<<std::endl;
        }
    }

    void MainWindow::LoadFromFile(){
        std::ifstream file("omnivault_data.json");
        if(file.is_open()){
            json j_array;
            try{
                file >> j_array;
                items.clear();

                for(const auto& j_item : j_array){
                    VaultItem item;
                    item.title = j_item.value("title", "Sin Titulo");
                    item.content = j_item.value("content", "");
                    item.type = j_item.value("type", "Texto");
                    items.push_back(item);
                }
            }
            catch(json::parse_error& e){
                std::cerr<<"Error al leer el JSON: "<<e.what()<<std::endl;
            }
            file.close();
        }
    }

    void MainWindow::Render(){
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);

        // Ocultar bordes y barras de título de la ventana de ImGui
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | 
                                        ImGuiWindowFlags_NoCollapse | 
                                        ImGuiWindowFlags_NoResize | 
                                        ImGuiWindowFlags_NoMove | 
                                        ImGuiWindowFlags_NoBringToFrontOnFocus | 
                                        ImGuiWindowFlags_NoNavFocus | 
                                        ImGuiWindowFlags_NoBackground;

        // Comenzamos a dibujar la ventana principal invisible que contendrá todo
        ImGui::Begin("MainDockSpace", nullptr, window_flags);

        // =========================================
        //             PANEL IZQUIERDO
        // =========================================
        ImGui::BeginChild("Sidebar", ImVec2(250,0), true);

        ImGui::Text("OMNIVAULT");
        ImGui::Separator();

        if(ImGui::Button("+ Nuevo Elemento", ImVec2(-1,0))){
            VaultItem new_item;
            new_item.title = "Nuevo fragmento";
            new_item.content = "";
            new_item.type = "Texto";

            items.push_back(new_item);

            selected_item_index = items.size() - 1;
        }
        //Boton de guardar
        if(ImGui::Button("Guardar Todo", ImVec2(-1,0))){
            SaveToFile();
        }
        //Mensaje temporal
        if(show_save_message){
            ImGui::TextColored(ImVec4(0.2f, 1.0f, 0.2f, 1.0f), "Guardado con exito!!");
            save_message_timer--;
            if(save_message_timer<=0) show_save_message = false;
        }
        ImGui::Separator;

        for(int i = 0; i<items.size(); i++){
            std::string display_name = items[i].title.empty() ? "<Sin titulo>" : items[i].title;
            std::string label = display_name + "###item_" + std::to_string(i);

            if(ImGui::Selectable(label.c_str(), selected_item_index == i)){
                selected_item_index = i;
            }
        }
        ImGui::EndChild();//Fin de panel izquierdo
        ImGui::SameLine();

        // =========================================
        //      PANEL DERECHO(Area Principal)
        // =========================================
        ImGui::BeginChild("MainArea", ImVec2(0,0), true);

        if(selected_item_index>=0 && selected_item_index < items.size()){
            // Si hay un elemento seleccionado, lo mostramos
            VaultItem& current_item = items[selected_item_index];
            
            // EDITAR TITULO
            strncpy(&input_title_buffer[0], current_item.title.c_str(), input_title_buffer.size());
            ImGui::Text("Titulo:");
            ImGui::SameLine();
            if(ImGui::InputText("##TitleInput", &input_title_buffer[0], input_title_buffer.size())){
                current_item.title = input_title_buffer.c_str();
            }
            
            // EDITAR TIPO
            for(int i = 0; i<3; i++){
                if(current_item.type == type_options[i]){
                    current_type_index = i;
                    break;
                }
            }
            ImGui::Text("Tipo:  ");
            ImGui::SameLine();
            if(ImGui::Combo("##TypeCombo", &current_type_index, type_options, 3)){
                current_item.type = type_options[current_type_index];
            }

            ImGui::SameLine();
            ImGui::SetCursorPosX(ImGui::GetWindowWidth()-100);
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.2f, 0.2f, 1.0f));
            if(ImGui::Button("Eliminar")){
                items.erase(items.begin()+ selected_item_index);
                selected_item_index=-1;
            }
            ImGui::PopStyleColor();

            ImGui::Separator();
            ImGui::Spacing();
            
            //EDITAR CONTENIDO
            strncpy(&input_content_buffer[0], current_item.content.c_str(), input_content_buffer.size());
            if (ImGui::InputTextMultiline("##ContentInput", &input_content_buffer[0], 
                input_content_buffer.size(), ImVec2(-1, -1))){
                current_item.content = input_content_buffer.c_str();
            }
        }
        else{
            ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f), "Selecciona un elemento de la izquierda para ver su contenido.");
        }
        ImGui::EndChild();

        ImGui::End(); 
    }
}