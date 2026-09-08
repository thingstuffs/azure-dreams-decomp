#include "common.h"

typedef s32 M2C_UNK;

#ifndef NULL
#define NULL 0
#endif

typedef struct S_7FFE89B0_0_pre {
    u16 unk_00;
} S_7FFE89B0_0_pre;   /* the 0x2 bytes before arg0 in func_7FFE89B0, addressed as arg0[-1] */

typedef struct S_7FFE89B0_0 {
    void * unk_00;
    u8 pad_04[0x12];
    u16 unk_16;
    u8 pad_18[0x6];
    u16 unk_1E;
    u8 pad_20[0x4];
    void * unk_24;
    u8 pad_28[0x14];
    u16 unk_3C;
    u16 unk_3E;
    u16 unk_40;
} S_7FFE89B0_0;   /* arg0 in func_7FFE89B0 */

typedef struct S_7FFE89B0_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_7FFE89B0_1;   /* arg1 in func_7FFE89B0 */

typedef struct S_7FFE89B0_2 {
    u8 pad_00[0x8];
    void * unk_08;
} S_7FFE89B0_2;   /* temp_a0 in func_7FFE89B0 */

typedef struct S_7FFE89B0_3 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    M2C_UNK * unk_10;
    u8 pad_14[0x2A];
    s16 unk_3E;
    s16 unk_40;
} S_7FFE89B0_3;   /* temp_v0_2 in func_7FFE89B0 */

typedef struct S_7FFE89B0_4 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_7FFE89B0_4;   /* temp_s0 in func_7FFE89B0 */

typedef struct S_7FFE89B0_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_7FFE89B0_5;   /* ((S_7FFE89B0_2 *)temp_a0)->unk_08 in func_7FFE89B0 */

typedef struct S_7FFE89B0_6 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_7FFE89B0_6;   /* ((S_7FFE89B0_0 *)arg0)->unk_00 in func_7FFE89B0 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

void *func_7003CF18();
s32 func_700750E0();
M2C_UNK func_7010B864();
extern s32 D_80086AD8;
extern u8 D_800E0F20[];
extern u16 D_80094422;
extern M2C_UNK D_8010B4EC;

/* Emit particles at the parent-relative position and retire the emitter when its lifetime expires. */
void func_7FFE89B0(void *emitter, void *position, M2C_UNK spawn_context) {
    s32 spawn_index;
    u16 age;
    u16 lifetime;
    void *parent;
    void *particle_state;
    void *particle;

    parent = ((S_7FFE89B0_0 *)emitter)->unk_24;
    ((S_7FFE89B0_1 *)position)->unk_02 = (s16) (((S_7FFE89B0_5 *)(((S_7FFE89B0_2 *)parent)->unk_08))->unk_02 + ((S_7FFE89B0_0 *)emitter)->unk_3C);
    ((S_7FFE89B0_1 *)position)->unk_06 = (s16) (((S_7FFE89B0_5 *)(((S_7FFE89B0_2 *)parent)->unk_08))->unk_06 + ((S_7FFE89B0_0 *)emitter)->unk_3E);
    ((S_7FFE89B0_1 *)position)->unk_0A = (s16) (((S_7FFE89B0_5 *)(((S_7FFE89B0_2 *)parent)->unk_08))->unk_0A + ((S_7FFE89B0_0 *)emitter)->unk_40);
    age = ((S_7FFE89B0_0 *)emitter)->unk_16 + 1;
    ((S_7FFE89B0_0 *)emitter)->unk_16 = age;
    if ((s16) age < 0x14) {
        spawn_index = 0;
        do {
            particle = func_7003CF18(0x212);
            spawn_index += 1;
            if (particle != NULL) {
                func_7010B864(particle, emitter, position, spawn_context);
                ((S_7FFE89B0_3 *)particle)->unk_3E = 0xA;
                ((S_7FFE89B0_3 *)particle)->unk_40 = 0xA;
                ((S_7FFE89B0_3 *)particle)->unk_10 = &D_8010B4EC;
                particle_state = ((S_7FFE89B0_3 *)particle)->unk_08;
                ((S_7FFE89B0_4 *)particle_state)->unk_0C = (s32) (((func_700750E0() & 0x7FFF) - 0x4000) << 7);
                ((S_7FFE89B0_4 *)particle_state)->unk_10 = (s32) (((func_700750E0() & 0x7FFF) - 0x4000) << 7);
                ((S_7FFE89B0_4 *)particle_state)->unk_14 = (s32) (((func_700750E0() & 0x7FFF) - 0x4000) << 7);
                ((S_7FFE89B0_4 *)particle_state)->unk_0A = (u16) (((S_7FFE89B0_4 *)particle_state)->unk_0A - (D_800E0F20[((S_7FFE89B0_6 *)(((S_7FFE89B0_0 *)emitter)->unk_00))->unk_13] >> 1));
            }
        } while (spawn_index < 4);
    }
    lifetime = ((S_7FFE89B0_0 *)emitter)->unk_1E - 1;
    ((S_7FFE89B0_0 *)emitter)->unk_1E = lifetime;
    if ((lifetime << 0x10) <= 0) {
        u16 *active_count = &D_80094422;
        u16 next_active_count;

        (*(u16 *)((u8 *)emitter + -2)) = (u16) (((S_7FFE89B0_0_pre *)emitter)[-1].unk_00 | 0x8000);
        next_active_count = *active_count - 1;
        D_80086AD8 |= 0x8000;
        *active_count = next_active_count;
    }
}
