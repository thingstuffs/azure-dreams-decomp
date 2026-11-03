#include "common.h"
#include "slus.h"
#include "shared/game_work.h"
#include "engine/node.h"
#include "shared/entity.h"
#include "shared/town_object.h"
#include "shared/object_node.h"
#include "town/map/object.h"

typedef struct {
    u32 unk0;
    s8 unk4;
    s8 unk5;
    u8 pad6[2];
    s32 unk8;
    u8 unkC;
    u8 unkD;
    u8 unkE;
    u8 padF;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    s16 unk1E;
    s16 unk20;
} FuncData;



/* Initializes object data, transform, color, and rendering defaults. */
void initialize_object_data_transform_color(TownObjectRecord *object, ObjectPosition *render_data, FuncData *state) {
    u8 blue;

    ((ObjectNodeHeader *)object - 1)->update_callback = deactivate_object_triggered;
    register_node((ObjectNodeHeader *)object - 1, draw_linked_lit_meshes);

    object->unk_66.as_s16 = 0;
    state->unk1C = 0x1000;
    state->unk1E = 0x1000;
    state->unk20 = 0x1000;
    state->unk12 = 0;
    state->unk14 = 0;
    state->unk10 = 0;
    state->unk16 = 0;
    state->unk18 = 0;
    state->unk1A = 0;
    state->unk0 = 0;
    state->unk4 = 0;
    state->unk5 = 0;
    state->unkC = g_game_work.view.tint.parts.tint_r;
    state->unkD = g_game_work.view.tint.parts.tint_g;
    blue = g_game_work.view.tint.parts.tint_b;
    state->unk8 = 0x1F;
    state->unkE = blue;
    render_data->z.v = 0xFF600000;
}
