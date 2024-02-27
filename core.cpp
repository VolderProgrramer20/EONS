#include <iostream>
#include <string>
#include <map>
bool is_login = false;
std::string user_name;
std::map<std::string, std::string> user_list;
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
void core_version()
{
    std::cout << "EONS 1.0.2a" << std::endl;
}
void command_render()
{
    std::string command;
    std::cout << ">>> ";
    std::cin >> command;
    if (command == "help")
    {
        std::cout << "List of commands:\nhelp\nadd_file\nexit\nver\noff" << std::endl;
        command_render();
    }
    else if (command == "add_file")
    {
        add_file();
        command_render();
    }
    else if (command == "exit")
    {
        is_login == false;
    }
    else if (command == "ver")
    {
        core_version();
        command_render();
    }
    else if (command == "off")
    {
        std::cout << "Goodbye," << user_name << std::endl;
    }
    else
    {
        std::cout << "Unknown command" << std::endl;
        command_render();
    }
}
void user_login()
{
    if (is_login == false)
    {
        std::string user_password;
        std::cout << "Please,login" << std::endl;
        std::cout << "User_name:\n>>> ";
        std::cin >> user_name;
        std::cout << "Password:\n>>> ";
        std::cin >> user_password;
        if (user_list.count(user_name) == 1)
        {
            if (user_list[user_name] == user_password)
            {
                is_login == true;
                std::cout << "Hello," << user_name << std::endl;
                core_version();
                command_render();
            }
            else
            {
                std::cout << "Password is wrong, try again" << std::endl;
                user_login();
            }
        }
        else
        {
            std::cout << "User isn't exists,try again" << std::endl;
            user_login();
        }
    }
}
void users_system_create()
{
    std::string user_name;
    std::string user_password;
    std::cout << "Write name of user account:\n>>> ";
    std::cin >> user_name;
    std::cout << "Write password:\n>>> ";
    std::cin >> user_password;
    std::cout << "User is created" << std::endl;
    user_list[user_name] = user_password;
    user_login();
}
int main()
{
    users_system_create();
    return 0;
}