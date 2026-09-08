#include "common.h"

typedef struct {
    u32 value;
} __attribute__((packed)) UA32;

extern s8 D_80016000[];
extern UA32 D_8001C31C;

UA32 *func_80018B64(UA32 *arg0)
{
    UA32 *ret;
    u8 *page;
    u8 *table;
    u32 hi;
    register UA32 *src ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    UA32 **cursor;
    register u8 *out ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    u8 *list;
    u8 *root;
    u8 y;
    u8 x;
    u8 *row;

    ret = arg0;
    page = (u8 *)0x80010000;
    ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    root = *(u8 **)(page + 0x6000);
    table = *(u8 **)(*(u8 **)(root + 0x24) + 0x6C);
    hi = 0x80020000;
    ASM_KEEP(hi);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    src = (UA32 *)(hi - 0x3CE4);
    ASM_KEEP(src);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    *ret = *src;
    ASM_KEEP(hi);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

    root = *(u8 **)(page + 0x6000);
    list = *(u8 **)(root + 0x38);
    cursor = (UA32 **)(list + 0x29C);
    out = (u8 *)ret + 4;
    if (*(UA32 **)(list + 0x29C) != 0) {
        do {
            *(UA32 *)out = **cursor;
            y = out[1];
            row = (u8 *)((u32)(y * 0x14) + (u32)table);
            x = out[0];
            if (*(s16 *)(*(u8 **)(row + 0xC) + (x * 0x14) + 0x12) == 0) {
                out[3] |= 0x80;
            }
            cursor++;
            out += 4;
        } while (*cursor != 0);
    }
    *(s32 *)out = 0;
    return ret;
}

/* MECHANISM: A frameless leaf holds ret/page/table/cursor in the retail caller-saved roles.
   Packed UA32 assignments reproduce both lwl/lwr + swl/swr copies; split list/cursor names
   force the fresh null-check load, and integer-form scaled addition preserves operand order. */
