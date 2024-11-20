#include <vector>
#include <complex>

using namespace std;

class ClassQAMDemod {
private:
    int M;

public:
    ClassQAMDemod(int M) : M(M) {}

    vector<int> demodulate(const vector<complex<double> > & recieved_symbols) {
        int Ns = recieved_symbols.size();
        vector<int> received_bits(Ns * log2(M));
        if(M == 4){ 
            for (int i = 0; i < Ns; i++) {
                complex<double> sсaled_symb = recieved_symbols[i] * sqrt(2);
                received_bits[i * log2(M)] = sсaled_symb.real() > 0 ? 1 : 0;
                received_bits[i * log2(M) + 1] = sсaled_symb.imag() > 0 ? 1 : 0;
            }
        }
        else if(M == 16){
            for (int i = 0; i < Ns; i++) {
                complex<double> sсaled_symb = recieved_symbols[i] * sqrt(10);
                received_bits[i * log2(M)] = sсaled_symb.real() > 0 ? 1 : 0;
                received_bits[i * log2(M) + 1] = abs(sсaled_symb.real()) <= 2 ? 1 : 0; 
                received_bits[i * log2(M) + 2] = sсaled_symb.imag() > 0 ? 1 : 0;
                received_bits[i * log2(M) + 3] = abs(sсaled_symb.imag()) <= 2 ? 1 : 0;
            }
        }
        else if(M == 64){
            for (int i = 0; i < Ns; i++) {
                complex<double> sсaled_symb = recieved_symbols[i] * sqrt(42);
                received_bits[i * log2(M)] = sсaled_symb.real() > 0 ? 1 : 0;
                received_bits[i * log2(M) + 1] = abs(sсaled_symb.real()) <= 4 ? 1 : 0; 
                received_bits[i * log2(M) + 2] = (abs(sсaled_symb.real()) >= 2 && abs(sсaled_symb.real()) <= 6) ? 1 : 0; 
                received_bits[i * log2(M) + 3] = sсaled_symb.imag() > 0 ? 1 : 0;
                received_bits[i * log2(M) + 4] = abs(sсaled_symb.imag()) <= 4 ? 1 : 0;
                received_bits[i * log2(M) + 5] = (abs(sсaled_symb.imag()) >= 2 && abs(sсaled_symb.imag()) <= 6) ? 1 : 0;
            }
        }
        return received_bits;
    }
};