#include "shared/object_node.h"
#include "common.h"
#include "shared/dungeon_sprite_data.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_status.h"

struct Dst;
struct Elem;

extern s32 func_8003DB94(struct Dst *state, struct Elem *entries, s32 index);  /* extern */
extern s32 func_8004491C();
s32 rand();                                /* extern */
extern s32 play_sound_if_enabled();
extern void damp_effect_motion_and_fade(void *effect, s32 *motion, void *primitive);

typedef struct S_800C5BBC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
} S_800C5BBC_0;

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
} S_800C5BBC_1;

typedef struct S_800C5BBC_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800C5BBC_2;

typedef struct S_800C5BBC_3 {
    u8 pad_00[0xC];
    s16 unk_0C;
    u8 pad_0E[0x2];
    s16 unk_10;
} S_800C5BBC_3;

typedef struct S_800C5BBC_4 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800C5BBC_4;

/* Spawn a burst of randomized particles and return the first particle. */
void *spawn_randomized_particle_burst(s16 x, s16 y, s16 z, s32 sprite_data, u16 sprite_id, s16 play_sound) {
    s32 alloc_flags;
    s32 particle_index;
    s32 remaining;
    S_800C5BBC_1 *position;
    S_800C5BBC_2 *sprite;
    void *particle;
    S_800C5BBC_3 *particle_state;
    void *first_particle;

    first_particle = 0;
    if (play_sound != 0) {
        play_sound_if_enabled(0x608);
    }
    particle_index = 0;
    remaining = (rand() & 0xF) | 0x10;
    if (remaining >= 0) {
        do {
            alloc_flags = 0x12;
            if (particle_index != 0) {
                alloc_flags = 0x212;
            }
            particle = func_8003FC64(alloc_flags);
            if (particle != 0) {
                ((S_800C5BBC_0 *)particle)->unk_10 = damp_effect_motion_and_fade;
                func_8004491C(particle, func_80045340);
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
                    g_dungeon_status.unk_0A = (u16) (((u16)g_dungeon_status.unk_0A) + 1);
                }
            }
            remaining -= 1;
            particle_index += 1;
        } while (remaining >= 0);
    }
    return first_particle;
}
