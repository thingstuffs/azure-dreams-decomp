#include "common.h"

typedef struct S_80FFF000_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80FFF000_0;   /* created in BODY_NAME */

typedef struct S_80FFF000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    u32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
} S_80FFF000_1;   /* result in BODY_NAME */

typedef struct S_80FFF000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80FFF000_2;   /* position in BODY_NAME */

typedef struct S_80FFF000_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80FFF000_3;   /* part_b in BODY_NAME */

typedef struct S_80FFF000_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80FFF000_4;   /* actor in BODY_NAME */



extern void *func_8003FD64();
extern void func_8004491C();
extern void func_800A48F0();
extern s32 func_800A6D30();
extern void func_800A9C18();
extern void func_800AA36C();

extern s32 D_80045340;
extern u8 D_80083498[];
extern u8 D_8014CA7C[];
extern u8 D_8014CEA8[];
extern u8 D_80150038[];
extern u8 D_80150088[];
extern u8 D_8014D2B8[];
extern u8 D_8014D2E4[];
extern u8 D_8014D264[];
extern u8 D_8014D1F4[];
extern u8 D_8014D1E4[];
extern u8 D_8014D2A8[];
extern u8 D_8014EAC4[];
extern u8 D_8014EABC[];
extern u8 D_8014EAB4[];
extern u8 D_8014EACC[];
extern u8 D_8014EA74[];
extern u8 D_8014EA6C[];
extern u8 D_8014EA64[];

#ifdef __mips__
extern void *func_8014C8A8(void *, s32, s32, s32);

static const u32 bank_words[] __asm__("func_8014C800")
    __attribute__((section(".text.func_8014C800"), aligned(4))) = {
    (u32)func_8014C8A8,
    (u32)D_8014CA7C,
    (u32)D_8014D2B8,
    (u32)D_8014D2B8,
    (u32)D_8014D2B8,
    (u32)D_8014D2E4,
    (u32)D_8014D264,
    (u32)D_8014D264,
    (u32)D_8014D264,
    (u32)D_8014D1F4,
    (u32)D_8014D1E4,
    (u32)D_8014D2E4,
    (u32)D_8014D2E4,
    (u32)D_8014D2A8,
    (u32)D_8014EAC4,
    (u32)D_8014EABC,
    (u32)D_8014EAB4,
    (u32)D_8014EACC,
    (u32)D_8014EA74,
    (u32)D_8014EA6C,
    (u32)D_8014EA64,
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
    0x12004481,
};
__asm__(".globl func_8014C800\n"
        ".size func_8014C800, 636");
#define BODY_NAME func_8014C8A8
#define BODY_ATTR __attribute__((section(".text.func_8014C800")))
#else
#define BODY_NAME func_8014C800
#define BODY_ATTR
#endif

void *BODY_NAME(void *arg0, s32 arg1, s32 arg2, s32 arg3) BODY_ATTR;

void *BODY_NAME(void *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    void *result = 0;
    void *created;
    register void *position ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    S_80FFF000_3 *part_b;
    S_80FFF000_4 *actor;
    s32 left;
    s32 right;
    s16 saved_arg1;
    s32 saved_arg3;
    s16 saved_arg2;
    register s32 saved_arg0 = (s32)arg0;
    s16 original_arg0;
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
    ((S_80FFF000_0 *)created)->unk_10 = D_8014CA7C;
    ((S_80FFF000_1 *)result)->unk_13 = 0x28;
    func_8004491C(created, &D_80045340);

    position = ((S_80FFF000_0 *)created)->unk_08;
    ((S_80FFF000_2 *)position)->unk_0A = saved_arg3;
    part_b = ((S_80FFF000_0 *)created)->unk_0C;
    kind = saved_arg0 & 3;
    part_b->unk_25 = saved_arg2;
    actor = result;
    part_b->unk_2C = D_80150038;
    part_b->unk_24 = saved_arg1;

    if (kind == 1) {
        ((S_80FFF000_1 *)result)->unk_14 |= 0x6000;
        ((S_80FFF000_1 *)result)->unk_1C |= 0x6000;
        goto setup;
    }
    if (kind >= 2) {
        ((S_80FFF000_1 *)result)->unk_14 |= 0x2000;
        ((S_80FFF000_1 *)result)->unk_1C |= 0x2000;
        goto setup;
    }

    call_a0 = created;
    if (((saved_arg0 & ~3) << 16) == 0) {
        if (!(((S_80FFF000_1 *)result)->unk_14 & 0x200)) {
            call_a1 = position;
            if (func_800A6D30() & 1) {
                ((S_80FFF000_1 *)result)->unk_1C |= 0x200;
                func_800A48F0(result, 1,
                    (func_800A6D30() & 0x3F) | 0x20);
                part_b->unk_2C = D_80150088;
            }
        }
    }

setup:
    func_800A9C18(created, position, part_b,
        (s16)original_arg0);
    actor->unk_9A = 0xFF;
    actor->unk_9C = -1;
    actor->unk_8C = D_8014CEA8;
    func_800AA36C(actor, position, part_b, result);

done:
    return result;
}
