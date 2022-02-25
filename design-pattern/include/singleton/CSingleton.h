
#include <iostream>

class CSingleton {
public:
    static CSingleton& getInstance();

private:
    CSingleton();
    ~CSingleton();

    static CSingleton m_Instance;
    bool m_flags;
};

