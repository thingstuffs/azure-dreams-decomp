#include "common.h"

#ifndef NULL
#define NULL 0
#endif


extern void *D_800E3D7C[];

extern void func_800A2D68(void *, s32);
extern void func_800B4C7C(s32, void *, s16, s32);


typedef struct S_800A2DB8_0 {
    u8 pad_00[0x6];
    union { u16 u; s16 s; } unk_06;   /* accessed as both */
    u8 pad_08[0x9];
    u8 unk_11;
    u8 pad_12[0x42];
    s32 unk_54;
    u8 pad_58[0x8];
    void * unk_60;
} S_800A2DB8_0;   /* arg0 in func_800A2DB8 */

typedef struct S_800A2DB8_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    u8 pad_14[0x40];
    s32 unk_54;
} S_800A2DB8_1;   /* initial_target in func_800A2DB8 */

typedef struct S_800A2DB8_2 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_800A2DB8_2;   /* slot in func_800A2DB8 */

typedef struct S_800A2DB8_3 {
    u8 pad_00[0x11];
    u8 unk_11;
    u8 pad_12[0x16];
    u8 unk_28;
} S_800A2DB8_3;   /* member in func_800A2DB8 */

typedef struct S_800A2DB8_4 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800A2DB8_4;   /* target in func_800A2DB8 */

typedef struct S_800A2DB8_5 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_800A2DB8_5;   /* (u8 *)D_800E3D7C[0] + index * 4 in func_800A2DB8 */

typedef struct S_800A2DB8_6 {
    u8 pad_00[0x3D7C];
    void * unk_3D7C;
} S_800A2DB8_6;   /* global_page in func_800A2DB8 */

typedef struct S_800A2DB8_7 {
    u8 pad_00[0x11];
    u8 unk_11;
    u8 pad_12[0x16];
    u8 unk_28;
} S_800A2DB8_7;   /* global_member in func_800A2DB8 */

typedef struct S_800A2DB8_8 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800A2DB8_8;   /* final_target in func_800A2DB8 */

/* Award experience to the target or its party and display experience popups. */
s32 func_800A2DB8(S_800A2DB8_0 *source)
{
    void *initial_target;
    void *target;
    S_800A2DB8_8 *final_target;
    S_800A2DB8_7 *global_member;
    S_800A2DB8_3 *member;
    u8 *member_slot;
    u8 *global_page;
    s32 recipient_count;
    register s32 member_index ASM_REG("$17");
    s32 level_delta;
    s32 award;
    s32 rounding_sum;
    s32 popup_code;
    s32 experience;
    s32 bonus_shift;

    initial_target = source->unk_60;
    experience = 0;
    if (initial_target == NULL) {
        goto done;
    }
    if (((S_800A2DB8_1 *)initial_target)->unk_13 < 0) {
        goto done;
    }

    experience = source->unk_06.u;
    if (((S_800A2DB8_1 *)initial_target)->unk_54 & 0x20) {
        experience *= 2;
    }

    recipient_count = 1;
    if (source->unk_54 & 0x40) {
        experience *= 2;
    }

    ASM_KEEP(recipient_count);
    member_index = recipient_count;
    member_slot = (u8 *)D_800E3D7C[0] + 4;
    do {
        member = ((S_800A2DB8_2 *)member_slot)->unk_AC;
        if ((member != NULL) && (member->unk_28 != 0)) {
            recipient_count++;
        }
        member_index--;
        member_slot -= 4;
    } while (member_index >= 0);

    rounding_sum = experience + recipient_count;
    target = source->unk_60;
    experience = (rounding_sum - 1) / recipient_count;

    if (((S_800A2DB8_4 *)target)->unk_14 & 0x4000) {
        member_index = 1;
        do {
            member = ((S_800A2DB8_5 *)((u8 *)D_800E3D7C[0] + member_index * 4))->unk_AC;
            if ((member != NULL) && (member->unk_28 != 0)) {
                level_delta = member->unk_11 - source->unk_11;
                award = experience;
                if (level_delta < 0) {
                    bonus_shift = (level_delta < 2) ^ 1;
                    award = experience + (experience >> bonus_shift);
                }
                func_800B4C7C(0x82, member, (s16)award, 1);
                func_800A2D68(member, award & 0xFFFF);
            }
            member_index--;
        } while (member_index >= 0);

        global_page = (u8 *)0x800E0000;
        global_member = ((S_800A2DB8_6 *)global_page)->unk_3D7C;
        if (global_member->unk_28 == 0) {
            return 0;
        }
        level_delta = global_member->unk_11 - source->unk_11;
        award = experience;
        if (level_delta < 0) {
            bonus_shift = (level_delta < 2) ^ 1;
            award = experience + (experience >> bonus_shift);
        }
        func_800A2D68(global_member, award & 0xFFFF);
        func_800B4C7C(0x82, ((S_800A2DB8_6 *)global_page)->unk_3D7C, (s16)award, 1);
        return award;
    }

    experience = source->unk_06.u;
    func_800A2D68(target, experience);
    final_target = source->unk_60;
    popup_code = 0x83;
    if (final_target->unk_14 & 0x2000) {
        popup_code = 0x82;
    }
    func_800B4C7C(popup_code, final_target, source->unk_06.s, 1);
done:
    return experience;
}
