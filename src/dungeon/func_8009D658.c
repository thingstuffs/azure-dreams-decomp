#include "common.h"

#ifndef NULL
#define NULL 0
#endif


extern void *D_800E3D7C[];

extern void func_800A2D68(void *, s32);
extern void func_800B4C7C(s32, void *, s16, s32);


typedef struct S_800A2DB8_0 {
    u8 pad_00[0x6];
    union { u16 u; s16 s; } unk_06;   /* accessed as both */
    u8 pad_08[0x9];
    u8 unk_11;
    u8 pad_12[0x42];
    s32 unk_54;
    u8 pad_58[0x8];
    void * unk_60;
} S_800A2DB8_0;   /* arg0 in func_800A2DB8 */

typedef struct S_800A2DB8_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    u8 pad_14[0x40];
    s32 unk_54;
} S_800A2DB8_1;   /* initial_target in func_800A2DB8 */

typedef struct S_800A2DB8_2 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_800A2DB8_2;   /* slot in func_800A2DB8 */

typedef struct S_800A2DB8_3 {
    u8 pad_00[0x11];
    u8 unk_11;
    u8 pad_12[0x16];
    u8 unk_28;
} S_800A2DB8_3;   /* member in func_800A2DB8 */

typedef struct S_800A2DB8_4 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800A2DB8_4;   /* target in func_800A2DB8 */

typedef struct S_800A2DB8_5 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_800A2DB8_5;   /* (u8 *)D_800E3D7C[0] + index * 4 in func_800A2DB8 */

typedef struct S_800A2DB8_6 {
    u8 pad_00[0x3D7C];
    void * unk_3D7C;
} S_800A2DB8_6;   /* global_page in func_800A2DB8 */

typedef struct S_800A2DB8_7 {
    u8 pad_00[0x11];
    u8 unk_11;
    u8 pad_12[0x16];
    u8 unk_28;
} S_800A2DB8_7;   /* global_member in func_800A2DB8 */

typedef struct S_800A2DB8_8 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800A2DB8_8;   /* final_target in func_800A2DB8 */

s32 func_800A2DB8(S_800A2DB8_0 *arg0)
{
    void *initial_target;
    void *target;
    S_800A2DB8_8 *final_target;
    S_800A2DB8_7 *global_member;
    S_800A2DB8_3 *member;
    u8 *slot;
    u8 *global_page;
    s32 count;
    register s32 index ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    s32 diff;
    s32 amount;
    s32 numerator;
    s32 opcode;
    s32 result;
    s32 shift;

    initial_target = arg0->unk_60;
    result = 0;
    if (initial_target == NULL) {
        goto done;
    }
    if (((S_800A2DB8_1 *)initial_target)->unk_13 < 0) {
        goto done;
    }

    result = arg0->unk_06.u;
    if (((S_800A2DB8_1 *)initial_target)->unk_54 & 0x20) {
        result *= 2;
    }

    count = 1;
    if (arg0->unk_54 & 0x40) {
        result *= 2;
    }

    ASM_KEEP(count);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    index = count;
    slot = (u8 *)D_800E3D7C[0] + 4;
    do {
        member = ((S_800A2DB8_2 *)slot)->unk_AC;
        if ((member != NULL) && (member->unk_28 != 0)) {
            count++;
        }
        index--;
        slot -= 4;
    } while (index >= 0);

    numerator = result + count;
    target = arg0->unk_60;
    result = (numerator - 1) / count;

    if (((S_800A2DB8_4 *)target)->unk_14 & 0x4000) {
        index = 1;
        do {
            member = ((S_800A2DB8_5 *)((u8 *)D_800E3D7C[0] + index * 4))->unk_AC;
            if ((member != NULL) && (member->unk_28 != 0)) {
                diff = member->unk_11 - arg0->unk_11;
                amount = result;
                if (diff < 0) {
                    shift = (diff < 2) ^ 1;
                    amount = result + (result >> shift);
                }
                func_800B4C7C(0x82, member, (s16)amount, 1);
                func_800A2D68(member, amount & 0xFFFF);
            }
            index--;
        } while (index >= 0);

        global_page = (u8 *)0x800E0000;
        global_member = ((S_800A2DB8_6 *)global_page)->unk_3D7C;
        if (global_member->unk_28 == 0) {
            return 0;
        }
        diff = global_member->unk_11 - arg0->unk_11;
        amount = result;
        if (diff < 0) {
            shift = (diff < 2) ^ 1;
            amount = result + (result >> shift);
        }
        func_800A2D68(global_member, amount & 0xFFFF);
        func_800B4C7C(0x82, ((S_800A2DB8_6 *)global_page)->unk_3D7C, (s16)amount, 1);
        return amount;
    }

    result = arg0->unk_06.u;
    func_800A2D68(target, result);
    final_target = arg0->unk_60;
    opcode = 0x83;
    if (final_target->unk_14 & 0x2000) {
        opcode = 0x82;
    }
    func_800B4C7C(opcode, final_target, arg0->unk_06.s, 1);
done:
    return result;
}

/* MECHANISM: The 0x28 frame follows from s4=arg0, s3=result, s2=amount,
   s1=index, and s0=loop member; guarded pins preserve the measured volatile roles.
   Splitting numerator/shift live ranges and the global member lets v1/v0 hold the
   arithmetic while the 0x800e page and its loaded member naturally take s0/a0. */
