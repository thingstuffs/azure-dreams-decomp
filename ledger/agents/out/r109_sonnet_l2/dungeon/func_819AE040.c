#include "common.h"

/* Animation player state; entry is the current entry in the owner's table (0x16-byte AnimEntry stride). */
typedef struct AnimPlayer {
    s32 entry;
    u8 index;           /* current entry number, signed when compared */
    u8 pad_05[0x3];
    void *owner;
    u8 pad_0C[0x8];
    u16 flags;          /* 0x4000 set while the index is clamped to a bound */
} AnimPlayer;

/* Owner of the animation table. */
typedef struct AnimOwner {
    u8 pad_00[0xC];
    s32 table;
} AnimOwner;

/* Resolve the current entry, apply an index step, and enforce the index bounds. */
void func_80025840(AnimPlayer *player, s16 *index_step, s32 min_index, s32 max_index) {
    s16 step;
    u32 clamp_flags;
    u8 index;
    s32 initial_index = (s8)player->index;
    AnimOwner *owner = player->owner;

    player->entry =
        owner->table + (initial_index * 22);
    step = *index_step;
    if (step > 0) {
        player->index = player->index + 1;
    } else if (step < 0) {
        player->index =
            player->index - 1;
    }
    index = player->index;
    if ((s8)index < (s16)min_index) {
        clamp_flags = player->flags | 0x4000;
        player->index = min_index;
        player->flags = clamp_flags;
        return;
    }
    if ((s8)index > (s16)max_index) {
        clamp_flags = player->flags | 0x4000;
        player->index = max_index;
        player->flags = clamp_flags;
        return;
    }
    player->flags &= 0xBFFF;
}
