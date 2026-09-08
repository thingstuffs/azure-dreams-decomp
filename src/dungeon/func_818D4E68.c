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

void func_818D4E68(Actor *arg0, Motion *arg1, Render *arg2)
{
    s16 delta[4];
    PackedOffsets offsets;
    Actor *self = arg0;
    register Motion *motion ASM_REG("$17") = arg1;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    Render *render = arg2;
    Entity *entity;
    register Owner *owner ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register Motion *source ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    s32 state;
    u16 timer;
    void **jump_table;

    static void *const keepalive[] = {
        &&state0, &&state1, &&state2, &&state3, &&state4, &&state5, &&state6
    };
    {
        u8 *copy_page;
        register PackedOffsets *copy_src ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        copy_page = (u8 *)0x80020000;
        ASM_KEEP(copy_page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(self);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ASM_KEEP(render);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        entity = self->entity;
        ASM_KEEP(entity);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        copy_src = (PackedOffsets *)(copy_page + 0x4004);
        ASM_KEEP(copy_src);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        offsets.copy.first = copy_src->copy.first;
        offsets.copy.second = copy_src->copy.second;
        offsets.copy.third = copy_src->copy.third;
        ASM_KEEP(copy_page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    }
    timer = self->timer82;
    state = self->state;
    ASM_KEEP(state);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    owner = (Owner *)((u8 *)entity - 0x20);
    ASM_KEEP(owner);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    source = owner->position;
    timer++;
    self->timer82 = timer;

    if ((u32)state >= 7U) {
        return;
    }
    jump_table = (void **)0x80020000;
    ASM_KEEP(jump_table);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    jump_table = (void **)((u8 *)jump_table + 0x4028);
    ASM_KEEP(jump_table);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    goto *jump_table[state];

state0:
    *(u32 *)&render->color0 = 0x00808080;
    render->scale_y = 0x1000;
    render->scale_x = 0x1000;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    {
        u8 *copy_page;
        register Packed12 *copy_src ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        copy_page = (u8 *)0x80020000;
        ASM_KEEP(copy_page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        copy_src = (Packed12 *)(copy_page + 0x510C);
        ASM_KEEP(copy_src);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        self->image_data = *copy_src;
        ASM_USE_NV(copy_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    }
    {
        u8 *copy_dest = (u8 *)self + 0x94;
        ASM_KEEP(copy_dest);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        render->image = copy_dest;
    }
    {
        u32 entity_bits;
        u16 scalar;
        register s16 *flag_base ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

        flag_base = (s16 *)0x80020000;
        ASM_KEEP(flag_base);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        entity_bits = entity->flags2A;
        scalar = 1;
        *(volatile s16 *)((u8 *)flag_base + 0x5118) = scalar;
        scalar = self->state;
        entity_bits = (entity_bits >> 9) & 7;
        scalar++;
        self->direction = entity_bits;
        self->state = scalar;
    }
    if (func_8003DF74(owner->aux->field08, owner->aux, delta, 0) == 0 &&
        !(owner->aux->flags14 & 0x8000)) {
        return;
    }
    {
        u16 motion_z;
        u16 delta_z;
        motion->x.half.hi = source->x.half.hi;
        motion->y.half.hi = source->y.half.hi;
        motion->z.half.hi = source->z.half.hi;
        if (!(owner->aux->flags14 & 0x8000)) {
            motion->x.half.hi += (u16)delta[0];
            motion->y.half.hi += (u16)delta[1];
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            motion_z = motion->z.half.hi;
            delta_z = (u16)delta[2];
            motion_z += delta_z;
            ASM_TAILSLOT_PIN_TIED(motion_z);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            func_80024898();
        }
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        motion->z.half.hi -= 0x40;
    }
    if (!(*(u16 *)self->field04 & 0x80)) {
        return;
    }
    {
        void *callback_owner;
        if (!(self->flags7A & 4)) {
            callback_owner = (u8 *)self - 0x20;
            ASM_KEEP_NV(callback_owner);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            func_8004491C(callback_owner, func_80045340);
            render->field10 = 0x40;
            render->color2 = 0x80;
            render->color1 = 0x80;
            render->color0 = 0x80;
            render->scale_y = 0x800;
            render->scale_x = 0x800;
            render->flags |= 0xC;
            self->flags7A |= 4;
        }
    }
    if (entity->link60 != 0) {
        void *link;
        register u8 *linked_pos ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        u16 linked_z;
        link = entity->link60;
        linked_pos = *(u8 **)((u8 *)link - 0x18);
        linked_z = *(u16 *)(linked_pos + 0xA) - 0x40;
        ASM_TAILSLOT_PIN_TIED(linked_z);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        func_80024948();
    }
    self->target_y = (s16)(entity->height88 - 0x50);
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    {
        Aux *aux;
        s32 entity_coord;
        register s32 aux_coord ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        s32 distance;

        {
            u8 *lookup_base;
            u32 lookup;
            register u32 tile ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            lookup_base = D_8006CCD8;
            lookup = (u32)self->direction << 1;
            aux = *(Aux **)((u8 *)entity - 0x14);
            lookup += (u32)lookup_base;
            ASM_KEEP(lookup);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
            tile = aux->tile_x;
            lookup = *(u8 *)lookup;
            tile += lookup;
            self->target_x = (s8)tile;
        }
        {
            register u8 *lookup_page ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            u8 *lookup_base;
            u32 lookup;
            u32 tile;
            lookup_page = (u8 *)0x80070000;
            ASM_KEEP(lookup_page);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
            lookup = (u32)self->direction << 1;
            lookup_base = lookup_page - 0x3318;
            lookup += (u32)lookup_base;
            ASM_KEEP(lookup);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
            tile = aux->tile_y;
            lookup = *(u8 *)lookup;
            tile += lookup;
            self->target_z = (s8)tile;
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
        self->countdown = (s8)(distance * 4 - 3);
    }
    {
        AlignedOffsetPair *offset_base;
        register s32 direction ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        direction = self->direction;
        offset_base = (AlignedOffsetPair *)(void *)offsets.bytes;
        direction <<= 2;
        direction = (u32)offset_base + direction;
        motion->dx = ((AlignedOffsetPair *)(u32)direction)->x << 16;
        direction = self->direction;
        direction <<= 2;
        offset_base = (AlignedOffsetPair *)((u8 *)offset_base + direction);
        motion->dy = offset_base->y << 16;
    }
    motion->dz = ((self->target_y << 16) - motion->z.word) / self->countdown;
    {
        u16 dead_state;
        dead_state = self->state;
        ASM_KEEP(dead_state);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    }
    self->timer82 = 0;
    func_80025064();

state1:
    if ((func_800A4778(motion->x.half.hi, motion->y.half.hi,
                       (s16)motion->z.half.hi, entity->link60) << 16) != 0) {
        goto state1_cleanup;
    }
    {
        u16 angle;
        register Task *task ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        angle = render->angle;
        render->angle = angle + 0x300;
        if ((u16)(angle + 0x300) >= 0x1001) {
            render->angle = angle - 0xD00;
        }
        task = func_8003FC64(0x212);
        if (task != 0) {
            Motion *task_motion;
            register Render *task_render ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
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
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            {
                u8 *copy_page;
                register Packed12 *copy_src ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                copy_page = (u8 *)0x80020000;
                ASM_KEEP(copy_page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                copy_src = (Packed12 *)(copy_page + 0x510C);
                ASM_KEEP(copy_src);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
                task->image_data = *copy_src;
                ASM_USE_NV(copy_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            }
            {
                u8 *task_image = (u8 *)task + 0x40;
                task_render->image = task_image;
            }
        }
        self->countdown--;
        if (self->countdown <= 0) {
            if (entity->link60 != 0) {
                register void *link ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                register Motion *linked_motion ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                s32 sound_id;
                link = entity->link60;
                sound_id = 0x300;
                ASM_KEEP(sound_id);
                linked_motion = *(Motion **)((u8 *)link - 0x18);
                motion->x.half.hi = linked_motion->x.half.hi;
                motion->y.half.hi = linked_motion->y.half.hi;
                motion->z.half.hi = self->target_y;
                render->image = D_80025100;
                render->scale_y = 0x400;
                render->scale_x = 0x400;
                render->field10 = 0x40;
                motion->z.word += 0x80000;
                render->color0 = 0x20;
                render->color1 = 0x20;
                render->color2 = 0x20;
                self->step88 = 600;
                self->color_step = 2;
                self->accel = 400;
                self->timer84 = 0;
                self->state++;
                render->field06 = 100;
                func_800A56E0(sound_id);
                func_800250D4();
            }
state1_cleanup:
            func_80044A50((u8 *)self - 0x20);
            self->state = 6;
            self->timer84 = 0;
            self->timer82 = 0;
            func_800250D4();
        }
        motion->x.word += motion->dx;
        motion->y.word += motion->dy;
        motion->z.word += motion->dz;
        func_800250D4();
    }

state2:
    self->timer84++;
    if (self->timer84 < 5) {
        render->scale_y += 3000;
        render->scale_x = render->scale_y;
        func_80024D6C();
    }
    if (render->scale_x >= 0x1001) {
        if (render->scale_x >= 0x2EE1) {
            self->step88 = 700;
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
            self->step88 = 40;
        }
        render->scale_x -= self->step88;
        render->scale_y -= self->step88;
    }
    render->angle += self->accel;
    self->accel += 20;
    if (render->color0 < 120) {
        u32 color;
        s32 below_60;
        color = render->color0;
        below_60 = color < 60;
        if (below_60) {
            self->color_step = 4;
        } else {
            self->color_step = 1;
        }
        render->color0 += (u8)self->color_step;
        render->color1 += (u8)self->color_step;
        render->color2 += (u8)self->color_step;
    }
    {
        s32 i;
        register s32 color ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        register s32 x ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        register s32 y ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        s32 loop_test;
        s32 z;
        i = 0;
        if (self->timer84 >= 81) {
            self->timer84 = 0;
            self->timer82 = 0;
            self->state++;
        }
        ASM_KEEP(i);
        i++;
        color = func_80069EF8();
        color &= 0xFF;
        color |= 0x80;
        x = func_80069EF8();
        x &= 0x7F;
        x -= 0x40;
        x = (s16)x;
        y = func_80069EF8();
        y &= 0x7F;
        y -= 0x40;
        y = (s16)y;
        z = (s16)((func_80069EF8() & 0x7F) - 0x40);
        func_80024394((u8 *)self - 0x20, self->direction, 0xC0C0C0,
                      color, x, y, z);
        loop_test = i < 2;
        if (!loop_test) {
            return;
        }
    }
    func_80024E18();

state3:
    {
        register s32 i ASM_REG("$19");
        for (i = 0; i < 2; i++) {
            register s32 color ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            register s32 x ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            register s32 y ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            s32 z;
            color = func_80069EF8();
            color &= 0xFF;
            color |= 0x80;
            x = func_80069EF8();
            x &= 0x7F;
            x -= 0x40;
            x = (s16)x;
            y = func_80069EF8();
            y &= 0x7F;
            y -= 0x40;
            y = (s16)y;
            z = (s16)((func_80069EF8() & 0x7F) - 0x40);
            func_80024394((u8 *)self - 0x20, self->direction, 0xC0C0C0,
                          color, x, y, z);
        }
    }

state4:
    render->angle += self->accel;
    self->timer84 += 2;
    if (self->timer84 >= 61) {
        s32 kind;
        s32 room;
        self->timer84 = 40;
        self->state++;
        if (func_8009D218(entity->link60, 4, entity) == 0) {
            register s32 roll ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            register s32 field ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            s32 call_kind;
            register u8 *room_table ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            roll = func_800A6D30();
            roll &= 3;
            ASM_KEEP_NV(roll);
            field = self->field09;
            roll += 4;
            field >>= 2;
            call_kind = field + roll;
            room_table = (u8 *)0x800E0000;
            ASM_KEEP(room_table);
            field = room_table[0x3D68];
            {
                register s32 selected ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                selected = 0xFF;
                room = 0x10;
                if (field == selected) {
                    ASM_CLOBBER("$3");
                    room = selected;
                }
            }
            kind = call_kind;
            func_800C8B84(entity->link60, room, kind);
            func_800250D4();
        }
    }
    return;

state5:
    if (render->scale_x >= 51) {
        render->scale_x -= self->step88 * 2;
        render->scale_y -= self->step88 * 2;
    }
    render->angle += self->accel;
    if (render->color0 >= 7) {
        render->color0 -= 4;
        render->color1 -= 4;
        render->color2 -= 4;
    }
    self->timer84 -= 2;
    if (self->timer84 <= 0) {
        self->timer84 = 0;
        self->timer82 = 0;
        self->state++;
        func_800250D4();
    }
    return;

state6:
    {
        u16 old_timer;
        old_timer = self->timer82;
        self->timer82 = old_timer + 1;
        if ((s16)(old_timer + 1) >= 21) {
            register volatile s16 *flag_page ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
            s32 flag;
            flag_page = (volatile s16 *)0x80020000;
            ASM_KEEP_NV(flag_page);
            flag = *(s16 *)((u8 *)flag_page + 0x5118);
            self->timer82 = old_timer;
            if (flag == 0) {
                s32 *clear_page;
                s32 *flag_word_page;
                clear_page = (s32 *)0x80080000;
                ASM_KEEP(clear_page);
                clear_page[0x346C / 4] = 0;
                *(u16 *)((u8 *)self - 2) |= 0x8000;
                flag_word_page = (s32 *)0x80080000;
                ASM_KEEP(flag_word_page);
                flag_word_page[0x14A0 / 4] |= 0x8000;
                func_800250D4();
            }
            *(volatile s16 *)((u8 *)flag_page + 0x5118) = 0;
        }
    }
}
