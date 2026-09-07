#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"


typedef struct Copy48 {
    u32 words[12];
} Copy48;

typedef struct ItemInfo {
    u8 pad00[0x12];
    u8 type;
    u8 pad13;
} ItemInfo;

extern s32 func_8003F270(void);
extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, u8, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, u16 *);
extern void func_801708B8(void *, void *, void *);

extern s32 D_80045340;
extern ItemInfo D_8006DE24[];
extern void *D_800814A8;
extern u8 D_80083160[];
extern s16 D_80083228;
extern u8 D_80083460[];
extern s32 D_8008346C;
extern u8 D_80083498[];
extern u8 D_800D58D8[];
extern s8 D_800DCECC[];
extern u8 D_800E23E0[];
extern u8 D_800E2410[];
extern void *D_80170868[];
extern u8 D_80171A80[];


typedef struct S_80173A60_0 {
    u8 pad_00[0x2A];
    union { s16 s; u16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x60];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x14];
    u8 unk_B0;
} S_80173A60_0;   /* arg0 in func_80173A60 */

typedef struct S_80173A60_1_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} S_80173A60_1_pre;   /* the 0x14 bytes before active in func_80173A60, addressed as active[-1] */



typedef struct S_80173A60_4 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x68];
    u16 unk_94;
    u16 unk_96;
    u8 pad_98[0x14];
    void * unk_AC;
} S_80173A60_4;   /* state in func_80173A60 */

typedef struct S_80173A60_5 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 * unk_0C;
    void * unk_10;
} S_80173A60_5;   /* object in func_80173A60 */

typedef struct S_80173A60_6 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0xC];
    void * unk_2C;
} S_80173A60_6;   /* copy in func_80173A60 */

typedef struct S_80173A60_7 {
    u8 pad_00[0xC8];
    s16 unk_C8;
} S_80173A60_7;   /* direction in func_80173A60 */

typedef struct S_80173A60_8 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80173A60_8;   /* target in func_80173A60 */

typedef struct S_80173A60_9 {
    u8 pad_00[0xA];
    u16 unk_0A;
    volatile s32 unk_0C;
} S_80173A60_9;   /* global in func_80173A60 */

void func_80173A60(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const kind_keep[] = {
        &&L_kind1, &&L_kind2, &&L_kind3, &&L_kind4,
        &&L_kind5, &&L_kind6, &&L_kind7
    };
    register s32 special ASM_REG("$17");   /* MATCH pin: keeps a constant in a register as retail does */
    u8 *selector;

    special = 0;
    switch (((S_80173A60_0 *)arg0)->unk_9B) {
    case 0:
        if ((*(u32 *)((u8 *)arg3 + 0x1C)) & 0x2000) {
            u32 dispatch;

            dispatch = ((*(u16 *)((u8 *)arg3 + 0x46)) & 0x3FFF) - 1;
            if (dispatch >= 7) {
                goto L_kind4;
            }
            (void)kind_keep;
            goto *D_80170868[dispatch];

L_kind7:
            special = 1;
            goto L_kind3;
L_kind6:
            special = 1;
            goto L_kind2;
L_kind5:
            special = 1;
            goto L_kind1;
        }

        switch ((*(u16 *)((u8 *)arg3 + 0x46)) & 0x3FFF) {
        case 3:
L_kind3:
            selector = (u8 *)arg3 + 0xE;
            break;
        case 2:
L_kind2:
            selector = (u8 *)arg3 + 0xB;
            break;
        case 1:
L_kind1:
            selector = (u8 *)arg3 + 8;
            break;
        default:
L_kind4:
            selector = 0;
            break;
        }

        if (*selector != 0) {
            s32 special_test;
            void *active;

            ((S_80173A60_0 *)arg0)->unk_98 &= 0xFF7F;
            ASM_KEEP(special);   /* MATCH pin: retail delay-slot fill depends on it */
            special_test = special;
            ASM_KEEP(special_test);   /* MATCH pin: retail delay-slot fill depends on it */
            if (special_test != 0) {
                active = D_800814A8;
                (*(void * *)((u8 *)arg3 + 0x60)) = active;
                goto L_copy_linked;
            } else if (D_8006DE24[*selector].type == 2) {
                active = (*(void * *)((u8 *)arg3 + 0x60));
                if (active != 0) {
                    register u8 *linked ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */

L_copy_linked:
                    linked = ((S_80173A60_1_pre *)active)[-1].unk_00;
                    (*(u8 *)((u8 *)arg3 + 0x72)) = linked[0x24];
                    (*(u8 *)((u8 *)arg3 + 0x73)) = linked[0x25];
                }
            } else {
                s32 x;
                s32 y;

                active = func_800A05A4(arg3,
                                       ((Rec_D_80082E80 *)arg2)->unk_24,
                                       ((Rec_D_80082E80 *)arg2)->unk_25,
                                       (*(s16 *)((u8 *)arg3 + 0x2A)), 0x10);
                (*(void * volatile *)((u8 *)arg3 + 0x60)) = active;
                ASM_USE(active);   /* MATCH pin: keeps a statement from moving across a call/branch */
                x = (*(s8 *)((u8 *)arg3 + 0x72));
                y = (*(s8 *)((u8 *)arg3 + 0x73));
                if (x < 0) {
                    x = -x;
                }
                if (y < 0) {
                    y = -y;
                }
                (*(u8 *)((u8 *)arg3 + 0x72)) = x;
                (*(u8 *)((u8 *)arg3 + 0x73)) = y;
            }

            if (func_800A94A0(arg3, selector, special,
                              (u16 *)((u8 *)arg0 + 0x98)) == 0) {
                return;
            }
            ((S_80173A60_0 *)arg0)->unk_96.u = 0;
            ((S_80173A60_0 *)arg0)->unk_9B++;
            return;
        }

        ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
        func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);
        D_8008346C = 0;
        (*(u16 *)((u8 *)D_800814A8 + 0xA6))--;
        func_800A4ACC(arg3);
        (*(u8 *)((u8 *)arg3 + 0x6D))--;
        ((S_80173A60_0 *)arg0)->unk_8C = D_80171A80;
        (*(u8 *)((u8 *)arg3 + 0x73)) = 0;
        (*(u8 *)((u8 *)arg3 + 0x72)) = 0;
        (*(u16 *)((u8 *)arg3 + 0x46)) &= 0x7FFF;
        return;

    case 1:
        if (func_8003F270() != 0) {
            ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v |= 0x0800;
            return;
        }
        ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v &= 0xF7FF;
        ((S_80173A60_0 *)arg0)->unk_9B++;
        func_800A56E0(0x703);
        /* fall through */

    case 2:
        {
            u16 timer;

            timer = ((S_80173A60_0 *)arg0)->unk_96.u + 1;
            ((S_80173A60_0 *)arg0)->unk_96.u = timer;
            if ((s16)timer == 3) {
                u8 *object;

                object = func_8003FD64(0x112, D_80083498);
                if (object != 0) {
                    u8 *state;
                    u8 *copy;
                    u8 *direction;
                    u8 *target;
                    u8 *animation;
                    u8 *animation_entry;
                    s8 *offsets;
                    register s32 index ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

                    state = object + 0x20;
                    ((S_80173A60_4 *)state)->unk_96 = 0x10;
                    ((S_80173A60_5 *)object)->unk_10 = D_800D58D8;
                    ((S_80173A60_4 *)state)->unk_AC = arg1;
                    ((S_80173A60_4 *)state)->unk_94 = (*(u16 *)((u8 *)arg3 + 0x2A));
                    copy = ((S_80173A60_5 *)object)->unk_0C;
                    *(Copy48 *)copy = *(Copy48 *)arg2;
                    ((S_80173A60_6 *)copy)->unk_1E = 0x1000;
                    ((S_80173A60_6 *)copy)->unk_1C = 0x1000;
                    ((S_80173A60_6 *)copy)->unk_0E = 0x80;
                    ((S_80173A60_6 *)copy)->unk_0D = 0x80;
                    ((S_80173A60_6 *)copy)->unk_0C = 0x80;
                    func_8004491C(object, &D_80045340);

                    animation = D_800E2410;
                    ((S_80173A60_6 *)copy)->unk_2C = animation;
                    direction = D_80083160;
                    index = ((((S_80173A60_7 *)direction)->unk_C8 +
                              (*(s16 *)((u8 *)arg3 + 0x2A)) + 0x100) >> 9) & 7;
                    animation_entry = (u8 *)((u32)index + (u32)animation);
                    func_80047784(copy, *animation_entry, 0);
                    ((S_80173A60_6 *)copy)->unk_14 &= 0xFFF3;

                    index = ((((S_80173A60_7 *)direction)->unk_C8 +
                              ((S_80173A60_0 *)arg0)->unk_2A.s + 0x100) >> 9) & 7;
                    offsets = D_800DCECC;
                    ((S_80173A60_6 *)copy)->unk_06 = -(offsets[index] * 4);
                    ((S_80173A60_4 *)state)->unk_94 =
                        (((S_80173A60_0 *)arg0)->unk_2A.u >> 9) & 7;
                    ((S_80173A60_4 *)state)->unk_2A = ((S_80173A60_0 *)arg0)->unk_2A.u;

                    target = ((S_80173A60_5 *)object)->unk_08;
                    ((S_80173A60_8 *)target)->unk_02 = ((Rec_D_800E3D7C *)arg1)->unk_00.at02_u16.v;
                    ((S_80173A60_8 *)target)->unk_06 = ((Rec_D_800E3D7C *)arg1)->unk_04.at02_u16.v;
                    ((S_80173A60_8 *)target)->unk_0A = ((Rec_D_800E3D7C *)arg1)->unk_08.at02_u16.v;
                }
            }

            if (((S_80173A60_0 *)arg0)->unk_96.s == 0x10) {
                u8 *animation;
                s32 index;

                animation = D_800E23E0;
                (*(void * *)((u8 *)arg2 + 0x2C)) = animation;
                index = ((D_80083228 + (*(s16 *)((u8 *)arg3 + 0x2A)) + 0x100) >> 9) & 7;
                func_80047784(arg2, animation[index], 3);
                if (((S_80173A60_0 *)arg0)->unk_B0 == 0) {
                    func_801708B8(arg0, arg1, arg2);
                }
            }

            if (((S_80173A60_0 *)arg0)->unk_96.s == 0x13 ||
                (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000)) {
                ((S_80173A60_0 *)arg0)->unk_98 |= 0x80;
                func_800A56E0(0x81B);
            }

            if (((S_80173A60_0 *)arg0)->unk_96.s < 0x19 &&
                !(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000)) {
                return;
            }
            ((S_80173A60_0 *)arg0)->unk_9B++;
            return;
        }

    case 3:
        {
            u8 *global;

            global = D_80083460;
            if (((S_80173A60_9 *)global)->unk_0C != 0) {
                return;
            }
            ((S_80173A60_0 *)arg0)->unk_96.u = 0;
            if (((S_80173A60_9 *)global)->unk_0C != 0) {
                return;
            }
            ((S_80173A60_9 *)global)->unk_0A--;
            ((S_80173A60_0 *)arg0)->unk_8C = D_80171A80;
            func_800A4ACC(arg3);
            (*(u8 *)((u8 *)arg3 + 0x73)) = 0;
            (*(u8 *)((u8 *)arg3 + 0x72)) = 0;
            (*(u8 *)((u8 *)arg3 + 0x6D))--;
            (*(u16 *)((u8 *)arg3 + 0x46)) &= 0x7FFF;
            func_800A56E0(0xB4);
            return;
        }
    }
}

/* MECHANISM: The four long-lived arguments and scoped temporaries reproduce the 0x40 frame
   and s4/s7/s6/s2 plus s1/s5/s3/s0 save contract; the shared linked-copy label restores both CFG edges.
   ASM_USE orders the returned-pointer store before signed-byte loads, while a v0-pinned index and
   named integer address sum reproduce the two table-lookup register roles and final addu polarity. */
