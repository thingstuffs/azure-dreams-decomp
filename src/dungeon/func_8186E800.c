#include "modules/dungeon_ovl_188e800.h"
#include "modules/dungeon_native_abi.h"
#include "common.h"



extern s32 get_unused_text_buffer(void);
extern s32 expand_text_control_codes(u8 *src, u8 *dst);
extern void func_80099290(s8 *byte_ptr);
extern s32 append_entity_display_text(void *record, u8 *out);
extern void adjust_source_value_and_finalize(void *, void *);
extern s32 try_trigger_target_record_effect(void *, s32);
extern s32 set_or_clear_actor_status_slot(void *, s32, s8);
extern void display_text_with_fullwidth_adjustment(s8 *text);
extern s32 get_random_scaled_value(s16 input_value);

extern const u8 D_80024004[48];
extern const u8 D_80024034[4];
extern s32 D_800E1C64;



/* Applies effect 0x12 to an eligible entity and handles messages for flagged entities. */
void apply_random_actor_value_adjustment(S_func_8186E800_0 *entity, s32 effect_param, void *context)
{
    s32 message_end;
    s32 message_start;

    if (try_trigger_target_record_effect(entity, 1) == 0) {
        if ((set_or_clear_actor_status_slot(entity, 0x12,
                           (s8)(get_random_scaled_value(effect_param & 0xFF) + 2)) << 16) != 0) {
            if (entity->unk_14 & 0x4000) {
                adjust_source_value_and_finalize(entity, &D_800E1C64);
                return;
            }
        } else if (entity->unk_14 & 0x4000) {
            message_end = get_unused_text_buffer();
            message_start = message_end;
            message_end = expand_text_control_codes(&D_80024004, message_end);
            message_end = append_entity_display_text(entity, message_end);
            message_end = expand_text_control_codes(&D_80024034, message_end);
            func_80099290(message_end);
            display_text_with_fullwidth_adjustment(message_start);
        }
    }
}
