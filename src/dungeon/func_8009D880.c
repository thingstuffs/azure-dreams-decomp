#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

s32 func_8003AD08();                        /* extern */
s32 get_unused_text_buffer();                                /* extern */
s32 expand_text_control_codes();                  /* extern */
extern void * func_80099290(s8 *byte_ptr);
s32 append_entity_display_text();                     /* extern */
s32 distribute_experience_awards();                          /* extern */
s32 display_text_with_fullwidth_adjustment();                         /* extern */
extern void *D_8007359C;

extern M2C_UNK D_800E09CD;
extern M2C_UNK D_800E09D9;
extern M2C_UNK D_800E09E6;
extern M2C_UNK D_800E09EE;
extern M2C_UNK D_800E09FB;


typedef struct S_800A2FE0_2 {
    u8 pad_00[0x13];
    s8 unk_13;
} S_800A2FE0_2;   /* targetState in distribute_experience_and_report_gains */

typedef struct S_800A2FE0_3 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
} S_800A2FE0_3;   /* targetData in distribute_experience_and_report_gains */

typedef struct S_800A2FE0_4 {
    u8 pad_00[0x4];
    s32 * unk_04;
} S_800A2FE0_4;   /* globalData in distribute_experience_and_report_gains */

void distribute_experience_and_report_gains(EntityRec *entity) {
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
        result = distribute_experience_awards(entity);
    }
    flags14 = entity->flags14;
    if (!(flags14 & 0x20000000)) {
        if (!(flags14 & 0x4000)) {
            targetState = entity->target;
            if ((targetState != NULL) && (targetState->unk_13 >= 0)) {
                currentValue = get_unused_text_buffer();
                func_80099290(expand_text_control_codes(D_80089000, append_entity_display_text(entity, expand_text_control_codes(&D_800E09CD, currentValue))));
                display_text_with_fullwidth_adjustment(currentValue);
            }
        }
        if ((result != 0) && (targetData = entity->target, (targetData != NULL))) {
            if (targetData->unk_14 & 0x4000) {
                if (!(entity->flags14 & 0x4000)) {
                    selectionInputThird = get_unused_text_buffer();
                    globalData = D_8007359C;
                    currentValue = selectionInputThird;
                    func_80099290(expand_text_control_codes(&D_800E09E6, func_8003AD08(result, expand_text_control_codes(&D_800E09D9,
                        expand_text_control_codes(globalData->unk_04, currentValue)))));
                } else {
                    return;
                }
            } else {
                if (targetData->unk_13 < 0) {
                    return;
                }
                selectionInputSecond = get_unused_text_buffer();
                currentValue = selectionInputSecond;
                func_80099290(expand_text_control_codes(&D_800E09FB, func_8003AD08(result, expand_text_control_codes(&D_800E09EE,
                    append_entity_display_text(entity->target, currentValue)))));
            }
            display_text_with_fullwidth_adjustment(currentValue);
        }
    }
}

/* MECHANISM: The seed's 0x20 frame, s1/s2/s0 roles, CFG, and 124-word shape were already exact.
   The middle get_unused_text_buffer result stays guarded in v0 through the D_8007359C load, then copies
   to guarded s0 in that load-delay slot; this fixes both equal-length register substitutions. */
