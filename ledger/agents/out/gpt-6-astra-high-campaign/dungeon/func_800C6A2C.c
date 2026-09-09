#include "common.h"

typedef struct S_800CC18C_0 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x13];
    u8 unk_1B;
    u8 pad_1C[0xF];
    u8 unk_2B;
} S_800CC18C_0;   /* arg0 in func_800CC18C; pointer addresses record offset 0x18 */


extern u8 D_800E3D40[];
extern u8 D_800E1BDA[];
extern s32 func_80099844(void *, void *);
extern s32 func_800A56E0(u32);
extern s32 func_800A6508(void);
extern s32 func_800A6D30(void *, s32, s32, s32);
extern s32 func_800AA5E4(void *, s32, s32, void *);

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

/* Resolve a ranged random check, apply its effects, and return the outcome. */
s32 func_800CC18C(void *entity, s32 forwarded_1, s32 forwarded_2, s32 forwarded_3) {
    register s32 roll ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    register s32 random_value ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 range;
    register s32 remainder ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s16 outcome;
    s16 final_outcome;
    s32 feedback_kind;
    s32 feedback_or_result;

    outcome = 0;
    if (D_800E3D40[0] == 0) {
        random_value = func_800A6D30(entity, forwarded_1, forwarded_2, forwarded_3) & 0xFFFF;
        range = ((S_800CC18C_0 *)((u8 *)entity - 0x18))->unk_1B;
        if (range != 0) {
            roll = range;
            ASM_KEEP(roll);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            remainder = random_value % roll;
            roll = remainder;
            goto value_ready;
        }
    }
    roll = 0;
value_ready:
    if (roll < 0x40) {
        func_800AA5E4(entity, ((S_800CC18C_0 *)((u8 *)entity - 0x18))->unk_00, ((S_800CC18C_0 *)((u8 *)entity - 0x18))->unk_04, entity);
        func_800A56E0(0x705);
        if (D_800E3D40[0] != 0) {
            outcome = -1;
        }
        feedback_kind = ((S_800CC18C_0 *)((u8 *)entity - 0x18))->unk_2B == 0;
    } else {
        outcome = 1;
        feedback_kind = (((S_800CC18C_0 *)((u8 *)entity - 0x18))->unk_2B == 0) * 2;
    }
    feedback_or_result = feedback_kind;
    if (feedback_or_result != 0) {
        if (feedback_or_result == 1) {
            func_80099844(entity, &D_800E1BDA);
        } else {
            func_800A6508();
        }
    }
    final_outcome = outcome;
    if (final_outcome < 0) {
        return 0;
    }
    if (final_outcome != 0) {
        feedback_or_result = 1;
    } else {
        feedback_or_result = -1;
    }
    return feedback_or_result;
}
