#include "common.h"
#include "shared/game_work.h"
struct Dst;
struct Elem;

void select_record_entry_and_value(struct Dst *state, struct Elem *entries, short index);        /* extern */
s32 play_sound_if_enabled();                     /* extern */
extern u8 actor_alternate_frames[];

typedef struct S_func_80097A68_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0x6];
    u16 unk_A2;
} S_func_80097A68_0;

typedef struct S_func_80097A68_1 {
    u8 pad_00[0x2C];
    u8 *unk_2C;
} S_func_80097A68_1;

typedef struct S_func_80097A68_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_func_80097A68_2;

typedef struct S_func_80097A68_3 {
    s32 unk_00;
} S_func_80097A68_3;

/* Initializes actor state and selects an animation from the adjusted facing angle. */
void initialize_facing_animation(S_func_80097A68_0 *actor, s32 unused, S_func_80097A68_1 *anim,
    S_func_80097A68_2 *facing_source) {
    actor->unk_9A = 0x38;
    actor->unk_9B = 0;
    actor->unk_8C = 0;
    *(u8 **)((u8 *)anim + 0x2C) = actor_alternate_frames;
    select_record_entry_and_value(anim, ((S_func_80097A68_3 *) (actor_alternate_frames + (((s32) (g_game_work.view.camera_rotation.parts.viewAngle + facing_source->unk_2A
        + 0x100) >> 7) & 0x1C)))->unk_00, 0);
    play_sound_if_enabled(0x50A);
    actor->unk_96 = 2;
    actor->unk_A2 = (u16) (actor->unk_A2 & 0xFFEF);
}
