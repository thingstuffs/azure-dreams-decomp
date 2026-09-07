#include "common.h"

extern void func_800241D4(void *, s32);
extern void func_80024224(void *, s32);
extern void func_80024274(void *);
extern void func_80024F3C(s32, s32, s32);
extern void func_8002515C(void);

void func_800250E8(void *arg0)
{
    s32 index;
    u8 *entry;

    index = 0;
    entry = arg0;
    do {
        if (index == *(s32 *)((u8 *)arg0 + 0x2C)) {
            func_80024224(*(void **)(entry + 4), 1);
            func_8002515C();
            entry += 4;
        }
        if (index == *(s32 *)((u8 *)arg0 + 0x28)) {
            func_800241D4(*(void **)(entry + 4), 1);
            func_8002515C();
            entry += 4;
        }
        func_80024274(*(void **)(entry + 4));
        entry += 4;
        index++;
    } while (index < 5);

    func_80024F3C(
        *(s32 *)((u8 *)arg0 + 0x1C),
        *(s32 *)((u8 *)arg0 + 0x28),
        *(s32 *)((u8 *)arg0 + 0x44)
    );
}
