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
sys=ss(A,B,C,D);
G=tf(sys)

%Postroqvane na singulqrni chisla
sigma(G),grid on

%Postroqvane na vremevite harakteristikki na obekta za upravlenie
step(G,10),grid on