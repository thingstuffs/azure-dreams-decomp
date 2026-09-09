#include "common.h"

typedef struct {
    u8 unk0[0xB];
    u8 floor;
} State;

extern void func_80016EC0(void);
extern void func_80017018(void);
extern void bzero(void *, s32);
extern void func_80017068(void);
extern void func_8004A918(void);
extern s32 func_80048D00(void);
extern s32 rand(void);
extern void func_800A9024(s32);
extern void func_8004AB7C(void);
extern void func_80040AA0(s32);
extern void func_8003F6D4(s32, void *, void *, s32);
extern void Control_CD(s32, void *, s32);
extern void func_8003F320(void);
extern void func_8009FAC4(void);
extern void func_800499BC(void);

extern s32 D_8001022C;
extern s32 D_80010234;
extern s32 D_80012090;
extern s16 D_8001209C;
extern s16 D_80013624;
extern s32 D_80013628;
extern u16 D_80013714;
extern s32 D_80080A80;
extern s8 D_80080A88;
extern s16 D_8008146C;
extern State D_80082E60;
extern s32 D_80082EB8;
extern u16 D_8008347E;
extern s8 D_800DCF4E;
extern u8 D_800E3CD0;
extern s32 D_800E3D1C;
extern u8 D_800E3E48[];

/* Initialize dungeon state, random seeds, and floor-specific data. */
void func_800163F4(void) {
    s32 floor_data;
    s32 floor_index;
    u32 saved_init_value;
    u8 *dungeon_state;
    u8 *globals_base;

    func_80016EC0();
    func_80017018();
    bzero(D_800E3E48, 0xAF0);
    D_80082EB8 = 0;
    D_8008347E = 0;
    D_80080A88 = 0;
    if ((D_80013714 & 3) == 0) {
        D_8008146C = 1;
        D_8001022C++;
        func_80017068();
        func_8004A918();
        goto check_init;
    }
    saved_init_value = 0x80010000;

    saved_init_value = *(u16 *)(saved_init_value + 0x234);

    D_8008146C = (u16)saved_init_value;

check_init:
    globals_base = (u8 *)0x80010000;
    if (D_800DCF4E == 0) {
        D_80080A80 = func_80048D00();
        D_800DCF4E = 1;
    }
    if ((*(u16 *)(globals_base + 0x3714) & 3) == 0) {
        *(s32 *)(globals_base + 0x3628) = rand();
        *(s16 *)(globals_base + 0x3624) = rand() & 0xFF;
        *(s16 *)(globals_base + 0x209C) = rand() & 0xFF;
        func_800A9024(*(s32 *)(globals_base + 0x2090));
    }
    func_8004AB7C();
    dungeon_state = (u8 *)&D_80082E60;
    if (dungeon_state[0xB] >= 0x12) {
        floor_index = dungeon_state[0xB] - 0x12;
        func_80040AA0(0x11);
        func_8003F6D4(0xC, (void *)0x80010000, &floor_data,
                     (floor_index * 0xC) + 0x399D);
        Control_CD(6, &floor_data, 0);
        func_8003F320();
        D_800E3D1C = 0x384;
        *(u16 *)(globals_base + 0x3714) |= 5;
        goto finish;
    }
    func_80040AA0(0x11);
    D_800E3D1C = 0;

finish:
    func_8009FAC4();
    func_800499BC();
    D_800E3CD0 = 0;
}
