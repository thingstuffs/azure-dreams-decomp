#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003DB94();  /* extern */
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 rand();                                /* extern */
M2C_UNK func_800A56E0();                     /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083460;
extern M2C_UNK D_800C5A64;
extern M2C_UNK D_800DEA68;

typedef struct S_800C5BBC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_800C5BBC_0;   /* temp_v0 in func_800C5BBC */

typedef struct S_800C5BBC_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800C5BBC_1;   /* temp_s0 in func_800C5BBC */

typedef struct S_800C5BBC_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800C5BBC_2;   /* temp_s0_2 in func_800C5BBC */

typedef struct S_800C5BBC_3 {
    u8 pad_00[0xC];
    s16 unk_0C;
    u8 pad_0E[0x2];
    s16 unk_10;
} S_800C5BBC_3;   /* temp_v1 in func_800C5BBC */

typedef struct S_800C5BBC_4 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800C5BBC_4;   /* var_s5 in func_800C5BBC */

/* Spawn a burst of randomized particles and return the first particle. */
void *func_800C5BBC(s16 x, s16 y, s16 z, s32 sprite_data, u16 sprite_id, s16 play_sound) {
    M2C_UNK alloc_flags;
    s32 particle_index;
    s32 remaining;
    S_800C5BBC_1 *position;
    S_800C5BBC_2 *sprite;
    void *particle;
    S_800C5BBC_3 *particle_state;
    void *first_particle;
    S_800C5BBC_4 *effect_state;

    first_particle = NULL;
    if (play_sound != 0) {
        func_800A56E0(0x608);
    }
    particle_index = 0;
    remaining = (rand() & 0xF) | 0x10;
    if (remaining >= 0) {
        effect_state = &D_80083460;
        do {
            alloc_flags = 0x12;
            if (particle_index != 0) {
                alloc_flags = 0x212;
            }
            particle = func_8003FC64(alloc_flags);
            if (particle != NULL) {
                ((S_800C5BBC_0 *)particle)->unk_10 = &D_800C5A64;
                func_8004491C(particle, &D_80045340);
                position = ((S_800C5BBC_0 *)particle)->unk_08;
                position->unk_02 = (u16) x;
                position->unk_06 = y;
                position->unk_0A = z;
                position->unk_0C = (s32) (position->unk_0C + (((rand() & 0x1F) - 0x10) << 0xE));
                position->unk_10 = (s32) (position->unk_10 + (((rand() & 0x1F) - 0x10) << 0xE));
                position->unk_14 = (s32) ((0 - ((rand() & 0xF) + 0x18)) << 0xD);
                sprite = ((S_800C5BBC_0 *)particle)->unk_0C;
                func_8003DB94(sprite, &D_800DEA68, 0);
                sprite->unk_0C = sprite_data;
                sprite->unk_1E = 0x1000;
                sprite->unk_1C = 0x1000;
                sprite->unk_10 = sprite_id;
                sprite->unk_12 = 3;
                sprite->unk_14 = (u16) (sprite->unk_14 | 0xC);
                particle_state = particle + 0x20;
                particle_state->unk_10 = (s16) ((rand() & 0xF) | 0x10);
                particle_state->unk_0C = particle_index;
                if (particle_index == 0) {
                    first_particle = particle;
                    effect_state->unk_0A = (u16) (effect_state->unk_0A + 1);
                }
            }
            remaining -= 1;
            particle_index += 1;
        } while (remaining >= 0);
    }
    return first_particle;
}
