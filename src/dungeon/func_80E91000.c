#include "common.h"
#include "m2c_compat.h"

#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)

extern void func_80098B38(void *, void *);
extern void *func_800A04F0(void *, u8, u8, s16);
extern s32 func_800A6D30(void);
extern s16 func_800A70E4(s16, s16, s16);
extern s32 func_800C8310(void *, void *);

extern s32 D_80010248[];
extern s32 D_8001029C[];
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern s32 D_800E3548[];
extern s32 D_800E3D7C[];
extern s32 D_8016EFE4[];

#ifdef __mips__
static const u32 identity_bank[] __asm__("func_80E91000")
    __attribute__((section(".text.func_80E91000"), aligned(4))) = {
    0x8016AAF4, 0x8016ACC8, 0x8016B504, 0x8016B504,
    0x8016B504, 0x8016B530, 0x8016B4B0, 0x8016B4B0,
    0x8016B4B0, 0x8016B430, 0x8016B484, 0x8016B468,
    0x8016B530, 0x8016B4F4, 0x8016CD30, 0x8016CFF4,
    0x8016D074, 0x8016D0B8, 0x8016D11C, 0x8016D1E8,
    0x8016D294, 0x8016D3F0, 0x8016D3F0, 0x8016D3F0,
    0x8016D3F0, 0x8016D3F0, 0x8016D3F0, 0x8016D3F0,
    0x8016D3F0, 0x8016D3F0, 0x8016D304, 0x00000000,
    0x8016CDEC, 0x8016CDE4, 0x8016CDDC, 0x8016CDF4,
    0x8016CD98, 0x8016CD90, 0x8016CD88, 0x93824081,
    0x8F829482, 0x85828C82, 0x00000000, 0x94828982,
    0x8D828582, 0x00004081, 0x00004981, 0x83824081,
    0x95828F82, 0x84828C82, 0x66818E82, 0x40819482,
    0x94829382, 0x81828582, 0x40818C82, 0x88829482,
    0x40818582, 0x94828982, 0x8D828582, 0x00004481,
    0x8016E4B8, 0x8016E558, 0x8016E5E8, 0x8016E674,
    0x8016E6E4, 0x8016E7C4,
};
__asm__(".type func_80E91000,@function\n.size func_80E91000,756\n");
#define BODY_NAME composite_body
#define BODY_STORAGE static
#define BODY_ATTR __attribute__((used, section(".text.func_80E91000")))
#else
#define BODY_NAME func_80E91000
#define BODY_STORAGE
#define BODY_ATTR
#endif

BODY_STORAGE s32 BODY_NAME(void *, void *) BODY_ATTR;
/* Selects an item from the adjacent tile or target inventory and transfers it for processing. */
BODY_STORAGE s32 BODY_NAME(void *origin, void *actor)
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
        (s16)(*(u8 *)(origin_bytes + 0x24) + *(u16 *)(D_8006CCD8 + direction_offset)),
        (s16)(*(u8 *)(origin_bytes + 0x25) + *(u16 *)(D_8006CCE8 + direction_offset)),
        *(s16 *)(actor_bytes + 0x88));
    if (ground_index >= 0) {
        D_8016EFE4[0] = D_800E3548[ground_index];
        D_800E3548[ground_index] = 0;
        return (s32)D_8016EFE4;
    }

    target = func_800A04F0(actor, *(u8 *)(origin_bytes + 0x24), *(u8 *)(origin_bytes + 0x25),
                          *(s16 *)(actor_bytes + 0x2A));
    if (target == NULL) {
        goto return_zero;
    }
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
            if ((u32)item_slot == 0) {
                goto return_zero;
            }
            if ((u32)item_slot == 0x13) {
                return 0;
            }
            if (*(u8 *)(inventory_base + 0x24B) & 0x20) {
                goto entry_zero;
            }
            {
                s32 item_data;

                item_slot = (u8 *)0x80010248;
                item_slot += item_offset;
                item_data = *(s32 *)item_slot;
                D_8016EFE4[0] = item_data;
                func_80098B38(item_slot, inventory_base);
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
entry_zero:
return_zero:
    return 0;
}
