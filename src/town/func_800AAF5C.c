#include "common.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_800A86BC_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800A86BC_0;   /* arg1 in func_800A86BC */

typedef struct S_800A86BC_1_pre {
    u16 unk_00;
} S_800A86BC_1_pre;   /* the 0x2 bytes before arg0 in func_800A86BC, addressed as arg0[-1] */

typedef struct S_800A86BC_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    s32 unk_04;
} S_800A86BC_1;   /* arg0 in func_800A86BC */



#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_800478B8();
extern s32 D_800814A0[];

/* Update effect motion, fade its primitive, and flag expiration when its timer ends. */
void func_800A86BC(void *effect, S_800A86BC_0 *motion, Rec_D_80082E80 *primitive) {
    u8 shade;
    u16 ticks_left;

    motion->unk_14 = motion->unk_14 + ((S_800A86BC_1 *)effect)->unk_04;
    motion->unk_00 = motion->unk_00 + motion->unk_0C;
    motion->unk_04 = motion->unk_04 + motion->unk_10;
    motion->unk_08 = motion->unk_08 + motion->unk_14;
    func_800478B8(primitive);
    shade = primitive->unk_0C.at00_u8.v;
    if (shade != 0) {
        shade -= 0x10;
        primitive->unk_0C.at00_u8.v = shade;
        primitive->unk_0C.at02_u8.v = shade;
        primitive->unk_0C.at01_u8.v = shade;
    }
    ticks_left = ((S_800A86BC_1 *)effect)->unk_02 - 1;
    ((S_800A86BC_1 *)effect)->unk_02 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        ((S_800A86BC_1_pre *)effect)[-1].unk_00 = ((S_800A86BC_1_pre *)effect)[-1].unk_00 | 0x8000;
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
}
