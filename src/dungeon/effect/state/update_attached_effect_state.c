#include "shared/actor_status_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"

typedef struct Entity800B4194
{
    u8 pad00[0x1C];
    u32 flags1C;
    u8 pad20[8];
    u8 value28;
    u8 pad29[0x1F];
    u8 state48;
    u8 state49;
    u8 state4A;
    u8 state4B;
    u8 pad4C[0x18];
    s16 value64;
}
Entity800B4194;
typedef struct Context800B4194
{
    u8 pad00[0x4C];
    u8 *event4C;
    u8 pad50[0x14];
    u16 value64;
}
Context800B4194;
extern s32 dungeon_mode_state[];
extern s16 current_dungeon_floor[];
extern u8 D_800892C4[];
extern u8 D_800892C8[];
extern u8 D_800E0BC7[];
extern u8 D_800E0BDC[];
extern u8 D_800E0BF3[];
extern u8 D_800E0C09[];
extern u8 D_800E0C1D[];
extern volatile u8 *dungeon_actor_ring_anchor[];
extern s16 get_entity_effect_value(Entity800B4194 *, s32);
extern u8 *get_unused_text_buffer(void);
extern u8 *expand_text_control_codes(u8 *, u8 *);
extern u8 *clear_byte_and_advance(u8 *);
extern u8 *append_entity_display_text(Entity800B4194 *, u8 *);
extern s16 set_or_clear_actor_status_slot(Entity800B4194 *, s32, s32);
extern void play_sound_if_enabled(s32);
extern void display_text_with_fullwidth_adjustment(u8 *);
extern s32 generate_random_value(void);
extern s32 random_dungeon_range_16(s32, s32);
extern s16 resolve_alternate_spell_id(s16);
extern void create_actor_value_popup(s32 flags, u8 *source_data, s16 value, u16 callback_mode);
extern s32 roll_chance_and_apply_effect_four(Entity800B4194 *, s32, s32);
extern s32 roll_threshold_effect_variant_b(Entity800B4194 *, s32, s32);
/* Applies secondary spell and event-record effects, updating actor status, values, and displayed messages. */
s32 update_attached_effect_state(s16 tile_index, Entity800B4194 *entityp, Context800B4194 *contextp)
{
    s16 blocked;
    s32 total;
    s32 flag;
    u8 *saved;
    u8 *text;
    s16 code;
    s32 delta;
    s16 amount;
    s16 range;
    u8 *event;
    s16 value;
    code = resolve_alternate_spell_id(tile_index);
    total = entityp->value28 + entityp->value64;
    flag = total < 1;
    blocked = flag;
    if (code != 0) {
        switch (code) {
        case 0x10:
        case 0x13:
        {
            if (!blocked) {
                value = generate_random_value();
                range = (dungeon_actor_ring_anchor[0][0xA9] >> 2) + 0x10;
                if (roll_threshold_effect_variant_b(entityp, dungeon_actor_ring_anchor[0][0xA9] + 0x80, range + (value & 3)) != 0) {
                    saved = get_unused_text_buffer();
                    text = expand_text_control_codes(D_800E0BC7, saved);
                    text = append_entity_display_text(entityp, text);
                    text = expand_text_control_codes(D_800892C4, text);
                    text = clear_byte_and_advance(text);
                    display_text_with_fullwidth_adjustment(saved);
                }
            }
            break;
        }
        case 0x12:
        case 0x15:
        {
            if (!(blocked || (entityp->flags1C & ACTOR_PARALYZED))) {
                value = generate_random_value();
                range = (dungeon_actor_ring_anchor[0][0xA9] >> 2) + 2;
                if (roll_chance_and_apply_effect_four(entityp, dungeon_actor_ring_anchor[0][0xA9] + 0x80, range + (value & 3)) != 0) {
                    saved = get_unused_text_buffer();
                    text = expand_text_control_codes(D_800E0BDC, saved);
                    text = append_entity_display_text(entityp, text);
                    text = expand_text_control_codes(D_800892C8, text);
                    text = clear_byte_and_advance(text);
                    display_text_with_fullwidth_adjustment(saved);
                }
            }
            break;
        }
        }
    }

    event = contextp->event4C;

    if (event == 0) {
        return 0;
    }
    if (event[1] != 0x10) {
        return 0;
    }
    value = event[0];
    switch (value) {
    case 3:
    {
        delta = -(((s16) (*((u16 *) (((u8 *) entityp) + 0x64)))) >> 3);

        amount = delta;
        if (amount == 0) {
            return 0;
        }
        contextp->value64 += delta;
        create_actor_value_popup(0x10, contextp, amount, 1);
        return 0;
    }
    case 4:
    {
        if (blocked || (entityp->flags1C & ACTOR_PARALYZED)) {
            return 0;
        }
        if (roll_chance_and_apply_effect_four(entityp, 8, 8) == 0) {
            return 0;
        }
        play_sound_if_enabled(0x700);
        saved = get_unused_text_buffer();
        text = expand_text_control_codes(D_800E0BF3, saved);
        text = append_entity_display_text(entityp, text);
        text = expand_text_control_codes(D_800892C4, text);
        text = clear_byte_and_advance(text);
        display_text_with_fullwidth_adjustment(saved);
        return 0;
    }
    case 5:
    {
        s32 low; /* MATCH: merge random-range bounds in the retail argument registers. */
        s32 high; /* MATCH: preserve the range-bound delay slots. */
        if (!blocked) {
            return 0;
        }
        saved = &entityp->state48;
        if (saved[1] != 0) {
            return 0;
        }
        if ((generate_random_value() & 3) != 0) {
            return 0;
        }
        saved[1] = 0xE;
        if ((dungeon_mode_state[0] != 2) && (current_dungeon_floor[0] < 0xC)) {
            low = 0x10;
            high = 0x18;
            saved[0] = 1;
            saved[2] = random_dungeon_range_16(low, high);
            saved[3] = 0;
        }
        else if ((dungeon_mode_state[0] != 2) && (current_dungeon_floor[0] < 0x16)) {
            low = 0x50;
            high = 0x78;
            saved[0] = 2;
            saved[2] = random_dungeon_range_16(low, high);
            saved[3] = 0;
        }
        else {
            entityp->state48 = 3;
            saved[2] = random_dungeon_range_16(0x10, 0x18);
            saved[3] = 1;
        }
        return 0;
    }
    case 9:
    {
        if (blocked) {
            return 0;
        }
        if (get_entity_effect_value(entityp, STATUS_MAGIC_BIND) != 0) {
            return 0;
        }
        if ((generate_random_value() & 7) != 0) {
            return 0;
        }
        if (set_or_clear_actor_status_slot(entityp, STATUS_MAGIC_BIND, 0x10) < 0) {
            return 0;
        }
        play_sound_if_enabled(0x700);
        saved = get_unused_text_buffer();
        text = expand_text_control_codes(D_800E0C09, saved);
        text = append_entity_display_text(entityp, text);
        text = expand_text_control_codes(D_800E0C1D, text);
        text = clear_byte_and_advance(text);
        display_text_with_fullwidth_adjustment(saved);
        return 0;
    }
    }
    return 0;
}
