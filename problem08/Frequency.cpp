#include "Frequency.hpp"

#include <stdexcept>
#include <cmath>

// Default Constructor
Frequency::Frequency() {
    num_components = 301;
    increment = 0.1;
    zeros();
}

// Constructor with Arguments
Frequency::Frequency(int num_components_arg, double increment_arg)
    : num_components(num_components_arg), increment(increment_arg) {
    if (num_components <= 0 || num_components > MAX_COMPONENTS_NUM)
        throw std::invalid_argument("Invalid number of components.");
    if (increment <= 0)
        throw std::invalid_argument("Increment must be positive.");

    zeros();
}

// Accessors
int Frequency::get_component() const {
    return num_components;
}

double Frequency::get_increment() const {
    return increment;
}

// provided: assign zero amplitudes to frequencies
void Frequency::zeros() {
    for (int i = 0; i < num_components; i++)
    {
        freq_data[i].frequencies = static_cast<double>(i) * increment;
        freq_data[i].amplitudes = 0.0;
    }
}

// Assign constant amplitudes to all frequencies
void Frequency::constant(double val) {
    if (val < 0)
        throw std::invalid_argument("Amplitude value cannot be negative.");

    for (int i = 0; i < num_components; i++) {
        freq_data[i].frequencies = static_cast<double>(i) * increment;
        freq_data[i].amplitudes = val;
    }
}

// Gaussian build-up
void Frequency::gaussian(double A, double alpha) {
    if (A <= 0 || alpha <= 0)
        throw std::invalid_argument("Magnitude and width must be positive.");

    for (int i = 0; i < num_components; i++) {
        // Get current frequency
        double w = freq_data[i].frequencies;
        freq_data[i].amplitudes = A * std::sqrt(M_PI / alpha) * std::exp(- (w * w) / (4.0 * alpha));
    }
}

// == Equal to
bool Frequency::operator==(const Frequency &fcomp) const {
    // same increment and number of components required
    if (num_components != fcomp.num_components || increment != fcomp.increment)
        return false;

    // Compare each frequency and amplitude
    for (int i = 0; i < num_components; i++) {
        if (freq_data[i].frequencies != fcomp.freq_data[i].frequencies)
            return false;
        if (freq_data[i].amplitudes != fcomp.freq_data[i].amplitudes)
            return false;
    }
    return true;
}

// <= Less than or equal to
bool Frequency::operator<=(const Frequency &fcomp) const {
    // increments and component counts must match
    if (num_components != fcomp.num_components || increment != fcomp.increment)
        throw std::logic_error("Frequencies must have same increment and number of components.");

    for (int i = 0; i < num_components; i++) {
        if (freq_data[i].amplitudes > fcomp.freq_data[i].amplitudes)
            return false;
    }
    return true;
}

// >> Far greater than
bool Frequency::operator>>(const Frequency &fcomp) const {
    // Average power of current Frequency
    double power_current = 0.0;
    for (int i = 0; i < num_components; i++)
        power_current += freq_data[i].amplitudes * freq_data[i].amplitudes;
    power_current /= num_components;

    // Average power of argument Frequency
    double power_arg = 0.0;
    for (int i = 0; i < fcomp.num_components; i++)
        power_arg += fcomp.freq_data[i].amplitudes * fcomp.freq_data[i].amplitudes;
    power_arg /= fcomp.num_components;

    // 100× greater or more
    return power_current > 100.0 * power_arg;
}

// ^ Multiply
Frequency Frequency::operator^(const Frequency &fcomp) const {
    // Increments must match
    if (increment != fcomp.increment)
        throw std::logic_error("Cannot multiply with different increments.");

    // Determine which has more components
    int shorter = std::min(num_components, fcomp.num_components);
    int longer = std::max(num_components, fcomp.num_components);

    // Result takes the longer length
    Frequency result(longer, increment);

    // Multiply amplitudes up to the shorter one
    for (int i = 0; i < shorter; i++) {
        result.freq_data[i].frequencies = freq_data[i].frequencies;
        result.freq_data[i].amplitudes = freq_data[i].amplitudes * fcomp.freq_data[i].amplitudes;
    }

    // Zero the rest of amplitudes
    for (int i = shorter; i < longer; i++){
        result.freq_data[i].frequencies = static_cast<double>(i) * increment;
        result.freq_data[i].amplitudes = 0.0;
    }

    return result;
}

// provided: exports
void Frequency::export_frequency(double freq[], double amps[]) const {
    for (int i = 0; i < num_components; i++) {
        freq[i] = freq_data[i].frequencies;
        amps[i] = freq_data[i].amplitudes;
    }
}

bool Frequency::export_csv(const std::string &outfile) const {
    std::ofstream filewrite(outfile + ".csv");
    if (!filewrite.fail()) {
        filewrite << "w, |F(w)|" << std::endl;
        for (int i = 0; i < num_components; i++) {
            filewrite << freq_data[i].frequencies << ", " << freq_data[i].amplitudes << std::endl;
        }
        // Close file
        filewrite.close();
        return true;
    }
    return false;
}

void Frequency::Gated_Spectrum(double A, double Wa, double Wb){
    for (int i = 0; i < num_components; i++){
        double W = freq_data[i].frequencies;
        if (W >= Wa && W <= Wb)
            freq_data[i].amplitudes = A;
        else
            freq_data[i].amplitudes = 0;
    }
}