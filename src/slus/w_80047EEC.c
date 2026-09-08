#include "common.h"

typedef struct {
    void *entry;
    u16 pad4;
    s16 id;
} S_80047EEC_D8;

extern S_80047EEC_D8 D_80083D08[6];
extern u8 D_8014A000[];

extern s32 func_80047C60(void *a0);
extern void *func_80047AB0(void *a0, s32 a1, s32 a2, s32 a3, void *a4);

/* Registers an entity and its type in three consecutive slots, then starts loading. */
void func_80047EEC(s32 type_id, void *entity)
{
    s32 slot_index = func_80047C60(entity);

    D_80083D08[slot_index].entry = entity;
    D_80083D08[slot_index].id = (s16)type_id;

    D_80083D08[slot_index + 1].entry = entity;
    D_80083D08[slot_index + 1].id = (s16)type_id;

    D_80083D08[slot_index + 2].entry = entity;
    D_80083D08[slot_index + 2].id = (s16)type_id;

    {
        s32 load_offset = (slot_index * 3 + 0x1D2) * 64;
        func_80047AB0(entity, slot_index + 5, load_offset, 0xD, &D_8014A000);
    }
}
