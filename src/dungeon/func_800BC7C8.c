#include "common.h"
#include "records/Rec_D_80082E80.h"


#ifndef NULL
#define NULL 0
#endif


typedef struct S_800C1F28_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800C1F28_1;   /* temp_v1 in func_800C1F28 */


typedef struct {
    u8 pad[0x24];
    u8 coord0;
    u8 coord1;
} Coord;

typedef struct {
    u8 pad0[0x1C];
    u32 flags;
    u8 pad1[0x68];
    u16 value;
} ArgObj;

typedef struct {
    u8 pad[8];
    u16 value;
} Entry;

extern s16 D_800DCED4[];
extern s32 D_80083460[3];
extern u8 D_80082E80[];
extern u8 D_800C1EC4;

extern void *func_8003FC64(s32);
extern s32 func_800429E4(void *);
extern void func_8009A3D0(u8, u8, s32);
extern s32 func_8009B88C(s32, u8, u8, s16 *, s16 *);
extern u16 func_800BCB04(s32, s32, s16);
extern void func_800C542C(void *, s16, s16, s32);
extern void func_8009A21C(u8, u8, s32);

/* Creates a relocation task and updates the object's tile and height. */
void *func_800C1F28(void *object, s16 action_arg) {
    s16 tile_x;
    s16 tile_y;
    s32 tile_mask;
    u16 target_height;
    u16 source_height;
    u8 source_y;
    S_800C1F28_1 *task_object;
    u8 *position;
    u8 *task_data;
    void *task;
    u8 *task_counters;
    u8 *search_origin;
    s32 object_index;
    u8 old_x;
    u8 old_y;

    task = func_8003FC64(2);
    if (task != NULL) {
        object_index = func_800429E4(object);
        func_800C542C(object, D_800DCED4[object_index], action_arg, 3);
        tile_mask = 0x3000;
        task_counters = (u8 *)D_80083460;
        *(u16 *)(task_counters + 0xA) = (u16)(*(u16 *)(task_counters + 0xA) + 1);
        position = *(u8 **)((u8 *)object - 0x14);
        task_data = (u8 *)task + 0x20;
        old_x = position[0x24];
        old_y = position[0x25];
        if (((Rec_D_80082E80 *)object)->unk_1C.at00_u32.v & 0x2000) {
            tile_mask = 0x300;
        }
        func_8009A3D0(old_x, old_y, tile_mask);
        search_origin = D_80082E80;
        if ((func_8009B88C(0, search_origin[0x24], search_origin[0x25], &tile_x, &tile_y) << 16) == 0) {
            tile_x = ((Coord *)position)->coord0;
            source_height = ((ArgObj *)object)->value;
            source_y = ((Coord *)position)->coord1;
            tile_y = source_y;
            ((Entry *)task_data)->value = source_height;
        } else {
            target_height = func_800BCB04(((tile_x << 6) + 0x20) & 0xFFE0,
                                       ((tile_y << 6) + 0x20) & 0xFFE0,
                                       (s16)(((Rec_D_80082E80 *)object)->unk_88.as_u16 - 0x20));
            *(u16 *)(task_data + 8) = target_height;
            if ((s16)target_height >= 0x201) {
                *(u16 *)(task_data + 8) = func_800BCB04(((tile_x << 6) + 0x20) & 0xFFE0,
                                                       ((tile_y << 6) + 0x20) & 0xFFE0,
                                                       -0x400);
            }
        }
        position[0x24] = (u8)tile_x;
        position[0x25] = (u8)tile_y;
        ((Rec_D_80082E80 *)object)->unk_88.as_u16 = *(u16 *)(task_data + 8);
        *(void **)((u8 *)task + 0x10) = &D_800C1EC4;
        *(void **)(task_data + 0xC) = object;
        *(s16 *)(task_data + 2) = 0x20;
        *(s16 *)(task_data + 4) = position[0x24];
        task_object = *(void **)(task_data + 0xC);
        *(s16 *)(task_data + 6) = position[0x25];
        func_8009A21C(position[0x24], position[0x25],
                      (task_object->unk_1C & 0x2000) ? 0x300 : 0x3000);
    }
    return task;
}
