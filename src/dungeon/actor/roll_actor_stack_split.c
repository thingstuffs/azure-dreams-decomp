#include "common.h"
#include "dungeon/system/random.h"
#include "engine/entity.h"
#include "shared/entity.h"
#include "dungeon/actor.h"
#include "dungeon/item.h"
#include "dungeon/item/message.h"
#include "dungeon/system.h"
#include "dungeon/data.h"


extern char stack_split_opening_text[];
extern char stack_split_named_text[];
extern char stack_split_unnamed_text[];

/* Roll the actor's stack-split chance; on a hit decrement the stack and post the split message. */
s32 roll_actor_stack_split(ActorRecord *actor, s32 chance)
{
    s32 mod;
    void *handle;
    s32 text;
    u8 count;
    s32 signed_arg;

    if (check_entity_flag_4000(actor) != 0) {
        return 0;
    }

    {
        signed_arg = generate_random_value() & 0xFFFF;
        if (actor->luck != 0) {
            mod = signed_arg % actor->luck;
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

    count = actor->current_attack;
    if (count < 2) {
        return 0;
    }

    {
        void *object;
        s32 decremented;

        object = actor;
        decremented = count - 1;
        actor->current_attack = decremented;
        apply_entity_effects(object);
    }
    handle = get_unused_text_buffer();
    text = expand_text_control_codes(stack_split_opening_text, handle);

    {
        s32 named = actor->flags14 & 0x4000;
        void *msg = actor;
        if (named) {
            text = append_entity_display_text(msg, text);
            text = expand_text_control_codes(stack_split_named_text, text);
        } else {
            text = expand_text_control_codes(stack_split_unnamed_text, text);
            text = append_entity_display_text(actor, text);
            msg = stack_split_text;
            text = expand_text_control_codes(msg, text);
        }
    }

    clear_byte_and_advance(text);
    display_text_with_fullwidth_adjustment(handle);
    play_sound_if_enabled(0x615);
    return 1;
}
