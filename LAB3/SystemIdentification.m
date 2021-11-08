A=load('MotorRPM11.csv');

RPM=A(:,2);
Time=A(:,3);
Input=A(:,1);

figure(1)
plot(Time,RPM)
hold on


%Lowpass filter
v=RPM;
for i=2:length(RPM)
 v(i)=0.854*v(i-1)+0.0728*RPM(i)+0.0728*RPM(i-1);
end


B = 1/3*ones(3,1);
Mfilt = filter(B,1,RPM);

plot(Time,v)
legend("Raw speed (RPM)", "Filtered speed (RPM)");
xlabel("Time (ms)");
ylabel("Speed (RPM)");
hold on
yyaxis right
plot(Time,Input)
% Input=255*ones(length(RPM),1);

num=55.61;
den=[1 11.7];

G=tf(num,den)
figure(2)
step(255*G)

num2=50.2;
den2=[1 9.597]
G2=tf(num2,den2)
step(G2)
