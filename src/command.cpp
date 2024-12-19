#include "command.h"

namespace smd
{
    int calculateRandom()
    {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist10(1,10); // distribution in range [1, 6]

        return dist10(rng);
    }

    int Command::calculateIf()
    {
        return TIME_IF;
    }

    int Command::calculateOr1()
    {
        return TIME_REG_ACCESS;
    }

    int Command::calculateOr2()
    {
        if (calculateRandom() <= CHANCE_P1)
        {
            return TIME_REG_ACCESS;
        }
        else
        {
            return TIME_MEM_ACCESS;
        }
    }

    int Command::calculateEx()
    {
        if (calculateRandom() <= CHANCE_P2)
        {
            return TIME_EX_1;
        }
        else
        {
            return TIME_EX_2;
        }
    }

    int Command::calculateWb()
    {
        return stages[2];
    }

    Command::Command()
    {
        stages[0] = calculateIf();
        stages[1] = calculateOr1();
        stages[2] = calculateOr2();
        stages[3] = calculateEx();
        stages[4] = calculateWb();
    }

    int Command::get_currentStage()
    {
        return currentStage;
    }

    int Command::get_timeIf()
    {
        return stages[0];
    }

    int Command::get_timeOr1()
    {
        return stages[1];
    }

    int Command::get_timeOr2()
    {
        return stages[2];
    }

    int Command::get_timeEx()
    {
        return stages[3];
    }

    int Command::get_timeWb()
    {
        return stages[4];
    }

    void Command::set_currentStage(int stage)
    {
        currentStage = stage;
    }

    float calculateAverageTime(int commandCount)
    {
        std::vector<Command> commands(commandCount);
        int totalTime = 0;
        int timeToAdd = -1;
        bool state_or_wb = false;
        int completedCommands = 0;
        int tmp = 0;

        while (true)
        {
            int i = 0;
            for (; i < commandCount; ++i)
            {
                if (commands[i].get_currentStage() != 5)
                {
                    switch (commands[i].get_currentStage())
                    {
                    case static_cast<int>(smd::Stages::WB):
                        timeToAdd = std::max(commands[i].get_timeWb(), timeToAdd);
                        state_or_wb = true;
                        ++completedCommands;
                        commands[i].set_currentStage(commands[i].get_currentStage() + 1);
                        break;
                    case static_cast<int>(smd::Stages::EX):
                        timeToAdd = std::max(commands[i].get_timeEx(), timeToAdd);
                        commands[i].set_currentStage(commands[i].get_currentStage() + 1);
                        break;
                    case static_cast<int>(smd::Stages::OR2):
                        if (!state_or_wb)
                        {
                            timeToAdd = std::max(commands[i].get_timeOr2(), timeToAdd);
                            state_or_wb = true;
                            commands[i].set_currentStage(commands[i].get_currentStage() + 1);
                        } 
                        break;
                    case static_cast<int>(smd::Stages::OR1):
                        if (!state_or_wb)
                        {
                            timeToAdd = std::max(commands[i].get_timeOr1(), timeToAdd);
                            state_or_wb = true;
                            commands[i].set_currentStage(commands[i].get_currentStage() + 1);
                        }
                        break;
                    case static_cast<int>(smd::Stages::IF): 
                        timeToAdd = std::max(commands[i].get_timeIf(), timeToAdd);
                        commands[i].set_currentStage(commands[i].get_currentStage() + 1);
                        i = INF;
                        break;
                    default:
                        break;
                    }
                }
            }
            state_or_wb = false;
            totalTime += timeToAdd;
            if (completedCommands == commandCount)
                break;
        }

        return static_cast<float>(totalTime) / commandCount;
    }
}