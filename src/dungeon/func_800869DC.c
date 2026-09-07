#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"



typedef struct S_8008C13C_2 {
    u8 pad_00[0x8C];
    union { s32 s; void * u; } unk_8C;   /* accessed as both */
    u8 pad_90[0x8];
    u16 unk_98;
    s8 unk_9A;
    s8 unk_9B;
} S_8008C13C_2;   /* arg0 in func_8008C13C */

typedef struct S_8008C13C_3 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0xBC];
    s16 unk_C8;
} S_8008C13C_3;   /* global_base in func_8008C13C */


typedef struct D_80083460_s {
    u8 pad0[2];
    u16 flags;
    s16 value;
    u8 pad6[6];
} D_80083460_s;

typedef struct D_80013714_s {
    u16 flags;
    u8 pad2[8];
} D_80013714_s;

extern D_80013714_s D_80013714;
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern u8 D_80083160[];
extern s16 D_80083228;
extern D_80083460_s D_80083460;
extern u8 D_8008EAC8[];
extern u8 D_800DCFD8[8];
extern u8 D_800DD0B8[8];

extern void func_80048A44(void *, s32, s32, s32);
extern void func_80094ED4(void *, s32, void *, void *);
extern void func_80099F04(s32);
extern void func_80099F70(s32);
extern void func_8009A21C(s32, s32, s32);
extern void func_8009A3D0(s32, s32, s32);
extern s16 func_8009ABA0(s16, s32, void *, s16, s32);
extern void func_8009F644(void *, s32, s32, s32);
extern s32 func_800A5C70(void);
extern void func_800A67F4(void);


/* Synthetic batch key: func_800869DC; true rowbase link symbol: func_8008C13C. */
void func_8008C13C(void *arg0, s32 arg1, void *arg2, void *arg3) {
    u8 *global_base;
    D_80083460_s *state;
    s16 action;
    u8 index;
    u8 value;
    u8 *table;

    global_base = D_80083160;
    action = func_8009ABA0(((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16, arg1, arg2,
                           ((Rec_D_800E3D7C *)arg3)->unk_88.as_s16, 0x20);

    if (action > 0) {
        func_8009A3D0(((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25, 0x300);

        index = ((u16)((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 >> 8) & 0xE;
        table = D_8006CCD8;
        value = ((Rec_D_80082E80 *)arg2)->unk_24;
        value += table[index];
        ((Rec_D_80082E80 *)arg2)->unk_24 = value;
        ((Rec_D_80082E80 *)arg2)->unk_25 += D_8006CCE8[index];

        func_8009A21C(((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25, 0x300);

        D_80083460.flags |= 8;
        ((S_8008C13C_2 *)arg0)->unk_8C.s = 0;

        if (action != 4) {
            if (D_80013714.flags & 2) {
                D_80083460.flags |= 0x80;
            } else if ((((S_8008C13C_3 *)global_base)->unk_08 & 0x20) && func_800A5C70()) {
                D_80083460.flags |= 0x80;
            }
        }

        state = &D_80083460;
        if ((state->flags & 0x80) || (action == 1)) {
            if (((Rec_D_80082E80 *)arg2)->unk_2C.as_pv != D_800DCFD8) {
                (*(void * *)((u8 *)arg2 + 0x2C)) = D_800DCFD8;
                index = ((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7;
                func_80048A44(arg2, D_800DCFD8[index], 0, 1);
            }
            func_80099F70(((Rec_D_800E3D7C *)arg3)->unk_5C);
            func_80099F04(((Rec_D_800E3D7C *)arg3)->unk_5C);
            state->value = 8;
            ((S_8008C13C_2 *)arg0)->unk_9A = 0x1D;
        } else {
            ((S_8008C13C_2 *)arg0)->unk_98 |= 0xC;
            ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v |= 0x4000;
            func_80094ED4(arg0, arg1, arg2, arg3);
            if (action == 2) {
                ((S_8008C13C_2 *)arg0)->unk_9B = 8;
            }
            state->value = 8;
            ((S_8008C13C_2 *)arg0)->unk_9A = 0x1E;
            ((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 |= 0x40000000;
            func_8009F644(arg3, 8, 0, 0);
            return;
        }

        func_8009F644(arg3, 8, 0, 0);
    } else {
        ((Rec_D_80082E80 *)arg2)->unk_2C.as_pv = D_800DD0B8;
        index = ((((S_8008C13C_3 *)global_base)->unk_C8 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7;
        func_80048A44(arg2, D_800DD0B8[index], 0, 1);
        ((S_8008C13C_2 *)arg0)->unk_8C.u = D_8008EAC8;
        return;
    }

    func_800A67F4();
    func_80094ED4(arg0, arg1, arg2, arg3);
    ((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 |= 0x40000000;
    D_80083460.flags |= 0x812;
}
