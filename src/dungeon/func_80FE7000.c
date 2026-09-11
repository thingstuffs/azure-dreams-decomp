#include "common.h"

typedef struct S_80FE7000_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80FE7000_0;   /* created in BODY_NAME */

typedef struct S_80FE7000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    u32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
} S_80FE7000_1;   /* result in BODY_NAME */

typedef struct S_80FE7000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80FE7000_2;   /* position in BODY_NAME */

typedef struct S_80FE7000_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80FE7000_3;   /* part_b in BODY_NAME */

typedef struct S_80FE7000_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80FE7000_4;   /* actor in BODY_NAME */

#if 0 /* rowbase_rename_reverify precondition marker: dead declaration, never
         seen by the real compiler; satisfies the tool's textual defines()
         check for the proven-region rename of func_80164800. */
void func_80164800(void);
#endif


extern void *func_8003FD64();
extern void func_8004491C();
extern void func_800A48F0();
extern s32 func_800A6D30();
extern void func_800A9C18();
extern void func_800AA36C();

extern s32 D_80045340;
extern u8 D_80083498[];
extern u8 D_80164A7C[];
extern u8 D_80164EA8[];
extern u8 D_80168038[];
extern u8 D_80168088[];
extern void *func_801648A8();
extern u8 D_801652B8[];
extern u8 D_801652E4[];
extern u8 D_80165264[];
extern u8 D_801651F4[];
extern u8 D_801651E4[];
extern u8 D_801652A8[];
extern u8 D_80166AC4[];
extern u8 D_80166ABC[];
extern u8 D_80166AB4[];
extern u8 D_80166ACC[];
extern u8 D_80166A74[];
extern u8 D_80166A6C[];
extern u8 D_80166A64[];

#ifdef __mips__
static const u32 bank_words[] __asm__("func_80164800")
    __attribute__((section(".text.func_80164800"), aligned(4))) = {
    (u32)func_801648A8,
    (u32)D_80164A7C,
    (u32)D_801652B8,
    (u32)D_801652B8,
    (u32)D_801652B8,
    (u32)D_801652E4,
    (u32)D_80165264,
    (u32)D_80165264,
    (u32)D_80165264,
    (u32)D_801651F4,
    (u32)D_801651E4,
    (u32)D_801652E4,
    (u32)D_801652E4,
    (u32)D_801652A8,
    (u32)D_80166AC4,
    (u32)D_80166ABC,
    (u32)D_80166AB4,
    (u32)D_80166ACC,
    (u32)D_80166A74,
    (u32)D_80166A6C,
    (u32)D_80166A64,
    0x89824081,
    0x40819382,
    0x93829082,
    0x83829982,
    0x85828882,
    0x7c818482,
    0x90829582,
    0x00004481,
    0x92824081,
    0x96828582,
    0x81828582,
    0x85828c82,
    0x40818482,
    0x94828982,
    0x40819382,
    0x92829482,
    0x85829582,
    0x90824081,
    0x97828f82,
    0x92828582,
    0x75004481,
};
__asm__(".globl func_80164800\n"
        ".size func_80164800, 636");
#define BODY_NAME func_801648A8
#else
#define BODY_NAME func_80164800
#endif

void *BODY_NAME(void *arg0, s32 arg1, s32 arg2, s32 arg3)
#ifdef __mips__
    __attribute__((section(".text.func_80164800")))
#endif
    ;

void *BODY_NAME(void *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    void *result = 0;
    void *created;
    register void *position ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    S_80FE7000_3 *part_b;
    S_80FE7000_4 *actor;
    s32 left;
    s32 right;
    s16 saved_arg1;
    s32 saved_arg3;
    s16 saved_arg2;
    register s32 saved_arg0 = (s32)arg0;
    register s32 original_arg0 ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *call_a0;
    void *call_a1;
    s32 kind;

    saved_arg1 = arg1;
    saved_arg3 = arg3;
    saved_arg2 = arg2;
    created = func_8003FD64(0x112, D_80083498);
    original_arg0 = saved_arg0;
    if (created == 0) {
        goto done;
    }

    result = (u8 *)created + 0x20;
    ((S_80FE7000_0 *)created)->unk_10 = D_80164A7C;
    ((S_80FE7000_1 *)result)->unk_13 = 0x28;
    func_8004491C(created, &D_80045340);

    position = ((S_80FE7000_0 *)created)->unk_08;
    ((S_80FE7000_2 *)position)->unk_0A = saved_arg3;
    part_b = ((S_80FE7000_0 *)created)->unk_0C;
    kind = saved_arg0 & 3;
    part_b->unk_25 = saved_arg2;
    actor = result;
    part_b->unk_2C = D_80168038;
    part_b->unk_24 = saved_arg1;

    if (kind == 1) {
        ((S_80FE7000_1 *)result)->unk_14 |= 0x6000;
        ((S_80FE7000_1 *)result)->unk_1C |= 0x6000;
        goto setup;
    }
    if (kind >= 2) {
        ((S_80FE7000_1 *)result)->unk_14 |= 0x2000;
        ((S_80FE7000_1 *)result)->unk_1C |= 0x2000;
        goto setup;
    }

    call_a0 = created;
    if (((saved_arg0 & ~3) << 16) == 0) {
        if (!(((S_80FE7000_1 *)result)->unk_14 & 0x200)) {
            call_a1 = position;
            if (func_800A6D30() & 1) {
                ((S_80FE7000_1 *)result)->unk_1C |= 0x200;
                func_800A48F0(result, 1,
                    (func_800A6D30() & 0x3F) | 0x20);
                part_b->unk_2C = D_80168088;
            }
        }
    }

setup:
    func_800A9C18(created, position, part_b,
        (s16)original_arg0);
    actor->unk_9A = 0xFF;
    actor->unk_9C = -1;
    actor->unk_8C = D_80164EA8;
    func_800AA36C(actor, position,
        part_b, result);

done:
    return result;
}
