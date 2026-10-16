/* Relink of matched dungeon/func_80CBF800; every changed retail word is a paired relocation. */
#define D_80170F20 D_8015EF20
#define D_80173B98 D_80161B98
#include "common.h"

extern s32 dungeonUpdateActorHopAndGrow(void);
extern u8 D_8015EF20;
extern u8 D_80161B98;

/* Selects object data from its variant flag when the condition is met. */
void func_80161000(void *object)
{
    u8 *selected_data;

    if (dungeonUpdateActorHopAndGrow() != 0) {
        if (*(u8 *)((u8 *)object + 0xA7) != 0) {
            selected_data = &D_80161B98;
        } else {
            selected_data = &D_8015EF20;
        }
        *(u8 **)((u8 *)object + 0x8C) = selected_data;
    }
}
