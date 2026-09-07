#include "common.h"
#include "m2c_compat.h"

typedef struct S_7FFEA9D4_4 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_7FFEA9D4_4;   /* temp_v0_2 in func_7FFEA9D4 */

typedef struct S_7FFEA9D4_5 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_7FFEA9D4_5;   /* ((S_7FFEA9D4_4 *)temp_v0_2)->unk_0C in func_7FFEA9D4 */


typedef struct S_7FFEA9D4_0_pre {
    u16 unk_00;
} S_7FFEA9D4_0_pre;   /* the 0x2 bytes before arg0 in func_7FFEA9D4, addressed as arg0[-1] */

typedef struct S_7FFEA9D4_0 {
    void * unk_00;
    u8 pad_04[0x12];
    u16 unk_16;
    u8 pad_18[0x6];
    u16 unk_1E;
} S_7FFEA9D4_0;   /* arg0 in func_7FFEA9D4 */

typedef struct S_7FFEA9D4_1 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    M2C_UNK * unk_10;
    u8 pad_14[0x2A];
    s16 unk_3E;
    s16 unk_40;
    u8 pad_42[0x1E];
    u16 unk_60;
} S_7FFEA9D4_1;   /* temp_v0_2 in func_7FFEA9D4 */

typedef struct S_7FFEA9D4_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_7FFEA9D4_2;   /* temp_s0 in func_7FFEA9D4 */

typedef struct S_7FFEA9D4_3 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_7FFEA9D4_3;   /* temp_s1 in func_7FFEA9D4 */


void *func_7003CF18();                       /* extern */
s32 func_700750E0();                                /* extern */
M2C_UNK func_7010CD00(); /* extern */
extern s32 D_80086AD8;
extern u8 D_800E0F20[0x100];
extern u16 D_80094422;
extern M2C_UNK D_8010C994;

/* Spawns randomized particles while the emitter is young and marks it inactive when its timer expires. */
void func_7FFEA9D4(void *emitter, M2C_UNK init_param_1, M2C_UNK init_param_2) {
    M2C_UNK saved_init_param_1 = init_param_1;
    register M2C_UNK saved_init_param_2 ASM_REG("$23") = init_param_2;   /* MATCH pin: keeps a statement from moving across a call/branch */
    register s32 z_offset ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
    s32 spawn_count;
    s32 rand_value;
    s32 pos_z;
    s32 pos_x;
    s32 pos_y;
    u16 age_or_flags;
    u16 ticks_left;
    u16 active_count;
    u16 *active_counter;
    S_7FFEA9D4_2 *position;
    S_7FFEA9D4_3 *emitter_data;
    S_7FFEA9D4_1 *particle;

    age_or_flags = ((S_7FFEA9D4_0 *)emitter)->unk_16 + 1;
    ((S_7FFEA9D4_0 *)emitter)->unk_16 = age_or_flags;
    if ((s16) age_or_flags < 0x28) {
        spawn_count = 0;
        do {
            particle = func_7003CF18(0x212);
            spawn_count += 1;
            if (particle != NULL) {
                func_7010CD00(particle, emitter, saved_init_param_1, saved_init_param_2);
                position = particle->unk_08;
                particle->unk_3E = 8;
                particle->unk_40 = 8;
                particle->unk_10 = &D_8010C994;
                rand_value = func_700750E0();
                pos_x = position->unk_02;
                pos_x -= 0x1F;
                pos_x += rand_value & 0x3F;
                position->unk_02 = (u16) pos_x;
                rand_value = func_700750E0();
                pos_y = position->unk_06;
                pos_y -= 0x1F;
                pos_y += rand_value & 0x3F;
                position->unk_06 = (u16) pos_y;
                emitter_data = ((S_7FFEA9D4_0 *)emitter)->unk_00;
                particle->unk_60 = (u16) position->unk_0A;
                rand_value = func_700750E0();
                z_offset = D_800E0F20[emitter_data->unk_13];
                pos_z = position->unk_0A;
                z_offset += 0x20;
                z_offset -= rand_value & 0xF;
                pos_z -= z_offset;
                position->unk_0A = (u16) pos_z;
                ((S_7FFEA9D4_5 *)(((S_7FFEA9D4_4 *)particle)->unk_0C))->unk_0C = 0;
            }
        } while (spawn_count < 2);
    }
    ticks_left = ((S_7FFEA9D4_0 *)emitter)->unk_1E - 1;
    ((S_7FFEA9D4_0 *)emitter)->unk_1E = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        age_or_flags = ((S_7FFEA9D4_0_pre *)emitter)[-1].unk_00;
        active_counter = &D_80094422;
        age_or_flags |= 0x8000;
        ((S_7FFEA9D4_0_pre *)emitter)[-1].unk_00 = age_or_flags;
        active_count = *active_counter - 1;
        D_80086AD8 |= 0x8000;
        *active_counter = active_count;
    }
}
