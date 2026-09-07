#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void *D_800E3D7C[];

extern void func_800A2D68(void *, s32);
extern void func_800A2FBC(void);
extern void func_800B4C7C(s32, void *, s16, s32);

s32 func_800A2DB8(void *arg0)
{
    register void *initial_target ASM_REG("$3");
    register void *target ASM_REG("$4");
    void *final_target;
    void *global_member;
    void *member;
    u8 *slot;
    u8 *global_page;
    register s32 count ASM_REG("$5");
    register s32 index ASM_REG("$17");
    s32 diff;
    s32 amount;
    register s32 numerator ASM_REG("$3");
    s32 opcode;
    s32 result;
    register s32 shift ASM_REG("$2");

    initial_target = FIELD(arg0, void *, 0x60);
    ASM_KEEP(initial_target);
    result = 0;
    if (initial_target == NULL) {
        goto done;
    }
    if (FIELD(initial_target, s8, 0x13) < 0) {
        goto done;
    }

    result = FIELD(arg0, u16, 6);
    if (FIELD(initial_target, s32, 0x54) & 0x20) {
        result *= 2;
    }

    count = 1;
    if (FIELD(arg0, s32, 0x54) & 0x40) {
        result *= 2;
    }

    ASM_KEEP(count);
    index = count;
    slot = (u8 *)D_800E3D7C[0] + 4;
    do {
        member = FIELD(slot, void *, 0xAC);
        if ((member != NULL) && (FIELD(member, u8, 0x28) != 0)) {
            count++;
        }
        index--;
        slot -= 4;
    } while (index >= 0);

    numerator = result + count;
    ASM_KEEP(numerator);
    target = FIELD(arg0, void *, 0x60);
    result = (numerator - 1) / count;

    if (FIELD(target, s32, 0x14) & 0x4000) {
        index = 1;
        do {
            member = FIELD((u8 *)D_800E3D7C[0] + index * 4, void *, 0xAC);
            if ((member != NULL) && (FIELD(member, u8, 0x28) != 0)) {
                diff = FIELD(member, u8, 0x11) - FIELD(arg0, u8, 0x11);
                amount = result;
                if (diff < 0) {
                    shift = (diff < 2) ^ 1;
                    ASM_KEEP(shift);
                    amount = result + (result >> shift);
                }
                func_800B4C7C(0x82, member, (s16)amount, 1);
                func_800A2D68(member, amount & 0xFFFF);
            }
            index--;
        } while (index >= 0);
        ASM_KEEP(index);

        global_page = (u8 *)0x800E0000;
        global_member = FIELD(global_page, void *, 0x3D7C);
        if (FIELD(global_member, u8, 0x28) == 0) {
            return 0;
        }
        diff = FIELD(global_member, u8, 0x11) - FIELD(arg0, u8, 0x11);
        amount = result;
        if (diff < 0) {
            shift = (diff < 2) ^ 1;
            ASM_KEEP(shift);
            amount = result + (result >> shift);
        }
        func_800A2D68(global_member, amount & 0xFFFF);
        func_800B4C7C(0x82, FIELD(global_page, void *, 0x3D7C), (s16)amount, 1);
        func_800A2FBC();
        return amount;
    }

    result = FIELD(arg0, u16, 6);
    ASM_KEEP(target);
    func_800A2D68(target, result);
    final_target = FIELD(arg0, void *, 0x60);
    opcode = 0x83;
    if (FIELD(final_target, s32, 0x14) & 0x2000) {
        opcode = 0x82;
    }
    func_800B4C7C(opcode, final_target, FIELD(arg0, s16, 6), 1);
done:
    return result;
}

/* MECHANISM: The 0x28 frame follows from s4=arg0, s3=result, s2=amount,
   s1=index, and s0=loop member; guarded pins preserve the measured volatile roles.
   Splitting numerator/shift live ranges and the global member lets v1/v0 hold the
   arithmetic while the 0x800e page and its loaded member naturally take s0/a0. */
