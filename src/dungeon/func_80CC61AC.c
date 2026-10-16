/* Relink of matched dungeon/func_80CC01AC; every changed retail word is a paired relocation. */
#define D_80170F20 D_8016AF20
#define D_80173B98 D_8016DB98
#include "common.h"

extern s32 dungeonResolveActorFloorTrapOnce(void);
extern u8 D_8016AF20;
extern u8 D_8016DB98;

/* Selects object data from its variant flag when the query returns positive. */
void func_8016D9AC(void *object)
{
    u8 *selected_data;

    if (dungeonResolveActorFloorTrapOnce() > 0) {
        if (*(u8 *)((u8 *)object + 0xA7) != 0) {
            selected_data = &D_8016DB98;
        } else {
            selected_data = &D_8016AF20;
        }
        *(u8 **)((u8 *)object + 0x8C) = selected_data;
    }
}
