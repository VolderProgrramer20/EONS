#include <iostream>
#include <string>
#include <vector>
#include <map>
class shell
{
private:
    /* data */
public:
    void core_version();
    void command_render();
    void logs();
    void cd(std::string folder_name);
    void mkdir(std::string folder_name);
    void rewrite_file(std::string file_name, std::string new_data);
    void delete_file(std::string delete_file_name);
    void rename_file(std::string new_name, std::string data_name);
    void add_file(std::string name, std::string type, std::string file);
    int find_directory(std::string directory);
    void rename_file_dialog();
    void add_file_dialog();
    void delete_file_dialog();
    void rewrite_file_dialog();
    void read_file();
    void mkdir_dialog();
    void cd_dialog();
    void add_user(std::string user_name, std::string user_password, bool root);
    void user_check_password();
    void user_login();
    void users_system_create();
    void user_add_dialog();
    void user_delete(std::string delete_user_name);
    void user_rename(std::string old_name, std::string new_name);
    void user_rename_dialog();
    void user_delete_dialog();
    void load();
    std::map<std::string, int> commands_list;
    bool is_login;
    bool is_password_check;
    std::string user_name;
    std::map<std::string, std::string> user_list;
    std::map<std::string, std::string> user_permissions;
    std::vector<std::map<std::string, std::string>> disk;
    std::vector<std::string> folders_names;
    std::string directory;
};
shell core;
void shell::core_version()
{
    std::cout << "Version of kernel: EONS 1.1.4b\nVersion of BFS: BasicFS 3.0" << std::endl;
}
void shell::logs()
{
    if (user_permissions[user_name] == "root")
    {
        user_check_password();
        std::cout << disk[0]["logs.txt"] << std::endl;
    }
    else
    {
        std::cout << "You need root to do this." << std::endl;
    }
}
void shell::command_render()
{
    std::string command;
    std::cout << user_name << " >>> ";
    std::cin >> command;
    switch (commands_list[command])
    {
    case 1:
        std::cout << "List of commands\n";
        for (const auto &[commands, price] : commands_list)
            std::cout << commands << std::endl;
        break;

    case 2:
        add_file_dialog();
        break;
    case 3:
        is_login = false;
        user_login();
        break;
    case 4:
        core_version();
        break;
    case 5:
        std::cout << "Goodbye," << user_name << std::endl;
        exit(0);
        break;
    case 6:
        logs();
        break;
    case 7:
        user_add_dialog();
        break;
    case 8:
        user_delete_dialog();
        break;
    case 9:
        delete_file_dialog();
        break;
    case 10:
        rename_file_dialog();
        break;
    case 11:
        read_file();
        break;
    case 12:
        user_rename_dialog();
        break;
    case 13:
        rewrite_file_dialog();
        break;
    case 14:
        mkdir_dialog();
        break;
    case 15:
        cd_dialog();
        break;
    default:
        std::cout << "Unknown command" << std::endl;
        break;
    }
    if (commands_list[command] == 0)
    {
        commands_list.erase(command);
    }
    disk[0]["logs.txt"] += user_name + " wrote command:" + command + "\n";
    command_render();
}
int shell::find_directory(std::string directory)
{
    int index = 0;
    while (folders_names[index] != directory)
    {
        index++;
    }
    return index;
}
void shell::add_file(std::string name, std::string type, std::string file)
{
    if (type == "txt")
    {
        name += ".txt";
        disk[find_directory(directory)][name] = file;
    }
    else if (type == "int")
    {
        name += ".int";
        disk[find_directory(directory)][name] = file;
    }
}
void shell::add_file_dialog()
{
    std::string data_type;
    std::string data_name;
    std::cout << "Write type of data:\n>>> ";
    std::cin >> data_type;
    std::cout << "Write name of file:\n>>> ";
    std::cin >> data_name;
    std::cout << "Write your file:";
    std::string new_file;
    std::cin >> new_file;
    add_file(data_name, data_type, new_file);
}
void shell::rename_file(std::string new_name, std::string data_name)
{
    disk[find_directory(directory)][new_name] = disk[find_directory(directory)][data_name];
    disk[find_directory(directory)].erase(data_name);
}
void shell::rename_file_dialog()
{
    std::string data_name;
    std::string new_name;
    std::cout << "Write name file (for example volder.int):\n>>> ";
    std::cin >> data_name;
    std::cout << "Write new file name:\n>>> ";
    std::cin >> new_name;
    if (data_name != "logs.txt" && disk[find_directory(directory)].count(data_name) == 1)
    {
        rename_file(new_name, data_name);
    }
    else
    {
        std::cout << "Acsess denied" << std::endl;
    }
}
void shell::delete_file(std::string delete_file_name)
{
    disk[find_directory(directory)].erase(delete_file_name);
}
void shell::delete_file_dialog()
{
    std::string delete_file_name;
    std::cout << "Write name of file\n>>> ";
    std::cin >> delete_file_name;
    if (disk[find_directory(directory)].count(delete_file_name) == 1 && delete_file_name != "logs.txt")
    {
        user_check_password();
        delete_file(delete_file_name);
    }
    else
    {
        std::cout << "Acsess denied" << std::endl;
    }
}
void shell::read_file()
{
    std::string file_name;
    std::cout << "Write name of file:\n>>> ";
    std::cin >> file_name;
    if (file_name != "logs.txt" && disk[find_directory(directory)].count(file_name) == 1)
    {
        std::cout << disk[find_directory(directory)][file_name] << std::endl;
    }
    else if (file_name == "logs.txt")
    {
        logs();
    }
    else
    {
        std::cout << "File didn't find" << std::endl;
    }
}
void shell::rewrite_file(std::string file_name, std::string new_data)
{
    disk[find_directory(directory)][file_name] = new_data;
}
void shell::rewrite_file_dialog()
{
    std::string file_name;
    std::string new_data;
    std::cout << "Write name of file:\n>>> ";
    std::cin >> file_name;
    std::cout << "Write new data\n>>> ";
    std::cin >> new_data;
    if (disk[find_directory(directory)].count(file_name) == 1 && file_name != "logs.txt")
    {
        user_check_password();
        rewrite_file(file_name, new_data);
    }
    else
    {
        std::cout << "Acsess denied" << std::endl;
    }
}
void shell::mkdir(std::string folder_name)
{
    folders_names.push_back(folder_name);
    disk.push_back({});
}
void shell::mkdir_dialog()
{
    std::string folder_name;
    std::cout << "Write name of folder:\n>>> ";
    std::cin >> folder_name;
    mkdir(folder_name);
}
void shell::cd(std::string folder_name)
{
    directory = folder_name;
}
void shell::cd_dialog()
{
    std::string folder_name;
    std::cout << "Write name of folder:\n>>> ";
    std::cin >> folder_name;
    cd(folder_name);
}
void shell::user_login()

{
    if (is_login == false)
    {
        std::string user_password;
        std::string user_name1;
        std::cout << "Please,login" << std::endl;
        std::cout << "User_name:\n>>> ";
        std::cin >> user_name1;
        std::cout << "Password:\n>>> ";
        std::cin >> user_password;
        if (user_list[user_name1] == user_password && user_list.count(user_name1) == 1)
        {
            is_login = true;
            disk[0]["logs.txt"] += user_name1 + " is login\n";
            std::cout << "Hello," << user_name1 << std::endl;
            user_name = user_name1;
            command_render();
        }
        else
        {
            std::cout << "Password is wrong, try again or user didn't find" << std::endl;
            exit(0);
        }
    }
}
void shell::users_system_create()
{
    std::string user_name;
    std::string user_password;
    std::cout << "Write name of user account:\n>>> ";
    std::cin >> user_name;
    std::cout << "Write password:\n>>> ";
    std::cin >> user_password;
    std::cout << "User created" << std::endl;
    user_list[user_name] = user_password;
    disk[0]["logs.txt"] += user_name + " created\n";
    user_permissions[user_name] = "root";
    user_login();
}
void shell::add_user(std::string user_name, std::string user_password, bool root)
{
    user_list[user_name] = user_password;
    if (root == true)
    {
        user_permissions[user_name] = "root";
        disk[0]["logs.txt"] += user_name + " created\n";
    }
    else
    {
        disk[0]["logs.txt"] += user_name + " created\n";
    }
}
void shell::user_check_password()
{
    std::string password;
    std::cout << "Write password:\n>>> ";
    std::cin >> password;
    if (user_list[user_name] == password)
    {
        std::cout << "Password is right" << std::endl;
        is_password_check = true;
    }
    else
    {
        std::cout << "Password is wrong" << std::endl;
        command_render();
    }
}
void shell::user_add_dialog()
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
        user_check_password();
        bool user_root = true;
        add_user(user_name1, user_password, user_root);
        std::cout << "User created" << std::endl;
    }
    else
    {
        bool user_root = false;
        add_user(user_name1, user_password, user_root);
        std::cout << "User created without root" << std::endl;
    }
}
void shell::user_delete(std::string delete_user_name)
{
    user_list.erase(delete_user_name);
    disk[0]["logs.txt"] += user_name + " created\n";
}
void shell::user_rename(std::string old_name, std::string new_name)
{
    user_list[new_name] = user_list[old_name];
    user_permissions[new_name] = user_permissions[old_name];
    user_list.erase(old_name);
    user_permissions.erase(old_name);
    disk[0]["logs.txt"] += old_name + " is renamed" + " to " + new_name + "\n";
    user_name = new_name;
}
void shell::user_rename_dialog()
{
    std::string user_name1;
    std::string new_name;
    std::cout << "Write username:\n>>> ";
    std::cin >> user_name1;
    std::cout << "Write new username:\n>>> ";
    std::cin >> new_name;
    if (user_list.count(user_name1) == 1)
    {
        user_check_password();
        user_rename(user_name1, new_name);
    }
    else
    {
        std::cout << "User didn't found or you don't have permissions to do this" << std::endl;
    }
}
void shell::user_delete_dialog()
{
    std::string delete_user_name;
    std::cout << "Write name of user account\n"
              << user_name << " >>> ";
    std::cin >> delete_user_name;
    if (user_list.count(delete_user_name) == 1 && user_permissions[user_name] == "root" && delete_user_name != user_name)
    {
        user_check_password();
        user_delete(delete_user_name);
        std::cout << "User is delete" << std::endl;
    }
    else
    {
        std::cout << "User isn't exist or you don't have root to do this or you try delete your account" << std::endl;
    }
}
void shell::load()
{
    commands_list["help"] = 1;
    commands_list["create_file"] = 2;
    commands_list["exit"] = 3;
    commands_list["neofetch"] = 4;
    commands_list["off"] = 5;
    commands_list["logs"] = 6;
    commands_list["add_user"] = 7;
    commands_list["delete_user"] = 8;
    commands_list["delete_file"] = 9;
    commands_list["rename_file"] = 10;
    commands_list["read_file"] = 11;
    commands_list["rename_user"] = 12;
    commands_list["rewrite_file"] = 13;
    commands_list["mkdir"] = 14;
    commands_list["cd"] = 15;
    disk.push_back({{"logs.txt", "System is load\n"}});
    folders_names.push_back("/main");
    directory = folders_names[0];
    users_system_create();
}