#include "common.h"

typedef struct {
    s16 kind;
    s16 x;
    s16 y;
    s16 value;
} SpawnEntry;

typedef struct {
    u16 flags;
    u16 value;
    u16 extra;
} MapCell;

extern u16 func_800A4E2C(u8 *, u8 *);
extern void func_8009A21C(s32, s32, s32);
extern s32 func_800A6D30(void);

extern s32 D_80012090;
extern s16 D_8008146C;
extern u8 D_8008333C[32];
extern u8 D_800E3548[];
extern u8 D_800E3648[];
extern u8 D_800E36C8[];
extern u8 D_800E39C8[];
extern u8 D_800E3CD8[];

void func_8001784C(void) {
    register s32 state ASM_REG("$3");
    u8 x;
    u8 y;
    register u8 *config ASM_REG("$19");
    MapCell *map;
    s32 count;
    s32 i;
    u8 *first_meta;
    SpawnEntry *entries;

    {
        register u8 *pg0 ASM_REG("$3");
        pg0 = (u8 *)0x80010000;
        state = *(s32 *)(pg0 + 0x2090);
    }
    ASM_KEEP_NV(state);
    config = D_8008333C;
    map = *(MapCell **)D_8008333C;

    if ((state == 2) || (D_8008146C != 0x28)) {
        count = 0;
        first_meta = D_800E3548;

retry:
        do {
        } while ((s16)func_800A4E2C(&x, &y) < 0);

        {
            u8 *meta;
            u8 *position;

            i = 0;
            position = D_800E36C8;
            meta = first_meta;

            do {
                if ((meta[1] != 0) && (position[0] == x) &&
                    (position[1] == y)) {
                    goto retry;
                }
                position += 12;
                i++;
                meta += 4;
            } while (i < 0x40);
        }

        {
            register u8 *page1 ASM_REG("$2");
            register u8 *page2 ASM_REG("$2");
            register u8 *meta ASM_REG("$5");
            register u8 *position ASM_REG("$3");

            i = 0;
            page1 = (u8 *)0x800e0000;
            ASM_KEEP(page1);
            position = page1 + 0x39c8;
            ASM_KEEP(position);
            page2 = (u8 *)0x800e0000;
            ASM_KEEP(page2);
            meta = page2 + 0x3648;

            do {
                if ((meta[1] != 0) && (position[6] == x) &&
                    (position[7] == y)) {
                    goto retry;
                }
                position += 24;
                i++;
                meta += 4;
            } while (i < 0x20);
        }

        entries = (SpawnEntry *)D_800E3CD8;
        {
            register SpawnEntry *entry ASM_REG("$7") = &entries[count];
            register s32 store_x ASM_REG("$4");
            register s32 store_y ASM_REG("$5");
            register s32 calc_x ASM_REG("$6");
            register s32 calc_y ASM_REG("$8");
            register s32 shift ASM_REG("$3");
            register s32 shift2 ASM_REG("$3");
            register s32 shift3 ASM_REG("$2");
            register s32 one ASM_REG("$3");
            s32 index;
            MapCell *final_cell;
            s32 call_size;

            store_x = x;
            store_y = y;
            entry->kind = 2;
            entry->x = store_x;
            entry->y = store_y;
            ASM_MEM_BARRIER();

            calc_y = y;
            shift = *(s16 *)(config + 0x14);
            calc_x = x;
            ASM_KEEP(shift);
            index = calc_x + (calc_y << shift);
            map[index].value -= 0x20;

            shift2 = *(s16 *)(config + 0x14);
            ASM_KEEP(shift2);
            index = calc_x + (calc_y << shift2);
            entry->value = map[index].value;

            shift3 = *(s16 *)(config + 0x14);
            ASM_KEEP(shift3);
            one = 1;
            ASM_KEEP(one);
            calc_y <<= shift3;
            calc_x += calc_y;
            ASM_KEEP(calc_x);
            final_cell = (MapCell *)(calc_x * 6 + (s32)map);
            ASM_KEEP(final_cell);
            call_size = 0x20;
            ASM_KEEP(call_size);
            final_cell->flags = one;
            func_8009A21C(store_x, store_y, call_size);
        }

        if ((func_800A6D30() & 0x3F) == 0) {
            count++;
            if (count < 4) {
                goto retry;
            }
        }

        count++;
        while (count < 4) {
            entries[count].kind = 0;
            count++;
        }
    }
}
