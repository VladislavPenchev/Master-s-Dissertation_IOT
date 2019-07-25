R = 100;
L = 1;
km = 1;
kt = 10;
kl = 1;
kedn = 100;
J = 1;
T = 1;

%Predavatelna matrica
[A,B,C,D]=linmod('Sl_blind_object')
sys=ss(A,B,C,D)
G=tf(sys)

%Postroqvane na singulqrni chisla
sigma(G),grid on

%Postroqvane na vremevite harakteristikki na obekta za upravlenie
step(G(1,1),1),grid on
step(G(1,2)),grid on

%%-------
t = 0:0.1:141/10
%plot(t,lamp,'r',t,ldr,'b',t,motor,'g-');

%figure(1);
%plot(t,lamp);
figure(2);
plot(t,ldr);
figure(3);
plot(t,motor);
