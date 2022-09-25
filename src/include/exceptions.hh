#ifndef __EXCEPTIONS_HH
#define __EXCEPTIONS_HH

#include <exception>

class E_NoSpec : public std::exception
{
public:
    using std::exception::what;
    const char *what() 
    {
        return "NoSpec: This method has no generic body, it can be only used with the specialized templates.";
    }
};

class E_TODO : public std::exception
{
public:
    using std::exception::what;
    const char *what() 
    {
        return "TODO: This method is not implemented yet.";
    }
};

#endif
