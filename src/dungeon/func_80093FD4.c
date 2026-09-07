#include "common.h"

typedef struct S_80099734_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_80099734_0;   /* D_800E3D7C in func_80099734 */

typedef struct S_80099734_1 {
    u8 pad_00[0x13];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[0x8E];
    s16 unk_A6;
} S_80099734_1;   /* arg0 in func_80099734 */

typedef struct S_80099734_2 {
    u8 pad_00[0x359C];
    s32 unk_359C;
} S_80099734_2;   /* table_page in func_80099734 */

typedef struct S_80099734_3 {
    u8 pad_00[0x4];
    u8 * unk_04;
} S_80099734_3;   /* (u8 *)((S_80099734_2 *)table_page)->unk_359C + offset * 4 in func_80099734 */



extern s32 D_8007359C;
extern s32 D_800DD728;
extern u8 *D_800E3D7C;

u8 *func_80099734(void *arg0, u8 *out)
{
    u8 *src;
    s32 index;
    s32 offset;
    register u8 *table_page ASM_REG("$4");   /* MATCH pin: retail delay-slot fill depends on it */
    u8 ch;

    if ((((S_80099734_0 *)D_800E3D7C)->unk_1C & 0x10) &&
        (((S_80099734_1 *)arg0)->unk_13 != 0)) {
        src = (u8 *)D_800DD728;
        goto copy;
    }

    if (((S_80099734_1 *)arg0)->unk_14 & 0x4000) {
        src = (u8 *)arg0 + 0x34;
        goto copy;
    }

    index = ((S_80099734_1 *)arg0)->unk_13;
    if (index == 0x23) {
        if (((S_80099734_1 *)arg0)->unk_A6 != 0) {
            src = (u8 *)D_800DD728;
            goto copy;
        }
    }
    table_page = (u8 *)0x80070000;
    ASM_KEEP_NV(table_page);   /* MATCH pin: load-bearing for the whole function shape */
    offset = index * 5;
    src = ((S_80099734_3 *)((u8 *)((S_80099734_2 *)table_page)->unk_359C + offset * 4))->unk_04;

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
