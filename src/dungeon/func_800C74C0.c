#include "modules/trap_effects_candidate.h"
#include "common.h"

typedef struct {
    u8 pad[3];
    u8 flags;
} Entry4;




extern u8 D_800E5908;
extern s32 D_800DCF78;

extern s32 play_sound_if_enabled();
extern void display_fixed_item_action_message();
s32 generate_random_value(void);
void draw_textured_ellipse(void *, void *, s32, s32);
extern void create_five_part_target_effect(u16 x, u16 y, s16 z);

/* Take the item in map slot `slot`: with no object, drop the slot's 0x80 flag and bump the pickup count; otherwise roll the object's 0x3 chance and give the fallback cue at or above 0x40, then cue 0x817 for the slot's item. */
s32 take_map_item_slot(void *object, s16 slot)
{
    s32 stack_args[2];
    s16 value;
    s32 random;
    s32 index;
    s32 scaled_index;
    s32 field;
    s8 count;
    s32 flags;
    u8 *map_base;
    u8 *item_base;
    u8 *entry;
    u8 *item;
    u8 * item_2;
    u8 *countp;
    s32 tail_index;
    u8 *tail_base;

    if (object == 0) {
        map_base = (u8 *)D_800E3648;
        index = slot;
        scaled_index = index * 4;
        entry = scaled_index + map_base;
        flags = entry[3];
        if (flags & 0x80) {
            value = flags & 0x7F;
            item_base = (u8 *)D_800E39C8;
            entry[3] = value;
            item = item_base + index * 24;
            countp = &D_800E5908;
            field = *(u16 *)(item + 0x14);
            count = *countp;
            field &= 0xF7FF;
            count++;
            *(u16 *)(item + 0x14) = field;
            *countp = count;
        } else {
            return 1;
        }
    } else {
        if (D_800E3D40 != 0) {
            value = 0;
        } else {
            random = generate_random_value() & 0xFFFF;
            if (*((u8 *)object + 3) != 0) {
                value = random % *((u8 *)object + 3);
            } else {
                value = 0;
            }
        }

        if (value >= 0x40) {
            display_fixed_item_action_message();
            value = 1;
            return value;
        }

        D_800DCF78 = 0x00202080;
        stack_args[0] = 0x01000340;
        stack_args[1] = 0x00200020;
        draw_textured_ellipse((u8 *)&D_800DCF78 - 0x10, stack_args, 1, 0);
        D_800E5908 = 0;
    }

    tail_base = (u8 *)D_800E39C8;
    tail_index = slot;
    item_2 = tail_base + tail_index * 24;
    create_five_part_target_effect(item_2[6], item_2[7], *(s16 *)(item_2 + 0x12));
    play_sound_if_enabled(0x817);
    return 1;
}

/* MECHANISM: Recover true-space joins locally and model the call workspace as an
   escaping 8-byte stack record.  Hold object/slot in s0/s1 and use guarded a0/v1
   RNG/remainder roles so the explicit result merge survives before the threshold. */
