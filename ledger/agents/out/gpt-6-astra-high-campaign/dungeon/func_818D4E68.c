#include "common.h"

typedef union FixedWord {
    s32 word;
    struct {
        u16 lo;
        u16 hi;
    } half;
} FixedWord;

typedef struct Motion {
    FixedWord x;
    FixedWord y;
    FixedWord z;
    s32 dx;
    s32 dy;
    s32 dz;
} Motion;

typedef struct Packed12 {
    u8 bytes[12];
} __attribute__((packed)) Packed12;

typedef struct Packed8 {
    u8 bytes[8];
} __attribute__((packed)) Packed8;

typedef struct OffsetPair {
    s16 x;
    u16 y;
} __attribute__((packed)) OffsetPair;

typedef union PackedOffsets {
    struct {
        Packed12 first;
        Packed12 second;
        Packed8 third;
    } copy;
    u8 bytes[32];
} __attribute__((packed)) PackedOffsets;

typedef struct AlignedOffsetPair {
    s16 x;
    u16 y;
} AlignedOffsetPair;

typedef struct Render {
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
} Render;

typedef struct Aux {
    u8 pad00[8];
    void *field08;
    u8 pad0C[8];
    u16 flags14;
    u8 pad16[14];
    u8 tile_x;
    u8 tile_y;
} Aux;

typedef struct Entity {
    u8 pad00[0x2A];
    u16 flags2A;
    u8 pad2C[0x34];
    void *link60;
    u8 pad64[0x0E];
    s8 tile_x72;
    s8 tile_y73;
    u8 pad74[0x14];
    u16 height88;
} Entity;

typedef struct Owner {
    u8 pad00[8];
    Motion *position;
    Aux *aux;
} Owner;

typedef struct Actor {
    Entity *entity;
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
} Actor;

typedef struct Task {
    u8 pad00[8];
    Motion *position;
    Render *render;
    void (*update)(void);
    u8 pad14[0x0E];
    s16 field22;
    u8 pad24[0x1C];
    Packed12 image_data;
} Task;

extern PackedOffsets D_80024004;
extern void *D_80024028[7];
extern u8 D_80025100[16];
extern Packed12 D_8002510C;
extern volatile s16 D_80025118[5];
extern u8 D_8006CCD8[16];
extern u8 D_8006CCE8[16];
extern s32 D_800814A0[3];
extern s32 D_8008346C[3];
extern u8 D_800E3D68[16];

extern s32 func_8003DF74(void *, void *, s16 *, s32);
extern Task *func_8003FC64(s32);
extern void func_8004491C(void *, void (*)(void));
extern void func_80044A50(void *);
extern s32 func_80069EF8(void);
extern s32 func_800A4778(u16, u16, s16, void *);
extern void func_800A56E0(s32);
extern s32 func_8009D218(void *, s32, void *);
extern s32 func_800A6D30(void);
extern void func_800C8B84(void *, s32, s32);
extern void func_80024394(void *, s16, s32, s32, s32, s32, s32);
extern void func_80024548(void);
extern void func_80045340(void);

extern void func_80024898(void) __attribute__((noreturn));
extern void func_80024948(void) __attribute__((noreturn));
extern void func_80024D40(void) __attribute__((noreturn));
extern void func_80024D6C(void) __attribute__((noreturn));
extern void func_80024E18(void) __attribute__((noreturn));
extern void func_80025064(void) __attribute__((noreturn));
extern void func_800250D4(void) __attribute__((noreturn));

/* Updates the actor effect through movement, particle emission, fading, and cleanup. */
void func_818D4E68(Actor *actor, Motion *position, Render *sprite)
{
    s16 position_delta[4];
    PackedOffsets offsets;
    Actor *actor_data = actor;
    register Motion *motion ASM_REG("$17") = position;
    Render *render = sprite;
    Entity *entity;
    register Owner *owner ASM_REG("$16");
    register Motion *owner_motion ASM_REG("$18");
    s32 state;
    u16 timer;
    void **jump_table;

    static void *const state_labels[] = {
        &&state0, &&state1, &&state2, &&state3, &&state4, &&state5, &&state6
    };
    {
        u8 *copy_page;
        register PackedOffsets *copy_src ASM_REG("$6");
        copy_page = (u8 *)0x80020000;
        ASM_KEEP(copy_page);
        ASM_KEEP(actor_data);
        ASM_KEEP(render);
        entity = actor_data->entity;
        ASM_KEEP(entity);
        copy_src = (PackedOffsets *)(copy_page + 0x4004);
        ASM_KEEP(copy_src);
        offsets.copy.first = copy_src->copy.first;
        offsets.copy.second = copy_src->copy.second;
        offsets.copy.third = copy_src->copy.third;
        ASM_KEEP(copy_page);
    }
    timer = actor_data->timer82;
    state = actor_data->state;
    ASM_KEEP(state);
    owner = (Owner *)((u8 *)entity - 0x20);
    ASM_KEEP(owner);
    owner_motion = owner->position;
    timer++;
    actor_data->timer82 = timer;

    if ((u32)state >= 7U) {
        return;
    }
    jump_table = (void **)0x80020000;
    ASM_KEEP(jump_table);
    jump_table = (void **)((u8 *)jump_table + 0x4028);
    ASM_KEEP(jump_table);
    goto *jump_table[state];

state0:
    *(u32 *)&render->color0 = 0x00808080;
    render->scale_y = 0x1000;
    render->scale_x = 0x1000;
    ASM_SCHED_BARRIER();
    {
        u8 *copy_page;
        register Packed12 *copy_src ASM_REG("$6");
        copy_page = (u8 *)0x80020000;
        ASM_KEEP(copy_page);
        copy_src = (Packed12 *)(copy_page + 0x510C);
        ASM_KEEP(copy_src);
        actor_data->image_data = *copy_src;
        ASM_USE_NV(copy_page);
    }
    {
        u8 *copy_dest = (u8 *)actor_data + 0x94;
        ASM_KEEP(copy_dest);
        render->image = copy_dest;
    }
    {
        u32 direction_bits;
        u16 next_state;
        register s16 *flag_base ASM_REG("$4");

        flag_base = (s16 *)0x80020000;
        ASM_KEEP(flag_base);
        direction_bits = entity->flags2A;
        next_state = 1;
        *(volatile s16 *)((u8 *)flag_base + 0x5118) = next_state;
        next_state = actor_data->state;
        direction_bits = (direction_bits >> 9) & 7;
        next_state++;
        actor_data->direction = direction_bits;
        actor_data->state = next_state;
    }
    if (func_8003DF74(owner->aux->field08, owner->aux, position_delta, 0) == 0 &&
        !(owner->aux->flags14 & 0x8000)) {
        return;
    }
    {
        u16 motion_z;
        u16 delta_z;
        motion->x.half.hi = owner_motion->x.half.hi;
        motion->y.half.hi = owner_motion->y.half.hi;
        motion->z.half.hi = owner_motion->z.half.hi;
        if (!(owner->aux->flags14 & 0x8000)) {
            motion->x.half.hi += (u16)position_delta[0];
            motion->y.half.hi += (u16)position_delta[1];
            ASM_SCHED_BARRIER();
            motion_z = motion->z.half.hi;
            delta_z = (u16)position_delta[2];
            motion_z += delta_z;
            ASM_TAILSLOT_PIN_TIED(motion_z);
            func_80024898();
        }
        ASM_SCHED_BARRIER();
        motion->z.half.hi -= 0x40;
    }
    if (!(*(u16 *)actor_data->field04 & 0x80)) {
        return;
    }
    {
        void *callback_owner;
        if (!(actor_data->flags7A & 4)) {
            callback_owner = (u8 *)actor_data - 0x20;
            ASM_KEEP_NV(callback_owner);
            func_8004491C(callback_owner, func_80045340);
            render->field10 = 0x40;
            render->color2 = 0x80;
            render->color1 = 0x80;
            render->color0 = 0x80;
            render->scale_y = 0x800;
            render->scale_x = 0x800;
            render->flags |= 0xC;
            actor_data->flags7A |= 4;
        }
    }
    if (entity->link60 != 0) {
        void *link;
        register u8 *linked_pos ASM_REG("$6");
        u16 linked_z;
        link = entity->link60;
        linked_pos = *(u8 **)((u8 *)link - 0x18);
        linked_z = *(u16 *)(linked_pos + 0xA) - 0x40;
        ASM_TAILSLOT_PIN_TIED(linked_z);
        func_80024948();
    }
    actor_data->target_y = (s16)(entity->height88 - 0x50);
    ASM_SCHED_BARRIER();
    {
        Aux *aux;
        s32 entity_coord;
        register s32 aux_coord ASM_REG("$3");
        s32 distance;

        {
            u8 *lookup_base;
            u32 lookup;
            register u32 tile ASM_REG("$2");
            lookup_base = D_8006CCD8;
            lookup = (u32)actor_data->direction << 1;
            aux = *(Aux **)((u8 *)entity - 0x14);
            lookup += (u32)lookup_base;
            ASM_KEEP(lookup);
            tile = aux->tile_x;
            lookup = *(u8 *)lookup;
            tile += lookup;
            actor_data->target_x = (s8)tile;
        }
        {
            register u8 *lookup_page ASM_REG("$2");
            u8 *lookup_base;
            u32 lookup;
            u32 tile;
            lookup_page = (u8 *)0x80070000;
            ASM_KEEP(lookup_page);
            lookup = (u32)actor_data->direction << 1;
            lookup_base = lookup_page - 0x3318;
            lookup += (u32)lookup_base;
            ASM_KEEP(lookup);
            tile = aux->tile_y;
            lookup = *(u8 *)lookup;
            tile += lookup;
            actor_data->target_z = (s8)tile;
        }

        entity_coord = entity->tile_x72;
        aux_coord = aux->tile_x;
        if (entity_coord == aux_coord) {
            entity_coord = entity->tile_y73;
            aux_coord = aux->tile_y;
        }
        distance = entity_coord - aux_coord;
        if (distance < 0) {
            distance = -distance;
        }
        actor_data->countdown = (s8)(distance * 4 - 3);
    }
    {
        AlignedOffsetPair *offset_base;
        register s32 direction ASM_REG("$2");
        ASM_SCHED_BARRIER();
        direction = actor_data->direction;
        offset_base = (AlignedOffsetPair *)(void *)offsets.bytes;
        direction <<= 2;
        direction = (u32)offset_base + direction;
        motion->dx = ((AlignedOffsetPair *)(u32)direction)->x << 16;
        direction = actor_data->direction;
        direction <<= 2;
        offset_base = (AlignedOffsetPair *)((u8 *)offset_base + direction);
        motion->dy = offset_base->y << 16;
    }
    motion->dz = ((actor_data->target_y << 16) - motion->z.word) / actor_data->countdown;
    {
        u16 current_state;
        current_state = actor_data->state;
        ASM_KEEP(current_state);
    }
    actor_data->timer82 = 0;
    func_80025064();

state1:
    if ((func_800A4778(motion->x.half.hi, motion->y.half.hi,
                       (s16)motion->z.half.hi, entity->link60) << 16) != 0) {
        goto state1_cleanup;
    }
    {
        u16 angle;
        register Task *task ASM_REG("$16");
        angle = render->angle;
        render->angle = angle + 0x300;
        if ((u16)(angle + 0x300) >= 0x1001) {
            render->angle = angle - 0xD00;
        }
        task = func_8003FC64(0x212);
        if (task != 0) {
            Motion *task_motion;
            register Render *task_render ASM_REG("$7");
            task->field22 = 0x10;
            task->update = func_80024548;
            func_8004491C(task, func_80045340);
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
            ASM_SCHED_BARRIER();
            {
                u8 *copy_page;
                register Packed12 *copy_src ASM_REG("$6");
                copy_page = (u8 *)0x80020000;
                ASM_KEEP(copy_page);
                copy_src = (Packed12 *)(copy_page + 0x510C);
                ASM_KEEP(copy_src);
                task->image_data = *copy_src;
                ASM_USE_NV(copy_page);
            }
            {
                u8 *task_image = (u8 *)task + 0x40;
                task_render->image = task_image;
            }
        }
        actor_data->countdown--;
        if (actor_data->countdown <= 0) {
            if (entity->link60 != 0) {
                register void *link ASM_REG("$6");
                register Motion *linked_motion ASM_REG("$6");
                s32 sound_id;
                link = entity->link60;
                sound_id = 0x300;
                ASM_KEEP(sound_id);
                linked_motion = *(Motion **)((u8 *)link - 0x18);
                motion->x.half.hi = linked_motion->x.half.hi;
                motion->y.half.hi = linked_motion->y.half.hi;
                motion->z.half.hi = actor_data->target_y;
                render->image = D_80025100;
                render->scale_y = 0x400;
                render->scale_x = 0x400;
                render->field10 = 0x40;
                motion->z.word += 0x80000;
                render->color0 = 0x20;
                render->color1 = 0x20;
                render->color2 = 0x20;
                actor_data->step88 = 600;
                actor_data->color_step = 2;
                actor_data->accel = 400;
                actor_data->timer84 = 0;
                actor_data->state++;
                render->field06 = 100;
                func_800A56E0(sound_id);
                func_800250D4();
            }
state1_cleanup:
            func_80044A50((u8 *)actor_data - 0x20);
            actor_data->state = 6;
            actor_data->timer84 = 0;
            actor_data->timer82 = 0;
            func_800250D4();
        }
        motion->x.word += motion->dx;
        motion->y.word += motion->dy;
        motion->z.word += motion->dz;
        func_800250D4();
    }

state2:
    actor_data->timer84++;
    if (actor_data->timer84 < 5) {
        render->scale_y += 3000;
        render->scale_x = render->scale_y;
        func_80024D6C();
    }
    if (render->scale_x >= 0x1001) {
        if (render->scale_x >= 0x2EE1) {
            actor_data->step88 = 700;
        }
        if (render->scale_x >= 0x2711) {
            s32 step = 500;
            ASM_TAILSLOT_PIN_TIED(step);
            func_80024D40();
        }
        if (render->scale_x >= 0x2001) {
            s32 step = 200;
            ASM_TAILSLOT_PIN_TIED(step);
            func_80024D40();
        }
        if (render->scale_x >= 0x1801) {
            s32 step = 120;
            ASM_TAILSLOT_PIN_TIED(step);
            func_80024D40();
        }
        if (render->scale_x >= 0x1001) {
            s32 step = 60;
            ASM_TAILSLOT_PIN_TIED(step);
            func_80024D40();
        }
        if (render->scale_x >= 0x801) {
            actor_data->step88 = 40;
        }
        render->scale_x -= actor_data->step88;
        render->scale_y -= actor_data->step88;
    }
    render->angle += actor_data->accel;
    actor_data->accel += 20;
    if (render->color0 < 120) {
        u32 color;
        s32 is_dim;
        color = render->color0;
        is_dim = color < 60;
        if (is_dim) {
            actor_data->color_step = 4;
        } else {
            actor_data->color_step = 1;
        }
        render->color0 += (u8)actor_data->color_step;
        render->color1 += (u8)actor_data->color_step;
        render->color2 += (u8)actor_data->color_step;
    }
    {
        s32 particle_count;
        register s32 color ASM_REG("$18");
        register s32 offset_x ASM_REG("$17");
        register s32 offset_y ASM_REG("$16");
        s32 more_particles;
        s32 offset_z;
        particle_count = 0;
        if (actor_data->timer84 >= 81) {
            actor_data->timer84 = 0;
            actor_data->timer82 = 0;
            actor_data->state++;
        }
        ASM_KEEP(particle_count);
        particle_count++;
        color = func_80069EF8();
        color &= 0xFF;
        color |= 0x80;
        offset_x = func_80069EF8();
        offset_x &= 0x7F;
        offset_x -= 0x40;
        offset_x = (s16)offset_x;
        offset_y = func_80069EF8();
        offset_y &= 0x7F;
        offset_y -= 0x40;
        offset_y = (s16)offset_y;
        offset_z = (s16)((func_80069EF8() & 0x7F) - 0x40);
        func_80024394((u8 *)actor_data - 0x20, actor_data->direction, 0xC0C0C0,
                      color, offset_x, offset_y, offset_z);
        more_particles = particle_count < 2;
        if (!more_particles) {
            return;
        }
    }
    func_80024E18();

state3:
    {
        register s32 particle_count ASM_REG("$19");
        for (particle_count = 0; particle_count < 2; particle_count++) {
            register s32 color ASM_REG("$18");
            register s32 offset_x ASM_REG("$17");
            register s32 offset_y ASM_REG("$16");
            s32 offset_z;
            color = func_80069EF8();
            color &= 0xFF;
            color |= 0x80;
            offset_x = func_80069EF8();
            offset_x &= 0x7F;
            offset_x -= 0x40;
            offset_x = (s16)offset_x;
            offset_y = func_80069EF8();
            offset_y &= 0x7F;
            offset_y -= 0x40;
            offset_y = (s16)offset_y;
            offset_z = (s16)((func_80069EF8() & 0x7F) - 0x40);
            func_80024394((u8 *)actor_data - 0x20, actor_data->direction, 0xC0C0C0,
                          color, offset_x, offset_y, offset_z);
        }
    }

state4:
    render->angle += actor_data->accel;
    actor_data->timer84 += 2;
    if (actor_data->timer84 >= 61) {
        s32 effect_type;
        s32 room_id;
        actor_data->timer84 = 40;
        actor_data->state++;
        if (func_8009D218(entity->link60, 4, entity) == 0) {
            register s32 roll ASM_REG("$2");
            register s32 room_value ASM_REG("$3");
            s32 effect_kind;
            register u8 *room_table ASM_REG("$2");
            roll = func_800A6D30();
            roll &= 3;
            ASM_KEEP_NV(roll);
            room_value = actor_data->field09;
            roll += 4;
            room_value >>= 2;
            effect_kind = room_value + roll;
            room_table = (u8 *)0x800E0000;
            ASM_KEEP(room_table);
            room_value = room_table[0x3D68];
            {
                register s32 no_room ASM_REG("$2");
                no_room = 0xFF;
                room_id = 0x10;
                if (room_value == no_room) {
                    ASM_CLOBBER("$3");
                    room_id = no_room;
                }
            }
            effect_type = effect_kind;
            func_800C8B84(entity->link60, room_id, effect_type);
            func_800250D4();
        }
    }
    return;

state5:
    if (render->scale_x >= 51) {
        render->scale_x -= actor_data->step88 * 2;
        render->scale_y -= actor_data->step88 * 2;
    }
    render->angle += actor_data->accel;
    if (render->color0 >= 7) {
        render->color0 -= 4;
        render->color1 -= 4;
        render->color2 -= 4;
    }
    actor_data->timer84 -= 2;
    if (actor_data->timer84 <= 0) {
        actor_data->timer84 = 0;
        actor_data->timer82 = 0;
        actor_data->state++;
        func_800250D4();
    }
    return;

state6:
    {
        u16 old_timer;
        old_timer = actor_data->timer82;
        actor_data->timer82 = old_timer + 1;
        if ((s16)(old_timer + 1) >= 21) {
            register volatile s16 *flag_page ASM_REG("$4");
            s32 active_flag;
            flag_page = (volatile s16 *)0x80020000;
            ASM_KEEP_NV(flag_page);
            active_flag = *(s16 *)((u8 *)flag_page + 0x5118);
            actor_data->timer82 = old_timer;
            if (active_flag == 0) {
                s32 *clear_page;
                s32 *flag_word_page;
                clear_page = (s32 *)0x80080000;
                ASM_KEEP(clear_page);
                clear_page[0x346C / 4] = 0;
                *(u16 *)((u8 *)actor_data - 2) |= 0x8000;
                flag_word_page = (s32 *)0x80080000;
                ASM_KEEP(flag_word_page);
                flag_word_page[0x14A0 / 4] |= 0x8000;
                func_800250D4();
            }
            *(volatile s16 *)((u8 *)flag_page + 0x5118) = 0;
        }
    }
}
