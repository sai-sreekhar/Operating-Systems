#include <iostream>
#include <unistd.h>
using namespace std;

int main()
{
    pid_t c_pid = fork();

    if (c_pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (c_pid > 0)
    {
        cout << "Printed from parent process with id: " << getpid()
             << "\n";
    }
    else
    {
        cout << "Printed from child process with id: " << getpid()
             << "\n";
    }

    return 0;
}
