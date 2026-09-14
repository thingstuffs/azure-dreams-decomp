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
extern s32 D_80150FE4[];

#ifdef __mips__
static const u32 identity_bank[] __asm__("func_80EAF000")
    __attribute__((section(".text.func_80EAF000"), aligned(4))) = {
    0x8014caf4, 0x8014ccc8, 0x8014d504, 0x8014d504,
    0x8014d504, 0x8014d530, 0x8014d4b0, 0x8014d4b0,
    0x8014d4b0, 0x8014d430, 0x8014d484, 0x8014d468,
    0x8014d530, 0x8014d4f4, 0x8014ed30, 0x8014eff4,
    0x8014f074, 0x8014f0b8, 0x8014f11c, 0x8014f1e8,
    0x8014f294, 0x8014f3f0, 0x8014f3f0, 0x8014f3f0,
    0x8014f3f0, 0x8014f3f0, 0x8014f3f0,
    0x8014f3f0, 0x8014f3f0, 0x8014f3f0, 0x8014f304,
    0x00000000, 0x8014edec, 0x8014ede4, 0x8014eddc,
    0x8014edf4, 0x8014ed98, 0x8014ed90, 0x8014ed88,
    0x93824081, 0x8f829482, 0x85828c82, 0x00000000,
    0x94828982, 0x8d828582, 0x00004081, 0x00004981,
    0x83824081, 0x95828f82, 0x84828c82, 0x66818e82,
    0x40819482, 0x94829382, 0x81828582, 0x40818c82,
    0x88829482, 0x40818582, 0x94828982, 0x8d828582,
    0x00004481, 0x801504b8, 0x80150558, 0x801505e8,
    0x80150674, 0x801506e4, 0x801507c4,
};
__asm__(".type func_80EAF000,@function\n.size func_80EAF000,756\n");
#define BODY_NAME composite_body
#define BODY_STORAGE static
#define BODY_ATTR __attribute__((used, section(".text.func_80EAF000")))
#else
#define BODY_NAME func_80EAF000
#define BODY_STORAGE
#define BODY_ATTR
#endif

BODY_STORAGE s32 BODY_NAME(void *, void *) BODY_ATTR;
/* Transfer an eligible ground or carried item to the pending item slot. */
BODY_STORAGE s32 BODY_NAME(void *origin, void *actor) {
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
        (s16)(*(u8 *)(origin_bytes + 0x24) + *(u16 *)(D_8006CCD8 + direction_offset)),
        (s16)(*(u8 *)(origin_bytes + 0x25) + *(u16 *)(D_8006CCE8 + direction_offset)),
        *(s16 *)(actor_bytes + 0x88));
    if (ground_slot >= 0) {
        D_80150FE4[0] = D_800E3548[ground_slot];
        D_800E3548[ground_slot] = 0;
        return (s32)D_80150FE4;
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
            if ((u32)item_ptr == 0) {
                goto return_zero;
            }
            if ((u32)item_ptr == 0x13) {
                return 0;
            }
            if (*(u8 *)(slot_base + 0x24B) & 0x20) {
                goto entry_zero;
            }
            {
                s32 item_word;

                item_ptr = (u8 *)0x80010248;
                item_ptr += slot_offset;
                item_word = *(s32 *)item_ptr;
                D_80150FE4[0] = item_word;
                func_80098B38(item_ptr, slot_base);
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
entry_zero:
return_zero:
    return 0;
}
