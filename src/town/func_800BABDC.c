#include "common.h"

#ifdef NON_MATCHING
#include <stdint.h>
typedef uintptr_t uptr;
#else
typedef unsigned long uptr;
#endif

extern void func_800B7B48();
extern u8 D_800D2644[];
extern u8 D_800D2EA4[];

void func_800B833C(void)
{
    s32 i = 0;
    u8 *entity = D_800D2644;
    u8 *record = D_800D2EA4;
    u8 *page = (u8 *)0x80010000;
    u8 id;

    do {
        id = page[(i * 2) + 0x33A4];
        if (id != 0) {
            register s32 one ASM_REG("$3");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
            s16 *slot;

            func_800B7B48(record[0], record[1],
                          *(u8 *)((uptr)(id << 5) + (uptr)entity));
            id = page[(i * 2) + 0x33A4];
            one = 1;
            slot = (s16 *)((uptr)(id << 5) + (uptr)entity + 0xA);
            *slot = one;
        }
        record += 8;
        i++;
    } while (i < 0x21);
}
