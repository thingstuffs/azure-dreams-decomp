#include "common.h"
#include "shared/game_work.h"

typedef struct {
    u8 pad00[0x8c];
    void *field8c;
} Obj0;

typedef struct {
    u8 pad00[0x2c];
    u8 *table2c;
} Obj2;

typedef struct {
    u8 pad00[0x1c];
    u32 flags1c;
    u8 pad20[5];
    u8 flag25;
    u8 pad26[4];
    s16 value2a;
    u8 pad2c[0x1c];
    u8 kind48;
} Obj3;

extern u8 D_801664BC[];
extern s32 D_80169DC4;
extern s32 D_80169DCC;
extern s32 D_80169DD4;
extern u8 D_80169E24[];
extern u8 D_80169E2C[];
extern u8 D_80169E34[];
extern u8 D_80169E54[];
extern u8 D_80169E5C[];
extern u8 D_80169E64[];

extern void func_80047784(Obj2 *, u8, s32);
extern s32 func_800AC82C(Obj0 *, void *, Obj2 *, Obj3 *);
extern s32 func_800AD9B4(Obj2 *, Obj3 *);

/* Updates the direction table and selected entry for entity kinds 13 through 15. */
void func_801699A0(Obj0 *owner, void *context, Obj2 *sprite_arg, Obj3 *entity_arg)
{
    Obj2 *sprite = sprite_arg;
    Obj3 *entity = entity_arg;
    u32 selected_table;
    u32 current_table;
    u8 kind;
    s32 direction_index;

    kind = entity->kind48;
    switch (kind) {
    case 13:
        if ((entity->flags1c & 0x200) != 0 || entity->flag25 == 0) {
            current_table = (u32)sprite->table2c;
            selected_table = (u32)D_80169E54;
        } else {
            current_table = (u32)sprite->table2c;
            selected_table = (u32)D_80169E24;
        }
        if (current_table != selected_table) {
            *(u32 *)((u8 *)sprite + 0x2c) = selected_table;
            direction_index = (gameWork.view.viewAngle + entity->value2a + 0x100) >> 9;
            func_80047784(sprite, *(u8 *)((direction_index & 7) + selected_table), 0);
        }
        break;
    case 14:
        if ((entity->flags1c & 0x200) != 0 || entity->flag25 == 0) {
            current_table = (u32)sprite->table2c;
            selected_table = (u32)D_80169E5C;
        } else {
            current_table = (u32)sprite->table2c;
            selected_table = (u32)D_80169E2C;
        }
        if (current_table != selected_table) {
            *(u32 *)((u8 *)sprite + 0x2c) = selected_table;
            direction_index = (gameWork.view.viewAngle + entity->value2a + 0x100) >> 9;
            func_80047784(sprite, *(u8 *)((direction_index & 7) + selected_table), 0);
        }
        break;
    case 15:
        if ((entity->flags1c & 0x200) != 0 || entity->flag25 == 0) {
            current_table = (u32)sprite->table2c;
            selected_table = (u32)D_80169E64;
        } else {
            current_table = (u32)sprite->table2c;
            selected_table = (u32)D_80169E34;
        }
        if (current_table != selected_table) {
            *(u32 *)((u8 *)sprite + 0x2c) = selected_table;
            direction_index = (gameWork.view.viewAngle + entity->value2a + 0x100) >> 9;
            func_80047784(sprite, *(u8 *)((direction_index & 7) + selected_table), 0);
        }
        break;
    default:
        break;
    }
    if (func_800AC82C(owner, context, sprite, entity) != 0) {
        if ((func_800AD9B4(sprite, entity) << 16) > 0) {
            owner->field8c = D_801664BC;
        }
        return;
    }

    switch (entity->kind48) {
    case 13:
        if (sprite->table2c != D_80169E54 ||
            (entity->flags1c & 0x208) != 0) {
            return;
        }
        *(u32 *)((u8 *)sprite + 0x2c) = (u32)&D_80169DC4;
        direction_index = (gameWork.view.viewAngle + entity->value2a + 0x100) >> 9;
        func_80047784(sprite, *(u8 *)((direction_index & 7) + (u32)&D_80169DC4), 0);
        return;
    case 14:
        if (sprite->table2c != D_80169E5C ||
            (entity->flags1c & 0x208) != 0) {
            return;
        }
        *(u32 *)((u8 *)sprite + 0x2c) = (u32)&D_80169DCC;
        direction_index = (gameWork.view.viewAngle + entity->value2a + 0x100) >> 9;
        func_80047784(sprite, *(u8 *)((direction_index & 7) + (u32)&D_80169DCC), 0);
        return;
    case 15:
        if (sprite->table2c != D_80169E64 ||
            (entity->flags1c & 0x208) != 0) {
            return;
        }
        *(u32 *)((u8 *)sprite + 0x2c) = (u32)&D_80169DD4;
        direction_index = (gameWork.view.viewAngle + entity->value2a + 0x100) >> 9;
        func_80047784(sprite, *(u8 *)((direction_index & 7) + (u32)&D_80169DD4), 0);
        return;
    default:
        return;
    }
}
