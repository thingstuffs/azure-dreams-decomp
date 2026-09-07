#include "common.h"
#include "m2c_compat.h"

void func_800247B8(void) __attribute__((noreturn));  /* extern -- frame-live dispatcher */
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 rand();                                /* extern */
extern u8 D_80024674[];
extern u8 D_80025214[];
extern u8 D_80045340[];

typedef struct S_818A4ED0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_818A4ED0_0;   /* temp_v0 in func_818A4ED0 */

typedef struct S_818A4ED0_1 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_818A4ED0_1;   /* temp_s0 in func_818A4ED0 */

typedef struct S_818A4ED0_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_818A4ED0_2;   /* temp_s0_2 in func_818A4ED0 */

typedef struct S_818A4ED0_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_818A4ED0_3;   /* arg1 in func_818A4ED0 */

/* Creates an object at the supplied position with a randomized rotation. */
s32 func_818A4ED0(s32 object_param, S_818A4ED0_3 *spawn_position) {
    s32 rotation_rng;
    S_818A4ED0_1 *render_state;
    S_818A4ED0_2 *position;
    S_818A4ED0_0 *object;

    object = func_8003FC64(0x212);
    if (object != NULL) {
        object->unk_10 = D_80024674;
        object->unk_20 = object_param;
        render_state = object->unk_0C;
        render_state->unk_08 = D_80025214;
        render_state->unk_12 = 0x7E07;
        render_state->unk_0E = 0;
        render_state->unk_0D = 0;
        render_state->unk_0C = 0;
        render_state->unk_10 = (u16) (render_state->unk_10 | 0x60);
        render_state->unk_14 = (u16) (render_state->unk_14 | 0x10C);
        rotation_rng = rand();
        render_state->unk_1A = (s16) (rotation_rng % 0x1000);
        render_state->unk_1E = 0;
        render_state->unk_1C = 0;
        func_8004491C(object, D_80045340);
        position = object->unk_08;
        {
            s32 unused_rng;
            unused_rng = rand();
        }
        position->unk_02 = (u16) spawn_position->unk_02;
        position->unk_06 = (u16) spawn_position->unk_06;
        {
            u16 final_z = spawn_position->unk_0A;
#ifndef NON_MATCHING
            __asm__ __volatile__("" : : : "$2");
#endif
            {
                register s32 object_result ASM_REG("$2");   /* MATCH pin: retail basic-block layout depends on it */
                object_result = (s32) object;
                ASM_KEEP(object_result);   /* MATCH pin: retail basic-block layout depends on it */
                position->unk_0A = final_z;
                func_800247B8();
            }
        }
    }
    {
        register s32 failure_result ASM_REG("$2");   /* MATCH pin: retail basic-block layout depends on it */
        failure_result = 0;
        ASM_KEEP(failure_result);   /* MATCH pin: retail schedule: same instructions, different order without it */
        return failure_result;
    }
}
