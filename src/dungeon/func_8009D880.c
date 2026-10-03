#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

s32 func_8003AD08();                        /* extern */
s32 func_800990FC();                                /* extern */
s32 func_80099194();                  /* extern */
M2C_UNK func_80099290();                         /* extern */
s32 func_80099734();                     /* extern */
s32 func_800A2DB8();                          /* extern */
M2C_UNK func_800A5720();                         /* extern */
extern void *D_8007359C;
extern M2C_UNK D_80089000;
extern M2C_UNK D_800E09CD;
extern M2C_UNK D_800E09D9;
extern M2C_UNK D_800E09E6;
extern M2C_UNK D_800E09EE;
extern M2C_UNK D_800E09FB;


typedef struct S_800A2FE0_2 {
    u8 pad_00[0x13];
    s8 unk_13;
} S_800A2FE0_2;   /* targetState in func_800A2FE0 */

typedef struct S_800A2FE0_3 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
} S_800A2FE0_3;   /* targetData in func_800A2FE0 */

typedef struct S_800A2FE0_4 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
} S_800A2FE0_4;   /* globalData in func_800A2FE0 */

void func_800A2FE0(EntityRec *entity) {
    s32 selectionInputFirst;
    s32 selectionInputSecond;
    s32 currentValue;
    s32 selectionInputThird;
    s32 flagBits;
    s32 flags14;
    s32 result;
    s32 hasFlag;
    S_800A2FE0_4 *globalData;
    EntityRec *targetEntity;
    S_800A2FE0_2 *targetState;
    S_800A2FE0_3 *targetData;

    result = 0;
    targetEntity = entity->target;
    hasFlag = 0;
    if ((targetEntity != NULL) && (targetEntity->flags14 & 0x4000)) {
        flagBits = entity->flags14 & 0x4000;
        hasFlag = flagBits != 0;
    }
    if (hasFlag == 0) {
        result = func_800A2DB8(entity);
    }
    flags14 = entity->flags14;
    if (!(flags14 & 0x20000000)) {
        if (!(flags14 & 0x4000)) {
            targetState = entity->target;
            if ((targetState != NULL) && (targetState->unk_13 >= 0)) {
                do {
                    selectionInputFirst = func_800990FC();
                } while (0);
                func_80099290(func_80099194(&D_80089000, func_80099734(entity, func_80099194(&D_800E09CD, selectionInputFirst))));
                func_800A5720(selectionInputFirst);
            }
        }
        if ((result != 0) && (targetData = entity->target, (targetData != NULL))) {
            if (targetData->unk_14 & 0x4000) {
                if (!(entity->flags14 & 0x4000)) {
                    selectionInputThird = func_800990FC();
                    globalData = D_8007359C;
                    currentValue = selectionInputThird;
                    func_80099290(func_80099194(&D_800E09E6, func_8003AD08(result, func_80099194(&D_800E09D9,
                        func_80099194(globalData->unk_04, currentValue)))));
                } else {
                    return;
                }
            } else {
                if (targetData->unk_13 < 0) {
                    return;
                }
                selectionInputSecond = func_800990FC();
                currentValue = selectionInputSecond;
                func_80099290(func_80099194(&D_800E09FB, func_8003AD08(result, func_80099194(&D_800E09EE,
                    func_80099734(entity->target, currentValue)))));
            }
            func_800A5720(currentValue);
        }
    }
}

/* MECHANISM: The seed's 0x20 frame, s1/s2/s0 roles, CFG, and 124-word shape were already exact.
   The middle func_800990FC result stays guarded in v0 through the D_8007359C load, then copies
   to guarded s0 in that load-delay slot; this fixes both equal-length register substitutions. */
