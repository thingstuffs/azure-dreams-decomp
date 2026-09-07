#include "common.h"

#ifndef NULL
#define NULL 0
#endif

extern void *D_8001029C;
__asm__(".set D_8001029C, 0x8001029C");

void *func_8009EBE0(s32 arg0, s32 arg1) {
    void **var_a2;
    void *temp_v1;

    if (D_8001029C != NULL) {
        var_a2 = &D_8001029C;
        do {
            temp_v1 = *var_a2;
            if ((((u8 *)temp_v1)[0] == arg0) && (((u8 *)temp_v1)[1] == arg1)) {
                return temp_v1;
            }
            var_a2 += 1;
        } while (*var_a2 != NULL);
    }
    return NULL;
}
