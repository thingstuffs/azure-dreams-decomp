#include "common.h"

typedef struct DungeonRecord80285E80 {
    u8 value;
    u8 level;
} DungeonRecord80285E80;

typedef struct DungeonState80285E80 {
    u8 pad00[0x18];
    DungeonRecord80285E80 *records;
} DungeonState80285E80;

typedef struct Packed16_80285E80 {
    s32 w0;
    s32 w4;
    s32 w8;
    s32 wC;
} __attribute__((packed)) Packed16_80285E80;

typedef struct DungeonGlobals80285E80 {
    u8 pad022c[0x22C];
    s32 state_022c;
    u8 pad0230[4];
    s32 floor_0234;
    u8 pad0238[0x2090 - 0x238];
    s32 state_2090;
} DungeonGlobals80285E80;

typedef struct DungeonPage80285E80 {
    u8 pad0000[0x146C];
    s16 floor_146C;
} DungeonPage80285E80;

#define DUNGEON_GLOBALS ((DungeonGlobals80285E80 *)0x80010000)
extern s8 D_80080A88[12];
extern u8 D_80081468[12];
extern s16 D_8008146C[5];
extern u8 D_80082E6B[9];
extern DungeonState80285E80 D_80083460;
extern u8 *D_80083478[3];
extern u8 D_800DDC9C[4][8];
extern s32 D_800E296C[3];
extern u8 D_800E3648[12];
extern u8 D_800E39C8[12];

extern void func_80018EF0(void) __attribute__((noreturn));
extern void func_80019068(void) __attribute__((noreturn));
extern void func_80019118(void) __attribute__((noreturn));
extern void func_800193A4() __attribute__((noreturn));
extern void func_80019490(void) __attribute__((noreturn));
extern void func_80019494(void) __attribute__((noreturn));
extern void func_800194C4(s16 arg0);
extern void func_80019648(void);
extern s32 func_80019684(s16 arg0, s32 arg1, s32 arg2);
extern void func_80019A74(void);
extern s32 func_80033BC0(s32 arg0);
extern void func_80044698(void);
extern void func_80048088(s16 arg0);
extern void func_80053DA8(s32 arg0);
extern void func_800542BC(void);
extern s32 func_800A6D30(void);
extern s32 func_800A6DA4(s32 arg0, s32 arg1);

s32 func_80018E80(void)
{
    s32 result;
    s32 forced_exit;
    s32 state;
    s32 quotient;
    s32 encounter;
    s16 *floor_base;
    DungeonPage80285E80 *final_page;
    s32 final_floor;

    result = 0;
    forced_exit = 0;
    state = DUNGEON_GLOBALS->state_022c;
    if (state == 1) {
        if (D_8008146C[0] < 2) {
            DUNGEON_GLOBALS->state_2090 = state;
            func_80019648();
            goto after_initial;
        }
        if (DUNGEON_GLOBALS->state_2090 == state) {
            DUNGEON_GLOBALS->state_2090 = 0;
        }
    }

after_initial:
    state = D_80082E6B[0];
    if (state < 0x16) {
        if (state >= 0x12) {
            result = 0;
            goto load_final_page;
        }
    }

    state = DUNGEON_GLOBALS->state_2090;
    if (state == 0) {
        quotient = (s16)(D_8008146C[0] / 5);
        if (D_8008146C[0] >= 0x28) {
            forced_exit = 1;
            D_800E296C[0] |= 0x10000000;
        }

        if (D_8008146C[0] == 0x28) {
            result = 1;
            if (func_80033BC0(0xA2) != 0) {
                quotient = 7;
            } else {
                quotient = -1;
                func_80019A74();
            }
            forced_exit = 1;
            goto process_quotient;
        }

        if (D_8008146C[0] < 2) {
            result = (func_800A6D30() & 3) + 3;
            goto process_quotient;
        }

        if (D_8008146C[0] == 2 && DUNGEON_GLOBALS->state_022c != 1) {
            result = 2;
            D_800E296C[0] |= 0x10000000;
            goto process_quotient;
        }

        if (D_8008146C[0] == 0x1F && func_80033BC0(0x1389) == 0) {
            D_800E39C8[6] = 1;
            D_800E39C8[7] = 1;
            D_800E3648[0] = 0x37;
            D_800E3648[1] = 0x13;
            D_800E3648[3] = 0;
            D_800E3648[2] = 0x63;
            D_800E296C[0] |= 0x10000000;
        }

process_quotient:
        if (quotient >= 0) {
            encounter = func_80019684((s16)(quotient + 1), 1, 1);
            if (encounter == 0) {
                D_80080A88[0] = 0;
            }
            if (D_80080A88[0] == 0) {
                func_80044698();
                D_80080A88[0] = 1;
                func_80053DA8(0x200);
                func_800542BC();
            }
            if (encounter == 0) {
                func_80019684(0, 1, 0);
                goto finish_state_zero;
            }
        } else {
            func_80019684(0, 1, 0);
            func_80019684(0x29, 1, 1);
            func_80053DA8(0x200);
            func_800542BC();
            func_80048088(0x38);
        }

finish_state_zero:
        if (forced_exit == 0) {
            final_page = (DungeonPage80285E80 *)0x80080000;
            ASM_KEEP_NV(final_page);   /* MATCH pin: retail immediate-load split depends on it */
            func_800194C4(final_page->floor_146C);
            final_page = (DungeonPage80285E80 *)0x80080000;
            goto final;
        }
    } else {
        forced_exit = 1;
        if (state == 1) {
            result = 9;
            D_800E296C[0] |= 0x10000000;
            func_80019684(1, 1, 1);
            func_80053DA8(0x200);
            func_800542BC();
            func_80019684(0, 1, 0);
            final_page = (DungeonPage80285E80 *)0x80080000;
            goto final;

        } else if (state == 2) {
            quotient = func_800A6D30() & 7;
            encounter = func_80019684(quotient + 1, 1, 1);
            if (encounter == 0) {
                func_80044698();
                func_80053DA8(0x200);
                func_800542BC();
                func_80019684(0, 1, 0);
            }

            floor_base = (s16 *)D_80081468;
            if (floor_base[2] == 1) {
            {
                s32 value;
                s32 level;
                register s32 i ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
                u8 *left;
                u8 *right;
                u8 *base;
                DungeonState80285E80 *dungeon;

                value = func_800A6DA4(3, 0x2D) & 0xFFFF;
                level = floor_base[2] + (func_800A6D30() & 1);
                if (level >= 100) {
                    level = 99;
                }
                i = 0;
                dungeon = &D_80083460;
                base = D_800DDC9C[0];
                ASM_KEEP_NV(base);   /* MATCH pin: retail delay-slot fill depends on it */
                left = base;
                right = left + 1;
                do {
                    dungeon->records[i].value = value;
                    dungeon->records[i].level = level;
                    i++;
                    *right = value;
                    *left = value;
                    left += 2;
                    right += 2;
                } while (i < 4);
            }

            {
                s32 value;
                s32 level;
                register s32 i ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
                u8 *left;
                u8 *right;
                u8 *base;
                DungeonState80285E80 *dungeon;

                value = func_800A6DA4(3, 0x2D) & 0xFFFF;
                level = D_8008146C[0] + (func_800A6D30() & 1);
                if (level >= 100) {
                    level = 99;
                }
                i = 0;
                dungeon = &D_80083460;
                base = D_800DDC9C[1];
                ASM_KEEP_NV(base);   /* MATCH pin: retail delay-slot fill depends on it */
                left = base;
                right = left + 1;
                do {
                    dungeon->records[i + 4].value = value;
                    dungeon->records[i + 4].level = level;
                    i++;
                    *right = value;
                    *left = value;
                    left += 2;
                    right += 2;
                } while (i < 4);
            }
            goto third_pair;
            }

            *(Packed16_80285E80 *)D_80083478[0] =
                *(Packed16_80285E80 *)(D_80083478[0] + 0x10);
            *(Packed16_80285E80 *)D_800DDC9C[0] =
                *(Packed16_80285E80 *)D_800DDC9C[2];

third_pair:
            {
            s32 value;
            s32 level;
            s32 randbit;
            register s32 i ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
            u8 *left;
            u8 *right;
            s32 scratch;
            DungeonState80285E80 *dungeon;

            value = func_800A6DA4(3, 0x2D) & 0xFFFF;
            randbit = func_800A6D30() & 1;
            i = 0;
            scratch = 0x80080000;
            ASM_KEEP_NV(scratch);   /* MATCH pin: load-bearing for the whole function shape */
            dungeon = (DungeonState80285E80 *)(scratch + 0x3460);
            scratch = (s32)D_800DDC9C[2];
            ASM_KEEP_NV(scratch);   /* MATCH pin: load-bearing for the whole function shape */
            left = (u8 *)scratch;
            right = left + 1;
            scratch = D_8008146C[0];
            level = scratch + randbit;
            ASM_KEEP_NV(level);   /* MATCH pin: retail register colouring depends on it */
            do {
                dungeon->records[i + 8].value = value;
                dungeon->records[i + 8].level = level;
                i++;
                *right = value;
                *left = value;
                left += 2;
                right += 2;
            } while (i < 4);
        }

            {
            s32 value;
            s32 level;
            s32 randbit;
            register s32 i ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
            u8 *left;
            u8 *right;
            s32 scratch;
            DungeonState80285E80 *dungeon;

            value = func_800A6DA4(3, 0x2D) & 0xFFFF;
            randbit = func_800A6D30() & 1;
            i = 0;
            scratch = 0x80080000;
            ASM_KEEP_NV(scratch);   /* MATCH pin: load-bearing for the whole function shape */
            dungeon = (DungeonState80285E80 *)(scratch + 0x3460);
            scratch = (s32)D_800DDC9C[3];
            ASM_KEEP_NV(scratch);   /* MATCH pin: load-bearing for the whole function shape */
            left = (u8 *)scratch;
            right = left + 1;
            scratch = D_8008146C[0];
            level = scratch + randbit;
            ASM_KEEP_NV(level);   /* MATCH pin: retail register colouring depends on it */
            do {
                dungeon->records[i + 12].value = value;
                dungeon->records[i + 12].level = level;
                i++;
                *right = value;
                *left = value;
                left += 2;
                right += 2;
            } while (i < 4);
            }
        }
    }

load_final_page:
    final_page = (DungeonPage80285E80 *)0x80080000;
final:
    final_floor = final_page->floor_146C;
    DUNGEON_GLOBALS->floor_0234 = final_floor;
    return result;
}
