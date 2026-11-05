/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "records/Rec_D_80082E80.h"
#include "shared/object_node.h"

typedef void (*Callback)(void *, void *, void *);

#include "town/system/person_idle_dispatch.h"
#include "town/person.h"
#include "town/person/object.h"

/* Run the object callback and update its selected entry and record flags when enabled. */
void run_object_callback(TownObjectRecord *object, ObjectPosition *context, SpriteFrameState *record) {
    s32 entry_index;
    u16 flags;

    (*(Callback *)((u8 *)object + 0x50))(object, context, record);
    if (!((((ObjectNodeHeader *)object - 1)->flags) & 0x8000)) {
        entry_index = quantize_heading_to_sector(object->heading, ((s16)(object->unk_64)));
        if (((s16)(object->unk_74.as_u16)) != entry_index) {
            clear_object_status_and_dispatch_target(object, record, object->unk_78[entry_index], record->unk_04);
            object->unk_74.as_u16 = entry_index;
        }
        if ((check_heading_past_half_sector(object->heading, ((s16)(object->unk_64))) << 0x10) != 0) {
            flags = record->flags | 1;
        } else {
            flags = record->flags & 0xFFFE;
        }
        record->flags = flags;
        dispatch_object_when_idle(object, record, 0, 0);
    }
}
