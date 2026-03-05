
// Classes/managers/UndoManager.h
#ifndef __UNDO_MANAGER_H__
#define __UNDO_MANAGER_H__

#include "../commands/ICommand.h"
#include <stack>
#include <memory>

class UndoManager {
public:
    // 执行并记录一个命令
    void executeCommand(std::shared_ptr<ICommand> command) {
        command->execute();         
        _commandStack.push(command); 
    }

    // 执行回退
    void undo() {
        if (_commandStack.empty()) return;

        auto command = _commandStack.top();
        command->undo(); 
        _commandStack.pop();
    }

    bool canUndo() const {
        return !_commandStack.empty();
    }

   
    void clear() {
        while (!_commandStack.empty()) {
            _commandStack.pop();
        }
    }

private:
    std::stack<std::shared_ptr<ICommand>> _commandStack;
};

#endif