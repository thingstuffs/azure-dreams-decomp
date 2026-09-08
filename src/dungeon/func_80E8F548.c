#include "common.h"
#include "records/Rec_func_800AD058_arg2.h"

typedef s32 M2C_UNK;
typedef struct {
    s32 value;
} __attribute__((packed)) unaligned_s32;

#ifndef NULL
#define NULL 0
#endif


extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *, s32);
extern s32 func_8004A658(s32, s32);
extern void func_800BC26C(void *, s32, s32, s32);
extern void func_80174E18(void) __attribute__((noreturn));

extern u8 D_80045340[9];
extern u8 D_8006E240[9];
extern u8 D_80174978[9];


typedef struct S_80174D48_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80174D48_0;   /* temp_v0 in func_80174D48 */

typedef struct S_80174D48_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x9C];
    s16 unk_A8;
    s16 unk_AA;
} S_80174D48_1;   /* temp_s2 in func_80174D48 */

typedef struct S_80174D48_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80174D48_2;   /* temp_v1 in func_80174D48 */

typedef struct S_80174D48_3 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_80174D48_3;   /* temp_s1 in func_80174D48 */


void func_80174D48(void *arg0, Rec_func_800AD058_arg2 *arg1, void *arg2)
{
    s32 temp_a2;
    s32 temp_byte;
    s32 temp_copy;
    void *first_call_a0;
    u32 first_call_page;
    void *call_a0;
    s32 call_zero;
    s32 temp_half;
    S_80174D48_3 *temp_s1;
    register void *temp_s2 ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *temp_s3 ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    void *tail_value;
    void *temp_v0;
    S_80174D48_2 *temp_v1;

    if (((*(u8 *)((u8 *)arg2 + 0x49)) != 0) &&
        (temp_v0 = func_8003FC64(0x12), temp_v0 != NULL)) {
        first_call_a0 = temp_v0;
        ASM_KEEP(first_call_a0);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        temp_v1 = ((S_80174D48_0 *)temp_v0)->unk_08;
        ASM_KEEP(temp_v1);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        temp_s2 = arg0;
        temp_copy = ((S_80174D48_1 *)temp_s2)->unk_00;
        temp_s1 = ((S_80174D48_0 *)temp_v0)->unk_0C;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        first_call_page = 0x80040000;
        ASM_KEEP(first_call_page);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        temp_v1->unk_00 = temp_copy;
        temp_copy = ((S_80174D48_1 *)temp_s2)->unk_04;
        first_call_page += 0x5340;
        temp_v1->unk_04 = temp_copy;
        temp_a2 = ((S_80174D48_1 *)temp_s2)->unk_08;
        temp_v1->unk_10 = 0;
        temp_v1->unk_0C = 0;
        temp_v1->unk_14 = 0xFFEE0000;
        temp_v1->unk_08 = temp_a2;
        func_8004491C(first_call_a0, (void *)first_call_page, temp_a2);
        temp_s1->unk_0C = 0x808080;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        temp_half = 0xC90;
        ASM_KEEP(temp_half);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        temp_s3 = (u8 *)temp_v0 + 0x20;
        temp_s1->unk_1E = temp_half;
        temp_s1->unk_1C = temp_half;
        temp_s2 = temp_s3;
        if ((*(u8 *)((u8 *)arg2 + 0x49)) == 0x12) {
            tail_value = D_8006E240;
            ASM_KEEP(tail_value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            func_80174E18();
        }
        temp_s1->unk_08 =
            func_8004A658((*(volatile u8 *)((u8 *)arg2 + 0x49)),
                          (*(u8 *)((u8 *)arg2 + 0x48)));
        ASM_KEEP(temp_s2);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        temp_byte = arg1->unk_24;
        ASM_KEEP(temp_byte);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        call_a0 = temp_v0;
        ASM_KEEP(call_a0);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        ((S_80174D48_1 *)temp_s2)->unk_A8 = temp_byte;
        temp_byte = arg1->unk_25;
        ASM_KEEP(temp_byte);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        call_zero = 0;
        ASM_KEEP(call_zero);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        ((S_80174D48_1 *)temp_s2)->unk_AA = temp_byte;
        ASM_KEEP(temp_s3);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        (*(unaligned_s32 *)((u8 *)temp_s3 + 0x48)) = (*(unaligned_s32 *)((u8 *)arg2 + 0x48));
        func_800BC26C(call_a0, call_zero, call_zero, call_zero);
        ((S_80174D48_0 *)temp_v0)->unk_10 = D_80174978;
    }
}

/* MECHANISM: Distinct pinned s2/s3 object bases force the retail 0x30 frame and saved-register roles.
   A packed four-byte assignment produces lwl/lwr/swl/swr; named call ABI values fill load-delay slots.
   Fenced split a1 materialization plus the noreturn tail carrier reproduce retail scheduling and tail j. */
