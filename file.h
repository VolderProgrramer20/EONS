#include <string>
class file
{
private:
public:
    std::string file_name;
    std::string file;
    std::string file_way;
    std::string file_extension;
    void set_name(std::string name);
    void set_file_way(std::string way);
    void set_extension(std::string extension);
    void set_file(std::string file1);
};
void file::set_name(std::string name)
{
    file_name = name;
}
void file::set_file_way(std::string way)
{
    file_way = way;
}
void file::set_extension(std::string extension)
{
    file_extension = extension;
}
void file::set_file(std::string file1)
{
    file = file1;
}