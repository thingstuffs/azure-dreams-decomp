#include "common.h"
#include "m2c_compat.h"
/* Selector-image function at DUNGEON file [0x1943DD0, 0x1944338), true 0x800255D0
 * (rowbase img_1942998_80024198 delta 0x7E6E1800 continued).  Five-state handler:
 * spawn a directional effect object, follow it, then print the result message and
 * finish.  Reconstruction from r121_remnants continuation 5 (v8); the message
 * builder uses the engine's cursor idiom (message_end / message_start, as in
 * src/dungeon/func_800BB400.c and func_800940E4.c).  Evidence:
 * docs/evidence/r121_rem_opus.md. */
extern void func_8003DB94(void *, void *, short);
extern void * func_8003FD64(s32, void *);
extern s32 func_8004491C(void *, s32);
extern void func_80047784(void *, s16, s16);
extern void * func_800990FC(void);
extern void * func_80099194(void *, void *);
extern void * func_80099290(void *);
extern u8 *func_80099734(void *, u8 *);
extern s16 func_800A48F0(void *, s8, s8);
extern s32 func_800A5720(s8 *);
extern s32 func_800A6D30(void);
typedef struct { s32 w[12]; } Packet48;
typedef struct { s16 x; u16 y; } DirectionPair;
typedef struct { DirectionPair v[8]; } DirectionTable;
extern DirectionTable D_80024004;
extern u8 D_80024024[];
extern u8 D_80024E5C[];
extern u8 D_80025B40[];
extern s16 D_80025B60;
extern u8 D_80045340[];
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern u8 D_800814A0[];
extern u8 D_80083228[];
extern u8 D_8008346C[];
extern u8 D_80083498[];
extern u8 D_800DEC00[];
void dungeonProcessResolvedItemValue(void *arg0, void *arg1, void *arg2) {
    DirectionTable directions;
    M2C_UNK temp_a1;
    s16 temp_a0;
    s32 done_flag;
    u16 direction;
    s32 temp_t0;
    u16 temp_v0_4;
    u16 temp_v1_3;
    void *temp_a0_2;
    void *temp_a1_2;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_s2;
    void *temp_s5;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v1;
    void *temp_v1_2;
    void *var_a2;
    void *var_a3;

    temp_s2 = M2C_FIELD(arg0, void **, 0);
    directions = D_80024004;
    temp_a0 = M2C_FIELD(arg0, s16 *, 0xA);
    temp_v0 = temp_s2 - 0x20;
    temp_s0 = M2C_FIELD(temp_v0, void **, 8);
    temp_s5 = M2C_FIELD(temp_v0, void **, 0xC);
    switch (temp_a0) {
    case 0:
        M2C_FIELD(arg2, s32 *, 0xC) = 0x808080;
        M2C_FIELD(arg2, s16 *, 0x1E) = 0x1000;
        M2C_FIELD(arg2, s16 *, 0x1C) = 0x1000;
        func_8003DB94(arg2, ((u32)D_800DEC00), 0);
        direction = M2C_FIELD(temp_s2, u16 *, 0x2A);
        D_80025B60 = 1;
        M2C_FIELD(arg0, s16 *, 0x7E) = (direction >> 9) & 7;
        M2C_FIELD(arg0, s16 *, 0xA) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0xA) + 1);
        /* fallthrough */
    case 1:
        M2C_FIELD(arg1, u16 *, 2) = (u16) M2C_FIELD(temp_s0, u16 *, 2);
        M2C_FIELD(arg1, u16 *, 6) = (u16) M2C_FIELD(temp_s0, u16 *, 6);
        M2C_FIELD(arg1, u16 *, 0xA) = (u16) M2C_FIELD(temp_s0, u16 *, 0xA);
        if (*M2C_FIELD(arg0, u16 **, 4) & 0x80) {
            M2C_FIELD(arg0, u16 *, 0x84) = 0U;
            M2C_FIELD(arg0, s16 *, 0xA) = (u16) M2C_FIELD(arg0, s16 *, 0xA) + 1;
            return;
        }
    default:
        return;
    case 2:
        temp_v0_2 = func_8003FD64(0x112, ((u32)D_80083498));
        if (temp_v0_2 != NULL) {
            temp_a0_2 = temp_v0_2 + 0x20;
            M2C_FIELD(temp_a0_2, s32 *, 0x98) = (s32) (directions.v[M2C_FIELD(arg0, s16 *, 0x7E)].x << 0x10);
            M2C_FIELD(temp_a0_2, s32 *, 0x9C) = (s32) (directions.v[M2C_FIELD(arg0, s16 *, 0x7E)].y << 0x10);
            M2C_FIELD(temp_a0_2, s16 *, 0x58) = 0;
            M2C_FIELD(temp_a0_2, void **, 0x84) = temp_s2;
            M2C_FIELD(temp_a0_2, s32 *, 0x88) = (s32) M2C_FIELD(temp_s2, s32 *, 0x60);
            M2C_FIELD(temp_a0_2, void **, 0x8C) = arg0;
            M2C_FIELD(temp_a0_2, u8 *, 0x6A) = (u8) M2C_FIELD(arg0, u8 *, 9);
            M2C_FIELD(temp_a0_2, u16 *, 0x6C) = (u16) M2C_FIELD(arg0, s16 *, 0x7E);
            temp_a1_2 = M2C_FIELD(temp_s2, void **, -0x14);
            M2C_FIELD(arg0, s8 *, 0xA0) = (s8) (M2C_FIELD(temp_a1_2, u8 *, 0x24) + M2C_FIELD((M2C_FIELD(arg0, s16 *, 0x7E) * 2), u8 *, ((u32)D_8006CCD8)));
            M2C_FIELD(arg0, s8 *, 0xA1) = (s8) (M2C_FIELD(temp_a1_2, u8 *, 0x25) + M2C_FIELD((M2C_FIELD(arg0, s16 *, 0x7E) * 2), u8 *, ((u32)D_8006CCE8)));
            if (M2C_FIELD(temp_s2, s32 *, 0x60) != 0) {
                M2C_FIELD(temp_a0_2, s16 *, 0x90) = (s16) (s8) M2C_FIELD(temp_s2, u8 *, 0x72);
                M2C_FIELD(temp_a0_2, s16 *, 0x92) = (s16) (s8) M2C_FIELD(temp_s2, u8 *, 0x73);
                M2C_FIELD(temp_a0_2, s16 *, 0x94) = (s16) M2C_FIELD(temp_a1_2, u8 *, 0x24);
                M2C_FIELD(temp_a0_2, s16 *, 0x96) = (s16) M2C_FIELD(temp_a1_2, u8 *, 0x25);
                M2C_FIELD(temp_a0_2, s16 *, 0x60) = 1;
                M2C_FIELD(temp_a0_2, s16 *, 0x5A) = 0;
                func_800A48F0(M2C_FIELD(temp_s2, s32 *, 0x60), 0x1D, (s8) (((u8) M2C_FIELD(arg0, u8 *, 9) >> 2) + 3 + (func_800A6D30() & 3)));
                var_a2 = temp_s5;
            } else {
                M2C_FIELD(temp_a0_2, s16 *, 0x5C) = 0x20;
                M2C_FIELD(temp_a0_2, s16 *, 0x5A) = 0;
                M2C_FIELD(temp_a0_2, s16 *, 0x60) = 0;
                var_a2 = temp_s5;
            }
            temp_t0 = var_a2 + 0x30;
            M2C_FIELD(arg0, s16 *, 0x86) = 0;
            temp_s0_2 = M2C_FIELD(temp_v0_2, void **, 0xC);
            var_a3 = temp_s0_2;
            M2C_FIELD(temp_s0_2, u8 *, 0xE) = 0x80;
            M2C_FIELD(temp_s0_2, u8 *, 0xD) = 0x80;
            M2C_FIELD(temp_s0_2, u8 *, 0xC) = 0x80;
            M2C_FIELD(temp_s0_2, s16 *, 0x1E) = 0x1000;
            M2C_FIELD(temp_s0_2, s16 *, 0x1C) = 0x1000;
            *(Packet48 *)temp_s0_2 = *(Packet48 *)temp_s5;
            M2C_FIELD(temp_s0_2, s16 *, 0x10) = 0x20;
            M2C_FIELD(temp_s0_2, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0_2, u16 *, 0x14) | 0xC);
            M2C_FIELD(temp_v0_2, s32 *, 0x10) = ((u32)D_80024E5C);
            func_8004491C(temp_v0_2, ((u32)D_80045340));
            M2C_FIELD(temp_s0_2, s32 *, 0x2C) = ((u32)D_80025B40);
            func_80047784(temp_s0_2, M2C_FIELD((((s32) (*(s16 *)((u32)D_80083228) + (s16) M2C_FIELD(temp_s2, u16 *, 0x2A) + 0x100) >> 9) & 7), u8 *, ((u32)D_80025B40)), 0);
            temp_v1 = M2C_FIELD(temp_v0_2, void **, 8);
            M2C_FIELD(temp_v1, s32 *, 0) = (s32) M2C_FIELD(arg1, s32 *, 0);
            M2C_FIELD(temp_v1, s32 *, 4) = (s32) M2C_FIELD(arg1, s32 *, 4);
            M2C_FIELD(temp_v1, s32 *, 8) = (s32) M2C_FIELD(arg1, s32 *, 8);
            M2C_FIELD(arg0, void **, 0xA8) = temp_v0_2;
            M2C_FIELD(arg0, void **, 0xAC) = temp_v1;
            M2C_FIELD(arg0, s16 *, 0x88) = 0x63;
        }
        M2C_FIELD(arg0, s16 *, 0xA) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0xA) + 1);
        return;
    case 3:
        if (M2C_FIELD(arg0, s16 *, 0x88) == 0x63) {
            temp_v0_2 = M2C_FIELD(arg0, void **, 0xA8);
            temp_v1_2 = M2C_FIELD(arg0, void **, 0xAC);
            if (M2C_FIELD(temp_v0_2, u16 *, 0x1E) & 0x8000) {
                M2C_FIELD(arg0, s16 *, 0x88) = 0;
            } else {
                M2C_FIELD(arg1, s32 *, 0) = (s32) M2C_FIELD(temp_v1_2, s32 *, 0);
                M2C_FIELD(arg1, s32 *, 4) = (s32) M2C_FIELD(temp_v1_2, s32 *, 4);
                M2C_FIELD(arg1, s32 *, 8) = (s32) M2C_FIELD(temp_v1_2, s32 *, 8);
            }
        }
        if (M2C_FIELD(arg0, s16 *, 0x86) != 0) {
            M2C_FIELD(arg0, u16 *, 0x84) = 0U;
            M2C_FIELD(arg0, s16 *, 0xA) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0xA) + 1);
            if (M2C_FIELD(temp_s2, s32 *, 0x60) != 0) {
                {
                    u8 *message_end;
                    u8 *message_start;

                    message_end = func_800990FC();
                    message_start = message_end;
                    message_end = func_80099734(M2C_FIELD(temp_s2, s32 *, 0x60), message_end);
                    message_end = func_80099194(((u32)D_80024024), message_end);
                    func_80099290(message_end);
                    func_800A5720((s8 *)message_start);
                }
                return;
            }
        }
        break;
    case 4:
        temp_v1_3 = M2C_FIELD(arg0, u16 *, 0x84);
        temp_v0_4 = temp_v1_3 + 1;
        M2C_FIELD(arg0, u16 *, 0x84) = temp_v0_4;
        if ((s16) temp_v0_4 >= 0xB) {
            done_flag = D_80025B60;
            M2C_FIELD(arg0, u16 *, 0x84) = temp_v1_3;
            if (done_flag == 0) {
                *(s32 *)((u32)D_8008346C) = 0;
                M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
                *(s32 *)((u32)D_800814A0) |= 0x8000;
                return;
            }
            D_80025B60 = 0;
        }
        break;
    }
}
