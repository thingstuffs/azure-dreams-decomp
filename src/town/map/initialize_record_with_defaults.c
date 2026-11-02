#include "common.h"
#include "town/scene/list_setup.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "shared/dungeon_effect_views.h"
#include "town/map.h"
#include "town/player/object.h"
#include "town/scene.h"

typedef struct S_800A9734_0 {
    void (*unk_00)(void *, void *, void *);
    u8 pad_04[0x5C];
    s32 unk_60;
} S_800A9734_0;   /* arg0 in initialize_record_with_defaults; pointer addresses record offset 0x10 */

   /* arg1 in initialize_record_with_defaults */

extern M2C_UNK D_800D0E60;

/* Initializes the record and context using the default data. */
void initialize_record_with_defaults(TownObjectRecord *record_data, ObjectPosition *placement, struct SpriteFrameState *unused_sprite) {
    ObjectPosition *context = placement;

    ((S_800A9734_0 *)((u8 *)record_data - 0x10))->unk_00 = &retire_object_on_check_or_callback;
    record_data->unk_50.as_s32 = 0;
    configure_the_set_mode_n_3(record_data, context, &D_800D0E60);
    context->z.v = 0;
}
