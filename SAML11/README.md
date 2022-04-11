## Getting started:
 






Generic clock gerenrator 0 supplies clock to the power managmenet and MCLK so this is always enabled. 
MCLK is responsible for syncronous clock generation (CPU and other bus clocks)

MCLK.APBxMASK is an important reigister

- Generator 0 is always a source for GCLK_MAIN.