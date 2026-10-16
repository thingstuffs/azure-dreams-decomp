#include "modules/trap_effects_candidate.h"
#include "common.h"
#include "shared/entity.h"


extern void dungeonAdjustSourceValueAndFinalize();
extern void func_800A6508();
extern void * dungeonSpawnRandomizedParticleBurst();
extern s32 dungeonRollThresholdEffectVariantA();
extern void dungeonWrapPositionAndSetStateValue();
extern s32 D_800DCF1C;
extern M2C_UNK D_800E1C14;



typedef struct S_800CD384_0_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800CD384_0_pre;   /* the 0x14 bytes before object in dungeonAttemptTrapRequestEightSlots, addressed as object[-1] */


typedef struct S_800CD384_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800CD384_1;   /* entry in dungeonAttemptTrapRequestEightSlots */

/* Run the 8-slot request for the object with the budget the global mode picks; on refusal give the fallback cue, otherwise apply the effect and raise the tile marker unless the owning entry is flagged. */
s32 dungeonAttemptTrapRequestEightSlots(void *object) {
    s32 amount;
    S_800CD384_1 *entry;

    amount = 0x40;
    if (D_800E3D40 != 0) {
        amount = 0x400;
    }
    if (dungeonRollThresholdEffectVariantA(object, amount, 8) == 0) {
        if (((EntityRec *)object)->flags14 & 0x4000) {
            func_800A6508();
            return 1;
        }
        return 1;
    }
    dungeonAdjustSourceValueAndFinalize(object, &D_800E1C14);
    if ((*(u8 *)((u8 *)&((EntityRec *)object)->unk_10 + 3)) == 0) {
        dungeonWrapPositionAndSetStateValue(D_800DCF1C);
    }
    entry = ((S_800CD384_0_pre *)object)[-1].unk_00;
    if (!(entry->unk_14 & 0x8000)) {
        dungeonSpawnRandomizedParticleBurst((entry->unk_24 << 6) | 0x20,
                      (entry->unk_25 << 6) | 0x20,
                      ((EntityRec *)object)->unk_88, 0x802080, 0x20, 1);
    }
    return 1;
}
