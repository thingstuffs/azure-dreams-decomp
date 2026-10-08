#include "shared/dungeon_item_entries.h"
#include "common.h"
#include "shared/dir_step.h"
#include "m2c_compat.h"

#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)

extern void func_80098B38(void *);
extern void *func_800A04F0(void *, u8, u8, s16);
extern s32 func_800A6D30(void);
extern s16 func_800A70E4(s16, s16, s16);
extern s32 func_800C8310(void *, void *);

extern s32 D_800E3D7C[];
extern s32 D_8016EFE4[];



 s32 func_8016A908(void *, void *) ;
/* Selects an item from the adjacent tile or target inventory and transfers it for processing. */
 s32 func_8016A908(void *origin, void *actor)
{
    u8 *origin_bytes = (u8 *)origin;
    u8 *actor_bytes = (u8 *)actor;
    s32 direction_offset;
    s16 ground_index;
    void *target;
    s32 item_offset;
    u8 *inventory_base;
    u8 *item_slot;

    direction_offset = (*(u16 *)(actor_bytes + 0x2A) >> 8) & 0xE;
    ground_index = func_800A70E4(
        (s16)(*(u8 *)(origin_bytes + 0x24) + *(u16 *)(((u8 *)dirStepX) + direction_offset)),
        (s16)(*(u8 *)(origin_bytes + 0x25) + *(u16 *)(((u8 *)dirStepY) + direction_offset)),
        *(s16 *)(actor_bytes + 0x88));
    if (ground_index >= 0) {
        D_8016EFE4[0] = ((s32 *)D_800E3548)[ground_index];
        ((s32 *)D_800E3548)[ground_index] = 0;
        return (s32)D_8016EFE4;
    }

    target = func_800A04F0(actor, *(u8 *)(origin_bytes + 0x24), *(u8 *)(origin_bytes + 0x25),
                           *(s16 *)(actor_bytes + 0x2A));
    if (target != NULL) {
        if (target == (void *)D_800E3D7C[0]) {
            if (func_800C8310(target, target) != 0) {
                return 0;
            }
            {
#ifdef __mips__
                s16 occupied_count;
                register s32 slot_index;
#else
                s32 slot_index;
                s16 occupied_count;
                s32 *slot_scan;
#endif
                slot_index = 0;
                occupied_count = slot_index;
                item_slot = (u8 *)0x80010000;
scan_loop:
                if (((s32 *)item_slot)[167] != 0) {
                    occupied_count++;
                }
                slot_index++;
                item_slot += sizeof(s32);
                if (slot_index < 20) {
                    goto scan_loop;
                }
                if (occupied_count == 0) {
                    return 0;
                }
                item_offset =
                    (s32)((((func_800A6D30() & 0xFFFF) % occupied_count) << 16) >> 14);
                inventory_base = (u8 *)(item_offset + 0x80010000);
                item_slot = (u8 *)(u32)*(u8 *)(inventory_base + 0x249);
                if ((u32)item_slot == 0 || (u32)item_slot == 0x13) {
                    return 0;
                }
                if (*(u8 *)(inventory_base + 0x24B) & 0x20) {
                    return 0;
                }
                {
                    s32 item_data;

                    item_slot = (u8 *)0x80010248;
                    item_slot += item_offset;
                    item_data = *(s32 *)item_slot;
                    D_8016EFE4[0] = item_data;
                    func_80098B38(item_slot);
                    return (s32)D_8016EFE4;
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
            s32 item_data;

            item_data = *(s32 *)((u8 *)target + 0x48);
            D_8016EFE4[0] = item_data;
            *(s32 *)((u8 *)target + 0x48) = 0;
            return (s32)D_8016EFE4;
        }
    }
    return 0;
}
