#include "common.h"

#include "common.h"

void func_8003B7C8(void);
void func_8003B8DC(void);
void func_80043458();                            /* extern */

/* Runs the three Konami runtime routines in sequence. */
void func_8003B9B8(void) {
    func_80043458();
    func_8003B8DC();
    func_8003B7C8();
}
