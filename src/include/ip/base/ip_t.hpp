#ifndef __IP_T_HH
#define __IP_T_HH

#include <string>
#include <vector>
#include "exceptions.hh"

namespace IP
{

    template <typename T>
    class IP
    {
    protected:
        T value;

    public:
        IP(T raw);
        IP(std::vector<uint8_t>);
        IP(std::string);

        T getValue();
        std::string toString(char _flags = 0000);

        template <typename U>
        friend bool operator<(const IP<U> &a, const IP<U> &b);
        template <typename U>
        friend bool operator>(const IP<U> &a, const IP<U> &b);
        template <typename U>
        friend bool operator==(const IP<U> &a, const IP<U> &b);

        friend IP<T> operator+(const IP<T> &derived, const T num) { return IP<T>(derived.value + num); }
        //  TODO: ADD-MASK operator
    };
    template <typename T>
    IP<T>::IP(T raw) { value = raw; }

    template <typename T>
    IP<T>::IP(std::vector<uint8_t>) { throw std::string("CTR not implemented yet"); }

    template <typename T>
    IP<T>::IP(std::string) { throw E_NoSpec(); }

    template <typename T>
    T IP<T>::getValue() { return value; }

    template <typename T>
    std::string IP<T>::toString(char _flags) { throw E_NoSpec(); }
    template <typename T>
    bool operator<(const IP<T> &a, const IP<T> &b) { return a.value < b.value; }
    template <typename T>
    bool operator>(const IP<T> &a, const IP<T> &b) { return a.value > b.value; }
    template <typename T>
    bool operator==(const IP<T> &a, const IP<T> &b) { return a.value == b.value; }

    template <typename T>
    IP<T> operator+(const IP<T> &base, const T num)
    {
        return IP<T>::IP(base.value + num);
    }

}

#endif