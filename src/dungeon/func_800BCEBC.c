#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"

typedef struct Entity {
    u8 pad[0x13];
    u8 unk_13;
    u32 flags;
    u8 pad2[0x110 - 0x18];
    s32 unk_110;
} Entity;

extern s32 D_80012090;
extern s16 D_8008146C;
extern u8 D_80089384[];
extern u8 D_800E15FE[];
extern u8 D_800E1677[];

s32 func_80033BC0(s32);
void func_8008D330(Entity *, void *, void *, Entity *);
void func_80098B38(s32);
s32 func_800990FC(void);
s32 func_80099194(void *, s32);
void func_80099290(s32);
s32 func_80099368(s32, s32);
s32 func_80099734(Entity *, s32);
void func_800997FC(void *);
void func_800A5720(s32);
void func_800A5F38(Entity *, s32);
void func_800A63B8(Entity *, s32, s16);
s32 func_800C2C7C(Entity *);

/* Handles an item's effect on an entity and updates the pending action count. */
s32 func_800C261C(Entity *entity, s32 item, s16 action_type) {
    if (entity == ((Entity *)D_800E3D7C)) {
        entity->unk_110 = item;
        func_8008D330(entity, ((u8 *)(&D_80083780)), ((u8 *)(&D_80082E80)), entity);
        return 0;
    }
    if (entity->flags & 0x4000) {
        if ((u32)(entity->unk_13 - 3) < 0x2B) {
            if (D_80012090 == 0 && D_8008146C == 0x28 && func_80033BC0(0xA2) == 0) {
                DungeonGlobalStatus *counter;
                func_800997FC(D_800E15FE);
                counter = &dungeonStatus;
                (*(u16 *)&counter->unk_0A)--;
                func_80098B38(item);
                return 1;
            }
            if (func_800C2C7C(entity) != 0) {
                DungeonGlobalStatus *counter;
                func_80098B38(item);
                counter = &dungeonStatus;
                (*(u16 *)&counter->unk_0A)--;
                return 1;
            }
            return 0;
        }
        {
            s32 original_value;
            s32 current_value;
            s32 adjusted_value;

            adjusted_value = func_80099734(entity, current_value = func_800990FC());
            original_value = current_value;
            current_value = adjusted_value;
            func_80099290(func_80099194(D_80089384, func_80099368(item, func_80099194(D_800E1677, current_value))));
            func_800A5720(original_value);
            func_800A5F38(entity, item);
        }
        return 1;
    }
    if ((u32)(entity->unk_13 - 3) < 0x2B) {
        if (func_800C2C7C(entity) != 0) {
            DungeonGlobalStatus *counter = &dungeonStatus;
            (*(u16 *)&counter->unk_0A)--;
            return 1;
        }
        return 0;
    }
    func_800A63B8(entity, item, action_type);
    {
        DungeonGlobalStatus *counter = &dungeonStatus;
        (*(u16 *)&counter->unk_0A)--;
    }
    return 1;
}
