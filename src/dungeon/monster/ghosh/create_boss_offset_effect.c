#include "shared/object_node.h"
#include "common.h"
#include "dungeon/monster/ghosh.h"
#include "shared/slus_callbacks.h"
#include "engine/node.h"

typedef struct {
    u8 bytes[12];
} Blob12;

extern s32 D_801723D0;
extern Blob12 D_80174AC8;

/* Creates and initializes an effect offset from the current object's position. */
void create_boss_offset_effect(void) {
    ObjectPosition *source_pos;
    ObjectNodeHeader *effect;
    u8 *sprite;
    s32 *effect_pos;
    u8 *effect_state;

    source_pos = ghosh_boss_node->position;
    effect = allocate_flagged_object_node(0x212);
    if (effect != (void *)0) {
        effect_state = ((u8 *)effect) + 0x20;
        *(s16 *)(effect_state + 0x16) = 0x1E;
        *(s16 *)(effect_state + 0x18) = 0x1E;
        effect->update_callback = &D_801723D0;
        register_node(effect, project_sprite_chain);
        sprite = *(u8 * *)&effect->sprite;
        *(s16 *)(sprite + 0x10) = 0x20;
        *(s16 *)(sprite + 6) = 0;
        *(u16 *)(sprite + 0x14) |= 0xC;
        effect_pos = *(s32 * *)&effect->position;
        effect_pos[0] = source_pos->x.v;
        effect_pos[1] = source_pos->y.v;
        effect_pos[2] = source_pos->z.v + 0xFFC80000;
        sprite = *(u8 * *)&effect->sprite;
        *(s16 *)(sprite + 0x1E) = 0x400;
        *(s16 *)(sprite + 0x1C) = 0x400;
        *(sprite + 0xD) = 0x80;
        *(sprite + 0xC) = 0x80;
        *(sprite + 0xE) = 0;
        *(Blob12 *)(((u8 *)effect) + 0x48) = D_80174AC8;
        *(void **)(sprite + 8) = ((u8 *)effect) + 0x48;
    }
}
