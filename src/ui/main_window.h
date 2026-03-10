#pragma once
#include <string>
#include <vector>

namespace UI{
    struct VaultItem{
        std::string title;
        std::string content;
        std::string type;
    };

    class MainWindow{
    public:
        MainWindow();
        ~MainWindow();
        void Render();

    private:
        void SaveToFile();
        void LoadFromFile();

        std::vector<VaultItem> items;
        int selected_item_index = -1;

        std::string input_title_buffer;
        std::string input_content_buffer;

        const char* type_options[3] = {"Texto", "Código", "Enlace"};
        int current_type_index = 0;

        bool show_save_message = false;
        int save_message_timer = 0;
    };

}