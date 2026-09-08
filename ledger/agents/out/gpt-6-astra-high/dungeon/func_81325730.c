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

/* Advances the dungeon transition animation and resets entry resources when it completes. */
void func_8016CF30(DungeonState *state, Arg1 *motion, Arg2 *animation, Arg3 *actor) {
    s32 stage;

    stage = state->unk9b;
    if (stage == 1) {
        goto phase1;
    }
    if (stage < 2) {
        if (stage == 0) {
            goto phase0;
        }
        return;
    }
    if (stage == 2) {
        goto phase2;
    }
    if (stage == 3) {
        goto phase3;
    }
    return;

phase0:
    motion->unk14 = 0;
    motion->unk10 = 0;
    motion->unkC = 0;
    state->unk96 = 0;
    state->unk9b = state->unk9b + 1;
    if (!(animation->flags & 0x8000)) {
        goto done;
    }

phase1:
    state->unk96 = 0;
    state->unk9b = state->unk9b + 1;
    animation->unk2c = D_801746B4;
    func_80047784(animation, D_801746B4[(((s32)D_80083228[0] + actor->unk2a + 0x100) >> 9) & 7], 0);

phase2:
    state->unk96 = state->unk96 + 1;
    if ((s16)state->unk96 == 10 || (animation->flags & 0x8000)) {
        func_8009C12C(actor, animation, actor->unk2a, 1);
        state->unk96 = 0;
        state->unk9b = state->unk9b + 1;
    }
    if ((s16)state->unk96 == 8) {
        func_800A56E0(0x804);
        return;
    }
    goto done;

phase3:
    if (animation->flags & 0xE000) {
        if (D_800E3D7C.entries->unk28 < 2) {
            s32 entry_index;
            s32 resource_flag;
            void *effect;

            func_8016AD00();
            effect = D_800F93AA;
            ASM_USE_NV(effect);
            entry_index = 0;
            state->unk8c = D_8016B778;
            D_80083460.zero = 0;
            D_80083460.count = D_80083460.count + 1;
            ((volatile Arg3 *)actor)->flags46 = ((volatile Arg3 *)actor)->flags46 & 0x7FFF;
            *(u16 *)&D_80013714 = D_80013714 | 8;
            resource_flag = 0x80000000;
            func_800353F4(effect);
            actor->unk6d = 0;
            state->unk9b = 0;
            for (;;) {
                DungeonEntry *entry;
                register u32 entry_addr ASM_REG("$2");

                entry_addr = (u32)(entry_index * 4) + (u32)D_800E3D7C.entries;
                entry = (DungeonEntry *)entry_addr;
                if (entry->unkac != 0) {
                    u32 *resource_header;

                    func_8016A908(entry->unkac);
                    entry_addr = (u32)(entry_index * 4) + (u32)D_800E3D7C.entries;
                    entry = (DungeonEntry *)entry_addr;
                    resource_header = (u32 *)(entry->unkac - 0x20);
                    resource_header[4] = resource_header[4] | resource_flag;
                }
                entry_index++;
                if (entry_index >= 2) {
                    goto done;
                }
            }
        } else {
            state->unk8c = D_8016B778;
            D_8008346C[0] = 0;
            func_800A4ACC(actor);
            actor->flags46 = actor->flags46 & 0x7FFF;
        }
    }

done:
    return;
}
