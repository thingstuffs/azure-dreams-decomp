#include "common.h"

typedef struct EntitySlot {
    u8 pad_00[6];
    u8 x;
    u8 y;
    u8 pad_08[4];
    void *entity;
    u8 pad_10[8];
} EntitySlot;

typedef struct Entity {
    u8 pad_00[0x1E];
    u16 flags;
} Entity;

typedef struct GlobalFlags {
    s32 value;
    s32 pad[2];
} GlobalFlags;

extern s32 D_800E3648[0x20];
extern EntitySlot D_800E39C8[0x20];
extern GlobalFlags D_800814A0;

extern void func_8009A3D0(u8 x, u8 y, s32 type);

void func_800B5F80(s32 index) {
    s32 slot_offset;
    EntitySlot *slot_base;
    EntitySlot *slot;
    Entity *entity;
    u16 entity_flags;
    s32 global_flags;

    slot_base = D_800E39C8;
    D_800E3648[index] = 0;
    ASM_SCHED_BARRIER();
    slot_offset = index * 0x18;
    
    slot = (EntitySlot *)((u8 *)slot_base + slot_offset);
    func_8009A3D0(slot->x, slot->y, 0x20);
    entity = slot->entity;
    if (entity != 0) {
        entity_flags = entity->flags;
        global_flags = D_800814A0.value;
        entity->flags = entity_flags | 0x8000;
        D_800814A0.value = global_flags | 0x8000;
        slot->entity = 0;
    }
}
