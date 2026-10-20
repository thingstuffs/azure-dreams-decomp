#include "common.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

void initialize_object_entries(s32, void *, void *);           /* extern */
void clear_record_indexed_byte();        /* extern */
extern M2C_UNK D_800D54C4;

/* Process the object when either of its 0x6000 flag bits is set. */
void process_object_0x6000_flag_bits(s32 contextId, s32 contextData, SpriteFrameState *object) {
    if (object->flags & 0x6000) {
        initialize_object_entries(contextId, object, &D_800D54C4);
        clear_record_indexed_byte(contextId, contextData, object);
    }
}
