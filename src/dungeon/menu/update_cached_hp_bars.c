#include "shared/entity.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "dungeon/menu.h"


typedef struct S_800DC0BC_1 {
    u8 pad_00[0x10];
    s32 unk_10;
    s32 unk_14;
} S_800DC0BC_1;   /* arg0 in update_cached_hp_bars */

/* Updates two target entries when their cached values differ from the current values. */
void update_cached_hp_bars(S_800DC0BC_1 *cached_values, u8 **target_base) {
    ActorRecord **page;
    ActorRecord *owner;
    u8 first_value;
    u8 second_value;

    page = &primary_actor_record;
    owner = *page;
    first_value = owner->hp;
    if (first_value != cached_values->unk_10) {
        set_hud_bar_fill(target_base[0], owner->hp);
        cached_values->unk_10 = (*page)->hp;
    }
    owner = *page;
    second_value = owner->max_hp;
    if (second_value != cached_values->unk_14) {
        set_hud_bar_fill(target_base[0] + 0xC, owner->max_hp);
        cached_values->unk_14 = (*page)->max_hp;
    }
}
