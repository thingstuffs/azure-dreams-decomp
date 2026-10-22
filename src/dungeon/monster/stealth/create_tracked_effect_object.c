#include "dungeon/monster/stealth/create_tracked_effect_object.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/monster/stealth/create_tracked_effect_object.h"

/* Creates a Stealth actor, initializes its status and tile, and optionally unlinks its translucent render
 * node. */
void *create_tracked_effect_object(s16 mode, s16 value24, s16 value25, s16 value0A)
{
    s32 modeBits;
    s32 optionValue;
    void *objectBaseForCallbacks;
    SpriteFrameState *data0C;
    S_8015E854_2 *data08;
    void *objectState;
    void *objectBase;
    S_8015E854_1 *result;

    result = 0;
    optionValue = 1;
    objectBase = allocate_list_node(274, ((u8 *)(&scene_object_list_anchor)));
    if (objectBase != 0) {
        result = (u8 *)objectBase + 0x20;
        ((S_8015E854_0 *)objectBase)->unk_10 = func_8015EA8C;
        result->unk_13 = 0x23;
        register_node(objectBase, project_sprite_chain);
        data08 = ((S_8015E854_0 *)objectBase)->unk_08;
        data08->unk_0A = value0A;
        data0C = ((S_8015E854_0 *)objectBase)->unk_0C;
        data0C->unk_25 = value25;
        objectState = result;
        data0C->frameTable = D_80161D30;
        modeBits = mode & 3;
        data0C->unk_24 = value24;
        if (modeBits == 1) {
            result->unk_14 |= 0x6000;
            result->unk_1C |= 0x6000;
        } else if (modeBits >= 2) {
            result->unk_14 |= 0x2000;
            result->unk_1C |= 0x2000;
        } else if (((mode & ~3) << 16) == 0) {
            if (!(result->unk_14 & 0x200)) {
                if (generate_random_value() & 1) {
                    result->unk_1C |= 0x200;
                    set_or_clear_actor_status_slot(result, 1, (generate_random_value() & 0x3F) | 0x20);
                    data0C->frameTable = D_80161D78;
                }
            }
            optionValue = generate_random_value() & 3;
        }
        initialize_actor_sprite_and_animation(objectBase, data08, data0C, mode);
        ((S_8015E854_4 *)objectState)->unk_9A = 0xFF;
        ((S_8015E854_4 *)objectState)->unk_9C = -1;
        ((S_8015E854_4 *)objectState)->unk_8C = func_8015EF74;
        ((S_8015E854_4 *)objectState)->unk_A4 = -1;
        if (optionValue != 0) {
            ((S_8015E854_4 *)objectState)->unk_A6 = 0;
        } else {
            objectBaseForCallbacks = (u8 *)objectState - 0x20;
            ((S_8015E854_4 *)objectState)->unk_A6 = 1;
            data0C->tpage_abr = 0x60;
            data0C->flags |= 0xC;
            data0C->clut -= 0x80;
            unlink_node(objectBaseForCallbacks);
            retire_tracked_effect_by_id(objectBaseForCallbacks);
        }
        try_move_actor_to_valid_position(objectState, data08, data0C, result);
    }
    return result;
}
