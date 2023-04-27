#include <security/pam_appl.h>
#include <security/pam_misc.h>

#include "signals.h"
#include"secure.h"

// Структура для хранения ответов PAM
struct pam_response* reply;

int my_conv(int num_msg, const struct pam_message** msg,
        struct pam_response** resp, void* appdata_ptr)
{
    *resp = reply;
    return PAM_SUCCESS;
}

int getUserData(file)
{
  char* username = NULL;
  char* password = NULL;
  int maxLen = 100;
  // Выделяем память для имени пользователя и пароля
  username = (char*)malloc(maxLen* sizeof(char));
  password = (char*)malloc(maxLen* sizeof(char));

  // проверяем, что память выделена успешно
  if (username == NULL || password == NULL)
  {
    printf("Ошибка при выделении памяти.\n");
    return -1;
  }

  // запрашиваем у пользователя имя пользователя и пароль
  printf("Введите имя пользователя: ");
  scanf("%s", username);

  printf("Введите пароль: ");
  scanf("%s", password);
  // Вызываем функцию аутентификации с PAM
  int pamRet = authenticate(username, password, file);
  return pamRet;
}

int authenticate(const char* username, char* password, FILE* logfd)
{
    // Создаем структуру для общения с PAM
    const struct pam_conv localConversation = {my_conv, NULL};

    // Создаем дескриптор для PAM
    pam_handle_t* localAuthHandle = NULL;

    // Запускаем PAM с указанным именем пользователя и функцией общения
    int pamRet = pam_start("lpam", username,
                           &localConversation, &localAuthHandle);

    if (pamRet != PAM_SUCCESS)
    {
        fprintf(stderr, "Ошибка при запуске PAM.\n");
        writeLog(logfd, "%s\n", "Ошибка при запуске PAM.");
        return -1;
    }

    // Выделяем память для ответов PAM
    reply = (struct pam_response*)malloc(sizeof(struct pam_response));

    // Получаем пароль
    reply[0].resp = password;

    // Устанавливаем код ответа PAM
    reply[0].resp_retcode = 0;

    // Проверяем аутентификацию пользователя с помощью PAM
    pamRet = pam_authenticate(localAuthHandle, 0);

    if (pamRet == PAM_SUCCESS) // Если аутентификация успешна
    {
        printf("Аутентификация прошла успешно.\n");
        writeLog(logfd, "%s\n", "Аутентификация прошла успешно.");
    }
    else
    {
        // Если аутентификация не успешна
        printf("Аутентификация не прошла.\n");
        writeLog(logfd, "%s\n", "Аутентификация не прошла.");
    }

    // Заканчиваем работу с PAM
    pam_end(localAuthHandle, pamRet);

    return pamRet;
}