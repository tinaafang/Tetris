#include <cstdlib>
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include "commandInterpreter.h"
using std::cin;
using std::cout;
using std::endl;

struct CommandInterpreterImpl
{
    std::string curCommand;
    int multiplier;
    std::vector<std::string> remainCommands;
    std::vector<std::string> commands;
    std::map<std::string, std::string> renameMap;
    std::map<std::string, std::vector<std::string>> macros;
};

bool CommandInterpreter::isDigit(char c)
{
    if (c >= '0' && c <= '9')
        return true;
    return false;
}

CommandInterpreter::~CommandInterpreter() {}

std::string CommandInterpreter::toString(int i)
{
    std::stringstream os;
    os << i;
    std::string s{};
    os >> s;
    return s;
}

int CommandInterpreter::toInt(std::string s)
{
    std::stringstream os;
    os << s;
    int i;
    os >> i;
    return i;
}

CommandInterpreter::CommandInterpreter(std::vector<std::string> commands)
{
    pImpl = std::make_unique<CommandInterpreterImpl>();
    pImpl->commands = commands;
}

std::string CommandInterpreter::isValid(std::string name, int multiplier)
{
    int duplicate = 0;
    int nameLen = name.length();
    std::string extCommand;
    // loop through the commands pool to see any of them matches the name
    for (auto it : pImpl->commands)
    {
        if (name == it)
        {
            // few commands do not need multiplier
            if (name == "restart" || name == "norandom" || name == "random" || name == "ENDGAME" || name == "done" || name == "heavy" || name == "force" || name == "blind" || name == "YES" || name == "NOPE")
            {
                return name;
            }
            return toString(multiplier) + name;
        }
    }
    // check if any head of the command equals to the current command
    for (auto it : pImpl->commands)
    {
        if (name == it.substr(0, nameLen))
        {
            ++duplicate;
            extCommand = it;
        }
    }
    // if no ambiguious meaning of the current command, return the command
    if (duplicate == 1)
        return toString(multiplier) + extCommand;
    return name;
}

void CommandInterpreter::rename()
{
    int commandInCommands = 0;
    int nameUsed = 0;
    std::string oldCommand;
    // read in the command name
    if (pImpl->remainCommands.size() != 0)
    {
        oldCommand = pImpl->remainCommands.front();
        pImpl->remainCommands.erase(pImpl->remainCommands.begin());
    }
    else
    {
        cin >> oldCommand;
    }
    // check if the command name is a valid command
    for (auto &it : pImpl->commands)
    {
        if (oldCommand == it)
        {
            commandInCommands = 1;
        }
    }
    // if it is, read the name used for renaming
    if (commandInCommands)
    {
        std::string name;
        if (pImpl->remainCommands.size() != 0)
        {
            name = pImpl->remainCommands.front();
            pImpl->remainCommands.erase(pImpl->remainCommands.begin());
        }
        else
        {
            cin >> name;
        }
        // check if the name is already used
        for (auto &p : pImpl->renameMap)
        {
            if (p.first == name && p.second != oldCommand)
            {
                nameUsed = 1;
            }
        }
        // if not used, create a new pair in renameMap
        if (!nameUsed)
        {
            pImpl->renameMap[name] = oldCommand;
        }
    }
}

void CommandInterpreter::addMacro()
{
    // read in the name of the macro
    std::string name, macroCommand;
    std::vector<std::string> macroCommands;
    if (pImpl->remainCommands.size() != 0)
    {
        name = pImpl->remainCommands.front();
        pImpl->remainCommands.erase(pImpl->remainCommands.begin());
    }
    else
    {
        cin >> name;
    }
    // read in the sequence of commands
    while (true)
    {
        if (pImpl->remainCommands.size() != 0)
        {
            macroCommand = pImpl->remainCommands.front();
            pImpl->remainCommands.erase(pImpl->remainCommands.begin());
        }
        else
        {
            cin >> macroCommand;
        }
        if (macroCommand == "done")
        {
            cout << "macro: " << name << " added" << endl;
            break;
        }
        macroCommands.emplace_back(macroCommand);
    }
    // add the new macro pair to macro map
    pImpl->macros[name] = macroCommands;
}

std::vector<std::string> CommandInterpreter::breakCommand(std::string command)
{
    std::vector<std::string> breakedCommand;
    std::string multiplier;
    int commandIndex = 0;
    if (isDigit(command[0]))
    {
        int len = command.length();
        for (int i = 0; i < len; ++i)
        {
            if (!isDigit(command[i]))
            {
                break;
            }
            ++commandIndex;
        }
        if (commandIndex >= len)
        {
            return breakedCommand;
        }
        multiplier = command.substr(0, commandIndex);
        command = command.substr(commandIndex, command.length() - commandIndex);
        breakedCommand.emplace_back(command);
        breakedCommand.emplace_back(multiplier);
        return breakedCommand;
    }
    breakedCommand.emplace_back(command);
    return breakedCommand;
}

std::string CommandInterpreter::getCommand()
{
    std::string command = "";
    int multiplier = 1;

    // if there is any remaining commands from previous actions, return them first
    if (pImpl->remainCommands.size() != 0)
    {
        std::string nextCommand = pImpl->remainCommands.front();
        pImpl->remainCommands.erase(pImpl->remainCommands.begin());
        std::vector<std::string> breakedCommand = breakCommand(nextCommand);
        if (breakedCommand.size() == 0)
        {
            return "";
        }
        else if (breakedCommand.size() == 1)
        {
            command = breakedCommand[0];
            multiplier = 1;
        }
        else
        {
            command = breakedCommand[0];
            multiplier = toInt(breakedCommand[1]);
            if (multiplier == 0) {
                multiplier = 1;
            }
        }
    }
    else
    {
        // read in the command
        cin >> command;
        // if eof, end the game
        if (cin.eof())
            return "ENDGAME";

        // check if a multiplier exists
        std::vector<std::string> brokeCommand = breakCommand(command);
        if (brokeCommand.size() == 0)
        {
            return "";
        }
        else if (brokeCommand.size() == 1)
        { // if size-one vector is return, it means there is no multiplier
            command = brokeCommand[0];
            multiplier = 1;
        }
        else
        {
            command = brokeCommand[0];
            multiplier = toInt(brokeCommand[1]);
            if (multiplier == 0) {
                multiplier = 1;
            }
        }
    }

    // rename, macro, and sequence command
    std::string renameCommand = "rename";
    std::string macroCommand = "macro";
    std::string seCommand = "sequence";
    std::string noRandCommand = "norandom";
    if ((command == renameCommand.substr(0, command.size()) && command.size() > 2))
    {
        rename();
    }
    else if (command == macroCommand.substr(0, command.size()))
    { // macro command
        addMacro();
    }
    else if (command == seCommand.substr(0, command.size()))
    { // sequence command
        std::string fileName;
        bool firstCommand = 0;
        std::string command1;
        std::vector<std::string> newRemainCommands;

        // read in the file name
        if (pImpl->remainCommands.size() != 0)
        {
            fileName = pImpl->remainCommands.front();
            pImpl->remainCommands.erase(pImpl->remainCommands.begin());
        }
        else
        {
            cin >> fileName;
        }
        std::ifstream infile{fileName};

        // read all commands in the file. Store the first command locally and store the other ones in remainCommands.
        while (infile >> command)
        {
            if (!firstCommand)
            {
                command1 = command;
                firstCommand = 1;
            }
            else
            {
                // if there are other remaining commands not executed, prioritize the current sequence commands
                newRemainCommands.emplace_back(command);
            }
        }

        std::vector<std::string> tmpNewRemainCommands = newRemainCommands;

        // if multiple sequences are called, add all of them to newRemainCommands
        for (int i = 1; i < multiplier; ++i)
        {
            tmpNewRemainCommands.emplace_back(command1);
            for (auto &it : newRemainCommands)
            {
                tmpNewRemainCommands.emplace_back(it);
            }
        }

        for (auto &it : pImpl->remainCommands)
        {
            tmpNewRemainCommands.emplace_back(it);
        }
        pImpl->remainCommands = tmpNewRemainCommands;

        // convert the command to the format of command + multiplier vector
        std::vector<std::string> breakedCommand = breakCommand(command1);
        // if no command is return, it means the command is composed of only number, hence not a valid command
        if (breakedCommand.size() == 0)
        {
            return "";
        }
        else if (breakedCommand.size() == 1)
        { // if size-one vector is return, it means there is no multiplier
            return isValid(breakedCommand[0], 1);
        }
        // if none of the above happens, it means its a command with a multiplier
        return isValid(breakedCommand[0], toInt(breakedCommand[1]));
    }
    else
    {
        // check if command is a rename of command
        for (auto const &p : pImpl->renameMap)
        {
            if (command == p.first)
            {
                cout << "Command applied was: " << p.first << ", "
                     << "a rename of " << p.second << endl;
                return isValid(p.second, multiplier);
            }
        }

        // check if command is the name of a macro
        std::string newCommand;
        std::vector<std::string> tmpMacro;
        std::vector<std::string> newRemainCommands;
        for (auto &p : pImpl->macros)
        {
            if (command == p.first)
            {
                // if command is the name of a macro, run the first command in the macro and store the rest in the remainCommands
                newCommand = pImpl->macros[command][0];
                tmpMacro = pImpl->macros[command];
                tmpMacro.erase(tmpMacro.begin());

                newRemainCommands = pImpl->macros[command];
                // if multiple macros are called, add all of them to newRemainCommands
                for (int i = 1; i < multiplier; ++i)
                {
                    for (auto &it : pImpl->macros[command])
                    {
                        newRemainCommands.emplace_back(it);
                    }
                }

                // if there are any commands left not executed from the previous actions, add them to the back of newRemainCommands
                for (auto &it : pImpl->remainCommands)
                {
                    newRemainCommands.emplace_back(it);
                }

                pImpl->remainCommands = newRemainCommands;

                // execute the first command
                std::vector<std::string> breakedCommand = breakCommand(newCommand);
                if (breakedCommand.size() == 0)
                {
                    return "";
                }
                else if (breakedCommand.size() == 1)
                {
                    return isValid(breakedCommand[0], 1);
                }
                return isValid(breakedCommand[0], toInt(breakedCommand[1]));
            }
        }
    }
    return isValid(command, multiplier);
}
