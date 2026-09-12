#include "common.h"

typedef union {
    s32 value;
    struct {
        u16 lo;
        s16 hi;
    } half;
} FixedCoord;

typedef struct {
    FixedCoord x;
    FixedCoord y;
    u8 pad08[2];
    s16 height;
    s32 velocity_x;
    s32 velocity_y;
} Motion;

typedef struct {
    u8 pad00[0x8C];
    void (*callback)(void);
    u8 pad90[6];
    s16 timer;
    u8 pad98[3];
    u8 state;
    u8 pad9C[12];
    s16 saved_x;
    s16 saved_y;
} Entity;

typedef struct {
    u8 pad00[0x14];
    u16 flags;
    u8 pad16[0xE];
    u8 x_tile;
    u8 y_tile;
    u8 pad26[6];
    void (*callback)(void);
} Effect;

typedef struct {
    u8 bytes[4];
} PackedRecord __attribute__((packed));

typedef struct {
    u8 x;
    u8 y;
    u8 pad02[10];
} TileRecord;

typedef struct {
    u8 pad00[0x2A];
    u16 angle;
    u8 pad2C[0x1A];
    u16 flags;
    PackedRecord copy;
    u8 pad4C[0x21];
    s8 flag6D;
    u8 pad6E[0x1A];
    s16 height;
} Object;

typedef struct {
    u8 pad00[0x10];
    void (*callback)(void);
    u8 pad14[0xA7];
    u8 state;
} Spawned;

typedef struct {
    u8 pad00[10];
    u16 count;
} CounterBlock;

extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern s16 D_80083228[];
extern CounterBlock D_80083460[];
extern PackedRecord D_800E3548[];
extern TileRecord D_800E36C8[];
extern u8 D_80174A74[];
extern u8 D_80174AE4[];
extern u8 D_80174AEC[];
extern void *D_800E3DE8[];

extern s32 func_800A70E4(s16, s16, s16);
extern Spawned *func_800A8608(void *, PackedRecord *, s32, s32, s16);
extern void func_8009A3D0(s32, s32, s32);
extern void func_80047784(Effect *, u8, s32);
extern void func_800A56E0(s32);
extern void func_800AD594(Object *, s32);
extern void func_800A4ACC(Object *);
extern void func_801743E8(void);
extern void func_80170E94(void);

/* Moves the entity forward, then returns it to its saved position and restores its callback. */
void func_80F36D0C(Entity *entity_arg, Motion *motion_arg, Effect *effect_arg, Object *object_arg)
{
    Entity *entity = entity_arg;
    Motion *motion = motion_arg;
    Effect *effect = effect_arg;
    register Object *object ASM_REG("$22") = object_arg;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 direction ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    PackedRecord *record;
    register TileRecord *tile ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register u8 *animation ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 *animation_entry;
    register u32 angle_index ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    s32 animation_angle;
    register s32 zero_arg ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    register PackedRecord *record_base ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    s32 record_offset;
    u16 saved_y;
    register TileRecord *tile_base ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    void *spawn_parent;
    register unsigned long step_addr ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s16 *step_table ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    register s32 velocity ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    s32 scaled_velocity;
    register u32 angle_bits ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    register unsigned long return_step_addr ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s32 delta_y;
    register s32 coord_delta ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    s32 current_x;
    s32 return_distance;
    register u8 *angle_page ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    u8 *data_page;
    void *object_base;
    s32 record_index;
    Spawned *spawned;

    switch (entity->state) {
    case 0:
        angle_index = object->angle >> 9;
        direction = angle_index & 7;
        step_table = (s16 *)0x80070000;
        ASM_KEEP_NV(step_table);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        entity->saved_x = motion->x.half.hi;
        saved_y = motion->y.half.hi;
        ASM_KEEP_NV(saved_y);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        step_table = (s16 *)((u8 *)step_table - 0x3328);
        ASM_KEEP_NV(step_table);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        entity->saved_y = saved_y;
        record_offset = direction << 1;

        record_index = func_800A70E4(
            effect->x_tile + *(s16 *)(record_offset + (unsigned long)step_table),
            effect->y_tile + *(s16 *)((u8 *)D_8006CCE8 + record_offset),
            object->height);
        angle_index = record_index << 16;
        record_index = (s32)angle_index >> 16;
        record_base = D_800E3548;
        record = (PackedRecord *)((record_index << 2) + (unsigned long)record_base);

        if (record->bytes[1] == 0x12) {
            object->copy = *record;
            ASM_KEEP(record);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
            spawn_parent = (u8 *)entity - 0x20;
            ASM_KEEP_NV(spawn_parent);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            tile_base = D_800E36C8;
            animation_entry = record_index * 12;
            tile = (TileRecord *)(animation_entry + (unsigned long)tile_base);
            ASM_KEEP_NV(tile);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            spawned = func_800A8608(
                spawn_parent,
                record,
                (tile->x << 6) | 0x20,
                (tile->y << 6) | 0x20,
                motion->height);
            if (spawned != 0) {
                spawned->callback = func_801743E8;
                spawned->state = 0;
            }
            record->bytes[0] = 0;
            record->bytes[1] = 0;
            func_8009A3D0(tile->x, tile->y, 0x800);
        }

        if (effect->flags & 0x8000) {
            entity->state = 3;
            entity->timer = 0;
            break;
        }

        step_table = D_8006CCD8;
        step_addr = direction << 1;
        step_table = (s16 *)(step_addr + (unsigned long)step_table);
        velocity = *step_table;
        ASM_KEEP_NV(velocity);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        animation = (u8 *)0x80170000;
        ASM_KEEP_NV(animation);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        scaled_velocity = (velocity << 16) + (velocity << 15);
        step_table = D_8006CCE8;
        step_addr += (unsigned long)step_table;
        ASM_KEEP_NV(step_addr);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        motion->velocity_x = scaled_velocity;
        velocity = *(s16 *)step_addr;
        ASM_KEEP_NV(velocity);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        animation += 0x4AE4;
        scaled_velocity = (velocity << 16) + (velocity << 15);
        motion->velocity_y = scaled_velocity;
        effect->callback = (void (*)(void))animation;
        angle_page = (u8 *)0x80080000;
        ASM_KEEP_NV(angle_page);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        angle_index = *(s16 *)(angle_page + 0x3228);
        ASM_KEEP_NV(angle_index);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        animation_angle = (s16)object->angle;
        ASM_KEEP_NV(animation_angle);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        zero_arg = 0;
        ASM_KEEP_NV(zero_arg);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        angle_index = (((s32)angle_index + animation_angle + 0x100) >> 9) & 7;
        animation_entry = (u8 *)(angle_index + (unsigned long)animation);
        func_80047784(effect, *animation_entry, zero_arg);
        func_800A56E0(0x51E);
        entity->timer = 2000;
        entity->state++;
        break;

    case 1:
        if ((effect->flags & 0x6000) && entity->timer >= 1001) {
            motion->velocity_x = 0;
            motion->velocity_y = 0;
            entity->timer = 10;
        }
        entity->timer--;
        if (entity->timer >= 0) {
            break;
        }
        animation = D_80174AEC;
        effect->callback = (void (*)(void))animation;
        angle_page = (u8 *)0x80080000;
        ASM_KEEP_NV(angle_page);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        angle_index = ((*(s16 *)(angle_page + 0x3228) + (s16)object->angle + 0x100) >> 9) & 7;
        animation_entry = (u8 *)(angle_index + (unsigned long)animation);
        func_80047784(effect, *animation_entry, 0);
        entity->timer = 2000;
        entity->state++;
        break;

    case 2:
        if ((effect->flags & 0x6000) && entity->timer >= 1001) {
            entity->timer = 12;
        }
        entity->timer--;
        if (entity->timer >= 0) {
            break;
        }

        angle_index = object->angle;
        angle_bits = angle_index >> 8;
        step_table = D_8006CCD8;
        return_step_addr = angle_bits & 0xE;
        step_table = (s16 *)(return_step_addr + (unsigned long)step_table);
        velocity = -*step_table;
        velocity <<= 16;
        motion->velocity_x = velocity;
        step_table = D_8006CCE8;
        return_step_addr += (unsigned long)step_table;
        ASM_KEEP_NV(return_step_addr);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        velocity = *(s16 *)return_step_addr;
        animation = (u8 *)&D_80174A74;
        velocity = -velocity;
        velocity <<= 16;
        motion->velocity_y = velocity;
        effect->callback = (void (*)(void))animation;
        angle_page = (u8 *)0x80080000;
        ASM_KEEP_NV(angle_page);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        angle_index = ((*(s16 *)(angle_page + 0x3228) + (s16)object->angle + 0x100) >> 9) & 7;
        animation_entry = (u8 *)(angle_index + (unsigned long)animation);
        func_80047784(effect, *animation_entry, 0);

        delta_y = entity->saved_y;
        coord_delta = motion->y.half.hi;
        current_x = motion->x.half.hi;
        delta_y -= coord_delta;
        coord_delta = entity->saved_x;
        direction = delta_y;
        if (delta_y < 0) {
            direction = -direction;
        }
        coord_delta -= current_x;
        return_distance = coord_delta;
        if (coord_delta < 0) {
            return_distance = -return_distance;
        }
        if (return_distance < direction) {
            return_distance = direction;
        }
        entity->timer = return_distance;
        entity->state++;
        break;

    case 3:
        entity->timer--;
        if (entity->timer > 0) {
            break;
        }
        motion->x.value = entity->saved_x << 16;
        motion->y.value = entity->saved_y << 16;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        func_800AD594(object, 0x100);
        entity->callback = func_80170E94;
        D_80083460[0].count--;
        func_800A4ACC(object);
        if (object->flag6D == 0) {
            data_page = (u8 *)0x800E0000;
            object->flags &= 0x7FFF;
        } else {
            data_page = (u8 *)0x800E0000;
            ASM_KEEP_NV(data_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            object_base = (u8 *)object - 0x20;
            ASM_KEEP_NV(object_base);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            *(void **)(data_page + 0x3DE8) = object_base;
        }
        break;
    }
    ASM_KEEP4(entity, motion, effect, object);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
}
