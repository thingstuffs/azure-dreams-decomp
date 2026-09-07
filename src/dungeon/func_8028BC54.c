#include "common.h"

typedef struct {
    u8 type;
    u8 state;
    u8 amount;
    u8 flag;
} DungeonEntry;

typedef struct {
    u8 x;
    u8 y;
    u8 pad2[2];
    s16 height;
    u8 pad6;
    u8 flag7;
    s32 object;
} DungeonCell;

extern s32 func_800A4E2C(u8 *, u8 *);
extern s32 func_800A6D30(void);
extern u16 func_800A6DA4(s32, s32);
extern s32 func_800A71F4(void);
extern s32 func_8009A21C(s32, s32, s32);
extern s32 func_800A7A38(void *);
extern s16 func_800BCA68(s32, s32);

extern s32 D_80012090[];
extern s16 D_8008146C;
extern u8 D_80010000[];
extern u8 D_800E3548[];
extern u8 D_800E36C8[];

void func_8001EC54(void)
{
    u8 x;
    u8 y;
    register s32 budget;
    s32 index;
    register s32 decrement ASM_REG("$18");   /* MATCH pin: retail register colouring depends on it */
    s32 amount;
    s32 flag;
    s32 type;
    s32 cell_index;
    s32 scan_x;
    s32 scan_y;
    s32 level;
    s32 scaled;
    register u8 *mode_page ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    s32 entry_state;
    volatile DungeonEntry *entry;
    volatile DungeonCell *cell;
    DungeonEntry *entry_scan;
    DungeonCell *cell_scan;
    DungeonEntry *entry_base;
    u8 *cell_page;
    DungeonCell *cell_base;

    mode_page = D_80010000;
    if (*(s32 *)(mode_page + 0x2090) == 2) {
        level = D_8008146C;
        scaled = level * 25;
        budget = scaled << 3;
    } else {
        budget = 75;
        if (D_8008146C >= 12) {
            budget = 700;
            if (D_8008146C < 22) {
                budget = 200;
            }
        }
    }

    if (func_800A6D30() & 1) {
        budget += func_800A6DA4(0, (budget / 2) & 0xFFFF);
    } else {
        budget -= func_800A6DA4(0, (budget / 2) & 0xFFFF);
    }

    if (budget >= 0) {
        entry_base = (DungeonEntry *)D_800E3548;
        cell_page = (u8 *)0x800E0000;
loop:
        cell_index = (s16)func_800A71F4();
        if (cell_index < 0) {
            goto done;
        }

        if (budget >= 301) {
            decrement = func_800A6DA4(160, 240);
            flag = 1;
            type = 3;
            amount = (decrement / 10 + (decrement >> 31)) & 0x3FFFFFFF;
        } else if (budget >= 151) {
            decrement = func_800A6DA4(80, 120);
            amount = decrement;
            flag = 0;
            type = 2;
        } else {
            decrement = func_800A6DA4(16, 24);
            amount = decrement;
            flag = 0;
            type = 1;
        }

        do {
        } while ((func_800A4E2C(&x, &y) << 16) < 0);

        index = 0;
        cell_scan = (DungeonCell *)D_800E36C8;
        entry_scan = entry_base;
        scan_x = x;
        scan_y = y;
scan:
        if (entry_scan->state == 0 || cell_scan->x != scan_x || cell_scan->y != scan_y) {
            cell_scan++;
            index++;
            entry_scan++;
            if (index < 64) {
                goto scan;
            }
        }

        entry_state = 14;
        if (index == 64) {
            entry = (volatile DungeonEntry *)((cell_index << 2) + (unsigned long)entry_base);
            cell_base = (DungeonCell *)(cell_page + 0x36C8);
            entry->type = type;
            entry->state = entry_state;
            entry->flag = flag;
            entry->amount = amount;
            cell = (volatile DungeonCell *)((cell_index * 12) +
                                            (unsigned long)cell_base);
            cell->x = x;
            cell->y = y;
            ((DungeonCell *)cell)->height = func_800BCA68((x << 6) | 32, (y << 6) | 32);
            cell->flag7 = 0;
            func_8009A21C(x, y, 0x800);
            cell->object = func_800A7A38((void *)entry);
        }

        budget -= decrement;
        if (budget >= 0) {
            goto loop;
        }
    }
done:
    return;
}
