#include "shell.h"
int main()
{
    shell core;
    core.file_system_create();
    core.user_system_create();
    core.user_login();
    return 0;
}