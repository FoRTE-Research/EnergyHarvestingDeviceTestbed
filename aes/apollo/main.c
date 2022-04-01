#include "test.h"

#include <stdint.h>
#include <string.h>

#ifdef slow_tiny_aes
#include "slow_tiny_aes/aes.h"
#endif

#include "am_mcu_apollo.h"
#include "am_bsp.h"
#include "am_util.h"

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

/** Globals (test inputs) **/
uint8_t key[] = { 0x60, 0x3d, 0xeb, 0x10, 0x15, 0xca, 0x71, 0xbe, 0x2b, 0x73,
                  0xae, 0xf0, 0x85, 0x7d, 0x77, 0x81, 0x1f, 0x35, 0x2c, 0x07,
                  0x3b, 0x61, 0x08, 0xd7, 0x2d, 0x98, 0x10, 0xa3, 0x09, 0x14,
                  0xdf, 0xf4 };
uint8_t check_encrypt[] = { 0xf3, 0xee, 0xd1, 0xbd, 0xb5, 0xd2, 0xa0, 0x3c,
                            0x06, 0x4b, 0x5a, 0x7e, 0x3d, 0xb1, 0x81, 0xf8 };
#ifdef AES_CBC
uint8_t pt[MSG_LNGTH];
uint8_t ct[MSG_LNGTH];
// initialization vector for CBC mode
unsigned char iv[AES_BLOCK_SIZE_BYTES] = { 0xb2, 0x4b, 0xf2, 0xf7, 0x7a, 0xc5, 0xec, 0x0c, 0x5e,
                         0x1f, 0x4d, 0xc1, 0xae, 0x46, 0x5e, 0x75 };
#else
uint8_t pt[] = { 0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d,
                 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a };
uint8_t ct[] = { 0xf3, 0xee, 0xd1, 0xbd, 0xb5, 0xd2, 0xa0, 0x3c, 0x06, 0x4b,
                 0x5a, 0x7e, 0x3d, 0xb1, 0x81, 0xf8 };
#endif

/** contexts **/
#ifdef tiny_aes
struct AES_ctx ctx;
#endif
#ifdef mbedtls_aes
struct mbedtls_aes_context ctx;
#endif

/** define keysizes **/
#if defined AES_128
long keysize = 128;
#elif defined AES_192
long keysize = 192;
#else
long keysize = 256;
#endif

/** Call initialization functions for different AES implementations **/
void init_aes()
{
#ifdef gladman_aes
    gladman_init(key, pt, ct, keysize);
#endif
#ifdef tiny_aes
    AES_init_ctx(&ctx, key);
#endif
#ifdef mbedtls_aes
    mbedtls_aes_init(&ctx);
    mbedtls_aes_setkey_enc(&ctx, key, keysize);
#endif
}

void test_encrypt()
{
    /** Gladman AES **/
#ifdef gladman_aes
#ifdef AES_128
    aes_gladman_128_encrypt(key, pt, ct);
#elif AES_192
    aes_gladman_192_encrypt(key, pt, ct);
#else // AES_256
    aes_gladman_256_encrypt(key, pt, ct);
#endif
#endif

    /** tiny AES **/
#ifdef tiny_aes
    AES_encrypt(&ctx, key, pt, ct);
#endif

    /** SLOW tiny AES **/
#ifdef slow_tiny_aes
    test_AES_encrypt();
#endif

    /** MbedTLS AES **/
#ifdef mbedtls_aes
    mbedtls_internal_aes_encrypt(&ctx, pt, ct);
#endif
}

void test_decrypt()
{
    /** Gladman AES **/
#ifdef gladman_aes
#ifdef AES_128
    aes_gladman_128_decrypt(key, ct, pt);
#elif AES_192
    aes_gladman_192_decrypt(key, ct, pt);
#else // AES_256
    aes_gladman_256_decrypt(key, ct, pt);
#endif
#endif
    /** tiny AES **/
#ifdef tiny_aes
    AES_decrypt(&ctx, key, ct, pt);
#endif

    /** SLOW tiny AES **/
#ifdef slow_tiny_aes
    test_AES_decrypt();
#endif

    /** MbedTLS AES **/
#ifdef mbedtls_aes
    mbedtls_internal_aes_decrypt(&ctx, pt, ct);
#endif
}

int check_result()
{
    return memcmp((char*) pt, (char*) check_encrypt, 16);
}

#ifdef AES_CBC
void aes_encrypt_cbc(size_t length) {
    uint8_t * p = pt;
    uint8_t * c = ct;

    while (length > 0) {
        // Perform IV xor PT for 128 bits
        int i = 0;
        for (i = 0; i < AES_BLOCK_SIZE_BYTES; i++)
            p[i] = p[i] ^ iv[i];

        // Perform 1 encrypt
        test_encrypt();

        // IV is now CT
        memcpy(iv, c, AES_BLOCK_SIZE_BYTES);

        // Go to next block of PT
        p += AES_BLOCK_SIZE_BYTES;
        c += AES_BLOCK_SIZE_BYTES;
        length -= AES_BLOCK_SIZE_BYTES;
    }
}

void aes_decrypt_cbc(size_t length) {
    uint8_t * p = pt;
    uint8_t * c = ct;

    while (length > 0) {
        // Perform 1 encrypt
        test_decrypt();

        // Perform IV xor PT for 128 bits
        int i = 0;
        for (i = 0; i < AES_BLOCK_SIZE_BYTES; i++)
             p[i] = p[i] ^ iv[i];

        // IV is now CT
        memcpy(iv, c, AES_BLOCK_SIZE_BYTES);

        // Go to next block of PT
        p += AES_BLOCK_SIZE_BYTES;
        c += AES_BLOCK_SIZE_BYTES;
        length -= AES_BLOCK_SIZE_BYTES;
    }
}
#endif

void init(void){
    // Set the clock frequency.
    am_hal_clkgen_control(AM_HAL_CLKGEN_CONTROL_SYSCLK_MAX, 0);

    // Set the default cache configuration
    am_hal_cachectrl_config(&am_hal_cachectrl_defaults);
    am_hal_cachectrl_enable();

    // Configure the board for low power operation.
    am_bsp_low_power_init();
    
    //// Configure GPIO for measurement
    am_hal_gpio_pinconfig(1, g_AM_HAL_GPIO_OUTPUT);
    am_hal_gpio_state_write(1, AM_HAL_GPIO_OUTPUT_CLEAR);

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

    // Configure the system timer
    am_hal_stimer_config(AM_HAL_STIMER_CFG_THAW | AM_HAL_STIMER_HFRC_3MHZ);

}

//*****************************************************************************
//
// Main
//
//*****************************************************************************
int main(void)
{
  init();
  am_hal_gpio_state_write(1, AM_HAL_GPIO_OUTPUT_CLEAR);
  am_util_delay_us(20);

  uint32_t startClock, stopClock, aesTime;

  init_aes();

  volatile int result;

  /** Choose the function to be called **/
  /** Encrypt or decrypt possibly many times **/
  startClock = am_hal_stimer_counter_get();
  am_hal_gpio_state_write(1, AM_HAL_GPIO_OUTPUT_SET);
  #ifdef slow_tiny_aes
      result = test_AES_encrypt();  // for slow_tiny_aes, test_AES_encrypt/decrypt does the testing for us
      //result = test_AES_decrypt();  // for slow_tiny_aes, test_AES_encrypt/decrypt does the testing for us
  #endif
  am_hal_gpio_state_write(1, AM_HAL_GPIO_OUTPUT_CLEAR);
  stopClock = am_hal_stimer_counter_get();

  if(result == 0){
    am_hal_gpio_state_write(44, AM_HAL_GPIO_OUTPUT_SET);
  }else{
    am_hal_gpio_state_write(46, AM_HAL_GPIO_OUTPUT_SET);
  }

  if(stopClock < startClock){ // Overflow
    aesTime = (0xFFFFFFFF - startClock) + stopClock;
  }else{
    aesTime = stopClock - startClock;
  }

  aesTime /= 3;   // Convert from 3 MHz frequency to us
  
  am_util_stdio_terminal_clear();
  am_util_stdio_printf("Encryption time: %u us\r\n", aesTime);

  while(1);
}
