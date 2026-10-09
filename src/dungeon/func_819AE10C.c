#include "common.h"

/* Animation player state (see func_80025840): the first word is the current entry in the owner's table. */
typedef struct AnimPlayer {
    s32 entry;
    u8 pad_04[4];
    void *owner;
} AnimPlayer;

/* Owner of the animation table. */
typedef struct AnimOwner {
    u8 pad_00[0xC];
    s32 table;
} AnimOwner;

/* Sets the player's current entry address using a 22-byte stride. */
void func_8002590C(AnimPlayer *player, s16 entry_index) {
    player->entry = ((AnimOwner *)player->owner)->table + (entry_index * 0x16);
}
