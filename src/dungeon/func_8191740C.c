#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_80024600_arg1.h"


extern void func_80024A34();
extern void func_80024D78() __attribute__((noreturn));
extern void func_800478B8();
extern s32 func_800644B8();
extern s32 func_80064584();
extern s32 D_800814A0;


typedef struct S_80024C0C_0 {
    void * unk_00;
    union { s16 s; u16 u; } unk_04;   /* accessed as both */
    u8 pad_06[0x8];
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
} S_80024C0C_0;   /* arg0 in func_80024C0C */

typedef struct S_80024C0C_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u16 unk_16;
} S_80024C0C_1;   /* object in func_80024C0C */



void func_80024C0C(void *arg0, void *arg1, void *arg2) {
    register s32 x ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 a0;
    s32 a1;
    s32 a2;
    s32 d0;
    u16 value;
    u8 byte;
    void *object;
    s32 *global;
    s16 state;

    object = ((S_80024C0C_0 *)arg0)->unk_00;
    ((S_80024C0C_1 *)object)->unk_14++;
    state = ((S_80024C0C_0 *)arg0)->unk_04.s;
    if (state == 0) {
        goto state0;
    }
    if (state == 1) {
        goto state1;
    }
    return;

state0:
    ((Rec_D_80082E80 *)arg2)->unk_1A.as_u16 += 0x200;
    x = func_800644B8(((S_80024C0C_0 *)arg0)->unk_0E);
    x = (x >> 4) * (func_800644B8(((S_80024C0C_0 *)arg0)->unk_10) >> 4);
    ((Rec_func_80024600_arg1 *)arg1)->unk_00 += x * 0x1C;
    x = func_800644B8(((S_80024C0C_0 *)arg0)->unk_0E);
    x = (x >> 4) * (func_80064584(((S_80024C0C_0 *)arg0)->unk_10) >> 4);
    ((Rec_func_80024600_arg1 *)arg1)->unk_04 += x * 0x1C;
    ((Rec_func_80024600_arg1 *)arg1)->unk_08 += (func_80064584(((S_80024C0C_0 *)arg0)->unk_0E) >> 4) * 0x1C00;
    x = func_800644B8(((S_80024C0C_0 *)arg0)->unk_0E);
    x = (x >> 4) * (func_800644B8(((S_80024C0C_0 *)arg0)->unk_10) >> 4);
    a1 = ((Rec_func_80024600_arg1 *)arg1)->unk_00;
    state = ((S_80024C0C_0 *)arg0)->unk_12;
    a2 = a1 + x * 0x1C;
    if (state != 0) {
        s32 cmp;

        a0 = ((Rec_func_80024600_arg1 *)arg1)->unk_0C;
        cmp = a0 < a1;
        ASM_TAILSLOT_PIN(cmp);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        func_80024D78(a0, a1, a2);
        return;
    }
    a0 = ((Rec_func_80024600_arg1 *)arg1)->unk_0C;
    if (a1 < a0) {
        register s32 d1 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

        d1 = a1 - a0;
        if (d1 < 0) {
            d1 = -d1;
        }
        ASM_KEEP(d1);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        d0 = a2 - a0;
        if (d0 < 0) {
            d0 = -d0;
        }
        if (d0 < d1) {
            goto done;
        }
        ASM_KEEP(d1);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    }
    func_80024A34(arg0, arg1, arg2);
    ((S_80024C0C_0 *)arg0)->unk_04.u++;
    return;

state1:
    if (((Rec_D_80082E80 *)arg2)->unk_0C.at00_u8.v != 0) {
        byte = ((Rec_D_80082E80 *)arg2)->unk_0C.at02_u8.v - 0x20;
        ((Rec_D_80082E80 *)arg2)->unk_0C.at02_u8.v = byte;
        ((Rec_D_80082E80 *)arg2)->unk_0C.at01_u8.v = byte;
        ((Rec_D_80082E80 *)arg2)->unk_0C.at00_u8.v = byte;
    }
    value = ((Rec_D_80082E80 *)arg2)->unk_1C.at02_u16.v + 0x400;
    ((Rec_D_80082E80 *)arg2)->unk_1C.at02_u16.v = value;
    ((Rec_D_80082E80 *)arg2)->unk_1C.at00_u16.v = value;
    func_800478B8(arg2);
    func_800478B8(arg2);
    if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x6000) {
        object = ((S_80024C0C_0 *)arg0)->unk_00;
        ((S_80024C0C_1 *)object)->unk_16++;
        global = &D_800814A0;
        (*(u16 *)((u8 *)arg0 + (-2))) |= 0x8000;
        *global |= 0x8000;
    }

done:
    return;
}
