#include "common.h"

typedef struct S_80FE1000_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80FE1000_0;   /* obj in BODY_NAME */

typedef struct S_80FE1000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80FE1000_1;   /* work in BODY_NAME */

typedef struct S_80FE1000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80FE1000_2;   /* part_a in BODY_NAME */

typedef struct S_80FE1000_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80FE1000_3;   /* part_b in BODY_NAME */

typedef struct S_80FE1000_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80FE1000_4;   /* actor in BODY_NAME */



extern void *func_8003FD64();
extern void func_8004491C();
extern s32 func_800A6D30();
extern void func_800A48F0();
extern void func_800A9C18();
extern void func_800AA36C();

extern s32 D_80045340;
extern u8 D_80083498[];
extern u8 D_8016AA7C[];
extern u8 D_8016E038[];
extern u8 D_8016E088[];
extern u8 D_8016AEA8[];

#ifdef __mips__
extern void *func_8016A8A8(s16, s8, s8, s16);
extern void *func_8016B2B8(void);
extern void *func_8016B2E4(void);
extern void *func_8016B264(void);
extern void *func_8016B1F4(void);
extern void *func_8016B1E4(void);
extern void *func_8016B2A8(void);
extern void *func_8016CAC4(void);
extern void *func_8016CABC(void);
extern void *func_8016CAB4(void);
extern void *func_8016CACC(void);
extern void *func_8016CA74(void);
extern void *func_8016CA6C(void);
extern void *func_8016CA64(void);

static const u32 func_8016A800_prefix[42] __asm__("func_8016A800")
    __attribute__((section(".text.func_8016A800"), aligned(4))) = {
        (u32)func_8016A8A8,
        (u32)D_8016AA7C,
        (u32)func_8016B2B8,
        (u32)func_8016B2B8,
        (u32)func_8016B2B8,
        (u32)func_8016B2E4,
        (u32)func_8016B264,
        (u32)func_8016B264,
        (u32)func_8016B264,
        (u32)func_8016B1F4,
        (u32)func_8016B1E4,
        (u32)func_8016B2E4,
        (u32)func_8016B2E4,
        (u32)func_8016B2A8,
        (u32)func_8016CAC4,
        (u32)func_8016CABC,
        (u32)func_8016CAB4,
        (u32)func_8016CACC,
        (u32)func_8016CA74,
        (u32)func_8016CA6C,
        (u32)func_8016CA64,
        0x89824081,
        0x40819382,
        0x93829082,
        0x83829982,
        0x85828882,
        0x7C818482,
        0x90829582,
        0x00004481,
        0x92824081,
        0x96828582,
        0x81828582,
        0x85828C82,
        0x40818482,
        0x94828982,
        0x40819382,
        0x92829482,
        0x85829582,
        0x90824081,
        0x97828F82,
        0x92828582,
        0x00004481,
    };
__asm__(".globl func_8016A800\n"
        ".size func_8016A800, 636");
#define BODY_NAME func_8016A8A8
#else
#define BODY_NAME func_8016A800
#endif

void *BODY_NAME(s16 arg0, s8 arg1, s8 arg2, s16 arg3)
{
    s32 kind;
    void *obj;
    void *part_a;
    S_80FE1000_3 *part_b;
    void *work;
    S_80FE1000_4 *actor;
    s32 left;
    s32 right;
    register s8 saved_arg1 ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s16 saved_arg3;
    register s8 saved_arg2 ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s16 call_arg0;
    register void *call_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *call_a1;

    work = 0;
    saved_arg1 = arg1;
    saved_arg3 = arg3;
    saved_arg2 = arg2;
    obj = func_8003FD64(0x112, D_80083498);
    if (obj != 0) {
        call_arg0 = arg0;
        ASM_KEEP(call_arg0);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        work = (u8 *)obj + 0x20;
        ((S_80FE1000_0 *)obj)->unk_10 = D_8016AA7C;
        ((S_80FE1000_1 *)work)->unk_13 = 0x28;
        func_8004491C(obj, &D_80045340);

        part_a = ((S_80FE1000_0 *)obj)->unk_08;
        ((S_80FE1000_2 *)part_a)->unk_0A = saved_arg3;
        part_b = ((S_80FE1000_0 *)obj)->unk_0C;
        kind = arg0 & 3;
        part_b->unk_25 = saved_arg2;
        actor = work;
        part_b->unk_2C = D_8016E038;
        part_b->unk_24 = saved_arg1;

        if (kind == 1) {
            left = ((S_80FE1000_1 *)work)->unk_14 | 0x6000;
            right = ((S_80FE1000_1 *)work)->unk_1C | 0x6000;
            goto write_kind;
        }
        if (kind < 2) {
            goto normal_kind;
        }

        left = ((S_80FE1000_1 *)work)->unk_14 | 0x2000;
        right = ((S_80FE1000_1 *)work)->unk_1C | 0x2000;
write_kind:
        ((S_80FE1000_1 *)work)->unk_14 = left;
        ((S_80FE1000_1 *)work)->unk_1C = right;
        goto post_kind;

normal_kind:
        call_a0 = obj;
        if (((arg0 & ~3) << 16) != 0) {
            goto call_a1_setup;
        }
        call_a1 = part_a;
        if (((S_80FE1000_1 *)work)->unk_14 & 0x200) {
            goto call_a2_setup;
        }
        left = func_800A6D30(call_a0, call_a1);
        call_a0 = obj;
        if (!(left & 1)) {
            goto call_a1_setup;
        }
        ((S_80FE1000_1 *)work)->unk_1C |= 0x200;
        func_800A48F0(work, 1,
                      (func_800A6D30(obj) & 0x3F) | 0x20);
        part_b->unk_2C = D_8016E088;
        goto post_kind;

post_kind:
        call_a0 = obj;
call_a1_setup:
        call_a1 = part_a;
call_a2_setup:
        func_800A9C18(call_a0, call_a1, part_b, call_arg0);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &D_8016AEA8;
        func_800AA36C(actor, part_a, part_b, work);
    }
    return work;
}
