#pragma once

#define TIME_IF 1 // Время для дешифрации
#define TIME_REG_ACCESS 1 // Время для доступа к регистру
#define CHANCE_P1 6 // Вероятность того, что второй операнд будет в регистре. P1(0.9; 0.8; 0.6)
#define TIME_MEM_ACCESS 5 // Время для доступа к памяти. N(2, 5, 10)
#define CHANCE_P2 5 // Вероятность того, что команда является командой 1ого типа. P2(0.9; 0.7; 0.5)
#define TIME_EX_1 1 // Время для выполнения команды 1ого типа
#define TIME_EX_2 8 // Время для выполнения команды 2ого типа
#define INF 2147483646

#include <random>
#include <vector>
#include <algorithm>

namespace smd 
{
    int calculateRandom();

    enum class Stages {IF, OR1, OR2, EX, WB};

    class Command
    {
    public:
        Command();

        int get_currentStage();
        int get_timeIf();
        int get_timeOr1();
        int get_timeOr2();
        int get_timeEx();
        int get_timeWb();

        void set_currentStage(int stage);
    private:
        int stages[5];
        int currentStage = 0;
        bool isCompleted = false;

        int calculateIf();
        int calculateOr1();
        int calculateOr2();
        int calculateEx();
        int calculateWb();
    };

    float calculateAverageTime(int commandCount);
}