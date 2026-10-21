#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "shared/vector.h"
void register_node_if_unregistered(void *block_data, s32 registration_id);           /* extern */
struct Dst;
struct Elem;
void select_record_entry_and_value(struct Dst *state, struct Elem *entries, short index);  /* extern */
void *allocate_list_node();            /* extern */
void load_indexed_state_value();      /* extern */
typedef struct S_800C8B8C_0 S_800C8B8C_0;
void call_owner_callback(S_800C8B8C_0 *owner);
extern M2C_UNK D_800EE344;

typedef struct S_800C8A68_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
} S_800C8A68_0;

typedef struct S_800C8A68_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
} S_800C8A68_1;

   /* arg0 in create_offset_effect_object */

typedef struct S_800C8A68_3 {
    u8 pad_00[0x90];
    s16 unk_90;
} S_800C8A68_3;

/* Allocate and initialize an object at an offset from the supplied position. */
s32 create_offset_effect_object(IntVector3 *source_pos) {
    S_800C8A68_1 *position;
    S_800C8A68_3 *object_state;
    SpriteFrameState *render_state;
    void *object;
    s32 offset_z;

    object = allocate_list_node(0x136, ((s32 *)&scene_object_list_anchor.next));
    if (object == NULL) {
        return 0;
    }
    position = ((S_800C8A68_0 *)object)->unk_08;
    render_state = ((S_800C8A68_0 *)object)->unk_0C;
    object_state = object + 0x20;
    position->unk_00 = source_pos->x;
    position->unk_04 = source_pos->y;
    offset_z = source_pos->z + 0xFFDC0000;
    position->unk_0C = 0x100000;
    position->unk_10 = 0;
    position->unk_08 = offset_z;
    ((S_800C8A68_0 *)object)->unk_10 = &call_owner_callback;
    object_state->unk_90 = 2;
    load_indexed_state_value(object_state, position, render_state);
    render_state->scale_y = 0x1000;
    render_state->scale_x = 0x1000;
    render_state->color.word = 0x808080;
    select_record_entry_and_value(render_state, &D_800EE344, 0);
    register_node_if_unregistered(object_state, project_sprite_chain);
    return (s32) object;
}
