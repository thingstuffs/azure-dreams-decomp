#include "common.h"
#include "m2c_compat.h"
#include "shared/sprite_frame_state.h"
#include "town/scene/list_setup.h"
#include "town/player/object_setup.h"
#include "town/menu.h"
#include "town/player/object.h"

typedef struct S_800A6E1C_0 {
    void (*unk_00)();
    u8 pad_04[0x5C];
    void (*unk_60)();
} S_800A6E1C_0;   /* arg0 in initialize_unit_scale_object; pointer addresses record offset 0x10 */

extern void unit_scale_record_handler_address();
extern void D_800A6EA4();
extern M2C_UNK D_800D0DC0;

/* Initializes object callbacks and state, then sets unit scale. */
void initialize_unit_scale_object(void *object, void *position, struct SpriteFrameState *transform) {
    ((S_800A6E1C_0 *)((u8 *)object - 0x10))->unk_00 = &unit_scale_record_handler_address;
    ((S_800A6E1C_0 *)((u8 *)object - 0x10))->unk_60 = &D_800A6EA4;
    initialize_object_transform_and_state((s32)(object), transform, 0xA);
    configure_the_set_mode_n_3(object, position, &D_800D0DC0);
    transform->offset_x = 0x1000;
    transform->scale_y = 0x1000;
    transform->scale_x = 0x1000;
    transform->angle_x = 0;
}
