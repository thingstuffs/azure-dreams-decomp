#include "common.h"

#define NULL ((void *)0)

s32 generate_random_value(void);
s32 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern void * create_actor_value_popup(s32 flags, u8 *source_data, s16 value, u16 callback_mode);
s32 get_unused_text_buffer(void);
s32 expand_text_control_codes(u8 *src, u8 *dst);
s32 func_8003AD08(s32, s32);
s32 append_entity_display_text(void *record, u8 *out);
extern void * func_80099290(s8 *byte_ptr);
extern s32 display_text_with_fullwidth_adjustment(s8 *text);

extern u8 D_80088CAC[];
extern u8 D_800E0D51[];
extern u8 D_800E0D6D[];

/* Randomly adds a quarter of the source value to the target and reports the change. */
void add_random_quarter_value(void *source, void *target) {
    int direction_aux;
    s32 amount;
    s16 signed_amount;
    s32 message_start;
    s32 message_end;
    u8 *type_data;
    void *source_entity;
    void *target_entity;

    type_data = *(u8 **)((s8 *)source + 0x50);
    if (type_data != NULL && *type_data == 0xB && !(generate_random_value() & 3)) {
        amount = ((s32)(*(u16 *)((s8 *)source + 0x64) << 0x10)) >> 0x12;
        signed_amount = amount;
        *(u16 *)((s8 *)target + 0x64) += amount;
        if (signed_amount != 0) {
            source_entity = *(void **)((s8 *)source - 0x14);
            target_entity = *(void **)((s8 *)target - 0x14);
            *(void **)((s8 *)target + 0x60) = source;
            *(s16 *)((s8 *)target + 0x6A) = get_rounded_facing_and_rounding_flag(
                *(u8 *)((s8 *)source_entity + 0x24),
                *(u8 *)((s8 *)source_entity + 0x25),
                *(u8 *)((s8 *)target_entity + 0x24),
                *(u8 *)((s8 *)target_entity + 0x25),
                &direction_aux
                );
            create_actor_value_popup(3, target, -amount, 0);
            message_end = get_unused_text_buffer();
            message_start = message_end;
            message_end = expand_text_control_codes(D_800E0D51, message_start);
            message_end = func_8003AD08(-signed_amount, message_end);
            message_end = expand_text_control_codes(D_800E0D6D, message_end);
            message_end = append_entity_display_text(target, message_end);
            message_end = expand_text_control_codes(D_80088CAC, message_end);
            func_80099290(message_end);
            display_text_with_fullwidth_adjustment(message_start);
        }
    }
}
