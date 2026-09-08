#include "common.h"

typedef struct {
    s32 value[5];
} TownFiveWords;

typedef struct {
    s32 value[4];
} TownFourWords;

extern TownFiveWords D_800894D0;
extern TownFourWords D_800895F0;
extern u8 D_800133A6;
extern u8 D_800133A7;
extern u8 D_800133BA;
extern u8 D_800133BB;
extern u8 D_800133C8;
extern u8 D_800133C9;
extern u8 D_800133E6;
extern s8 D_800133E7[9];

s32 func_800B8C90(void)
{
    TownFiveWords first = D_800894D0;
    TownFourWords second = D_800895F0;
    s32 *outer;
    s32 *inner;
    u8 *page;
    u8 *entry;
    s32 wanted;
    s32 limit;
    s32 i;
    s32 j;
    s32 compare;

    compare = 3;
    if (D_800133BA != compare) {
        u8 *other = (u8 *)0x80010000;

        if (other[0x33BB] != compare) {
            return 0;
        }
        ASM_KEEP(other);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    }
    compare = 0x29;
    if (D_800133E6 != compare) {
        u8 *other = (u8 *)0x80010000;

        if (other[0x33E7] != compare) {
            return 0;
        }
        ASM_KEEP(other);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    }
    compare = 7;
    if (D_800133C8 != compare) {
        u8 *other = (u8 *)0x80010000;

        if (other[0x33C9] != compare) {
            return 0;
        }
        ASM_KEEP(other);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    }
    compare = 10;
    if (D_800133A6 != compare) {
        register u8 *other ASM_REG("$3") = (u8 *)0x80010000;   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

        ASM_KEEP(other);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        i = 0;
        if (other[0x33A7] != compare) {
return_zero:
            return 0;
        }
        goto loop_preheader;
    }
    i = 0;
loop_preheader:

    page = (u8 *)0x80010000;
    limit = 5;
    outer = first.value;
    do {
        j = 0;
        wanted = outer[6];
        inner = first.value;
        do {
            entry = (u8 *)((u32)(*inner * 2) + (u32)page);
            if ((entry[0x33A4] == wanted) || (entry[0x33A5] == wanted)) {
                break;
            }
            j++;
            inner++;
        } while (j < 5);
        if (j == limit) {
            goto return_zero;
        }
        i++;
        outer++;
    } while (i < 4);
    ASM_KEEP(outer);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    return 1;
}

/* MECHANISM: sibling five-word/four-word aggregates create the frameless 0x28 copy layout.
   A shared early zero-return label restores the backward failure edge and removes tail drift.
   Scoped page pins plus t0/a3/t1/t2 role pins reproduce the retail loop live ranges.
   Integer-domain index+page addition preserves the final addu operand order. */
