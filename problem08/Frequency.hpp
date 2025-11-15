#ifndef _FREQUENCY_HPP
#define _FREQUENCY_HPP

#include <fstream>

class Frequency {
public:
    // provided: max components
    static const int MAX_COMPONENTS_NUM = 1001;

    // Default constructor and constructor with args
    Frequency();
    Frequency(int num_components, double increment);

    // Accessors
    int get_component() const;
    double get_increment() const;

    // provided: assign zero amplitudes to all frequencies
    void zeros();

    // Assign constant amplitudes to all frequencies
    void constant(double val);

    // Gaussian
    void gaussian(double A, double alpha);

    // Overloaded operators (==, <=, >>, ^)
    bool operator==(const Frequency &fcomp) const; // first one looks like such
    bool operator<=(const Frequency &fcomp) const;
    bool operator>>(const Frequency &fcomp) const;
    Frequency operator^(const Frequency &fcomp) const;


    // provided: exports
    void export_frequency(double freq[], double amps[]) const;
    bool export_csv(const std::string &outfile) const;

    // Checkoff
    void Frequency::Gated_Spectrum(double, double, double);


private:
    // provided: Cpnt struct, private members
    struct Cpnt {
        double frequencies;
        double amplitudes;
    };

    int num_components;
    double increment;
    Cpnt freq_data[MAX_COMPONENTS_NUM];
};

#endif