#include <iostream>
#include <string>
#include <unistd.h>
#include <wait.h>


void fork_process_example()
{
    pid_t process_pid = fork(); //duplicamos el proceso, el pid se usa para saber si es el proceso padre o el hijo
    switch (process_pid)
    {
        case -1: //error al duplicar el proceso
            std::cout << "Error while forking, process terminated" << std::endl;
            break;
        case 0: //si somos el proceso hijo
            std::cout << "Hello from child process" << std::endl;
            exit(0);
        default://somos el proceso padre
            std::cout << "Hello from parent process" << std::endl;
            int child_status = 0;
            waitpid(process_pid, &child_status, 0);//debemos esperar a que nuestro hijo termine, o terminarlo nosotros
            break;
    }

}

std::string os_call_example(std::string cmd)
{
    std::string data;
    const int   max_buffer = 256;
    char        buffer[max_buffer];
    cmd.append(" 2>&1"); //redirecionar error to stdout, asi podemos leer pase lo que pase
    FILE* stream = popen(cmd.c_str(), "r");
    if (stream)
    {
        while (!feof(stream)) //llegamos al final?
            if (fgets(buffer, max_buffer, stream) != nullptr) data.append(buffer); //podemos leer datos?
        pclose(stream);//cerramos el pipe de comunicacion
    }
    return data;
}

void pipe_example()
{
    int pipefd[2];
    pid_t process_pid;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }
    process_pid = fork();
    if (process_pid == -1) {

    }
    switch (process_pid)
    {
        case -1:
            perror("fork");
            exit(1);
        case 0:
            // Child reads from pipe
            std::cout << "Child Process Start" << std::endl;
            close(pipefd[1]);          /* Close unused write end */
            char buff;
            while (read(pipefd[0], &buff, 1) > 0)
                std::cout << buff;
            std::cout << "Child Process Exit" << std::endl;
            close(pipefd[0]);
            exit(0);

        default:
            // Parent writes to pipe
            std::cout << "Parent Process Start" << std::endl;
            close(pipefd[0]);          //Close unused read end
            for (int i = 0; i < 10; ++i) {
                std::cout << "Parent Send data" << std::endl;
                std::string output{"Hello from child "};
                output.append(std::to_string(i));
                output.append("\n");
                write(pipefd[1], output.c_str(), output.length());
            }
            std::cout << "Parent Process End" << std::endl;
            close(pipefd[1]);          /* Reader will see EOF */
            int child_status = 0;
            waitpid(process_pid, &child_status, 0);                /* Wait for child */
            exit(0);
    }

}

int main() {
    std::cout << "Process fork example" << std::endl;
    fork_process_example();

    std::cout << "External process example" << std::endl;
    std::cout << os_call_example("ls -la");

    std::cout << "Pipe process example" << std::endl;
    pipe_example();
    return 0;
}