%sintez na LQR regulator
%1-vi variant
Q=[0.45 0 0 0;
    0 1 0 0;
    0 0 0.000001 0;
    0 0 0 0.000001]
R=[0.01 0;
    0 0.01]
Kp=lqr(A,B,Q,R)
%sus suglasuvashta matrica L,bez integrator
L=inv([C*inv(-A+B*Kp)*B])

plot(tout,u),grid on

plot(tout,y),grid on

%Task 3.1
%chestotna harakteristika
%1-vi variant bez L
G=ss(A,B,eye(4),zeros(4,2))
systemnames='G C Kp';
inputvar='[r{2};d{4}]';
outputvar='[C;r-Kp]';
input_to_Kp ='[G+d]';
input_to_C ='[G+d]';
input_to_G ='[r-Kp]';
CL=sysic

figure(1);sigma(CL(1:2,1:2)),grid on;%T
figure(2);sigma(CL(1:2,3:6)),grid on;%S
figure(3);sigma(CL(3:4,1:2)),grid on;%K*S

%2-ri variant s L
G=ss(A,B,eye(4),zeros(4,2))
systemnames='G C Kp L';
inputvar='[r{2};d{4}]';
outputvar='[C;r-Kp]';
input_to_Kp ='[G+d]';
input_to_C ='[G+d]';
input_to_G ='[L-Kp]';
input_to_L ='[r]';
CL=sysic
figure(1);sigma(CL(1:2,1:2)),grid on;%T
figure(2);sigma(CL(1:2,3:6)),grid on;%S
figure(3);sigma(CL(3:4,1:2)),grid on;%K*S

%Kalman
sysKalman = ss(A,B,C,D);
kf = kalman(sysKalman,[],eye(2))

figure(4);
plot(y),grid on

figure(5);
plot(y1),grid on

%zad4
%Astatichno upravlenie s LQR
%sintez na LQR s integrator,bez L
H=[0 0;
    0 0];
H1=[0 0;
    0 0;
    0 0;
    0 0];
Ach=[H -C;
     H1 A];
Bch=[H;
    B];
Q1=[50 0 0 0 0 0;
    0 20 0 0 0 0;
    0 0 0.1 0 0 0;
    0 0 0 1 0 0;
    0 0 0 0 0.001 0;
    0 0 0 0 0 0.001];
R1=[0.1 0;
    0 0.01];
Kp1=lqr(Ach,Bch,Q1,R1)
Ki=-Kp1(:,1:2)
Kp=Kp1(:,3:6)
plot(tout,u1),grid on
plot(tout,y1),grid on

%zad4.1
%chestotna harakteristika

int=tf(1,[1 0]);
int2=tf(1,[1 0]);
Z=[int 0;
    0 int2];
G=ss(A,B,eye(4),zeros(4,2))
systemnames='G C Kp Z Ki';
inputvar='[r{2};d{2}]';
outputvar='[C+d;Ki-Kp]';
input_to_Kp ='[G]';
input_to_C ='[G]';
input_to_G ='[Ki-Kp]';
input_to_Z ='[r-C-d]';
input_to_Ki ='[Z]';
CL=sysic
figure(1);sigma(CL(1:2,1:2)),grid on;%T
figure(2);sigma(CL(1:2,3:4)),grid on;%S
figure(3);sigma(CL(3:4,1:2)),grid on;%K*S
figure(4);sigma(CL(1:2,1:2)/CL(1:2,3:4)),grid on;
