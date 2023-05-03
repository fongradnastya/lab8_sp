/*! \file secure.h
*  \brief   Функции для авторизации пользователей
*
*  \details Заголовочный файл, содержащий объявления функций 
*   для безопасной проверки входа пользователей
*/

#ifndef SECURE_H
#define SECURE_H

struct pam_response* reply;

/*!
 * \brief Функция общения с PAM. Используется для передачи ответов от приложения к модулю PAM
 * \param[in] num_msg Количество сообщений, переданных модулем PAM
 * \param[in] msg Указатель на массив указателей на структуры pam_message, содержащие сообщения от модуля PAM
 * \param[in] resp Указатель на указатель на массив структур pam_response, в котором функция должна сохранить ответы от приложения
 * \param[in] appdata_ptr Указатель на данные, переданные приложением через структуру pam_conv.
 * \return Код возврата PAM. В данном случае всегда возвращает PAM_SUCCESS
 */
int my_conv(int num_msg, const struct pam_message** msg, 
    struct pam_response** resp, void* appdata_ptr);

/*!
* \brief Считывает имя пользователя и пароль
* \param[in] file имя лог файла
* \return получилось ли авторизировать пользователя
*/
int getUserData(FILE* file);

/*!
 * \brief Функция аутентификации с PAM. Эта функция используется для проверки имени пользователя и пароля с помощью модуля PAM
 * \param[in] username Указатель на строку, содержащую имя пользователя
 * \param[in] password Указатель на строку, содержащую пароль пользователя
 * \param[in] logfd Дескриптор лог файла
 * \return Код возврата PAM. Возвращает PAM_SUCCESS, если аутентификация успешна, иначе возвращает другой код ошибки PAM
 */
int authenticate(const char* username, char* password, FILE* logfd);

#endif