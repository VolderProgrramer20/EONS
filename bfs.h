#include <iostream>
#include <map>
#include <vector>
#include "file.h"
class bfs
{
private:
    std::vector<std::string> folder_names;
    std::string current_dir;
    bool check_file_name(std::string file_name, std::string folder_name);
    bool check_folder_name(std::string folder_name);
    void check_file_system();

public:
    std::map<std::string, std::vector<file>> disk;
    void write_file(file file1, std::string folder);
    void delete_file(file file1, std::string folder);
    void rename_file(file file1, std::string folder, std::string new_name);
    void read_file(file file1);
    void add_folder(std::string folder_name);
    void delete_folder(std::string folder_name);
    void rename_folder(std::string folder_name, std::string new_name);
    void cd(std::string folder_name);
};
void bfs::check_file_system()
{
    for (int i = 0; i < folder_names.size(); i++)
    {
        std::cout << folder_names[i] << std::endl;
    }
}
bool bfs::check_file_name(std::string file_name, std::string folder_name)
{
    for (int i = 0; i < disk[folder_name].size(); i++)
    {
        if (disk[folder_name][i].file_name == file_name)
        {
            return false;
        }
    }
    return true;
}
bfs file_system;
bool bfs::check_folder_name(std::string folder_name)
{
    for (int i = 0; i < folder_names.size(); i++)
    {
        if (folder_names[i] == folder_name)
        {
            return false;
        }
    }
    return true;
}
void bfs::write_file(file file1, std::string folder)
{
    if (check_file_name(file1.file_name, folder))
    {
        disk[folder].push_back(file1);
    }
    else
    {
        std::cout << "This file has already created" << std::endl;
    }
}
void bfs::delete_file(file file1, std::string folder)
{
    auto iter = disk[folder].begin();
    for (int i = 0; i < disk[folder].size(); i++)
    {
        if (disk[folder][i].file_name == file1.file_name)
        {
            disk[folder].erase(iter);
        }
        iter++;
    }
}
void bfs::rename_file(file file1, std::string folder, std::string new_name)
{
    for (int i = 0; i < disk[folder].size(); i++)
    {
        if (disk[folder][i].file_name == file1.file_name && check_file_name(new_name, folder))
        {
            disk[folder][i].file_name = new_name;
        }
        else if (!check_file_name(new_name, folder))
        {
            std::cout << "File with this name has already created" << std::endl;
        }
    }
}
void bfs::read_file(file file1)
{
    if (file1.file_extension == "txt")
    {
        std::cout << file1.file << std::endl;
    }
    else
    {
        std::cout << "Wrong file extension" << std::endl;
    }
}
void bfs::add_folder(std::string folder_name)
{
    folder_names.push_back(folder_name);
    disk[folder_name] = {};
}
void bfs::delete_folder(std::string folder_name)
{
    auto iter = folder_names.begin();
    for (int i = 0; i < folder_names.size(); i++)
    {
        if (folder_names[i] == folder_name && *(iter) == folder_name)
        {
            disk.erase(folder_name);
            folder_names.erase(iter);
        }
        iter++;
    }
}
void bfs::rename_folder(std::string folder_name, std::string new_name)
{
    if (check_folder_name(folder_name))
    {
        disk[new_name] = disk[folder_name];
        disk.erase(folder_name);
    }
    else
    {
        std::cout << "Folder with this name has already created" << std::endl;
    }
}
void bfs::cd(std::string folder_name)
{
    for (int i = 0; i < folder_names.size(); i++)
    {
        if (folder_names[i] == folder_name)
        {
            current_dir = folder_name;
        }
    }
}