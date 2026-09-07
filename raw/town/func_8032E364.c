#include "common.h"

typedef struct {
    u32 value;
} __attribute__((packed)) UA32;

extern s8 D_80016000[];
extern UA32 D_8001C31C;

UA32 *func_80018B64(UA32 *arg0)
{
    register UA32 *ret ASM_REG("$9");
    register u8 *page ASM_REG("$3");
    register u8 *table ASM_REG("$10");
    register u32 hi ASM_REG("$2");
    register UA32 *src ASM_REG("$7");
    register UA32 **cursor ASM_REG("$8");
    register u8 *out ASM_REG("$7");
    register u8 *list ASM_REG("$2");
    u8 *root;
    u8 y;
    u8 x;
    u8 *row;

    ret = arg0;
    ASM_KEEP(ret);
    page = (u8 *)0x80010000;
    ASM_KEEP(page);
    root = *(u8 **)(page + 0x6000);
    table = *(u8 **)(*(u8 **)(root + 0x24) + 0x6C);
    ASM_KEEP(table);
    hi = 0x80020000;
    ASM_KEEP(hi);
    src = (UA32 *)(hi - 0x3CE4);
    ASM_KEEP(src);
    *ret = *src;
    ASM_KEEP(hi);

    root = *(u8 **)(page + 0x6000);
    list = *(u8 **)(root + 0x38);
    ASM_KEEP(list);
    cursor = (UA32 **)(list + 0x29C);
    ASM_KEEP(cursor);
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
    ASM_KEEP(out);
    *(s32 *)out = 0;
    return ret;
}

/* MECHANISM: A frameless leaf holds ret/page/table/cursor in the retail caller-saved roles.
   Packed UA32 assignments reproduce both lwl/lwr + swl/swr copies; split list/cursor names
   force the fresh null-check load, and integer-form scaled addition preserves operand order. */
