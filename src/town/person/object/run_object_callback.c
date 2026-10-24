/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "records/Rec_D_80082E80.h"

typedef void (*Callback)(void *, void *, void *);

#include "town/system/person_idle_dispatch.h"
s32 quantize_heading_to_sector();
s32 check_heading_past_half_sector();

/* Run the object callback and update its selected entry and record flags when enabled. */
void run_object_callback(void *object, void *context, SpriteFrameState *record) {
    s32 entry_index;
    u16 flags;

    (*(Callback *)((u8 *)object + 0x50))(object, context, record);
    if (!((*(u16 *)((u8 *)object + -2)) & 0x8000)) {
        entry_index = quantize_heading_to_sector((*(s16 *)((u8 *)object + 0x72)), (*(s16 *)((u8 *)object + 0x64)));
        if ((*(s16 *)((u8 *)object + 0x74)) != entry_index) {
            clear_object_status_and_dispatch_target(object, record, (*(s32 **)((u8 *)object + 0x78))[entry_index], record->unk_04);
            (*(s16 *)((u8 *)object + 0x74)) = entry_index;
        }
        if ((check_heading_past_half_sector((*(s16 *)((u8 *)object + 0x72)), (*(s16 *)((u8 *)object + 0x64))) << 0x10) != 0) {
            flags = record->flags | 1;
        } else {
            flags = record->flags & 0xFFFE;
        }
        record->flags = flags;
        dispatch_object_when_idle(object, record, 0, 0);
    }
}
