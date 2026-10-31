#include "shared/object_node_flags.h"
#include "shared/audio_commands.h"
/* Ground-following attack particles, delayed fades, and target impact bursts. */
#include "modules/dungeon_ovl_1870800.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/dungeon_moving_views.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/actor.h"
#include "dungeon/level.h"


extern int abs(int);

extern void *allocate_list_node(s32, void *);
extern s32 rand(void);
extern void apply_attack_power_and_element_effects();
extern s32 play_sound_if_enabled(s32);

extern u8 countdown_sprite_entries[];
extern u8 directional_effect_entries[];

typedef struct S_81850800_0 {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x1];
    u8 unk_09;
    union {
        s16 unk_0A_s16;
        u16 unk_0A_u16;
    } unk_0A;
    u8 pad_0C[0x44];
    union {
        s16 unk_50_s16;
        u16 unk_50_u16;
    } unk_50;
    union {
        s16 unk_52_s16;
        u16 unk_52_u16;
    } unk_52;
} S_81850800_0;

typedef struct S_81850800_1 {
    u8 pad_00[0x2A];
    union {
        s16 unk_2A_s16;
        u16 unk_2A_u16;
    } unk_2A;
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0xE];
    s8 unk_72;
    s8 unk_73;
} S_81850800_1;

typedef struct S_81850800_2 {
    void * unk_00;
} S_81850800_2;

typedef struct S_81850800_5 {
    union {
        s32 unk_00_s32;
        struct {
            u8 pad_00[0x2];
            s16 unk_02_s16;
        } unk_02_view_s16;
    } unk_00;
    union {
        s32 unk_04_s32;
        struct {
            u8 pad_04[0x2];
            s16 unk_06_s16;
        } unk_06_view_s16;
    } unk_04;
    union {
        s32 unk_08_s32;
        struct {
            u8 pad_08[0x2];
            s16 unk_0A_s16;
        } unk_0A_view_s16;
    } unk_08;
    s32 unk_0C;
    s32 unk_10;
    union {
        s32 unk_14_s32;
        u16 unk_14_u16;
    } unk_14;
    u8 pad_18[0xC];
    u8 unk_24;
    u8 unk_25;
} S_81850800_5;

typedef struct S_81850800_7 {
    union {
        s32 unk_00_s32;
        struct {
            u8 pad_00[0x2];
            u16 unk_02_u16;
        } unk_02_view_u16;
    } unk_00;
    union {
        s32 unk_04_s32;
        struct {
            u8 pad_04[0x2];
            u16 unk_06_u16;
        } unk_06_view_u16;
    } unk_04;
    union {
        s32 unk_08_s32;
        struct {
            u8 pad_08[0x2];
            s16 unk_0A_s16;
        } unk_0A_view_s16;
        struct {
            u8 pad_08[0x2];
            u16 unk_0A_u16;
        } unk_0A_view_u16;
    } unk_08;
    union {
        s32 unk_0C_s32;
        struct {
            u8 pad_0C[0x2];
            u16 unk_0E_u16;
        } unk_0E_view_u16;
    } unk_0C;
    union {
        s32 unk_10_s32;
        struct {
            u8 pad_10[0x2];
            u16 unk_12_u16;
        } unk_12_view_u16;
    } unk_10;
} S_81850800_7;

typedef struct S_81850800_8 {
    void * unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    union {
        s32 unk_08_s32;
        void * unk_08_ptr;
    } unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_81850800_8;

typedef struct S_81850800_9 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void (*unk_10)(void *, void *, void *);
    u8 pad_14[0xC];
    void * unk_20;
} S_81850800_9;

typedef struct S_81850800_10 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_81850800_10;

typedef struct S_81850800_11 {
    u8 pad_00[0x48];
    union {
        s16 unk_48_s16;
        u16 unk_48_u16;
    } unk_48;
    s16 unk_4A;
    s16 unk_4C;
    s16 unk_4E;
} S_81850800_11;

void decrement_flagged_item_parameters(S_81850800_0 *owner, S_81850800_7 *motion, SpriteFlagsView *sprite);
void (*const dungeon_1870800_entry)(S_81850800_0 *, S_81850800_7 *, SpriteFlagsView *) = decrement_flagged_item_parameters;

/* Advance a directional effect, spawn its particles, and apply its target impact. */
extern s32 register_node(ObjectNodeHeader *, void *);
extern s32 project_sprite_chain(void *, s32, struct SpriteFrameState *, s32);
extern void advance_sprite_animation_and_textures(void *);
extern s32 rand(void);

/* Emits a ground-following particle trail and target burst, applies the attack, and waits for effect
   cleanup. */
void decrement_flagged_item_parameters(S_81850800_0 *owner, S_81850800_7 *motion, SpriteFlagsView *sprite)
{
    s32 step_x;
    s32 step_y;
    s32 state;
    s32 mode;
    void (*effect_flags)(void *, void *, void *);
    s32 tiles_ahead;
    s32 off_x;
    s32 off_y;
    s32 facing_shift;
    s32 dx;
    u32 magnitude;
    s32 tile_x;
    s32 tile_y;
    s32 color;
    s32 copy_value;
    s32 spawn_color;
    u32 tile_step_x;
    s32 tile_step_y;
    s32 pixel_step_x;
    u16 timer;
    u16 flags;
    u32 base_y;
    s16 ground_height;
    S_81850800_1 *caster_data;
    MovingTile *caster_sprite;
    SpriteFrameState *work;
    S_81850800_9 *obj;
    S_81850800_1 *target;
    union { S_81850800_11 * pointer; s32 value; } effect_data;
    S_81850800_5 *position;
    ObjectNodeHeader *spawn_cb;
    S_81850800_10 *particle_anim;
    u8 *step_x_table;
    u8 *step_y_table;
    s32 pix_x;
    s32 origin_y;
    u8 origin_x;
    s32 pix_y;
    caster_data = owner->unk_00;
    step_x_table = (u8 *)((s8 *)dir_step_x);
    magnitude = (u16)caster_data->unk_2A.unk_2A_u16;
    facing_shift = magnitude >> 8;
    caster_sprite = ((S_81850800_2 *)((u8 *)caster_data - 0x14))->unk_00;
    base_y = facing_shift & 0xE;
    step_x_table = (base_y + (u8 *)step_x_table);
    step_x = *(s16 *)step_x_table;
    step_y_table = (u8 *)((s8 *)dir_step_y);
    base_y = (s32)step_y_table + base_y;
    timer = owner->unk_50.unk_50_u16 - 1;
    base_y = *(s16 *)base_y;
    step_y = base_y;
    work = (S_81850800_8 *)((u8 *)caster_data - 0x20);
    mode = owner->unk_0A.unk_0A_s16;
    owner->unk_50.unk_50_u16 = timer;

    switch (mode) {
    case 0:
        if ((((u16 *)owner->unk_04)[0] & 0x80) == 0) {
            return;
        }
        target = caster_data->unk_60;
        tiles_ahead = 0;
        if (target == 0) {
            s32 min_height;
            s32 probe_y;

            off_y = 0;
            off_x = 0;
            do {
                min_height = -0x400;
                dx = ((caster_sprite->tile_x + off_x) << 6) + 0x20;
                facing_shift = ((caster_sprite->tile_y + off_y) << 6) + 0x20;
                obj = (S_81850800_9 *)((u16)dx);
                probe_y = (u16)facing_shift;
                ground_height = sample_terrain_surface_height((s32)obj, probe_y, min_height);
                if ((s16)check_enabled_neighbor_height((s32)obj, probe_y, ground_height, caster_data->unk_2A.unk_2A_s16,
                                       caster_data->unk_60) != 0) {
                    break;
                }
                tiles_ahead++;
                off_y += step_y;
                off_x += step_x;
                if (tiles_ahead >= 2) {
                    break;
                }
            } while (1);
            dx = step_x * tiles_ahead;
            facing_shift = step_y * tiles_ahead;
        } else {
            position = ((S_81850800_2 *)((u8 *)target - 0x14))->unk_00;
            copy_value = caster_sprite->tile_x;
            base_y = position->unk_24;
            facing_shift = position->unk_25;
            dx = base_y - copy_value;
            base_y = caster_sprite->tile_y;
            facing_shift -= base_y;
            if ((position->unk_14.unk_14_u16 & 0x8000) &&
                (sprite->flags & 0x8000)) {
                owner->unk_0A.unk_0A_s16 = 2;
                owner->unk_50.unk_50_u16 = 0;
                return;
            }
        }
        effect_data.value = abs(dx);
        state = abs(facing_shift);
        if (effect_data.value < state) {
            effect_data.value = state;
        }
        magnitude = effect_data.value * 4;
        owner->unk_50.unk_50_u16 = magnitude;
        switch (effect_data.value) {
        case 0:
            dx = 0;
            facing_shift = 2;
            owner->unk_50.unk_50_u16 = 0;
            break;
        case 1:
            dx = 0;
            facing_shift = 3;
            state = facing_shift;
            if (caster_data->unk_60 != 0) {
                state = 1;
            }
            owner->unk_50.unk_50_u16 = state;
            break;
        default:
            dx = 1;
            facing_shift = 0;
            owner->unk_50.unk_50_u16 -= 2;
            break;
        }
        tile_step_x = step_x * dx;
        state = facing_shift << 4;
        pixel_step_x = step_x * state;
        tile_step_y = step_y * dx;
        origin_x = caster_sprite->tile_x;
        pix_x = (origin_x + tile_step_x) << 6;
        tile_step_x = step_y * state;
        state = pixel_step_x + 0x20;
        pix_x += state;
        motion->unk_00.unk_02_view_u16.unk_02_u16 = pix_x;
        origin_y = caster_sprite->tile_y;
        motion->unk_0C.unk_0E_view_u16.unk_0E_u16 = step_x << 4;
        motion->unk_10.unk_12_view_u16.unk_12_u16 = step_y << 4;
        pix_y = (origin_y + tile_step_y) << 6;
        state = tile_step_x + 0x20;
        pix_y += state;
        motion->unk_04.unk_06_view_u16.unk_06_u16 = pix_y;
        play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
        owner->unk_0A.unk_0A_u16++;
        return;

    case 1:
        ground_height = sample_terrain_surface_height(motion->unk_00.unk_02_view_u16.unk_02_u16,
                            motion->unk_04.unk_06_view_u16.unk_06_u16,
                            (s16)(((S_81850800_7 *)work->source)->unk_08.unk_0A_view_u16.unk_0A_u16 -
                                  0x30));
        motion->unk_08.unk_0A_view_s16.unk_0A_s16 = ground_height;
        if (ground_height >= 0x200) {
            motion->unk_08.unk_0A_view_u16.unk_0A_u16 =
                ((S_81850800_7 *)work->source)->unk_08.unk_0A_view_u16.unk_0A_u16;
        }
        spawn_cb = &scene_object_list_anchor;
        obj = allocate_list_node(0x112, spawn_cb);
        if (obj != 0) {
            obj->unk_10 = delay_and_fade_particle;
            position = obj->unk_08;
            work = obj->unk_0C;
            copy_value = motion->unk_00.unk_00_s32;
            position->unk_00.unk_00_s32 = copy_value;
            position = obj->unk_08;
            copy_value = motion->unk_04.unk_04_s32;
            effect_data.pointer = (S_81850800_11 *)((u8 *)obj + 0x20);
            position->unk_04.unk_04_s32 = copy_value;
            position = obj->unk_08;
            copy_value = motion->unk_08.unk_08_s32;
            spawn_color = 0xC00000;
            position->unk_08.unk_08_s32 = copy_value;
            work->scale_y = 0x1000;
            work->scale_x = 0x1000;
            work->tpage_abr = 0x60;
            work->flags |= 0xC;
            work->unk_00 = countdown_sprite_entries;
            copy_value = ((S_81850800_10 *)countdown_sprite_entries)->unk_04;
            spawn_color |= 0x8080;
            work->unk_04 = 0;
            work->frame_ticks = 0;
            work->color.word = spawn_color;
            work->source = copy_value;
            obj->unk_20 = owner;
            effect_data.pointer->unk_48.unk_48_s16 = rand() & 3;
            effect_data.pointer->unk_4E = (rand() & 3) + 8;
            effect_data.pointer->unk_4A = (rand() & 7) + 0xC;
            effect_data.pointer->unk_4C = 0;
        }
        if (owner->unk_50.unk_50_s16 <= 0) {
            if (caster_data->unk_60 != 0) {
                owner->unk_50.unk_50_u16 = 4;
                owner->unk_0A.unk_0A_u16++;
                tile_x = caster_data->unk_72;
                motion->unk_00.unk_02_view_u16.unk_02_u16 = (tile_x << 6) + 0x20;
                tile_y = caster_data->unk_73;
                motion->unk_10.unk_10_s32 = 0;
                motion->unk_0C.unk_0C_s32 = 0;
                motion->unk_04.unk_06_view_u16.unk_06_u16 = (tile_y << 6) + 0x20;
                obj = allocate_list_node(0x112, spawn_cb);
                if (obj != 0) {
                    obj->unk_10 = delay_and_fade_particle;
                    position = obj->unk_08;
                    work = obj->unk_0C;
                    copy_value = motion->unk_00.unk_00_s32;
                    position->unk_00.unk_00_s32 = copy_value;
                    position = obj->unk_08;
                    copy_value = motion->unk_04.unk_04_s32;
                    effect_data.pointer = (S_81850800_11 *)((u8 *)obj + 0x20);
                    position->unk_04.unk_04_s32 = copy_value;
                    position = obj->unk_08;
                    copy_value = motion->unk_08.unk_08_s32;
                    spawn_color = 0x600000;
                    position->unk_08.unk_08_s32 = copy_value;
                    work->scale_x = 0x2000;
                    work->scale_y = 0x2800;
                    work->tpage_abr = 0x20;
                    work->flags |= 0xC;
                    work->unk_00 = countdown_sprite_entries;
                    copy_value = ((S_81850800_10 *)countdown_sprite_entries)->unk_04;
                    spawn_color |= 0x6060;
                    work->unk_04 = 0;
                    work->frame_ticks = 0;
                    work->color.word = spawn_color;
                    work->source = copy_value;
                    obj->unk_20 = owner;
                    timer = owner->unk_50.unk_50_u16;
                    effect_data.pointer->unk_4E = 8;
                    effect_data.pointer->unk_4A = 8;
                    effect_data.pointer->unk_4C = 0;
                    effect_data.pointer->unk_48.unk_48_u16 = timer;
                }
                dx = 0x3C;
                effect_flags = delay_and_fade_particle;
                particle_anim = (S_81850800_10 *)directional_effect_entries;
                do {
                    obj = allocate_list_node(0x312, &scene_object_list_anchor.next);
                    if (obj != 0) {
                        work = obj->unk_0C;
                        obj->unk_10 = effect_flags;
                        ((S_81850800_5 *)obj->unk_08)->unk_00.unk_02_view_s16.unk_02_s16 =
                            motion->unk_00.unk_02_view_u16.unk_02_u16 + (rand() & 0x3F) - 0x20;
                        ((S_81850800_5 *)obj->unk_08)->unk_04.unk_06_view_s16.unk_06_s16 =
                            motion->unk_04.unk_06_view_u16.unk_06_u16 + (rand() & 0x3F) - 0x20;
                        ((S_81850800_5 *)obj->unk_08)->unk_08.unk_0A_view_s16.unk_0A_s16 =
                            motion->unk_08.unk_0A_view_u16.unk_0A_u16 - (rand() & 0x1F);
                        color = 0x800000;
                        work->scale_y = 0x800;
                        work->scale_x = 0x800;
                        work->tpage_abr = 0x60;
                        work->unk_00 = particle_anim;
                        work->flags |= 0xC;
                        copy_value = particle_anim->unk_04;
                        color |= 0x8080;
                        work->unk_04 = 0;
                        work->frame_ticks = 0;
                        work->color.word = color;
                        work->source = copy_value;
                        ((S_81850800_5 *)obj->unk_08)->unk_0C =
                            step_x * (rand() << 3);
                        effect_data.pointer = (S_81850800_11 *)((u8 *)obj + 0x20);
                        ((S_81850800_5 *)obj->unk_08)->unk_10 =
                            step_y * (rand() << 3);
                        ((S_81850800_5 *)obj->unk_08)->unk_14.unk_14_s32 =
                            0xFFF7FFFF - rand();
                        obj->unk_20 = owner;
                        effect_data.pointer->unk_48.unk_48_s16 = 2;
                        effect_data.pointer->unk_4E = (rand() & 7) + 8;
                        effect_data.pointer->unk_4A = 0x10;
                        effect_data.pointer->unk_4C = 0;
                    }
                    dx--;
                } while (dx >= 0);
            } else {
                owner->unk_50.unk_50_u16 = 4;
                owner->unk_0A.unk_0A_s16 = 3;
            }
        }
        motion->unk_00.unk_00_s32 += motion->unk_0C.unk_0C_s32;
        motion->unk_04.unk_04_s32 += motion->unk_10.unk_10_s32;
        return;

    case 2:
        if ((s16)timer > 0) {
            return;
        }
        if (caster_data->unk_60 != 0) {
            apply_attack_power_and_element_effects(caster_data->unk_60, 0x13,
                          owner->unk_09, 2,
                          caster_data->unk_2A.unk_2A_s16, caster_data, mode);
        }
        owner->unk_50.unk_50_u16 = 0x10;
        owner->unk_0A.unk_0A_u16++;
        return;

    case 3:
        flags = owner->unk_52.unk_52_u16;
        if (owner->unk_52.unk_52_s16 & 0x8000) {
            owner->unk_52.unk_52_u16 = flags & 0x7FFF;
            return;
        }
        if ((s16)timer > 0) {
            return;
        }
        g_dungeon_status.active_actor = 0;
        (*(u16 *)((u8 *)owner - 2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    default:
        return;
    }
}

typedef struct ParticleOwner {
    u8 pad_00[0x52];
    u16 flags;
} ParticleOwner;

typedef struct ParticleEffect {
    ParticleOwner *owner;
    u8 pad_04[0x44];
    s16 delay;
    s16 fade_step;
    s16 state;
    s16 lifetime;
} ParticleEffect;

typedef struct ParticleMotion {
    s32 x, y, z;
    s32 vx, vy, vz;
} ParticleMotion;

typedef struct ParticlePrimitive {
    u8 pad_00[4];
    u8 frame_x, frame_y;
    u8 pad_06[6];
    u8 red, green, blue;
    u8 pad_0F[5];
    u16 flags;
} ParticlePrimitive;

struct SpriteFrameState;

/* Delay a spawned particle, then integrate its motion and fade until deletion.
 * Retail: [file 0x1870FDC,0x1871178), [RAM 0x800247DC,0x80024978).
 */
void delay_and_fade_particle(void *effect, void *position, void *primitive)
{
    ParticleEffect *p = effect;
    ParticleMotion *motion = position;
    SpriteFrameState *sprite= primitive;

    p->owner->flags |= 0x8000;
    switch (p->state) {
    case 0:
        if (--p->delay <= 0) {
            register_node((ObjectNodeHeader *)p - 1, project_sprite_chain);
            p->state++;
        }
        break;
    case 1:
        advance_sprite_animation_and_textures(sprite);
        if (sprite->flags & 0x6000) {
            sprite->unk_04 = 0;
            sprite->frame_ticks = 0;
        }
        motion->x += motion->vx;
        motion->y += motion->vy;
        if (motion->vz != 0) {
            motion->z += motion->vz;
            motion->vz += 0x8000 + (rand() & 0xFFF);
        }
        if (--p->lifetime <= 0) {
            if (sprite->color.c.r >= p->fade_step) {
                sprite->color.c.r = sprite->color.c.g = sprite->color.c.b -= p->fade_step;
            } else {
                ((ObjectNodeHeader *)p - 1)->flags |= NODE_REMOVE; /* header precedes the record */
                object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            }
        }
        break;
    }
}
