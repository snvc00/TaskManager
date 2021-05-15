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

class Task {
private:
    short id;
    unsigned int start;
    unsigned int duration;
public:
    Task() : id(0), start(0U), duration(0U) {}
    Task(const short& _id, const unsigned int& _start, const unsigned int& _duration)
        : id(_id), start(_start), duration(_duration) {}

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

    unsigned int getGlobalTime() {
        return start + duration;
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
unsigned int inputUnsignedInt(const std::string& message = "Ingrese un numero: ");
Task inputTask(const short id);

// Declarations: Handlers
void handleStartInputTask();

int main()
{
    bool endApplication = false;
    std::string input;
    unsigned int option = 0U, start = 0U, duration = 0U;

    try
    {
        do
        {
            system("cls");
            printTeamInfo();
            printMainMenu();
            option = inputUnsignedInt("Ingresa el numero de opcion: ");

            if (option == Options::START_INPUT_TASK) {
                handleStartInputTask();
            }
            else if (option == Options::EXIT_APPLICATION) {
                std::cout << "\nSaliendo de la aplicacion\n";
                endApplication = true;
            }
            else {
                std::cout << "\nOpcion invalida\n";
                system("pause");
            } 

        } while (!endApplication);
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    
    system("pause");
}

// Definitions: Functions to pretty print common text

void printMainMenu() {
    std::cout << "Administrador de Tareas\n\n"
        << "1. Ingresar tareas\n"
        << "2. Salir\n\n";
}

void printTeamInfo() {
    std::cout << "Actividad 9 (Examen)\n"
        "\tComputacion Tolerante a Fallas\n"
        "\tCampos Alpizar Alejandro, Seccion D01\n"
        "\tMedina Davila Jonathan Eslavi, Seccion D01\n"
        "\tRuiz Gutierrez Daniel de la Cruz, Seccion D01\n"
        "\tTorres Sebastian Erick Alejandro, Seccion D01\n"
        "\tValle Contreras Santiago Nicolas, Seccion D01\n\n";
}


// Definitions: Input helpers

unsigned int inputUnsignedInt(const std::string& message) {
    std::string input;
    int result = 0;

    std::cout << "[ENTRADAS MENORES A 0 SE CONVIERTEN A 0] " << message;
    std::getline(std::cin, input);

    result = std::atoi(input.c_str());
    
    return result < 0 ? 0U : (unsigned int)result;
}

Task inputTask(const short id) {
    unsigned int start, duration, newMaxDuration;
    char confirmation;
    bool userWantsToContinue = true;

    std::cout << "\n-----\n";
    std::cout << "*Entrada con autoajuste al rango valido [" << Settings::MIN_START << ", " << Settings::MAX_START << "]\n";
    start = inputUnsignedInt("Ingrese inicio: ");

    if (start < Settings::MIN_START) {
        start = Settings::MIN_START;
    }

    if (start > Settings::MAX_START) {
        start = Settings::MAX_START;
    }

    newMaxDuration = Settings::MAX_GLOBAL_TIME - start;

    std::cout << "\n*Entrada con autoajuste al rango valido [" << Settings::MIN_DURATION << ", " << newMaxDuration << "]\n";
    duration = inputUnsignedInt("Ingrese duracion: ");

    if (duration < Settings::MIN_DURATION) {
        duration = Settings::MIN_DURATION;
    }

    if (duration > newMaxDuration) {
        duration = newMaxDuration;
    }
    std::cout << "-----\n";

    return Task(id, start, duration);
}


// Definitions: Handlers

void handleStartInputTask() {
    system("cls");
    printTeamInfo();

    unsigned int totalTasks;
    Task task;
    std::vector<Task> taskList;

    std::cout << "\n*Entrada con autoajuste al rango valido [" << Settings::MIN_TASK_INPUT << ", " << Settings::MAX_TASK_INPUT << "]\n";
    totalTasks = inputUnsignedInt("Ingrese total de tareas: ");

    if (totalTasks < Settings::MIN_TASK_INPUT) {
        totalTasks = Settings::MIN_TASK_INPUT;
    }

    if (totalTasks > Settings::MAX_TASK_INPUT) {
        totalTasks = Settings::MAX_TASK_INPUT;
    }

    for (int i = 0; i < totalTasks; ++i) {
        task = inputTask((short)i);
        taskList.emplace_back(task);
    }
    
    std::cout << "\n\n\n";
    for (int i = 0; i < taskList.size(); ++i) {
        std::cout << taskList[i].toString() << std::endl;
    }

    system("pause");
}
