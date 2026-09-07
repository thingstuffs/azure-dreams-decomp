#include "common.h"

typedef long long s64;
typedef s32 M2C_UNK;

#ifndef NULL
#define NULL 0
#endif

typedef struct S_7FFE79F4_0_pre {
    u16 unk_00;
} S_7FFE79F4_0_pre;   /* the 0x2 bytes before arg0 in func_7FFE79F4, addressed as arg0[-1] */

typedef struct S_7FFE79F4_0 {
    u8 pad_00[0x16];
    u16 unk_16;
    u8 pad_18[0x6];
    u16 unk_1E;
    u8 pad_20[0x4];
    void * unk_24;
    u8 pad_28[0x14];
    u16 unk_3C;
    u16 unk_3E;
    u16 unk_40;
} S_7FFE79F4_0;   /* arg0 in func_7FFE79F4 */

typedef struct S_7FFE79F4_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_7FFE79F4_1;   /* arg1 in func_7FFE79F4 */

typedef struct S_7FFE79F4_2 {
    u8 pad_00[0x8];
    void * unk_08;
} S_7FFE79F4_2;   /* temp_a0 in func_7FFE79F4 */

typedef struct S_7FFE79F4_3 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    M2C_UNK * unk_10;
    u8 pad_14[0x2A];
    s16 unk_3E;
    s16 unk_40;
    u8 pad_42[0x6];
    s16 unk_48;
    s16 unk_4A;
    u8 pad_4C[0xC];
    u16 unk_58;
    u16 unk_5A;
} S_7FFE79F4_3;   /* temp_v0_2 in func_7FFE79F4 */

typedef struct S_7FFE79F4_4 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_7FFE79F4_4;   /* temp_s0 in func_7FFE79F4 */

typedef struct S_7FFE79F4_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_7FFE79F4_5;   /* ((S_7FFE79F4_2 *)temp_a0)->unk_08 in func_7FFE79F4 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

void *func_7003CF18();
s32 func_7006DC5C();
s32 func_7006DD28();
s32 func_700750E0();
M2C_UNK func_7010AE28();
extern s32 D_80086AD8;
extern u16 D_80094422;
extern M2C_UNK D_8010AA44;

/* Update the emitter position, spawn particles, and mark it for removal when its lifetime expires. */
void func_7FFE79F4(void *emitter, void *position, M2C_UNK init_arg) {
    register s32 product ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
    s32 spawn_count;
    u16 age;
    u16 life_left;
    void *parent;
    void *particle_pos;
    void *particle;

    parent = ((S_7FFE79F4_0 *)emitter)->unk_24;
    ((S_7FFE79F4_1 *)position)->unk_02 = (u16) (((S_7FFE79F4_5 *)(((S_7FFE79F4_2 *)parent)->unk_08))->unk_02 + ((S_7FFE79F4_0 *)emitter)->unk_3C);
    ((S_7FFE79F4_1 *)position)->unk_06 = (u16) (((S_7FFE79F4_5 *)(((S_7FFE79F4_2 *)parent)->unk_08))->unk_06 + ((S_7FFE79F4_0 *)emitter)->unk_3E);
    ((S_7FFE79F4_1 *)position)->unk_0A = (u16) (((S_7FFE79F4_5 *)(((S_7FFE79F4_2 *)parent)->unk_08))->unk_0A + ((S_7FFE79F4_0 *)emitter)->unk_40);
    age = ((S_7FFE79F4_0 *)emitter)->unk_16 + 1;
    ((S_7FFE79F4_0 *)emitter)->unk_16 = age;
    if ((s16) age < 0x14) {
        spawn_count = 0;
        do {
            particle = func_7003CF18(0x212);
            spawn_count += 1;
            if (particle != NULL) {
                func_7010AE28(particle, emitter, position, init_arg);
                ((S_7FFE79F4_3 *)particle)->unk_3E = 0x28;
                ((S_7FFE79F4_3 *)particle)->unk_40 = 0x28;
                ((S_7FFE79F4_3 *)particle)->unk_48 = (s16) ((func_700750E0() & 0x1F) << 7);
                ((S_7FFE79F4_3 *)particle)->unk_4A = 0x32;
                particle_pos = ((S_7FFE79F4_3 *)particle)->unk_08;
                ((S_7FFE79F4_3 *)particle)->unk_58 = (u16) ((S_7FFE79F4_1 *)position)->unk_02;
                ((S_7FFE79F4_3 *)particle)->unk_5A = (u16) ((S_7FFE79F4_1 *)position)->unk_06;
                ((S_7FFE79F4_3 *)particle)->unk_10 = &D_8010AA44;
                product = ((S_7FFE79F4_3 *)particle)->unk_4A * func_7006DD28(((S_7FFE79F4_3 *)particle)->unk_48);
                ((S_7FFE79F4_4 *)particle_pos)->unk_02 = (s16) ((product >> 0xC) + ((S_7FFE79F4_3 *)particle)->unk_58);
                product = ((S_7FFE79F4_3 *)particle)->unk_4A * func_7006DC5C(((S_7FFE79F4_3 *)particle)->unk_48);
                ((S_7FFE79F4_4 *)particle_pos)->unk_06 = (s16) ((product >> 0xC) + ((S_7FFE79F4_3 *)particle)->unk_5A);
                ((S_7FFE79F4_4 *)particle_pos)->unk_0A = (s16) (((S_7FFE79F4_1 *)position)->unk_0A - (func_700750E0() & 0x3F));
            }
        } while (spawn_count < 4);
    }
    life_left = ((S_7FFE79F4_0 *)emitter)->unk_1E - 1;
    ((S_7FFE79F4_0 *)emitter)->unk_1E = life_left;
    if ((life_left << 0x10) <= 0) {
        u16 *counter = &D_80094422;
        u16 next_counter;

        (*(u16 *)((u8 *)emitter + -2)) = (u16) (((S_7FFE79F4_0_pre *)emitter)[-1].unk_00 | 0x8000);
        next_counter = *counter - 1;
        D_80086AD8 |= 0x8000;
        *counter = next_counter;
    }
}
