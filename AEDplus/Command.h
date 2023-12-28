#ifndef COMMAND_H
#define COMMAND_H

#include <QString>

/**
 * @brief The Command interface for AED actions
 *
 * This interface declares a method for executing AED functions.
 *
 * Each concrete implementation of this command will carry out
 * one of: powering on AED, powering off AED, delivering shock,
 * analyzing heart rhythm or providing CPR instructions
 *
 */

class Command {
public:
    virtual ~Command() = default; // virtual dtor for inheritable interface

    /**
     * @brief Execute the commands
     *
     * This is the primary method of the command pattern that
     * is to be implemented by all concrete command classes.
     * When called, it will execute the action that is encapsulated
     * by the commands.
     */
    virtual void execute() = 0;

    // determine if cmd can be executed (could be useful to deliverShock?)
    virtual bool canExecute() const = 0;

    // for debugging purposes
    virtual QString toString() const = 0;
};

#endif // COMMAND_H
