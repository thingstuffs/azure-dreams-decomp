#include "common.h"

typedef struct Entity {
    u8 pad[0x13];
    u8 unk_13;
    u32 flags;
    u8 pad2[0x110 - 0x18];
    s32 unk_110;
} Entity;

typedef struct Struct_80083460 {
    u8 pad[10];
    u16 count;
} Struct_80083460;

extern Entity *D_800E3D7C;
extern u8 D_80083780[];
extern u8 D_80082E80[];
extern s32 D_80012090;
extern s16 D_8008146C;
extern Struct_80083460 D_80083460;
extern u8 D_80089384[];
extern u8 D_800E15FE[];
extern u8 D_800E1677[];

s32 func_80033BC0(s32);
void func_8008D330(Entity *, void *, void *, Entity *);
void func_80098B38(s32);
s32 func_800990FC(void);
s32 func_80099194(void *, s32);
void func_80099290(s32);
s32 func_80099368(s32, s32);
s32 func_80099734(Entity *, s32);
void func_800997FC(void *);
void func_800A5720(s32);
void func_800A5F38(Entity *, s32);
void func_800A63B8(Entity *, s32, s16);
s32 func_800C2C7C(Entity *);

s32 func_800C261C(Entity *arg0, s32 arg1, s16 arg2) {
    if (arg0 == D_800E3D7C) {
        arg0->unk_110 = arg1;
        func_8008D330(arg0, D_80083780, D_80082E80, arg0);
        return 0;
    }
    if (arg0->flags & 0x4000) {
        if ((u32)(arg0->unk_13 - 3) < 0x2B) {
            if (D_80012090 == 0 && D_8008146C == 0x28 && func_80033BC0(0xA2) == 0) {
                Struct_80083460 *counter;
                func_800997FC(D_800E15FE);
                counter = &D_80083460;
                counter->count--;
                func_80098B38(arg1);
                return 1;
            }
            if (func_800C2C7C(arg0) != 0) {
                func_80098B38(arg1);
                goto block_20;
            }
            return 0;
        }
        {
            register Entity *call_arg ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            register s32 pass_val ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            register s32 saved_val ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            s32 res;

            res = func_800990FC();
            call_arg = arg0;
            pass_val = res;
            saved_val = pass_val;
            func_80099290(func_80099194(D_80089384, func_80099368(arg1, func_80099194(D_800E1677, func_80099734(call_arg, pass_val)))));
            func_800A5720(saved_val);
            func_800A5F38(arg0, arg1);
        }
        return 1;
    }
    if ((u32)(arg0->unk_13 - 3) < 0x2B) {
        if (func_800C2C7C(arg0) != 0) {
            goto block_20;
        }
        return 0;
    }
    func_800A63B8(arg0, arg1, arg2);
block_20:
    {
        Struct_80083460 *counter = &D_80083460;
        counter->count--;
    }
    return 1;
}
