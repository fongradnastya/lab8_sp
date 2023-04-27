# Практическая работа №8. Безопасность системных программ

Восьмая практическая работа по дисциплине Системное программирование

## Цель работы

Исследование вопросов безопасности в GNU/Linux.

## Задачи

1. Ознакомиться с теоретическими сведениями по проблеме обеспечения информационной безопасности в ОС GNU/Linux.
2. Модифицировать результаты выполнения ЛР 7 добавлением использования программных средств обеспечения информационной безопасности в ОС GNU/Linux.
3. Обеспечить сборку обеих частей программы, как отдельно, так и полностью, с использованием инструментального набора GNU Autotools. Серверная часть должна запускаться только привилегированным пользователем, а клиентская часть для передачи сообщений должна пройти процедуру аутентификации с использованием библиотеки PAM (Pluggable Authentication Modules).
4. Используя изученные механизмы, разработать и отладить серверную и клиентскую части приложения.
5. Составить общее описание результатов, инструкции по сборке и использованию программы, а также инструкцию по получению документации, сформировать архив формата tar.gz и представить на проверку с исходными текстами программы. Исходные тексты программ должны соответствовать принятому стандарту кодирования, а также содержать комментарии в стиле системы Doxygen.

## Вариант задания

Вариант 22.
Клиент принимает от пользователя целочисленную квадратнуюматрицу и отсылает ее серверу.Сервер принимает целочисленную квадратную матрицу, после этогозаменяет строку с минимальным элементом нулями, а затем  удаляет  путемперемещения   элементов  столбец   с   максимальным   элементом.   На   экранвыводится результирующая матрица, номера модифицированной строки иудаленного столбца.
