#include "common.h"

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))

typedef s32 M2C_UNK;

extern void *func_8003FD64();
extern void func_8004491C();
extern s32 func_800A6D30();
extern void func_800A48F0();
extern void func_800A9C18();
extern void func_800AA36C();
extern s32 D_80045340;
extern u8 D_80083498[];
extern u8 D_8014CA30[];
extern M2C_UNK D_8014CE5C;
extern u8 D_8014FD0C[];
extern u8 D_8014FD4C[];

void *func_8014C854(s16 arg0, s8 arg1, s8 arg2, s16 arg3)
{
    s32 kind;
    register void *work ASM_REG("$16") = 0;
    register void *obj ASM_REG("$17");
    void *part_a;
    void *part_b;
    void *actor;
#ifdef __mips__
    register u32 initial_callback ASM_REG("$2");
#else
    void *initial_callback;
#endif
    register void *call_a0 ASM_REG("$4");
    s32 left;
    s32 right;
    s8 saved_arg1;
    s16 saved_arg3;
    s8 saved_arg2;

    saved_arg1 = arg1;
    saved_arg2 = arg2;
    saved_arg3 = arg3;
    ASM_KEEP_DEP_NV(saved_arg2, saved_arg3);
    obj = func_8003FD64(0x112, D_80083498);
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ASM_KEEP(work);
        actor = work;
        FIELD(obj, void *, 0x10) = D_8014CA30;
        FIELD(work, s8, 0x13) = 0xD;
        func_8004491C(obj, &D_80045340);

#ifdef __mips__
        initial_callback = 0x80150000;
        ASM_KEEP_NV(initial_callback);
#else
        initial_callback = D_8014FD0C;
#endif
        part_a = FIELD(obj, void *, 8);
#ifdef __mips__
        initial_callback -= 0x2F4;
#endif
        FIELD(part_a, s16, 0xA) = saved_arg3;
        part_b = FIELD(obj, void *, 0xC);
        kind = arg0 & 3;
        FIELD(part_b, s8, 0x25) = saved_arg2;
        FIELD(part_b, void *, 0x2C) = (void *)initial_callback;
        FIELD(part_b, s8, 0x24) = saved_arg1;

        if (kind == 1) {
            left = FIELD(work, s32, 0x14) | 0x6000;
            right = FIELD(work, s32, 0x1C) | 0x6000;
            goto write_kind;
        }
        if (kind < 2) {
            goto normal_kind;
        }

        left = FIELD(work, s32, 0x14) | 0x2000;
        right = FIELD(work, s32, 0x1C) | 0x2000;
write_kind:
        FIELD(work, s32, 0x14) = left;
        FIELD(work, s32, 0x1C) = right;
        goto post_kind;

normal_kind:
        call_a0 = obj;
        if (((arg0 & ~3) << 16) == 0) {
            if (!(FIELD(work, s32, 0x14) & 0x200)) {
                left = func_800A6D30();
                call_a0 = obj;
                if (!(left & 1)) {
                    goto call_a1_setup;
                }
                FIELD(work, s32, 0x1C) |= 0x200;
                func_800A48F0(work, 1,
                              (func_800A6D30(obj) & 0x3F) | 0x20);
                FIELD(part_b, void *, 0x2C) = D_8014FD4C;
                goto post_kind;
            }
        }
        goto call_a1_setup;

post_kind:
        call_a0 = obj;
call_a1_setup:
        func_800A9C18(call_a0, part_a, part_b, arg0);
        FIELD(actor, u8, 0x9A) = 0xFF;
        FIELD(actor, s8, 0x9C) = -1;
        FIELD(actor, void *, 0x8C) = &D_8014CE5C;
        FIELD(actor, s16, 0xA4) = -1;
        func_800AA36C(actor, part_a, part_b, work);
    }
    return work;
}
