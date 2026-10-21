#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"

void *allocate_list_node();            /* extern */
s32 register_node();           /* extern */
extern M2C_UNK D_80026FB0;
extern u8 D_80028808;

typedef struct S_80027070_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
} S_80027070_0;

typedef struct S_80027070_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80027070_1;

typedef struct S_80027070_3 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x5E];
    s16 unk_66;
} S_80027070_3;

/* Creates an object with the given position, graphic index, and state value. */
void *create_positioned_graphic_object(s16 x, s16 y, s16 z, s16 graphic_index, s32 state_value) {
    SpriteFrameState *graphics;
    void *object;
    S_80027070_1 *position;
    S_80027070_3 *state;

    object = allocate_list_node(0x12, ((s32 *)&scene_object_list_anchor.next));
    if (object != NULL) {
        ((S_80027070_0 *)object)->unk_10 = &D_80026FB0;
        register_node(object, project_sprite_chain);
        position = ((S_80027070_0 *)object)->unk_08;
        position->unk_02 = x;
        position->unk_06 = y;
        position->unk_0A = z;
        graphics = ((S_80027070_0 *)object)->unk_0C;
        graphics->source = (void *) ((graphic_index * 0xC) + &D_80028808);
        graphics->scale_y = 0x1000;
        graphics->scale_x = 0x1000;
        graphics->tpage_abr = 0x20;
        graphics->flags = (u16) (graphics->flags | 0xC);
        state = object + 0x20;
        state->unk_04 = state_value;
        state->unk_66 = 0x1C;
    }
    return object;
}
