%H_Infinity
s=tf('s')

%Filter na izhoda
Ty11=50;
Ty12=0.001;
Ky1=0.01;
num1 = Ky1*(Ty11*s+1);
den1 = (Ty12*s+1);
Wy=[num1/den1]

figure(1)
sigma(Wy,G),grid on

% figure(10)
% bodemag(Wy),grid on

%reverse KU 

%Filter na motor - purvi vhod
T1u=0.001;
T2u=1;
Ku=100;
numu = Ku*(T1u*s+1);
denu = (T2u*s+1);
Wu1=[numu/denu]

figure(2)
sigma(Wu1,G),grid on;

% Filter na lampa - vtori vhod
T1u=0.001;
T2u=1;
Ku=0.1;
numu = Ku*(T1u*s+1);
denu = (T2u*s+1);
Wu2=[numu/denu]

figure(3)
sigma(Wu2,G),grid on;

% %Sravnenie dvata filtura na vhoda s predavatelnata
% figure(2)
% sigma(Wu1,Wu2,G),grid on;

% linerizaciq
[A,B,C,D]=linmod('Sl_H_Infinity')

%sintez na H bezkrainost regulator
[K,~,GAM]=hinfsyn(ss(A,B,C,D),1,2,'display','on')
figure(4)
sigma(K)
kd = c2d(K,0.1)

%%%%%%%
[A,B,C,D]=linmod('Sl_H_Infinity_Close_loop')
sys1=(ss(A,B,C,D))

%izhodna custvitelnost - S 
Wyk=sys1(3,1)
figure(5)
sigma(Wyk,Wy),grid on

%custvitelnost na upravlqvashtiq signal k*S
Wuk=sys1(1:2,1)
figure(6)
sigma(Wuk,[Wu1,0;0,Wu2]),grid on

To=sys1(4,1)
figure(7)
sigma(To),grid on
% 
% figure(8)
% hold on
% plot(time,upr,'k'),grid on
% plot(time,upr1,'r*'),grid on
% hold off
% 
% figure(9)
% hold on
% plot(time,izhod,'k'),grid on
% plot(time,izhod1,'g*'),grid on
% hold off
