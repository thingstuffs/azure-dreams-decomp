#include "common.h"
#include "shared/entity.h"

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
extern s32 func_800A6D30(void);
extern s32 func_800CBB98(u8, u16, s16, void *);
extern u8 D_800E1AE6[];
extern u8 D_800E3D40;

/* Checks an entity's flags and random roll before attempting its parent-based action. */
s32 func_800CBCA0(void *entity, s32 input_a, s32 input_b, s32 input_c)
{
    S_800CBCA0_1 *parent;
    s32 action_result;
    s32 roll;
    s32 divisor;
    s32 random_value;
    void *rng_entity = entity;

    if ((*(u8 *)((u8 *)&((EntityRec *)entity)->unk_10 + 3)) != 0) {
        if (((EntityRec *)entity)->flags14 & 0x4000) {
            roll = 1;
            return roll;
        }
    }
    if (D_800E3D40 == 0) {
        random_value = (u16)func_800A6D30();
        if ((*(u8 *)((u8 *)&((EntityRec *)entity)->x + 3)) != 0) {
            divisor = random_value % (*(u8 *)((u8 *)&((EntityRec *)entity)->x + 3));
            goto value_ready2;
        }
    }
    roll = 0;
    goto value_ready;
value_ready2:
    roll = divisor;
value_ready:

    if (roll < 0x30) {
        parent = ((S_800CBCA0_0_pre *)entity)[-1].unk_00;
        action_result = func_800CBB98(parent->unk_24,
                               parent->unk_25,
                               ((EntityRec *)entity)->unk_88, entity);
        if (action_result != 0) {
            if ((*(u8 *)((u8 *)&((EntityRec *)entity)->unk_10 + 3)) == 0) {
                func_80094E34();
                func_80099844(entity, D_800E1AE6);
            }
        }
    } else {
        if ((*(u8 *)((u8 *)&((EntityRec *)entity)->unk_10 + 3)) == 0) {
            func_800A6508();
        }
        return 1;
    }
    return action_result != 0;
}
