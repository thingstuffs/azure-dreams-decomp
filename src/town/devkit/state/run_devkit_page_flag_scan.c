#include "common.h"
void func_80700C08(s32);                     /* extern */
void func_80701060(void);                            /* extern */

/* Devkit flag-test entry: select page 3, then run the page's flag scan. */
void run_devkit_page_3_flag_scan(void) {
    func_80700C08(3);
    func_80701060();
}

/* MECHANISM: The seed already had retail's 24-byte frame, sole $ra save, and two-call CFG. Zero | (3);
   }) prevents li/addiu folding and emits retail's ori $a0,$zero,3 in the first jal delay slot; every
   other word stays unchanged. */
