#include "common.h"

extern s32 apply_entity_effects(void *);
extern s32 get_unused_text_buffer(void);
extern s32 expand_text_control_codes(u8 *src, u8 *dst);
extern s32 func_80099290(s8 *byte_ptr);
extern s32 append_entity_display_text(void *record, u8 *out);
extern s32 play_sound_if_enabled(s32);
extern s32 display_text_with_fullwidth_adjustment(s8 *text);
extern s32 generate_random_value(void);
extern s32 check_entity_flag_4000(void *);

extern char D_800E1A88[];
extern char D_800E1A9D[];
extern char D_800E1AC2[];
extern char stack_split_text[];

/* Roll the actor's stack-split chance; on a hit decrement the stack and post the split message. */
s32 roll_actor_stack_split(void *actor, s32 chance)
{
    s32 mod;
    s32 handle;
    s32 text;
    u8 count;
    s32 signed_arg;

    if (check_entity_flag_4000(actor) != 0) {
        return 0;
    }

    {
        signed_arg = generate_random_value() & 0xFFFF;
        if (*(u8 *)((u8 *)actor + 3) != 0) {
            mod = signed_arg % *(u8 *)((u8 *)actor + 3);
        } else {
            mod = 0;
        }
    }

    {
        s32 work;

        text = chance << 16;
        signed_arg = text >> 16;
        work = mod < signed_arg;
        if (!work) {
            work = 0xFF;
            if (signed_arg != work) {
                return 0;
            }
        }
    }

    count = *(u8 *)((u8 *)actor + 0x26);
    if (count < 2) {
        return 0;
    }

    {
        void *object;
        s32 decremented;

        object = actor;
        decremented = count - 1;
        *(u8 *)((u8 *)actor + 0x26) = decremented;
        apply_entity_effects(object);
    }
    handle = get_unused_text_buffer();
    text = expand_text_control_codes(D_800E1A88, handle);

    {
        s32 named = *(s32 *)((u8 *)actor + 0x14) & 0x4000;
        void *msg = actor;
        if (named) {
            text = append_entity_display_text(msg, text);
            text = expand_text_control_codes(D_800E1A9D, text);
        } else {
            text = expand_text_control_codes(D_800E1AC2, text);
            text = append_entity_display_text(actor, text);
            msg = stack_split_text;
            text = expand_text_control_codes(msg, text);
        }
    }

    func_80099290(text);
    display_text_with_fullwidth_adjustment(handle);
    play_sound_if_enabled(0x615);
    return 1;
}
