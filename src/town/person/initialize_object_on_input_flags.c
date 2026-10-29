#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_index_slots.h"

typedef struct {
    s8 pad0[0x54];
    void *unk54;
    u8 pad58[8];
    s32 unk60;
} Obj;


extern void initialize_object_entries();
extern u8 D_800C3C28[];
extern s32 D_800D5CD0[];

// Process the flagged event, clear the object's indexed flag, and reset its state pointer.
void initialize_object_on_input_flags(Obj *object, s32 unused, SpriteFrameState *event) {
    if (event->flags & 0x6000) {
        initialize_object_entries(object, event, D_800D5CD0);
        object_index_slots[object->unk60].unk_00 = 0;
        object->unk54 = D_800C3C28;
    }
}
