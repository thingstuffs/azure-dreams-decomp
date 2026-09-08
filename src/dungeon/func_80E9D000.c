#include "common.h"
#include "m2c_compat.h"

extern void func_80098B38(void *, void *);
extern void *func_800A04F0(void *, u8, u8, s16);
extern s32 func_800A6D30(void);
extern s16 func_800A70E4(s16, s16, s16);
extern s32 func_800C8310(void *, void *);
extern void func_8015EADC() __attribute__((noreturn));

extern s32 D_80010248[];
extern s32 D_8001029C[];
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern s32 D_800E3548[];
extern s32 D_800E3D7C[];
extern s32 D_80162FE4[];

#ifdef __mips__
static const u32 identity_bank[] __asm__("func_80E9D000")
    __attribute__((section(".text.func_80E9D000"), aligned(4))) = {
    0x8015EAF4, 0x8015ECC8, 0x8015F504, 0x8015F504,
    0x8015F504, 0x8015F530, 0x8015F4B0, 0x8015F4B0,
    0x8015F4B0, 0x8015F430, 0x8015F484, 0x8015F468,
    0x8015F530, 0x8015F4F4, 0x80160D30, 0x80160FF4,
    0x80161074, 0x801610B8, 0x8016111C, 0x801611E8,
    0x80161294, 0x801613F0, 0x801613F0, 0x801613F0,
    0x801613F0, 0x801613F0, 0x801613F0, 0x801613F0,
    0x801613F0, 0x801613F0, 0x80161304, 0x00000000,
    0x80160DEC, 0x80160DE4, 0x80160DDC, 0x80160DF4,
    0x80160D98, 0x80160D90, 0x80160D88, 0x93824081,
    0x8F829482, 0x85828C82, 0x00000000, 0x94828982,
    0x8D828582, 0x00004081, 0x00004981, 0x83824081,
    0x95828F82, 0x84828C82, 0x66818E82, 0x40819482,
    0x94829382, 0x81828582, 0x40818C82, 0x88829482,
    0x40818582, 0x94828982, 0x8D828582, 0x00004481,
    0x801624B8, 0x80162558, 0x801625E8, 0x80162674,
    0x801626E4, 0x801627C4,
};
__asm__(".type func_80E9D000,@function\n.size func_80E9D000,756\n");
#define BODY_NAME composite_body
#define BODY_STORAGE static
#define BODY_ATTR __attribute__((used, section(".text.func_80E9D000")))
#else
#define BODY_NAME func_80E9D000
#define BODY_STORAGE
#define BODY_ATTR
#endif

BODY_STORAGE s32 BODY_NAME(void *, void *) BODY_ATTR;
/* Moves an eligible item from a nearby slot or target into the shared item slot. */
BODY_STORAGE s32 BODY_NAME(void *origin, void *actor) {
    u8 *origin_bytes = (u8 *)origin;
    u8 *actor_bytes = (u8 *)actor;
    s32 direction_offset;
    s16 tile_slot;
    void *target;
    s32 item_offset;
    u8 *item_base;
    u8 *item_ptr;

    direction_offset = (*(u16 *)(actor_bytes + 0x2A) >> 8) & 0xE;
    tile_slot = func_800A70E4(
        (s16)(*(u8 *)(origin_bytes + 0x24) + *(u16 *)(D_8006CCD8 + direction_offset)),
        (s16)(*(u8 *)(origin_bytes + 0x25) + *(u16 *)(D_8006CCE8 + direction_offset)),
        *(s16 *)(actor_bytes + 0x88));
    if (tile_slot >= 0) {
#ifdef __mips__
        s32 *shared_base;
        s32 *shared_slot;
#else
        s32 *shared_base;
        s32 *shared_slot;
#endif
        s32 item_data;

        shared_base = (s32 *)0x80160000;
        ASM_KEEP(shared_base);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        item_data = D_800E3548[tile_slot];
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        shared_slot = shared_base + 3065;
        ASM_KEEP(shared_slot);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        shared_base[3065] = item_data;
        D_800E3548[tile_slot] = 0;
        func_8015EADC(item_data, shared_base);
        __builtin_unreachable();
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
            register s32 slot_index ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            s16 item_count;
            register s32 *slot_scan ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
#else
            s32 slot_index;
            s16 item_count;
            s32 *slot_scan;
#endif
            slot_index = 0;
            item_count = slot_index;
            slot_scan = (s32 *)0x80010000;
            do {
                if (slot_scan[167] != 0) {
                    item_count++;
                }
                slot_index++;
                slot_scan++;
            } while (slot_index < 20);
            if (item_count == 0) {
                return 0;
            }
            item_offset =
                (s32)((((func_800A6D30() & 0xFFFF) % item_count) << 16) >> 14);
            item_base = (u8 *)(item_offset + 0x80010000);
            if (*(u8 *)(item_base + 0x249) == 0) {
                goto return_zero;
            }
            if (*(u8 *)(item_base + 0x249) == 0x13) {
                return 0;
            }
            if (*(u8 *)(item_base + 0x24B) & 0x20) {
                goto entry_zero;
            }
            {
                s32 item_data;
                s32 *shared_base;
#ifdef __mips__
                register s32 shared_slot_addr ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
#else
                s32 shared_slot_addr;
#endif
                item_ptr = (u8 *)(item_offset + 0x80010248);
                item_data = *(s32 *)item_ptr;
                ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
                shared_base = (s32 *)0x80160000;
                ASM_KEEP(shared_base);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                shared_base[3065] = item_data;
                shared_base += 3065;
                func_80098B38(item_ptr, item_base);
                shared_slot_addr = (s32)shared_base;
                ASM_TAILSLOT_PIN(shared_slot_addr);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                func_8015EADC();
                __builtin_unreachable();
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
#ifdef __mips__
        s32 *shared_base;
        register s32 *shared_slot ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
#else
        s32 *shared_base;
        s32 *shared_slot;
#endif
        s32 item_data;

        shared_base = (s32 *)0x80160000;
        ASM_KEEP(shared_base);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        item_data = *(s32 *)((u8 *)target + 0x48);
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        shared_slot = shared_base + 3065;
        ASM_KEEP(shared_slot);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        shared_base[3065] = item_data;
        *(s32 *)((u8 *)target + 0x48) = 0;
        func_8015EADC(item_data, target);
        __builtin_unreachable();
    }
entry_zero:
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
return_zero:
    return 0;
}
