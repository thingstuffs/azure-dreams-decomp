#include "common.h"
#include "shared/object_node.h"
#include "shared/entity_objects.h"
#include "shared/dungeon_status.h"

typedef struct SubA_800B4204 {
    u8 pad0[2];
    s16 f2;
    u8 pad4[2];
    s16 f6;
    u8 pad8[2];
    s16 fA;
} SubA_800B4204;

typedef struct SubB_800B4204 {
    u8 pad0[6];
    u16 f6;
    u8 pad8[4];
    u32 fC;
    u16 f10;
    u8 pad12[2];
    u16 f14;
    u8 pad16[6];
    u16 f1C;
    u16 f1E;
} SubB_800B4204;

typedef struct Obj_800B4204 {
    u8 pad0[8];
    SubA_800B4204 *sub1;
    SubB_800B4204 *sub2;
    void (*stateFn)(void *);
    u8 pad14[0x20 - 0x14];
    void *owner;
} Obj_800B4204;

typedef struct EntityHdr {
    u8 pad[0x88];
    u16 f88;
} EntityHdr;

extern u8 D_80079444[];
extern s16 D_800DCE66[5];

extern void * func_8003FD64();
extern s32 func_8004491C();
extern s32 func_80045C34();
extern void update_familiar_selection_marker(void *state, void *position_arg, void *marker_arg);
extern void func_8003DB94();
extern s32 select_nearby_target_and_initialize_slot();

/* Creates and initializes a display object attached to the entity. */
void *create_familiar_selection_marker(EntityHdr **entity_ref) {
    Obj_800B4204 *object;
    SubA_800B4204 *transform;
    SubB_800B4204 *sprite;
    u8 *owner_data;

    object = func_8003FD64(18, &D_80083498.next);
    if (object != 0) {
        owner_data = (u8 *)object + 0x20;
        func_8004491C(object, (void *)func_80045C34);
        object->stateFn = update_familiar_selection_marker;

        transform = object->sub1;
        sprite = object->sub2;
        transform->f2 = ((u16)D_80083780.x.w.i);
        transform->f6 = ((u16)D_80083780.y.w.i);
        transform->fA = (*entity_ref)->f88;
        func_8003DB94(sprite, D_80079444, 0);

        {
            u32 color;
            u16 flags;

            color = 0x2c808080;
            sprite->f1E = 256;
            sprite->f1C = 256;
            sprite->f10 = 32;
            flags = sprite->f14;
            sprite->fC = color;
            sprite->f6 = 4;
            sprite->f14 = flags | 0xC;
            *(s16 *)(owner_data + 0xE) = 4;
            object->owner = entity_ref;

            g_dungeon_status.unk_0C = object;
            select_nearby_target_and_initialize_slot(object, transform, 8, D_800DCE66[0]);
        }
    }

    return (void *)object;
}
