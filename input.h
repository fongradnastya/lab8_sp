/*! \file    input.h
 *  \brief   Функции для считывания данных из консоли
 *
 *  \details Заголовочный файл, содержащий объявления функций 
 *           для обраотки пользовательского ввода
 */

#ifndef INPUT_H
#define INPUT_H

/*!
 * \brief Выводит информацию о доступных при запуске опциях
 * \param[in] command имя введённой комманды
 */
void showHelp(char* command);

/*!
 * \brief Считывает целое число из консоли
 * \param[in] argc количество аргументов командной строки
 * \param[in] argv массив аргументов командной строки
 * \param[out] logFile имя лог файла
 * \param[out] timeout время ожидания запроса
 */
void parseArguments(int argc, char* argv[], char** logFile, int* timeout);

/*!
 * \brief Считывает строку из консоли
 * \return полученная строка
 */
char* GetString();

/*!
 * \brief Считывает целое число из консоли
 * \param[out] val считанное значение
 * \return код выполнения операции
 */
int InputInt(int* val);

/*!
 * \brief Считывает матрицу из консоли
 * \param[out] matrix матрица для считывания
 * \param[in] size размер матрицы для ввода
 * \return
 */
int InputMatrix(int** matrix, int size);

/*!
 * \brief Считывает размер создаваемой матрицы
 * \return значение размера
 */
int InputSize();

#endif