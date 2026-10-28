#include "common.h"
#include "town/event/object_setup.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"
#include "records/Rec_func_80094268_arg0.h"
#include "records/Rec_D_80082E80.h"
void register_node_if_unregistered(void *block_data, void *registration_id);
struct EntityRec; struct Rec_D_80082E80; struct Rec_func_80094268_arg0; void select_object_value_by_height_band(struct Rec_func_80094268_arg0 *, void *, struct EntityRec *, struct Rec_D_80082E80 *);
void dispatch_object_event_or_retire(void *object, s32 event, s32 event_data);
void noop_hook(void);

typedef struct TownObjectSetup {
    u8 pad_00[0x58];
    void *data;
} TownObjectSetup;

typedef struct S_8009B218_0_pre {
    s32 * unk_00;
    u8 pad_04[0xC];
} S_8009B218_0_pre;   /* the 0x10 bytes before arg0 in initialize_optional_object_state, addressed as arg0[-1] */

/* Initialize object and state, using the supplied value or default data. */
void initialize_optional_object_state(void *object, void *context, void *state, void *init_value) {
    ((S_8009B218_0_pre *)object)[-1].unk_00 = &dispatch_object_event_or_retire;
    register_node_if_unregistered(object, project_sprite_chain);
    ((Rec_func_80094268_arg0 *)object)->unk_8C = 0;
    ((Rec_func_80094268_arg0 *)object)->unk_8E = 0;
    ((SpriteFrameState *)state)->unk_00 = 0;
    ((SpriteFrameState *)state)->unk_04 = 0;
    ((SpriteFrameState *)state)->frame_ticks = 0;
    if (init_value != 0) {
        ((TownObjectSetup *)object)->data = init_value;
        select_object_value_by_height_band(object, object, context, state);
        return;
    }
    ((Rec_func_80094268_arg0 *)object)->unk_50.as_pm = &noop_hook;
}
