#include "common.h"

typedef void (*Callback)(void *);

extern u8 D_800C1E50[];
extern u8 D_800C1EA4[];
extern Callback D_800D4668[];

void *func_8003FC64(s32);

void func_800C1DD8(void) {
    Callback *callback = D_800D4668;
    void *object = func_8003FC64(0x11);

    if (object != 0) {
        *(void **)((u8 *)object + 0x10) = D_800C1E50;
        if (D_800D4668[0] != 0) {
            do {
                *callback = (Callback)D_800C1EA4;
                callback += 6;
            } while (*callback != 0);
        }
    }
}

/* MECHANISM: The callback table has a separately reusable page base and a live cursor;
   six Callback entries give the retail 0x18 stride, while the do-while preserves CFG. */
