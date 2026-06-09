/* 
* Author: Amilie (amilietf)
* Date: 2026-06-08
* Desc: A temporary application for testing logging.
* Lang: C
*/

#include "logging_test.h"
#include "../../drivers/video/vga.h"
#include "../../drivers/serial/serial.h"

int logging_main(void){
    print_to_screen("hi from the logging test app\n");
    serial_write("[APPLICATION] Hello from the serial test application.\n\r");
    return 0;
}