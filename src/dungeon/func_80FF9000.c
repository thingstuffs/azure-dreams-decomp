/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_80FF9000_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80FF9000_0;   /* obj in BODY_NAME */

typedef struct S_80FF9000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80FF9000_1;   /* work in BODY_NAME */

typedef struct S_80FF9000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80FF9000_2;   /* part_a in BODY_NAME */

typedef struct S_80FF9000_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    M2C_UNK * unk_2C;
} S_80FF9000_3;   /* part_b in BODY_NAME */

typedef struct S_80FF9000_4 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80FF9000_4;   /* actor in BODY_NAME */

#if 0 /* rowbase_rename_reverify precondition marker: dead declaration, never
         seen by the real compiler; satisfies the tool's textual defines()
         check for the proven-region rename of func_80152800. */
void func_80152800(void);
#endif

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
    register s16 saved_arg0 ASM_REG("$19");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s8 saved_arg1;
    s8 saved_arg2;
    s16 saved_arg3;
    s16 late_arg0;
    S_80FF9000_1 *work;
    register s32 alloc_kind ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
    void *alloc_desc;
    s32 unksp24;
    s32 sp24;
    s32 kind;
    s32 left;
    s32 right;
    S_80FF9000_3 *part_b;
    S_80FF9000_2 *part_a;
    void *obj;
    S_80FF9000_4 *actor;

    saved_arg0 = arg0;
    ASM_KEEP_NV(saved_arg0);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    work = NULL;
    alloc_kind = 0x112;
    saved_arg1 = arg1;
    ASM_KEEP_NV(saved_arg1);   /* MATCH pin: retail schedule: same instructions, different order without it */
    alloc_desc = &D_80083498;
    saved_arg3 = arg3;
    ASM_KEEP_NV(saved_arg3);   /* MATCH pin: retail schedule: same instructions, different order without it */
    saved_arg2 = arg2;
    ASM_KEEP_NV(saved_arg2);   /* MATCH pin: retail schedule: same instructions, different order without it */
    unksp24 = (s32) *(s8 *)0x4A64;
    obj = func_8003FD64(alloc_kind, alloc_desc);
    late_arg0 = saved_arg0;
    if (obj != NULL) {
        work = obj + 0x20;
        ((S_80FF9000_0 *)obj)->unk_10 = &D_80152A7C;
        work->unk_13 = 0x28;
        func_8004491C(obj, &D_80045340);
        part_a = ((S_80FF9000_0 *)obj)->unk_08;
        part_a->unk_0A = saved_arg3;
        part_b = ((S_80FF9000_0 *)obj)->unk_0C;
        kind = saved_arg0 & 3;
        part_b->unk_25 = saved_arg2;
        actor = work;
        part_b->unk_2C = &D_80156038;
        part_b->unk_24 = saved_arg1;

        if (kind == 1) {
            left = work->unk_14 | 0x6000;
            right = work->unk_1C | 0x6000;
            goto write_kind;
        }
        if (kind < 2) {
            goto normal_kind;
        }

        left = work->unk_14 | 0x2000;
        right = work->unk_1C | 0x2000;
write_kind:
        work->unk_14 = left;
        work->unk_1C = right;
        goto post_kind;

normal_kind:
        sp24 = (saved_arg0 & ~3) << 0x10;
        ASM_USE_NV(saved_arg0);   /* MATCH pin: load-bearing for the whole function shape */
        alloc_kind = (s32)obj;
        if (sp24 != 0) {
            goto post_arg1;
        }
        alloc_desc = part_a;
        if (work->unk_14 & 0x200) {
            goto post_arg2;
        }
        unksp24 = func_800A6D30(alloc_kind, alloc_desc);
        alloc_kind = (s32)obj;
        if (!(unksp24 & 1)) {
            goto post_arg1;
        }
        work->unk_1C = (s32) (work->unk_1C | 0x200);
        func_800A48F0(work, 1, (func_800A6D30(alloc_kind) & 0x3F) | 0x20);
        part_b->unk_2C = &D_80156088;

post_kind:
        alloc_kind = (s32)obj;
post_arg1:
        alloc_desc = part_a;
post_arg2:
        func_800A9C18(alloc_kind, alloc_desc, part_b, late_arg0);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &D_80152EA8;
        func_800AA36C(actor, part_a, part_b, work);
    }
    return work;
}
