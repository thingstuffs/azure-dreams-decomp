#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_818CEB58_0 {
    u8 pad_00[0x8];
    union { void * s; s32 u; } unk_08;   /* accessed as both */
    u8 pad_0C[0x4];
    s32 unk_10;
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
} S_818CEB58_0;   /* temp_s0 in func_818CEB58 */

typedef struct S_818CEB58_1 {
    u8 pad_00[0x8];
    void * unk_08;
} S_818CEB58_1;   /* held_arg0 in func_818CEB58 */

typedef struct S_818CEB58_2 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_818CEB58_2;   /* dest1 in func_818CEB58 */

typedef struct S_818CEB58_3 {
    u8 pad_00[0x6];
    s16 unk_06;
} S_818CEB58_3;   /* dest2 in func_818CEB58 */

typedef struct S_818CEB58_4 {
    u8 pad_00[0x8];
    void * unk_08;
} S_818CEB58_4;   /* call_obj in func_818CEB58 */

typedef struct S_818CEB58_5 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_818CEB58_5;   /* dest3 in func_818CEB58 */

typedef struct S_818CEB58_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_818CEB58_6;   /* ((S_818CEB58_1 *)held_arg0)->unk_08 in func_818CEB58 */



extern void *func_8003FD64(s32, void *);
extern s32 rand(void);
extern void func_8004491C(void *, void *, void *);
extern u8 D_8002403C[];
extern u8 D_8002428C[];

void func_818CEB58(
    void *arg0,
    s16 arg1,
    s32 arg2,
    s16 arg3,
    s32 arg4,
    s32 arg5,
    s32 arg6)
{
    register s32 held_arg4 ASM_REG("$18") = arg4;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    void *held_arg0 = arg0;
    register s16 held_arg1 ASM_REG("$21") = arg1;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register s32 held_arg2 ASM_REG("$23") = arg2;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s16 held_arg3 ASM_REG("$22") = arg3;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 held_arg5 = arg5;
    s32 held_arg6 = arg6;
    void *temp_s0;
    s32 random1;
    s32 random2;
    s32 random3;
    s32 offset1;
    s32 offset2;
    s32 offset3;
    s32 value1;
    s32 value2;
    s32 value3;
    u32 descriptor_page;
    register void *call_obj ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    void *call_data;
    S_818CEB58_2 *dest1;
    S_818CEB58_3 *dest2;
    S_818CEB58_5 *dest3;

    temp_s0 = func_8003FD64(0x211, held_arg0);
    if (temp_s0 != NULL) {
        descriptor_page = 0x80020000;
        ASM_KEEP(descriptor_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        ((S_818CEB58_0 *)temp_s0)->unk_10 = descriptor_page + 0x428C;
        random1 = rand() & 0x1F;
        value1 = ((S_818CEB58_6 *)(((S_818CEB58_1 *)held_arg0)->unk_08))->unk_02;
        dest1 = ((S_818CEB58_0 *)temp_s0)->unk_08.s;
        value1 += random1;
        offset1 = held_arg4 - 0x10;
        value1 += offset1;
        dest1->unk_02 = (s16)value1;

        random2 = rand() & 0x1F;
        value2 = ((S_818CEB58_6 *)(((S_818CEB58_1 *)held_arg0)->unk_08))->unk_06;
        dest2 = ((S_818CEB58_0 *)temp_s0)->unk_08.s;
        value2 += random2;
        offset2 = held_arg5 - 0x10;
        value2 += offset2;
        dest2->unk_06 = (s16)value2;

        random3 = rand();
        call_obj = temp_s0;
        call_data = &D_8002403C;
        ASM_USE2(call_obj, call_data);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        random3 &= 0x1F;
        value3 = ((S_818CEB58_6 *)(((S_818CEB58_1 *)held_arg0)->unk_08))->unk_0A;
        temp_s0 = (u8 *)call_obj + 0x20;
        dest3 = ((S_818CEB58_4 *)call_obj)->unk_08;
        value3 += random3;
        offset3 = held_arg6 - 0x10;
        value3 += offset3;
        dest3->unk_0A = (s16)value3;
        ASM_KEEP(held_arg4);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        ASM_KEEP(temp_s0);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        ((S_818CEB58_0 *)temp_s0)->unk_14 = held_arg1;
        ASM_KEEP(held_arg1);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ((S_818CEB58_0 *)temp_s0)->unk_32 = held_arg3;
        func_8004491C(call_obj, call_data, dest3);
        ASM_KEEP(held_arg3);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ((S_818CEB58_0 *)temp_s0)->unk_08.u = held_arg2;
        ASM_KEEP(held_arg2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    }
}

/* MECHANISM: The true-space definition and guarded s0-s7 role map reproduce the 0x38 frame.
   Separate random/value/destination/offset lifetimes plus the three-argument callee ABI align the body.
   A kept 0x80020000 page plus 0x40E4 exposes the branch-delay lui; the tail keep anchors s0 stores. */
