// Classes/commands/ICommand.h
#ifndef __I_COMMAND_H__
#define __I_COMMAND_H__

class ICommand {
public:
    virtual ~ICommand() {}
    virtual void execute() = 0; // 执行操作
    virtual void undo() = 0;    // 撤销操作
};

#endif