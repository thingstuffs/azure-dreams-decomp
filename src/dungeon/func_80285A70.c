#include "common.h"

typedef struct {
    s32 seed;
    u16 flags;
    s16 field6;
    s16 field8;
    s16 fieldA;
    u8 padC[4];
    s8 field10;
    s8 field11;
} State13710;

typedef struct {
    u8 pad0000[0x234];
    s32 level;
    u8 pad0238[0x2090 - 0x238];
    s32 mode;
} Page8001;

typedef struct {
    u8 kind;
    u8 arg;
    u8 track;
    u8 table_index;
    u8 special;
} TrackRecord;

typedef struct {
    u8 pad0000[0x296C];
    u32 flags;
} Page800E;

extern void func_80016E6C(void);
extern void func_8001744C(void);
extern void func_80017560(void);
extern void func_800177A8(void);
extern void func_8001784C(void);
extern void func_80017A9C(void);
extern void func_80018464();
extern void func_8004D0C8();
extern void func_80046E38();
extern s32 bzero();
extern s32 rand(void);
extern s32 srand();
extern void func_800A0E44(void);
extern s32 func_800A6D30(void);
extern void func_800A6D98();
extern void func_800B0544();
extern void func_800BC228();
extern void func_800C7D54();
extern s32 func_80018E80(void);
extern s32 func_80019AF8(void);
extern void func_8001E96C(void);
extern void func_8001F32C(void);
extern void file_load_com();

extern u8 D_80083160[];
extern u8 D_80083780[];
extern u16 D_80082E76;
extern s32 D_800E3D6C;
extern s16 D_800E3CD8[8];
extern TrackRecord D_8001F62C[];
extern s32 D_8001F588[];
extern u8 D_8001F584;
extern s16 D_8001F586;
extern s32 D_8001F594[];
extern u8 D_800F0000[];
typedef struct {
    s32 seed;
    u16 level;
    s16 ready;
} SaveHead;
extern SaveHead D_80081468;
typedef struct {
    u8 pad0000[0x234];
    u16 level;
} LevelPage;

/* Sets up the run's save state and RNG (new game or continue), then loads the selected dungeon track and waits for it to finish loading. */
void func_80018A70(void) {
    State13710 *state;
    Page8001 *page1;
    TrackRecord *track;
    s16 *clearp;
    s32 value;
    s32 track_no;
    s32 action;
    s32 i;
    {
        u8 *xor_base;
        u16 entry_flags;

        state = (State13710 *)0x80013710;
        entry_flags = state->flags;
        xor_base = D_80083160;

        if (entry_flags & 2) {
            u32 r;
            u16 fl;

            func_800A6D98(state->seed);
            r = func_800A6D30();
            state->field8 = 0;
            state->fieldA = 0;
            state->field6 = 0;
            state->seed += r & 0xFFFF;
            D_80081468.seed = state->seed;
            fl = state->flags;
            D_80081468.level = ((LevelPage *)0x80010000)->level;
            fl &= 0xFFFC;
            state->flags = fl;
            func_8004D0C8(D_80083780);
            bzero((void *)0x80013720, 0x2000);
        } else if (entry_flags & 1) {
            state->field8 = 0;
            state->fieldA = 0;
            D_80081468.seed = state->seed;
            D_80081468.level = ((LevelPage *)0x80010000)->level;
            func_8004D0C8(D_80083780);
        } else {
            u32 hi;

            state->flags = 0;
            value = rand();
            hi = rand();
            state->field8 = 0;
            state->field6 = 0;
            state->field11 = 0;
            state->field10 = 0;
            state->seed = D_80081468.seed = (value | (hi << 16)) ^ ((State13710 *)xor_base)->flags;
            func_8004D0C8(D_80083780);
            bzero((void *)0x80013720, 0x2000);
        }
    }

    srand(D_80081468.seed);
    func_800A6D98(D_80081468.seed);
    func_800A0E44();
    D_80082E76 = 0;
    D_800E3D6C = 0;
    func_8001F32C();
    func_8001E96C();

    i = 3;
    clearp = D_800E3CD8;
    clearp += 12;
    loop_0: {
        *clearp = 0;
        i--;
        clearp -= 4;
    } if (i >= 0) goto loop_0;

    page1 = (Page8001 *)0x80010000;
    if ((u32)page1->level >= 100U) {
        page1->level = 99;
    }

    track_no = func_80018E80();
    if (track_no != 0) {
        TrackRecord *tracks;

        track_no--;
        func_80017560();
        tracks = D_8001F62C;
        track = &tracks[track_no];
        func_800B0544(track->track);
        file_load_com(D_8001F588[track->table_index]);
        func_80046E38(track->kind, D_800F0000);
        func_8001744C();
        func_800177A8();
        if (track->arg != 0) {
            func_80018464(track->arg);
        }
        if (track->special != 0) {
            func_800C7D54(((volatile TrackRecord *)track)->special - 1);
        }
        ((Page800E *)0x800E0000)->flags &= ~0x20000000;
        goto final_cleanup;
    }

    if (page1->mode != 2) {
        func_800B0544(D_8001F584 % 24 + 3);
        action = D_8001F594[D_8001F584 % 24];
    } else {
        s32 random_remainder;

        random_remainder = func_800A6D30() & 0xFFFF;
        random_remainder %= 24;
        func_800B0544((s16)(random_remainder + 3));
        action = D_8001F594[random_remainder];
    }

    file_load_com(action);
    ((Page800E *)0x800E0000)->flags |= 0x20000000;
    func_80046E38(0x29, D_800F0000, (Page800E *)0x800E0000);
    func_800BC228(2);

    do {
        func_8001744C();
        func_800177A8();
    } while ((func_80019AF8() << 16) != 0 || D_80081468.ready == 0);

final_cleanup:
    func_80016E6C();
    if (D_8001F586 == 0) {
        func_8001784C();
    }
    func_80017A9C();
}

