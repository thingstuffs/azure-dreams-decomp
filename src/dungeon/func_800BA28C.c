#include "common.h"
#include "records/Rec_D_800E3D7C.h"


typedef struct {
    u8 pad[0xA];
    u16 field_A;
} D_80083460_t;

extern void *D_800814A8;
extern u8 D_80082E80[];
extern D_80083460_t D_80083460;
extern s32 D_800835E8[];
extern u8 D_80083780[];
extern u16 D_800DDE84[];
extern u8 D_800E131C[];
extern u8 *D_800E3D7C;

extern s32 func_80042900(void *, s32);
extern void func_8008D344(void *, void *, void *, void *);
extern void func_80098864(s32, s32);
extern void func_80098B38(s32);
extern void func_800997FC(void *);
extern void func_800A1D4C(void *, s32);
extern void func_800A5F38(void *, s32);
extern void func_800A6480(void *, s32, s16);
extern s32 func_800AD6FC(void *, s32, s32);
extern void func_800B4C7C(s32, void *, s32, s32);
extern s32 func_800BFBDC(void);
extern void func_800C4D78(s32, s32);



typedef struct S_800BF9EC_1 {
    u8 pad_00[0x5C];
    void * unk_5C;
} S_800BF9EC_1;   /* head in func_800BF9EC */

typedef struct S_800BF9EC_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800BF9EC_2_pre;   /* the 0x14 bytes before node in func_800BF9EC, addressed as node[-1] */

typedef struct S_800BF9EC_2 {
    u8 pad_00[0x11];
    u8 unk_11;
    u8 pad_12[0x2];
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
    u8 pad_20[0x3C];
    void * unk_5C;
} S_800BF9EC_2;   /* node in func_800BF9EC */

typedef struct S_800BF9EC_3 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_800BF9EC_3;   /* ((S_800BF9EC_2_pre *)node)[-1].unk_00 in func_800BF9EC */

s32 func_800BF9EC(Rec_D_800E3D7C *arg0, s32 arg1, s16 arg2, s32 arg3)
{
    S_800BF9EC_1 *head;
    void *node;

    if (arg2 == 13) {
        func_80098864(arg1, arg3);
        return func_800BFBDC();
    }

    if (arg0 == D_800E3D7C) {
        arg0->unk_110 = arg1;
        func_8008D344(arg0, D_80083780, D_80082E80, arg0);
        func_800BFBDC();
        return 0;
    }

    if ((u32)arg0 <= 0x9FFFFFFF) {
        func_800A6480(arg0, arg1, arg2);
        if (func_800AD6FC(arg0, D_800DDE84[arg0->unk_10.at03_u8.v] & 3, arg1) == 0) {
            func_800A5F38(arg0, arg1);
            func_800BFBDC();
            return 1;
        }
    } else {
        func_800C4D78(0x2020C0, 1);
        func_800997FC(D_800E131C);

        head = D_800814A8;
        node = (u8 *)head->unk_5C + 0x20;
        if (node != head) {
            do {
                if (((((S_800BF9EC_2 *)node)->unk_1C & 0x2400) != 0x2000 ||
                     (func_80042900(node, 12) << 16) != 0) &&
                    arg0->unk_10.at01_u8.v < 99) {
                    ((S_800BF9EC_2 *)node)->unk_18 = D_800835E8[((S_800BF9EC_2 *)node)->unk_11];
                    func_800A1D4C(node, 0);
                    if ((((S_800BF9EC_3 *)(((S_800BF9EC_2_pre *)node)[-1].unk_00))->unk_14 & 0x8000) == 0) {
                        s32 kind = 0x8003;
                        if (((S_800BF9EC_2 *)node)->unk_14 & 0x2000) {
                            kind = 0x8002;
                        }
                        func_800B4C7C(kind, node, -2, 1);
                    }
                }
                node = (u8 *)((S_800BF9EC_2 *)node)->unk_5C + 0x20;
            } while (node != head);
        }
    }

    func_80098B38(arg1);
    D_80083460.field_A--;
    return 1;
}
