#include "town/person/state_updates.h"
#include "engine/node/registration.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity_objects.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "records/Rec_D_80082E80.h"
#include "engine/script.h"
#include "town/person.h"

/* garbage-passthru: a2/a3 survive load_position_history_entry; explicit arguments add saves/reloads absent from retail. */
#include "town/system/person_idle_dispatch.h"

extern s32 D_800834A8;

/* Tracks idle time, runs the person's callback, and updates the sprite for its heading and mirror flag. */
void update_person_view_and_record(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *record) {
    GameWork *work = &g_game_work;
    Fixed1616 buf[6];
    s32 index;
    u16 flag_value;

    if (D_800834A8 == 0) {
        unlink_node_if_registered(object);
        NODE_HEADER(object)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }

    load_position_history_entry(buf, 0);
    if (buf[0].w.i != view_reference_entity.x.w.i || buf[1].w.i != view_reference_entity.y.w.i ||
        buf[2].w.i != view_reference_entity.z.w.i || service_script_controller() != 0 ||
        (work->buttons & 0xF000) != 0) {
        push_position_history();
        object->unk_90 = 0;
    } else {
        object->unk_90 = object->unk_90 + 1;
        if (object->unk_90 > 100) {
            object->unk_90 = 100;
        }
    }
    ((TownIndexedHandler)object->state_callback.as_pm)(object, position, record);
    if ((NODE_HEADER(object)->flags & 0x8000) != 0) {
        return;
    }

    index = quantize_heading_to_sector(object->heading, (s16)object->direction_count);
    if ((*(s16 *)((u8 *)object + (0x74))) != index) {
        clear_object_status_and_dispatch_target(object, record, object->direction_animations[index],
                      record->unk_04);
        (*(s16 *)((u8 *)object + (0x74))) = index;
    }

    if ((object->flip_inverted & 1) == 0) {
        if ((s16)check_heading_past_half_sector(object->heading,
                               (s16)object->direction_count) == 0) {
            flag_value = record->flags;
                         /* MATCH: keep each clear load in its own arm. */
            flag_value = (u16)(flag_value - (flag_value & 1));
        } else {
            flag_value = record->flags | 1;
        }
    } else {
        if ((s16)check_heading_past_half_sector(object->heading,
                               (s16)object->direction_count) != 0) {
            flag_value = record->flags;

            flag_value &= 0xFFFE;
        } else {
            flag_value = record->flags | 1;
        }
    }

         /* MATCH: keep the flag store in the common tail. */
    record->flags = flag_value;
    advance_object_animation_when_idle(object, record, 0, 0);
}
