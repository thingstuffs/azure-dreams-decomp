#include "modules/dungeon_native_abi.h"

typedef struct S_func_8187A800_0 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_func_8187A800_0;

extern s32 get_unused_text_buffer(void);
extern s32 expand_text_control_codes(u8 *src, u8 *dst);
extern void func_80099290(s8 *byte_ptr);
extern s32 append_entity_display_text(void *record, u8 *out);
extern void adjust_source_value_and_finalize(void *, void *);
extern s32 try_trigger_target_record_effect(void *, s32);
extern s32 set_or_clear_actor_status_slot(void *, s32, s8);
extern void display_text_with_fullwidth_adjustment(s8 *text);
extern s32 get_random_scaled_value(s16 input_value);

void update_projectile_trail_and_hit_effect(void *, void *, void *);
void (*const dungeon_189a800_entry)(void *, void *, void *) = update_projectile_trail_and_hit_effect;
const u8 D_80024004[48] = {0x82,0x73,0x82,0x88,0x82,0x85,0x82,0x92,0x82,0x85,0x81,0x40,0x82,0x97,0x82,0x81,0x82,0x93,0x81,0x40,0x82,0x8e,0x82,0x8f,0x81,0x40,0x82,0x85,0x82,0x86,0x82,0x86,0x82,0x85,0x82,0x83,0x82,0x94,0x81,0x40,0x82,0x8f,0x82,0x8e,0x81,0x40,0x0,0x0};
const u8 D_80024034[4] = {0x81,0x44,0x0,0x0};
extern s32 D_800E1CB0;

void func_800240B8(S_func_8187A800_0 *target, s32 effect_arg, void *unused);

/* Attempts to apply an effect and reports the outcome for flagged targets. */
void func_800240B8(S_func_8187A800_0 *target, s32 effect_arg, void *unused)
{
    s32 message;
    s32 message_start;

    if (try_trigger_target_record_effect(target, 4) == 0) {
        if ((set_or_clear_actor_status_slot(target, 0x14,
                           (s8)(get_random_scaled_value(effect_arg & 0xFF) + 2)) << 16) != 0) {
            if (target->unk_14 & 0x4000) {
                adjust_source_value_and_finalize(target, &D_800E1CB0);
                return;
            }
        } else if (target->unk_14 & 0x4000) {
            message = get_unused_text_buffer();
            message_start = message;
            message = expand_text_control_codes(&D_80024004, message);
            message = append_entity_display_text(target, message);
            message = expand_text_control_codes(&D_80024034, message);
            func_80099290(message);
            display_text_with_fullwidth_adjustment(message_start);
        }
    }
}
