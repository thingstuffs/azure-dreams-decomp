#include "common.h"

typedef struct {
    s32 words[6];
} Copy24;

extern void func_8003EA54(s32 arg0);
extern s32 D_80084D5C;

/* Copy an entry's 24-byte payload, decrement its count, and flag exhaustion. */
void func_8080E480(void *entry, Copy24 *dst, s32 call_arg) {
    u16 remaining;
    Copy24 *payload;

    func_8003EA54(call_arg);
    payload = *(Copy24 **)((u8 *)entry + 4);
    *dst = *payload;

    remaining = *(u16 *)((u8 *)entry + 2) - 1;
    *(u16 *)((u8 *)entry + 2) = remaining;
    if ((remaining << 16) <= 0) {
        *(u16 *)((u8 *)entry - 2) |= 0x8000;
        D_80084D5C |= 0x8000;
    }
}
