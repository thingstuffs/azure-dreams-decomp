#include "common.h"
#include "records/Rec_D_800E3D7C.h"



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
    u8 *table_page;
    u8 ch;

    if ((((Rec_D_800E3D7C *)D_800E3D7C)->unk_1C.as_s32 & 0x10) &&
        (((Rec_D_800E3D7C *)record)->unk_10.at03_u8.v != 0)) {
        src = (u8 *)D_800DD728;
        goto copy;
    }

    if (((Rec_D_800E3D7C *)record)->unk_14.as_s32 & 0x4000) {
        src = (u8 *)record + 0x34;
        goto copy;
    }

    text_index = ((Rec_D_800E3D7C *)record)->unk_10.at03_u8.v;
    if (text_index == 0x23) {
        if (((Rec_D_800E3D7C *)record)->unk_A4.at02_s16.v != 0) {
            src = (u8 *)D_800DD728;
            goto copy;
        }
        table_page = (u8 *)0x80070000;
    } else {
        table_page = (u8 *)0x80070000;
    }
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
