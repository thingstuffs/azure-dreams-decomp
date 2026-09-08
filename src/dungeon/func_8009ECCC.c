#include "common.h"

#ifndef NULL
#define NULL 0
#endif

/* This data symbol is not present in the shared symbol catalog. */
__asm__(".set D_80081470, 0x80081470");

extern u8 D_80081470[];
extern void *D_800814A8;

/* Return the stored pointer when available, otherwise the fallback data buffer. */
u8 *func_800A442C(void) {
    u8 *stored_data;

    if (D_80081470[1] < 0x14U) {
        stored_data = *(u8 **)((u8 *)D_800814A8 + 0xF0);
        if (stored_data != NULL) {
            return stored_data;
        }
        *(s32 *)D_80081470 = 0;
    }
    return D_80081470;
}
