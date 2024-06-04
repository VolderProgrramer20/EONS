#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "user_system.h"

class shell
{
private:
    bool core_work = true;
    user_system kernel;
    std::string version = "1.1.5b";
    std::string current_command;
    user current_user;
    std::vector<std::string> command_list = {"off", "help", "ver", "add_user", "exit", "delete_user", "rename_user", "write_file", "cd", "delete_file", "add_folder", "delete_folder", "add_permission", "delete_permisison"};
    std::vector<std::string> commands_with_arguments = {"add_user", "delete_user", "rename_user"};
    int find_command_index(std::string command, std::vector<std::string> vector);

public:
    std::vector<std::string> parse_command(std::string command);
    void command_input();
    void exit();
    void command_render(std::string command, std::string command_without_arguments);
    void kernel_version();
    void help();
    void add_user_dialog(std::string user_name, std::string password);
    void delete_user_dialog(std::string user_name);
    void rename_user(std::string user_name, std::string new_name);
    void user_login();
    void user_system_create();
    bool user_check_password(user user);
    void file_system_create();
};
void shell::file_system_create()
{
    file_system.add_folder("/");
    file_system.add_folder("/shell");
    file_system.add_folder("/users");
}
bool shell::user_check_password(user user)
{
    std::string password;
    std::cout << "Write password\n>>> ";
    std::cin >> password;
    if (user.user_password == password)
    {
        std::cout << "Password is right" << std::endl;
        return true;
    }
    else
    {
        std::cout << "Password is wrong,try again" << std::endl;
        return true;
    }
}
int shell::find_command_index(std::string command, std::vector<std::string> vector)
{
    for (int i = 0; i < command_list.size(); i++)
    {
        if (command == vector[i])
        {
            return i;
        }
    }
    return -1;
}
void shell::command_render(std::string command, std::string command_without_arguments)
{
    auto vector = parse_command(command);
    int index = find_command_index(command_without_arguments, command_list);
    switch (index)
    {
    case 0:
        core_work = false;
        break;
    case 1:
        help();
        break;
    case 2:
        kernel_version();
        break;
    case 3:
        add_user_dialog(vector[1], vector[2]);
        break;
    case 4:
        exit();
        break;
    case 5:
        delete_user_dialog(vector[1]);
        break;
    case 6:
        rename_user(vector[1], vector[2]);
        break;
    }
}
void shell::command_input()
{
    while (core_work)
    {
        std::cout << current_user.user_name << " >>> ";
        std::cin >> current_command;
        std::string command_without_arguments = current_command;
        getline(std::cin, current_command);
        if (find_command_index(command_without_arguments, command_list) != -1 && find_command_index(current_command, commands_with_arguments) != -1)
        {
            command_render(current_command, command_without_arguments);
        }
        else if (find_command_index(command_without_arguments, command_list) != -1 && find_command_index(current_command, commands_with_arguments) == -1)
        {
            command_render(current_command, command_without_arguments);
        }
        else
        {
            std::cout << "Unknown command or wrong arguments" << std::endl;
        }
    }
}
void shell::user_system_create()
{
    std::string user_name;
    std::string password;
    user first_user;
    std::cout << "Welcome to the EONS! Please write name of your new user and password" << std::endl;
    std::cout << "Write name of user\n>>> ";
    std::cin >> user_name;
    std::cout << "Write password\n>>> ";
    std::cin >> password;
    first_user.set_name(user_name);
    first_user.set_password(password);
    first_user.add_permission(root);
    kernel.add_user(first_user);
    std::cout << "User is created. Please,login" << std::endl;
}
void shell::rename_user(std::string user_name, std::string new_name)
{
    kernel.user_rename(user_name, new_name);
    current_user.user_name = new_name;
}
void shell::help()
{
    std::cout << "List of commands\n";
    for (int i = 0; i < command_list.size(); i++)
    {
        std::cout << command_list[i] << std::endl;
    }
}
void shell::user_login()
{
    std::string user_name;
    std::string password;
    if (!kernel.is_empty())
    {
        std::cout << "Write name of user\n>>> ";
        std::cin >> user_name;
        std::cout << "Write password\n>>> ";
        std::cin >> password;
        if (kernel.login_user(user_name, password).user_name != "user")
        {
            current_user.user_name = user_name;
            current_user.user_permissions = kernel.login_user(user_name, password).user_permissions;
            command_input();
        }
        else
        {
            std::cout << "Wrong name or password" << std::endl;
        }
    }
    else
    {
        user_system_create();
    }
}
void shell::add_user_dialog(std::string user_name, std::string password)
{
    user new_user;
    if (new_user.set_name(user_name))
    {
        new_user.set_password(password);
        new_user.add_permission(read_file);
        new_user.add_permission(write_file);
        new_user.add_permission(delete_file);
        new_user.add_permission(delete_folder);
        new_user.add_permission(write_folder);
        kernel.add_user(new_user);
        std::cout << "User is created" << std::endl;
    }
    else
    {
        std::cout << "This user has already created." << std::endl;
    }
}
void shell::delete_user_dialog(std::string user)
{
    if (user_check_password(current_user))
    {
        if (user != current_user.user_name && current_user.find_permission_index(delete_user, current_user) != -1 || current_user.find_permission_index(root, current_user) != -1)
        {
            kernel.delete_user(user);
            std::cout << "User is deleted" << std::endl;
        }
        else
        {
            std::cout << "You can't delete your user or you don't have permissions to delete user" << std::endl;
        }
        auto iter = user_names.begin();
        for (int i = 0; i < user_names.size(); i++)
        {
            if (*(iter) == user)
            {
                user_names.erase(iter);
            }
            iter++;
        }
    }
}
void shell::kernel_version()
{
    std::cout << "EONS version: " << version << std::endl;
}
void shell::exit()
{
    current_user.user_name = "";
    user_login();
}
std::vector<std::string> shell::parse_command(std::string command)
{
    std::vector<std::string> result;
    std::string part = "";
    command = command + " "; // если последний символ - не пробел, последнего push_back не произойдет.
    for (char ch : command)
    {
        if (ch == ' ') // пропуск всех пробелов
        {
            result.push_back(part);
            part = "";
            continue;
        }
        part += ch;
    }
    return result;
}