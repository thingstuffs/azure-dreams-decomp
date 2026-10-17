#include "common.h"

extern void townInitializeObjectAndRegisterSlot(void *, s32, s32, s32, s32, s32);
extern u8 D_800D5DD4[];
extern u8 D_800D5DDC[];
extern u8 D_800D5E04[];
extern u8 D_800D5E08[];

void initialize_scene_slot_53(void *object, s32 unused, void *context)
{
    townInitializeObjectAndRegisterSlot(object, 53, (s32)D_800D5E04, (s32)D_800D5E08, (s32)D_800D5DD4, (s32)D_800D5DDC);
}
