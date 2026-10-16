#include "common.h"

extern s32 dungeonResolveActorFloorTrapOnce(void);
extern u8 D_80170F20;
extern u8 D_80173B98;

/* Selects object data from its variant flag when the query returns positive. */
void dungeonSelectVariantObjectDataWhenPositive(void *object)
{
    u8 *selected_data;

    if (dungeonResolveActorFloorTrapOnce() > 0) {
        if (*(u8 *)((u8 *)object + 0xA7) != 0) {
            selected_data = &D_80173B98;
        } else {
            selected_data = &D_80170F20;
        }
        *(u8 **)((u8 *)object + 0x8C) = selected_data;
    }
}
