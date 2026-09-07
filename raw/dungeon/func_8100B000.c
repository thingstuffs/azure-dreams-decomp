/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

void *func_8003FD64();
M2C_UNK func_8004491C();
M2C_UNK func_800A48F0();
s32 func_800A6D30();
M2C_UNK func_800A9C18();
M2C_UNK func_800AA36C();
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083498;
extern M2C_UNK D_8016AA78;
extern M2C_UNK D_8016B058;
extern M2C_UNK D_8016E880;
extern M2C_UNK D_8016E8E0;

#ifdef __mips__
static const u32 bank_words[] __asm__("func_8016A800")
    __attribute__((section(".text.func_8016A800"), aligned(4))) = {
    0x8016A88C, 0x8016AA78, 0x8016B4EC, 0x8016B4EC,
    0x8016B4EC, 0x8016B518, 0x8016B498, 0x8016B498,
    0x8016B498, 0x8016B460, 0x8016B404, 0x8016B518,
    0x8016B518, 0x8016B4DC, 0x94824081, 0x8F828F82,
    0x40818B82, 0x00000000, 0x81824081, 0x81829782,
    0x44819982, 0x00000000, 0x8016C950, 0x8016C948,
    0x8016C940, 0x8016C958, 0x8016C900, 0x8016C8F8,
    0x8016C8F0, 0x00000000, 0x8016DEE0, 0x8016E0F8,
    0x8016E204, 0x8016E4F8, 0x8016E668,
};
__asm__(".globl func_8016A800\n"
        ".size func_8016A800, 632");
#define BODY_NAME func_8016A88C
#else
#define BODY_NAME func_8016A800
#endif

void *BODY_NAME(s32, s8, s8, s16)
#ifdef __mips__
    __attribute__((section(".text.func_8016A800")))
#endif
    ;

void *BODY_NAME(s32 arg0, s8 arg1, s8 arg2, s16 arg3) {
    s32 kind;
    s16 final_arg0;
    s32 left;
    s32 right;
    register void *work ASM_REG("$16") = NULL;
    register void *obj ASM_REG("$17");
    register void *part_a ASM_REG("$20");
    void *part_b;
    void *actor;
    register s8 saved_arg1 ASM_REG("$22");
    register s16 saved_arg3 ASM_REG("$18");
    register s8 saved_arg2 ASM_REG("$21");
    register void *call_a0 ASM_REG("$4");
    register void *call_a1 ASM_REG("$5");

    saved_arg1 = arg1;
    saved_arg3 = arg3;
    saved_arg2 = arg2;
    obj = func_8003FD64(0x112, &D_80083498);
    if (obj != NULL) {
        final_arg0 = arg0;
        ASM_SCHED_BARRIER();
        work = obj + 0x20;
        M2C_FIELD(obj, M2C_UNK **, 0x10) = &D_8016AA78;
        M2C_FIELD(work, s8 *, 0x13) = 0x29;
        func_8004491C(obj, &D_80045340);
        part_a = M2C_FIELD(obj, void **, 8);
        M2C_FIELD(part_a, s16 *, 0xA) = saved_arg3;
        part_b = M2C_FIELD(obj, void **, 0xC);
        kind = arg0 & 3;
        M2C_FIELD(part_b, s8 *, 0x25) = saved_arg2;
        actor = work;
        M2C_FIELD(part_b, M2C_UNK **, 0x2C) = &D_8016E880;
        M2C_FIELD(part_b, s8 *, 0x24) = saved_arg1;
        if (kind == 1) {
            left = M2C_FIELD(work, s32 *, 0x14) | 0x6000;
            right = M2C_FIELD(work, s32 *, 0x1C) | 0x6000;
            goto write_kind;
        }
        if (kind < 2) {
            goto normal_kind;
        }
        left = M2C_FIELD(work, s32 *, 0x14) | 0x2000;
        right = M2C_FIELD(work, s32 *, 0x1C) | 0x2000;
write_kind:
        M2C_FIELD(work, s32 *, 0x14) = left;
        M2C_FIELD(work, s32 *, 0x1C) = right;
        goto post_kind;

normal_kind:
        call_a0 = obj;
        if (((arg0 & ~3) << 16) == 0) {
            if (!(M2C_FIELD(work, s32 *, 0x14) & 0x200)) {
                call_a1 = part_a;
                left = func_800A6D30();
                call_a0 = obj;
                if (!(left & 1)) {
                    goto post_kind;
                }
                    M2C_FIELD(work, s32 *, 0x1C) |= 0x200;
                    func_800A48F0(work, 1,
                                  (func_800A6D30() & 0x3F) | 0x20);
                    M2C_FIELD(part_b, M2C_UNK **, 0x2C) = &D_8016E8E0;
            }
        }
post_kind:
        func_800A9C18(obj, part_a, part_b, final_arg0);
        M2C_FIELD(actor, u8 *, 0x9A) = 0xFF;
        M2C_FIELD(actor, s8 *, 0x9C) = -1;
        M2C_FIELD(actor, M2C_UNK **, 0x8C) = &D_8016B058;
        M2C_FIELD(work, s32 *, 0x1C) |= 0x40000;
        M2C_FIELD(actor, s16 *, 0x92) = -0x18;
        func_800AA36C(actor, part_a, part_b, work);
    }
    return work;
}
