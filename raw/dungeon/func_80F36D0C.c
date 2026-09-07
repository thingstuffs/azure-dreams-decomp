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
    register Entity *entity ASM_REG("$18") = arg0;
    register Motion *motion ASM_REG("$19") = arg1;
    register Effect *effect ASM_REG("$21") = arg2;
    register Object *object ASM_REG("$22") = arg3;
    register s32 direction ASM_REG("$20");
    register PackedRecord *record ASM_REG("$17");
    register TileRecord *tile ASM_REG("$16");
    register u8 *animation ASM_REG("$5");
    register u8 *animation_entry ASM_REG("$2");
    register u32 shifted ASM_REG("$2");
    register s32 animation_angle ASM_REG("$3");
    register s32 zero_arg ASM_REG("$6");
    register PackedRecord *record_base ASM_REG("$2");
    register s32 record_offset ASM_REG("$3");
    register u16 saved_half ASM_REG("$3");
    register TileRecord *tile_base ASM_REG("$3");
    register s32 tile_offset ASM_REG("$2");
    register void *spawn_parent ASM_REG("$4");
    register unsigned long table_address ASM_REG("$4");
    register s16 *velocity_base ASM_REG("$2");
    register s32 velocity ASM_REG("$2");
    register s32 velocity_result ASM_REG("$3");
    register u32 angle_bits ASM_REG("$6");
    register unsigned long state2_address ASM_REG("$3");
    register s32 raw_y ASM_REG("$3");
    register s32 raw_x ASM_REG("$2");
    register s32 current_x ASM_REG("$4");
    register s32 other_delta ASM_REG("$3");
    register u8 *global_page ASM_REG("$2");
    register u8 *data_page ASM_REG("$3");
    register void *detached ASM_REG("$2");
    s32 index;
    Spawned *spawned;

    switch (entity->state) {
    case 0:
        shifted = object->angle >> 9;
        ASM_KEEP_NV(shifted);
        direction = shifted & 7;
        ASM_KEEP_NV(direction);
        velocity_base = (s16 *)0x80070000;
        ASM_KEEP_NV(velocity_base);
        entity->saved_x = motion->x.half.hi;
        saved_half = motion->y.half.hi;
        ASM_KEEP_NV(saved_half);
        velocity_base = (s16 *)((u8 *)velocity_base - 0x3328);
        ASM_KEEP_NV(velocity_base);
        entity->saved_y = saved_half;
        record_offset = direction << 1;
        ASM_KEEP_NV(record_offset);

        index = func_800A70E4(
            effect->x_tile + *(s16 *)(record_offset + (unsigned long)velocity_base),
            effect->y_tile + *(s16 *)((u8 *)D_8006CCE8 + record_offset),
            object->height);
        shifted = index << 16;
        ASM_KEEP_NV(shifted);
        index = (s32)shifted >> 16;
        record_base = D_800E3548;
        ASM_KEEP_NV(record_base);
        record_offset = index << 2;
        ASM_KEEP_NV(record_offset);
        record = (PackedRecord *)(record_offset + (unsigned long)record_base);
        ASM_KEEP_NV(record);

        if (record->bytes[1] == 0x12) {
            object->copy = *record;
            ASM_KEEP(record);
            spawn_parent = (u8 *)entity - 0x20;
            ASM_KEEP_NV(spawn_parent);
            tile_base = D_800E36C8;
            ASM_KEEP_NV(tile_base);
            tile_offset = index * 12;
            ASM_KEEP_NV(tile_offset);
            tile = (TileRecord *)(tile_offset + (unsigned long)tile_base);
            ASM_KEEP_NV(tile);
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
        ASM_KEEP_NV(velocity_base);
        table_address = direction << 1;
        ASM_KEEP_NV(table_address);
        velocity_base = (s16 *)(table_address + (unsigned long)velocity_base);
        ASM_KEEP_NV(velocity_base);
        velocity = *velocity_base;
        ASM_KEEP_NV(velocity);
        animation = (u8 *)0x80170000;
        ASM_KEEP_NV(animation);
        velocity_result = (velocity << 16) + (velocity << 15);
        ASM_KEEP_NV(velocity_result);
        velocity_base = D_8006CCE8;
        ASM_KEEP_NV(velocity_base);
        table_address += (unsigned long)velocity_base;
        ASM_KEEP_NV(table_address);
        motion->velocity_x = velocity_result;
        velocity = *(s16 *)table_address;
        ASM_KEEP_NV(velocity);
        animation += 0x4AE4;
        ASM_KEEP_NV(animation);
        velocity_result = (velocity << 16) + (velocity << 15);
        ASM_KEEP_NV(velocity_result);
        motion->velocity_y = velocity_result;
        effect->callback = (void (*)(void))animation;
        global_page = (u8 *)0x80080000;
        ASM_KEEP_NV(global_page);
        shifted = *(s16 *)(global_page + 0x3228);
        ASM_KEEP_NV(shifted);
        animation_angle = (s16)object->angle;
        ASM_KEEP_NV(animation_angle);
        zero_arg = 0;
        ASM_KEEP_NV(zero_arg);
        shifted = (((s32)shifted + animation_angle + 0x100) >> 9) & 7;
        ASM_KEEP_NV(shifted);
        animation_entry = (u8 *)(shifted + (unsigned long)animation);
        ASM_KEEP_NV(animation_entry);
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
        ASM_KEEP_NV(animation);
        effect->callback = (void (*)(void))animation;
        global_page = (u8 *)0x80080000;
        ASM_KEEP_NV(global_page);
        shifted = ((*(s16 *)(global_page + 0x3228) + (s16)object->angle + 0x100) >> 9) & 7;
        ASM_KEEP_NV(shifted);
        animation_entry = (u8 *)(shifted + (unsigned long)animation);
        ASM_KEEP_NV(animation_entry);
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
        ASM_KEEP_NV(animation);
        shifted = object->angle;
        ASM_KEEP_NV(shifted);
        angle_bits = shifted >> 8;
        ASM_KEEP_NV(angle_bits);
        velocity_base = D_8006CCD8;
        ASM_KEEP_NV(velocity_base);
        state2_address = angle_bits & 0xE;
        ASM_KEEP_NV(state2_address);
        velocity_base = (s16 *)(state2_address + (unsigned long)velocity_base);
        ASM_KEEP_NV(velocity_base);
        velocity = -*velocity_base;
        velocity <<= 16;
        ASM_KEEP_NV(velocity);
        motion->velocity_x = velocity;
        velocity_base = D_8006CCE8;
        ASM_KEEP_NV(velocity_base);
        state2_address += (unsigned long)velocity_base;
        ASM_KEEP_NV(state2_address);
        velocity = *(s16 *)state2_address;
        ASM_KEEP_DEP_NV(animation, velocity);
        animation += 0x4A74;
        ASM_KEEP_NV(animation);
        velocity = -velocity;
        velocity <<= 16;
        ASM_KEEP_NV(velocity);
        motion->velocity_y = velocity;
        effect->callback = (void (*)(void))animation;
        global_page = (u8 *)0x80080000;
        ASM_KEEP_NV(global_page);
        shifted = ((*(s16 *)(global_page + 0x3228) + (s16)object->angle + 0x100) >> 9) & 7;
        ASM_KEEP_NV(shifted);
        animation_entry = (u8 *)(shifted + (unsigned long)animation);
        ASM_KEEP_NV(animation_entry);
        func_80047784(effect, *animation_entry, 0);

        raw_y = entity->saved_y;
        ASM_KEEP_NV(raw_y);
        raw_x = motion->y.half.hi;
        ASM_KEEP_NV(raw_x);
        current_x = motion->x.half.hi;
        ASM_KEEP_NV(current_x);
        raw_y -= raw_x;
        ASM_KEEP_NV(raw_y);
        raw_x = entity->saved_x;
        ASM_KEEP_NV(raw_x);
        direction = raw_y;
        if (raw_y < 0) {
            direction = -direction;
        }
        ASM_KEEP_NV(direction);
        raw_x -= current_x;
        other_delta = raw_x;
        if (raw_x < 0) {
            other_delta = -other_delta;
        }
        ASM_KEEP_NV(other_delta);
        if (other_delta < direction) {
            other_delta = direction;
        }
        entity->timer = other_delta;
        entity->state++;
        break;

    case 3:
        entity->timer--;
        ASM_KEEP_NV(motion);
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
            ASM_KEEP_NV(data_page);
            object->flags &= 0x7FFF;
        } else {
            data_page = (u8 *)0x800E0000;
            ASM_KEEP_NV(data_page);
            detached = (u8 *)object - 0x20;
            ASM_KEEP_NV(detached);
            *(void **)(data_page + 0x3DE8) = detached;
        }
        break;
    }
    ASM_KEEP4(entity, motion, effect, object);
}
