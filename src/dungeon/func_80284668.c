#include "common.h"



#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((u8 *)(expr) + (offset)))

extern u8 D_8008333C[32];
extern u8 D_800EA000[];


void func_80017668(s16 arg0, s16 arg1, s16 arg2, s32 arg3, u16 arg4) {
    s32 outer;
    register u16 value ASM_REG("$11");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 inner ASM_REG("$7") = arg3;   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    register s32 arg2_shift ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 arg0_shift;
    s32 column;
    register s32 row;
    s16 *settings;
    s32 temp;
    s32 index;
    u16 *entry;

    outer = arg3;
    do { value = arg4; } while (0);
    settings = (s16 *)D_8008333C;
    inner <<= 16;
    if (inner > 0) {
        arg2_shift = arg2 << 16;
        arg0_shift = arg0 << 16;
        do {
            inner = arg2_shift >> 16;
            column = arg0_shift >> 16;
            if (inner > 0) {
                row = arg1;
                do {
                    inner--;
                    index = settings[10];
                    index = row << index;
                    index += column;
                    column++;
                    entry = (u16 *)(D_800EA000 + index * 6);
                    entry[2] = value;
                } while (inner > 0);
            }
            temp = outer - 1;
            outer = temp;
            ASM_KEEP(temp);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            arg1++;
        } while ((temp << 16) > 0);
    }
}

/* MECHANISM: Frameless leaf with pinned argument/live-range roles reproduces the retail temporaries.
   ASM_KEEP(temp) after the outer decrement blocks CSE from substituting $t2,
   preserving retail's final sll $v0,$v0,16 at word 28. */
