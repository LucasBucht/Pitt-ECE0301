#include <cstdlib>
#include <iostream>
#include <iomanip>

int main(int argc, char *argv[]){
    // Declare variables
    double resistance = 1000.0, voltage;
    // Check if at least one argument is provided
    if (argc > 1) { 
        resistance = atof(argv[1]); // Assign the first argument to resistance
    }
    // Check if resistance is positive
    if (resistance <= 0){
        std:: cout << "Invalid resistance, must be positive." << std:: endl;
        return EXIT_FAILURE;
    }

    // Ask for voltage value
    std:: cout << "Enter voltage: " << std:: endl;
    std:: cin >> voltage;

    // Check if voltage is positive
    if (voltage <= 0){
        std:: cout << "Invalid voltage, must be positive." << std:: endl;
        return EXIT_FAILURE;
    }
    else{
    std:: cout << std:: fixed << std:: setprecision(3) << "If R = " << resistance << " Ohms and V = " << voltage << " Volts, then I =  " << voltage/resistance << " Amps" << std:: endl;
    return EXIT_SUCCESS;
    }
}
