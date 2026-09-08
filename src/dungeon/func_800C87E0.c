#include "common.h"

typedef struct {
    u8 pad0;
    u8 active;
    u8 pad2[2];
} ActiveEntry;

typedef struct {
    u8 x;
    u8 y;
    u8 pad2[2];
    s16 value;
    u8 pad6[6];
} FirstEntry;

typedef struct {
    u8 pad0[6];
    u8 x;
    u8 y;
    u8 pad8[10];
    s16 value;
    u8 pad20[4];
} SecondEntry;

extern ActiveEntry D_800E3548[64];
extern ActiveEntry D_800E3648[32];
extern FirstEntry D_800E36C8[64];
extern SecondEntry D_800E39C8[32];

void func_800CDF40(s16 arg0, s16 arg1, s16 arg2) {
    FirstEntry *entry1;
    ActiveEntry *status1;
    SecondEntry *entry2;
    ActiveEntry *status2;
    s32 i1;
    register s32 i2 ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 x1;
    s32 y1;
    s32 x2;
    s32 y2;

    i1 = 0;
    x1 = arg0;
    y1 = arg1;
    entry1 = D_800E36C8;
    status1 = D_800E3548;
    do {
        if (status1->active != 0 && entry1->x == x1 && entry1->y == y1) {
            entry1->value = arg2;
        }
        entry1++;
        i1++;
        status1++;
    } while (i1 < 64);

    i2 = 0;
    x2 = arg0;
    y2 = arg1;
    entry2 = D_800E39C8;
    status2 = D_800E3648;
    do {
        if (status2->active != 0 && entry2->x == x2 && entry2->y == y2) {
            entry2->value = arg2;
        }
        entry2++;
        i2++;
        status2++;
    } while (i2 < 32);
}

/* MECHANISM: Frameless leaf with exact 12-byte/24-byte record strides and narrow stores.
   Removing inherited keeps restored raw arg holds in t1/t2 and the exact 58-word shape.
   A guarded t0 pin for the second counter closed the final a1/a3/t0 role rotation. */
