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
extern s32 D_80150FE4[];



 s32 func_8014C908(void *, void *) ;
/* Transfer an eligible ground or carried item to the pending item slot. */
 s32 func_8014C908(void *origin, void *actor) {
    u8 *origin_bytes = (u8 *)origin;
    u8 *actor_bytes = (u8 *)actor;
    s32 direction_offset;
    s16 ground_slot;
    void *target;
    s32 slot_offset;
    u8 *slot_base;
    u8 *item_ptr;

    direction_offset = (*(u16 *)(actor_bytes + 0x2A) >> 8) & 0xE;
    ground_slot = func_800A70E4(
        (s16)(*(u8 *)(origin_bytes + 0x24) + *(u16 *)(((u8 *)dirStepX) + direction_offset)),
        (s16)(*(u8 *)(origin_bytes + 0x25) + *(u16 *)(((u8 *)dirStepY) + direction_offset)),
        *(s16 *)(actor_bytes + 0x88));
    if (ground_slot >= 0) {
        D_80150FE4[0] = ((s32 *)D_800E3548)[ground_slot];
        ((s32 *)D_800E3548)[ground_slot] = 0;
        return (s32)D_80150FE4;
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
                s16 item_count;
                register s32 slot_index;
#else
                s32 slot_index;
                s16 item_count;
                s32 *inventory_scan;
#endif
                slot_index = 0;
                item_count = slot_index;
                item_ptr = (u8 *)0x80010000;
scan_loop:
                if (((s32 *)item_ptr)[167] != 0) {
                    item_count++;
                }
                slot_index++;
                item_ptr += sizeof(s32);
                if (slot_index < 20) {
                    goto scan_loop;
                }
                if (item_count == 0) {
                    return 0;
                }
                slot_offset = (s32)((((func_800A6D30() & 0xFFFF) % item_count) << 16) >> 14);
                slot_base = (u8 *)(slot_offset + 0x80010000);
                item_ptr = (u8 *)(u32)*(u8 *)(slot_base + 0x249);
                if ((u32)item_ptr == 0 || (u32)item_ptr == 0x13) {
                    return 0;
                }
                if (*(u8 *)(slot_base + 0x24B) & 0x20) {
                    return 0;
                }
                {
                    s32 item_word;

                    item_ptr = (u8 *)0x80010248;
                    item_ptr += slot_offset;
                    item_word = *(s32 *)item_ptr;
                    D_80150FE4[0] = item_word;
                    func_80098B38(item_ptr);
                    return (s32)D_80150FE4;
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
            s32 item_word;

            item_word = *(s32 *)((u8 *)target + 0x48);
            D_80150FE4[0] = item_word;
            *(s32 *)((u8 *)target + 0x48) = 0;
            return (s32)D_80150FE4;
        }
    }
    return 0;
}
