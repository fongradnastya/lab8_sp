#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <stdarg.h>

#include"signals.h"


void signalHandler(int signum)
{
    // Выводим сообщение об ошибке в зависимости от типа сигнала
    switch (signum)
    {
        case SIGINT:
            fprintf(stderr, "The program was interrapted by the user\n");
            writeLog("%s\n", "The program was interrapted by the user");
            break;
        case SIGTERM:
            fprintf(stderr, "The program is terminated by the system.\n");
            writeLog("%s\n", "The program is terminated by the system.");
            break;
        case SIGSEGV:
            fprintf(stderr, "The program caused a segmentation fault.\n");
            writeLog("%s\n", "The program caused a segmentation fault.");
            break;
        default:
            fprintf(stderr, "The program ended with an unknown signal.\n");
            writeLog("%s\n", "The program ended with an unknown signal.");
            break;
    }
    // Выходим из программы с кодом ошибки
    exit(1);
}

void timeoutHandler()
{
    // Выводим сообщение об ошибке
    fprintf(stderr, "Timeout exceeded.\n");
    writeLog("%s\n", "Timeout exceeded.");
    // Выходим из программы с кодом ошибки
    exit(1);
}

FILE* openLogFile(char* logFileName)
{
    // Если имя файла журнала не задано, то используем стандартное имя
    // Открываем файл журнала для записи или создаем его, если он не существует
    FILE* logfd = fopen(logFileName, "a");

    // Проверяем на ошибки
    if (logfd == NULL)
    {
        perror("fopen");
        exit(1);
    }
    return logfd;
}

void writeLog(FILE* logfd, const char* format, ...)
{
    // Проверяем, что файл журнала открыт
    if (logfd == NULL)
    {
        return;
    }
    // Получаем текущее время и форматируем его в строку
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char time_str[20];
    strftime(time_str, 20, "%Y-%m-%d %H:%M:%S", tm);

    // Выводим время в файл журнала
    fprintf(logfd, "[%s] ", time_str);
    va_list args;  // информация о списке аргументов.
    va_start(args, format);
    // Первым параметром vfprintf является дескриптор файла журнала logfd,
    // вторым - формат сообщения format, третьим - список аргументов args.
    vfprintf(logfd, format, args);
    // Освобождаем ресурсы, связанные со списком аргументов args, с
    // помощью макроса va_end.
    va_end(args);
}

void setTimer(int timeout)
{
    // Проверяем, что время ожидания задано
    if (timeout > 0) {
        // Устанавливаем таймер с помощью alarm
        alarm(timeout);
        // Устанавливаем обработчик сигнала SIGALRM
        signal(SIGALRM, timeoutHandler);
    }
}