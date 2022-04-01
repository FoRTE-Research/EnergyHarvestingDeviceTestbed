# This file loads a test binary to FE310 device.

if [[ ! -f start.hex ]] && [[ ! -f CommandFile.jlink ]] 
    then 
    echo "Error: start.hex and CommandFile.jlink files must be in the same directory (./)"
    exit 1
fi

echo "Loading blinky in the device ......................................................................"
JLinkExe -AutoConnect 1 -Device FE310 -If JTAG -Speed 4000 -jtagconf -1,-1 -CommandFile ./CommandFile.jlink
