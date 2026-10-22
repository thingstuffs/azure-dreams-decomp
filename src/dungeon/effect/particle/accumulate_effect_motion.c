#include "common.h"
#include "shared/object_flags.h"

typedef struct S_81814A80_0 {
    u16 unk_00;
} S_81814A80_0;   /* state in accumulate_effect_motion; pointer addresses record offset 0x2 */



typedef struct {
    unsigned char pad00[2];
    u16 unk02;
    unsigned char pad04[20];
    s16 unk18;
    s16 unk1a;
    u16 unk1c;
    unsigned char pad1e[0x3a];
    s32 unk58;
    s32 unk5c;
    s32 unk60;
    s32 unk64;
    s32 unk68;
    s32 unk6c;
} State;

typedef struct {
    unsigned char pad00[0x14];
    u16 unk14;
} Flags;

extern s16 D_80025338;
extern void advance_sprite_animation_and_textures(void *flags);

/* Accumulate motion, process the update mode, and mark expired or flagged state. */
void accumulate_effect_motion(State *state, s32 *sum, Flags *flags) {
    s32 update_count;
    s32 more_updates;
    u16 next_tick;

    state->unk02 = state->unk02 - 1;
    state->unk58 = state->unk58 + state->unk64;
    state->unk5c = state->unk5c + state->unk68;
    state->unk60 = state->unk60 + state->unk6c;
    sum[0] = sum[0] + state->unk58;
    sum[1] = sum[1] + state->unk5c;
    D_80025338 = 1;
    sum[2] = sum[2] + state->unk60;

    switch (state->unk18) {
    case 0:
        advance_sprite_animation_and_textures(flags);
        break;
    case 1:
        if (state->unk1a > 0) {
            update_count = 0;
            do {
                advance_sprite_animation_and_textures(flags);
                update_count = update_count + 1;
                more_updates = update_count < state->unk1a;
            } while (more_updates);
        }
        break;
    case 2:
        next_tick = state->unk1c + 1;
        state->unk1c = next_tick;
        if ((s16) next_tick >= state->unk1a) {
            advance_sprite_animation_and_textures(flags);
            state->unk1c = 0;
        }
        break;
    default:
        break;
    }

    if ((s16) state->unk02 <= 0) {
        ((S_81814A80_0 *)((u8 *)state - 0x2))->unk_00 = ((S_81814A80_0 *)((u8 *)state - 0x2))->unk_00 | 0x8000;
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    }
    if (flags->unk14 & 0x8000) {
        ((S_81814A80_0 *)((u8 *)state - 0x2))->unk_00 = ((S_81814A80_0 *)((u8 *)state - 0x2))->unk_00 | 0x8000;
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    }
}
