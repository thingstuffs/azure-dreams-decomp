#include "shared/actor_status_ids.h"
#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/item_ids.h"
#include "shared/dungeon_item_entries.h"
#include "shared/entity.h"


extern void *get_unused_text_buffer(void);
extern s32 get_entity_effect_value(ActorRecord *entry, s32 effect_id);
extern u8 *expand_text_control_codes(u8 *src, u8 *dst);
extern u8 *append_entity_display_text(void *record, u8 *out);
extern void clear_byte_and_advance(s8 *byte_ptr);
extern void play_sound_if_enabled(s32 query_value);
extern void display_text_with_fullwidth_adjustment(s8 *text);

extern u8 D_80089084[];
extern u8 D_800E0CAE[];
extern u8 D_800E0CDC[];
extern u8 D_800E0CF3[];
extern u8 D_800E0D1B[];
extern u8 D_800E0D36[];

/* Displays the mode-specific message and updates the state meter within its limit. */
s32 feed_actor_restore_mp(ActorRecord *state, s32 mode, DungeonItemEntry *item) {
    void *message;
    s32 meter;
    void *base_message;
    s32 old_meter;

    base_message = get_unused_text_buffer();
    message = base_message;
    if ((get_entity_effect_value(state, STATUS_ANOREXIA) << 16) != 0) {
        clear_byte_and_advance(expand_text_control_codes(D_80089084,
                                    append_entity_display_text(state,
                                                  expand_text_control_codes(D_800E0CAE, base_message))));
        display_text_with_fullwidth_adjustment(base_message);
        return 0;
    }

    if ((mode == 3) && (item != 0)) {
        if ((item->kind == ITEM_KIND_FRUIT) && (item->unk_00 == ITEM_PITA_FRUIT)) {
            mode = 2;
        } else if ((item->kind == 0xC) && (item->unk_00 == ITEM_MEAT)) {
            mode = 2;
        }
    }

    meter = *(u16 *)&state->mp_fraction;
    old_meter = meter;
    switch (mode) {
    case 0:
        message = expand_text_control_codes(D_80089084,
                                append_entity_display_text(state,
                                              expand_text_control_codes(D_800E0CDC, message)));
        break;
    case 1:
        message = append_entity_display_text(state, message);
        message = expand_text_control_codes(D_800E0CF3, message);
        meter += 0x300;
        break;
    case 2:
        message = expand_text_control_codes(D_800E0D1B, append_entity_display_text(state, message));
        if ((item != 0) && (item->kind == 0xC) && (item->unk_00 == ITEM_MEAT)) {
            meter += 0xA00;
        } else {
            meter += 0x3200;
        }
        break;
    case 3:
        message = expand_text_control_codes(D_800E0D36, append_entity_display_text(state, message));
        meter += 0x6400;
        break;
    }

    if (item != 0) {
        clear_byte_and_advance(message);
        display_text_with_fullwidth_adjustment(base_message);
    } else if (mode == 0) {
        clear_byte_and_advance(message);
        display_text_with_fullwidth_adjustment(base_message);
    }
    if (old_meter != meter) {
        play_sound_if_enabled(0x51E);
    }
    /*
     * BUG: exactly 0x10000 is not saturated and becomes zero in the u16 MP store. The overflow check should
     * include equality so feeding fills MP instead of emptying it.
     */
    if (meter > 0x10000) {
        meter = 0xFFFF;
    }
    *(u16 *)&state->mp_fraction = (u16)meter;
    if (((u8 *)state)[0x25] != 0) {
        state->flags1C &= ~ACTOR_MP_EMPTY;
    }
    if (state->max_mp < state->mp) {
        state->mp = state->max_mp;
        ((u8 *)state)[0x24] = 0xFF;
    }
    return mode;
}
