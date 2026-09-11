#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800DAB50_0_pre {
    u16 unk_00;
} S_800DAB50_0_pre;   /* the 0x2 bytes before var_s2 in func_800DAB50, addressed as var_s2[-1] */

typedef struct S_800DAB50_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    union { u16 s; volatile u16 u; } unk_02;   /* accessed as both */
    s16 unk_04;
    u8 pad_06[0x2];
    s16 unk_08;
    union { u16 s; s16 u; } unk_0A;   /* accessed as both */
    s32 unk_0C;
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_10;   /* overlapping accesses */
    u8 pad_14[0xC];
    u16 unk_20;
    u16 unk_22;
    u16 unk_24;
} S_800DAB50_0;   /* var_s2 in func_800DAB50 */

typedef struct S_800DAB50_1 {
    u8 pad_00[0x28];
    u16 unk_28;
    u16 unk_2A;
    u16 unk_2C;
} S_800DAB50_1;   /* p in func_800DAB50 */


typedef struct WorkBlock {
    s16 *unk0;
    s16 *unk4;
    s32 unk8;
    u16 unkC;
    s32 unk10;
    s32 unk14;
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    s16 unk1E;
    s16 unk20;
    s16 unk22;
    s16 unk24;
    s16 unk26;
    s16 unk28;
    s16 unk2A;
    s16 unk2C;
} WorkBlock;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 D_800814A0[3];
extern s32 func_800644B8();
extern s32 func_80066460();
extern void func_800DBA90(WorkBlock *);

/* Update the effect vertices, animate their color, and advance the rotation. */
void func_800DAB50(void *effect_data) {
    WorkBlock work;
    void *effect = effect_data;
    s32 index;
    register s32 vertex_offset ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 color_step ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 color_value;
    s32 updated_value;
    register s32 phase_value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 state;

    work.unk28 = 0;
    work.unk20 = 0;
    if (((S_800DAB50_0 *)effect)->unk_08 != 0) {
        work.unk22 = 0x30;
        work.unk2A = ((S_800DAB50_0 *)effect)->unk_02.s + 0x30;
    } else {
        phase_value = ((S_800DAB50_0 *)effect)->unk_02.s;
        work.unk2A = 0x30;
        work.unk22 = (phase_value * 2) + 0x40;
    }
    index = 0;
    work.unk24 = (s16)(func_800644B8(((s16)((S_800DAB50_0 *)effect)->unk_02.s - 0x20) << 6) >> 6);
    work.unk0 = &work.unk20;
    work.unk2C = 0;
    work.unk18 = 2;
    phase_value = ((S_800DAB50_0 *)effect)->unk_0A.s;
    vertex_offset = 0x28;
    work.unk8 = 0;
    work.unk14 = 0;
    work.unk10 = 0;
    work.unk1A = 0;
    work.unkC = phase_value;
    do {
        work.unk4 = (s16 *)((s8 *)effect + vertex_offset);
        func_800DBA90(&work);
        phase_value = work.unkC;
        do {
            index += 1;
        } while (0);
        work.unkC = phase_value + 0x200;
        vertex_offset += 0x10;
    } while (index < 2);

    index = 3;
    {
        register s16 *vertex ASM_REG("$4") = (s16 *)((s8 *)effect + 0x18);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        do {
            ((S_800DAB50_1 *)vertex)->unk_28 = (u16)(((S_800DAB50_1 *)vertex)->unk_28 + ((S_800DAB50_0 *)effect)->unk_20);
            ((S_800DAB50_1 *)vertex)->unk_2A = (u16)(((S_800DAB50_1 *)vertex)->unk_2A + ((S_800DAB50_0 *)effect)->unk_22);
            index -= 1;
            ((S_800DAB50_1 *)vertex)->unk_2C = (u16)(((S_800DAB50_1 *)vertex)->unk_2C + ((S_800DAB50_0 *)effect)->unk_24);
            vertex -= 4;
        } while (index >= 0);
    }

    state = ((S_800DAB50_0 *)effect)->unk_00.s;
    switch (state) {
    case 0: goto init_color;
    case 1: goto brighten;
    case 2: goto dim_color;
    case 3: goto fade_out;
    default: goto update_angle;
    }

init_color:
    ((S_800DAB50_0 *)effect)->unk_10.at00.v = 0;
    ((S_800DAB50_0 *)effect)->unk_04 = func_80066460(0, 1, 0x2C0, 0x100);
    ((S_800DAB50_0 *)effect)->unk_0C = 0x242424;
    ((S_800DAB50_0 *)effect)->unk_00.s = (s16)((u16)((S_800DAB50_0 *)effect)->unk_00.s + 1);
    goto brighten;

brighten:
    ((S_800DAB50_0 *)effect)->unk_10.at00.v = ((S_800DAB50_0 *)effect)->unk_10.at00.v + ((S_800DAB50_0 *)effect)->unk_0C;
    color_step = 0;
    if (((S_800DAB50_0 *)effect)->unk_10.at03.v != 0) {
        phase_value = func_80066460(0, 3, 0x2C0, 0x100);
        color_value = 0xFFFFFF;
        goto advance_state;
    }
    goto update_angle;

dim_color:
    ((S_800DAB50_0 *)effect)->unk_10.at00.v = ((S_800DAB50_0 *)effect)->unk_10.at00.v - ((S_800DAB50_0 *)effect)->unk_0C;
    color_step = 0;
    if ((u8)((S_800DAB50_0 *)effect)->unk_10.at00.v == 0x7F) {
        phase_value = func_80066460(0, 3, 0x2C0, 0x100);
        color_value = 0xA0A0A0;
advance_state:
        color_step = 0x101010;
        state = ((S_800DAB50_0 *)effect)->unk_00.u;
        ((S_800DAB50_0 *)effect)->unk_04 = phase_value;
        ((S_800DAB50_0 *)effect)->unk_10.at00.v = color_value;

        ((S_800DAB50_0 *)effect)->unk_0C = color_step;
        state += 1;
        ((S_800DAB50_0 *)effect)->unk_00.s = state;
        goto update_angle;
    }
    goto update_angle;

fade_out:
    color_step = ((S_800DAB50_0 *)effect)->unk_0C;
    color_value = color_step;
    updated_value = ((S_800DAB50_0 *)effect)->unk_10.at00.v - color_step;
    ((S_800DAB50_0 *)effect)->unk_10.at00.v = updated_value;
    if (color_value > 0x80808) {
        ((S_800DAB50_0 *)effect)->unk_0C = color_value + 0xFFFEFEFF;
    }
    if (((S_800DAB50_0 *)effect)->unk_10.at00.v < 0) {
        ((S_800DAB50_0 *)effect)->unk_10.at00.v = 0;
        ((S_800DAB50_0_pre *)effect)[-1].unk_00 = (u16)(((S_800DAB50_0_pre *)effect)[-1].unk_00 | 0x8000);
        D_800814A0[0] |= 0x8000;
    }

    ASM_USE_NV(color_step); /* MATCH: keep a0 live so the subtraction uses a0 after the a1 copy. */

update_angle:
    phase_value = ((S_800DAB50_0 *)effect)->unk_02.u;
    phase_value <<= 0x10;
    updated_value = phase_value >> 0xE;
    phase_value >>= 0x11;
    index = updated_value + phase_value;
    phase_value = ((S_800DAB50_0 *)effect)->unk_08;
    updated_value = ((S_800DAB50_0 *)effect)->unk_0A.u;
    if (phase_value == 0) {
        updated_value -= index;
    } else {
        updated_value += index;

    }
    phase_value = ((S_800DAB50_0 *)effect)->unk_02.u;
    ((S_800DAB50_0 *)effect)->unk_0A.s = updated_value;
    ((S_800DAB50_0 *)effect)->unk_02.s = phase_value - 1;
}
