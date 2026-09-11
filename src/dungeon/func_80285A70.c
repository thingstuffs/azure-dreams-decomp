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
    u8 pad0000[0x1468];
    s32 seed;
    u16 level;
    s16 ready;
    u8 pad1470[0x2E76 - 0x1470];
    u16 field2E76;
} Page8008;

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
extern u8 D_80080004[];
extern Page8001 D_80010000[];
extern Page800E D_800E0000[];
extern u16 D_80082E76;
extern s32 D_800E3D6C;
extern s16 D_800E3CD8[8];
extern TrackRecord D_8001F62C[];
extern s32 D_8001F588[];
extern u8 D_8001F584;
extern s16 D_8001F586;
extern s32 D_8001F594[];
extern u8 D_800F0000[];

void func_80018A70(void) {
    u8 *page8_common;
    State13710 *state;
    u8 *common_arg;
    Page8001 *page1;
    TrackRecord *track;
    s16 *clearp;
    s32 random_lo;
    s32 value;
    s32 track_no;
    s32 remainder;
    s32 action;
    s32 i;
    {
        u8 *xor_base;
        u8 *xor_page;
        u16 entry_flags;

        state = (State13710 *)0x80013710;
        xor_page = (u8 *)0x80080000;
        ASM_KEEP(xor_page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        entry_flags = state->flags;
        xor_base = xor_page + 0x3160;

        if (entry_flags & 2) {
            u32 v0role;
            s32 sum;
            register u32 a1role ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

            func_800A6D98(state->seed);
            v0role = func_800A6D30();
            common_arg = D_80083780;
            ASM_KEEP_NV(common_arg);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            sum = state->seed;
            v0role &= 0xFFFF;
            state->field8 = 0;
            state->fieldA = 0;
            state->field6 = 0;
            sum += v0role;
            v0role = 0x80080000;
            ASM_KEEP_NV(v0role);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            state->seed = sum;
            *(s32 *)(v0role + 0x1468) = sum;
            v0role += 0x1468;
            ASM_KEEP_NV(v0role);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            sum = state->flags;
            a1role = 0x80010000;
            a1role = *(u16 *)(a1role + 0x234);
            sum &= 0xFFFC;
            *(u16 *)(v0role + 4) = a1role;
            state->flags = sum;
            goto call_common_setup;
        }

        if (entry_flags & 1) {
            u32 v0role;
            u32 v1role;

            common_arg = D_80083780;
            ASM_KEEP_NV(common_arg);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            v1role = state->seed;
            do {
                v0role = 0x80080000;
            } while (0);
            ASM_KEEP_NV(v0role);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            state->field8 = 0;
            state->fieldA = 0;
            *(s32 *)(v0role + 0x1468) = v1role;
            v1role = 0x80010000;
            v1role = *(volatile u16 *)(v1role + 0x234);
            do {
                v0role += 0x1468;
            } while (0);
            ASM_KEEP_NV(v0role);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            *(u16 *)(v0role + 4) = v1role;
            func_8004D0C8(common_arg);
            goto after_optional_setup;
        }

        state->flags = 0;
        {
            u32 v0role;
            u32 v1role;
            register u8 *a1role ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

        value = rand();
        v0role = rand();
        common_arg = D_80083780;
        ASM_KEEP_NV(common_arg);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        a1role = (u8 *)0x80080000;
        ASM_KEEP_NV(a1role);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        v0role <<= 16;
        state->field8 = 0;
        state->field6 = 0;
        state->field11 = 0;
        state->field10 = 0;
        v1role = *(u16 *)(xor_base + 4);
        value |= v0role;
        value ^= v1role;
        *(s32 *)(a1role + 0x1468) = value;
        state->seed = value;
        }
    }

call_common_setup:
    func_8004D0C8(common_arg);
    bzero((void *)0x80013720, 0x2000);

after_optional_setup:
    page8_common = (u8 *)0x80080000;
    ASM_KEEP_NV(page8_common);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    srand(*(s32 *)(page8_common + 0x1468));
    func_800A6D98(*(s32 *)(page8_common + 0x1468));
    func_800A0E44();
    {
        u8 *v0base;
        v0base = (u8 *)0x80080000;
        ASM_KEEP_NV(v0base);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        *(u16 *)(v0base + 0x2E76) = 0;
        v0base = (u8 *)0x800E0000;
        ASM_KEEP_NV(v0base);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        *(s32 *)(v0base + 0x3D6C) = 0;
        func_8001F32C();
    }
    func_8001E96C();

    i = 3;
    clearp = D_800E3CD8;
    clearp += 12;
    do {
        *clearp = 0;
        i--;
        clearp -= 4;
    } while (i >= 0);

    state = (State13710 *)0x80010000;
    page1 = (Page8001 *)state;
    if ((u32)page1->level >= 100U) {
        page1->level = 99;
    }

    track_no = func_80018E80();
    if (track_no != 0) {
        u32 v0index;
        u32 v1base;

        track_no--;
        func_80017560();
        v1base = (u32)D_8001F62C;
        do {
            v0index = (u32)track_no << 2;
        } while (0);
        v0index += track_no;
        track = (TrackRecord *)(v0index + v1base);
        func_800B0544(track->track);
        file_load_com(D_8001F588[track->table_index]);
        func_80046E38(track->kind, D_800F0000);
        func_8001744C();
        func_800177A8();
        if (track->arg != 0) {
            func_80018464(track->arg);
        }
        {
            u32 mask;
            Page800E *pageE;
            u32 flags;

            mask = 0xDFFF0000;
            if (track->special != 0) {
                func_800C7D54(((volatile TrackRecord *)track)->special - 1);
                mask = 0xDFFF0000;
            }
            pageE = (Page800E *)0x800E0000;
            flags = pageE->flags;
            mask |= 0xFFFF;
            flags &= mask;
            pageE->flags = flags;
        }
        goto final_cleanup;
    }

    if (page1->mode != 2) {
        {
            u32 first_remainder;
            first_remainder = D_8001F584 % 24;
            func_800B0544(first_remainder + 3);
        }
        {
            u32 second_remainder;
            s32 *table;
            second_remainder = D_8001F584 % 24;
            table = D_8001F594;
            action = table[second_remainder];
        }
        goto do_action;
    } else {
        register s32 random_remainder ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        s32 *table;
        s32 random_result;
        s32 division_magic;

        random_result = func_800A6D30();
        division_magic = 0x2AAAAAAB;
        ASM_USE(division_magic);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        random_remainder = random_result & 0xFFFF;
        random_remainder -= (random_remainder / 24) * 24;
        ASM_KEEP_NV(random_remainder);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        func_800B0544((s16)(random_remainder + 3));
        table = D_8001F594;
        action = table[random_remainder];
    }

do_action:
    file_load_com(action);
    {
        s32 call_arg0;
        u8 *call_arg1;
        Page800E *pageE;

        call_arg0 = 0x29;
        call_arg1 = (u8 *)D_800E0000 + 0x10000;
        pageE = (Page800E *)0x800E0000;
        pageE->flags |= 0x20000000;
        func_80046E38(call_arg0, call_arg1, pageE);
    }
    func_800BC228(2);

    {
        u8 *page8_temp;
        page8_temp = (u8 *)0x80080000;
        ASM_KEEP_NV(page8_temp);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        page8_common = page8_temp + 0x1468;
    }
poll_ready:
        func_8001744C();
        func_800177A8();
        if ((func_80019AF8() << 16) != 0) {
            goto poll_ready;
        }
        if (*(s16 *)(page8_common + 6) == 0) {
            goto poll_ready;
        }

final_cleanup:
    func_80016E6C();
    {
        u32 cleanup_flag;
        cleanup_flag = 0x80020000;
        cleanup_flag = *(s16 *)(cleanup_flag - 0xA7A);
        if (cleanup_flag == 0) {
            func_8001784C();
        }
    }
    func_80017A9C();
}

