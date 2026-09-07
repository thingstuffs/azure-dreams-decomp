#include "common.h"

typedef struct S_80022C8C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_80022C8C_0;   /* (void *)state in func_80022C8C */

typedef struct S_80022C8C_1 {
    u8 pad_00[0x4];
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    void * unk_08;
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_80022C8C_1;   /* record in func_80022C8C */

typedef struct S_80022C8C_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80022C8C_2;   /* ((S_80022C8C_0 *)((void *)state))->unk_08 in func_80022C8C */


#define NULL ((void *)0)

extern volatile u16 D_800135C2;
extern s32 D_80020054;
extern s32 D_80022F60;
extern s32 D_8002390C;
extern s32 D_80023920;
extern s32 D_800240B0;
extern s32 D_80026F0C;
extern s32 D_80045340;
extern s32 D_800F9B40;

extern void *func_8003FC64(s32);
extern void func_80022E64(void *, s32, void *, void *);
extern void func_8004491C(void *, void *);
extern void func_8008F104(void *, void *, void *);

/* Creates linked town objects at fixed positions and initializes their display data. */
s32 func_80022C8C(void)
{
    s32 position[6];
    s32 object_or_slot;
    void *parent_link;
    S_80022C8C_1 *render_record;
    void *shared_data;
    void *object_data;
    s32 left_x;
    s32 right_x;
    s32 top_y;
    s32 count;
    u8 *data_page;
    volatile u16 *count_page;
    s32 bottom_y;
    void *spawn_position;
    s32 spawn_kind;
    void *spawn_table;

    parent_link = NULL;
    data_page = (u8 *)0x80020000;
    ASM_KEEP_NV(data_page);   /* MATCH pin: keeps a statement from moving across a call/branch */
    count_page = (volatile u16 *)0x80010000;
    count = (s16)*(count_page + (0x35C2 / 2));
    shared_data = data_page + 0x54;
    if (count < 20) {
        *(count_page + (0x35C2 / 2)) = 20;
    }

    object_or_slot = (s32)func_8003FC64(2);
    if (object_or_slot != 0) {
        parent_link = (u8 *)object_or_slot + 0x20;
        ((S_80022C8C_0 *)((void *)object_or_slot))->unk_10 = &D_80022F60;
    }

    position[0] = 0x03800000;
    position[1] = 0x02600000;
    position[2] = (s32)0xFFA00000;
    func_80022E64(position, 0x34, &D_8002390C, parent_link);

    object_or_slot = 3;
    left_x = 0x02700000;
    right_x = 0x04900000;
    top_y = 0x02E00000;
    position[2] = (s32)0xFFE00000;
    do {
        if ((object_or_slot >> 1) != 0) {
            position[0] = left_x;
        } else {
            position[0] = right_x;
        }

        if (object_or_slot & 1) {
            position[1] = top_y;
        } else {
            bottom_y = 0x03E00000;
            ASM_KEEP(bottom_y);   /* MATCH pin: retail immediate-load split depends on it */
            position[1] = bottom_y;
        }

        spawn_position = position;
        ASM_KEEP(spawn_position);   /* MATCH pin: retail schedule: same instructions, different order without it */
        spawn_kind = 0x35;
        ASM_KEEP(spawn_kind);   /* MATCH pin: retail schedule: same instructions, different order without it */
        spawn_table = (void *)0x80020000;
        ASM_KEEP(spawn_table);   /* MATCH pin: load-bearing for the whole function shape */
        spawn_table = (u8 *)spawn_table + 0x3920;
        func_80022E64(spawn_position, spawn_kind, spawn_table, parent_link);
        object_or_slot--;
    } while (object_or_slot >= 0);

    object_or_slot = (s32)func_8003FC64(0x136);
    if (object_or_slot != 0) {
        ((S_80022C8C_0 *)((void *)object_or_slot))->unk_10 = &D_800240B0;
        func_8004491C((void *)object_or_slot, &D_80045340);

        render_record = ((S_80022C8C_0 *)((void *)object_or_slot))->unk_0C;
        render_record->unk_1E = 0x1000;
        render_record->unk_1C = 0x1000;
        render_record->unk_08 = &D_800F9B40;
        render_record->unk_04 = 0;
        render_record->unk_05 = 0;
        render_record->unk_0C = 0x00808080;
        object_data = (u8 *)object_or_slot + 0x20;
        (*(void * volatile *)((u8 *)object_data + 0x4C)) = shared_data;

        func_8008F104((u8 *)object_or_slot + 0x24,
                      ((S_80022C8C_0 *)((void *)object_or_slot))->unk_08,
                      &D_80026F0C);

        ((S_80022C8C_2 *)(((S_80022C8C_0 *)((void *)object_or_slot))->unk_08))->unk_00 = 0x03800000;
        ((S_80022C8C_2 *)(((S_80022C8C_0 *)((void *)object_or_slot))->unk_08))->unk_04 = 0x03C00000;
        ((S_80022C8C_2 *)(((S_80022C8C_0 *)((void *)object_or_slot))->unk_08))->unk_08 = 0;
        ((S_80022C8C_0 *)((void *)object_or_slot))->unk_20 = parent_link;
    }

    return 0;
}
