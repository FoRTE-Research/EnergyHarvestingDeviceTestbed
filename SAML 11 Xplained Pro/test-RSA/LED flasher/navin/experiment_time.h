unsigned int ticks = 0;

#ifdef msp432p401r
void SysTick_Handler(void) {
    ticks++;
}

#define startTimer() MAP_SysTick_setPeriod(300);    /* 1ms resolution */ \
                     MAP_SysTick_enableInterrupt();                       \
                     /* Enabling MASTER interrupts */                     \
                     MAP_Interrupt_enableMaster();                        \
                     MAP_SysTick_enableModule();   /* Start timer */      \
                     unsigned int start = ticks;
#endif

#if defined(msp430g2553) || defined(msp430fr5994)
// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TimeA0 (void)
{
  ticks++;
}

#define startTimer() TA0CCTL0 = CCIE;                 /* CCR0 interrupt enabled */    \
                     TA0CTL = TASSEL_2 + MC_1 + ID_3; /* SMCLK/8 (1 MHz/8), upmode */ \
                     TA0CCR0 =  128;                  /* 1 KHz */                     \
                     __bis_SR_register(GIE);         /* Enable all interrupts */     \
                     unsigned int start = ticks
#endif

#define getElapsedTime() (ticks - start)

// Stop watchdog timer
#if defined(msp430g2553) || defined(msp430fr5994)
   #define board_init()    WDTCTL = WDTPW | WDTHOLD
#endif
#ifdef msp432p401r
   #define board_init() WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD
#endif
