#include "dungeon/monster/troll/troll_flash_effects.h"

/* Creates and initializes an object at an offset from the supplied position. */
void spawn_growing_rotating_flash(void *unused, s32 *position) {
    T_80171928_Object *object;
    T_80171928_Header *header;
    T_80171928_Child *child;
    u32 *object_pos;

    object = func_8003FC64(0x212);
    if (object != NULL) {
        header = (T_80171928_Header *)((u8 *)object + 0x20);
        header->value18 = 0x1C;
        header->value1a = 0x1C;
        object->field10 = &update_growing_rotating_flash;
        register_node(object, project_sprite_chain);
        child = object->child;
        child->value10 = 0x60;
        child->flags14 |= 0xC;
        object_pos = object->data;
        object_pos[0] = position[0];
        object_pos[1] = position[1];
        object_pos[2] = position[2] + (s32)0xFFB00000;
        child = object->child;
        child->value1e = 0x190;
        child->value1c = 0x190;
        child->color_e = 0x80;
        child->color_d = 0x80;
        child->color_c = 0x80;
        object->blob = D_80175EDC;
        child->field8 = &object->blob;
    }
}
