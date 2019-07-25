function [b,a Ncheb2, signal]=cheby2filter(s)

Ts=0.1;
fs=1/Ts;
N=length(s);
t=0:Ts:(size(s)-1)*Ts;
df=fs/N;
y=fft(s,N);
py=y.*conj(y);
Amp=(2/N)*sqrt(py);
Amp(1)=sqrt(py(1))/N;
Rp=0.9;
Rs=50;
Fp=1;
Fs=100;
Fs2=Fs/2;

Ncheb2=cheb2ord(Fp/Fs2,0.1,Rp,Rs);
[b,a]=cheby2(Ncheb2,Rs,Fp/Fs2,'low');
[h,w]=freqz(b,a,128);
m=abs(h);
signal=filter(b,a,s);