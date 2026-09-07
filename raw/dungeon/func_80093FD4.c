#include "common.h"

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))

extern s32 D_8007359C;
extern s32 D_800DD728;
extern u8 *D_800E3D7C;

u8 *func_80099734(void *arg0, u8 *out)
{
    u8 *src;
    register s32 index ASM_REG("$3");
    register s32 offset ASM_REG("$2");
    register u8 *table_page ASM_REG("$4");
    u8 ch;

    if ((FIELD(D_800E3D7C, s32, 0x1C) & 0x10) &&
        (FIELD(arg0, u8, 0x13) != 0)) {
        src = (u8 *)D_800DD728;
        goto copy;
    }

    if (FIELD(arg0, s32, 0x14) & 0x4000) {
        src = (u8 *)arg0 + 0x34;
        goto copy;
    }

    index = FIELD(arg0, u8, 0x13);
    if (index == 0x23) {
        if (FIELD(arg0, s16, 0xA6) != 0) {
            src = (u8 *)D_800DD728;
            goto copy;
        }
    }
    ASM_KEEP_NV(index);
    table_page = (u8 *)0x80070000;
    ASM_KEEP_NV(table_page);
    offset = index * 5;
    ASM_KEEP_NV(offset);
    src = FIELD((u8 *)FIELD(table_page, s32, 0x359C) + offset * 4, u8 *, 4);

copy:
    ch = *src;
    if (ch != 0) {
        do {
            src++;
            *out = ch;
            ch = *src;
            out++;
        } while (ch != 0);
    }
    return out;
}

/* MECHANISM: Frameless true-space leaf; both apparent calls are local joins into copy.
   Nested tests preserve the branch/delay-slot CFG and the exact 50-word layout.
   Short lookup roles hold v1=index/table, v0=index*5, and a0=0x80070000 page. */
