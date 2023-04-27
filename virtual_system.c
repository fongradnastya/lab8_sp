#include <stdio.h>
#include <string.h>
#include <sys/statvfs.h>
#include <unistd.h>

#include"virtual_system.h"

// Файл с информацией о смонтированных файловых системах
#define MOUNT_FILE "/proc/mounts"
#define THRESHOLD 90 // Порог заполнения диска в процентах

int CheckDiskFull()
{
    FILE *fp; // Указатель на файл
    char line[256]; // Буфер для чтения строки из файла
    char device[256]; // Буфер для хранения имени устройства
    char mountPoint[256]; // Буфер для хранения точки монтирования
    struct statvfs buf; // Структура для хранения данных о файловой системе
    unsigned long freeSpace; // Свободное пространство на диске в байтах
    unsigned long totalSpace; // Общее пространство на диске в байтах
    int usage; // Процент заполнения диска

    char buffer[256]; // Буфер для хранения пути к текущей директории
    char* directory; // Указатель для хранения результата функции getcwd()

    directory = getcwd(buffer, sizeof(buffer));
    if (directory == NULL)
    {
        perror("getcwd");
        return 1;
    }
    printf("Current directory: %s\n", buffer);

    // Открываем файл с информацией о смонтированных файловых системах
    fp = fopen(MOUNT_FILE, "r");

    if (fp == NULL)
    {
        perror("File opening error");
        return 1;
    }

    // Читаем файл построчно
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        // Разбиваем строку на токены по пробелам и получаем имя устройства и
        // точку монтирования
        sscanf(line, "%s %s", device, mountPoint);

        // Проверяем, совпадает ли точка монтирования с директорией с log
        // файлами или ее родителем
        if (strcmp(mountPoint, directory) == 0 || strcmp(mountPoint, "/") == 0)
        {
            // Закрываем файл
            fclose(fp);

            // Получаем данные о файловой системе по точке монтирования
            if (statvfs(mountPoint, &buf) == -1)
            {
                perror("Error getting file system data");
                return 1;
            }

            // Вычисляем свободное и общее пространство на диске в байтах
            freeSpace = buf.f_bsize * buf.f_bavail;
            totalSpace = buf.f_bsize * buf.f_blocks;

            // Вычисляем процент заполнения диска
            usage = 100 * (totalSpace - freeSpace) / totalSpace;

            // Выводим информацию о диске и его заполнении
            printf("Devise: %s\n", device);
            printf("Mount point: %s\n", mountPoint);
            printf("Free space: %lu byte\n", freeSpace);
            printf("Common space: %lu byte\n", totalSpace);
            printf("Fill percentage: %d%%\n", usage);

            // Проверяем, превышает ли заполнение порог
            if (usage > THRESHOLD)
            {
                printf("Warning: Disk is more than %d%% full\n", THRESHOLD);
            }
            return 0;
        }
    }

    // Если не нашли нужный диск, выводим сообщение об ошибке
    printf("Disk with log files not found\n");
    return 1;
}