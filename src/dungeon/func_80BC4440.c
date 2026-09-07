#include "common.h"

typedef struct S_80173C40_0 {
    u8 pad_00[0xA4];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_A4;   /* overlapping accesses */
    s32 unk_A8;
    s32 unk_AC;
    s32 unk_B0;
} S_80173C40_0;   /* arg0 in func_80173C40 */


extern void func_800AB538(void);


void func_80173C40(S_80173C40_0 *arg0) {
    s32 field_A4;

    func_800AB538();
    field_A4 = arg0->unk_A4.at00.v;
    arg0->unk_A4.at02.v = 0;
    arg0->unk_AC = 0;
    arg0->unk_B0 = 0;
    arg0->unk_A8 = field_A4;
}
