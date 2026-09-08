#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800478B8();                      /* extern */
typedef struct { s32 v; s32 pad[2]; } S_800814A0;
extern S_800814A0 D_800814A0;


typedef struct S_800CB374_0_pre {
    u16 unk_00;
} S_800CB374_0_pre;   /* the 0x2 bytes before arg0 in func_800CB374, addressed as arg0[-1] */

typedef struct S_800CB374_0 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x10];
    void * unk_A8;
    u8 pad_AC[0x8];
    s16 unk_B4;
} S_800CB374_0;   /* arg0 in func_800CB374 */

typedef struct S_800CB374_1 {
    u8 pad_00[0x6];
    u16 unk_06;
    u8 pad_08[0x4];
    union { struct { u8 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_0C;   /* overlapping accesses */
    u8 pad_10[0xC];
    u16 unk_1C;
    u16 unk_1E;
} S_800CB374_1;   /* arg2 in func_800CB374 */

typedef struct S_800CB374_2 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
} S_800CB374_2;   /* temp_v1 in func_800CB374 */

typedef struct S_800CB374_3 {
    u8 pad_00[0xC];
    void * unk_0C;
    u8 pad_10[0xE];
    u16 unk_1E;
    u8 pad_20[0xAC];
    s32 unk_CC;
} S_800CB374_3;   /* ((S_800CB374_0 *)arg0)->unk_A8 in func_800CB374 */

/* Fades primitive colors or copies source attributes and propagates completion flags. */
void func_800CB374(void *effect, void *unused, S_800CB374_1 *primitive) {
    s16 fade_steps;
    u8 blue;
    S_800CB374_2 *source_primitive;

    func_800478B8(primitive);
    if (((S_800CB374_0 *)effect)->unk_B4 != 0) {
        primitive->unk_0C.at00.v = (u8) (primitive->unk_0C.at00.v - ((s32) primitive->unk_0C.at00.v / (s16) ((S_800CB374_0 *)effect)->unk_96));
        primitive->unk_0C.at01.v = (u8) (primitive->unk_0C.at01.v - ((s32) primitive->unk_0C.at01.v / (s16) ((S_800CB374_0 *)effect)->unk_96));
        blue = primitive->unk_0C.at02.v - ((s32) primitive->unk_0C.at02.v / (s16) ((S_800CB374_0 *)effect)->unk_96);
        primitive->unk_0C.at02.v = blue;
        primitive->unk_06 = (u16) (primitive->unk_06 - 1);
        fade_steps = (u16) ((S_800CB374_0 *)effect)->unk_96 - 1;
        ((S_800CB374_0 *)effect)->unk_96 = fade_steps;
        if ((fade_steps << 0x10) > 0) {
            return;
        }
        goto mark_complete;
    }
    primitive->unk_0C.at00u.v = ((S_800CB374_3 *)(((S_800CB374_0 *)effect)->unk_A8))->unk_CC;
    source_primitive = ((S_800CB374_3 *)(((S_800CB374_0 *)effect)->unk_A8))->unk_0C;
    primitive->unk_1C = (u16) source_primitive->unk_1C;
    primitive->unk_1E = (u16) source_primitive->unk_1E;
    if (((S_800CB374_3 *)(((S_800CB374_0 *)effect)->unk_A8))->unk_1E & 0x8000) {
mark_complete:
        ((S_800CB374_0_pre *)effect)[-1].unk_00 = (u16) (((S_800CB374_0_pre *)effect)[-1].unk_00 | 0x8000);
        D_800814A0.v |= 0x8000;
    }
}
