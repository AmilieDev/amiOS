/* 
* Author: Amilie (amilietf)
* Date: 2026-06-08
* Desc: A temporary application for testing logging.
* Lang: C
*/

#include "../../drivers/video/vga.h"

int logging_main(void){
    print_to_screen("hi from the logging test app\n");
    return 0;
}