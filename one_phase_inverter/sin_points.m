clear all 
close all 

N= 250 ; % nbr of points 
fn=(2*pi)/N ; % the "sample frequency"
A = 2000000 ; % the magnitude 
voltage_sf = 0.67925 ; % the scale factor of the software for the ADC 
offset = 0 ; %1023 ; % offset the signal 

sin_array = zeros(1,N) ; % init the array 

% for i=1:N
%     sin_array(i) = round(A*sin(fn*i))  ;  % we use "round" because it is an array of int 
% end 

for i=1:N
    sin_array(i) =1/2.02*sin(fn*i)  ;  % we use "round" because it is an array of int 
end

%% plot 

plot(sin_array,'*') 


%% export in a file 

dlmwrite('sin_ref',sin_array) ; 