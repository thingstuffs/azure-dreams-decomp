#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/dungeon_sprite_data.h"
#include "shared/slus_callbacks.h"

typedef struct RegistrationNode RegistrationNode;
struct Dst;
struct Elem;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Vec3;

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
    Vec3 *position;
    Sub *sub;
    s32 *callback;
} Node;

void select_record_entry_and_value(struct Dst *state, struct Elem *entries, short index);
s32 register_node(RegistrationNode *entry, void *registration_id);
void func_80170D60(void *destination, s32 unused, void *source);

/* Creates and configures a node at a fixed offset from the given position. */
void create_offset_animation_sprite(void *unused, ObjectPosition *origin) {
    ObjectNodeHeader *node;
    SpriteFrameState *node_sub;
    ObjectPosition *position;
    SpriteFrameState *display_sub;

    node = (Node *)allocate_flagged_object_node(0x212);
    if (node != 0) {
        node->update_callback = &func_80170D60;
        register_node(node, project_sprite_chain);
        node_sub = *(Sub * *)&node->sprite;
        node_sub->tpage_abr = 0x20;
        node_sub->depth_bias = 6;
        node_sub->flags |= 0xC;
        position = *(Vec3 * *)&node->position;
        position->x.v = origin->x.v + 0x180000;
        position->y.v = origin->y.v;
        position->z.v = origin->z.v + 0xFFF00000;
        display_sub = *(Sub * *)&node->sprite;
        display_sub->scale_y = 0x1400;
        display_sub->scale_x = 0x1400;
        display_sub->color.c.b = 0x80;
        display_sub->color.c.g = 0x80;
        display_sub->color.c.r = 0x80;
        select_record_entry_and_value(display_sub, effect_sprite_sources, 0);
    }
}
