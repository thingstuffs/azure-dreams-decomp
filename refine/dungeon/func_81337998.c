#include "common.h"
#include "m2c_compat.h"

typedef struct S_8016E998_0 {
    u8 pad_00[0x1];
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[0x15];
    s16 unk_18;
    s16 unk_1A;
    u8 pad_1C[0x58];
    s16 unk_74;
    s16 unk_76;
    s16 unk_78;
    s16 unk_7A;
    s16 unk_7C;
    s16 unk_7E;
    s16 unk_80;
    s16 unk_82;
    s16 unk_84;
    s16 unk_86;
    s16 unk_88;
    s16 unk_8A;
} S_8016E998_0;   /* temp_s0 in func_8016E998 */

typedef struct S_8016E998_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s8 unk_20;
} S_8016E998_1;   /* temp_v0 in func_8016E998 */

typedef struct S_8016E998_2 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} S_8016E998_2;   /* temp_a1 in func_8016E998 */

typedef struct S_8016E998_3 {
    s32 unk_00;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    s32 unk_08;
} S_8016E998_3;   /* temp_v1 in func_8016E998 */

typedef struct S_8016E998_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_8016E998_4;   /* arg0 in func_8016E998 */

typedef struct S_8016E998_5 {
    u8 pad_00[0xC];
    s8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    s16 unk_1C;
    s16 unk_1E;
} S_8016E998_5;   /* temp_a1_3 in func_8016E998 */


void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                        /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_8016E4E8;
extern void *D_80175D78;

/* Creates sixteen radial effect segments around the supplied position. */
void func_8016E998(S_8016E998_4 *origin) {
    s32 origin_z;
    s32 start_angle;
    s32 end_x;
    s32 start_x;
    s32 end_z;
    s32 start_z;
    s32 unit_scale;
    s32 initial_count;
    register s32 intensity ASM_REG("$4");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    void *init_effect;
    register s32 color_level ASM_REG("$3");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    u16 flags_copy;
    s32 end_angle;
    s32 segment_index;
    u16 render_flags;
    M2C_UNK *effect_handler;
    void **effect_slot;
    register S_8016E998_2 *render_config ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
    S_8016E998_5 *appearance;
    S_8016E998_0 *effect_data;
    void *effect;
    S_8016E998_3 *position;

    segment_index = 0;
    effect_handler = &D_8016E4E8;
    effect_slot = &D_80175D78;
    end_angle = 0x100;
    do {
        effect = func_8003FC64(0x12);
        if (effect != NULL) {
            init_effect = effect;
            ASM_KEEP(init_effect);   /* MATCH pin: retail schedule: same instructions, different order without it */
            effect_data = effect + 0x20;
            initial_count = 0x32;
            ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
            effect_data->unk_18 = (s16) initial_count;
            effect_data->unk_1A = (s16) initial_count;
            ((S_8016E998_1 *)effect)->unk_10 = effect_handler;
            func_8004491C(init_effect, &D_80045340);
            render_config = ((S_8016E998_1 *)effect)->unk_0C;
            render_flags = render_config->unk_14 | 0xC;
            render_config->unk_14 = render_flags;
            ASM_KEEP(render_flags);   /* MATCH pin: retail schedule: same instructions, different order without it */
            flags_copy = render_flags;
            ASM_KEEP(flags_copy);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            render_config->unk_10 = 0x20;
            render_config->unk_14 = (u16) (flags_copy | 0x80);
            position = ((S_8016E998_1 *)effect)->unk_08;
            position->unk_00 = (s32) origin->unk_00;
            position->unk_04.at00.v = (s32) origin->unk_04;
            origin_z = origin->unk_08;
            position->unk_04.at02.v = (u16) (position->unk_04.at02.v - 0x440);
            position->unk_08 = origin_z;
            effect_data->unk_7E = -0x40;
            effect_data->unk_78 = -0x40;
            effect_data->unk_8A = 0;
            effect_data->unk_84 = 0;
            start_angle = segment_index << 8;
            end_x = (s32) (func_80064584(end_angle, origin_z) << 5) >> 0xC;
            effect_data->unk_80 = (s16) end_x;
            effect_data->unk_74 = (s16) end_x;
            start_x = (s32) (func_80064584(start_angle) << 5) >> 0xC;
            effect_data->unk_86 = (s16) start_x;
            effect_data->unk_7A = (s16) start_x;
            end_z = (s32) (func_800644B8(end_angle) << 5) >> 0xC;
            effect_data->unk_82 = (s16) end_z;
            effect_data->unk_76 = (s16) end_z;
            start_z = (s32) (func_800644B8(start_angle) << 5) >> 0xC;
            color_level = 0x40;
            effect_data->unk_88 = (s16) start_z;
            effect_data->unk_7C = (s16) start_z;
            appearance = ((S_8016E998_1 *)effect)->unk_0C;
            ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
            unit_scale = 0x1000;
            ASM_KEEP(unit_scale);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
            appearance->unk_0C = (s8) color_level;
            ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
            intensity = color_level;
            appearance->unk_1E = (s16) unit_scale;
            appearance->unk_1C = (s16) unit_scale;
            appearance->unk_0D = (u8) color_level;
            appearance->unk_0E = (u8) color_level;
            ((S_8016E998_1 *)effect)->unk_20 = (s8) intensity;
            effect_data->unk_01 = (u8) appearance->unk_0D;
            effect_data->unk_02 = (u8) appearance->unk_0E;
            *effect_slot = effect;
        }
        effect_slot = (void **)((s8 *)((void **)((s8 *)effect_slot + 4)));
        segment_index += 1;
        end_angle += 0x100;
    } while (segment_index < 0x10);
}

/* MECHANISM: Held global bases and caller-saved constant pins restore the 0x38
   s0-s7 prologue; split RMW names and schedule seams preserve retail copies,
   delay-slot fills, and tail store order. */
