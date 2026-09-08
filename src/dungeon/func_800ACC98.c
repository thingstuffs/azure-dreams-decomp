#include "common.h"


typedef s32 M2C_UNK;

typedef struct S_800B23F8_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_800B23F8_0;   /* obj in func_800B23F8 */

typedef struct S_800B23F8_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_800B23F8_1;   /* work in func_800B23F8 */

typedef struct S_800B23F8_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_800B23F8_2;   /* part_a in func_800B23F8 */

typedef struct S_800B23F8_3 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x18];
    s8 unk_24;
    s8 unk_25;
} S_800B23F8_3;   /* (void *)reg_s2 in func_800B23F8 */

typedef struct S_800B23F8_4 {
    u8 pad_00[0x9A];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_800B23F8_4;   /* (void *)reg_s3 in func_800B23F8 */


extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_800B22F0(void *, void *, void *, s16);
extern u8 D_80045340;
extern s32 D_80083498;
extern M2C_UNK D_800B274C;
extern M2C_UNK D_800B2A60;

/* Create an object and initialize its components and flags from the mode and supplied values. */
void *func_800B23F8(s32 mode, s32 part_b_byte_24, s32 part_b_byte_25, s32 part_a_value,
                    volatile s32 part_b_value)
{
    s32 saved_mode;
    register s32 saved_byte_24 ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    long value_or_part_b;
    long byte_or_work;
    register s32 alloc_code ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register void *alloc_data ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s32 kind;
    s32 kind_test;
    s32 flags_14;
    s32 flags_1c;
    void *part_a;
    void *obj;
    void *work;
    s16 init_mode;

    saved_mode = mode;
    work = 0;
    alloc_code = 0x112;
    saved_byte_24 = part_b_byte_24;
    alloc_data = &D_80083498;
    value_or_part_b = part_a_value;
    byte_or_work = part_b_byte_25;
    ASM_KEEP_NV(alloc_code);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(alloc_data);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    obj = func_8003FD64(alloc_code, alloc_data);
    if (obj != 0) {
        init_mode = saved_mode;
        work = (u8 *)obj + 0x20;
        ASM_KEEP(work);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        ((S_800B23F8_0 *)obj)->unk_10 = &D_800B274C;
        ((S_800B23F8_1 *)work)->unk_13 = 0x1E;
        func_8004491C(obj, &D_80045340);

        part_a = ((S_800B23F8_0 *)obj)->unk_08;
        kind = saved_mode & 3;
        ((S_800B23F8_2 *)part_a)->unk_0A = (s16)value_or_part_b;
        ASM_KEEP(kind);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        value_or_part_b = (long)((S_800B23F8_0 *)obj)->unk_0C;
        kind_test = 1;
        ((S_800B23F8_3 *)((void *)value_or_part_b))->unk_25 = (s8)byte_or_work;
        byte_or_work = (long)work;
        ((S_800B23F8_3 *)((void *)value_or_part_b))->unk_24 = saved_byte_24;

        if (kind == kind_test) {
            flags_14 = ((S_800B23F8_1 *)work)->unk_14 | 0x6000;
            flags_1c = ((S_800B23F8_1 *)work)->unk_1C | 0x6000;
            goto write_kind;
        }
        kind_test = kind < 2;
        if (kind_test) {
            goto post_kind;
        }
        flags_14 = ((S_800B23F8_1 *)work)->unk_14 | 0x2000;
        flags_1c = ((S_800B23F8_1 *)work)->unk_1C | 0x2000;
write_kind:
        ((S_800B23F8_1 *)work)->unk_14 = flags_14;
        ((S_800B23F8_1 *)work)->unk_1C = flags_1c;

post_kind:
        func_800B22F0(obj, part_a, (void *)value_or_part_b, init_mode);
        ((S_800B23F8_4 *)((void *)byte_or_work))->unk_9A = 0xFF;
        ((S_800B23F8_4 *)((void *)byte_or_work))->unk_9C = -1;
        (*(M2C_UNK * *)((u8 *)((void *)byte_or_work) + 0x8C)) = &D_800B2A60;
        ((S_800B23F8_3 *)((void *)value_or_part_b))->unk_08 = part_b_value;
    }
    return work;
}
