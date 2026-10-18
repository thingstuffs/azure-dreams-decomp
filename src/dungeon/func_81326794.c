#include "common.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"

/* Sparse views for fields not covered by the existing record types. */
typedef struct {
    u8 pad_00[0xC];
    u8 *field_0C;
} ActiveObjectFieldView_81326794;

typedef struct {
    u8 pad_00[0x2A];
    u16 field_2A;
} MapDataFieldView_81326794;

typedef struct {
    u8 pad_00[0x3D7C];
    u8 *field_3D7C;
} EntryPageFieldView_81326794;

typedef struct {
    u8 pad_00[0x10];
    u32 field_10;
} EntryFieldView_81326794;


typedef struct {
    u8 pad[0x3714];
    u16 flags;        /* 0x3714 */
    s16 f3716;
    s16 f3718;
    s16 f371A;
    void *handler;    /* 0x371C */
} SysWork;

extern void unlink_entity_node(void *);
extern u16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern void clear_actor_action_markers(u8 *state);

extern u16 D_800834E2;
extern s8 D_800DCF4D;
extern u8 * D_80174704;
extern s32 D_801748C8[];
extern s32 D_801749E0[];
extern s32 *D_80174CCC;
extern s16 D_80174CD0;

/* Reset map state, update coordinate lookup values, and process both active entries. */
void reset_map_state_and_process_entries(void) {
    s32 coord_aux;
    s16 entry_slot;
    s32 slot_offset;
    u16 coord_result;
    u16 lookup_key;
    u8 *map_object;
    u8 *active_object;
    u8 *map_data;
    u8 *entry;
    u8 *entry_page;
    SysWork *sys_work;

    entry_slot = 0;
    entry_page = (u8 *)0x800E0000;
    sys_work = (SysWork *)0x80010000;   /* integer page, five genuine accesses (decision 44); same SysWork view as func_81337FAC */
    D_80174704[0xD2] = 1;
    sys_work->f371A = 0;
    sys_work->f3718 = 0;
    sys_work->f3716 = 0;
    g_dungeon_status.unk_0A -= 1;
    active_object = D_80174704;
    sys_work->flags = (sys_work->flags | 9) & 0xFFEF;
    lookup_key = D_800834E2;
    sys_work->handler = (void *)D_801748C8[(lookup_key >> 9) & 7];
    map_object = ((ActiveObjectFieldView_81326794 *)active_object)->field_0C;
    D_800DCF4D = -1;
    map_data = active_object + 0x20;
    coord_result = get_rounded_facing_and_rounding_flag(map_object[0x24], map_object[0x25],
                           D_80082E80.tileX, D_80082E80.tileY, &coord_aux);
    ((MapDataFieldView_81326794 *)map_data)->field_2A = coord_result;
    D_80174CD0 = 0;
    D_80174CCC = (s32 *)D_801749E0[(coord_result >> 9) & 7];

loop:
    slot_offset = ((s32)entry_slot << 16) >> 14;
    entry = *(u8 **)&(((EntryPageFieldView_81326794 *)entry_page)->field_3D7C)[slot_offset + 0xAC];
    if (entry != 0) {

        clear_actor_action_markers(entry);
        unlink_entity_node(*(u8 **)&(((EntryPageFieldView_81326794 *)entry_page)->field_3D7C)[slot_offset + 0xAC]);
        entry = *(u8 **)&(((EntryPageFieldView_81326794 *)entry_page)->field_3D7C)[slot_offset + 0xAC];
        entry -= 0x20;
        ((EntryFieldView_81326794 *)entry)->field_10 |= 0x80000000;
    }
    entry_slot++;
    if (entry_slot < 2)
        goto loop;
}
