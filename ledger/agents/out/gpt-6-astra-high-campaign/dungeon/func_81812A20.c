#include "common.h"

extern void (*D_80029514[])(void);

/* Call the indexed callback when the record is enabled. */
void func_80027A20(s32 *record) {
    if (record[8] != 0) {
        D_80029514[record[5]]();
    }
}
