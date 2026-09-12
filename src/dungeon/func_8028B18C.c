#include "common.h"

typedef struct {
    u8 kind;
    u8 active;
    u8 pad2[2];
} DungeonState;

typedef struct {
    u8 x;
    u8 y;
    u8 pad2[2];
    s16 field4;
    u8 pad6;
    u8 field7;
    s32 field8;
} DungeonRecord;

typedef struct {
    u16 flags;
    u8 pad2[18];
} DungeonItem;

typedef struct {
    u8 pad0[12];
    DungeonItem *entries;
    u8 pad10[4];
} DungeonGroup;

extern s32 func_8001E110(s32, u8, u8);
extern s32 func_8001E660(u8 *, u8 *, s32, s32);
extern void func_8001E824(DungeonState *);
extern void func_8001EC54(void);
extern void func_8009A21C(u8, u8, s32);
extern s32 func_800A4E2C(u8 *, u8 *);
extern s16 func_800A6928(s32, s32);
extern s32 func_800A6D30(void);
extern s32 func_800A71F4(void);
extern s32 func_800A7A38(DungeonState *);
extern s16 func_800BCA68(s32, s32);

extern u8 D_80010000[];
extern s8 D_8001F6F0[];
extern s32 D_80012090[];
extern u8 D_800DDC9C[];
extern DungeonGroup D_80073414[];
extern s16 D_80081468[3];
extern u8 D_800E3548[];
extern u8 D_800E36C8[];
extern s32 D_800E3D6C[];

/* Populates dungeon items with special item rolls or restores their occupied tiles on reload. */
void func_8001E18C(void)
{
    u8 tile_x;
    u8 tile_y;
    u8 item_category;
    u8 item_subtype;
    register s32 count ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 crystal_pending;
    s16 category18_pending;
    s32 slot_limit;
    s32 spawn_index;
    s32 special_flag;
    s32 spawn_check;
    register u8 *page ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    DungeonGroup *item_category_table;
    DungeonRecord *item_record;
    DungeonState *item_state;
    DungeonRecord *saved_record;
    DungeonRecord *spawn_records;
    u8 *setup_globals;
    if (D_800E3D6C[0] & 2) {
        count = 0;
        saved_record = (DungeonRecord *)D_800E36C8;
        item_state = (DungeonState *)D_800E3548;
        do {
            if (item_state->kind != 0) {
                func_8009A21C(saved_record->x, saved_record->y, 0x800);
            }
            saved_record++;
            count++;
            item_state++;
        } while (count < 0x40);
        goto function_end;
    }

    setup_globals = (u8 *)0x80010000;
    *(u16 *)(setup_globals + 0x3626) = *(u16 *)(setup_globals + 0x3624);
    *(u16 *)(setup_globals + 0x209E) = *(u16 *)(setup_globals + 0x209C);
    D_8001F6F0[0] = 0;
    *(u16 *)(setup_globals + 0x3626) += (func_800A6D30() & 3) + 0x33;
    *(u16 *)(setup_globals + 0x209E) += (func_800A6D30() & 3) + 0x33;

    if (D_80081468[3] == 1) {
        s32 limit_roll;

        crystal_pending = 0;
        limit_roll = func_800A6D30() & 7;
        slot_limit = limit_roll + 8;
    } else {
        s32 limit_roll;
        s32 base_limit;

        crystal_pending = 0;
        limit_roll = func_800A6D30() & 3;
        base_limit = (s16)D_80081468[3] / 2;
        slot_limit = base_limit + limit_roll;
    }

    if ((func_800A6D30() & 3) == 0) {
        crystal_pending = *(s16 *)0x8001209E >= 0x101;
    }
    category18_pending = 0;
    if ((func_800A6D30() & 3) == 0) {
        category18_pending = *(s16 *)0x80013626 >= 0x101;
    }

    count = 0;
    if (*(s32 *)0x80012090 == 0) {
        spawn_check = func_800A6928(6, 3);
        ASM_UNDEF(count);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        count = 0;
        if ((s16)spawn_check < 2) {
            if ((func_800A6D30() & 3) == 0) {
                spawn_index = (s16)func_800A71F4();
                if (spawn_index >= 0) {
                    do {
                        do {
                        } while ((s16)func_800A4E2C(&tile_x, &tile_y) < 0);
                    } while (func_8001E110(spawn_index, tile_x, tile_y) != 0);

                    {
                        s32 *spawn_table = (s32 *)D_800E3548;
                        spawn_table[spawn_index] = 0x603;
                    }
                    spawn_records = (DungeonRecord *)D_800E36C8;
                    spawn_records[spawn_index].x = tile_x;
                    spawn_records[spawn_index].y = tile_y;
                    func_8009A21C(spawn_records[spawn_index].x,
                                  spawn_records[spawn_index].y, 0x800);
                    count = 0;
                }
            }
        }
    }

    page = (u8 *)0x80010000;
    item_category_table = D_80073414;
    item_state = (DungeonState *)D_800E3548;
    item_record = (DungeonRecord *)D_800E36C8;
main_loop:
    if (item_state->active == 0) {
            if (count >= slot_limit) {
                goto cleanup;
            }

            if ((s16)func_8001E660(&item_category, &item_subtype, 0, 0) == 0) {
                if (item_category == 0) {
                    goto next_entry;
                }

                special_flag = crystal_pending;
                if (special_flag != 0) {
                    register u16 page_value ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

                    item_subtype = ((func_800A6D30() & 0xF) == 0) ? 2 : 1;
                    crystal_pending = 0;
                    page_value = *(u16 *)(page + 0x209E);
                    item_category = 2;
                    page_value &= 0xF;
                    *(u16 *)(page + 0x209E) = page_value;
                    goto commit_state;
                }

                special_flag = category18_pending;
                if (special_flag != 0) {
                    u32 item_flags;

                    item_category = 0x12;
                    item_subtype = D_800DDC9C[func_800A6D30() & 0x1F];
                    item_flags = item_category_table[18].entries[item_subtype].flags;
                    if ((item_flags & 0x10) != 0 &&
                        (item_category_table[19].entries[item_subtype].flags & 0x80) != 0 &&
                        item_subtype >= 2) {
                        item_subtype++;
                    }
                    category18_pending = 0;
                    *(u16 *)(page + 0x3626) &= 0x3F;
                }
            }

commit_state:
            item_state->active = item_category;
            item_state->kind = item_subtype;
            func_8001E824(item_state);

            do {
            } while ((s16)func_800A4E2C(&tile_x, &tile_y) < 0);

            if (func_8001E110(count, tile_x, tile_y) != 0) {
                item_state->active = 0;
                goto next_entry;
            }

            item_record->x = tile_x;
            item_record->y = tile_y;
            goto place_record;
        }

        tile_x = item_record->x;
        tile_y = item_record->y;
        func_8001E824(item_state);

place_record:
        item_record->field4 = func_800BCA68((tile_x << 6) | 0x20,
                                       (tile_y << 6) | 0x20);
        item_record->field7 = 0;
        func_8009A21C(tile_x, tile_y, 0x800);
        item_record->field8 = func_800A7A38(item_state);

next_entry:
    item_state++;
    count++;
    item_record++;
    if (count < 0x40) {
        goto main_loop;
    }

cleanup:
    if (count < 0x40) {
        DungeonState *cleanup_base;
        DungeonState *cleanup_state;

        cleanup_base = (DungeonState *)D_800E3548;
        cleanup_state = cleanup_base + count;
        do {
            cleanup_state->active = 0;
            cleanup_state->kind = 0;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            count++;
            cleanup_state++;
        } while (count < 0x40);
    }
    func_8001EC54();

function_end:
    return;
}
