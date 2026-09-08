#include "common.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80172620_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x8];
    union { void * s; s32 u; } unk_A4;   /* accessed as both */
} S_80172620_0;   /* arg0 in func_80172620 */


typedef struct S_80172620_2 {
    u8 pad_00[0x2A];
    union { s16 s; u16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    s8 unk_6D;
} S_80172620_2;   /* arg3 in func_80172620 */

typedef struct S_80172620_3 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    u8 * unk_10;
    u8 pad_14[0x36];
    u16 unk_4A;
    u8 pad_4C[0x6F];
    u8 unk_BB;
} S_80172620_3;   /* created in func_80172620 */

typedef struct S_80172620_4 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x2];
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x8];
    s32 unk_28;
    u8 * unk_2C;
} S_80172620_4;   /* child in func_80172620 */

typedef struct S_80172620_5 {
    u8 pad_00[0xBB];
    u8 unk_BB;
} S_80172620_5;   /* pending in func_80172620 */



typedef struct Copy24 {
    s32 word[6];
} Copy24;

extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, s32, s32);
extern s32 rand(void);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

extern s32 D_80045340;
extern s16 D_80083228;
extern s32 D_8008346C;
extern u8 D_80083498[];
extern u8 D_800D7960[];
extern void *D_800E3DE8;
extern u8 D_80170E54;
extern u8 D_80173CA4[];
extern u8 D_80173CAC[];
extern u8 D_80173CB4[];
extern u8 D_80173CBC[];

void func_80172620(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 state;
    void *ret;
    void *created;
    void *child;
    void *copy_dst;

    ((S_80172620_0 *)arg0)->unk_96--;
    state = ((S_80172620_0 *)arg0)->unk_9B;
    if (state == 2) {
        goto state_two;
    }
    if (state < 3) {
        if (state == 0) {
            goto state_zero;
        }
        if (state == 1) {
            goto state_one;
        }
        goto done;
    }
    if (state == 3) {
        goto state_three;
    }
    if (state == 0xFF) {
        goto state_ff;
    }
    goto done;

state_zero:
    if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000) {
        ((S_80172620_0 *)arg0)->unk_9B = 0xFF;
        ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v |= 0x6000;
        func_8009C12C(arg3, arg2, ((S_80172620_2 *)arg3)->unk_2A.s, 1);
        goto done;
    }

    if (rand() & 3) {
        ((Rec_D_80082E80 *)arg2)->unk_2C.as_pu8 = D_80173CBC;
        (*(s32 *)((u8 *)arg0 + 0xA4)) = 0;
        func_80047784(arg2,
            ((Rec_D_80082E80 *)arg2)->unk_2C.as_pu8
                [((D_80083228 + ((S_80172620_2 *)arg3)->unk_2A.s + 0x100) >> 9) & 7],
            0);
        ((S_80172620_0 *)arg0)->unk_9B = 3;
        goto done;
    }
    (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_80173CA4;
    func_80047784(arg2,
        D_80173CA4[((D_80083228 + ((S_80172620_2 *)arg3)->unk_2A.s + 0x100) >> 9) & 7],
        0);
    ((S_80172620_0 *)arg0)->unk_9B++;
    goto done;

state_one:
    if ((((Rec_D_80082E80 *)arg2)->unk_04.as_s8 == 2) &&
        (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x1000)) {
        ret = func_8003FD64(0x112, D_80083498);
        created = ret;
        ASM_KEEP(ret);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        ((S_80172620_0 *)arg0)->unk_A4.s = ret;
        if (created != 0) {
            s32 linked_field;
            s32 child_field;

            func_8004491C(created, &D_80045340);
            ((S_80172620_3 *)created)->unk_10 = D_800D7960;
            copy_dst = ((S_80172620_3 *)created)->unk_08;
            *(Copy24 *)copy_dst = *(Copy24 *)arg1;
            ((S_80172620_3 *)created)->unk_BB = 0;
            ((S_80172620_3 *)created)->unk_4A = ((S_80172620_2 *)arg3)->unk_2A.u;

            child = ((S_80172620_3 *)created)->unk_0C;
            linked_field = ((Rec_D_80082E80 *)arg2)->unk_28.at00_s32.v;
            ((S_80172620_4 *)child)->unk_1E = 0x1000;
            ((S_80172620_4 *)child)->unk_1C = 0x1000;
            ((S_80172620_4 *)child)->unk_28 = linked_field;
            ((S_80172620_4 *)child)->unk_14 = ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v;
            ((S_80172620_4 *)child)->unk_12 = ((Rec_D_80082E80 *)arg2)->unk_12.at00_u16.v;
            child_field = ((Rec_D_80082E80 *)arg2)->unk_0C.at00_s32.v;
            ((S_80172620_4 *)child)->unk_2C = D_80173CB4;
            ((S_80172620_4 *)child)->unk_0C = child_field;
            func_80047784(child,
                D_80173CB4[((D_80083228 + ((S_80172620_2 *)arg3)->unk_2A.s + 0x100) >> 9) & 7],
                0);
        }
    }

    if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000)) {
        goto done;
    }
    (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_80173CAC;
    func_80047784(arg2,
        D_80173CAC[((D_80083228 + ((S_80172620_2 *)arg3)->unk_2A.s + 0x100) >> 9) & 7],
        0);
    ((S_80172620_0 *)arg0)->unk_9B++;
    goto done;

state_two:
    if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000) {
        void *pending;

        (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_80173CBC;
        func_80047784(arg2,
            D_80173CBC[((D_80083228 + ((S_80172620_2 *)arg3)->unk_2A.s + 0x100) >> 9) & 7],
            0);
        pending = ((S_80172620_0 *)arg0)->unk_A4.s;
        if (pending != 0) {
            ((S_80172620_5 *)pending)->unk_BB = 0xFF;
            ((S_80172620_0 *)arg0)->unk_A4.u = 0;
        }
        ((S_80172620_0 *)arg0)->unk_9B++;
    }

state_three:
    if (((((Rec_D_80082E80 *)arg2)->unk_04.as_s8 == 2) &&
         (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x1000)) ||
        (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000)) {
        func_800A56E0(0x808);
        func_8009C12C(arg3, arg2, ((S_80172620_2 *)arg3)->unk_2A.s, 1);
        ((S_80172620_0 *)arg0)->unk_9B = 0xFF;
    }
    goto done;

state_ff:
    if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000)) {
        goto done;
    }
    func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);
    func_800AD594(arg3, 0x180);
    ((S_80172620_0 *)arg0)->unk_8C = &D_80170E54;
    D_8008346C = 0;
    func_800A4ACC(arg3);
    if (((S_80172620_2 *)arg3)->unk_6D == 0) {
        ((S_80172620_2 *)arg3)->unk_46 &= 0x7FFF;
    } else {
        D_800E3DE8 = (u8 *)arg3 - 0x20;
    }

done:
    return;
}
