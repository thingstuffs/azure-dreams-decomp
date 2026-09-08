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

void *BODY_NAME(s16 spawn_flags, s8 grid_x, s8 grid_y, s16 part_value) BODY_ATTR;

/* Allocates an actor and initializes its parts, position, and spawn flags. */
void *BODY_NAME(s16 spawn_flags, s8 grid_x, s8 grid_y, s16 part_value) {
    register s16 saved_flags ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s8 saved_x;
    s8 saved_y;
    s16 saved_part_value;
    s16 init_flags;
    S_80FF9000_1 *work;
    register s32 alloc_kind ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    void *alloc_desc;
    s32 random_bits;
    s32 extra_flags;
    s32 kind;
    s32 flags_14;
    s32 flags_1c;
    S_80FF9000_3 *part_b;
    S_80FF9000_2 *part_a;
    void *obj;
    S_80FF9000_4 *actor;

    saved_flags = spawn_flags;
    ASM_KEEP_NV(saved_flags);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    work = NULL;
    alloc_kind = 0x112;
    saved_x = grid_x;
    ASM_KEEP_NV(saved_x);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    alloc_desc = &D_80083498;
    saved_part_value = part_value;
    ASM_KEEP_NV(saved_part_value);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    saved_y = grid_y;
    ASM_KEEP_NV(saved_y);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    random_bits = (s32) *(s8 *)0x4A64;
    obj = func_8003FD64(alloc_kind, alloc_desc);
    init_flags = saved_flags;
    if (obj != NULL) {
        work = obj + 0x20;
        ((S_80FF9000_0 *)obj)->unk_10 = &D_80152A7C;
        work->unk_13 = 0x28;
        func_8004491C(obj, &D_80045340);
        part_a = ((S_80FF9000_0 *)obj)->unk_08;
        part_a->unk_0A = saved_part_value;
        part_b = ((S_80FF9000_0 *)obj)->unk_0C;
        kind = saved_flags & 3;
        part_b->unk_25 = saved_y;
        actor = work;
        part_b->unk_2C = &D_80156038;
        part_b->unk_24 = saved_x;

        if (kind == 1) {
            flags_14 = work->unk_14 | 0x6000;
            flags_1c = work->unk_1C | 0x6000;
            goto write_kind;
        }
        if (kind < 2) {
            goto normal_kind;
        }

        flags_14 = work->unk_14 | 0x2000;
        flags_1c = work->unk_1C | 0x2000;
write_kind:
        work->unk_14 = flags_14;
        work->unk_1C = flags_1c;
        goto post_kind;

normal_kind:
        extra_flags = (saved_flags & ~3) << 0x10;
        ASM_USE_NV(saved_flags);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        alloc_kind = (s32)obj;
        if (extra_flags != 0) {
            goto set_part_arg;
        }
        alloc_desc = part_a;
        if (work->unk_14 & 0x200) {
            goto init_actor;
        }
        random_bits = func_800A6D30(alloc_kind, alloc_desc);
        alloc_kind = (s32)obj;
        if (!(random_bits & 1)) {
            goto set_part_arg;
        }
        work->unk_1C = (s32) (work->unk_1C | 0x200);
        func_800A48F0(work, 1, (func_800A6D30(alloc_kind) & 0x3F) | 0x20);
        part_b->unk_2C = &D_80156088;

post_kind:
        alloc_kind = (s32)obj;
set_part_arg:
        alloc_desc = part_a;
init_actor:
        func_800A9C18(alloc_kind, alloc_desc, part_b, init_flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &D_80152EA8;
        func_800AA36C(actor, part_a, part_b, work);
    }
    return work;
}
