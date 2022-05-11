#include "Debug.h"


std::stack<std::string> Error::__err = std::stack<std::string>();

bool Error::empty() {
    return __err.empty();
}

void Error::insert(std::string file,
                   int         line,
                   std::string name,
                   std::string func,
                   std::string reason, ...) {
    std::string __e;
    if (!file.empty())      __e.append(file);
    if (line)               __e.append("::").append(std::to_string(line));
    if (!name.empty())      __e.append("::").append(name);
    if (!func.empty())      __e.append("::").append(func);
    if (!reason.empty())    __e.append(": ").append(reason);
    __err.push(__e);
}

void Error::traceBack() {
    std::cout << "ERROR OCCURRED!\n\n";
    std::cout << "TRACEBACK :\n";
    while (!__err.empty()) {
        std::cout << __err.top() << std::endl;
        __err.pop();
    }
    std::cout << "\n\n";
}
