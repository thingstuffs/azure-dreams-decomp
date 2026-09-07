#include "common.h"

typedef s32 M2C_UNK;
typedef void (*ObjectCallback)(void *, s32, s32);
typedef void (*ActorCallback)(void *, void *, s32);

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern s32 func_800352FC(void);
extern void func_8008B158(void *arg0);
extern s32 func_8008C180(s16 arg0, s16 arg1);
extern void func_8008F664(void *arg0, void *arg1);
extern void func_8009063C(void);
extern void func_8009065C(void *arg0, void *arg1, s32 arg2);
extern void func_8009539C(void *arg0);
extern void func_800953D0(void *arg0);
extern void func_80095460(void *arg0);
extern void func_8009550C(void *arg0);
extern void func_80095910(void *arg0);
extern s32 func_8009593C(void *arg0);
extern s16 func_80095978(void *arg0, void *arg1);
extern void func_80095A94(void *arg0, s16 arg1, void *arg2);
extern void func_80096FF4(void *arg0);
extern void func_80098868(void *arg0, void *arg1, s32 arg2);
extern void func_800A573C(void *arg0, void *arg1, s32 arg2);
extern s32 func_800C1D44(u16 arg0);

extern s16 D_8006ADD4[];
extern u8 D_80082BC0[];
extern u8 D_80090A64[];
extern u8 D_80097D2C[];
extern u8 D_800A5638[];
extern M2C_UNK D_800CFCB4;
extern u8 D_800FE488[];
extern M2C_UNK D_800FE490;

void func_800903FC(void *arg0, void *arg1, s32 arg2) {
    void *node;
    void *handler;
    u8 *base;
    u8 *object;
    u8 *work;
    s16 value;

    handler = FIELD(arg0, void *, 0);
    if (handler != D_80097D2C || handler != D_80090A64) {
        func_800953D0(arg1);
    }
    func_8009539C(arg1);

    handler = FIELD(arg0, void *, 0);
    if (handler != D_80097D2C || handler != D_80090A64) {
        func_80096FF4(arg1);
    }

    if (FIELD(arg1, s32, 8) > 0 && D_8006ADD4[0] != 12 &&
        FIELD(arg1, s32, 4) > 0x03FFFFFF) {
        if (func_800C1D44((u16)func_8008C180(FIELD(arg1, s16, 2),
                                                  FIELD(arg1, s16, 6))) == 0) {
            FIELD(arg1, s32, 8) = 0;
        }
    }

    func_80095460(arg1);

    work = (u8 *)&D_800FE490;
    FIELD(work, u16, 0x16) = FIELD(arg0, u16, 0x10);
    func_80095910(work);
    if (func_8009593C(work) != 0) {
        FIELD(arg0, s32, 0x2C) = 0;
        func_8008B158(FIELD(work, void *, 0x10));

        object = D_80082BC0;
        FIELD(object, ObjectCallback, 0x10)(object + 0x20, 0, 0);

        if (func_800352FC() != 0) {
            base = (u8 *)&D_800CFCB4;
            if (FIELD(base, u8, 0x3B) != 0) {
                node = FIELD(FIELD(base, void *, 0x20), void *, 8);
                if (FIELD(node, s32, 0xC) == 0 &&
                    FIELD(node, s32, 0x10) == 0 &&
                    FIELD(node, s32, 0x14) == 0) {
                    goto skip_update;
                }
            }

            {
                u8 *update_work;

                update_work = D_800FE488;
                value = func_80095978(arg1, update_work);
                func_80095A94(arg1, value, update_work);
            }

skip_update:
            func_8009550C(arg1);
            if (FIELD(arg0, void *, 0) != D_80097D2C) {
                func_80098868(arg0, arg1, arg2);
            }
        }
    }

    func_8008F664(&D_800CFCB4, arg1);
    FIELD(arg0, ActorCallback, 0)(arg0, arg1, arg2);

    if (FIELD(arg0, void *, -0x10) == D_800A5638) {
        func_800A573C(arg0, arg1, arg2);
        func_8009063C();
        return;
    }
    func_8009065C(arg0, arg1, arg2);
}

/* MECHANISM: The 0x28 frame and s2/s1/s3 argument holds preserve the retail prologue.
   A block-local update_work separates D_800FE488 from the earlier work lifetime.
   GCC coalesces both to s0 and emits the two-edge lui/addiu held base. */
