# Dump and calculate the execution time. 
#python3.8


import subprocess
FREQUENCY = 1 *10 **6
ITERATION = 200 # How many times have yu executed the code?

try:
    subprocess.call(['rm exec_time.bin'], shell=True) #remove the file first
    subprocess.call(['JLinkExe -AutoConnect 1 -Device FE310 -If JTAG -Speed 4000 -jtagconf -1,-1 -CommandFile ./CommandFile.jlink'], shell=True)
except:
    subprocess.call(['JLinkExe -AutoConnect 1 -Device FE310 -If JTAG -Speed 4000 -jtagconf -1,-1 -CommandFile ./CommandFile.jlink'], shell=True)

values = open('exec_time.bin', 'rb').read().hex()
# bin endina conversion 
values = list(values[::-1])
for i in range(0, len(values) - 1, 2):
    values[i],values[i+1] = values[i+1],values[i]
cycles = ''.join(values)
print("-----------------------------Calculating----------------------------------")
print('Execution time: ' + str (int(cycles, 16)/(ITERATION*FREQUENCY) * 1000) + ' ms')






