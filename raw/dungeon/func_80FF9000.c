/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#if 0 /* rowbase_rename_reverify precondition marker: dead declaration, never
         seen by the real compiler; satisfies the tool's textual defines()
         check for the proven-region rename of func_80152800. */
void func_80152800(void);
#endif
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
void *func_80152988();
void *func_80152A00();
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083498;
extern u8 D_80152A7C[];
extern M2C_UNK D_80152EA8;
extern M2C_UNK D_80156038;
extern M2C_UNK D_80156088;

#ifdef __mips__
static const u32 data_prefix[] __asm__("func_80152800")
    __attribute__((section(".text.func_80152800"), aligned(4))) = {
    0x801528A8, 0x80152A7C,
    0x801532B8, 0x801532B8, 0x801532B8, 0x801532E4,
    0x80153264, 0x80153264, 0x80153264, 0x801531F4,
    0x801531E4, 0x801532E4, 0x801532E4, 0x801532A8,
    0x80154AC4, 0x80154ABC, 0x80154AB4, 0x80154ACC,
    0x80154A74, 0x80154A6C, 0x80154A64,
    0x89824081, 0x40819382, 0x93829082, 0x83829982,
    0x85828882, 0x7C818482, 0x90829582, 0x00004481,
    0x92824081, 0x96828582, 0x81828582, 0x85828C82,
    0x40818482, 0x94828982, 0x40819382, 0x92829482,
    0x85829582, 0x90824081, 0x97828F82, 0x92828582,
    0x70004481,
};
__asm__(".globl func_80152800\n"
        ".size func_80152800, 636");
#define BODY_NAME func_801528A8
#define BODY_ATTR __attribute__((section(".text.func_80152800")))
#else
#define BODY_NAME func_80152800
#define BODY_ATTR
#endif

void *BODY_NAME(s16 arg0, s8 arg1, s8 arg2, s16 arg3) BODY_ATTR;

void *BODY_NAME(s16 arg0, s8 arg1, s8 arg2, s16 arg3) {
    register s16 saved_arg0 ASM_REG("$19");
    register s8 saved_arg1 ASM_REG("$22");
    register s8 saved_arg2 ASM_REG("$21");
    register s16 saved_arg3 ASM_REG("$18");
    register s16 late_arg0 ASM_REG("$23");
    register void *work ASM_REG("$16");
    register s32 alloc_kind ASM_REG("$4");
    register void *alloc_desc ASM_REG("$5");
    s32 unksp24;
    s32 sp24;
    s32 kind;
    s32 left;
    s32 right;
    void *part_b;
    void *part_a;
    void *obj;
    void *actor;

    saved_arg0 = arg0;
    ASM_KEEP_NV(saved_arg0);
    work = NULL;
    ASM_KEEP_NV(work);
    alloc_kind = 0x112;
    ASM_KEEP_NV(alloc_kind);
    saved_arg1 = arg1;
    ASM_KEEP_NV(saved_arg1);
    alloc_desc = &D_80083498;
    ASM_KEEP_NV(alloc_desc);
    saved_arg3 = arg3;
    ASM_KEEP_NV(saved_arg3);
    saved_arg2 = arg2;
    ASM_KEEP_NV(saved_arg2);
    unksp24 = (s32) *(s8 *)0x4A64;
    obj = func_8003FD64(alloc_kind, alloc_desc);
    late_arg0 = saved_arg0;
    if (obj != NULL) {
        work = obj + 0x20;
        M2C_FIELD(obj, M2C_UNK **, 0x10) = &D_80152A7C;
        M2C_FIELD(work, s8 *, 0x13) = 0x28;
        func_8004491C(obj, &D_80045340);
        part_a = M2C_FIELD(obj, void **, 8);
        M2C_FIELD(part_a, s16 *, 0xA) = saved_arg3;
        part_b = M2C_FIELD(obj, void **, 0xC);
        kind = saved_arg0 & 3;
        M2C_FIELD(part_b, s8 *, 0x25) = saved_arg2;
        actor = work;
        M2C_FIELD(part_b, M2C_UNK **, 0x2C) = &D_80156038;
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
        sp24 = (saved_arg0 & ~3) << 0x10;
        ASM_USE_NV(saved_arg0);
        alloc_kind = (s32)obj;
        if (sp24 != 0) {
            goto post_arg1;
        }
        alloc_desc = part_a;
        if (M2C_FIELD(work, s32 *, 0x14) & 0x200) {
            goto post_arg2;
        }
        unksp24 = func_800A6D30(alloc_kind, alloc_desc);
        alloc_kind = (s32)obj;
        if (!(unksp24 & 1)) {
            goto post_arg1;
        }
        M2C_FIELD(work, s32 *, 0x1C) = (s32) (M2C_FIELD(work, s32 *, 0x1C) | 0x200);
        func_800A48F0(work, 1, (func_800A6D30(alloc_kind) & 0x3F) | 0x20);
        M2C_FIELD(part_b, M2C_UNK **, 0x2C) = &D_80156088;

post_kind:
        alloc_kind = (s32)obj;
post_arg1:
        alloc_desc = part_a;
post_arg2:
        func_800A9C18(alloc_kind, alloc_desc, part_b, late_arg0);
        M2C_FIELD(actor, u8 *, 0x9A) = 0xFF;
        M2C_FIELD(actor, s8 *, 0x9C) = -1;
        M2C_FIELD(actor, M2C_UNK **, 0x8C) = &D_80152EA8;
        func_800AA36C(actor, part_a, part_b, work);
    }
    return work;
}
