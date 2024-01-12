//*****************************************************************************
//
//! @file binary_counter.c + hello_world_uart.c
//!
//! @brief Example that displays the timer count on the LEDs and prints Hello world.
//!
//! Purpose: This example increments a variable on every timer interrupt. The global
//! variable is used to set the state of the LEDs. The example sleeps otherwise.
//!
//! Printing takes place over the ITM at 1M Baud.
//!
//
//*****************************************************************************

//*****************************************************************************
//
// Copyright (c) 2020, Ambiq Micro
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from this
// software without specific prior written permission.
//
// Third party software included in this distribution is subject to the
// additional license terms as defined in the /docs/licenses directory.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// This is part of revision 2.4.2 of the AmbiqSuite Development Package.
//
//*****************************************************************************

#include "am_mcu_apollo.h"
#include "am_bsp.h"
#include "am_util.h"

//*****************************************************************************
//
// Macros
//
//*****************************************************************************
//
// The default is to use the LFRC as the clock source.
// Can  use the XTAL via the USE_XTAL define.
//
//#define USE_XTAL    1
#if USE_XTAL
#define BC_CLKSRC   "XTAL"
#else
#define BC_CLKSRC   "LFRC"
#endif

#ifdef AM_BSP_NUM_LEDS
#define NUM_LEDS    AM_BSP_NUM_LEDS
#else
#define NUM_LEDS    5       // Make up an arbitrary number of LEDs
#endif

#define MAX_COUNT   (1 << NUM_LEDS)

//*****************************************************************************
//
// Globals
//
//*****************************************************************************
volatile uint32_t g_ui32TimerCount = 0;

//**************************************
// Timer configuration.
//**************************************
am_hal_ctimer_config_t g_sTimer0 =
{
    // Don't link timers.
    0,

    // Set up Timer0A.
    (AM_HAL_CTIMER_FN_REPEAT    |
     AM_HAL_CTIMER_INT_ENABLE   |
#if USE_XTAL
     AM_HAL_CTIMER_XT_256HZ),
#else
     AM_HAL_CTIMER_LFRC_32HZ),
#endif

    // No configuration for Timer0B.
    0,
};

//*****************************************************************************
//
// Function to initialize Timer A0 to interrupt every 1/4 second.
//
//*****************************************************************************
void
timerA0_init(void)
{
    uint32_t ui32Period;

    //
    // Enable the LFRC.
    //
#if USE_XTAL
    am_hal_clkgen_control(AM_HAL_CLKGEN_CONTROL_XTAL_START, 0);
#else
    am_hal_clkgen_control(AM_HAL_CLKGEN_CONTROL_LFRC_START, 0);
#endif

    //
    // Set up timer A0.
    //
    am_hal_ctimer_clear(0, AM_HAL_CTIMER_TIMERA);
    am_hal_ctimer_config(0, &g_sTimer0);

    //
    // Set up timerA0 to 32Hz from LFRC divided to 1 second period.
    //
    ui32Period = 32;
#if USE_XTAL
    ui32Period *= 8;
#endif
    am_hal_ctimer_period_set(0, AM_HAL_CTIMER_TIMERA, ui32Period,
                             (ui32Period >> 1));

    //
    // Clear the timer Interrupt
    //
    am_hal_ctimer_int_clear(AM_HAL_CTIMER_INT_TIMERA0);
} // timerA0_init()

//*****************************************************************************
//
// Timer Interrupt Service Routine (ISR)
//
//*****************************************************************************
void
am_ctimer_isr(void)
{
    //
    // Clear TimerA0 Interrupt (write to clear).
    //
    am_hal_ctimer_int_clear(AM_HAL_CTIMER_INT_TIMERA0);

    //
    // Increment count and set limit based on the number of LEDs available.
    //
    g_ui32TimerCount++;

    if ( g_ui32TimerCount >= MAX_COUNT )
    {
        //
        // Reset the global.
        //
        g_ui32TimerCount = 0;
    }

} // am_ctimer_isr()

// -- UART Stuff --
void *phUART;

#define CHECK_ERRORS(x)                                                       \
    if ((x) != AM_HAL_STATUS_SUCCESS)                                         \
    {                                                                         \
        error_handler(x);                                                     \
    }

volatile uint32_t ui32LastError;

// Catch HAL errors
void error_handler(uint32_t ui32ErrorStatus)
{
    ui32LastError = ui32ErrorStatus;
    while (1);
}

// UART buffers
uint8_t g_pui8TxBuffer[256];
uint8_t g_pui8RxBuffer[2];

// UART configuration
const am_hal_uart_config_t g_sUartConfig =
{
    // Standard UART settings: 115200-8-N-1
    .ui32BaudRate = 115200,
    .ui32DataBits = AM_HAL_UART_DATA_BITS_8,
    .ui32Parity = AM_HAL_UART_PARITY_NONE,
    .ui32StopBits = AM_HAL_UART_ONE_STOP_BIT,
    .ui32FlowControl = AM_HAL_UART_FLOW_CTRL_NONE,

    // Set TX and RX FIFOs to interrupt at half-full.
    .ui32FifoLevels = (AM_HAL_UART_TX_FIFO_1_2 |
                       AM_HAL_UART_RX_FIFO_1_2),

    // Buffers
    .pui8TxBuffer = g_pui8TxBuffer,
    .ui32TxBufferSize = sizeof(g_pui8TxBuffer),
    .pui8RxBuffer = g_pui8RxBuffer,
    .ui32RxBufferSize = sizeof(g_pui8RxBuffer),
};

// UART0 interrupt handler
void am_uart_isr(void)
{
    // Service the FIFOs as necessary, and clear the interrupts
    uint32_t ui32Status, ui32Idle;
    am_hal_uart_interrupt_status_get(phUART, &ui32Status, true);
    am_hal_uart_interrupt_clear(phUART, ui32Status);
    am_hal_uart_interrupt_service(phUART, ui32Status, &ui32Idle);
}

// UART print string
void uart_print(char *pcStr)
{
    uint32_t ui32StrLen = 0;
    uint32_t ui32BytesWritten = 0;

    // Measure the length of the string
    while (pcStr[ui32StrLen] != 0){
        ui32StrLen++;
    }

    // Print the string via the UART
    const am_hal_uart_transfer_t sUartWrite =
    {
        .ui32Direction = AM_HAL_UART_WRITE,
        .pui8Data = (uint8_t *) pcStr,
        .ui32NumBytes = ui32StrLen,
        .ui32TimeoutMs = 0,
        .pui32BytesTransferred = &ui32BytesWritten,
    };

    CHECK_ERRORS(am_hal_uart_transfer(phUART, &sUartWrite));

    if (ui32BytesWritten != ui32StrLen)
    {
        // Couldn't send the whole string!!
        while(1);
    }
}

 // -- End UART Stuff --

void init(void){
/*    am_util_id_t sIdDevice;
    uint32_t ui32StrBuf;

    // Set the clock frequency.
    am_hal_clkgen_control(AM_HAL_CLKGEN_CONTROL_SYSCLK_MAX, 0);

    // Set the default cache configuration
    am_hal_cachectrl_config(&am_hal_cachectrl_defaults);
    am_hal_cachectrl_enable();
*/

    // Configure the board for low power operation.
    // am_bsp_low_power_init();

    // Initialize the printf interface for UART output
    CHECK_ERRORS(am_hal_uart_initialize(0, &phUART));
    CHECK_ERRORS(am_hal_uart_power_control(phUART, AM_HAL_SYSCTRL_WAKE, false));
    CHECK_ERRORS(am_hal_uart_configure(phUART, &g_sUartConfig));

    // Enable the UART pins
    am_hal_gpio_pinconfig(AM_BSP_GPIO_COM_UART_TX, g_AM_BSP_GPIO_COM_UART_TX);
    am_hal_gpio_pinconfig(AM_BSP_GPIO_COM_UART_RX, g_AM_BSP_GPIO_COM_UART_RX);

    // Enable interrupts
    NVIC_EnableIRQ((IRQn_Type)(UART0_IRQn + AM_BSP_UART_PRINT_INST));
    am_hal_interrupt_master_enable();

    // Set the main print interface to use the UART print function we defined
    am_util_stdio_printf_init(uart_print);

    //// Configure GPIO for measurement
    //am_hal_gpio_pinconfig(1, g_AM_HAL_GPIO_OUTPUT);
    //am_hal_gpio_state_write(1, AM_HAL_GPIO_OUTPUT_CLEAR);

    // Configure the system timer
    am_hal_stimer_config(AM_HAL_STIMER_CFG_THAW | AM_HAL_STIMER_HFRC_3MHZ);

}

//*****************************************************************************
//
// Main function.
//
//*****************************************************************************
int
main(void)
{
    uint32_t ui32Ret;
    am_hal_burst_mode_e     eBurstMode;
    am_hal_burst_avail_e    eBurstModeAvailable;

    //
    // Set the clock frequency.
    //
    am_hal_clkgen_control(AM_HAL_CLKGEN_CONTROL_SYSCLK_MAX, 0);

    //
    // Set the default cache configuration
    //
    am_hal_cachectrl_config(&am_hal_cachectrl_defaults);
    am_hal_cachectrl_enable();

    //
    // Configure the board for low power operation.
    //
    //am_bsp_low_power_init();
		init();
		am_util_stdio_terminal_clear();
		am_util_stdio_printf("Hello world \n");
	

#ifdef AM_BSP_NUM_LEDS
    //
    // Initialize the LED array
    //
    am_devices_led_array_init(am_bsp_psLEDs, AM_BSP_NUM_LEDS);
#endif

    //
    // Initialize the count to max so that the counting begins with 0
    // after the first trip to the ISR.
    //
    g_ui32TimerCount = MAX_COUNT;

    //
    // Initialize the printf interface for ITM/SWO output.
    //
    am_bsp_itm_printf_enable();

    //
    // Clear the terminal and print the banner.
    //
    am_util_stdio_terminal_clear();
    am_util_stdio_printf("Binary Counter Example for %s\n", AM_HAL_DEVICE_NAME);
    am_util_stdio_printf("  (Timer clock source is " BC_CLKSRC ")\n");

    //
    // Put into TurboSPOT mode
    //
    if ( am_hal_burst_mode_initialize(&eBurstModeAvailable) == AM_HAL_STATUS_SUCCESS )
    {
        if ( eBurstModeAvailable == AM_HAL_BURST_AVAIL )
        {
            am_util_stdio_printf("\nTurboSPOT mode is Available\n");

            //
            // It's available, put the MCU into TurboSPOT mode.
            //
            if ( am_hal_burst_mode_enable(&eBurstMode) == AM_HAL_STATUS_SUCCESS )
            {
                if ( eBurstMode == AM_HAL_BURST_MODE )
                {
                    am_util_stdio_printf("Operating in TurboSPOT mode (%dMHz)\n",
                                         AM_HAL_CLKGEN_FREQ_MAX_MHZ * 2);
                }
            }
            else
            {
                am_util_stdio_printf("Failed to Enable TurboSPOT mode operation\n");
            }
        }
        else
        {
            am_util_stdio_printf("TurboSPOT mode is Not Available\n");
        }
    }
    else
    {
        am_util_stdio_printf("Failed to Initialize for TurboSPOT mode operation\n");
    }

    //
    // TimerA0 init.
    //
    timerA0_init();

    //
    // Enable the timer Interrupt.
    //
    am_hal_ctimer_int_enable(AM_HAL_CTIMER_INT_TIMERA0);

    //
    // Enable the timer interrupt in the NVIC.
    //
    NVIC_EnableIRQ(CTIMER_IRQn);
    am_hal_interrupt_master_enable();

    //
    // Start timer A0
    //
    am_hal_ctimer_start(0, AM_HAL_CTIMER_TIMERA);

    //
    // We are done printing. Disable debug printf messages on ITM.
    //
    am_bsp_debug_printf_disable();

    //
    // Loop forever.
    //
    while (1)
    {
        //
        // Go to Deep Sleep.
        //
        am_hal_sysctrl_sleep(AM_HAL_SYSCTRL_SLEEP_DEEP);

#ifdef AM_BSP_NUM_LEDS
        //
        // Set the LEDs.
        //
        am_devices_led_array_out(am_bsp_psLEDs, AM_BSP_NUM_LEDS,
                                 g_ui32TimerCount);
#endif
        //
        // Enable debug printf messages using ITM on SWO pin
        //
        am_bsp_debug_printf_enable();

        am_util_stdio_printf("%2d ", g_ui32TimerCount);

        if ( (g_ui32TimerCount & ((MAX_COUNT / 2) - 1)) >= ((MAX_COUNT / 2) - 1) )
        {
            //
            // Take this opportunity to toggle TurboSPOT mode.
            //
            if ( (g_ui32TimerCount >= (MAX_COUNT - 1 ))  &&
                 eBurstModeAvailable == AM_HAL_BURST_AVAIL )
            {
                if ( am_hal_burst_mode_status() == AM_HAL_BURST_MODE )
                {
                    ui32Ret = am_hal_burst_mode_disable(&eBurstMode);
                    if ( (ui32Ret == AM_HAL_STATUS_SUCCESS) &&
                         (eBurstMode == AM_HAL_NORMAL_MODE) )
                    {
                        am_util_stdio_printf("\n\nSwitching to Normal mode (%dMHZ)",
                                             AM_HAL_CLKGEN_FREQ_MAX_MHZ);
                    }
                    else
                    {
                        am_util_stdio_printf("\nError (%d) while switching from Normal to TurboSPOT, eBurstMode=%d.",
                                             ui32Ret, eBurstMode);
                    }
                }
                else if ( am_hal_burst_mode_status() == AM_HAL_NORMAL_MODE )
                {
                    ui32Ret = am_hal_burst_mode_enable(&eBurstMode);
                    if ( (ui32Ret == AM_HAL_STATUS_SUCCESS) &&
                         (eBurstMode == AM_HAL_BURST_MODE) )
                    {
                        am_util_stdio_printf("\n\nSwitching to TurboSPOT mode (%dMHz)",
                                             AM_HAL_CLKGEN_FREQ_MAX_MHZ * 2);
                    }
                    else
                    {
                        am_util_stdio_printf("\nError (%d) while switching from TurboSPOT to Normal, eBurstMode=%d.",
                                             ui32Ret, eBurstMode);
                    }
                }
            }
            am_util_stdio_printf("\n");
        }


        //
        // We are done printing. Disable debug printf messages on ITM.
        //
        am_bsp_debug_printf_disable();
    }
} // main()
