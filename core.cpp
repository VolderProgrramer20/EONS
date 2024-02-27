#include <iostream>
#include <string>
#include <map>
bool is_login = false;
void user_login();
void command_render();
std::string logs = "System is load\n";
std::string user_name;
std::map<std::string, std::string> user_list;
std::map<std::string, std::string> user_permissions;
std::map<std::string, int> folder_int;
std::map<std::string, std::string> folder_str;
void add_file()
{
    std::string data_type;
    std::string data_name;
    std::cout << "Write type of data (int,str):\n>>>";
    std::cin >> data_type;
    std::cout << "Write name of file:\n>>> ";
    std::cin >> data_name;
    std::cout << "Write your file:";
    if (data_type == "int")
    {
        int new_file;
        std::cin >> new_file;
        data_name += ".int";
        folder_int[data_name] == new_file;
    }
    else if (data_type == "str")
    {
        std::string new_file;
        std::cin >> new_file;
        data_name += ".str";
        folder_str[data_name] == new_file;
    }
}
void rename_file()
{
    std::string data_name;
    std::string new_name;
    std::cout << "Write name file (for example volder.int):\n>>>";
    std::cin >> data_name;
    std::cout << "Write new file name:\n>>>";
    std::cin >> new_name;
    if (folder_int.count(data_name) == 1)
    {
        folder_int[new_name] = folder_int[data_name];
        folder_int.erase(data_name);
    }
    else if (folder_str.count(data_name) == 1)
    {
        folder_str[new_name] = folder_str[data_name];
        folder_str.erase(data_name);
    }
    else
    {
        std::cout << "File isn't exist" << std::endl;
        command_render();

    }
}
void delete_file()
{
    std::string delete_file_name;
    std::cout << "Write name of file\n>>>";
    std::cin >> delete_file_name;
    if (folder_int.count(delete_file_name) == 1)
    {
        folder_int.erase(delete_file_name);
    }
    else if (folder_str.count(delete_file_name))
    {
        folder_str.erase(delete_file_name);
    }
    else
    {
        std::cout << "File isn't exits" << std::endl;
        command_render();
    }
}
void core_version()
{
    std::cout << "EONS 1.1.2a" << std::endl;
}
void add_user()
{
    std::string user_name1;
    std::string user_password;
    std::string user_root;
    std::cout << "Write name of user account:\n>>> ";
    std::cin >> user_name1;
    std::cout << "Write password:\n>>> ";
    std::cin >> user_password;
    std::cout << "Do you want to make this user root? Y/N ";
    std::cin >> user_root;
    if (user_root == "Y" && user_permissions[user_name] == "root")
    {
        user_list[user_name] = user_password;
        user_permissions[user_name1] == "root";
        logs += user_name + " created\n";
        std::cout << "User created" << std::endl;
    }
    else if (user_permissions[user_name] != "root")
    {
        std::cout << "You don't have root to do this" << std::endl;
        std::cout << "User created" << std::endl;
        user_list[user_name] = user_password;
        logs += user_name + " created\n";
    }
    else
    {
        std::cout << "User created" << std::endl;
        user_list[user_name] = user_password;
        logs += user_name + " created\n";
    }
}
void add_user(std::string user_name, std::string user_password, bool root)
{
    user_list[user_name] = user_password;
    if (root == true)
    {
        user_permissions[user_name] == "root";
        logs += user_name + " created\n";
    }
    else
    {
        logs += user_name + " created\n";
    }
}
void user_delete()
{
    std::string delete_user_name;
    std::cout << "Write name of user account\n"
              << user_name << ">>>";
    std::cin >> delete_user_name;
    if (user_list.count(delete_user_name) == 1 && user_permissions[user_name] == "root" && delete_user_name != user_name)
    {
        user_list.erase(delete_user_name);
        std::cout << "User is delete" << std::endl;
    }
    else
    {
        std::cout << "User isn't exist or you don't have root to do this" << std::endl;
        command_render();
    }
}
void command_render()
{
    std::string command;
    std::cout << user_name << " >>> ";
    std::cin >> command;
    if (command == "help")
    {
        std::cout << "List of commands:\nhelp\nadd_file\nexit\nver\noff\nlogs\nadd_user\ndelete_user\ndelete_file\nrename_file" << std::endl;
        command_render();
        logs += "User wrote command:" + command + "\n";
    }
    else if (command == "add_file")
    {
        add_file();
        command_render();
        logs += "User wrote command:" + command + "\n";
    }
    else if (command == "exit")
    {
        is_login = false;
        user_login();
        logs += "User wrote command:" + command + "\n";

    }
    else if (command == "ver")
    {
        core_version();
        command_render();
        logs += "User wrote command:" + command + "\n";
    }
    else if (command == "off")
    {
        std::cout << "Goodbye," << user_name << std::endl;
        logs += "User wrote command:" + command + "\n";
    }
    else if (command == "logs")
    {
        logs += "User is watching logs\n";
        std::cout << logs << std::endl;
        command_render();
    }
    else if (command == "add_user")
    {
        add_user();
        logs += "User wrote command:" + command + "\n";
        command_render();
    }
    else if (command == "delete_user")
    {
        user_delete();
        logs += "User wrote command:" + command + "\n";
        command_render();
    }
    else if (command == "rename_file")
    {
        rename_file();
        logs += "User wrote command:" + command + "\n";
        command_render();
    }
    else if (command == "delete_file")
    {
        delete_file();
        logs += "User wrote command:" + command + "\n";
        command_render();
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
                is_login = true;
                logs += user_name + " is login\n";
                std::cout << "Hello," << user_name << std::endl;
                core_version();
                command_render();
            }
            else
            {
                std::cout << "Password is wrong, try again" << std::endl;
                
            }
        }
        else
        {
            std::cout << "User isn't exists,try again" << std::endl;
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
    std::cout << "User created" << std::endl;
    user_list[user_name] = user_password;
    logs += user_name + " created\n";
    user_permissions[user_name] = "root";
    user_login();
}
int main()
{
    users_system_create();
    return 0;
}