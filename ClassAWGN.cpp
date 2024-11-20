#include <vector>
#include <complex>
#include <random>

using namespace std;

class ClassAWGN {
private:
    default_random_engine generator;
    normal_distribution<double> noise;

public:
    ClassAWGN(double N0) : noise(0.0, sqrt(N0 / 2)) {}

    vector<complex<double> > addNoise(const vector<complex<double> > & signal) {
        vector<complex<double> > noised_signal(signal.size());
        for (int i = 0; i < signal.size(); i++) {
            double noise_real = noise(generator);
            double noise_imag = noise(generator);
            noised_signal[i] = signal[i] + complex<double>(noise_real, noise_imag);
        }
        return noised_signal;
    }
};