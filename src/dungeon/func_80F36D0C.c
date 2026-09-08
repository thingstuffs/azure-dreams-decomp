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

void func_80F36D0C(Entity *arg0, Motion *arg1, Effect *arg2, Object *arg3)
{
    Entity *entity = arg0;
    Motion *motion = arg1;
    Effect *effect = arg2;
    register Object *object ASM_REG("$22") = arg3;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 direction ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    PackedRecord *record;
    register TileRecord *tile ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register u8 *animation ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 *animation_entry;
    register u32 shifted ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    s32 animation_angle;
    register s32 zero_arg ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    register PackedRecord *record_base ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    register s32 record_offset ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register u16 saved_half ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register TileRecord *tile_base ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register s32 tile_offset ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    void *spawn_parent;
    register unsigned long table_address ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s16 *velocity_base ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    register s32 velocity ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    s32 velocity_result;
    register u32 angle_bits ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    register unsigned long state2_address ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s32 raw_y;
    register s32 raw_x ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    s32 current_x;
    s32 other_delta;
    register u8 *global_page ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    u8 *data_page;
    void *detached;
    s32 index;
    Spawned *spawned;

    switch (entity->state) {
    case 0:
        shifted = object->angle >> 9;
        direction = shifted & 7;
        velocity_base = (s16 *)0x80070000;
        ASM_KEEP_NV(velocity_base);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        entity->saved_x = motion->x.half.hi;
        saved_half = motion->y.half.hi;
        ASM_KEEP_NV(saved_half);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        velocity_base = (s16 *)((u8 *)velocity_base - 0x3328);
        ASM_KEEP_NV(velocity_base);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        entity->saved_y = saved_half;
        record_offset = direction << 1;

        index = func_800A70E4(
            effect->x_tile + *(s16 *)(record_offset + (unsigned long)velocity_base),
            effect->y_tile + *(s16 *)((u8 *)D_8006CCE8 + record_offset),
            object->height);
        shifted = index << 16;
        index = (s32)shifted >> 16;
        record_base = D_800E3548;
        record_offset = index << 2;
        record = (PackedRecord *)(record_offset + (unsigned long)record_base);

        if (record->bytes[1] == 0x12) {
            object->copy = *record;
            ASM_KEEP(record);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
            spawn_parent = (u8 *)entity - 0x20;
            ASM_KEEP_NV(spawn_parent);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            tile_base = D_800E36C8;
            tile_offset = index * 12;
            tile = (TileRecord *)(tile_offset + (unsigned long)tile_base);
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

        velocity_base = D_8006CCD8;
        table_address = direction << 1;
        velocity_base = (s16 *)(table_address + (unsigned long)velocity_base);
        velocity = *velocity_base;
        ASM_KEEP_NV(velocity);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        animation = (u8 *)0x80170000;
        ASM_KEEP_NV(animation);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        velocity_result = (velocity << 16) + (velocity << 15);
        velocity_base = D_8006CCE8;
        table_address += (unsigned long)velocity_base;
        ASM_KEEP_NV(table_address);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        motion->velocity_x = velocity_result;
        velocity = *(s16 *)table_address;
        ASM_KEEP_NV(velocity);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        animation += 0x4AE4;
        velocity_result = (velocity << 16) + (velocity << 15);
        motion->velocity_y = velocity_result;
        effect->callback = (void (*)(void))animation;
        global_page = (u8 *)0x80080000;
        ASM_KEEP_NV(global_page);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        shifted = *(s16 *)(global_page + 0x3228);
        ASM_KEEP_NV(shifted);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        animation_angle = (s16)object->angle;
        ASM_KEEP_NV(animation_angle);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        zero_arg = 0;
        ASM_KEEP_NV(zero_arg);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        shifted = (((s32)shifted + animation_angle + 0x100) >> 9) & 7;
        animation_entry = (u8 *)(shifted + (unsigned long)animation);
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
        global_page = (u8 *)0x80080000;
        ASM_KEEP_NV(global_page);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        shifted = ((*(s16 *)(global_page + 0x3228) + (s16)object->angle + 0x100) >> 9) & 7;
        animation_entry = (u8 *)(shifted + (unsigned long)animation);
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

        animation = (u8 *)0x80170000;
        shifted = object->angle;
        angle_bits = shifted >> 8;
        velocity_base = D_8006CCD8;
        state2_address = angle_bits & 0xE;
        velocity_base = (s16 *)(state2_address + (unsigned long)velocity_base);
        velocity = -*velocity_base;
        velocity <<= 16;
        motion->velocity_x = velocity;
        velocity_base = D_8006CCE8;
        state2_address += (unsigned long)velocity_base;
        ASM_KEEP_NV(state2_address);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        velocity = *(s16 *)state2_address;
        ASM_KEEP_DEP_NV(animation, velocity);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        animation += 0x4A74;
        velocity = -velocity;
        velocity <<= 16;
        motion->velocity_y = velocity;
        effect->callback = (void (*)(void))animation;
        global_page = (u8 *)0x80080000;
        ASM_KEEP_NV(global_page);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        shifted = ((*(s16 *)(global_page + 0x3228) + (s16)object->angle + 0x100) >> 9) & 7;
        animation_entry = (u8 *)(shifted + (unsigned long)animation);
        func_80047784(effect, *animation_entry, 0);

        raw_y = entity->saved_y;
        raw_x = motion->y.half.hi;
        current_x = motion->x.half.hi;
        raw_y -= raw_x;
        raw_x = entity->saved_x;
        direction = raw_y;
        if (raw_y < 0) {
            direction = -direction;
        }
        raw_x -= current_x;
        other_delta = raw_x;
        if (raw_x < 0) {
            other_delta = -other_delta;
        }
        if (other_delta < direction) {
            other_delta = direction;
        }
        entity->timer = other_delta;
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
            detached = (u8 *)object - 0x20;
            ASM_KEEP_NV(detached);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            *(void **)(data_page + 0x3DE8) = detached;
        }
        break;
    }
    ASM_KEEP4(entity, motion, effect, object);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
}
