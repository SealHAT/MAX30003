#include <atmel_start.h>
#include <stdlib.h>
#include "sealhat_menu.h"

#define NUMBER_OF_FACTS				(5)
const char* const facts[] = {
	"From end to end, large elephant seal males can grow to lengths of 20 feet and weigh up to 8800 pounds.\n",
	"In The Lord of the Rings, scrawny, cave-dwelling Moria orcs emit an eerie battle screech created from elephant seal pup calls.\n",
	"Once the lactation process starts, these pups grow up fast: In just 30 days, an average pup will go from weighing 75 to 300 pounds.\n",
	"Elephant seals can dive up to a depth of 5788 feet and hold their breath for up to two hours.\n",
	"By 1892, many people thought the northern elephant seal was extinct due to hunting. They were hunted to harvest blubber for oil.\n",
NULL};

void sealfact(uint8_t);
#define SPEEDTEST_SIZE          (2048)
void speedtest(uint8_t);

const MENU_t main_m;
const MENU_t sealfact_m  = {{"Seal Fact!"}, &sealfact, 0, 0, {NULL}};
const MENU_t speedtest_m = {{"Speed Test"}, &speedtest, 0, 0, {NULL}};
const MENU_t main_m = {{"Main Menu"}, NULL, 0, 2, {&sealfact_m, &speedtest_m}};

int main(void)
{
	const MENU_t* curMenu = &main_m;	// The main menu, starting point
	int32_t choice;						// the menu option selected by user

	atmel_start_init();		// Initializes the system
	srand(1996);
	
	for(;;) {		
		// the device is configured on the USB bus
		if(usb_state() == USB_Configured) {
            gpio_set_pin_level(LED_BUILTIN, usb_dtr());

            // The usb serial terminal is open and accepting data
            if(usb_dtr()) {
				menu_display(curMenu, NULL);
				while(usb_dtr()) {
					// there is OUT data ready to read
					if(usb_available() > 0) {
						choice  = menu_getOption();
						curMenu = menu_navigate(curMenu, choice);
						menu_display(curMenu, NULL);
					} // OUT data available
				} // DTR WHILE
			} // DTR IF
			else {
				// reset to main menu if DTR disconnects
				usb_haltTraffic();
				curMenu = &main_m;
			}

		} // USB CONFIGURED
		else {
			gpio_set_pin_level(LED_BUILTIN, false);
		}
	} // FOREVER LOOP
} // MAIN FUNCTION

void sealfact(uint8_t val) {
	int i = rand() % NUMBER_OF_FACTS;
	usb_write((void*)facts[i], strlen(facts[i]));
	delay_ms(1);
	usb_write("\n", 1);
}


// sends large buffers, checking if there is input between to abort test
// The large buffers amortizes the overhead of starting the test and checking for stop commands
void speedtest(uint8_t val) {
    uint8_t speedbuf[SPEEDTEST_SIZE];
    uint8_t j;                          // for filling the array
    int32_t i;                          // for iterating through array
    int32_t err;                        // catching API errors

    for (i = 0, j = 0; i < SPEEDTEST_SIZE; i++) {
        speedbuf[i] = j++;
    }

    while(usb_available() <= 0) {
        do {
            err = usb_write(speedbuf, SPEEDTEST_SIZE);
        } while(err < 0);
    }
}