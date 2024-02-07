# Dump and calculate the execution time. 
#python3.8


import subprocess
FREQUENCY = 4 *10 **6


try:
    subprocess.call(['rm exec_time.bin'], shell=True) #remove the file first
    subprocess.call(['JLinkExe -AutoConnect 1 -Device ATSAML11E16A -If SWD -Speed 4000 -CommandFile ./CommandFile.jlink'], shell=True)
except:
    subprocess.call(['JLinkExe -AutoConnect 1 -Device ATSAML11E16A -If SWD -Speed 4000 -CommandFile ./CommandFile.jlink'], shell=True)

values = open('exec_time.bin', 'rb').read().hex()
# bin endina conversion 
values = list(values[::-1])
for i in range(0, len(values) - 1, 2):
    values[i],values[i+1] = values[i+1],values[i]
cycles = ''.join(values)
print("-----------------------------Calculating----------------------------------")
print('Execution time: ' + str (int(cycles, 16)/FREQUENCY * 1000) + ' ms')






