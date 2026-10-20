#include "modules/dungeon_ovl_18a0800.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/dungeon_moving_views.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80024D90_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
} S_80024D90_0;

   /* saved_arg0 in spawn_ring_effects */

typedef struct S_80024D90_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80024D90_2;

typedef struct S_80024D90_4 {
    u8 pad_00[0x14];
    s16 unk_14;
    u8 pad_16[0x8];
    s16 unk_1E;
    u8 pad_20[0x4];
    s16 unk_24;
} S_80024D90_4;

/* Spawns sixteen effects in a ring around the source position. */
void *spawn_ring_effects(void *source_pos, s16 effect_param) {
    register MovingPosition *origin = source_pos;
    register s16 state_param = effect_param;
    register s32 effect_index = 0;
    register s32 *callback = func_80024B98;
    register u16 *counter_page = (u16 *)0x80020000;
    register s32 component_offset = -0x400;
    register void *effect;
    S_80024D90_2 *position;
    register s32 angle;
    s32 value;
    register SpriteFrameState *component;

    do {
        effect = func_8003FC64(0x202);
        if (effect != NULL) {
            ((S_80024D90_0 *)effect)->unk_10 = callback;
            register_node(effect, (s32)draw_linked_sprites_clipped);
            angle = effect_index << 8;
            position = ((S_80024D90_0 *)effect)->unk_08;
            value = origin->unk_02 + (func_80064584(angle) >> 7);
            position->unk_02 = value;
            value = origin->unk_06 + (func_800644B8(angle) >> 7);
            position->unk_06 = value;
            position->unk_0A =
                (s16)(origin->unk_0A - 0x100);
            component = ((S_80024D90_0 *)effect)->unk_0C;
            component->scale_x = 0x800;
            component->scale_y = 0x1CCC;
            component->color.word = 0;
            func_8003DB94(component, D_80025854, 0);
            value = counter_page[0x57CC / 2];
            source_pos = (u8 *)effect + 0x20;
            component->angle_x = 0x400;
            component->angle_y = component_offset;
            ((S_80024D90_4 *)source_pos)->unk_24 = effect_index;
            ((S_80024D90_4 *)source_pos)->unk_14 = state_param;
            ((S_80024D90_4 *)source_pos)->unk_1E = (s16)(effect_index * 2);
            value += 1;
            counter_page[0x57CC / 2] = value;
        }
        effect_index += 1;
        component_offset += 0x100;
    } while (effect_index < 0x10);
    return effect;
}

