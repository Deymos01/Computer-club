# Computer-club

### Сборка проекта
Создайте директорию для сборки и перейдите в неё:
```
mkdir build
cd build
```
Запуск CMake для генерации Makefile:
```
cmake .. -G "MinGW Makefiles"
```
Соберите проект:
```
mingw32-make
```

### Запуск программы
Для запуска программы используйте следующую команду:
```
YADRO_task_computer_club ..\tests\{FILE_NAME}
```
