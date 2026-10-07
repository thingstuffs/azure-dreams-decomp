#include "common.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"

typedef struct {
    u8 pad0[0x96];
    u16 countdown;
    u8 pad98[3];
    u8 state;
    u8 pad9C[8];
    u16 timer;
} EffectState;

typedef struct {
    u8 pad0[4];
    s8 type;
    u8 pad5[7];
    s32 value;
    u16 field10;
    u16 field12;
    u16 flags;
    u8 pad16[0xE];
    u8 x;
    u8 y;
    u8 pad26[6];
    u8 *table;
} Entity;

typedef struct {
    u8 pad0[0x14];
    s32 field14;
    u8 pad18[4];
    s32 flags;
    u8 pad20[0xA];
    s16 angle;
} Object;

extern void func_80047784(Entity *, u8, s32);
extern void func_8009A028(Object *);
extern void func_8009A3D0(u8, u8, s32);
extern void func_800A2FE0(Object *);
extern void func_800A32A4(Object *);
extern void func_800A56E0(s32);
extern void func_800ACF88(void *);

extern u8 D_80175AA4[];

/* Advances the entity fade effect, updates its countdown, and cleans up when fading ends. */
void func_801732EC(EffectState *effect, void *unused, Entity *entity, Object *object) {
    s32 state;
    s32 object_status;
    s32 status_mask;
    s32 direction_index;
    s32 fade_delta;
    s32 strength;
    s16 countdown;
    u16 timer;
    u8 x;
    u8 y;

    state = effect->state;
    switch (state) {
    case 0:
        if (*(s16 *)(((u8 *)(&dungeonStatus)) + 0xA) != 0) {
            return;
        }
        effect->state = 1;
                        /* fallthrough */
    case 1:
        object_status = object->field14;
        if (object_status & 0x4000) {
            status_mask = object_status & 0x20000000;
            if (status_mask == 0) {
                func_800ACF88(object);
            }
        }
        func_800A56E0(0x805);
        entity->field10 = 0x20;
        entity->flags |= 0xC;
        entity->field12 -= 0x80;
        object->flags |= 0x10000000;
        entity->value = 0x808080;
        effect->state++;
        return;
    case 2:
        entity->value += 0xFFF7F7F8;
        if (!(entity->flags & 0x6000)) {
            return;
        }
        object->flags |= 0x10000000;
        entity->table = D_80175AA4;
        effect->timer = 0x80;
        effect->countdown = 0;
        direction_index = ((gameWork.view.viewAngle + object->angle + 0x100) >> 9) & 7;
        func_80047784(entity, entity->table[direction_index], 0);
        effect->state++;
        return;
    case 3:
        fade_delta = 0xFFF7F7F8;
        object->flags |= 0x10000000;
        entity->value += fade_delta;
        if ((entity->field10 == 0x20) && ((u8)entity->value < 0x40)) {
            entity->field10 = 0x60;
            entity->value = 0xF0F0F0;
        }
        countdown = effect->countdown - 1;
        effect->countdown = countdown;
        if (countdown >= 0) {
            entity->flags |= 0x800;
        } else {
            entity->flags &= 0xF7FF;
            timer = effect->timer + 0x60;
            effect->timer = timer;
            effect->countdown = (u16)((s32)(timer << 16) >> 24);
        }
        if ((entity->type == 2) && (entity->flags & 0x1000)) {
            direction_index = ((gameWork.view.viewAngle + object->angle + 0x100) >> 9) & 7;
            func_80047784(entity, entity->table[direction_index], 0);
        }
        if ((u8)entity->value < 0x11) {
            if (((s32)dungeonStatus.unk_10) == (s32)((u8 *)object - 0x20)) {
                *(s32 *)&dungeonStatus.unk_10 &= 0x7FFFFFFF;
            }
            func_800A2FE0(object);
            func_800A32A4(object);
            x = entity->x;
            y = entity->y;
            strength = 0x3000;
            if (object->flags & 0x2000) {
                strength = 0x300;
            }
            func_8009A3D0(x, y, strength);
            func_8009A028(object);
            *(u16 *)((u8 *)object - 2) |= 0x8000;
            objectFlagBlock.flags |= 0x8000;
        }
        return;
    default:
        return;
    }
}
