#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_8016A800_0 {
    u8 pad_00[0x13];
    s8 unk_13;
    u32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
    u8 pad_20[0x6C];
    void * unk_8C;
} S_8016A800_0;   /* result in func_8016A800 */

typedef struct S_8016A800_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_8016A800_1;   /* root in func_8016A800 */

typedef struct S_8016A800_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8016A800_2;   /* position in func_8016A800 */

typedef struct S_8016A800_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_8016A800_3;   /* arg3_part in func_8016A800 */

typedef struct S_8016A800_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_8016A800_4;   /* (void *)arg2_work in func_8016A800 */



extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern s32 func_800A6D30(void);
extern void func_800A48F0(void *, s32, s32);
extern void func_800A9C18(void *, void *, void *, s16);
extern void func_800AA36C(void *, void *, void *, void *);

extern u8 D_80045340[];
extern u8 D_80083498[];
extern u8 D_8016AA58[];
extern u8 D_8016AE5C[];
extern u8 D_8016E510[];
extern u8 D_8016E538[];

void *func_8016A800(s32, s32, s32, s32);

#ifdef __mips__
extern void func_8016B2A0(void);
extern void func_8016B2CC(void);
extern void func_8016B24C(void);
extern void func_8016B198(void);
extern void func_8016B1D0(void);
extern void func_8016B290(void);
extern void func_8016CB74(void);
extern void func_8016CB6C(void);
extern void func_8016CB64(void);
extern void func_8016CB7C(void);
extern void func_8016CB24(void);
extern void func_8016CB1C(void);
extern void func_8016CB14(void);

static void (*const func_8016A800_table[])(void)
    __attribute__((section(".text.func_8016A800"))) = {
        (void (*)(void))func_8016A800,
        0,
        func_8016B2A0,
        func_8016B2A0,
        func_8016B2A0,
        func_8016B2CC,
        func_8016B24C,
        func_8016B24C,
        func_8016B24C,
        func_8016B198,
        func_8016B1D0,
        func_8016B2CC,
        func_8016B2CC,
        func_8016B290,
        func_8016CB74,
        func_8016CB6C,
        func_8016CB64,
        func_8016CB7C,
        func_8016CB24,
        func_8016CB1C,
        func_8016CB14,
    };
#endif

void *func_8016A800(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    void *result = NULL;
    register s32 arg1_role ASM_REG("$21");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    void *root;
    void *position;
    register s32 saved_arg0 ASM_REG("$23");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s32 opcode ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register void *factory ASM_REG("$5");   /* MATCH pin: retail schedule: same instructions, different order without it */
    s32 kind;

    {
    register void *arg3_part ASM_REG("$17");   /* MATCH pin: retail schedule: same instructions, different order without it */
    void *arg2_work;

    opcode = 0x112;
    arg1_role = arg1;
    factory = D_80083498;
    arg3_part = (void *)arg3;
    arg2_work = (void *)arg2;
    ASM_KEEP_DEP_NV(arg1_role, opcode);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP_DEP_NV(arg3_part, factory);   /* MATCH pin: retail schedule: same instructions, different order without it */
    root = func_8003FD64(opcode, factory);
    if (root != NULL) {
        saved_arg0 = arg0;
        ASM_USE_NV(saved_arg0);   /* MATCH pin: retail schedule: same instructions, different order without it */
        result = (u8 *)root + 0x20;
        ((S_8016A800_0 *)result)->unk_13 = 0x1C;
        func_8004491C(root, D_80045340);

        position = ((S_8016A800_1 *)root)->unk_08;
        kind = arg0 & 3;
        ((S_8016A800_2 *)position)->unk_0A = (s16)(s32)arg3_part;
        arg3_part = ((S_8016A800_1 *)root)->unk_0C;
        ((S_8016A800_3 *)arg3_part)->unk_25 = (s8)(s32)arg2_work;
        arg2_work = result;
        ((S_8016A800_3 *)arg3_part)->unk_24 = (s8)arg1_role;

        if (kind == 1) {
            ((S_8016A800_0 *)result)->unk_8C = D_8016AE5C;
            ((S_8016A800_0 *)result)->unk_14 |= 0x6000;
            ((S_8016A800_0 *)result)->unk_1C |= 0x6000;
            ((S_8016A800_3 *)arg3_part)->unk_2C = D_8016E510;
            goto after_state;
        }
        if (kind >= 2) {
            ((S_8016A800_0 *)result)->unk_8C = D_8016AE5C;
            ((S_8016A800_0 *)result)->unk_14 |= 0x2000;
            ((S_8016A800_0 *)result)->unk_1C |= 0x2000;
            ((S_8016A800_3 *)arg3_part)->unk_2C = D_8016E510;
            goto after_state;
        }

        if ((s16)(arg0 & ~3) == 0) {
            if (!(((S_8016A800_0 *)result)->unk_14 & 0x200) &&
                    (func_800A6D30() & 1)) {
                func_800A48F0(result, 1, (func_800A6D30() & 0x3F) | 0x20);
                ((S_8016A800_3 *)arg3_part)->unk_2C = D_8016E538;
            }
            ((S_8016A800_4 *)((void *)arg2_work))->unk_8C = D_8016AE5C;
        } else {
            ((S_8016A800_0 *)result)->unk_8C = D_8016AE5C;
        }

        ASM_KEEP(arg0);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        ((S_8016A800_3 *)arg3_part)->unk_2C = D_8016E510;
after_state:
        ((S_8016A800_1 *)root)->unk_10 = D_8016AA58;
        func_800A9C18(root, position, arg3_part, (s16)saved_arg0);
        ((S_8016A800_4 *)((void *)arg2_work))->unk_9A = 0xFF;
        ((S_8016A800_4 *)((void *)arg2_work))->unk_9C = -1;
        func_800AA36C(arg2_work, position, arg3_part, result);
    }
    }
    return result;
}
