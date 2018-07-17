
#--------------------------------------------
# SIN POINT REVIEWED FOR PYTHON
#--------------------------------------------

import numpy as np
import pyplot as plot

N  =  250             # nbr of points 
fn = (2*np.pi)/N         # the "sample frequency"
A = 512               # the magnitude 
voltage_sf = 0.67925  # the scale factor of the software for the ADC 
offset = 0  # 1023    # offset the signal 

sin_array = [(A * np.sin( fn * i ) + offset ) * voltage_sf for i in range(N)]    # we use "round" because it is an array of int 

## plot 

plot(sin_array,'*') 


## export in a file 

dlmwrite('sin_ref',sin_array)  
