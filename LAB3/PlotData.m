A=load('MotorRPM10_50.csv');

RPM=A(:,1);
Time=A(:,2);

plot(Time,RPM)
hold on


%Lowpass filter
v=RPM;
for i=2:length(RPM)
 v(i)=0.854*v(i-1)+0.0728*RPM(i)+0.0728*RPM(i-1);
end

plot(Time,v)
legend("Raw speed (RPM)", "Filtered speed (RPM)");
xlabel("Time (ms)");
ylabel("Speed (RPM)");