#include "town/person/state_updates.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity_objects.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082E80.h"
#include "engine/script.h"
#include "town/person.h"

typedef void (*Callback)(void *, void *, void *);

extern void unlink_node_if_registered(void *, void *);
/* garbage-passthru: a2/a3 survive load_record_halfwords_3; explicit arguments add saves/reloads absent from retail. */
#include "town/system/person_idle_dispatch.h"

extern s32 D_800834A8;

/* Tracks idle time, runs the person's callback, and updates the sprite for its heading and mirror flag. */
void update_person_view_and_record(void *ptr, void *value, SpriteFrameState *record) {
    GameWork *work = &g_game_work;
    s16 buf[12];
    s32 index;
    u16 flag_value;

    if (D_800834A8 == 0) {
        unlink_node_if_registered(ptr, value);
        (*(u16 *)((u8 *)ptr + (-2))) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }

    load_record_halfwords_3(buf, 0);
    if (buf[1] != view_reference_entity.x.w.i || buf[3] != view_reference_entity.y.w.i ||
        buf[5] != view_reference_entity.z.w.i || service_script_controller() != 0 ||
        (work->buttons & 0xF000) != 0) {
        shift_history_and_store_current_values();
        (*(s16 *)((u8 *)ptr + (0x90))) = 0;
    } else {
        (*(s16 *)((u8 *)ptr + (0x90))) = (*(s16 *)((u8 *)ptr + (0x90))) + 1;
        if ((*(s16 *)((u8 *)ptr + (0x90))) > 100) {
            (*(s16 *)((u8 *)ptr + (0x90))) = 100;
        }
    }
    (*(Callback *)((u8 *)ptr + (0x50)))(ptr, value, record);
    if (((*(u16 *)((u8 *)ptr + (-2))) & 0x8000) != 0) {
        return;
    }

    index = quantize_heading_to_sector((*(s16 *)((u8 *)ptr + (0x72))), (*(s16 *)((u8 *)ptr + (0x64))));
    if ((*(s16 *)((u8 *)ptr + (0x74))) != index) {
        clear_object_status_and_dispatch_target(ptr, record, ((void **)(*(void * *)((u8 *)ptr + (0x78))))[index],
                      record->unk_04);
        (*(s16 *)((u8 *)ptr + (0x74))) = index;
    }

    if (((*(u8 *)((u8 *)ptr + (0x71))) & 1) == 0) {
        if ((s16)check_heading_past_half_sector((*(s16 *)((u8 *)ptr + (0x72))),
                               (*(s16 *)((u8 *)ptr + (0x64)))) == 0) {
            flag_value = record->flags;
                         /* MATCH: keep each clear load in its own arm. */
            flag_value = (u16)(flag_value - (flag_value & 1));
        } else {
            flag_value = record->flags | 1;
        }
    } else {
        if ((s16)check_heading_past_half_sector((*(s16 *)((u8 *)ptr + (0x72))),
                               (*(s16 *)((u8 *)ptr + (0x64)))) != 0) {
            flag_value = record->flags;

            flag_value &= 0xFFFE;
        } else {
            flag_value = record->flags | 1;
        }
    }

         /* MATCH: keep the flag store in the common tail. */
    record->flags = flag_value;
    dispatch_object_when_idle(ptr, record, 0, 0);
}
