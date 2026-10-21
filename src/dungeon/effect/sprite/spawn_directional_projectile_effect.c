#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"

extern u8 D_80045340[];
extern u8 D_800DEC70[];
s32 register_node();
extern u8 D_800F6000[];
extern void advance_gravity_damped_effect_motion(void *entry, void *motion, void *object);

typedef struct S_80921B2C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
} S_80921B2C_0;

typedef struct S_80921B2C_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
} S_80921B2C_2;

typedef struct S_80921B2C_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80921B2C_3;   /* arg0 in func_80921B2C */

typedef struct S_80921B2C_4 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_80921B2C_4;

typedef struct S_80921B2C_6 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80921B2C_6;

/* Creates an effect at an offset position with direction-based motion and sprite settings. */
void func_80921B2C(S_80921B2C_3 *position, s16 x_offset, s16 y_offset, s16 z_offset) {
    u8 direction_table[32];
    u8 *direction_source;
    s32 effect_type;
    u8 *global_state;
    u8 *direction_state;
    S_80921B2C_2 *motion;
    SpriteFrameState *sprite;
    S_80921B2C_0 *effect;

    direction_source = D_800F6000;
    memcpy(direction_table, direction_source, 0x20);
    effect_type = 0x212;
    global_state = ((u8 *)(&scene_object_list_anchor));
    direction_state = global_state + 0x20;
    effect = func_8003FC64(effect_type);
    if (effect != 0) {
        u8 *directions = direction_table;

        effect->unk_10 = &advance_gravity_damped_effect_motion;
        register_node(effect, D_80045340);
        {
            SpriteFrameState *render_state;

            render_state = effect->unk_0C;
            render_state->flags |= 0xC;
            render_state->tpage_abr = 0x20;
            render_state->unk_06 = 6;
            render_state->flags |= 2;
        }
        motion = effect->unk_08;
        motion->unk_00.at00.v = (s32) position->unk_00;
        motion->unk_04.at00.v = (s32) position->unk_04;
        motion->unk_08.at00.v = (s32) position->unk_08;
        motion->unk_00.at02.v = (u16) (motion->unk_00.at02.v + x_offset);
        motion->unk_04.at02.v = (u16) (motion->unk_04.at02.v + y_offset);
        motion->unk_08.at02.v = (u16) (motion->unk_08.at02.v + z_offset);
        motion->unk_0C = (s32) ((*(s16 *)((u8 *)directions + (((u16) ((S_80921B2C_4 *)direction_state)->unk_2A
            >> 7) & 0x1C))) * 0x180000);
        motion->unk_10 = (s32) ((s16) ((S_80921B2C_6 *)((s8 *)directions
            + (((u16) ((S_80921B2C_4 *)direction_state)->unk_2A >> 7) & 0x1C)))->unk_02 * 0x180000);
        sprite = effect->unk_0C;
        sprite->scale_y = 0x800;
        sprite->scale_x = 0x800;
        sprite->color.c.b = 0x80;
        sprite->color.c.g = 0x80;
        sprite->color.c.r = 0x80;
        func_8003DB94(sprite, D_800DEC70, 0);
    }
}
