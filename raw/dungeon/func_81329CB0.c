#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s16 D_80083228;
extern u8 D_8006CCF8[];
extern void *D_80174CDC[3];

extern void func_80047738(void *, u8, s8);
extern void func_800478B8(void *);
extern void func_80171570(void) __attribute__((noreturn));

void func_801714B0(void *arg0, void *arg1, void *arg2)
{
    void *entity;
    u8 *table;
    s16 calculated_direction;
    s32 direction;

    entity = (u8 *)D_80174CDC[0] + 0x20;
    func_800478B8(arg2);
    if (D_80174CDC[0] != 0) {
        calculated_direction =
            ((D_80083228 + FIELD(entity, s16, 0x2A) + 0x100) >> 9) & 7;
        direction = calculated_direction;

        if (FIELD(arg0, s16, 0x94) != direction) {
            func_80047738(arg2,
                FIELD(arg2, u8 *, 0x2C)[direction],
                FIELD(arg2, s8, 4));
            FIELD(arg0, s16, 0x94) = calculated_direction;
        }

        table = D_8006CCF8;
        if (table[direction] != 0) {
            u32 tail_value;

            tail_value = FIELD(arg2, u16, 0x14) | 1;
            ASM_TAILSLOT_PIN_TIED(tail_value);
            func_80171570();
        }

        FIELD(arg2, u16, 0x14) &= 0xFFFE;
    }
}
