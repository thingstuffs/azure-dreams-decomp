#include "common.h"

#include "common.h"
void func_8003B64C(void);                            /* extern */
void func_8003B8DC(void);                            /* extern */
void func_80043458();                            /* extern */

/* Runs the three runtime routines in sequence. */
void func_8003B988(void) {
    func_80043458();
    func_8003B64C();
    func_8003B8DC();
}
