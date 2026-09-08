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

void func_8001E18C(void)
{
    u8 x;
    u8 y;
    u8 kind;
    u8 subtype;
    register s32 count ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 special_x;
    s32 special_y;
    s32 limit;
    s32 index;
    s32 special_flag;
    s32 setup_result;
    register u8 *page ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    DungeonGroup *groups;
    DungeonRecord *record;
    DungeonState *state;
    DungeonRecord *reload_record;
    DungeonRecord *spawn_record;
    u8 *setup_page;
    if (D_800E3D6C[0] & 2) {
        count = 0;
        reload_record = (DungeonRecord *)D_800E36C8;
        state = (DungeonState *)D_800E3548;
        do {
            if (state->kind != 0) {
                func_8009A21C(reload_record->x, reload_record->y, 0x800);
            }
            reload_record++;
            count++;
            state++;
        } while (count < 0x40);
        goto function_end;
    }

    setup_page = (u8 *)0x80010000;
    *(u16 *)(setup_page + 0x3626) = *(u16 *)(setup_page + 0x3624);
    *(u16 *)(setup_page + 0x209E) = *(u16 *)(setup_page + 0x209C);
    D_8001F6F0[0] = 0;
    *(u16 *)(setup_page + 0x3626) += (func_800A6D30() & 3) + 0x33;
    *(u16 *)(setup_page + 0x209E) += (func_800A6D30() & 3) + 0x33;

    if (D_80081468[3] == 1) {
        s32 limit_random;

        special_x = 0;
        limit_random = func_800A6D30() & 7;
        limit = limit_random + 8;
    } else {
        s32 limit_random;
        s32 half_limit;

        special_x = 0;
        limit_random = func_800A6D30() & 3;
        half_limit = (s16)D_80081468[3] / 2;
        limit = half_limit + limit_random;
    }

    if ((func_800A6D30() & 3) == 0) {
        special_x = *(s16 *)0x8001209E >= 0x101;
    }
    special_y = 0;
    if ((func_800A6D30() & 3) == 0) {
        special_y = *(s16 *)0x80013626 >= 0x101;
    }

    count = 0;
    if (*(s32 *)0x80012090 == 0) {
        setup_result = func_800A6928(6, 3);
        ASM_UNDEF(count);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        count = 0;
        if ((s16)setup_result < 2) {
            if ((func_800A6D30() & 3) == 0) {
                index = (s16)func_800A71F4();
                if (index >= 0) {
                    do {
                        do {
                        } while ((s16)func_800A4E2C(&x, &y) < 0);
                    } while (func_8001E110(index, x, y) != 0);

                    {
                        s32 *spawn_table = (s32 *)D_800E3548;
                        spawn_table[index] = 0x603;
                    }
                    spawn_record = (DungeonRecord *)D_800E36C8;
                    spawn_record[index].x = x;
                    spawn_record[index].y = y;
                    func_8009A21C(spawn_record[index].x,
                                  spawn_record[index].y, 0x800);
                    count = 0;
                }
            }
        }
    }

    page = (u8 *)0x80010000;
    groups = D_80073414;
    state = (DungeonState *)D_800E3548;
    record = (DungeonRecord *)D_800E36C8;
main_loop:
    if (state->active == 0) {
            if (count >= limit) {
                goto cleanup;
            }

            if ((s16)func_8001E660(&kind, &subtype, 0, 0) == 0) {
                if (kind == 0) {
                    goto next_entry;
                }

                special_flag = special_x;
                if (special_flag != 0) {
                    register u16 page_value ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

                    subtype = ((func_800A6D30() & 0xF) == 0) ? 2 : 1;
                    special_x = 0;
                    page_value = *(u16 *)(page + 0x209E);
                    kind = 2;
                    page_value &= 0xF;
                    *(u16 *)(page + 0x209E) = page_value;
                    goto commit_state;
                }

                special_flag = special_y;
                ASM_KEEP_NV(special_flag);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                if (special_flag != 0) {
                    u32 item;

                    kind = 0x12;
                    subtype = D_800DDC9C[func_800A6D30() & 0x1F];
                    item = groups[18].entries[subtype].flags;
                    if ((item & 0x10) != 0 &&
                        (groups[19].entries[subtype].flags & 0x80) != 0 &&
                        subtype >= 2) {
                        subtype++;
                    }
                    special_y = 0;
                    *(u16 *)(page + 0x3626) &= 0x3F;
                }
            }

commit_state:
            state->active = kind;
            state->kind = subtype;
            func_8001E824(state);

            do {
            } while ((s16)func_800A4E2C(&x, &y) < 0);

            if (func_8001E110(count, x, y) != 0) {
                state->active = 0;
                goto next_entry;
            }

            record->x = x;
            record->y = y;
            goto place_record;
        }

        x = record->x;
        y = record->y;
        func_8001E824(state);

place_record:
        record->field4 = func_800BCA68((x << 6) | 0x20,
                                       (y << 6) | 0x20);
        record->field7 = 0;
        func_8009A21C(x, y, 0x800);
        record->field8 = func_800A7A38(state);

next_entry:
    state++;
    count++;
    record++;
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
