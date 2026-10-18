#include "modules/dungeon_native_abi.h"
#include "modules/dungeon_ovl_1894800.h"
#include "common.h"

typedef s32 M2C_UNK;

extern const u8 D_80024004[48];
extern const u8 D_80024034[4];
extern M2C_UNK D_800E1C8A;

extern s32 get_unused_text_buffer(void);
extern s32 expand_text_control_codes(u8 *src, u8 *dst);
extern void func_80099290(s8 *byte_ptr);
extern s32 append_entity_display_text(void *record, u8 *out);
extern void adjust_source_value_and_finalize(void *, void *);
extern s32 try_trigger_target_record_effect(void *, s32);
extern s32 set_or_clear_actor_status_slot(void *, s32, s32);
extern void display_text_with_fullwidth_adjustment(s8 *text);
extern s32 get_random_scaled_value(s16 input_value);

/* Applies a directional effect and reports the result for flagged entities. */
void func_80024098(void *entity, s32 direction, void *unused)
{
    s32 message_start;
    s32 message_end;

    if (try_trigger_target_record_effect(entity, 2) == 0) {
        if (set_or_clear_actor_status_slot(
                entity, 0x13,
                ((get_random_scaled_value(direction & 0xFF) + 4) << 24) >> 24) << 16) {
            if (*(s32 *)((u8 *)entity + 0x14) & 0x4000) {
                adjust_source_value_and_finalize(entity, &D_800E1C8A);
                return;
            }
        } else if (*(s32 *)((u8 *)entity + 0x14) & 0x4000) {
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
