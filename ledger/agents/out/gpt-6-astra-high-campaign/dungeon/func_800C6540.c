#include "common.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_800CBCA0_0_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800CBCA0_0_pre;   /* the 0x14 bytes before arg0 in func_800CBCA0, addressed as arg0[-1] */


typedef struct S_800CBCA0_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800CBCA0_1;   /* parent in func_800CBCA0 */



extern void func_80094E34(void);
extern void func_80099844(void *, void *);
extern void func_800A6508(void);
extern s32 func_800A6D30(void *, s32, s32, s32);
extern s32 func_800CBB98(u8, u8, s16, void *);
extern u8 D_800E1AE6[];
extern u8 D_800E3D40;

/* Checks an entity's flags and random roll before attempting its parent-based action. */
s32 func_800CBCA0(void *entity, s32 input_a, s32 input_b, s32 input_c)
{
    S_800CBCA0_1 *parent;
    s32 action_result;
    s32 roll;
    register s32 divisor ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 random_value;
    void *rng_entity = entity;

    if (((Rec_D_800E3D7C *)entity)->unk_10.at03_u8.v == 0) {
        goto check_global;
    }
    if (!(((Rec_D_800E3D7C *)entity)->unk_14.as_s32 & 0x4000)) {
        goto check_global;
    }
    ASM_KEEP(entity);   /* UNRESOLVED C shape (pin): removing it flips a branch polarity; the source shape that makes it unnecessary has not been found */
    roll = 1;
    goto done;

check_global:
    if (D_800E3D40 == 0) {
        random_value = (u16)func_800A6D30(rng_entity, input_a, input_b, input_c);
        divisor = ((Rec_D_800E3D7C *)entity)->unk_00.at03_u8.v;
        if (divisor != 0) {
            roll = divisor;
            ASM_KEEP(roll);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            divisor = random_value % roll;
            roll = divisor;
            goto value_ready;
        }
    }
    roll = 0;
value_ready:

    if (roll < 0x30) {
        parent = ((S_800CBCA0_0_pre *)entity)[-1].unk_00;
        action_result = func_800CBB98(parent->unk_24,
                               parent->unk_25,
                               ((Rec_D_800E3D7C *)entity)->unk_88.as_s16, entity);
        if (action_result != 0) {
            if (((Rec_D_800E3D7C *)entity)->unk_10.at03_u8.v == 0) {
                func_80094E34();
                func_80099844(entity, D_800E1AE6);
            }
        }
        return action_result != 0;
    }

    if (((Rec_D_800E3D7C *)entity)->unk_10.at03_u8.v == 0) {
        func_800A6508();
    }
    return 1;

done:
    return roll;
}
