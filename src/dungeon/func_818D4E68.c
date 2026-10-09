#include "modules/dungeon_ovl_18f4800.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"

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
    u8 pad00[8];
    Motion33 *position;
    Render33 *render;
    void (*update)(void *, s32, struct RenderFade33 *);
    u8 pad14[0x0E];
    s16 field22;
    u8 pad24[0x1C];
    Packed12 image_data;
} Task;


extern u8 D_80025100[16];
extern Packed12 D_8002510C;
extern u8 D_800E3D68[16];

extern s32 func_8003DF74(void *, void *, s16 *, s32);
extern Task *func_8003FC64(s32);
extern void func_80044A50(void *);
extern s32 func_80069EF8(void);
extern s32 func_800A4778(u16, u16, s16, void *);

extern s32 func_8009D218(void *, s32, void *);
extern s32 func_800A6D30(void);
extern void func_800C8B84(void *entity, s16 chance, s16 effect_value);

#include "shared/slus_callbacks.h"


/* Updates the actor effect through movement, particle emission, fading, and cleanup. */
void func_80024668(Actor33 *actor, Motion33 *motion, Render33 *render)
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
        actor->image_data = D_8002510C;
        render->image = &actor->image_data;
        {
            u32 direction_bits;
            direction_bits = (u16)entity->facing;
            D_80025118[0] = 1;
            actor->direction = (direction_bits >> 9) & 7;
            actor->state++;
        }
    case 1:
        if (func_8003DF74(owner->aux->field08, owner->aux, position_delta, 0) == 0 &&
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
                func_8004491C(callback_owner, (s32)func_80045340);
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
            actor->target_x = aux->tile_x + dirStepX[actor->direction];
            actor->target_z = aux->tile_y + dirStepY[actor->direction];
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
        if ((func_800A4778(motion->x.half.hi, motion->y.half.hi,
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
            task = func_8003FC64(0x212);
            if (task != 0) {
                Motion33 *task_motion;
                Render33 *task_render;
                task->field22 = 0x10;
                task->update = func_80024548;
                func_8004491C(task, (s32)func_80045340);
                task_render = task->render;
                task_render->field10 = 0x40;
                task_render->flags |= 0xC;
                task_motion = task->position;
                task_motion->x.half.hi = motion->x.half.hi;
                task_motion->y.half.hi = motion->y.half.hi;
                task_motion->z.half.hi = motion->z.half.hi;
                task_render = task->render;
                task_render->scale_y = 0x800;
                task_render->scale_x = 0x800;
                task_render->color2 = 0x78;
                task_render->color1 = 0x78;
                task_render->color0 = 0x78;
                task->image_data = D_8002510C;
                task_render->image = &task->image_data;
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
                    func_800A56E0(sound_id);
                    return;
                }
state1_cleanup:
                func_80044A50((u8 *)actor - 0x20);
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
                shade = (func_80069EF8() & 0xFF) | 0x80;
                offset_x = (s16)((func_80069EF8() & 0x7F) - 0x40);
                offset_y = (s16)((func_80069EF8() & 0x7F) - 0x40);
                offset_z = (s16)((func_80069EF8() & 0x7F) - 0x40);
                func_80024394((u8 *)actor - 0x20, actor->direction, 0xC0C0C0,
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
                shade = (func_80069EF8() & 0xFF) | 0x80;
                offset_x = (s16)((func_80069EF8() & 0x7F) - 0x40);
                offset_y = (s16)((func_80069EF8() & 0x7F) - 0x40);
                offset_z = (s16)((func_80069EF8() & 0x7F) - 0x40);
                func_80024394((u8 *)actor - 0x20, actor->direction, 0xC0C0C0,
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
            if (func_8009D218(entity->target, 4, entity) == 0) {
                s32 effect_kind;
                effect_kind = (func_800A6D30() & 3) + 4;
                effect_type = (actor->field09 >> 2) + effect_kind;
                room_id = (D_800E3D68[0] == 0xFF) ? 0xFF : 0x10;
                func_800C8B84(entity->target, room_id, effect_type);
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
                    dungeonStatus.unk_0C = 0;
                    *(u16 *)((u8 *)actor - 2) |= 0x8000;
                    objectFlagBlock.flags |= 0x8000;
                    return;
                }
                D_80025118[0] = 0;
            }
        }
    }
}
