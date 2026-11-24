#include "common.h"
#include "shared/object_flags.h"
#include "sdk/libc.h"
#include "engine/text.h"
#include "town/minigame.h"


/* Displays a timed message and signals completion when its owner is ready. */
void tick_scene_value_text(TownCollectionText *message)
{
    s16 state;
    u16 timer;
    TownCollectionSequence *owner;

    owner = message->sequence;
    format_decimal_field_space_padded(
        *message->value,
        strlen(message->text),
        message->text);

    state = message->state;
    switch (state) {
    case 0:
        timer = message->timer - 1;
        message->timer = timer;
        if ((timer << 16) <= 0) {
            message->flags &= 0xFFFD;
            message->state++;
        }
        break;

    case 1:
        if (owner->flags & TOWN_COLLECTION_FINISHED) {
            (*(u16 *)((u8 *)message + -2)) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
        break;
    }
}
