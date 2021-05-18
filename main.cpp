/*
*	Actividad 9 (Examen)
*	Computacion Tolerante a Fallas
*
*	Campos Alpizar Alejandro, Seccion D01
*	Medina Davila Jonathan Eslavi, Seccion D01
*	Ruiz Gutierrez Daniel de la Cruz, Seccion D01
*	Torres Sebastian Erick Alejandro, Seccion D01
*	Valle Contreras Santiago Nicolas, Seccion D01
*
*   IMPORTANTE: Instrucciones de compilacion,
*
*   LLENAR ESTO AL FINAL
*
*/

#include <iostream>
#include <sstream>
#include <vector>
#include <windows.h>

#include "painter.h"

class Task {
private:
    short id;
    unsigned int start;
    unsigned int duration;
    unsigned int globalTime;
    bool finished;
public:
    Task() : id(0), start(0U), duration(0U), globalTime(0U), finished(false) {}
    Task(const short& _id, const unsigned int& _start, const unsigned int& _duration)
        : id(_id), start(_start), duration(_duration), globalTime(0U), finished(false) {}

    void setId(const short int& _id) {
        this->id = _id;
    }

    short getId() {
        return this->id;
    }

    void setStart(const unsigned int& _start) {
        this->start = _start;
    }

    unsigned int getStart() {
        return this->start;
    }

    void setDuration(const unsigned int& _duration) {
        this->duration = _duration;
    }

    unsigned int getDuration() {
        return this->duration;
    }

    void setGlobalTime(const unsigned int& _globalTime) {
        this->globalTime=_globalTime;
    }

    unsigned int getGlobalTime() {
        return globalTime;
    }

    void setFinished() {
        finished=true;
    }

    bool getFinished() {
        return finished;
    }

    std::string toString() {
        std::stringstream task;
        task << "Id: " << this->id
            << ", Inicio: " << this->start
            << ", Duracion: " << this->duration
            << ", Tiempo Global: " << this->getGlobalTime();

        return task.str();
    }
};

enum Settings {
    MIN_TASK_INPUT = 1U,
    MAX_TASK_INPUT = 10U,
    MAX_GLOBAL_TIME = 100U,
    MIN_START = 0U,
    MAX_START = MAX_GLOBAL_TIME - 1,
    MIN_DURATION = 1U,
    MAX_DURATION = MAX_GLOBAL_TIME,
};

enum Options {
    START_INPUT_TASK = 1U,
    EXIT_APPLICATION = 2U
};

// Declarations: Functions to pretty print common text
void printMainMenu();
void printTeamInfo();

// Declarations: Input helpers
unsigned int inputUnsignedInt(const std::string& message = "Ingrese un numero -> ", const int& x=4, const int &y=16);
Task inputTask(const short id, const int& x, const int &y);

// Declarations: Handlers
void handleStartInputTask();

/// Declarations: Color prints
void printTitle(const std::string& msg, const int& color, const int& x, const int &y);
void printGraphics(std::vector<Task> taskList);

int main()
{
    system("Color f0");
    bool endApplication = false;
    std::string input;
    unsigned int option = 0U, start = 0U, duration = 0U;

    HWND console = GetConsoleWindow();
    RECT rectangle;
    GetWindowRect(console, &rectangle);
    MoveWindow(console, rectangle.left, rectangle.top, 215 * 9, 54 * 20, TRUE);

    try
    {
        do
        {
            system("cls");
            drawWindow(52,211,7,0,0);
            printTeamInfo();
            printMainMenu();
            option = inputUnsignedInt("Ingresa el numero de opcion -> ", 4, 19);

            if (option == Options::START_INPUT_TASK) {
                handleStartInputTask();
            }
            else if (option == Options::EXIT_APPLICATION) {
                gotoxy(4,22);
                std::cout << "Saliendo de la aplicacion...";
                endApplication = true;
                gotoxy(0,54);
            }
            else {
                gotoxy(4,22);
                std::cout << "Opcion invalida.";
                gotoxy(4,23);
                system("pause");
            }

        } while (!endApplication);
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

// Definitions: Functions to pretty print common text

void printMainMenu() {
    printTitle("Administrador de Tareas", BLUE, 4, 14);
    gotoxy(6,16);
    std::cout << "1. Ingresar tareas\n";
    gotoxy(6,17);
    std::cout << "2. Salir\n\n";
}

void printTeamInfo() {
    printTitle("Actividad 9 (Examen)\n", BLUE,4,2);
    printTitle("\tComputacion Tolerante a Fallas", LBLUE, 4, 4);
    gotoxy(4,6);
    textColor(WHITE, GREEN);
    std::cout << "\tCampos Alpizar Alejandro"; textColor(WHITE, LGREEN); std::cout << ", Seccion D01\n";
    textColor(WHITE, GREEN);
    std::cout << "\tMedina Davila Jonathan Eslavi"; textColor(WHITE, LGREEN); std::cout << ", Seccion D01\n";
    textColor(WHITE, GREEN);
    std::cout << "\tRuiz Gutierrez Daniel de la Cruz"; textColor(WHITE, LGREEN); std::cout << ", Seccion D01\n";
    textColor(WHITE, GREEN);
    std::cout << "\tTorres Sebastian Erick Alejandro"; textColor(WHITE, LGREEN); std::cout << ", Seccion D01\n";
    textColor(WHITE, GREEN);
    std::cout << "\tValle Contreras Santiago Nicolas"; textColor(WHITE, LGREEN); std::cout << ", Seccion D01\n";
    textColor(DEFAULT_COLOR);
}


// Definitions: Input helpers

unsigned int inputUnsignedInt(const std::string& message, const int& x, const int &y) {
    std::string input;
    int result = 0;

    gotoxy(x, y);
    textColor(WHITE, LBLUE);
    std::cout << "[ENTRADAS MENORES A 0 SE CONVIERTEN A 0] ";
    textColor(DEFAULT_COLOR);
    gotoxy(x, y+1);
    std::cout<< message;
    std::getline(std::cin, input);

    result = std::atoi(input.c_str());

    return result < 0 ? 0U : (unsigned int)result;
}

Task inputTask(const short id, const int& x, const int &y) {
    system("cls");
    drawWindow(52,211,7,0,0);
    printTeamInfo();
    unsigned int start, duration, newMaxDuration;
    char confirmation;
    bool userWantsToContinue = true;
    gotoxy(x,y);
    textColor(WHITE, MAGENTA);
    std::cout << "*Entrada con autoajuste al rango valido";
    textColor(WHITE, LMAGENTA);
    std::cout << " [" << Settings::MIN_START << ", " << Settings::MAX_START << "]\n";
    start = inputUnsignedInt("Ingrese inicio -> ", x, y+2);

    if (start < Settings::MIN_START) {
        start = Settings::MIN_START;
    }

    if (start > Settings::MAX_START) {
        start = Settings::MAX_START;
    }

    newMaxDuration = Settings::MAX_GLOBAL_TIME - start;

    gotoxy(x,y+5);
    textColor(WHITE, MAGENTA);
    std::cout << "*Entrada con autoajuste al rango valido";
    textColor(WHITE, LMAGENTA);
    std::cout << " [" << Settings::MIN_DURATION << ", " << newMaxDuration << "]\n";
    duration = inputUnsignedInt("Ingrese duracion -> ", x, y+7);

    if (duration < Settings::MIN_DURATION) {
        duration = Settings::MIN_DURATION;
    }

    if (duration > newMaxDuration) {
        duration = newMaxDuration;
    }

    return Task(id, start, duration);
}


// Definitions: Handlers

void handleStartInputTask() {
    system("cls");
    drawWindow(52,211,7,0,0);
    printTeamInfo();

    unsigned int totalTasks;
    Task task;
    std::vector<Task> taskList;

    gotoxy(4,13);
    textColor(WHITE, MAGENTA);
    std::cout << "*Entrada con autoajuste al rango valido";
    textColor(WHITE, LMAGENTA);
    std::cout << " [" << Settings::MIN_TASK_INPUT << ", " << Settings::MAX_TASK_INPUT << "]\n";
    totalTasks = inputUnsignedInt("Ingrese total de tareas -> ", 4, 15);

    if (totalTasks < Settings::MIN_TASK_INPUT) {
        totalTasks = Settings::MIN_TASK_INPUT;
    }

    if (totalTasks > Settings::MAX_TASK_INPUT) {
        totalTasks = Settings::MAX_TASK_INPUT;
    }

    for (int i = 0; i < totalTasks; ++i) {
        task = inputTask((short)i, 4,13);
        taskList.emplace_back(task);
    }

    printGraphics(taskList);
}

///Definitions: Color prints

void printTitle(const std::string& msg, const int& color, const int& x, const int &y) {
    gotoxy(x,y);
    textColor(WHITE, color);
    std::cout << msg;
    textColor(DEFAULT_COLOR);
}

void printGraphics(std::vector<Task> taskList){
    system("cls");
    drawWindow(52,211,7,0,0);
    printTeamInfo();
    unsigned int color(1), x(10), y(13), prossesTime(0), sizeControl(30/taskList.size());
    bool allFinished(false);
    drawWindow(36, 60, LGREY, x, y);        ///Data
    drawWindow(36, 110, LGREY, x+60, y);    ///Graphic
    drawWindow(31,1,LGREY, x+64, y+2);      ///VLine
    drawWindow(1,101,LGREY, x+64, y+32);      ///HLine

    for (int i(0); i<=10; ++i) {
        gotoxy(x+65+(i*10), y+33);
        std::cout << i*10;
    }

    x+=2;
    while(!allFinished) {
        allFinished=true;
        for (int i = 0; i < taskList.size(); ++i) {
            y=15+(taskList[i].getId()*sizeControl);
            gotoxy(x,y);
            std::cout << taskList[i].toString() << std::endl;
            if (!taskList[i].getFinished()) {
                allFinished=false;
                if (taskList[i].getStart() <= prossesTime && prossesTime < (taskList[i].getDuration()+taskList[i].getStart())) {
                    for (int j(0); j<sizeControl; ++j) {
                        gotoxy(x+63+prossesTime, y+j);
                        textColor(taskList[i].getId()+1,taskList[i].getId()+1);
                        std::cout << " ";
                        textColor(DEFAULT_COLOR);
                    }
                } else if(taskList[i].getStart() <= prossesTime){
                    taskList[i].setFinished();
                }
            }
            if (!taskList[i].getFinished()) {
                taskList[i].setGlobalTime(prossesTime+1);
            }
        }
        std::cout.flush();
        Sleep(100);
        prossesTime++;
    }
    gotoxy(x, 46);
    system("pause");
}
