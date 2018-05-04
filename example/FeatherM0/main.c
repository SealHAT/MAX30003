#include "atmel_start.h"

/* Message Strings */
char WELCOME[]       = "Welcome to the SealHAT EKG test suite!\nPlease start the capture to textfile within CoolTerm now!\nBe sure to name your file \"sealtest.txt\" and change your baudrate to max.\n";
char START_TEST[]    = "Please press \"r\" to begin!\n";
char NEXT_TEST[]     = "Please press \"n\" if you are ready to proceed to the next test.\n";
char TEST_COMPLETE[] = "Test complete.\n";
char GOODBYE[]       = "All tests are complete. The device may now be disconnected. Goodbye!\n";

int main(void)
{
    /* VARIABLE DECLARATIONS */
    int  retVal;
    char charBuffer[16];
    
    /* ATMEL INIT */
	atmel_start_init();
    
    
    /* YOUR INIT CODE HERE */
    
    
    /* Set up USB connection */
    /* Wait for USB connection to be made with computer. Must be down to receive (DTR). */
    do { /* NOTHING */ } while (!usb_dtr());
        
    /* Write welcome message to the serial console. If the operation fails, it will continue
     * trying to send until it is successful. */
    do {
        retVal = usb_write((uint8_t *) WELCOME, sizeof(WELCOME));
    } while((retVal != USB_OK) || !usb_dtr());
	
    /**********
     * TEST 1 *
     **********/
    do { retVal = usb_write((uint8_t *) START_TEST, sizeof(START_TEST)); } while((retVal != USB_OK) || !usb_dtr());
    do { /* NOTHING */ } while(usb_get() != 'r');
    snprintf(charBuffer, 14,"Begin test %1d\n", 1);
    do { retVal = usb_write((uint8_t *) charBuffer, sizeof(charBuffer)); } while((retVal != USB_OK) || !usb_dtr());
    
    /* FUNCTION CALL FOR TEST 1 GOES HERE */
    
    
    do { retVal = usb_write((uint8_t *) TEST_COMPLETE, sizeof(TEST_COMPLETE)); } while((retVal != USB_OK) || !usb_dtr());
    
    /**********
     * TEST 2 *
     **********/
    do { retVal = usb_write((uint8_t *) NEXT_TEST, sizeof(NEXT_TEST)); } while((retVal != USB_OK) || !usb_dtr());
    do { /* NOTHING */ } while(usb_get() != 'n');
    snprintf(charBuffer, 14,"Begin test %1d\n", 2);
    do { retVal = usb_write((uint8_t *) charBuffer, sizeof(charBuffer)); } while((retVal != USB_OK) || !usb_dtr());
    
    /* FUNCTION CALL FOR TEST 2 GOES HERE */
    
    
    do { retVal = usb_write((uint8_t *) TEST_COMPLETE, sizeof(TEST_COMPLETE)); } while((retVal != USB_OK) || !usb_dtr());
    
    /**********
     * TEST 3 *
     **********/
    do { retVal = usb_write((uint8_t *) NEXT_TEST, sizeof(NEXT_TEST)); } while((retVal != USB_OK) || !usb_dtr());
    do { /* NOTHING */ } while(usb_get() != 'n');
    snprintf(charBuffer, 14,"Begin test %1d\n", 3);
    do { retVal = usb_write((uint8_t *) charBuffer, sizeof(charBuffer)); } while((retVal != USB_OK) || !usb_dtr());
    
    /* FUNCTION CALL FOR TEST 3 GOES HERE */
    
    
    do { retVal = usb_write((uint8_t *) TEST_COMPLETE, sizeof(TEST_COMPLETE)); } while((retVal != USB_OK) || !usb_dtr());
    
    /**********
     * TEST 4 *
     **********/
    do { retVal = usb_write((uint8_t *) NEXT_TEST, sizeof(NEXT_TEST)); } while((retVal != USB_OK) || !usb_dtr());
    do { /* NOTHING */ } while(usb_get() != 'n');
    snprintf(charBuffer, 14,"Begin test %1d\n", 4);
    do { retVal = usb_write((uint8_t *) charBuffer, sizeof(charBuffer)); } while((retVal != USB_OK) || !usb_dtr());
    
    /* FUNCTION CALL FOR TEST 4 GOES HERE */
    
    
    do { retVal = usb_write((uint8_t *) TEST_COMPLETE, sizeof(TEST_COMPLETE)); } while((retVal != USB_OK) || !usb_dtr());
    
    /**********
     * TEST 5 *
     **********/
    do { retVal = usb_write((uint8_t *) NEXT_TEST, sizeof(NEXT_TEST)); } while((retVal != USB_OK) || !usb_dtr());
    do { /* NOTHING */ } while(usb_get() != 'n');
    snprintf(charBuffer, 14,"Begin test %1d\n", 5);
    do { retVal = usb_write((uint8_t *) charBuffer, sizeof(charBuffer)); } while((retVal != USB_OK) || !usb_dtr());
    
    /* FUNCTION CALL FOR TEST 5 GOES HERE */
    
    
    do { retVal = usb_write((uint8_t *) TEST_COMPLETE, sizeof(TEST_COMPLETE)); } while((retVal != USB_OK) || !usb_dtr());
    
    /**********
     * TEST 6 *
     **********/
    do { retVal = usb_write((uint8_t *) NEXT_TEST, sizeof(NEXT_TEST)); } while((retVal != USB_OK) || !usb_dtr());
    do { /* NOTHING */ } while(usb_get() != 'n');
    snprintf(charBuffer, 14,"Begin test %1d\n", 6);
    do { retVal = usb_write((uint8_t *) charBuffer, sizeof(charBuffer)); } while((retVal != USB_OK) || !usb_dtr());
    
    /* FUNCTION CALL FOR TEST 6 GOES HERE */
    
    
    do { retVal = usb_write((uint8_t *) TEST_COMPLETE, sizeof(TEST_COMPLETE)); } while((retVal != USB_OK) || !usb_dtr());
    
    /**********
     * TEST 7 *
     **********/
    do { retVal = usb_write((uint8_t *) NEXT_TEST, sizeof(NEXT_TEST)); } while((retVal != USB_OK) || !usb_dtr());
    do { /* NOTHING */ } while(usb_get() != 'n');
    snprintf(charBuffer, 14,"Begin test %1d\n", 7);
    do { retVal = usb_write((uint8_t *) charBuffer, sizeof(charBuffer)); } while((retVal != USB_OK) || !usb_dtr());
    
    /* FUNCTION CALL FOR TEST 7 GOES HERE */
    
    
    do { retVal = usb_write((uint8_t *) TEST_COMPLETE, sizeof(TEST_COMPLETE)); } while((retVal != USB_OK) || !usb_dtr());
    
    /**********
     * TEST 8 *
     **********/
    do { retVal = usb_write((uint8_t *) NEXT_TEST, sizeof(NEXT_TEST)); } while((retVal != USB_OK) || !usb_dtr());
    do { /* NOTHING */ } while(usb_get() != 'n');
    snprintf(charBuffer, 14,"Begin test %1d\n", 8);
    do { retVal = usb_write((uint8_t *) charBuffer, sizeof(charBuffer)); } while((retVal != USB_OK) || !usb_dtr());
    
    /* FUNCTION CALL FOR TEST 8 GOES HERE */
    
    
    do { retVal = usb_write((uint8_t *) TEST_COMPLETE, sizeof(TEST_COMPLETE)); } while((retVal != USB_OK) || !usb_dtr());
    
    /**********
     * TEST 9 *
     **********/
    do { retVal = usb_write((uint8_t *) NEXT_TEST, sizeof(NEXT_TEST)); } while((retVal != USB_OK) || !usb_dtr());
    do { /* NOTHING */ } while(usb_get() != 'n');
    snprintf(charBuffer, 14,"Begin test %1d\n", 9);
    do { retVal = usb_write((uint8_t *) charBuffer, sizeof(charBuffer)); } while((retVal != USB_OK) || !usb_dtr());
    
    /* FUNCTION CALL FOR TEST 9 GOES HERE */
    
    
    do { retVal = usb_write((uint8_t *) TEST_COMPLETE, sizeof(TEST_COMPLETE)); } while((retVal != USB_OK) || !usb_dtr());
    
    /***********
     * TEST 10 *
     ***********/
    do { retVal = usb_write((uint8_t *) NEXT_TEST, sizeof(NEXT_TEST)); } while((retVal != USB_OK) || !usb_dtr());
    do { /* NOTHING */ } while(usb_get() != 'n');
    snprintf(charBuffer, 15,"Begin test %1d\n", 10);
    do { retVal = usb_write((uint8_t *) charBuffer, sizeof(charBuffer)); } while((retVal != USB_OK) || !usb_dtr());
    
    /* FUNCTION CALL FOR TEST 10 GOES HERE */
    
    
    do { retVal = usb_write((uint8_t *) TEST_COMPLETE, sizeof(TEST_COMPLETE)); } while((retVal != USB_OK) || !usb_dtr());
    
    /***********
     * GOODBYE *
     ***********/
    do { retVal = usb_write((uint8_t *) GOODBYE, sizeof(GOODBYE)); } while((retVal != USB_OK) || !usb_dtr());

    /* Toggle LED on/off forever. */
	while(1)
    {
        gpio_toggle_pin_level(LED_BUILTIN);
        delay_ms(1000);
    }
} 
