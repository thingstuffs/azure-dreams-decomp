#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"

typedef struct S_800C30D4_0 {
    void * unk_00;
    u8 pad_04[0x23];
    u8 unk_27;
    s32 unk_28;
    u8 pad_2C[0x70];
    s16 unk_9C;
    u8 pad_9E[0x86];
    s32 unk_124;
} S_800C30D4_0;   /* arg0 in func_800C30D4; pointer addresses record offset 0x14 */

typedef struct S_800C30D4_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800C30D4_1;   /* temp_v0 in func_800C30D4 */


/* cfail-repair: tf7-phase1-cache-v3 */
void func_8008D330(void *arg0, void *arg1, void *arg2, void *arg3);          /* extern */
void func_80098B38();                         /* extern */
void func_80099844();           /* extern */
s32 func_800A48F0();        /* extern */
void func_800A5F38();                 /* extern */
void func_800A63B8(void *arg0, s32 arg1, s16 arg2);   /* extern */
s32 func_800AD6FC();            /* extern */
void *func_800C5BBC(); /* extern */
extern M2C_UNK D_800E1729;

/* Handles an item action for an entity, including its effect and item cleanup. */
s32 func_800C30D4(void *entity, s32 item, s16 action_type) {
    S_800C30D4_1 *tile;

    if (entity == ((u8 *)D_800E3D7C)) {
        ((S_800C30D4_0 *)((u8 *)entity - 0x14))->unk_124 = item;
        func_8008D330(entity, ((u8 *)(&D_80083780)), ((u8 *)(&D_80082E80)), entity);
        return 0;
    }
    if ((u32) entity <= 0x9FFFFFFFU) {
        func_800A63B8(entity, item, action_type);
        if (func_800AD6FC(entity, (*((u16 *)(((u8 *)D_800DDE84) + ((S_800C30D4_0 *)((u8 *)entity - 0x14))->unk_27 * 2))
            >> 6) & 3, 0) == 0) {
            func_800A5F38(entity, item);
            return 1;
        }
    }
    tile = ((S_800C30D4_0 *)((u8 *)entity - 0x14))->unk_00;
    func_800C5BBC((tile->unk_24 << 6) | 0x20, (tile->unk_25 << 6) | 0x20,
        ((S_800C30D4_0 *)((u8 *)entity - 0x14))->unk_9C, 0x802080, 0x20, 1);
    if (((func_800A48F0(entity, 5, 8) << 0x10) != 0) && (((S_800C30D4_0 *)((u8 *)entity - 0x14))->unk_28 & 0x4000)) {
        func_80099844(entity, &D_800E1729);
    }
    func_80098B38(item);
    {
        dungeonStatus.unk_0A = (u16) (((u16)dungeonStatus.unk_0A) - 1);
    }
    return 1;
}
