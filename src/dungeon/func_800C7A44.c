#include "modules/trap_effects_candidate.h"
#include "common.h"
#include "shared/entity.h"


extern void dungeonAdjustSourceValueAndFinalize();
extern s32 func_800A56E0();
extern void func_800A6508();
extern void * dungeonSpawnRandomizedParticleBurst();
extern s32 dungeonRollChanceAndRunAction(void *record, s16 chance, s8 action);
extern void dungeonWrapPositionAndSetStateValue(s32);
extern s32 D_800DCF0C;
extern u8 D_800E1BF3[];



typedef struct S_800CD1A4_0_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800CD1A4_0_pre;   /* the 0x14 bytes before actor in dungeonRollTrapHitAndRaiseEvent520, addressed as actor[-1] */


typedef struct S_800CD1A4_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800CD1A4_1;   /* owner in dungeonRollTrapHitAndRaiseEvent520 */

/* Roll the actor's trap check; on a hit mark it, play the burst at the owner's tile and raise event 0x520. */
s32 dungeonRollTrapHitAndRaiseEvent520(void *actor) {
    s32 chance;
    S_800CD1A4_1 *owner;

    chance = 0x40;
    if (D_800E3D40 != 0) {
        chance = 0x400;
    }
    if (dungeonRollChanceAndRunAction(actor, chance, 0x10) == 0) {
        if ((*(u8 *)((u8 *)&((EntityRec *)actor)->unk_10 + 3)) == 0) {
            func_800A6508();
            return 1;
        }
        return 1;
    }
    dungeonAdjustSourceValueAndFinalize(actor, &D_800E1BF3);
    if ((*(u8 *)((u8 *)&((EntityRec *)actor)->unk_10 + 3)) == 0) {
        dungeonWrapPositionAndSetStateValue(D_800DCF0C);
    }
    owner = ((S_800CD1A4_0_pre *)actor)[-1].unk_00;
    if (!(owner->unk_14 & 0x8000)) {
        dungeonSpawnRandomizedParticleBurst((owner->unk_24 << 6) | 0x20,
                      (owner->unk_25 << 6) | 0x20,
                      ((EntityRec *)actor)->unk_88, 0x808080, 0x20, 0);
        func_800A56E0(0x520);
    }
    return 1;
}
