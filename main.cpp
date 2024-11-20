#include <iostream>
#include <vector> 
#include <complex>
#include <fstream>
#include "ClassQAMMod.cpp"
#include "ClassAWGN.cpp"
#include "ClassQAMDemod.cpp"


using namespace std;

int main() {
    const int Nbits = 1e8; // Количество бит для передачи (для одной итерации)
    const int M = 16;  // QPSK / QAM16 / QAM64
    const double target_BER = 1e-6; // Целевая вероятность ошибки
    const int min_errors = 500; // Минимальное количество ошибок для достоверной статистики
    const int max_total_bits = 1e10; // Максимально возможное общее количество бит для передачи
    const int min_total_bits = 1e7; // Минимально возможное общее количество бит для передачи

    const int Ns = Nbits / log2(M); // Количество символов
    const int Nb = Ns*log2(M); // Количество бит, которое будет передано

    if (M != 4 && M != 16 && M != 64) {
        cerr << "Unsupported M value!" << endl;
        return -1; 
    }

    srand(time(0));
    vector<int> bits(Nb);

    vector<double> h2_vector;
    vector<double> BER;

    double h2 = 0.0; // Начальное значение h2 = Eb/N0
    const double h2_step = 0.5; // Шаг изменения h2

    while (h2 <= 30.0) { // Устанавливаем максимальный h2
        double Pb = 1/log2(M);
        double N0 = Pb * pow(10, -h2 / 10);
        int errors_count = 0;
        int total_bits = 0;
        // Пока не наберётся достаточно статистики
        while ((errors_count < min_errors || total_bits < min_total_bits) && total_bits < max_total_bits) {

            for (int i = 0; i < Nb; i++) {
                bits[i] = rand() % 2;
            }

            ClassQAMMod qammod(M);
            vector<complex<double> > symbols = qammod.modulate(bits);

            ClassAWGN awgn(N0);
            vector<complex<double> > noised_signal = awgn.addNoise(symbols);

            ClassQAMDemod qamdemod(M);
            vector<int> received_bits = qamdemod.demodulate(noised_signal);

            for (int j = 0; j < Nb; j++) {
                if (bits[j] != received_bits[j]) {
                    errors_count++;
                }
            }
            total_bits += Nb;
        }
        double BER1 = (double)errors_count / total_bits;
        h2_vector.push_back(h2);
        BER.push_back(BER1);

        cout << "h2 = " << h2 << ", BER = " << errors_count << "/" << total_bits << " = " << BER1 << endl;

        if (BER1 < target_BER && errors_count != 0) {
            cout << "Target BER reached at h2 = " << h2 << endl;
            break;
        } else if (BER1 < target_BER && errors_count == 0) {
            cout << "Total bits has reached the maximum. Need to increase statistics" << endl;
            BER.pop_back();
            h2_vector.pop_back();
            break;
        }

        h2 += h2_step;

    }

    ofstream file("1BER_" + to_string(M) + ".txt");
    for (int i = 0; i < BER.size(); i++) {
        file << h2_vector[i] << " " << BER[i] << endl;
    } 
    file.close();

    cout << "Simulation complete. Results saved to BER_"+ to_string(M) + ".txt" << endl;
    return 0;
}