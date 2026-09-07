#include "common.h"

typedef struct {
    unsigned char pad8c[0x8c];
    void *unk8c;
    unsigned char pad90[6];
    s16 unk96;
    unsigned char pad98[3];
    u8 unk9b;
} DungeonState;

typedef struct {
    unsigned char pad0[0xC];
    s32 unkC;
    s32 unk10;
    s32 unk14;
} Arg1;

typedef struct {
    unsigned char pad0[0x14];
    u16 flags;
    unsigned char pad16[0x16];
    void *unk2c;
} Arg2;

typedef struct {
    unsigned char pad0[0x2A];
    s16 unk2a;
    unsigned char pad2c[0x1A];
    u16 flags46;
    unsigned char pad48[0x25];
    s8 unk6d;
} Arg3;

typedef struct {
    unsigned char pad0[0x28];
    u8 unk28;
    unsigned char pad29[0x83];
    u8 *unkac;
} DungeonEntry;

typedef struct {
    unsigned char pad0[10];
    u16 count;
    u32 zero;
} D83460;

typedef struct {
    DungeonEntry *entries;
    unsigned char pad4[8];
} DungeonEntryTable;

extern DungeonEntryTable D_800E3D7C;
extern u8 D_8016B778[];
extern D83460 D_80083460;
extern u32 D_8008346C[];
extern volatile u16 D_80013714;
extern s16 D_80083228[];
extern u8 D_801746B4[];
extern u8 D_800F93AA[];

extern void func_800353F4(void *);
extern void func_80047784(Arg2 *, u8, s32);
extern void func_8009C12C(Arg3 *, Arg2 *, s16, s32);
extern void func_800A4ACC(Arg3 *);
extern void func_800A56E0(s32);
extern void func_8016A908(void *);
extern void func_8016AD00(void);
extern void func_8016D11C(void) __attribute__((noreturn));
extern void func_8016D1A8(void) __attribute__((noreturn));

void func_8016CF30(DungeonState *state, Arg1 *arg1, Arg2 *arg2, Arg3 *arg3) {
    s32 stage;

    stage = state->unk9b;
    if (stage == 1) {
        goto phase1;
    }
    if (stage < 2) {
        if (stage == 0) {
            goto phase0;
        }
        func_8016D1A8();
    }
    ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot fill depends on it */
    if (stage == 2) {
        goto phase2;
    }
    if (stage == 3) {
        goto phase3;
    }
    func_8016D1A8();

phase0:
    arg1->unk14 = 0;
    arg1->unk10 = 0;
    arg1->unkC = 0;
    state->unk96 = 0;
    state->unk9b = state->unk9b + 1;
    if (!(arg2->flags & 0x8000)) {
        goto done;
    }

phase1:
    state->unk96 = 0;
    state->unk9b = state->unk9b + 1;
    arg2->unk2c = D_801746B4;
    func_80047784(arg2, D_801746B4[(((s32)D_80083228[0] + arg3->unk2a + 0x100) >> 9) & 7], 0);

phase2:
    state->unk96 = state->unk96 + 1;
    if ((s16)state->unk96 == 10 || (arg2->flags & 0x8000)) {
        func_8009C12C(arg3, arg2, arg3->unk2a, 1);
        state->unk96 = 0;
        state->unk9b = state->unk9b + 1;
    }
    if ((s16)state->unk96 == 8) {
        func_800A56E0(0x804);
        func_8016D1A8();
    }
    goto done;

phase3:
    if (arg2->flags & 0xE000) {
        if (D_800E3D7C.entries->unk28 < 2) {
            s32 i;
            s32 mask;
            void *effect;

            func_8016AD00();
            effect = D_800F93AA;
            ASM_USE_NV(effect);   /* MATCH pin: retail schedule: same instructions, different order without it */
            i = 0;
            state->unk8c = D_8016B778;
            D_80083460.zero = 0;
            D_80083460.count = D_80083460.count + 1;
            ((volatile Arg3 *)arg3)->flags46 = ((volatile Arg3 *)arg3)->flags46 & 0x7FFF;
            *(u16 *)&D_80013714 = D_80013714 | 8;
            mask = 0x80000000;
            func_800353F4(effect);
            arg3->unk6d = 0;
            state->unk9b = 0;
            for (;;) {
                DungeonEntry *entry;
                register u32 entryAddress ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

                entryAddress = (u32)(i * 4) + (u32)D_800E3D7C.entries;
                entry = (DungeonEntry *)entryAddress;
                if (entry->unkac != 0) {
                    u32 *p;

                    func_8016A908(entry->unkac);
                    entryAddress = (u32)(i * 4) + (u32)D_800E3D7C.entries;
                    entry = (DungeonEntry *)entryAddress;
                    p = (u32 *)(entry->unkac - 0x20);
                    p[4] = p[4] | mask;
                }
                i++;
                if (i >= 2) {
                    goto done;
                }
            }
        } else {
            state->unk8c = D_8016B778;
            D_8008346C[0] = 0;
            func_800A4ACC(arg3);
            arg3->flags46 = arg3->flags46 & 0x7FFF;
        }
    }

done:
    return;
}
