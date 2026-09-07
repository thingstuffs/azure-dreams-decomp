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

/* Copies the selected record text without its terminator and returns the output end. */
u8 *func_80099734(void *record, u8 *out)
{
    u8 *src;
    s32 text_index;
    s32 word_offset;
    register u8 *table_page ASM_REG("$4");   /* MATCH pin: retail delay-slot fill depends on it */
    u8 ch;

    if ((((S_80099734_0 *)D_800E3D7C)->unk_1C & 0x10) &&
        (((S_80099734_1 *)record)->unk_13 != 0)) {
        src = (u8 *)D_800DD728;
        goto copy;
    }

    if (((S_80099734_1 *)record)->unk_14 & 0x4000) {
        src = (u8 *)record + 0x34;
        goto copy;
    }

    text_index = ((S_80099734_1 *)record)->unk_13;
    if (text_index == 0x23) {
        if (((S_80099734_1 *)record)->unk_A6 != 0) {
            src = (u8 *)D_800DD728;
            goto copy;
        }
    }
    table_page = (u8 *)0x80070000;
    ASM_KEEP_NV(table_page);   /* MATCH pin: load-bearing for the whole function shape */
    word_offset = text_index * 5;
    src = ((S_80099734_3 *)((u8 *)((S_80099734_2 *)table_page)->unk_359C + word_offset * 4))->unk_04;

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
