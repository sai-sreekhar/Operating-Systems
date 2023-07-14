// Parent process finishes execution while the child process is running. The child processs becomes orphan.
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
        exit(EXIT_SUCCESS);
    }
    else
    {
        sleep(60);
        std::cout << "Child process with id: " << getpid() << "\n";
        exit(EXIT_SUCCESS);
    }

    return 0;
}