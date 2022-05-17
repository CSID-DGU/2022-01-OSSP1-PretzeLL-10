#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <stack>
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>


#ifdef __APPLE__
    #if COCOS2D_DEBUG > 0
        #define IF(x)       if(x) { Error::insert(__FILE_NAME__, __LINE__, typeid(this).name(), __func__   );               return false;   }
        #define IF_RV(x,y)  if(x) { Error::insert(__FILE_NAME__, __LINE__, typeid(this).name(), __func__, y); endProgram(); return;         }
        #define IF_RF(x,y)  if(x) { Error::insert(__FILE_NAME__, __LINE__, typeid(this).name(), __func__, y); endProgram(); return false;   }
        #define IF_RN(x,y)  if(x) { Error::insert(__FILE_NAME__, __LINE__, typeid(this).name(), __func__, y); endProgram(); return nullptr; }
    #else
        #define IF(x)       if(x) { return false;                 }
        #define IF_RV(x,y)  if(x) { endProgram(); return;         }
        #define IF_RF(x,y)  if(x) { endProgram(); return false;   }
        #define IF_RN(x,y)  if(x) { endProgram(); return nullptr; }
    #endif
#else
    #if COCOS2D_DEBUG > 0
        #define IF(x)       if(x) { Error::insert(__FILE__,      __LINE__, typeid(this).name(), __func__   );               return false;   }
        #define IF_RV(x,y)  if(x) { Error::insert(__FILE__,      __LINE__, typeid(this).name(), __func__, y); endProgram(); return;         }
        #define IF_RF(x,y)  if(x) { Error::insert(__FILE__,      __LINE__, typeid(this).name(), __func__, y); endProgram(); return false;   }
        #define IF_RN(x,y)  if(x) { Error::insert(__FILE__,      __LINE__, typeid(this).name(), __func__, y); endProgram(); return nullptr; }
    #else
        #define IF(x)       if(x) { return false;                 }
        #define IF_RV(x,y)  if(x) { endProgram(); return;         }
        #define IF_RF(x,y)  if(x) { endProgram(); return false;   }
        #define IF_RN(x,y)  if(x) { endProgram(); return nullptr; }
    #endif
#endif


class Error {
private:
    static std::stack<std::string> __err;
    
public:
    static bool empty();
    static void insert(std::string file,
                       int         line,
                       std::string name,
                       std::string func,
                       std::string reason = "", ...);
    static void traceBack();
};

#endif /* __DEBUG_H__ */
