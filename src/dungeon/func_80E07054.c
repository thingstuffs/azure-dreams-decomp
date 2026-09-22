#include "common.h"

typedef void (*Callback)(void);

extern u8 D_80083498[];

extern u8 *func_8003FD64(s32 kind, void *data);
extern void func_8004491C(void *object, Callback callback);
extern s32 func_800A6D30(void);
extern void func_800A48F0(void *object, s32 attr_a, s16 attr_b);
extern void func_800A9C18(void *object, void *attr_a, void *attr_b, s32 attr_c);
extern void func_800AA36C(void *object, void *attr_a, void *attr_b, void *attr_c);

extern void func_80045340(void);
extern void func_8014CE5C(void);
extern void func_80150510(void);
extern void func_80150538(void);
extern void func_8014CA58(void);

/* Spawn this overlay's effect object: allocate it, fill its two parts from the attributes and arm its handlers. */
void *func_8014C854(s32 spawn_flags, s32 attr_a, s16 attr_b, s32 attr_c)
{
    s32 held_flags = spawn_flags;
    u8 *work = 0;
    register s32 held_a ASM_REG("$21") = attr_a;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    long part_b;
    long work_copy;
    u8 *object;
    u8 *part_a;
    s16 flags_s16;
    s32 alloc_kind;
    u8 *alloc_data;
    u32 callback_page;
    u32 flags0;
    u32 flags1;
    u32 masked;
    s32 random;

    alloc_kind = 0x112;
    alloc_data = D_80083498;
    object = func_8003FD64(alloc_kind, alloc_data);
    flags_s16 = held_flags;
    if (object != 0) {
        work = object;
        work += 0x20;
        *(u8 *)(work + 0x13) = 0x1C;
        func_8004491C(object, func_80045340);

        part_a = *(u8 **)(object + 8);
        *(s16 *)(part_a + 0xA) = attr_c;
        part_b = (long)*(u8 **)(object + 0xC);
        *(u8 *)((u8 *)part_b + 0x25) = attr_b;
        work_copy = (long)work;
        *(u8 *)((u8 *)part_b + 0x24) = held_a;

    if ((held_flags & 3) == 1) {
        *(Callback *)(work + 0x8C) = func_8014CE5C;
        *(u32 *)(work + 0x14) |= 0x6000;
        *(u32 *)(work + 0x1C) |= 0x6000;
        *(Callback *)((u8 *)part_b + 0x2C) = func_80150510;
    } else if ((held_flags & 3) >= 2) {
        *(Callback *)(work + 0x8C) = func_8014CE5C;
        flags0 = *(u32 *)(work + 0x14) | 0x2000;
        flags1 = *(u32 *)(work + 0x1C) | 0x2000;
        *(u32 *)(work + 0x14) = flags0;
        *(u32 *)(work + 0x1C) = flags1;
        *(Callback *)((u8 *)part_b + 0x2C) = func_80150510;
    } else {
        masked = held_flags & -4;
        if ((s16)masked == 0) {
            if ((*(u32 *)(work + 0x14) & 0x200) == 0) {
                if ((func_800A6D30() & 1) != 0) {
                    random = func_800A6D30();
                    func_800A48F0(work, 1, (random & 0x3F) | 0x20);
                    *(Callback *)((u8 *)part_b + 0x2C) = func_80150538;
                }
            }
#ifdef NON_MATCHING
            *(Callback *)((u8 *)work_copy + 0x8C) = func_8014CE5C;
#else
            callback_page = 0x80150000;
            ASM_KEEP_NV(callback_page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
            callback_page -= 0x31A4;
            *(Callback *)((u8 *)work_copy + 0x8C) = (Callback)callback_page;
#endif
        } else {
#ifdef NON_MATCHING
            *(Callback *)(work + 0x8C) = func_8014CE5C;
#else
            callback_page = 0x80150000;
            ASM_KEEP_NV(callback_page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
            callback_page -= 0x31A4;
            *(Callback *)(work + 0x8C) = (Callback)callback_page;
#endif
        }
        *(Callback *)((u8 *)part_b + 0x2C) = func_80150510;
    }

    *(Callback *)(object + 0x10) = func_8014CA58;
    func_800A9C18(object, part_a, (u8 *)part_b, (s16)flags_s16);

        *(u8 *)((u8 *)work_copy + 0x9A) = 0xFF;
        *(s8 *)((u8 *)work_copy + 0x9C) = -1;
        func_800AA36C((u8 *)work_copy, part_a, (u8 *)part_b, work);
    }
    return work;
}
