#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/dungeon_sprite_data.h"
#include "shared/slus_callbacks.h"

typedef s32 M2C_UNK;
struct Dst;
struct Elem;

typedef struct S_80172CC8_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80172CC8_1;   /* arg0 in create_boss_display_variant */

typedef struct {
    u8 unk00[6];
    s16 field_06;
    u8 unk08[4];
    u8 field_0C;
    u8 field_0D;
    u8 field_0E;
    u8 unk0F;
    s16 field_10;
    u8 unk12[2];
    u16 flags_14;
    u8 unk16[6];
    s16 field_1C;
    s16 field_1E;
} Sub;

typedef struct {
    u8 unk00[8];
    void *position;
    Sub *sub;
    s32 *callback;
} Node;

extern void select_record_entry_and_value(struct Dst *state, struct Elem *entries, short index);
s32 register_node();

extern s32 rising_sprite_entries[3];
extern M2C_UNK D_80170D60[3];

/* Creates a node at an offset from the origin and configures its display variant. */
/* Creates an offset gray sprite at scale 0x1400, choosing effect_sprite_sources or D_800DEDB0 from the
 * variant. */
void create_boss_display_variant(S_80172CC8_1 *origin, s16 x_offset, s16 y_offset, s16 z_offset, s16 variant) {
    SpriteFrameState *setup_sub;
    SpriteFrameState *display_sub;
    ObjectNodeHeader *node;
    ObjectPosition *position;
    s32 origin_z;
    u16 x;
    u16 y;
    u16 z;

    node = (Node *)allocate_flagged_object_node(0x212);
    if (node != 0) {
        node->update_callback = D_80170D60;
        register_node(node, project_sprite_chain);
        setup_sub = *(Sub * *)&node->sprite;
        setup_sub->tpage_abr = 0x20;
        setup_sub->depth_bias = 6;
        setup_sub->flags |= 0xC;
        position = node->position;
        position->x.v = origin->unk_00;
        position->y.v = origin->unk_04;
        x = *(u16 *)&position->x.w.i;
        origin_z = origin->unk_08;
        position->x.w.i = (u16)(x + x_offset);
        y = *(u16 *)&position->y.w.i;
        position->z.v = origin_z;
        z = *(u16 *)&position->z.w.i;
        position->y.w.i = (u16)(y + y_offset);
        position->z.w.i = (u16)(z + z_offset);
        display_sub = *(Sub * *)&node->sprite;
        display_sub->scale_y = 0x1400;
        display_sub->scale_x = 0x1400;
        display_sub->color.c.b = 0x80;
        display_sub->color.c.g = 0x80;
        display_sub->color.c.r = 0x80;
        if (variant == 0) {
            select_record_entry_and_value(display_sub, effect_sprite_sources, 0);
        } else {
            select_record_entry_and_value(display_sub, rising_sprite_entries, 0);
        }
    }
}
