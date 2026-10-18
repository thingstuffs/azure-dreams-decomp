#include "modules/dungeon_ovl_19cc800.h"
#include "common.h"

/* Animation player state (see advance_animation_index_within_bounds): the first word is the current entry in the owner's table. */


/* Owner of the animation table. */


/* Sets the player's current entry address using a 22-byte stride. */
void set_animation_entry_address(AnimPlayer *player, s16 entry_index) {
    player->entry = ((AnimOwner *)player->owner)->table + (entry_index * 0x16);
}

