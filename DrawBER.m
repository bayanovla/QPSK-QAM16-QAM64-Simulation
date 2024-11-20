%% QPSK
set(0,'DefaultLineLinewidth',3);
data_4 = load('BER_4.txt');
h2_4 = data_4(:, 1);
BER_4=data_4(:, 2);
figure(1);
semilogy(h2_4, berawgn(h2_4, 'psk',4,'nondiff'),'DisplayName','theor QPSK')
hold on; 
grid on
semilogy(h2_4, BER_4,'--+','DisplayName','QPSK');
xlabel('E_b/N_0, дБ');
ylabel('BER');
legend('boxoff') 
handle_mas = findobj('type', 'axes');
set(handle_mas, 'FontSize', 20)
%% QAM16
data_16 = load('BER_16.txt');
h2_16 = data_16(:, 1);
BER_16=data_16(:, 2);
semilogy(h2_16, berawgn(h2_16, 'qam',16,'nondiff'),'DisplayName','theor QAM16')
hold on
grid on
semilogy(h2_16, BER_16,'--+','DisplayName','QAM16');
xlabel('E_b/N_0, дБ');
ylabel('BER');
legend('boxoff') 
handle_mas = findobj('type', 'axes');
set(handle_mas, 'FontSize', 20)
%% QAM64
data_64 = load('BER_64.txt');
h2_64 = data_64(:, 1);
BER_64=data_64(:, 2);
semilogy(h2_64, berawgn(h2_64, 'qam',64,'nondiff'),'DisplayName','theor QAM64')
hold on
grid on
semilogy(h2_64, BER_64,'--+','DisplayName','QAM64');
xlabel('E_b/N_0, дБ');
ylabel('BER');
legend('boxoff') 
handle_mas = findobj('type', 'axes');
set(handle_mas, 'FontSize', 20)