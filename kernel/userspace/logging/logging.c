/* 
* Author: Amilie (amilietf)
* Date: 2026-06-08
* Desc: Error handling for the kernel. Will be userspace for outputting to the FS at a later date.
* Lang: C
*/

#include "logging.h"
#include "../../drivers/video/vga.h"

void log_write(const char *s){
    print_to_screen(s); // just takes input from report_status, is the choke point.
}

// is routed via log_write
static void log_int(int n){
    char buf[12];
    int p = 0, neg = 0;
    if(n < 0){
        neg =1; n = -n;
    }do{
        buf[p++] = '0' + (n % 10); n /= 10;
    }while (n);

    char out[14];
    int j = 0;
    if(neg) out[j++] = buf[--p];
    while(p > 0) out[j++] = buf[--p];
    out[j] = '\0';
    log_write(out);
}

void report_status(const char *module, int code){
    log_write(code == 0 ? "[OK] " : "[FAIL] ");
    log_write(module);
    log_write(" code: ");
    log_int(code);
    log_write("\n");
}