#include "common.h"
#include "m2c_compat.h"

typedef struct {
    s32 words[3];
} __attribute__((packed)) Packed12;

#ifndef NON_MATCHING
void func_80024B18(void) __attribute__((noreturn));
#else
void *func_80024B18(void *);
#endif
void *func_8003FC64();
M2C_UNK func_8004491C();
extern M2C_UNK D_800249A0;
extern M2C_UNK D_80045340;


typedef struct S_800249F0_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_800249F0_0;   /* temp_s0 in func_800249F0 */

typedef struct S_800249F0_1 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x2];
    volatile u16 unk_14;
} S_800249F0_1;   /* temp_a3 in func_800249F0 */

typedef struct S_800249F0_2_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_800249F0_2_pre;   /* the 0x18 bytes before arg0 in func_800249F0, addressed as arg0[-1] */

typedef struct S_800249F0_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800249F0_3;   /* temp_a0 in func_800249F0 */

typedef struct S_800249F0_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800249F0_4;   /* temp_v1 in func_800249F0 */

typedef struct S_800249F0_5 {
    u8 pad_00[0x8];
    void * unk_08;
    s8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    s16 unk_1C;
    s16 unk_1E;
} S_800249F0_5;   /* temp_a3_2 in func_800249F0 */

void *func_800249F0(void *arg0, s32 arg1, s32 arg2, void *arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    u16 temp_v0_2;
    u16 temp_v1_2;
    register s32 arg4_copy ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    S_800249F0_3 *temp_a0;
    register void *temp_a3 ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register void *temp_a3_2 ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    S_800249F0_0 *temp_s0;
    void *temp_v0;
    S_800249F0_4 *temp_v1;
#ifndef NON_MATCHING
    register void *dispatch_result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    void *dispatch_arg;
#endif

    temp_v0 = func_8003FC64(0x212);
#ifndef NON_MATCHING
    dispatch_arg = temp_v0;
#endif
    if (temp_v0 == NULL) {
#ifndef NON_MATCHING
        dispatch_result = NULL;
        ASM_TAILSLOT_PIN(dispatch_result);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_80024B18();
#else
        return func_80024B18(temp_v0);
#endif
    }
    temp_s0 = temp_v0 + 0x20;
    temp_s0->unk_2A = 0x3C;
    (*(M2C_UNK **)((u8 *)temp_v0 + 0x10)) = &D_800249A0;
    func_8004491C(temp_v0, &D_80045340);
    temp_a3 = (*(void **)((u8 *)temp_v0 + 0xC));
    temp_v0_2 = ((S_800249F0_1 *)temp_a3)->unk_14 | 0xC;
    ((S_800249F0_1 *)temp_a3)->unk_14 = temp_v0_2;
    ASM_CLOBBER("$3");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    temp_v1_2 = temp_v0_2;
    ASM_KEEP(temp_v1_2);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    arg4_copy = arg4;
    ((S_800249F0_1 *)temp_a3)->unk_14 = (u16) (temp_v1_2 | 0x80);
    ASM_KEEP(arg4_copy);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    ((S_800249F0_1 *)temp_a3)->unk_10 = (s16) (arg4_copy << 5);
    temp_v1 = ((S_800249F0_2_pre *)arg0)[-1].unk_00;
    temp_a0 = (*(void **)((u8 *)temp_v0 + 8));
    temp_a0->unk_00 = (s32) temp_v1->unk_00;
    temp_a0->unk_04 = (s32) temp_v1->unk_04;
    temp_a0->unk_08 = (s32) temp_v1->unk_08;
    temp_a3_2 = (*(void **)((u8 *)temp_v0 + 0xC));
    ((S_800249F0_5 *)temp_a3_2)->unk_1C = (s16) arg5;
    ((S_800249F0_5 *)temp_a3_2)->unk_1E = (s16) arg6;
    ((S_800249F0_5 *)temp_a3_2)->unk_0E = 0x80;
    ((S_800249F0_5 *)temp_a3_2)->unk_0D = 0x80;
    ((S_800249F0_5 *)temp_a3_2)->unk_0C = (s8) arg7;
    (*(Packed12 *)((u8 *)temp_v0 + 0x92)) = *(Packed12 *)arg3;
    ((S_800249F0_5 *)temp_a3_2)->unk_08 = (void *) (temp_v0 + 0x92);
    return temp_s0;
}

/* MECHANISM: The 0x28 frame follows from held s2/s3 arguments plus s1 object and s0 return.
   Local a0/v0 dispatcher carriers and the tail-slot pin reproduce the noreturn j path.
   A fenced split RMW preserves both flag stores and the retail v0/v1 argument lifetimes.
   Disjoint a3 pointer roles free a0/a1 for the packed copy; u8 fields retain li 0x80. */
