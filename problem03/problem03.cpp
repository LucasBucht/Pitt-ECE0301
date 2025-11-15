#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstdlib>

int main(int argc, char *argv[]) {
    // Declare Variables
    double R, I, P;
    bool isR, isI, isP;
    std:: string input_file = "../input.txt";
    std:: string output_file ="../output.txt";
    
    // Check Arguments Entered in CLI
    if (argc > 3){
        std:: cout << "Invalid input format.";
        return EXIT_FAILURE;
    }
    if (argc == 3){
        input_file = argv[1];
        output_file = argv[2];
    }
    else if (argc == 2){
        input_file = argv[1];
    }

    // Set Files to Open and Read/Write to
    std::ifstream file_read(input_file);
    if (file_read.fail()) {
        std::cout << "Input file error" << std::endl;
        return EXIT_FAILURE;
    }
    std::ofstream file_write(output_file);
    if (file_write.fail()) {
        std::cout << "Output file error" << std::endl;
        return EXIT_FAILURE;
    }

    std::string line;

    // While there are more lines to check
    while(getline(file_read, line)){
        // Reset Values
        isR = false;
        isI = false;
        isP = false;
        R = 0;
        I = 0;
        P = 0;

        // Find indexes of R, I, P, and the comma
        int indexR = line.find("R = ");
        int indexI = line.find("I = ");
        int indexP = line.find("P = ");
        int indexComma = line.find(",");
        int indexComma2 = line.find(",", indexComma + 1);

        // If no comma, return error
        if (indexComma == -1){
            std:: cout << "Invalid input format." << std:: endl;
            file_read.close();
            file_write.close();
            return EXIT_FAILURE;
        }

        // Check if TWO commas
        if (indexComma2 != -1){
            std:: cout << "Invalid input format." << std:: endl;
            file_read.close();
            file_write.close();
            return EXIT_FAILURE;
        }

        // Try to run the file valuation
        try {
        // Find the value of R
            if(indexR != -1){
                if(indexR > indexComma){
                    std:: string valueR = line.substr(indexR + 4);
                    R = std:: stod(valueR);
                }
                else{
                    std:: string valueR = line.substr(indexR + 4, indexComma - (indexR + 4));
                    R = std:: stod(valueR);
                }
                isR = true;
            }
            // Find the value of I
            if(indexI != -1){
                if(indexI > indexComma){
                    std:: string valueI = line.substr(indexI + 4);
                    I = std:: stod(valueI);
                }
                else{
                    std:: string valueI = line.substr(indexI + 4, indexComma - (indexI + 4));
                    I = std:: stod(valueI);
                }
                isI = true;
            }
            // Find the value of P
            if(indexP != -1){
                if(indexP > indexComma){
                    std:: string valueP = line.substr(indexP + 4);
                    P = std:: stod(valueP);
                }
                else{
                    std:: string valueP = line.substr(indexP + 4, indexComma - (indexP + 4));
                    P = std:: stod(valueP);
                }
                isP = true;
            }
            // If an error is found...
        } catch(...){
            /// Run this
            std:: cout << "Invalid input format." << std:: endl;
            file_read.close();
            file_write.close();
            return EXIT_FAILURE;
        }

        // Find P
        if (isR && isI){
            P = pow(I, 2) * R;
            if (indexI < indexR){
                file_write << std:: fixed << std:: setprecision(3) << "If I = " << I << " Amps and R = " << R << " Ohms, then P = " << P << " Watts." << std:: endl;
            }
            else{
                file_write << std:: fixed << std:: setprecision(3) << "If R = " << R << " Ohms and I = " << I << " Amps, then P = " << P << " Watts." << std:: endl;
            }
        }
        // Find R
        else if (isI && isP){
            R = P / pow(I, 2);
            if (indexI < indexP){
                file_write << std:: fixed << std:: setprecision(3) << "If I = " << I << " Amps and P = " << P << " Watts, then R = " << R << " Ohms." << std:: endl;
            }
            else{
                file_write << std:: fixed << std:: setprecision(3) << "If P = " << P << " Watts and I = " << I << " Amps, then R = " << R << " Ohms." << std:: endl;
            }
        }
        // Find I
        else if (isR && isP){
            I = pow((P/R), 0.5);
            if (indexP < indexR){
                file_write << std:: fixed << std:: setprecision(3) << "If P = " << P << " Watts and R = " << R << " Ohms, then I = " << I << " Amps." << std:: endl;
            }
            else{
                file_write << std:: fixed << std:: setprecision(3) << "If R = " << R << " Ohms and P = " << P << " Watts, then I = " << I << " Amps." << std:: endl;
            }
        }
        // Return an error if something is wrong
        else{
            std:: cout << "Invalid input format." << std:: endl;;
            file_read.close();
            file_write.close();
            return EXIT_FAILURE;
        }
    }

    // Close files and return 0
    file_read.close();
    file_write.close();
    return EXIT_SUCCESS;
}
