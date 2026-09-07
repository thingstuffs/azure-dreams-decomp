#include "common.h"
#include "m2c_compat.h"

typedef struct S_800D5294_5 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800D5294_5;   /* temp_a0 in func_800D5294 */

typedef struct S_800D5294_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800D5294_6;   /* ((S_800D5294_5 *)temp_a0)->unk_08 in func_800D5294 */


typedef struct S_800D5294_0_pre {
    u16 unk_00;
} S_800D5294_0_pre;   /* the 0x2 bytes before arg0 in func_800D5294, addressed as arg0[-1] */

typedef struct S_800D5294_0 {
    u8 pad_00[0x16];
    u16 unk_16;
    u8 pad_18[0x6];
    u16 unk_1E;
    u8 pad_20[0x4];
    void * unk_24;
    u8 pad_28[0x14];
    u16 unk_3C;
    u16 unk_3E;
    u16 unk_40;
} S_800D5294_0;   /* arg0 in func_800D5294 */

typedef struct S_800D5294_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800D5294_1;   /* arg1 in func_800D5294 */

typedef struct S_800D5294_2 {
    u8 pad_00[0x1E];
    s16 unk_1E;
    s16 unk_20;
} S_800D5294_2;   /* temp_v0_3 in func_800D5294 */

typedef struct S_800D5294_3 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    M2C_UNK * unk_10;
} S_800D5294_3;   /* temp_v0_2 in func_800D5294 */

typedef struct S_800D5294_4 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800D5294_4;   /* temp_s0 in func_800D5294 */


/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_800814A0[3];
extern u16 D_80083460[];
void *func_8003FC64();                       /* extern */
s32 rand();                                /* extern */
M2C_UNK func_800D4BD4(); /* extern */
extern M2C_UNK D_800D50FC[3];

/* Emit randomized particles at the parent-relative position and expire the emitter when its lifetime ends. */
void func_800D5294(void *emitter, S_800D5294_1 *position, M2C_UNK spawn_context) {
    s32 particle_index;
    u16 tick_or_offset;
    u16 life_left;
    s16 coord;
    s16 particle_size;
    S_800D5294_5 *parent;
    S_800D5294_4 *particle_motion;
    u16 *effect_counters;
    M2C_UNK *particle_data;
    void *particle;
    S_800D5294_2 *particle_state;

    parent = ((S_800D5294_0 *)emitter)->unk_24;
    position->unk_02 = (s16) (((S_800D5294_6 *)(parent->unk_08))->unk_02 + ((S_800D5294_0 *)emitter)->unk_3C);
    position->unk_06 = (s16) (((S_800D5294_6 *)(parent->unk_08))->unk_06 + ((S_800D5294_0 *)emitter)->unk_3E);
    position->unk_0A = (s16) (((S_800D5294_6 *)(parent->unk_08))->unk_0A + ((S_800D5294_0 *)emitter)->unk_40);
    tick_or_offset = ((S_800D5294_0 *)emitter)->unk_16 + 1;
    ((S_800D5294_0 *)emitter)->unk_16 = tick_or_offset;
    if ((s16) tick_or_offset < 0x14) {
        particle_index = 0;
        particle_size = 0x20;
        particle_data = D_800D50FC;
        do {
            particle = func_8003FC64(0x212);
            if (particle != NULL) {
                func_800D4BD4(particle, emitter, position, spawn_context);
                particle_state = particle + 0x20;
                particle_state->unk_1E = particle_size;
                particle_state->unk_20 = particle_size;
                ((S_800D5294_3 *)particle)->unk_10 = particle_data;
                particle_motion = ((S_800D5294_3 *)particle)->unk_08;
                tick_or_offset = rand() & 0x3F;
                coord = particle_motion->unk_02;
                coord = coord - 0x1F;
                particle_motion->unk_02 = coord + tick_or_offset;
                tick_or_offset = rand() & 0x3F;
                coord = particle_motion->unk_06;
                coord = coord - 0x1F;
                particle_motion->unk_06 = coord + tick_or_offset;
                tick_or_offset = rand() & 0x1F;
                particle_motion->unk_0A = (s16) (particle_motion->unk_0A - tick_or_offset);
                particle_motion->unk_14 = (s32) ((0 - ((rand() & 0xFFFF) + 0x10000)) * 2);
            }
            particle_index += 1;
        } while (particle_index < 4);
    }
    life_left = ((S_800D5294_0 *)emitter)->unk_1E - 1;
    ((S_800D5294_0 *)emitter)->unk_1E = life_left;
    if ((life_left << 0x10) <= 0) {
        ((S_800D5294_0_pre *)emitter)[-1].unk_00 = (u16) (((S_800D5294_0_pre *)emitter)[-1].unk_00 | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
        effect_counters = D_80083460;
        effect_counters[5] = effect_counters[5] - 1;
    }
}
