#include "common.h"

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

#define FIELD(ptr, type, off) (*(type *)((u8 *)(ptr) + (off)))

/* Synthetic batch key: func_800869DC; true rowbase link symbol: func_8008C13C. */
void func_8008C13C(void *arg0, s32 arg1, void *arg2, void *arg3) {
    u8 *global_base;
    D_80083460_s *state;
    s16 action;
    u8 index;
    u8 value;
    u8 *table;

    global_base = D_80083160;
    action = func_8009ABA0(FIELD(arg3, s16, 0x2A), arg1, arg2,
                           FIELD(arg3, s16, 0x88), 0x20);

    if (action > 0) {
        func_8009A3D0(FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25), 0x300);

        index = ((u16)FIELD(arg3, s16, 0x2A) >> 8) & 0xE;
        table = D_8006CCD8;
        value = FIELD(arg2, u8, 0x24);
        value += table[index];
        FIELD(arg2, u8, 0x24) = value;
        FIELD(arg2, u8, 0x25) += D_8006CCE8[index];

        func_8009A21C(FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25), 0x300);

        D_80083460.flags |= 8;
        FIELD(arg0, s32, 0x8C) = 0;

        if (action != 4) {
            if (D_80013714.flags & 2) {
                D_80083460.flags |= 0x80;
            } else if ((FIELD(global_base, s32, 8) & 0x20) && func_800A5C70()) {
                D_80083460.flags |= 0x80;
            }
        }

        state = &D_80083460;
        if ((state->flags & 0x80) || (action == 1)) {
            if (FIELD(arg2, void *, 0x2C) != D_800DCFD8) {
                FIELD(arg2, void *, 0x2C) = D_800DCFD8;
                index = ((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7;
                func_80048A44(arg2, D_800DCFD8[index], 0, 1);
            }
            func_80099F70(FIELD(arg3, s32, 0x5C));
            func_80099F04(FIELD(arg3, s32, 0x5C));
            state->value = 8;
            FIELD(arg0, s8, 0x9A) = 0x1D;
        } else {
            FIELD(arg0, u16, 0x98) |= 0xC;
            FIELD(arg2, u16, 0x14) |= 0x4000;
            func_80094ED4(arg0, arg1, arg2, arg3);
            if (action == 2) {
                FIELD(arg0, s8, 0x9B) = 8;
            }
            state->value = 8;
            FIELD(arg0, s8, 0x9A) = 0x1E;
            FIELD(arg3, s32, 0x1C) |= 0x40000000;
            func_8009F644(arg3, 8, 0, 0);
            return;
        }

        func_8009F644(arg3, 8, 0, 0);
    } else {
        FIELD(arg2, void *, 0x2C) = D_800DD0B8;
        index = ((FIELD(global_base, s16, 0xC8) + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7;
        func_80048A44(arg2, D_800DD0B8[index], 0, 1);
        FIELD(arg0, void *, 0x8C) = D_8008EAC8;
        return;
    }

    func_800A67F4();
    func_80094ED4(arg0, arg1, arg2, arg3);
    FIELD(arg3, s32, 0x1C) |= 0x40000000;
    D_80083460.flags |= 0x812;
}
