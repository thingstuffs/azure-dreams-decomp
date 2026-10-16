#ifndef DUNGEON_OVL_191E87C_H
#define DUNGEON_OVL_191E87C_H
#include "common.h"
#include "m2c_compat.h"
/* cfail-repair: tf7-phase1-cache-v3 */

typedef struct Row_818FE800_Target {
    u8 pad0[3];
    u8 field3;
    u8 pad4[0x22];
    u8 field26;
} Row_818FE800_Target;

#ifdef __mips__






#endif

/* Roll the target's 0x3 resistance against the attack level: on a hit, halve its 0x26 counter and run effect 0x53 with that amount, otherwise apply the miss record and run 0x53 with -1. */
s32 func_800990FC(void);
s32 func_80099194(void *src, void *dst);
s32 func_80099290(void *byte_ptr);
s32 dungeonWriteTextByteAndAdvance(s8 value, void *dest);
s32 func_80099734(void *record, void *out);
s32 dungeonAdjustSourceValueAndFinalize(void *, void *);
s32 dungeonTryTriggerTargetRecordEffect(void *, s32);
s32 func_800A5720(void *text);
s32 func_800A6D30(void);
s32 createActorValuePopup(s32 flags, void *source_data, s16 value, u16 callback_mode);
void dungeonUpdateEffectParticlesAndCleanup(void);
void func_80024658(void);
void func_80024674(void);
void func_8002469C(void);
void cardBootRefreshFiveSlotSelection(void);
void func_800250A4(void);
void func_8002536C(void);
void func_8002561C(void);
void func_80025BB0(void);
void func_80025CDC(void);
void func_80025D20(void);
void func_80025DF4(void);
void func_80025D90(void);
extern M2C_UNK D_800E2096;
extern M2C_UNK D_800E20BC;
s32 func_8002407C(Row_818FE800_Target *target, s32 level);
#endif
