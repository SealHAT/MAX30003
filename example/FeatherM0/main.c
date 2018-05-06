#include "atmel_start.h"
#include "max30003.h"
#include "max30003test.h"

/* Message Strings */
char WELCOME[]       = "Welcome to the SealHAT EKG test suite!\nPlease start the capture to textfile within CoolTerm now!\nBe sure to name your file \"sealtest.txt\" and change your baudrate to max.\n";
char START_TEST[]    = "Please press \"b\" to begin!\n";
char TEST_PASS[]     = "Test complete. Result: PASS\n";
char TEST_FAIL[]     = "Test complete. Result: FAIL ";
char GOODBYE[]       = "\n\nAll tests are complete. The device may now be disconnected. Goodbye!\n";
char PASS[]          = "All tests passed!\n";
char FAIL[]          = "One or more tests failed :(\n";

char NEXT_OR_REDO[]  = "Press \'r\' to redo the test or \'n\' to go to the next test.\n";

#define HOTHPITAL (1)
void spi_init();

int main(void)
{
    /* VARIABLE DECLARATIONS */
	MAX30003_STATUS_VALS status_vals;
    test_result_t result;
    bool test_complete;
    int  retVal;
    char charBuffer[16];
    char getCharValue;

    /* ATMEL INIT */
    atmel_start_init();
    spi_init();
    
    /* YOUR INIT CODE HERE */
    result          = TEST_FAILURE;
    test_complete   = false;

    /* Set up USB connection */
    /* Wait for USB connection to be made with computer. Must be down to receive (DTR). */
    do { /* NOTHING */ } while (!usb_dtr());
        
    /* Write welcome message to the serial console. If the operation fails, it will continue
     * trying to send until it is successful. */
    do {
        retVal = usb_write((uint8_t *) WELCOME, sizeof(WELCOME) - 1);
    } while((retVal != USB_OK) || !usb_dtr());

    /**********
     * TEST 1 *
     **********/
    do { retVal = usb_write((uint8_t *) START_TEST, sizeof(START_TEST) - 1); } while((retVal != USB_OK) || !usb_dtr());
    do { /* NOTHING */ } while(usb_get() != 'b');
    
    while (test_complete == false)
    {

        snprintf(charBuffer, 15,"\nBegin test %1d\n", 1);
        do { retVal = usb_write((uint8_t *) charBuffer, 14); } while((retVal != USB_OK) || !usb_dtr());
    
        /* FUNCTION CALL FOR TEST 1 GOES HERE */
        result = MAX30003_INIT_TEST_ROUND();

        /* Print success or failure message to the console. */
        if(result == TEST_SUCCESS)
        {
            do { retVal = usb_write((uint8_t *) TEST_PASS, sizeof(TEST_PASS) - 1); } while((retVal != USB_OK) || !usb_dtr());
        }
        else
        {
            do { retVal = usb_write((uint8_t *) TEST_FAIL, sizeof(TEST_FAIL) - 1); } while((retVal != USB_OK) || !usb_dtr());
            do { retVal = usb_write((uint8_t *) error_no_to_string(), ERROR_STR_LEN - 1); } while((retVal != USB_OK) || !usb_dtr());
        }
    
        /* Determine if the user wants to redo the test ('r') or go to the next test ('n') */
        do { retVal = usb_write((uint8_t *) NEXT_OR_REDO, sizeof(NEXT_OR_REDO) - 1); } while((retVal != USB_OK) || !usb_dtr());
        do { getCharValue = usb_get(); } while(getCharValue != 'n' && getCharValue != 'r');
        
        if(getCharValue == 'n')
        {
            test_complete = true;
        }        
    
    } /* End test 1 loop. */
    
    /**********
     * TEST 2 *
     **********/
    test_complete = false;
    
    while (test_complete == false)
    {

        snprintf(charBuffer, 15,"\nBegin test %1d\n", 2);
        do { retVal = usb_write((uint8_t *) charBuffer, 14); } while((retVal != USB_OK) || !usb_dtr());
        
        /* FUNCTION CALL FOR TEST 2 GOES HERE */
        

        /* Print success or failure message to the console. */
        if(result == TEST_SUCCESS)
        {
            do { retVal = usb_write((uint8_t *) TEST_PASS, sizeof(TEST_PASS) - 1); } while((retVal != USB_OK) || !usb_dtr());
        }
        else
        {
            do { retVal = usb_write((uint8_t *) TEST_FAIL, sizeof(TEST_FAIL) - 1); } while((retVal != USB_OK) || !usb_dtr());
            do { retVal = usb_write((uint8_t *) error_no_to_string(), ERROR_STR_LEN - 1); } while((retVal != USB_OK) || !usb_dtr());
        }
        
        /* Determine if the user wants to redo the test ('r') or go to the next test ('n') */
        do { retVal = usb_write((uint8_t *) NEXT_OR_REDO, sizeof(NEXT_OR_REDO) - 1); } while((retVal != USB_OK) || !usb_dtr());
        do { getCharValue = usb_get(); } while(getCharValue != 'n' && getCharValue != 'r');
        
        if(getCharValue == 'n')
        {
            test_complete = true;
        }
        
    } /* End test 2 loop. */
        
#ifdef HOTHPITAL
    /**********
     * TEST 3 *
     **********/
    test_complete = false;
    
    while (test_complete == false)
    {

        snprintf(charBuffer, 15,"\nBegin test %1d\n", 3);
        do { retVal = usb_write((uint8_t *) charBuffer, 14); } while((retVal != USB_OK) || !usb_dtr());
        
        /* FUNCTION CALL FOR TEST 3 GOES HERE */


        /* Print success or failure message to the console. */
        if(result == TEST_SUCCESS)
        {
            do { retVal = usb_write((uint8_t *) TEST_PASS, sizeof(TEST_PASS) - 1); } while((retVal != USB_OK) || !usb_dtr());
        }
        else
        {
            do { retVal = usb_write((uint8_t *) TEST_FAIL, sizeof(TEST_FAIL) - 1); } while((retVal != USB_OK) || !usb_dtr());
            do { retVal = usb_write((uint8_t *) error_no_to_string(), ERROR_STR_LEN - 1); } while((retVal != USB_OK) || !usb_dtr());
        }
        
        /* Determine if the user wants to redo the test ('r') or go to the next test ('n') */
        do { retVal = usb_write((uint8_t *) NEXT_OR_REDO, sizeof(NEXT_OR_REDO) - 1); } while((retVal != USB_OK) || !usb_dtr());
        do { getCharValue = usb_get(); } while(getCharValue != 'n' && getCharValue != 'r');
        
        if(getCharValue == 'n')
        {
            test_complete = true;
        }
        
    } /* End test 3 loop. */
    
    /**********
     * TEST 4 *
     **********/
    test_complete = false;
    
    while (test_complete == false)
    {

        snprintf(charBuffer, 15,"\nBegin test %1d\n", 4);
        do { retVal = usb_write((uint8_t *) charBuffer, 14); } while((retVal != USB_OK) || !usb_dtr());
        
        /* FUNCTION CALL FOR TEST 4 GOES HERE */


        /* Print success or failure message to the console. */
        if(result == TEST_SUCCESS)
        {
            do { retVal = usb_write((uint8_t *) TEST_PASS, sizeof(TEST_PASS) - 1); } while((retVal != USB_OK) || !usb_dtr());
        }
        else
        {
            do { retVal = usb_write((uint8_t *) TEST_FAIL, sizeof(TEST_FAIL) - 1); } while((retVal != USB_OK) || !usb_dtr());
            do { retVal = usb_write((uint8_t *) error_no_to_string(), ERROR_STR_LEN - 1); } while((retVal != USB_OK) || !usb_dtr());
        }
        
        /* Determine if the user wants to redo the test ('r') or go to the next test ('n') */
        do { retVal = usb_write((uint8_t *) NEXT_OR_REDO, sizeof(NEXT_OR_REDO) - 1); } while((retVal != USB_OK) || !usb_dtr());
        do { getCharValue = usb_get(); } while(getCharValue != 'n' && getCharValue != 'r');
        
        if(getCharValue == 'n')
        {
            test_complete = true;
        }
        
    } /* End test 4 loop. */
    
    /**********
     * TEST 5 *
     **********/
    test_complete = false;
    
    while (test_complete == false)
    {

        snprintf(charBuffer, 15,"\nBegin test %1d\n", 5);
        do { retVal = usb_write((uint8_t *) charBuffer, 14); } while((retVal != USB_OK) || !usb_dtr());
            
        /* FUNCTION CALL FOR TEST 5 GOES HERE */


        /* Print success or failure message to the console. */
        if(result == TEST_SUCCESS)
        {
            do { retVal = usb_write((uint8_t *) TEST_PASS, sizeof(TEST_PASS) - 1); } while((retVal != USB_OK) || !usb_dtr());
        }
        else
        {
            do { retVal = usb_write((uint8_t *) TEST_FAIL, sizeof(TEST_FAIL) - 1); } while((retVal != USB_OK) || !usb_dtr());
            do { retVal = usb_write((uint8_t *) error_no_to_string(), ERROR_STR_LEN - 1); } while((retVal != USB_OK) || !usb_dtr());
        }
            
        /* Determine if the user wants to redo the test ('r') or go to the next test ('n') */
        do { retVal = usb_write((uint8_t *) NEXT_OR_REDO, sizeof(NEXT_OR_REDO) - 1); } while((retVal != USB_OK) || !usb_dtr());
        do { getCharValue = usb_get(); } while(getCharValue != 'n' && getCharValue != 'r');
            
        if(getCharValue == 'n')
        {
            test_complete = true;
        }
            
    } /* End test 5 loop. */
    
    /**********
     * TEST 6 *
     **********/
    test_complete = false;
    
    while (test_complete == false)
    {

        snprintf(charBuffer, 15,"\nBegin test %1d\n", 6);
        do { retVal = usb_write((uint8_t *) charBuffer, 14); } while((retVal != USB_OK) || !usb_dtr());
        
        /* FUNCTION CALL FOR TEST 6 GOES HERE */


        /* Print success or failure message to the console. */
        if(result == TEST_SUCCESS)
        {
            do { retVal = usb_write((uint8_t *) TEST_PASS, sizeof(TEST_PASS) - 1); } while((retVal != USB_OK) || !usb_dtr());
        }
        else
        {
            do { retVal = usb_write((uint8_t *) TEST_FAIL, sizeof(TEST_FAIL) - 1); } while((retVal != USB_OK) || !usb_dtr());
            do { retVal = usb_write((uint8_t *) error_no_to_string(), ERROR_STR_LEN - 1); } while((retVal != USB_OK) || !usb_dtr());
        }
        
        /* Determine if the user wants to redo the test ('r') or go to the next test ('n') */
        do { retVal = usb_write((uint8_t *) NEXT_OR_REDO, sizeof(NEXT_OR_REDO) - 1); } while((retVal != USB_OK) || !usb_dtr());
        do { getCharValue = usb_get(); } while(getCharValue != 'n' && getCharValue != 'r');
        
        if(getCharValue == 'n')
        {
            test_complete = true;
        }
        
    } /* End test 6 loop. */
    
    /**********
     * TEST 7 *
     **********/
    test_complete = false;
    
    while (test_complete == false)
    {

        snprintf(charBuffer, 15,"\nBegin test %1d\n", 7);
        do { retVal = usb_write((uint8_t *) charBuffer, 14); } while((retVal != USB_OK) || !usb_dtr());
        
        /* FUNCTION CALL FOR TEST 7 GOES HERE */


        /* Print success or failure message to the console. */
        if(result == TEST_SUCCESS)
        {
            do { retVal = usb_write((uint8_t *) TEST_PASS, sizeof(TEST_PASS) - 1); } while((retVal != USB_OK) || !usb_dtr());
        }
        else
        {
            do { retVal = usb_write((uint8_t *) TEST_FAIL, sizeof(TEST_FAIL) - 1); } while((retVal != USB_OK) || !usb_dtr());
            do { retVal = usb_write((uint8_t *) error_no_to_string(), ERROR_STR_LEN - 1); } while((retVal != USB_OK) || !usb_dtr());
        }
        
        /* Determine if the user wants to redo the test ('r') or go to the next test ('n') */
        do { retVal = usb_write((uint8_t *) NEXT_OR_REDO, sizeof(NEXT_OR_REDO) - 1); } while((retVal != USB_OK) || !usb_dtr());
        do { getCharValue = usb_get(); } while(getCharValue != 'n' && getCharValue != 'r');
        
        if(getCharValue == 'n')
        {
            test_complete = true;
        }
        
    } /* End test 7 loop. */
    
    /**********
     * TEST 8 *
     **********/
    test_complete = false;
    
    while (test_complete == false)
    {

        snprintf(charBuffer, 15,"\nBegin test %1d\n", 8);
        do { retVal = usb_write((uint8_t *) charBuffer, 14); } while((retVal != USB_OK) || !usb_dtr());
        
        /* FUNCTION CALL FOR TEST 8 GOES HERE */


        /* Print success or failure message to the console. */
        if(result == TEST_SUCCESS)
        {
            do { retVal = usb_write((uint8_t *) TEST_PASS, sizeof(TEST_PASS) - 1); } while((retVal != USB_OK) || !usb_dtr());
        }
        else
        {
            do { retVal = usb_write((uint8_t *) TEST_FAIL, sizeof(TEST_FAIL) - 1); } while((retVal != USB_OK) || !usb_dtr());
            do { retVal = usb_write((uint8_t *) error_no_to_string(), ERROR_STR_LEN - 1); } while((retVal != USB_OK) || !usb_dtr());
        }
        
        /* Determine if the user wants to redo the test ('r') or go to the next test ('n') */
        do { retVal = usb_write((uint8_t *) NEXT_OR_REDO, sizeof(NEXT_OR_REDO) - 1); } while((retVal != USB_OK) || !usb_dtr());
        do { getCharValue = usb_get(); } while(getCharValue != 'n' && getCharValue != 'r');
        
        if(getCharValue == 'n')
        {
            test_complete = true;
        }
        
    } /* End test 8 loop. */
    
    /**********
     * TEST 9 *
     **********/
    test_complete = false;
    
    while (test_complete == false)
    {

        snprintf(charBuffer, 15,"\nBegin test %1d\n", 9);
        do { retVal = usb_write((uint8_t *) charBuffer, 14); } while((retVal != USB_OK) || !usb_dtr());
        
        /* FUNCTION CALL FOR TEST 9 GOES HERE */


        /* Print success or failure message to the console. */
        if(result == TEST_SUCCESS)
        {
            do { retVal = usb_write((uint8_t *) TEST_PASS, sizeof(TEST_PASS) - 1); } while((retVal != USB_OK) || !usb_dtr());
        }
        else
        {
            do { retVal = usb_write((uint8_t *) TEST_FAIL, sizeof(TEST_FAIL) - 1); } while((retVal != USB_OK) || !usb_dtr());
            do { retVal = usb_write((uint8_t *) error_no_to_string(), ERROR_STR_LEN - 1); } while((retVal != USB_OK) || !usb_dtr());
        }
        
        /* Determine if the user wants to redo the test ('r') or go to the next test ('n') */
        do { retVal = usb_write((uint8_t *) NEXT_OR_REDO, sizeof(NEXT_OR_REDO) - 1); } while((retVal != USB_OK) || !usb_dtr());
        do { getCharValue = usb_get(); } while(getCharValue != 'n' && getCharValue != 'r');
        
        if(getCharValue == 'n')
        {
            test_complete = true;
        }
        
    } /* End test 9 loop. */
    
    /***********
     * TEST 10 *
     ***********/
    test_complete = false;
    
    while (test_complete == false)
    {

        snprintf(charBuffer, 16,"\nBegin test %1d\n", 10);
        do { retVal = usb_write((uint8_t *) charBuffer, 15); } while((retVal != USB_OK) || !usb_dtr());
        
        /* FUNCTION CALL FOR TEST 10 GOES HERE */


        /* Print success or failure message to the console. */
        if(result == TEST_SUCCESS)
        {
            do { retVal = usb_write((uint8_t *) TEST_PASS, sizeof(TEST_PASS) - 1); } while((retVal != USB_OK) || !usb_dtr());
        }
        else
        {
            do { retVal = usb_write((uint8_t *) TEST_FAIL, sizeof(TEST_FAIL) - 1); } while((retVal != USB_OK) || !usb_dtr());
            do { retVal = usb_write((uint8_t *) error_no_to_string(), ERROR_STR_LEN - 1); } while((retVal != USB_OK) || !usb_dtr());
        }
        
        /* Determine if the user wants to redo the test ('r') or go to the next test ('n') */
        do { retVal = usb_write((uint8_t *) NEXT_OR_REDO, sizeof(NEXT_OR_REDO) - 1); } while((retVal != USB_OK) || !usb_dtr());
        do { getCharValue = usb_get(); } while(getCharValue != 'n' && getCharValue != 'r');
        
        if(getCharValue == 'n')
        {
            test_complete = true;
        }
        
    } /* End test 10 loop. */

#endif // HOTHPITAL    

    /***********
     * GOODBYE *
     ***********/
    do { retVal = usb_write((uint8_t *) GOODBYE, sizeof(GOODBYE) - 1); } while((retVal != USB_OK) || !usb_dtr());
        
    uint8_t yAxis = 0;
    uint8_t xAxis = 0;

	for(;;) {
        ecg_get_status(&status_vals);
        gpio_toggle_pin_level(LED_BUILTIN);
        delay_ms(7);
        //ecg_get(&info_vals, REG_INFO);
        snprintf(charBuffer, 7,"%2d,%2d\n", (xAxis%25), (yAxis%25));
        do { retVal = usb_write((uint8_t *) charBuffer, 6); } while((retVal != USB_OK) || !usb_dtr());
        xAxis++;
        yAxis++;
	}
} 

void spi_init()
{
    spi_m_sync_set_mode(&ECG_SPI_DEV_0, SPI_MODE_0);
    spi_m_sync_enable(&ECG_SPI_DEV_0);
    gpio_set_pin_level(CS,true);

    ecg_spi_msg.size  = ECG_BUF_SZ;
    ecg_spi_msg.rxbuf = ECG_BUF_I;
    ecg_spi_msg.txbuf = ECG_BUF_O;
}