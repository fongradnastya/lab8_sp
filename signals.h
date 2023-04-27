/*! \file    signals.h
 *  \brief   Функции для работы с сигналами
 *
 *  \details Заголовочный файл, содержащий объявления функций 
 *   для обработки сигналов и настройки таймера
 */

#ifndef SIGNALS_H
#define SIGNALS_H

/*!
* \brief Обрабатывает разные виды сигналов
* \param[in] signum тип обрабатываемого сигнала
*/
void signalHandler(int signum);

/*!
* \brief Обрабатывает срабатывание таймера
*/
void timeoutHandler();

/*!
* \brief Открывает логгинг файл для дозаписи 
* \param[in] logFileName имя файла для открытия
* \return дескриптор логгинг файла
*/
FILE* openLogFile(char* logFileName);

/*!
* \brief Записывает сообщение в лог файл
* \param[in] logfd дескриптор файла
* \param[in] format формат сообщения
*/
void writeLog(FILE* logfd, const char* format, ...);

/*!
* \brief Устанавливает таймер на заданное время
* \param[in] timeout число секунд для ожидания
*/
void setTimer(int timeout);

#endif