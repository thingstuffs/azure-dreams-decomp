/* Relink of matched dungeon/func_80F0C3B8; every changed retail word is a paired relocation. */
#define D_80170F74 D_80158F74
#include "common.h"
#include "shared/dungeon_status.h"

extern void func_80044A50(void *);
extern void dungeonRetireTrackedEffectById(void *);
extern void dungeonReduceActorFoodMeter(void *, s32);

extern u8 D_80158F74[];

/* Dims the effect and clears its object and owner state when flagged. */
void func_8015BBB8(void *effect, s32 unused, void *primitive, void *owner)
{
    u8 intensity;
    void *effect_object;

    if (*(u8 *)((u8 *)effect + 0x9B) == 0) {
        intensity = *(u8 *)((u8 *)primitive + 0xC) - 0x10;
        *(u8 *)((u8 *)primitive + 0xE) = intensity;
        *(u8 *)((u8 *)primitive + 0xD) = intensity;
        *(u8 *)((u8 *)primitive + 0xC) = intensity;
        if (*(u16 *)((u8 *)primitive + 0x14) & 0xE000) {
            effect_object = (u8 *)effect - 0x20;
            func_80044A50(effect_object);
            dungeonRetireTrackedEffectById(effect_object);
            dungeonReduceActorFoodMeter(owner, 0x800);
            dungeonStatus.unk_0A--;
            *(u32 *)((u8 *)primitive + 0xC) = 0;
            *(u8 *)((u8 *)owner + 0x6D) = 0;
            *(u16 *)((u8 *)owner + 0x46) &= 0x7FFF;
            *(void **)((u8 *)effect + 0x8C) = D_80158F74;
        }
    }
}
