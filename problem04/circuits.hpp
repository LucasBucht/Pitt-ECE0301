#ifndef _CIRCUITS_HPP
#define _CIRCUITS_HPP

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstdlib>

#include <string>

void log_invalid_input()
{
    std:: cout << "Invalid input format." << std:: endl;
}

double get_value(std::string expr_string)
{
    int indexEquals = expr_string.find("=");
    int indexEquals2 = expr_string.find("=", indexEquals + 1);
    if (indexEquals == -1 || indexEquals2 != -1){
        return -1;
        }
    else{
        std:: string valueStr = expr_string.substr(indexEquals + 2);
        try{
            double value = std:: stod(valueStr);
            return value;
        }
        catch (...){
            return -1;
        }
    }
}

double get_current(double resistance, double power)
{
    double current;
    if (power < 0 || resistance < 0){
        return -1;
    }
    else
        current = pow((power/resistance), 0.5);
        return current;
}

double get_resistance(double current, double power)
{
    double resistance;
    if (power < 0 || current < 0){
        return -1;
    }
    else
        resistance = power / pow(current, 2);
        return resistance;
    
}

double get_power(double current, double resistance)
{
    double power;
    if (current < 0 || resistance < 0){
        return -1;
    }
    else
        power = pow(current, 2) * resistance;
        return power;
}

double get_divider_power(double source_power, double resistance1, double resistance2)
{
    double power2;
    if (source_power < 0 || resistance1 < 0 || resistance2 < 0){
        return -1;
    }
    else{
        power2 = source_power * (resistance2 / (resistance1 + resistance2));
        return power2;
    }
}

#endif