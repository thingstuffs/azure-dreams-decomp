#include "common.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800AD058_arg0.h"
#include "shared/entity.h"
#include "records/Rec_func_800AD058_arg2.h"
#include "dungeon/system.h"



extern s32 update_actor_defeat_removal();
extern void create_and_initializes_display_source_position_appearance(void *source, Rec_func_800AD058_arg2 *record, void *appearance);


/*
 * Waits for pending actions, creates an optional display, applies the defeat tint/flags with a
 * 16-tick delay and sound 0x805, then runs the shared defeat-removal update.
 */
void initialize_the_visual_effect_advances_action_state(Rec_func_800AD058_arg0 *action, ObjectPosition *context, Rec_func_800AD058_arg2 *visual, EntityRec *entity) {
    s32 one;
    s32 phase;

    phase = action->unk_9B;
    one = 1;
    switch (phase) {
    case 0:
        if (g_dungeon_status.activity_counts.parts.pending_action_count != 0) {
            return;
        }
        action->unk_9B = (u8)one;
    case 1:
        if (entity->unk_49 != 0) {
            create_and_initializes_display_source_position_appearance(context, visual, entity);
            entity->unk_48 = 0;
            entity->unk_49 = 0U;
        }

        visual->unk_10 = 0x20;
        visual->unk_12 = (u16)(visual->unk_12 - 0x80);
        visual->unk_14 = (u16)(visual->unk_14 | 0xC);
        entity->flags1C = entity->flags1C | 0x10000000;
        visual->unk_0C = 0x808080;
        action->unk_96 = 0x10;
        action->unk_9B = (u8)(action->unk_9B + 1);
        play_sound_if_enabled(0x805);
        return;
    case 2:
        update_actor_defeat_removal(action, context, visual, entity);
        return;
    }
}
