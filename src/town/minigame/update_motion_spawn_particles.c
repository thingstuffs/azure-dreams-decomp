#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"
#include "shared/dungeon_effect_views.h"
#include "shared/vector.h"

typedef struct Motion {
    s32 x;
    s32 y;
    s32 z;
    s32 dx;
    s32 unk10;
    s32 dz;
} Motion;

typedef struct Sprite {
    u8 pad0[0xC];
    u32 color;
    s16 unk10;
    u8 pad12[2];
    u16 flags;
    u8 pad16[6];
    s16 scale_y;
    s16 scale_x;
} Sprite;

typedef struct Object {
    u8 pad0[8];
    IntVector3 *position;
    Sprite *sprite;
    void (*callback)(void);
} Object;

extern void select_record_entry_and_value(void *state, void *entries, short index);
#include "engine/node.h"
extern void SD_Call(s32, s32);
extern void DrawSync(s32);
extern void LoadImage(void *, void *);
extern void StoreImage(void *, void *);
extern s32 rand(void);
extern void set_linked_object_and_global_flags(void);

extern u8 pool_palette_rect_2[];
extern u8 pool_palette_rect[];
extern u8 map_animation_sprite_entries[];
extern u16 pool_palette_backup[];

/* Update motion, spawn particles, and flash then restore the palette. */
void update_motion_spawn_particles(EffectPhaseTimer16 *state, Motion *motion, u8 *sprite_data)
{
    u16 colors[16];
    s32 index;
    s32 red;
    s32 green;
    s32 blue;
    s32 gravity;
    s16 timer;
    u16 color;
    u16 *source_color;
    u16 *original_palette;
    ObjectNodeHeader *particle;
    SpriteFrameState *sprite;

    gravity = 0x38000;
    state->timer--;
    motion->x += motion->dx;
    motion->z += motion->dz;
    motion->dz += gravity;

    switch (state->state) {
    case 0:
        if (state->timer > 0) {
            break;
        }

        SD_Call(0x519, gravity);
        index = 15;
        do {
            particle = allocate_flagged_object_node(0x136);
            if (particle != 0) {
                particle->update_callback = set_linked_object_and_global_flags;
                register_node(particle, project_sprite_chain);
                sprite = particle->sprite;
                (*(IntVector3 * *)&particle->position)->x = motion->x + ((rand() & 0x1FF) - 0x100) * 0x2000;
                (*(IntVector3 * *)&particle->position)->y = motion->y + ((rand() & 0x1FF) - 0x100) * 0x2000;
                (*(IntVector3 * *)&particle->position)->z = motion->z;
                sprite->tpage_abr = 0x60;
                sprite->scale_y = 0x1000;
                sprite->scale_x = 0x1000;
                sprite->flags |= 0xC;
                select_record_entry_and_value(sprite, map_animation_sprite_entries, 0);
                sprite->color.word = 0x606060;
            }
            index--;
        } while (index >= 0);
        state->timer = 8;
        state->state++;
        break;

    case 1:
        if (state->timer > 0) {
            break;
        }
        *(u16 *)(sprite_data + 0x14) |= 0x80;
        state->timer = 0x40;
        state->state++;
        break;

    case 2:
    {
        u16 *output_color;
        s32 channel_max;
        s32 color_bias;

        StoreImage(pool_palette_rect, colors);
        DrawSync(0);

        index = 15;
        channel_max = 0x1F;
        color_bias = -0x8000;
        output_color = &colors[15];
        do {
            color = *output_color;
            timer = state->timer;
            red = channel_max - (((channel_max - (color & 0x1F)) * timer) >> 6);
            green = channel_max - (((channel_max - ((s16)color >> 5 & 0x1F)) * timer) >> 6);
            blue = channel_max - (((channel_max - ((s16)color >> 10 & 0x1F)) * timer) >> 6);
            *output_color = (blue << 10) + ((green << 5) + color_bias) + red;
            index--;
            output_color--;
        } while (index >= 0);

        if (state->timer < 0x30) {
            index = 0;
            while (index < 0x10 - (state->timer >> 2)) {
                index++;
                red = (rand() % 3) * 8 + 0xF;
                green = (rand() % 3) * 8 + 0xF;
                blue = (rand() % 3) * 8 + 0xF;
                colors[rand() & 0xF] = (blue << 10) + ((green << 5) - 0x8000) + red;
            }
        }

        LoadImage(pool_palette_rect_2, colors);
        DrawSync(0);
        if (state->timer <= 0) {
            state->timer = 0x1E;
            state->state++;
        }
        break;
    }

    case 3:
        index = 15;
        do {
            red = (rand() % 3) * 8 + 0xF;
            green = (rand() % 3) * 8 + 0xF;
            blue = (rand() % 3) * 8 + 0xF;
            colors[index] = (blue << 10) + ((green << 5) - 0x8000) + red;
            index--;
        } while (index >= 0);
        LoadImage(pool_palette_rect_2, colors);
        DrawSync(0);
        if (state->timer <= 0) {
            state->timer = 0x20;
            state->state++;
        }
        break;

    case 4:
    {
        u16 *output_color;
        s32 channel_max;
        s32 color_bias;

        index = 15;
        channel_max = 0x1F;
        color_bias = -0x8000;
        output_color = &colors[15];
        original_palette = pool_palette_backup;
        source_color = original_palette + 15;
        do {
            color = *source_color;
            timer = state->timer;
            red = color & 0x1F;
            green = (color >> 5) & 0x1F;
            blue = (color >> 10) & 0x1F;
            red += ((channel_max - red) * timer) >> 5;
            green += ((channel_max - green) * timer) >> 5;
            blue += ((channel_max - blue) * timer) >> 5;
            *output_color = (blue << 10) + ((green << 5) + color_bias) + red;
            source_color--;
            output_color--;
            index--;
        } while (index >= 0);
        LoadImage(pool_palette_rect_2, colors);
        DrawSync(0);
        if (state->timer <= 0) {
            state->state++;
        }
        break;
    }

    case 5:
        LoadImage(pool_palette_rect_2, pool_palette_backup);
        DrawSync(0);
        *(u16 *)((u8 *)state - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
