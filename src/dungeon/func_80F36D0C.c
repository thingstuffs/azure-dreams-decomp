#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"

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

extern PackedRecord D_800E3548[];
extern TileRecord D_800E36C8[];
extern u8 D_80174A74[];
extern u8 D_80174AE4[];
extern u8 D_80174AEC[];
extern void *D_800E3DE8[];

extern s32 func_800A70E4(s16, s16, s16);
extern Spawned *func_800A8608(s32 parent, s32 sprite_source, s16 x, s32 y, s16 z);
extern void func_8009A3D0(s32, s32, s32);
extern void func_80047784(Effect *, u8, s32);
extern void func_800A56E0(s32);
extern void func_800AD594(Object *, s32);
extern void func_800A4ACC(Object *);
extern void func_801743E8(void);
extern void func_80170E94(void);
extern int abs(int);

/* Moves the entity forward, then returns it to its saved position and restores its callback. */
void func_80F36D0C(Entity *entity, Motion *motion, Effect *effect, Object *object)
{
    s32 direction;
    s32 index;
    PackedRecord *record;
    PackedRecord *records;
    TileRecord *tile;
    TileRecord *tiles;
    Spawned *spawned;
    s32 distance;

    switch (entity->state) {
    case 0:
        direction = (object->angle >> 9) & 7;
        entity->saved_x = motion->x.half.hi;
        entity->saved_y = motion->y.half.hi;
        index = (s16)func_800A70E4(effect->x_tile + dirStepX[direction],
                                   effect->y_tile + dirStepY[direction], object->height);
        records = D_800E3548;
        record = &records[index];
        if (record->bytes[1] == 0x12) {
            object->copy = *record;
            tiles = D_800E36C8;
            tile = &tiles[index];
            spawned = func_800A8608((u8 *)entity - 0x20, record, (tile->x << 6) | 0x20,
                                    (tile->y << 6) | 0x20, motion->height);
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
        motion->velocity_x = (dirStepX[direction] << 16) + (dirStepX[direction] << 15);
        motion->velocity_y = (dirStepY[direction] << 16) + (dirStepY[direction] << 15);
        effect->callback = (void (*)(void))D_80174AE4;
        func_80047784(effect, D_80174AE4[((gameWork.view.viewAngle + (s16)object->angle + 0x100) >> 9) & 7], 0);
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
        effect->callback = (void (*)(void))D_80174AEC;
        func_80047784(effect, D_80174AEC[((gameWork.view.viewAngle + (s16)object->angle + 0x100) >> 9) & 7], 0);
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
        index = (object->angle >> 9) & 7;
        motion->velocity_x = -dirStepX[index] << 16;
        motion->velocity_y = -dirStepY[index] << 16;
        effect->callback = (void (*)(void))D_80174A74;
        func_80047784(effect, D_80174A74[((gameWork.view.viewAngle + (s16)object->angle + 0x100) >> 9) & 7], 0);
        direction = abs(entity->saved_y - motion->y.half.hi);
        distance = abs(entity->saved_x - motion->x.half.hi);
        if (distance < direction) {
            distance = direction;
        }
        entity->timer = distance;
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
        dungeonStatus.unk_0A--;
        func_800A4ACC(object);
        if (object->flag6D == 0) {
            object->flags &= 0x7FFF;
        } else {
            D_800E3DE8[0] = (u8 *)object - 0x20;
        }
        break;
    }
}
