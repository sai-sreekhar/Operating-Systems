// Child becomes Zombie as parent is sleeping when child process exits.
#include <iostream>
#include <unistd.h>
int main()
{
    pid_t child_pid = fork();

    if (child_pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (child_pid > 0)
    {
        std::cout << "Parent process with id: " << getpid() << "\n";
        sleep(10);
        exit(EXIT_SUCCESS);
    }
    else
    {
        std::cout << "Child process with id: " << getpid() << "\n";
        exit(EXIT_SUCCESS);
    }

    return 0;
}