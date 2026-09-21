#include "common.h"
#include "records/Rec_D_800814A8.h"

typedef struct S_8197192C_0_pre {
    u16 unk_00;
} S_8197192C_0_pre;   /* the 0x2 bytes before arg0 in func_8197192C, addressed as arg0[-1] */

typedef struct S_8197192C_0 {
    u8 pad_00[0x4];
    void * unk_04;
    u8 unk_08;
    u8 pad_09[0x1];
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x20];
    union { u16 s; s16 u; } unk_2C;   /* accessed as both */
    union { s16 s; u16 u; } unk_2E;   /* accessed as both */
    union { s16 s; u16 u; } unk_30;   /* accessed as both */
    union { s16 s; u16 u; } unk_32;   /* accessed as both */
    u16 unk_34;
    u8 pad_36[0x2];
    u16 unk_38;
    u8 pad_3A[0x12];
    union { u16 s; s16 u; } unk_4C;   /* accessed as both */
    union { u16 s; s16 u; } unk_4E;   /* accessed as both */
    union { u16 s; s16 u; } unk_50;   /* accessed as both */
    u16 unk_52;
    u16 unk_54;
    u16 unk_56;
    union { u16 s; s16 u; } unk_58;   /* accessed as both */
    union { u16 s; s16 u; } unk_5A;   /* accessed as both */
    union { u16 s; s16 u; } unk_5C;   /* accessed as both */
    u16 unk_5E;
    u16 unk_60;
    u16 unk_62;
    union { u16 s; s16 u; } unk_64;   /* accessed as both */
    union { u16 s; s16 u; } unk_66;   /* accessed as both */
    union { u16 s; s16 u; } unk_68;   /* accessed as both */
    u16 unk_6A;
    u16 unk_6C;
    u16 unk_6E;
    union { u16 s; s16 u; } unk_70;   /* accessed as both */
    union { u16 s; s16 u; } unk_72;   /* accessed as both */
    union { u16 s; s16 u; } unk_74;   /* accessed as both */
    u16 unk_76;
    u16 unk_78;
    u16 unk_7A;
    union { u16 s; s16 u; } unk_7C;   /* accessed as both */
    union { u16 s; s16 u; } unk_7E;   /* accessed as both */
    union { u16 s; s16 u; } unk_80;   /* accessed as both */
} S_8197192C_0;   /* arg0 in func_8197192C */

typedef struct S_8197192C_1_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_8197192C_1_pre;   /* the 0x18 bytes before obj in func_8197192C, addressed as obj[-1] */

typedef struct S_8197192C_1 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 * unk_0C;
    union { struct { void * v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_10;   /* overlapping accesses */
    u8 pad_14[0x16];
    u16 unk_2A;
    u8 pad_2C[0x6A];
    s16 unk_96;
    u8 pad_98[0xE];
    u16 unk_A6;
    u8 unk_A8;
    u8 pad_A9[0x4B];
    s32 unk_F4;
} S_8197192C_1;   /* obj in func_8197192C */

typedef struct S_8197192C_2 {
    u16 unk_00;
} S_8197192C_2;   /* D_80082E86 in func_8197192C */

typedef struct S_8197192C_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8197192C_3;   /* gbase in func_8197192C */

typedef struct S_8197192C_4 {
    u16 unk_00;
} S_8197192C_4;   /* D_80025FF4 in func_8197192C */

typedef struct S_8197192C_5 {
    u8 pad_00[0x8];
    void * unk_08;
} S_8197192C_5;   /* map_base in func_8197192C */

typedef struct S_8197192C_7 {
    u8 pad_00[0xC];
    u32 unk_0C;
    u32 unk_10;
    u32 unk_14;
    u32 unk_18;
    u32 unk_1C;
    u32 unk_20;
    u32 unk_24;
    u32 unk_28;
    u8 pad_2C[0xC];
    u16 unk_38;
    u16 unk_3A;
    u8 pad_3C[0x10];
    u16 unk_4C;
    u16 unk_4E;
    u16 unk_50;
    u16 unk_52;
    u16 unk_54;
    u16 unk_56;
    u16 unk_58;
    u16 unk_5A;
    u16 unk_5C;
    u16 unk_5E;
    u16 unk_60;
    u16 unk_62;
} S_8197192C_7;   /* work in func_8197192C */

typedef struct S_8197192C_8 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_8197192C_8;   /* part in func_8197192C */

typedef struct S_8197192C_9 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x40];
    s16 unk_4C;
    s16 unk_4E;
    s16 unk_50;
} S_8197192C_9;   /* dst in func_8197192C */

typedef struct S_8197192C_10 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8197192C_10;   /* gbase3 in func_8197192C */

typedef struct S_8197192C_11 {
    u8 pad_00[0x4C];
    s16 unk_4C;
    s16 unk_4E;
    s16 unk_50;
} S_8197192C_11;   /* dst2 in func_8197192C */

typedef struct S_8197192C_12 {
    u8 pad_00[0x2E94];
    u16 unk_2E94;
} S_8197192C_12;   /* status_page in func_8197192C */

typedef struct S_8197192C_13 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_8197192C_13;   /* cleanup_obj in func_8197192C */

typedef struct S_8197192C_14 {
    u16 unk_00;
} S_8197192C_14;   /* ((S_8197192C_0 *)arg0)->unk_04 in func_8197192C */

typedef struct S_8197192C_15 {
    u8 pad_00[0x60];
    void * unk_60;
} S_8197192C_15;   /* ((Rec_D_800814A8 *)&D_800814A8)->unk_00.as_pv in func_8197192C */

typedef struct {
    u8 bytes[12];
} Data12;

/* These data objects are present in the retail image but are not in the
 * current symbol catalog.  Keep the bindings narrow: they are not local
 * definitions, only names for the linked overlay data. */
__asm__(".set D_80024058, 0x80024058");
__asm__(".set D_80024B98, 0x80024B98");
__asm__(".set D_80024D10, 0x80024D10");
__asm__(".set D_80024544, 0x80024544");
__asm__(".set D_80025FD0, 0x80025FD0");
__asm__(".set D_80025FDC, 0x80025FDC");
__asm__(".set D_800DDC40, 0x800DDC40");

extern void *D_80024058[];
extern void *D_80024B98;
extern void *D_80024D10;
extern void *D_80024544;
extern u8 D_80045340[];
extern Data12 D_80025FD0;
extern Data12 D_80025FDC;
extern u8 D_800DDC40[];

extern void *D_800814A8[3];
extern void *D_800814A8_case0[3] __asm__("D_800814A8");
extern s32 D_800814A0[3];
extern u16 D_80082E86[5];
extern u16 D_80082E94[5];
extern void *D_80082E80[10];
extern u8 D_80083460[];
extern u8 D_80083780[12];
extern s16 D_80025FF4[5];

extern s32 func_80053EF0(s32);
extern void func_800A56E0(s32);
extern void *func_8003DF74(void *, void *, void *, s16);
extern s32 func_80069EF8(void);
extern void func_800248A8(void *, s32, s32, s32, s32, s32, s32);
extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern void func_80024DD4(void *, void *, void *, s32, s32, s32);
extern void func_80024F60(void *, void *, void *, s32, s32, s32);

/* Advance the effect sequence, spawning sprites and particles along its sampled path. */
void func_8197192C(void *effect_arg, void *owner_arg, void *context_arg)
{
    u8 *position;
    u8 *effect_data_m;
    static void *const state_labels[] __attribute__((used)) = {
        &&case_0, &&case_1, &&case_2, &&case_3, &&case_4, &&cleanup, &&done
    };
    u32 state;
    void *effect = effect_arg;
    void *owner = owner_arg;
    register void *context ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u32 light_color;
    u32 light_color_2;
    u32 dark_color;

    (void)state_labels;
    ASM_KEEP4_NV(effect, owner, context, context);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    ((S_8197192C_0 *)effect)->unk_38 = ((S_8197192C_0 *)effect)->unk_38 + 1;
    state = ((S_8197192C_0 *)effect)->unk_0A.s;
    context = context_arg;
    if (state >= 5) {
        return;
    }
    goto *D_80024058[state];

case_0:
{
    void *player = D_800814A8_case0[0];
    void *player_2;
    u16 coord_z;
    u16 heading;
    ((S_8197192C_1 *)player)->unk_F4 = 0;
    ((S_8197192C_1 *)player)->unk_96 = 20;
    ((S_8197192C_2 *)D_80082E86)->unk_00 = 6;
    state = D_80083780;
    ((S_8197192C_0 *)effect)->unk_0A.u = ((S_8197192C_0 *)effect)->unk_0A.u + 1;
    ((S_8197192C_0 *)effect)->unk_7C.s = ((S_8197192C_3 *)state)->unk_02;
    ((S_8197192C_0 *)effect)->unk_7E.s = ((S_8197192C_3 *)state)->unk_06;
    coord_z = ((S_8197192C_3 *)state)->unk_0A;
    ((S_8197192C_4 *)D_80025FF4)->unk_00 = 1;
    ((S_8197192C_0 *)effect)->unk_80.s = coord_z;
    ASM_KEEP(coord_z);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    if ((((S_8197192C_14 *)(((S_8197192C_0 *)effect)->unk_04))->unk_00 & 0x80) == 0) {
        goto done;
    }
    player_2 = D_800814A8[0];
    ((S_8197192C_0 *)effect)->unk_2C.s = 33;
    ((S_8197192C_1 *)player_2)->unk_A6 = ((S_8197192C_1 *)player_2)->unk_A6 - 1;
    ((S_8197192C_1 *)player_2)->unk_A8 = ((S_8197192C_0 *)effect)->unk_08;
    player = D_800814A8[0];
    heading = ((S_8197192C_1 *)player)->unk_2A;
    ((S_8197192C_0 *)effect)->unk_0A.u = ((S_8197192C_0 *)effect)->unk_0A.u + 1;
    ((S_8197192C_0 *)effect)->unk_38 = 0;
    ((S_8197192C_0 *)effect)->unk_34 = (heading >> 9) & 7;
    return;
}

case_1:
{
    ((S_8197192C_0 *)effect)->unk_2C.s = ((S_8197192C_0 *)effect)->unk_2C.s - 1;
    if ((s16)((S_8197192C_0 *)effect)->unk_2C.s <= 0) {
        ((S_8197192C_0 *)effect)->unk_2C.s = 16;
        ((S_8197192C_0 *)effect)->unk_0A.u = ((S_8197192C_0 *)effect)->unk_0A.u + 1;
        return;
    }
    if ((s16)((S_8197192C_0 *)effect)->unk_2C.s == 26) {
        if (func_80053EF0(4) != 2) {
            func_800A56E0(0x300);
        } else {
            func_800A56E0(0x4300);
        }
    }

}

case_2:
{
    s32 step;
    if ((u16)(((S_8197192C_0 *)effect)->unk_2C.s - 5) < 19) {
        void *map_base = (void *)D_80082E80;
        if (func_8003DF74(
            ((S_8197192C_5 *)map_base)->unk_08, map_base,
            (u8 *)effect + 0x2E, 0) != 0) {
            step = 0;
            do {
                func_800248A8((u8 *)((Rec_D_800814A8 *)&D_800814A8)->unk_00.as_pv - 0x20, 0,
                              0xE04040, (func_80069EF8() & 0x3F) | 0x40,
                              ((S_8197192C_0 *)effect)->unk_2E.s,
                              ((S_8197192C_0 *)effect)->unk_30.s,
                              ((S_8197192C_0 *)effect)->unk_32.s);
                step++;
            } while (step < 2);
        }
    }

    if (((S_8197192C_0 *)effect)->unk_2C.u == 24) {
        void *map_base = (void *)D_80082E80;
        if (func_8003DF74(((S_8197192C_5 *)map_base)->unk_08, map_base,
                          (u8 *)effect + 0x2E, 0) != 0) {
            void *effect_obj;
            u8 *sprite;
            u8 *world_pos;

            effect_obj = func_8003FC64(0x212);
            if (effect_obj != 0) {
                effect_data_m = (u8 *)effect_obj + 0x20;
                ((S_8197192C_7 *)effect_data_m)->unk_38 = 20;
                ((S_8197192C_7 *)effect_data_m)->unk_3A = 20;
                ((S_8197192C_1 *)effect_obj)->unk_10.at00.v = (void *)&D_80024D10;
                func_8004491C(effect_obj, D_80045340);
                sprite = ((S_8197192C_1 *)effect_obj)->unk_0C;
                world_pos = D_80083780;
                ((S_8197192C_8 *)sprite)->unk_10 = 0x60;
                ((S_8197192C_8 *)sprite)->unk_14 = ((S_8197192C_8 *)sprite)->unk_14 | 0x0C;
                position = ((S_8197192C_1 *)effect_obj)->unk_08;
                ((S_8197192C_9 *)position)->unk_02 = ((S_8197192C_0 *)effect)->unk_2E.u +
                                      ((S_8197192C_3 *)world_pos)->unk_02;
                ((S_8197192C_9 *)position)->unk_06 = ((S_8197192C_0 *)effect)->unk_30.u +
                                      ((S_8197192C_3 *)world_pos)->unk_06;
                ((S_8197192C_9 *)position)->unk_0A = ((S_8197192C_0 *)effect)->unk_32.u +
                                       ((S_8197192C_3 *)world_pos)->unk_0A;
                sprite = ((S_8197192C_1 *)effect_obj)->unk_0C;
                ((S_8197192C_8 *)sprite)->unk_1E = 0x1000;
                ((S_8197192C_8 *)sprite)->unk_1C = 0x1000;
                ((S_8197192C_8 *)sprite)->unk_0E = 0x20;
                ((S_8197192C_8 *)sprite)->unk_0D = 0x20;
                ((S_8197192C_8 *)sprite)->unk_0C = 0x20;
                *(Data12 *)((u8 *)effect_obj + 0xA2) = D_80025FD0;
                ((S_8197192C_8 *)sprite)->unk_08 = (u8 *)effect_obj + 0xA2;
            }
        }
    }
}

case_3:
{
    s32 segment;
    s32 point_index;
    s32 step;
    u8 *world_pos;
    u8 *outer_point;
    if (((S_8197192C_0 *)effect)->unk_2C.u >= 10) {
        goto done;
    }
    if (((S_8197192C_0 *)effect)->unk_2C.u >= 6) {
        goto done;
    }
    if (((S_8197192C_0 *)effect)->unk_2C.u == 3) {
        goto done;
    }
    segment = (((S_8197192C_0 *)effect)->unk_2C.u == 4);
    if (((S_8197192C_0 *)effect)->unk_2C.u == 2) {
        segment = 2;
    }
    if (((S_8197192C_0 *)effect)->unk_2C.u == 1) {
        segment = 3;
    }
    {
        void *map_base = (void *)D_80082E80;
        if (func_8003DF74(((S_8197192C_5 *)map_base)->unk_08, map_base,
                          (u8 *)effect + 0x2E, 0) == 0) {
            goto after_coords;
        }
        if (((S_8197192C_0 *)effect)->unk_2C.u == 1) {
            ((S_8197192C_0 *)effect)->unk_32.s = -12;
        }
    }
    point_index = segment << 1;
    {
        outer_point = (u8 *)effect + ((point_index + segment) << 2);
        point_index++;
        {
            u32 shifted_x;
            s32 origin_x;
            s32 half_x;
            shifted_x = ((S_8197192C_0 *)effect)->unk_2E.u;
            origin_x = ((S_8197192C_0 *)effect)->unk_7C.u;
            shifted_x <<= 16;
            half_x = (s32)shifted_x >> 16;
            half_x += shifted_x >> 31;
            world_pos = D_80083780;
            half_x >>= 1;
            ((S_8197192C_9 *)outer_point)->unk_4C = (s16)(half_x +
                (((S_8197192C_10 *)world_pos)->unk_02 - origin_x) / 2);
        }
        ((S_8197192C_9 *)outer_point)->unk_4E = (s16)(((s16)((S_8197192C_0 *)effect)->unk_30.u) / 2 +
            (((S_8197192C_10 *)world_pos)->unk_06 - ((S_8197192C_0 *)effect)->unk_7E.u) / 2);
        ((S_8197192C_9 *)outer_point)->unk_50 = (s16)(((s16)((S_8197192C_0 *)effect)->unk_32.u) / 2 +
            (((S_8197192C_10 *)world_pos)->unk_0A - ((S_8197192C_0 *)effect)->unk_80.u) / 2);
    }

    {
        u8 *inner_point = (u8 *)effect + (((point_index << 1) + point_index) << 1);
        ((S_8197192C_11 *)inner_point)->unk_4C = (s16)(((s16)((S_8197192C_0 *)effect)->unk_2E.u) / 4 +
            (((S_8197192C_10 *)world_pos)->unk_02 - ((S_8197192C_0 *)effect)->unk_7C.u) / 2);
        ((S_8197192C_11 *)inner_point)->unk_4E = (s16)(((s16)((S_8197192C_0 *)effect)->unk_30.u) / 4 +
            (((S_8197192C_10 *)world_pos)->unk_06 - ((S_8197192C_0 *)effect)->unk_7E.u) / 2);
        ((S_8197192C_11 *)inner_point)->unk_50 = (s16)(((s16)((S_8197192C_0 *)effect)->unk_32.u) / 4 +
            (((S_8197192C_10 *)world_pos)->unk_0A - ((S_8197192C_0 *)effect)->unk_80.u) / 2);
    }

after_coords:
    if (((S_8197192C_0 *)effect)->unk_2C.u == 4) {
        void *effect_obj = func_8003FC64(0x212);
        u8 *effect_data = (u8 *)effect_obj + 0x20;
        if (effect_obj != 0) {

            u8 *sprite;
            void *init_data;
            light_color_2 = 0x00E0E0E0;
            dark_color = 0x00804020;
            init_data = (void *)&D_80024544;
            ((S_8197192C_7 *)effect_data)->unk_1C = light_color_2;
            ((S_8197192C_7 *)effect_data)->unk_24 = dark_color;
            ((S_8197192C_7 *)effect_data)->unk_28 = dark_color;
            ((S_8197192C_7 *)effect_data)->unk_20 = light_color_2;
            ((S_8197192C_7 *)effect_data)->unk_38 = 20;
            ((S_8197192C_7 *)effect_data)->unk_3A = 20;
            ((S_8197192C_7 *)effect_data)->unk_0C = ((S_8197192C_7 *)effect_data)->unk_1C;
            ((S_8197192C_7 *)effect_data)->unk_10 = ((S_8197192C_7 *)effect_data)->unk_20;
            ((S_8197192C_7 *)effect_data)->unk_14 = ((S_8197192C_7 *)effect_data)->unk_24;
            ((S_8197192C_7 *)effect_data)->unk_18 = ((S_8197192C_7 *)effect_data)->unk_28;
            ((S_8197192C_1 *)effect_obj)->unk_10.at00.v = (void *)&D_80024B98;
            func_8004491C(effect_obj, init_data);
            sprite = ((S_8197192C_1 *)effect_obj)->unk_0C;
            ((S_8197192C_8 *)sprite)->unk_10 = 0x20;
            ((S_8197192C_8 *)sprite)->unk_14 = ((S_8197192C_8 *)sprite)->unk_14 | 0x0C;
            ((S_8197192C_7 *)effect_data)->unk_4C = ((S_8197192C_0 *)effect)->unk_58.s;
            ((S_8197192C_7 *)effect_data)->unk_4E = ((S_8197192C_0 *)effect)->unk_5A.s;
            ((S_8197192C_7 *)effect_data)->unk_50 = ((S_8197192C_0 *)effect)->unk_5C.s;
            ((S_8197192C_7 *)effect_data)->unk_52 = ((S_8197192C_0 *)effect)->unk_4C.s;
            ((S_8197192C_7 *)effect_data)->unk_54 = ((S_8197192C_0 *)effect)->unk_4E.s;
            ((S_8197192C_7 *)effect_data)->unk_56 = ((S_8197192C_0 *)effect)->unk_50.s;
            ((S_8197192C_7 *)effect_data)->unk_58 = ((S_8197192C_0 *)effect)->unk_5E;
            ((S_8197192C_7 *)effect_data)->unk_5A = ((S_8197192C_0 *)effect)->unk_60;
            ((S_8197192C_7 *)effect_data)->unk_5C = ((S_8197192C_0 *)effect)->unk_62;
            ((S_8197192C_7 *)effect_data)->unk_5E = ((S_8197192C_0 *)effect)->unk_52;
            ((S_8197192C_7 *)effect_data)->unk_60 = ((S_8197192C_0 *)effect)->unk_54;
            ((S_8197192C_7 *)effect_data)->unk_62 = ((S_8197192C_0 *)effect)->unk_56;
            position = ((S_8197192C_1 *)effect_obj)->unk_08;
            ((S_8197192C_9 *)position)->unk_02 = ((S_8197192C_0 *)effect)->unk_7C.s;
            ((S_8197192C_9 *)position)->unk_06 = ((S_8197192C_0 *)effect)->unk_7E.s;
            ((S_8197192C_9 *)position)->unk_0A = ((S_8197192C_0 *)effect)->unk_80.s;
            sprite = ((S_8197192C_1 *)effect_obj)->unk_0C;
            ((S_8197192C_8 *)sprite)->unk_1E = 0x1000;
            ((S_8197192C_8 *)sprite)->unk_1C = 0x1000;
            ((S_8197192C_8 *)sprite)->unk_0E = 0x80;
            ((S_8197192C_8 *)sprite)->unk_0D = 0x80;
            ((S_8197192C_8 *)sprite)->unk_0C = 0x80;
            *(Data12 *)((u8 *)effect_obj + 0xA2) = D_80025FDC;
            ((S_8197192C_8 *)sprite)->unk_08 = (u8 *)effect_obj + 0xA2;
        }
    }
    if (((S_8197192C_0 *)effect)->unk_2C.u == 2) {
        void *effect_obj = func_8003FC64(0x212);
        u8 *effect_data = (u8 *)effect_obj + 0x20;
        if (effect_obj != 0) {

            u8 *sprite;
            void *init_data;
            light_color = 0x00E0E0E0;
            dark_color = 0x00804020;
            init_data = (void *)&D_80024544;
            ((S_8197192C_7 *)effect_data)->unk_1C = light_color;
            ((S_8197192C_7 *)effect_data)->unk_24 = dark_color;
            ((S_8197192C_7 *)effect_data)->unk_28 = dark_color;
            ((S_8197192C_7 *)effect_data)->unk_20 = light_color;
            ((S_8197192C_7 *)effect_data)->unk_38 = 20;
            ((S_8197192C_7 *)effect_data)->unk_3A = 20;
            ((S_8197192C_7 *)effect_data)->unk_0C = ((S_8197192C_7 *)effect_data)->unk_1C;
            ((S_8197192C_7 *)effect_data)->unk_10 = ((S_8197192C_7 *)effect_data)->unk_20;
            ((S_8197192C_7 *)effect_data)->unk_14 = ((S_8197192C_7 *)effect_data)->unk_24;
            ((S_8197192C_7 *)effect_data)->unk_18 = ((S_8197192C_7 *)effect_data)->unk_28;
            ((S_8197192C_1 *)effect_obj)->unk_10.at00.v = (void *)&D_80024B98;
            func_8004491C(effect_obj, init_data);
            sprite = ((S_8197192C_1 *)effect_obj)->unk_0C;
            ((S_8197192C_8 *)sprite)->unk_10 = 0x20;
            ((S_8197192C_8 *)sprite)->unk_14 = ((S_8197192C_8 *)sprite)->unk_14 | 0x0C;
            ((S_8197192C_7 *)effect_data)->unk_4C = ((S_8197192C_0 *)effect)->unk_64.s;
            ((S_8197192C_7 *)effect_data)->unk_4E = ((S_8197192C_0 *)effect)->unk_66.s;
            ((S_8197192C_7 *)effect_data)->unk_50 = ((S_8197192C_0 *)effect)->unk_68.s;
            ((S_8197192C_7 *)effect_data)->unk_52 = ((S_8197192C_0 *)effect)->unk_58.s;
            ((S_8197192C_7 *)effect_data)->unk_54 = ((S_8197192C_0 *)effect)->unk_5A.s;
            ((S_8197192C_7 *)effect_data)->unk_56 = ((S_8197192C_0 *)effect)->unk_5C.s;
            ((S_8197192C_7 *)effect_data)->unk_58 = ((S_8197192C_0 *)effect)->unk_6A;
            ((S_8197192C_7 *)effect_data)->unk_5A = ((S_8197192C_0 *)effect)->unk_6C;
            ((S_8197192C_7 *)effect_data)->unk_5C = ((S_8197192C_0 *)effect)->unk_6E;
            ((S_8197192C_7 *)effect_data)->unk_5E = ((S_8197192C_0 *)effect)->unk_5E;
            ((S_8197192C_7 *)effect_data)->unk_60 = ((S_8197192C_0 *)effect)->unk_60;
            ((S_8197192C_7 *)effect_data)->unk_62 = ((S_8197192C_0 *)effect)->unk_62;
            position = ((S_8197192C_1 *)effect_obj)->unk_08;
            ((S_8197192C_9 *)position)->unk_02 = ((S_8197192C_0 *)effect)->unk_7C.s;
            ((S_8197192C_9 *)position)->unk_06 = ((S_8197192C_0 *)effect)->unk_7E.s;
            ((S_8197192C_9 *)position)->unk_0A = ((S_8197192C_0 *)effect)->unk_80.s;
            sprite = ((S_8197192C_1 *)effect_obj)->unk_0C;
            ((S_8197192C_8 *)sprite)->unk_1E = 0x1000;
            ((S_8197192C_8 *)sprite)->unk_1C = 0x1000;
            ((S_8197192C_8 *)sprite)->unk_0E = 0x80;
            ((S_8197192C_8 *)sprite)->unk_0D = 0x80;
            ((S_8197192C_8 *)sprite)->unk_0C = 0x80;
            *(Data12 *)((u8 *)effect_obj + 0xA2) = D_80025FDC;
            ((S_8197192C_8 *)sprite)->unk_08 = (u8 *)effect_obj + 0xA2;
        }
    }
    if (((S_8197192C_0 *)effect)->unk_2C.u == 1) {
        register void *effect_obj ASM_REG("$17") = func_8003FC64(0x212);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        if (effect_obj != 0) {
            u8 *sprite;
            void *init_data;
            effect_data_m = (u8 *)effect_obj + 0x20;
            light_color = 0x00E0E0E0;
            dark_color = 0x00804020;
            init_data = (void *)&D_80024544;
            ((S_8197192C_7 *)effect_data_m)->unk_1C = light_color;
            ((S_8197192C_7 *)effect_data_m)->unk_24 = dark_color;
            ((S_8197192C_7 *)effect_data_m)->unk_28 = dark_color;
            ((S_8197192C_7 *)effect_data_m)->unk_20 = light_color;
            ((S_8197192C_7 *)effect_data_m)->unk_38 = 20;
            ((S_8197192C_7 *)effect_data_m)->unk_3A = 20;
            ((S_8197192C_7 *)effect_data_m)->unk_0C = ((S_8197192C_7 *)effect_data_m)->unk_1C;
            ((S_8197192C_7 *)effect_data_m)->unk_10 = ((S_8197192C_7 *)effect_data_m)->unk_20;
            ((S_8197192C_7 *)effect_data_m)->unk_14 = ((S_8197192C_7 *)effect_data_m)->unk_24;
            ((S_8197192C_7 *)effect_data_m)->unk_18 = ((S_8197192C_7 *)effect_data_m)->unk_28;
            ((S_8197192C_1 *)effect_obj)->unk_10.at00.v = (void *)&D_80024B98;
            func_8004491C(effect_obj, init_data);
            sprite = ((S_8197192C_1 *)effect_obj)->unk_0C;
            ((S_8197192C_8 *)sprite)->unk_10 = 0x20;
            ((S_8197192C_8 *)sprite)->unk_14 = ((S_8197192C_8 *)sprite)->unk_14 | 0x0C;
            ((S_8197192C_7 *)effect_data_m)->unk_4C = ((S_8197192C_0 *)effect)->unk_70.s;
            ((S_8197192C_7 *)effect_data_m)->unk_4E = ((S_8197192C_0 *)effect)->unk_72.s;
            ((S_8197192C_7 *)effect_data_m)->unk_50 = ((S_8197192C_0 *)effect)->unk_74.s;
            ((S_8197192C_7 *)effect_data_m)->unk_52 = ((S_8197192C_0 *)effect)->unk_64.s;
            ((S_8197192C_7 *)effect_data_m)->unk_54 = ((S_8197192C_0 *)effect)->unk_66.s;
            ((S_8197192C_7 *)effect_data_m)->unk_56 = ((S_8197192C_0 *)effect)->unk_68.s;
            ((S_8197192C_7 *)effect_data_m)->unk_58 = ((S_8197192C_0 *)effect)->unk_76;
            ((S_8197192C_7 *)effect_data_m)->unk_5A = ((S_8197192C_0 *)effect)->unk_78;
            ((S_8197192C_7 *)effect_data_m)->unk_5C = ((S_8197192C_0 *)effect)->unk_7A;
            ((S_8197192C_7 *)effect_data_m)->unk_5E = ((S_8197192C_0 *)effect)->unk_6A;
            ((S_8197192C_7 *)effect_data_m)->unk_60 = ((S_8197192C_0 *)effect)->unk_6C;
            ((S_8197192C_7 *)effect_data_m)->unk_62 = ((S_8197192C_0 *)effect)->unk_6E;
            position = ((S_8197192C_1 *)effect_obj)->unk_08;
            ((S_8197192C_9 *)position)->unk_02 = ((S_8197192C_0 *)effect)->unk_7C.s;
            ((S_8197192C_9 *)position)->unk_06 = ((S_8197192C_0 *)effect)->unk_7E.s;
            ((S_8197192C_9 *)position)->unk_0A = ((S_8197192C_0 *)effect)->unk_80.s;
            sprite = ((S_8197192C_1 *)effect_obj)->unk_0C;
            ((S_8197192C_8 *)sprite)->unk_1E = 0x1000;
            ((S_8197192C_8 *)sprite)->unk_1C = 0x1000;
            ((S_8197192C_8 *)sprite)->unk_0E = 0x80;
            ((S_8197192C_8 *)sprite)->unk_0D = 0x80;
            ((S_8197192C_8 *)sprite)->unk_0C = 0x80;
            *(Data12 *)((u8 *)effect_obj + 0xA2) = D_80025FDC;
            ((S_8197192C_8 *)sprite)->unk_08 = (u8 *)effect_obj + 0xA2;
            ASM_KEEP(effect_obj);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        }
    }

    if (((S_8197192C_0 *)effect)->unk_2C.u == 4) {
        step = 0;
        do {
            s32 spawn_x;
            s32 spawn_y;
            s32 spawn_z;
            spawn_x = (s16)((((S_8197192C_0 *)effect)->unk_58.s +
                      (((S_8197192C_0 *)effect)->unk_4C.u - ((S_8197192C_0 *)effect)->unk_58.u) * step / 6) << 1);
            spawn_y = (s16)((((S_8197192C_0 *)effect)->unk_5A.s +
                      (((S_8197192C_0 *)effect)->unk_4E.u - ((S_8197192C_0 *)effect)->unk_5A.u) * step / 6) << 1);
            spawn_z = (s16)((((S_8197192C_0 *)effect)->unk_5C.s +
                      (((S_8197192C_0 *)effect)->unk_50.u - ((S_8197192C_0 *)effect)->unk_5C.u) * step / 6) << 1);
            func_80024DD4(effect, owner, context,
                spawn_x, spawn_y, spawn_z);
            step++;
        } while (step < 6);
    }
    if (((S_8197192C_0 *)effect)->unk_2C.u == 2) {
        step = 0;
        do {
            s32 spawn_x;
            s32 spawn_y;
            s32 spawn_z;
            spawn_x = (s16)((((S_8197192C_0 *)effect)->unk_64.s +
                      (((S_8197192C_0 *)effect)->unk_58.u - ((S_8197192C_0 *)effect)->unk_64.u) * step / 12) << 1);
            spawn_y = (s16)((((S_8197192C_0 *)effect)->unk_66.s +
                      (((S_8197192C_0 *)effect)->unk_5A.u - ((S_8197192C_0 *)effect)->unk_66.u) * step / 12) << 1);
            spawn_z = (s16)((((S_8197192C_0 *)effect)->unk_68.s +
                      (((S_8197192C_0 *)effect)->unk_5C.u - ((S_8197192C_0 *)effect)->unk_68.u) * step / 12) << 1);
            func_80024DD4(effect, owner, context,
                spawn_x, spawn_y, spawn_z);
            step++;
        } while (step < 12);
    }
    if (((S_8197192C_0 *)effect)->unk_2C.u != 1) {
        goto done;
    }
    step = 0;
    do {
        s32 spawn_x;
        s32 spawn_y;
        s32 spawn_z;
        spawn_x = (s16)((((S_8197192C_0 *)effect)->unk_70.s +
                  (((S_8197192C_0 *)effect)->unk_64.u - ((S_8197192C_0 *)effect)->unk_70.u) * step / 2) << 1);
        spawn_y = (s16)((((S_8197192C_0 *)effect)->unk_72.s +
                  (((S_8197192C_0 *)effect)->unk_66.u - ((S_8197192C_0 *)effect)->unk_72.u) * step / 2) << 1);
        spawn_z = (s16)((((S_8197192C_0 *)effect)->unk_74.s +
                  (((S_8197192C_0 *)effect)->unk_68.u - ((S_8197192C_0 *)effect)->unk_74.u) * step / 2) << 1);
        func_80024DD4(effect, owner, context,
            spawn_x, spawn_y, spawn_z);
        step++;
    } while (step < 2);
    goto done;

}

case_4:
{
    s32 angle;
    void *source_obj;
    u8 *angle_base;
    u8 *angle_table;
    u8 angle_count;
    u8 *status_page;
    if (((S_8197192C_0 *)effect)->unk_2C.u != 16) {
        status_page = (u8 *)0x80080000;
        goto case_4_global_use;
    }
    source_obj = ((S_8197192C_15 *)(((Rec_D_800814A8 *)&D_800814A8)->unk_00.as_pv))->unk_60;
    if (source_obj != 0) {
        angle_table = D_800DDC40;
        angle_count = angle_table[((S_8197192C_1 *)source_obj)->unk_10.at03.v];
        owner = ((S_8197192C_1_pre *)source_obj)[-1].unk_00;
        angle = 0;
        if (angle_count == 0) {
            goto case_4_global;
        }
        angle_base = angle_table;
        loop_3: {
            func_80024F60(effect, owner, context, 0, 0, (s16)angle);
            angle -= 15;
        } if (-*(u8 *)((u32)((S_8197192C_1 *)source_obj)->unk_10.at03.v + (u32)angle_base) < angle) goto loop_3;
    }
case_4_global:
    status_page = (u8 *)0x80080000;
case_4_global_use:
    {
        u16 next_state = 4;
        if ((((S_8197192C_12 *)status_page)->unk_2E94 & 0x8000) != 0) {
            goto case_4_set_state;
        }
        ((S_8197192C_0 *)effect)->unk_2C.s = ((S_8197192C_0 *)effect)->unk_2C.s - 1;
        if ((s16)((S_8197192C_0 *)effect)->unk_2C.s >= 0) {
            goto done;
        }
case_4_set_state:
        ((S_8197192C_0 *)effect)->unk_0A.u = next_state;
        return;
    }
    goto done;
}

cleanup:
{
    void *cleanup_obj;
    u16 cleanup_count;
    if (D_80025FF4[0] == 0) {
        cleanup_obj = D_80083460;
        cleanup_count = ((S_8197192C_13 *)cleanup_obj)->unk_0A;
        ((S_8197192C_13 *)cleanup_obj)->unk_0C = 0;
        D_80082E86[0] = 0;
        ((S_8197192C_13 *)cleanup_obj)->unk_0A = cleanup_count - 1;
        ((S_8197192C_0_pre *)effect)[-1].unk_00 = ((S_8197192C_0_pre *)effect)[-1].unk_00 | 0x8000;
        D_800814A0[0] = D_800814A0[0] | 0x8000;
        return;
    }
    D_80025FF4[0] = 0;

}

done:
    return;
}
