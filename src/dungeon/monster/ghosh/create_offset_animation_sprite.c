#include "shared/object_node.h"
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

void func_8003DB94(struct Dst *state, struct Elem *entries, short index);
s32 register_node(RegistrationNode *entry, s32 registration_id);
void func_80170D60(void *destination, s32 unused, void *source);

/* Creates and configures a node at a fixed offset from the given position. */
void create_offset_animation_sprite(void *unused, void *origin) {
    Node *node;
    SpriteFrameState *node_sub;
    Vec3 *position;
    SpriteFrameState *display_sub;

    node = (Node *)func_8003FC64(0x212);
    if (node != 0) {
        node->callback = &func_80170D60;
        register_node(node, project_sprite_chain);
        node_sub = node->sub;
        node_sub->tpage_abr = 0x20;
        node_sub->unk_06 = 6;
        node_sub->flags |= 0xC;
        position = node->position;
        position->x = ((Vec3 *)origin)->x + 0x180000;
        position->y = ((Vec3 *)origin)->y;
        position->z = ((Vec3 *)origin)->z + 0xFFF00000;
        display_sub = node->sub;
        display_sub->scale_y = 0x1400;
        display_sub->scale_x = 0x1400;
        display_sub->color.c.b = 0x80;
        display_sub->color.c.g = 0x80;
        display_sub->color.c.r = 0x80;
        func_8003DB94(display_sub, D_800DE870, 0);
    }
}
