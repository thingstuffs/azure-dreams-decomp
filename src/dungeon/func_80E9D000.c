#include "shared/dungeon_item_entries.h"
#include "common.h"
#include "shared/dir_step.h"
#include "m2c_compat.h"

extern void func_80098B38(void *, void *);
extern void *func_800A04F0(void *, u8, u8, s16);
extern s32 func_800A6D30(void);
extern s16 func_800A70E4(s16, s16, s16);
extern s32 func_800C8310(void *, void *);

extern s32 D_800E3D7C[];
extern s32 D_80162FE4[];

typedef struct { s32 value; } ItemWord;


 s32 func_8015E908(void *, void *) ;
/* Moves an eligible item from a nearby slot or target into the shared item slot. */
 s32 func_8015E908(void *origin, void *actor) {
    u8 *origin_bytes = (u8 *)origin;
    u8 *actor_bytes = (u8 *)actor;
    s32 direction_offset;
    s16 tile_slot;
    void *target;
    u8 *item_ptr;

    direction_offset = (*(u16 *)(actor_bytes + 0x2A) >> 8) & 0xE;
    tile_slot = func_800A70E4(
        (s16)(*(u8 *)(origin_bytes + 0x24) + *(u16 *)(((u8 *)dirStepX) + direction_offset)),
        (s16)(*(u8 *)(origin_bytes + 0x25) + *(u16 *)(((u8 *)dirStepY) + direction_offset)),
        *(s16 *)(actor_bytes + 0x88));
    if (tile_slot >= 0) {
        s32 *shared_base;
        s32 *shared_slot;
        shared_base = D_80162FE4;
        shared_slot = shared_base;
        *(ItemWord *)shared_base = *(ItemWord *)&((s32 *)D_800E3548)[tile_slot];
        ((s32 *)D_800E3548)[tile_slot] = 0;
        return (s32)shared_slot;
    }

    target = func_800A04F0(actor, *(u8 *)(origin_bytes + 0x24), *(u8 *)(origin_bytes + 0x25),
                           *(s16 *)(actor_bytes + 0x2A));
    if (target != NULL) {
        if (target == (void *)D_800E3D7C[0]) {
            if (func_800C8310(target, target) != 0) {
                return 0;
            }
            {
                s32 slot_index;
                s16 item_count;
                s32 *slot_scan;
                s32 count;
                slot_index = 0;
                count = 0;
                slot_scan = (s32 *)0x80010000;
                for (;;) {
                    if (slot_scan[167] != 0) {
                        count++;
                    }
                    slot_scan++;
                    if (++slot_index >= 20) {
                        break;
                    }
                }
                item_count = count;
                if (item_count == 0) {
                    return 0;
                }
                count =
                    (s32)((((func_800A6D30() & 0xFFFF) % item_count) << 16) >> 14);
                slot_index = count + 0x80010000;
                if (*(u8 *)(slot_index + 0x249) == 0 || *(u8 *)(slot_index + 0x249) == 0x13) {
                    return 0;
                }
                if (*(u8 *)(slot_index + 0x24B) & 0x20) {
                    return 0;
                }
                {
                    s32 item_data;
                    s32 *shared_base;

                    item_ptr = (u8 *)(count + 0x80010248);
                    item_data = *(s32 *)item_ptr;
                    shared_base = D_80162FE4;
                    shared_base[0] = item_data;


                    func_80098B38(item_ptr, (void *)slot_index);
                    return (s32)shared_base;
                }
            }
        }
        if (*(u8 *)((u8 *)target + 0x49) == 0) {
            return 0;
        }
        if (*(u8 *)((u8 *)target + 0x4B) & 0x20) {
            return 0;
        }
        {
            s32 *shared_base;
            s32 *shared_slot;
            s32 item_data;

            shared_base = D_80162FE4;

            item_data = *(s32 *)((u8 *)target + 0x48);
            shared_slot = shared_base;
            shared_base[0] = item_data;

            *(s32 *)((u8 *)target + 0x48) = 0;
            return (s32)shared_slot;
        }
entry_zero:
    }
    return 0;
}
