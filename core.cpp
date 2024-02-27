#include <iostream>
#include <string>
void create_folder_for_int(int data_of_array, int size_of_array, int index_of_data)
{
    int intenger_array[size_of_array];
    intenger_array[index_of_data] = data_of_array;
    std::cout << intenger_array[1] << std::endl;
}
void create_folder_for_string(std::string data_of_array, int size_of_array, int index_of_data)
{
    std::string string_array[size_of_array];
    string_array[index_of_data] = data_of_array;
    std::cout << string_array[1] << std::endl;
}
void core_version()
{
    std::cout << "EONS 1.0" << std::endl;
}
void add_file()
{
    std::string data_type;
    std::cout << "Write type of data (int,str):";
    std::cin >> data_type;
    std::cout << "Write your file:";
    if (data_type == "int")
    {
        int new_file;
        std::cin >> new_file;
        create_folder_for_int(new_file, 1, 1);
    }
    else if (data_type == "str")
    {
        std::string new_file;
        std::cin >> new_file;
        create_folder_for_string(new_file, 1, 1);
    }
}
void command_render()
{
    std::string command;
    std::cout << ">>> ";
    std::cin >> command;
    if (command == "help")
    {
        std::cout << "List of commands:\nhelp\nadd_file\nexit" << std::endl;
        command_render();
    }
    else if (command == "add_file")
    {
        add_file();
        command_render();
    }
    else if (command == "exit")
    {
        std::cout << "Exit..." << std::endl;
    }
    else
    {
        std::cout << "Unknown command" << std::endl;
        command_render();
    }
}
int main()
{
    core_version();
    command_render();
    return 0;
}