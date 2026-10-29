#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "sdk/libc.h"
#include "slus.h"
#include "town/minigame/effect.h"
#include "town/scene/object.h"

extern u8 tako_target_timing_table[];
extern u8 tako_minigame_sprites[16];
extern u8 D_800F79E8[16];

extern void create_tako_projectile(void *, s32, s32);
extern void create_timed_sound(s16 value);

typedef struct B {
    u8 pad0[0x10];
    s16 field10;
    u8 pad12[0x18 - 0x12];
    s16 field18;
    u16 field1a;
} B;

typedef struct A {
    B *unk0;
    u8 pad4[0x50 - 0x04];
    s16 state;
    u16 timer;
    u8 pad54[2];
    s16 field56;
    u16 flags;
} A;

typedef struct C {
    s32 w0;
    s32 w4;
    s32 w8;
    u8 pad0c[0x14 - 0x0c];
    s32 w20;
} C;

typedef struct D {
    void *unk0;
    u8 pad4[0x0c - 0x04];
    union { u8 b; s32 w; } f0c;
    u8 pad10[0x14 - 0x10];
    u16 h14;
} D;

typedef struct Local {
    void *p;
    s32 a;
    s32 b;
    s16 c;
    u16 d;
    s16 e;
} Local;

/* Updates entity animation, vertical motion, particles, and timed removal. */
void update_tako_target(A *entity, C *motion, SpriteFrameState *sprite) {
    B *cell = entity->unk0;
    s32 cell_flags;
    s32 state;
    s32 particles_left;
    s32 random_value;
    s32 particle_x;

    if (entity->flags & 2) {
        if (sprite->color.c.r) {
            sprite->color.word += 0xfffefeff;
        }
    }

    cell_flags = cell->field1a;
    cell->field1a = cell_flags | 2;
    if (entity->flags & 1) {
        cell->field1a = cell_flags | 6;
    }

    advance_sprite_animation_and_textures(sprite);
    if (entity->flags & 4) {
        if (sprite->unk_00 == (void *)tako_minigame_sprites) {
            select_record_entry_and_value(sprite, D_800F79E8, 0);
        }
    }
    if (sprite->flags & 0x6000) {
        select_record_entry_and_value(sprite, tako_minigame_sprites, 0);
    }

    state = entity->state;
    switch (state) {

    case 0:
        if (motion->w8 > 0) {
            motion->w8 += motion->w20;
            for (particles_left = 3; particles_left >= 0; particles_left--) {
                random_value = rand();
                particle_x = motion->w0;
                particle_x += ((random_value & 0xff) - 128) << 14;
                random_value = rand();
                create_tinted_animated_particle(0x808080, particle_x, motion->w4 + 0x80000, (random_value & 0xf) << 16);
            }
            break;
        }
        motion->w8 = 0;
        motion->w20 = 0;
        entity->state = 1;
        break;

    case 1:
        if (cell->field1a & 1) {
            Local effect;
            u8 *effect_entry = tako_target_timing_table + cell->field18 * 400 + cell->field10 * 40 + (entity->field56 * 12 + 4);
            effect.d = *(u16 *)(effect_entry + 8);
            effect.a = *(s32 *)(effect_entry + 0);
            effect.b = *(s32 *)(effect_entry + 4);
            effect.c = 0;
            effect.e = 0;
            effect.p = entity;
            create_tako_projectile(&effect, motion->w4, 0);
        }
        break;

    case 2:
    {
        s32 timer_left = entity->timer - 1;
        entity->timer = timer_left;
        if ((s16)timer_left <= 0) {
            if (entity->field56 == 0) {
                create_timed_sound(90);
            }
            motion->w20 = 0x40000;
            entity->state = 3;
        }
    }
        break;

    case 3:
        if (motion->w8 <= 0x7fffff) {
            {
                s32 height = motion->w8 + motion->w20;
                motion->w8 = height;
                if (height <= 0x3fffff) {
                    for (particles_left = 3; particles_left >= 0; particles_left--) {
                        random_value = rand();
                        particle_x = random_value & 0xff;
                        particle_x -= 128;
                        particle_x <<= 14;
                        particle_x += 0x5600000;
                        random_value = rand();
                        create_tinted_animated_particle(0x808080, particle_x, motion->w4 + 0x80000, (random_value & 0xf) << 16);
                    }
                }
            }
            break;
        }
        entity->timer = 2;
        entity->state = 4;
        break;

    case 4:
    {
        s32 timer_left = entity->timer - 1;
        entity->timer = timer_left;
        if ((s16)timer_left <= 0) {
            unlink_scene_list_node((u8 *)entity + 4);
            *(u16 *)((u8 *)entity - 2) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
    }

    }
    entity->flags &= ~2;
}
