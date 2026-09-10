#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80173738_0_pre {
    u16 unk_00;
} S_80173738_0_pre;   /* the 0x2 bytes before arg0 in func_80173738, addressed as arg0[-1] */

typedef struct S_80173738_0 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[0x17];
    s16 unk_1A;
    u8 pad_1C[0x2];
    u16 unk_1E;
    u16 unk_20;
    u8 pad_22[0x1E];
    s32 unk_40;
    s32 unk_44;
} S_80173738_0;   /* arg0 in func_80173738 */


typedef struct S_80173738_2 {
    s32 unk_00;
} S_80173738_2;   /* D_800814A0 in func_80173738 */


typedef struct {
    s32 unk00;
    s32 unk04;
    s32 unk08;
} FuncArg1;

M2C_UNK func_8003DB94();
M2C_UNK func_800478B8(void *, s32);
s32 func_800644B8();
s32 func_80064584();
extern s32 D_800814A0[];
extern M2C_UNK D_800DEC70;

/* Move the effect in an expanding spiral, fade its color, and flag it when its lifetime ends. */
void func_80173738(void *effect, FuncArg1 *position, Rec_D_80082E80 *primitive) {
    s16 life;
    s16 next_life;
    s32 y_offset;
    s32 base_y;
    s32 z_step;
    void *primitive_dst;

    ((S_80173738_0 *)effect)->unk_1E = (u16) (((S_80173738_0 *)effect)->unk_1E - 0x12C);
    ((S_80173738_0 *)effect)->unk_20 = (u16) (((S_80173738_0 *)effect)->unk_20 + 2);
    position->unk00 = (s32) (((S_80173738_0 *)effect)->unk_40 + ((s16) ((S_80173738_0 *)effect)->unk_20 * func_80064584((s16) ((S_80173738_0 *)effect)->unk_1E) * 0x10));
    y_offset = (s16) ((S_80173738_0 *)effect)->unk_20 * func_800644B8((s16) ((S_80173738_0 *)effect)->unk_1E);
    primitive_dst = primitive;
    z_step = (0xFFF40000U) + y_offset;
    z_step -= y_offset;
    base_y = ((S_80173738_0 *)effect)->unk_44;
    position->unk08 = (s32) (position->unk08 + z_step);
    position->unk04 = (s32) (base_y + (y_offset * 0x10));
    func_800478B8(primitive_dst, z_step);
    if (primitive->unk_14.at00_u16.v & 0x4000) {
        func_8003DB94(primitive, &D_800DEC70, 0);
    }
    life = ((S_80173738_0 *)effect)->unk_1A;
    if (life < 0xA) {
        primitive->unk_0C.at00_s8.v = (s8) ((((S_80173738_0 *)effect)->unk_00 * life) / 9);
        primitive->unk_0C.at01_s8.v = (s8) ((((S_80173738_0 *)effect)->unk_01 * ((S_80173738_0 *)effect)->unk_1A) / 9);
        primitive->unk_0C.at02_s8.v = (s8) ((((S_80173738_0 *)effect)->unk_02 * ((S_80173738_0 *)effect)->unk_1A) / 9);
    }
    next_life = (u16) ((S_80173738_0 *)effect)->unk_1A - 1;
    ((S_80173738_0 *)effect)->unk_1A = next_life;
    if ((next_life << 0x10) <= 0) {
        ((S_80173738_0_pre *)effect)[-1].unk_00 = (u16) (((S_80173738_0_pre *)effect)[-1].unk_00 | 0x8000);
        ((S_80173738_2 *)D_800814A0)->unk_00 = (s32) (((S_80173738_2 *)D_800814A0)->unk_00 | 0x8000);
    }
}
