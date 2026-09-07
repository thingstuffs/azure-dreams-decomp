#include "common.h"

typedef struct S_8009F1C0_0 {
    u8 pad_00[0x14];
    s8 unk_14;
    s8 unk_15;
} S_8009F1C0_0;   /* arg1 in func_8009F1C0 */

typedef struct S_8009F1C0_1 {
    u8 pad_00[0x4D];
    u8 unk_4D;
    u8 pad_4E[0x2];
    void * unk_50;
    u8 pad_54[0x18];
    s16 unk_6C;
    u8 pad_6E[0x27];
    u8 unk_95;
} S_8009F1C0_1;   /* arg0 in func_8009F1C0 */


extern u32 D_8009EF88;

typedef struct {
    s32 words[0x15];
} Record84;

extern Record84 D_80100AF8;


void func_8009F1C0(S_8009F1C0_1 *arg0, S_8009F1C0_0 *arg1)
{
    u8 state;
    void *callback;

    arg1->unk_14 = 4;
    callback = &D_8009EF88;
    arg1->unk_15 = 0;
    state = arg0->unk_4D;
    arg0->unk_50 = callback;
    arg0->unk_6C = 8;

    if (state == 0x13) {
        Record84 *records = (Record84 *)0x80010A80;
        u8 *table = (u8 *)0x80010000;

        
        D_80100AF8 = records
            [table[arg0->unk_95 * 4 + 0x983] & 0x3F];
    }
}
