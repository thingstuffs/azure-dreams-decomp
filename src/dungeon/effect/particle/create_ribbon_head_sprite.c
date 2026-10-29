#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/dungeon_sprite_data.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "records/Rec_func_80167A98_arg1.h"
#include "records/Rec_func_80167A98_arg0.h"
#include "engine/node.h"
#include "dungeon/effect/particle.h"
#include "slus.h"

struct Dst;
struct Elem;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u8 pad[0x5A];
} PositionTableEntry;
extern s32 rising_sprite_entries[3];
#include "shared/sprite_source.h"
extern SpriteSourceEntry moving_sprite_entries[];
extern M2C_UNK D_80167A2C;
extern PositionTableEntry ribbon_vertices[];

/* Creates a visual object with a source-indexed position offset and appearance. */
void create_ribbon_head_sprite(Rec_func_80167A98_arg0 *source, Rec_func_80167A98_arg1 *origin) {
    ObjectPosition *position;
    SpriteFrameState *render_state;
    ObjectNodeHeader *object;

    object = allocate_flagged_object_node(0x212);
    if (object != NULL) {
        object->update_callback = &D_80167A2C;
        register_node(object, project_sprite_chain);
        render_state = object->sprite;
        render_state->tpage_abr = 0x20;
        render_state->depth_bias = 0;
        render_state->flags = (u16) (render_state->flags | 0xC);
        position = object->position;
        position->x.v = origin->unk_00 + (ribbon_vertices[source->unk_1C].x << 0x11);
        position->y.v = origin->unk_04 + (ribbon_vertices[source->unk_1C].y << 0x11);
        position->z.v = origin->unk_08 + (ribbon_vertices[source->unk_1C].z << 0x11);
        render_state = object->sprite;
        render_state->scale_y = 0x1000;
        render_state->scale_x = 0x1000;
        render_state->color.c.b = 0x80;
        render_state->color.c.g = 0x80;
        render_state->color.c.r = 0x80;
        if (source->unk_1C == 0) {
            select_record_entry_and_value(render_state, effect_sprite_sources, 0);
        }
        if (source->unk_1C == 1) {
            select_record_entry_and_value(render_state, &moving_sprite_entries, 0);
        }
        if (source->unk_1C == 2) {
            select_record_entry_and_value(render_state, &rising_sprite_entries, 0);
        }
    }
}
