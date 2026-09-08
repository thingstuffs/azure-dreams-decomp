#include "common.h"
#include "m2c_compat.h"

typedef struct S_81814EDC_0_pre {
    u16 unk_00;
} S_81814EDC_0_pre;   /* the 0x2 bytes before arg0 in func_81814EDC, addressed as arg0[-1] */

typedef struct S_81814EDC_0 {
    s16 unk_00;
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x4];
    s16 unk_08;
    u16 unk_0A;
    u8 pad_0C[0x9];
    u8 unk_15;
    u16 unk_16;
    u8 pad_18[0x14];
    s32 unk_2C;
    void * unk_30;
    u8 pad_34[0x24];
    s32 unk_58;
    s32 unk_5C;
    s32 unk_60;
} S_81814EDC_0;   /* arg0 in func_81814EDC */

typedef struct S_81814EDC_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xE];
    s16 unk_22;
} S_81814EDC_1;   /* temp_v0 in func_81814EDC */

typedef struct S_81814EDC_2 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    union { u8 s; s8 u; } unk_0C;   /* accessed as both */
    union { u8 s; s8 u; } unk_0D;   /* accessed as both */
    union { u8 s; s8 u; } unk_0E;   /* accessed as both */
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_81814EDC_2;   /* temp_s0_2 in func_81814EDC */

typedef struct S_81814EDC_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_81814EDC_3;   /* source in func_81814EDC */

typedef struct S_81814EDC_4 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
} S_81814EDC_4;   /* temp_s1_2 in func_81814EDC */

typedef struct S_81814EDC_5 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0x4C];
    s32 unk_58;
    s32 unk_5C;
    s32 unk_60;
} S_81814EDC_5;   /* temp_s1_4 in func_81814EDC */

typedef struct S_81814EDC_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_81814EDC_6;   /* temp_s3 in func_81814EDC */

typedef struct S_81814EDC_7_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_81814EDC_7_pre;   /* the 0x18 bytes before source_owner in func_81814EDC, addressed as source_owner[-1] */

typedef struct S_81814EDC_8_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_81814EDC_8_pre;   /* the 0x14 bytes before temp_a0 in func_81814EDC, addressed as temp_a0[-1] */

typedef struct S_81814EDC_8 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_81814EDC_8;   /* temp_a0 in func_81814EDC */

typedef struct S_81814EDC_9 {
    u8 pad_00[0xC];
    union { s8 s; u8 u; } unk_0C;   /* accessed as both */
    union { s8 s; u8 u; } unk_0D;   /* accessed as both */
    union { s8 s; u8 u; } unk_0E;   /* accessed as both */
} S_81814EDC_9;   /* temp_a1 in func_81814EDC */

typedef struct S_81814EDC_10 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} S_81814EDC_10;   /* arg1_value in func_81814EDC */

typedef struct S_81814EDC_11 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_81814EDC_11;   /* temp_a0_3 in func_81814EDC */

typedef struct S_81814EDC_12_pre {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x10];
} S_81814EDC_12_pre;   /* the 0x18 bytes before ((S_81814EDC_0 *)arg0)->unk_30 in func_81814EDC, addressed as ((S_81814EDC_0 *)arg0)->unk_30[-1] */


extern u8 D_80045340[];
extern u8 D_800DE938[];
extern u8 D_800DE870[9];
extern s32 D_800814A0[3];
M2C_UNK func_800245BC();
void func_80024B08() __attribute__((noreturn));
void func_80024BB8() __attribute__((noreturn));
void *func_8003FC64();
M2C_UNK func_8004491C();
s32 func_80069EF8();
M2C_UNK func_8009CE1C();
s32 func_800A4778();
extern M2C_UNK D_80024280;

/* Spawns particles, moves the effect, and restores its owner after the fade. */
void func_81814EDC(void *effect, void *position) {
    s16 state;
    s16 effect_type;
    s32 spark_speed;
    s32 burst_speed;
    s32 spark_kind;
    s32 burst_kind;
    s32 effect_index;
    s32 neutral_color;
    s32 double_scale;
    s32 unit_scale;
    u16 ticks_left;
    u16 fade_ticks;
    void *owner;
    S_81814EDC_11 *owner_flags;
    S_81814EDC_9 *owner_sprite;
    S_81814EDC_2 *sprite;
    S_81814EDC_4 *spawn_position;
    S_81814EDC_5 *debris;
    S_81814EDC_6 *owner_position;
    void *particle;

    if (((S_81814EDC_0 *)effect)->unk_00 == 0) {
        if (!(((S_81814EDC_0 *)effect)->unk_0A & 1)) {
            spark_kind = func_80069EF8() & 7;
            spark_speed = (func_80069EF8() & 0xFF) | 0x80;
            func_800245BC(effect - 0x20, spark_kind, 0xF0, spark_speed, 0, 0, (s32) (s16) (-0x20 - (func_80069EF8() & 0x1F)));
        }
        particle = func_8003FC64(0x212);
        if (particle != NULL) {
            void **position_ref = &position;

            ((S_81814EDC_1 *)particle)->unk_22 = 9;
            ((S_81814EDC_1 *)particle)->unk_10 = &D_80024280;
            func_8004491C(particle, D_80045340);
            sprite = ((S_81814EDC_1 *)particle)->unk_0C;
            sprite->unk_14 = (u16) (sprite->unk_14 | 0xC);
            spawn_position = ((S_81814EDC_1 *)particle)->unk_08;
            {
                s32 random_offset = func_80069EF8() & 0x1F;
                register void *source ASM_REG("$8") = *position_ref;   /* MATCH pin: load-bearing for the whole function shape */
                s32 coordinate = ((S_81814EDC_3 *)source)->unk_02;

                coordinate -= 0x10;
                coordinate += random_offset;
                spawn_position->unk_02 = (s16) coordinate;
            }
            {
                s32 random_offset = func_80069EF8() & 0x1F;
                register void *source ASM_REG("$8") = *position_ref;   /* MATCH pin: load-bearing for the whole function shape */
                s32 coordinate = ((S_81814EDC_3 *)source)->unk_06;

                coordinate -= 0x10;
                coordinate += random_offset;
                spawn_position->unk_06 = (s16) coordinate;
            }
            {
                s32 random_offset = func_80069EF8() & 7;
                register void *source ASM_REG("$8") = *position_ref;   /* MATCH pin: load-bearing for the whole function shape */
                s32 coordinate = ((S_81814EDC_3 *)source)->unk_0A;

                coordinate -= 4;
                coordinate += random_offset;
                spawn_position->unk_0A.s = (s16) coordinate;
            }
            sprite = ((S_81814EDC_1 *)particle)->unk_0C;
            sprite->unk_1C = 0x2000;
            sprite->unk_1E = 0x1000;
            sprite->unk_0E.s = 0x80;
            sprite->unk_0D.s = 0x80;
            sprite->unk_0C.s = 0x80;
            func_8003DB94(sprite, D_800DE938, 0);
            func_800478B8(sprite);
            func_800478B8(sprite);
        }
        ticks_left = ((S_81814EDC_0 *)effect)->unk_02.s - 1;
        ((S_81814EDC_0 *)effect)->unk_02.s = ticks_left;
        if ((ticks_left << 0x10) <= 0) {
            effect_index = 0;
            if (((S_81814EDC_0 *)effect)->unk_08 != 0) {
loop_effects:
                effect_index += 1;
                burst_kind = func_80069EF8() & 7;
                burst_speed = (func_80069EF8() & 0xFF) | 0x80;
                func_800245BC(effect - 0x20, burst_kind, 0xF0, burst_speed, 0, 0, (s32) (s16) (-0x20 - (func_80069EF8() & 0x1F)));
                if (effect_index < 4) {
                    goto loop_effects;
                }
                effect_index = 0;
                do {
                    particle = func_8003FC64(0x212);
                    debris = particle + 0x20;
                    if (particle != NULL) {
                        s32 random_offset;
                        s32 coordinate;

                        debris->unk_02 = 0xD;
                        owner_position = ((S_81814EDC_12_pre *)(((S_81814EDC_0 *)effect)->unk_30))[-1].unk_00;
                        ((S_81814EDC_1 *)particle)->unk_10 = &D_80024280;
                        func_8004491C(particle, D_80045340);
                        sprite = ((S_81814EDC_1 *)particle)->unk_0C;
                        sprite->unk_14 = (u16) (sprite->unk_14 | 0xC);
                        debris->unk_58 = (s32) (((func_80069EF8() & 0x7FFF) << 5) + 0xFFF80000);
                        debris->unk_5C = (s32) (((func_80069EF8() & 0x7FFF) << 5) + 0xFFF80000);
                        debris->unk_60 = (s32) (((func_80069EF8() & 0x3FFF) << 5) + 0xFFF80000);
                        debris = ((S_81814EDC_1 *)particle)->unk_08;
                        random_offset = func_80069EF8() & 0xF;
                        coordinate = owner_position->unk_02;
                        coordinate -= 8;
                        coordinate += random_offset;
                        debris->unk_02 = (s16) coordinate;
                        random_offset = func_80069EF8() & 1;
                        coordinate = owner_position->unk_06;
                        coordinate -= 1;
                        coordinate += random_offset;
                        debris->unk_06 = (s16) coordinate;
                        debris->unk_0A = (s16) (owner_position->unk_0A - 0x20);
                        sprite = ((S_81814EDC_1 *)particle)->unk_0C;
                        sprite->unk_1E = 0x1000;
                        sprite->unk_1C = 0x1000;
                        sprite->unk_0E.s = 0x80;
                        sprite->unk_0D.s = 0x80;
                        sprite->unk_0C.s = 0x80;
                        func_8003DB94(sprite, D_800DE870, 0);
                    }
                    effect_index += 1;
                } while (effect_index < 2);
                unit_scale = 0x1000;
                effect_index = 0;
                neutral_color = 0x80;
                double_scale = 0x2000;
spawn_flashes:
                particle = func_8003FC64(0x212);
                if (particle != NULL) {
                    s32 random_offset;
                    s32 coordinate;
                    s32 callback_type = 0xB;
                    register void *task ASM_REG("$4") = particle;   /* MATCH pin: retail schedule: same instructions, different order without it */

                    ASM_KEEP(callback_type);   /* MATCH pin: retail schedule: same instructions, different order without it */
                    {
                        void *source_owner;
                        register u8 *handler ASM_REG("$5") = (u8 *) 0x80040000;   /* MATCH pin: retail delay-slot fill depends on it */

                        ASM_KEEP(handler);   /* MATCH pin: retail delay-slot fill depends on it */
                        ((S_81814EDC_1 *)particle)->unk_22 = callback_type;
                        source_owner = ((S_81814EDC_0 *)effect)->unk_30;
                        handler += 0x5340;
                        owner_position = ((S_81814EDC_7_pre *)source_owner)[-1].unk_00;
                        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
                        {
                            register M2C_UNK *callback ASM_REG("$8") = &D_80024280;   /* MATCH pin: load-bearing for the whole function shape */

                            ((S_81814EDC_1 *)particle)->unk_10 = callback;
                        }
                        func_8004491C(task, handler);
                    }
                    sprite = ((S_81814EDC_1 *)particle)->unk_0C;
                    sprite->unk_14 = (u16) (sprite->unk_14 | 0xC);
                    spawn_position = ((S_81814EDC_1 *)particle)->unk_08;
                    random_offset = func_80069EF8() & 0xF;
                    coordinate = owner_position->unk_02;
                    coordinate -= 8;
                    coordinate += random_offset;
                    spawn_position->unk_02 = (s16) coordinate;
                    random_offset = func_80069EF8() & 1;
                    coordinate = owner_position->unk_06;
                    coordinate -= 1;
                    coordinate += random_offset;
                    spawn_position->unk_06 = (s16) coordinate;
                    spawn_position->unk_0A.u = (u16) owner_position->unk_0A;
                    sprite = ((S_81814EDC_1 *)particle)->unk_0C;
                    sprite->unk_0E.u = neutral_color;
                    sprite->unk_0D.u = neutral_color;
                    sprite->unk_0C.u = neutral_color;
                    sprite->unk_06 = 7;
                    if (effect_index == 0) {
                        sprite->unk_1C = unit_scale;
                        sprite->unk_1E = double_scale;
                        spawn_position->unk_0A.u -= 0x14;
                        func_80024B08();
                        return;
                    }
                    sprite->unk_1C = double_scale;
                    sprite->unk_1E = unit_scale;
                    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
                    func_8003DB94(sprite, D_800DE938, 0);
                    goto next_flash;
                }
next_flash:
                effect_index += 1;
                if (effect_index >= 2) {
                    effect_type = (s16) ((S_81814EDC_0 *)effect)->unk_0A;
                    if (effect_type == 4) {
                        func_8009CE1C(((S_81814EDC_0 *)effect)->unk_30, 0x10, ((S_81814EDC_0 *)effect)->unk_15, 1, (s32) (s16) (((S_81814EDC_0 *)effect)->unk_16 << 9), ((S_81814EDC_0 *)effect)->unk_2C, 2);
                        if ((s16) ((S_81814EDC_0 *)effect)->unk_0A == effect_type) {
                            owner = ((S_81814EDC_0 *)effect)->unk_30;
                            ((S_81814EDC_0 *)effect)->unk_00 = 1;
                            owner_sprite = ((S_81814EDC_8_pre *)owner)[-1].unk_00;
                            ((S_81814EDC_8 *)owner)->unk_1C = (s32) (((S_81814EDC_8 *)owner)->unk_1C | 0x10000000);
                            owner_sprite->unk_0E.s = 0x30;
                            owner_sprite->unk_0D.s = 0x30;
                            owner_sprite->unk_0C.s = 0x30;
                            ((S_81814EDC_0 *)effect)->unk_02.u = 0;
                            func_80024BB8(owner, owner_sprite);
                            return;
                        }
                    }
                    goto finish_effect;
                }
                goto spawn_flashes;
            }
            ((S_81814EDC_0 *)effect)->unk_00 = 1;
            goto move_effect;
        }
move_effect:
        {
            void **position_ref = &position;
            register S_81814EDC_10 *position_vec ASM_REG("$8") = *position_ref;   /* MATCH pin: load-bearing for the whole function shape */

            if ((func_800A4778(position_vec->unk_00.at02.v, position_vec->unk_04.at02.v, (s16) position_vec->unk_08.at02.v, ((S_81814EDC_0 *)effect)->unk_30) << 0x10) == 0) {
                position_vec = *position_ref;

                position_vec->unk_00.at00.v = (s32) (position_vec->unk_00.at00.v + ((S_81814EDC_0 *)effect)->unk_58);
                position_vec->unk_04.at00.v = (s32) (position_vec->unk_04.at00.v + ((S_81814EDC_0 *)effect)->unk_5C);
                position_vec->unk_08.at00.v = (s32) (position_vec->unk_08.at00.v + ((S_81814EDC_0 *)effect)->unk_60);
                goto update_fade;
            }
            goto finish_effect;
        }
    }
update_fade:
    state = ((S_81814EDC_0 *)effect)->unk_00;
    if (state == 1) {
        fade_ticks = ((S_81814EDC_0 *)effect)->unk_02.s + 1;
        ((S_81814EDC_0 *)effect)->unk_02.s = fade_ticks;
        if ((s16) fade_ticks >= 0x15) {
            if (((s16) ((S_81814EDC_0 *)effect)->unk_0A == 4) && (((S_81814EDC_0 *)effect)->unk_08 == state)) {
                owner_flags = ((S_81814EDC_0 *)effect)->unk_30;
                owner_flags->unk_1C = (s32) (owner_flags->unk_1C & 0xEFFFFFFF);
                owner_sprite = ((S_81814EDC_12_pre *)(((S_81814EDC_0 *)effect)->unk_30))[-1].unk_04;
                owner_sprite->unk_0E.u = 0x80;
                owner_sprite->unk_0D.u = 0x80;
                owner_sprite->unk_0C.u = 0x80;
            }
finish_effect:
            ((S_81814EDC_0_pre *)effect)[-1].unk_00 = (u16) (((S_81814EDC_0_pre *)effect)[-1].unk_00 | 0x8000);
            D_800814A0[0] |= 0x8000;
        }
    }
}
