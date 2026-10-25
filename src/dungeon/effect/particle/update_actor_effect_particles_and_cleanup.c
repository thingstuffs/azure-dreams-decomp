/* Shaded particle drawing, accelerating return particles, and staged actor effect cleanup. */
#include "shared/sprite_frame_state.h"
#include "modules/dungeon_ovl_18f4800.h"
#include "shared/object_node.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "shared/dungeon_moving_views.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/slus_callbacks.h"

typedef struct DungeonState818D4800 {
    u8 pad0[0x8D0];
    u8 *next;
} DungeonState818D4800;

typedef struct Scratch818D4800 {
    u16 x;
    u16 y;
    u16 z;
    u8 pad06[0x12];
    u8 *next;
    u8 pad1C[4];
    u32 *ot;
    u8 pad24[0x6C];
    u32 unk90;
    u32 unk94;
    u8 pad98[0x28];
    u32 index;
} Scratch818D4800;

typedef struct PrimTag818D4800 {
    u32 addr : 24;
    u32 len : 8;
} PrimTag818D4800;

extern u32 RotTransPers(void *scratch, void *prim_output, void *scratch_90, void *scratch_94);
extern s32 GetTPage(s32 value0, s32 value1, s32 value2, s32 value3);
extern void SetDrawMode(void *prim, s32 value0, s32 value1, s32 draw_mode, s32 value2);

void (*const dungeon_18f4800_entry)(struct Actor33 *, struct Motion33 *, struct Render33 *) = update_actor_effect_particles_and_cleanup;
const PackedOffsets dungeon_18f4800_offsets = { {
    {16, 0}, {16, 16}, {0, 16}, {-16, 16},
    {-16, 0}, {-16, 0xFFF0}, {0, 0xFFF0}, {16, 0xFFF0}
} };

/* Queue a shaded tile and draw mode packet, then continue the object chain. */
int abs(int);
extern u8 D_80025100[16];
extern Packed12 actor_particle_images;
extern u8 current_spell_effect_variant[16];
extern s32 get_sprite_attachment_vector(void *, void *, s16 *, s32);
extern void unlink_node(void *);
extern s32 rand(void);
extern s32 check_adjacent_tile_height_clearance(u16, u16, s16, void *);
extern s32 try_trigger_target_record_effect(void *, s32, void *);
extern s32 generate_random_value(void);
extern void try_apply_threshold_effect_variant_b(void *entity, s16 chance, s16 effect_value);

/* Projects linked points and queues visible square particles with color scaled by each point's intensity. */
s32 draw_actor_effect_points(void *object_data, void *position_data)
{
    u8 *object = object_data;
    u8 *position = position_data;
    GameWork *state_slot = &g_game_work;
    DungeonState818D4800 *state =
        g_game_work.draw_buffer;
    Scratch818D4800 *scratch = (Scratch818D4800 *)0x1F800000;
    register u8 *prim;
    u8 *tile_prim;
    u32 draw_mode;
    void *next_object;
    u8 *packet_start;
    u8 *next_prim;

    packet_start = state->next;
    scratch->ot = (u32 *)((u8 *)state + 0xB0);
    scratch->next = packet_start;

    do {
        scratch->x = *(u16 *)(position + 2);
        tile_prim = scratch->next;
        scratch->y = *(u16 *)(position + 6);
        scratch->z = *(u16 *)(position + 0xA);
        scratch->next = tile_prim + 0xC;

        scratch->index = RotTransPers(scratch, tile_prim + 8,
            &scratch->unk90, &scratch->unk94);

        if (scratch->index < 0x1E0U) {
            *(u32 *)(tile_prim + 4) = *(u32 *)(object + 8);

            tile_prim[4] = (tile_prim[4] * *(s16 *)(object + 0x32)) / 0x100;
            tile_prim[5] = (tile_prim[5] * *(s16 *)(object + 0x32)) / 0x100;
            tile_prim[6] = (tile_prim[6] * *(s16 *)(object + 0x32)) / 0x100;

            tile_prim[3] = 2;
            tile_prim[7] = 0x6A;

            ((PrimTag818D4800 *)tile_prim)->addr =
                ((PrimTag818D4800 *)&scratch->ot[scratch->index])->addr;
            ((PrimTag818D4800 *)&scratch->ot[scratch->index])->addr = (u32)tile_prim;

            prim = scratch->next;
            next_prim = prim + 0xC;
            scratch->next = next_prim;
            draw_mode = GetTPage(0, 1, 0, 0);
            SetDrawMode(prim, 0, 0, draw_mode & 0xFFFF, 0);

            ((PrimTag818D4800 *)prim)->addr = ((PrimTag818D4800 *)&scratch->ot[scratch->index])->addr;
            prim = (u8 *)((u32)prim & 0x00FFFFFF);
            scratch->ot[scratch->index] = (scratch->ot[scratch->index] & 0xFF000000) | (u32)prim;
        }
        next_object = *(void **)(object - 8);
        if (next_object == 0) {
            break;
        }

        object = (u8 *)next_object + 0x20;
        position = *(u8 **)((u8 *)next_object + 8);
    } while (1);

    (((DungeonState818D4800 *)state_slot->draw_buffer))->next = scratch->next;
    return 0;
}

typedef struct S_818D4A94_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    s32 unk_04;
    s32 unk_08;
} S_818D4A94_0;   /* arg1 in func_80024294 */

typedef struct S_818D4A94_1_pre {
    u16 unk_00;
} S_818D4A94_1_pre;   /* the 0x2 bytes before arg0 in func_80024294, addressed as arg0[-1] */

typedef struct S_818D4A94_1 {
    u8 pad_00[0x32];
    u16 unk_32;
    s16 unk_34;
    u8 pad_36[0x6];
    s32 unk_3C;
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    s32 unk_4C;
    s32 unk_50;
} S_818D4A94_1;   /* arg0 in func_80024294 */

/* Advance position and velocity, and flag completion near the target or when the countdown expires. */
void accelerate_particle_toward_source(void *motion, void *position_data)
{
    S_818D4A94_0 *position = position_data;
    s32 updated_value;
    s32 countdown;

    position->unk_00.at00.v += ((S_818D4A94_1 *)motion)->unk_3C;
    position->unk_04 += ((S_818D4A94_1 *)motion)->unk_40;
    position->unk_08 += ((S_818D4A94_1 *)motion)->unk_44;
    ((S_818D4A94_1 *)motion)->unk_3C += ((S_818D4A94_1 *)motion)->unk_48;
    ((S_818D4A94_1 *)motion)->unk_40 += ((S_818D4A94_1 *)motion)->unk_4C;
    ((S_818D4A94_1 *)motion)->unk_44 += ((S_818D4A94_1 *)motion)->unk_50;
    updated_value = abs(((S_818D4A94_1 *)motion)->unk_34 - position->unk_00.at02.v);
    updated_value = updated_value < 0x10;
    D_80025118[0] = 1;
    if (updated_value) {
        ((S_818D4A94_1_pre *)motion)[-1].unk_00 |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }

    countdown = ((S_818D4A94_1 *)motion)->unk_32;
    countdown -= 8;
    ((S_818D4A94_1 *)motion)->unk_32 = countdown;
    countdown <<= 16;
    if (countdown <= 0) {
        ((S_818D4A94_1_pre *)motion)[-1].unk_00 |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

   /* ((Rec_D_800E3D7C *)arg0)->unk_08.at00_pv.v in func_80024394 */

typedef struct S_818D4B94_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
    u16 unk_34;
    u16 unk_36;
    u16 unk_38;
    u8 pad_3A[0xE];
    s32 unk_48;
    s32 unk_4C;
    s32 unk_50;
} S_818D4B94_1;

/* Creates an offset effect with velocity directed back toward the source position. */
void create_accelerating_return_particle(ObjectNodeHeader *source, s32 setting_14, s32 setting_08, s32 duration, s32 offset_x, s32 offset_y, s32 offset_z) {
    s32 signed_duration;
    s32 step_count;
    s32 delta_x;
    s32 velocity;
    S_818D4B94_1 *state;
    ObjectNodeHeader *effect;

    effect = allocate_list_node(0x211, &source->next);
    if (effect != NULL) {
        effect->update_callback = (void *)accelerate_particle_toward_source;
        (effect->position)->x.w.i = (s16) (((MovingPosition *)source->position)->x + offset_x);
        (effect->position)->y.w.i = (s16) (((MovingPosition *)source->position)->y + offset_y);
        (effect->position)->z.w.i = (s16) (((MovingPosition *)source->position)->z + offset_z);
        state = ((void *)effect) + 0x20;
        state->unk_34 = (u16) ((MovingPosition *)source->position)->x;
        state->unk_36 = (u16) ((MovingPosition *)source->position)->y;
        state->unk_38 = (u16) ((MovingPosition *)source->position)->z;
        signed_duration = (s16) duration;
        delta_x = -(offset_x << 16);
        step_count = signed_duration / 8;
        velocity = delta_x / step_count;
        if (velocity < 0) {
            velocity += 0xF;
            state->unk_48 = velocity >> 4;
        } else {
            state->unk_48 = velocity >> 4;
        }
        velocity = -(offset_y << 16) / step_count;
        if (velocity < 0) {
            velocity += 0xF;
            state->unk_4C = velocity >> 4;
        } else {
            state->unk_4C = velocity >> 4;
        }
        state->unk_50 = -(offset_z << 16) / step_count / 16;
        state->unk_14 = setting_14;
        state->unk_32 = duration;
        register_node(effect, draw_actor_effect_points, signed_duration);
        state->unk_08 = setting_08;
    }
}

typedef struct S_818D4D48_0 {
    u16 unk_00;
    u8 pad_02[0x2];
    u16 unk_04;
} S_818D4D48_0;   /* held_arg0 in func_80024548; pointer addresses record offset 0x2 */

typedef struct RenderFade33 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x4];
    u16 unk_1A;
} RenderFade33;   /* arg2 in func_80024548 */

/* Fades and rotates an effect, decrements its timer, and flags completion. */
void fade_and_rotate_timed_effect(void *record_data, s32 unused, RenderFade33 *effect)
{
    void *record_cursor = record_data;
    u16 old_angle;
    u16 ticks_left;
    u16 next_angle;

    ticks_left = ((S_818D4D48_0 *)((u8 *)record_cursor - 0x2))->unk_04;
    D_80025118[0] = 1;
    ((S_818D4D48_0 *)((u8 *)record_cursor - 0x2))->unk_04 = (u16)(ticks_left - 1);

    effect->unk_0C = (u8)((effect->unk_0C * 0xA) / 13);
    effect->unk_0D = (u8)((effect->unk_0D * 0xA) / 13);
    effect->unk_0E = (u8)((effect->unk_0E * 0xA) / 13);

    old_angle = effect->unk_1A;
    next_angle = old_angle + 0x300;
    effect->unk_1A = next_angle;

    if ((u32)(next_angle & 0xFFFF) >= 0x1001U) {
        effect->unk_1A = (u16)(old_angle - 0xD00);
    }

    if ((s16)((S_818D4D48_0 *)((u8 *)record_cursor - 0x2))->unk_04 <= 0) {
        ((S_818D4D48_0 *)((u8 *)record_cursor - 0x2))->unk_00 = (u16)(((S_818D4D48_0 *)((u8 *)record_cursor - 0x2))->unk_00 | 0x8000);
        object_flag_block.flags = (s32)(object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }

    if (effect->unk_14 & 0x8000) {
        ((S_818D4D48_0 *)((u8 *)record_cursor - 0x2))->unk_00 = (u16)(((S_818D4D48_0 *)((u8 *)record_cursor - 0x2))->unk_00 | 0x8000);
        object_flag_block.flags = (s32)(object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}

typedef union FixedWord {
    s32 word;
    struct {
        u16 lo;
        u16 hi;
    } half;
} FixedWord;

typedef struct Motion33 {
    FixedWord x;
    FixedWord y;
    FixedWord z;
    s32 dx;
    s32 dy;
    s32 dz;
} Motion33;

typedef struct AlignedOffsetPair {
    s16 x;
    u16 y;
} AlignedOffsetPair;

typedef struct Render33 {
    u8 pad00[6];
    s16 field06;
    void *image;
    u8 color0;
    u8 color1;
    u8 color2;
    u8 pad0F;
    u16 field10;
    u8 pad12[2];
    u16 flags;
    u8 pad16[4];
    u16 angle;
    u16 scale_x;
    u16 scale_y;
} Render33;

typedef struct Aux {
    u8 pad00[8];
    void *field08;
    u8 pad0C[8];
    u16 flags14;
    u8 pad16[14];
    u8 tile_x;
    u8 tile_y;
} Aux;

typedef struct Owner {
    u8 pad00[8];
    Motion33 *position;
    Aux *aux;
} Owner;

typedef struct Actor33 {
    EntityRec *entity;
    void *field04;
    u8 pad08;
    u8 field09;
    s16 state;
    u8 pad0C[0x6C];
    s16 target_y;
    u8 flags7A;
    s8 countdown;
    u8 pad7C[2];
    s16 direction;
    u8 pad80[2];
    u16 timer82;
    s16 timer84;
    u8 pad86[2];
    s16 step88;
    s16 color_step;
    u16 accel;
    u8 pad8E[6];
    Packed12 image_data;
    s8 target_x;
    s8 target_z;
} Actor33;

typedef struct Task {
    ObjectNodeHeader header;
    u8 pad20[2];
    s16 field22;
    u8 pad24[0x1C];
    Packed12 image_data;
} Task;

/* Updates the actor effect through movement, particle emission, fading, and cleanup. */
void update_actor_effect_particles_and_cleanup(Actor33 *actor, Motion33 *motion, Render33 *render)
{
    s16 position_delta[4];
    PackedOffsets offsets;
    EntityRec *entity;
    Owner *owner;
    Motion33 *owner_motion;
    s32 state;
    s32 particle_count;
    u16 timer;
    Motion33 *linked_pos;

    entity = actor->entity;
    offsets = dungeon_18f4800_offsets;
    timer = actor->timer82;
    state = actor->state;
    owner = (Owner *)((u8 *)entity - 0x20);
    owner_motion = owner->position;
    timer++;
    actor->timer82 = timer;
    switch (state) {
    case 0:
        *(u32 *)&render->color0 = 0x00808080;
        render->scale_y = 0x1000;
        render->scale_x = 0x1000;
        actor->image_data = actor_particle_images;
        render->image = &actor->image_data;
        {
            u32 direction_bits;
            direction_bits = (u16)entity->facing;
            D_80025118[0] = 1;
            actor->direction = (direction_bits >> 9) & 7;
            actor->state++;
        }
    case 1:
        if (get_sprite_attachment_vector(owner->aux->field08, owner->aux, position_delta, 0) == 0 &&
            !(owner->aux->flags14 & 0x8000)) {
            return;
        }
        {
            motion->x.half.hi = owner_motion->x.half.hi;
            motion->y.half.hi = owner_motion->y.half.hi;
            motion->z.half.hi = owner_motion->z.half.hi;
            if (!(owner->aux->flags14 & 0x8000)) {
                motion->x.half.hi += (u16)position_delta[0];
                motion->y.half.hi += (u16)position_delta[1];
                motion->z.half.hi = (motion->z.half.hi) + ((u16)position_delta[2]);
            } else {
                motion->z.half.hi -= 0x40;
            }
        }
        if (!(*(u16 *)actor->field04 & 0x80)) {
            return;
        }
        {
            void *callback_owner;
            callback_owner = (u8 *)actor - 0x20;
            if (!(actor->flags7A & 4)) {
                register_node(callback_owner, project_sprite_chain);
                render->field10 = 0x40;
                render->color2 = 0x80;
                render->color1 = 0x80;
                render->color0 = 0x80;
                render->scale_y = 0x800;
                render->scale_x = 0x800;
                render->flags |= 0xC;
                actor->flags7A |= 4;
            }
        }
        if (entity->target != 0) {
            linked_pos = *(Motion33 **)((u8 *)entity->target - 0x18);
            actor->target_y = linked_pos->z.half.hi - 0x40;
        } else {
            actor->target_y = (u16)entity->unk_88 - 0x50;
        }
        {
            Aux *aux;
            s32 distance;

            aux = *(Aux **)((u8 *)entity - 0x14);
            actor->target_x = aux->tile_x + dir_step_x[actor->direction];
            actor->target_z = aux->tile_y + dir_step_y[actor->direction];
            {
                s32 aux_coord;
                distance = entity->unk_72;
                aux_coord = aux->tile_x;
                if (distance == aux_coord) {
                    distance = entity->unk_73;
                    aux_coord = aux->tile_y;
                }
                distance -= aux_coord;
                if (distance < 0) {
                    distance = -distance;
                }
            }
            actor->countdown = distance * 4 - 3;
        }
        {
            AlignedOffsetPair *offset_base = (AlignedOffsetPair *)offsets.bytes;
            motion->dx = ((AlignedOffsetPair *)((u8 *)offset_base + (actor->direction << 2)))->x << 16;
            motion->dy = ((AlignedOffsetPair *)((u8 *)offset_base + (actor->direction << 2)))->y << 16;
        }
        motion->dz = ((actor->target_y << 16) - motion->z.word) / actor->countdown;
        actor->timer82 = 0;
        actor->state++;
        return;

    case 2:
        if ((check_adjacent_tile_height_clearance(motion->x.half.hi, motion->y.half.hi,
                           (s16)motion->z.half.hi, entity->target) << 16) != 0) {
            goto state1_cleanup;
        }
        {
            u16 angle;
            Task *task;
            angle = render->angle;
            render->angle = angle + 0x300;
            if ((u16)(angle + 0x300) >= 0x1001) {
                render->angle = angle - 0xD00;
            }
            task = allocate_flagged_object_node(0x212);
            if (task != 0) {
                ObjectPosition *task_motion;
                SpriteFrameState *task_render;
                task->field22 = 0x10;
                task->header.update_callback = (void *)fade_and_rotate_timed_effect;
                register_node(task, project_sprite_chain);
                task_render = task->header.sprite;
                task_render->tpage_abr = 0x40;
                task_render->flags |= 0xC;
                task_motion = task->header.position;
                task_motion->x.w.i = motion->x.half.hi;
                task_motion->y.w.i = motion->y.half.hi;
                task_motion->z.w.i = motion->z.half.hi;
                task_render = task->header.sprite;
                task_render->scale_y = 0x800;
                task_render->scale_x = 0x800;
                task_render->color.c.b = 0x78;
                task_render->color.c.g = 0x78;
                task_render->color.c.r = 0x78;
                task->image_data = actor_particle_images;
                task_render->source = &task->image_data;
            }
            actor->countdown--;
            if (actor->countdown <= 0) {
                if (entity->target != 0) {
                    s32 sound_id;
                    sound_id = 0x300;
                    linked_pos = *(Motion33 **)((u8 *)entity->target - 0x18);
                    motion->x.half.hi = linked_pos->x.half.hi;
                    motion->y.half.hi = linked_pos->y.half.hi;
                    motion->z.half.hi = actor->target_y;
                    render->image = D_80025100;
                    render->scale_y = 0x400;
                    render->scale_x = 0x400;
                    render->field10 = 0x40;
                    motion->z.word += 0x80000;
                    render->color0 = 0x20;
                    render->color1 = 0x20;
                    render->color2 = 0x20;
                    actor->step88 = 600;
                    actor->color_step = 2;
                    actor->accel = 400;
                    actor->timer84 = 0;
                    actor->state++;
                    render->field06 = 100;
                    play_sound_if_enabled(sound_id);
                    return;
                }
state1_cleanup:
                unlink_node((u8 *)actor - 0x20);
                actor->state = 6;
                actor->timer84 = 0;
                actor->timer82 = 0;
                return;
            }
            motion->x.word += motion->dx;
            motion->y.word += motion->dy;
            motion->z.word += motion->dz;
            return;
        }

    case 3:
        actor->timer84++;
        if (actor->timer84 < 5) {
            render->scale_y += 3000;
            render->scale_x = render->scale_y;
        }
        else if (render->scale_x >= 0x1001) {
            if (render->scale_x >= 0x2EE1) {
                actor->step88 = 700;
            }
            if (render->scale_x >= 0x2711) {
                actor->step88 = 500;
            } else if (render->scale_x >= 0x2001) {
                actor->step88 = 200;
            } else if (render->scale_x >= 0x1801) {
                actor->step88 = 120;
            } else if (render->scale_x >= 0x1001) {
                actor->step88 = 60;
            } else if (render->scale_x >= 0x801) {
                actor->step88 = 40;
            }
            render->scale_x -= actor->step88;
            render->scale_y -= actor->step88;
        }
        render->angle += actor->accel;
        actor->accel += 20;
        {
            u32 color = render->color0;
            if (color < 120) {
                if (color < 60) {
                    actor->color_step = 4;
                } else {
                    actor->color_step = 1;
                }
                render->color0 += (u8)actor->color_step;
                render->color1 += (u8)actor->color_step;
                render->color2 += (u8)actor->color_step;
            }
        }
        {
            s32 more_particles;
            s32 shade;
            s32 offset_x;
            s32 offset_y;
            s32 offset_z;
            particle_count = 0;
            if (actor->timer84 >= 81) {
                actor->timer84 = 0;
                actor->timer82 = 0;
                actor->state++;
            }
            do {
                particle_count++;
                shade = (rand() & 0xFF) | 0x80;
                offset_x = (s16)((rand() & 0x7F) - 0x40);
                offset_y = (s16)((rand() & 0x7F) - 0x40);
                offset_z = (s16)((rand() & 0x7F) - 0x40);
                create_accelerating_return_particle((u8 *)actor - 0x20, actor->direction, 0xC0C0C0,
                              shade, offset_x, offset_y, offset_z);
                more_particles = particle_count < 2;
                if (!more_particles) {
                    return;
                }
            } while (1);
        }

    case 4:
        {
            for (particle_count = 0; particle_count < 2; particle_count++) {
                s32 shade;
                s32 offset_x;
                s32 offset_y;
                s32 offset_z;
                shade = (rand() & 0xFF) | 0x80;
                offset_x = (s16)((rand() & 0x7F) - 0x40);
                offset_y = (s16)((rand() & 0x7F) - 0x40);
                offset_z = (s16)((rand() & 0x7F) - 0x40);
                create_accelerating_return_particle((u8 *)actor - 0x20, actor->direction, 0xC0C0C0,
                              shade, offset_x, offset_y, offset_z);
            }
        }

        render->angle += actor->accel;
        actor->timer84 += 2;
        if (actor->timer84 >= 61) {
            s32 effect_type;
            s32 room_id;
            actor->timer84 = 40;
            actor->state++;
            if (try_trigger_target_record_effect(entity->target, 4, entity) == 0) {
                s32 effect_kind;
                effect_kind = (generate_random_value() & 3) + 4;
                effect_type = (actor->field09 >> 2) + effect_kind;
                room_id = (current_spell_effect_variant[0] == 0xFF) ? 0xFF : 0x10;
                try_apply_threshold_effect_variant_b(entity->target, room_id, effect_type);
                return;
            }
        }
        return;

    case 5:
        if (render->scale_x >= 51) {
            render->scale_x -= actor->step88 * 2;
            render->scale_y -= actor->step88 * 2;
        }
        render->angle += actor->accel;
        if (render->color0 >= 7) {
            render->color0 -= 4;
            render->color1 -= 4;
            render->color2 -= 4;
        }
        actor->timer84 -= 2;
        if (actor->timer84 <= 0) {
            actor->timer84 = 0;
            actor->timer82 = 0;
            actor->state++;
            return;
        }
        return;

    case 6:
        {
            s32 old_timer;
            old_timer = actor->timer82;
            actor->timer82 = old_timer + 1;
            if ((s16)(old_timer + 1) >= 21) {
                s32 active_flag;
                active_flag = D_80025118[0];
                actor->timer82 = old_timer;
                if (active_flag == 0) {
                    g_dungeon_status.active_actor = 0;
                    ((ObjectNodeHeader *)((u8 *)actor - 0x20) )->flags|= NODE_REMOVE;
                    object_flag_block.flags |= OBJECT_REMOVE_PENDING;
                    return;
                }
                D_80025118[0] = 0;
            }
        }
    }
}
