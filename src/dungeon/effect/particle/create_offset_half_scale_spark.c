#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/dungeon_sprite_data.h"
#include "shared/slus_callbacks.h"

typedef struct Sprite {
    u8 pad0[6];
    s16 field6;
    u8 pad8[4];
    u8 colorC;
    u8 colorD;
    u8 colorE;
    u8 padF;
    s16 field10;
    u8 pad12[2];
    u16 flags14;
    u8 pad16[6];
    s16 scale1C;
    s16 scale1E;
} Sprite;

typedef struct Object {
    u8 pad0[8];
    void *position;
    Sprite *sprite;
    void *callback;
} Object;

extern void select_record_entry_and_value(void *state, void *entries, short index);
#include "engine/node.h"
extern u8 D_80165580;

/* Creates a gray half-scale spark at the source position plus the supplied offsets. */
void create_offset_half_scale_spark(void *source_position, s32 x_offset, s32 y_offset, s32 z_offset) {
    ObjectNodeHeader *obj;
    SpriteFrameState *sprite;
    s32 z_fixed;
    u16 x;
    u16 y;

    obj = allocate_flagged_object_node(0x212);
    if (obj != 0) {
        obj->update_callback = &D_80165580;
        register_node(obj, project_sprite_chain);
        sprite = obj->sprite;
        sprite->tpage_abr = 0x20;
        sprite->depth_bias = 6;
        sprite->flags |= 0xC;
        {
            ObjectPosition *position;

            position = obj->position;
            position->x.v = *(s32 *)((u8 *)source_position + 0);
            position->y.v = *(s32 *)((u8 *)source_position + 4);
            x = *(u16 *)&position->x.w.i;
            z_fixed = *(s32 *)((u8 *)source_position + 8);
            position->x.w.i = (u16)(x + x_offset);
            y = *(u16 *)&position->y.w.i;
            position->z.v = z_fixed;
            z_fixed = *(u16 *)&position->z.w.i + z_offset;
            position->y.w.i = (u16)(y + y_offset);
            position->z.w.i = (u16)z_fixed;
        }
        sprite = obj->sprite;
        sprite->scale_y = 0x800;
        sprite->scale_x = 0x800;
        sprite->color.c.b = 0x80;
        sprite->color.c.g = 0x80;
        sprite->color.c.r = 0x80;
        select_record_entry_and_value(sprite, effect_sprite_sources, 0);
    }
}
