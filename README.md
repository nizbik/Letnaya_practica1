Настройка проекта для сборки в студии (выполняем команды в консоли в директории проекта):
> mkdir build
> cd build
> cmake -S .. -G "Visual Studio 17 2022" -A Win32 -DN=1024


Сборка проекта:
> cmake --build . --config Release
> cmake --build . --config Debug

Запуск программы:
После сборки исполняемый файл letmaya_practica_1.exe находится в каталоге build\app\Release (или build\app\Debug).

Синтаксис запуска:
> build\app\Release\letnaya_practica_1.exe <входной_файл> <выходной_файл> <паттерн_HEX> <замена_HEX>

Пример (замена "ad" на "12345"):
> build\app\Release\letnaya_practica_1.exe input.txt output.txt 6164 3132333435