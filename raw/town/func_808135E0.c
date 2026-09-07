#include "common.h"

extern u8 *D_8012F130;

extern s32 func_8006BC50(void *, void *, s32 *, s32 *);
extern u32 func_8006D9DC(s32, s32, s32, s32);
extern void func_8006DBBC(void *, s32);
extern void func_8006DD38(void *);
extern void func_8006F49C(void *, s32, s32, u32, s32);

s32 func_808135E0(void *arg0)
{
    u8 *current;
    u8 **rootp;
    u8 *alloc_base;
    u8 *bound_base0;
    u8 *link_base0;
    register u8 *link_base1 ASM_REG("$4");
    u8 *other_base;
    u8 *link_base2;
    u8 *object;
    u8 *next0;
    u8 *next1;
    u8 *other;
    u32 *entry0;
    u32 *entry1;
    u32 *entry2;
    u32 *entry3;
    register u32 low_mask ASM_REG("$19");
    u32 high_mask;
    s32 coords[2];
    s32 *coord1p;
    register s32 *call_arg2 ASM_REG("$6");
    register s32 *call_arg3 ASM_REG("$7");
    s32 raw_first;
    register s32 first ASM_REG("$16");
    s32 second;
    s32 index;
    s32 offset;
    u32 value;

    current = arg0;
    rootp = &D_8012F130;
    coord1p = &coords[1];
    low_mask = 0x00FFFFFF;
    high_mask = 0xFF000000;

    do {
        if ((*(u16 *)(current + 0x24) & 1) == 0) {
            next0 = 0;
            alloc_base = *rootp;
            object = *(u8 **)(alloc_base + 0x8D0);
            bound_base0 = alloc_base;
            if (object != 0) {
                register u32 limit0 ASM_REG("$2");
                limit0 = 0x108D4;
                next0 = object + 0x10;
                next0 = (u8 *)((u32)next0 & -(u32)(next0 <= bound_base0 + limit0));
            }
            *(u8 **)(alloc_base + 0x8D0) = next0;

            *(u32 *)(object + 4) = *(u32 *)(current + 0x14);
            func_8006DD38(object);
            func_8006DBBC(object, 1);

            raw_first = func_8006BC50(current + 4, object + 8, &coords[0], coord1p);
            link_base1 = current + 0xC;
            bound_base0 = object + 0xC;
            call_arg2 = &coords[0];
            call_arg3 = coord1p;
            ASM_USE2(link_base1, bound_base0);
            ASM_USE2(call_arg2, call_arg3);
            first = raw_first;
            second = func_8006BC50(link_base1, bound_base0, call_arg2, call_arg3);
            first = (s16)first;
            first += second;
            index = first >> 1;
            if ((u16)index < 0x200) {
                index = (s16)index;
                offset = index * 4;
                link_base0 = *rootp;
                entry0 = (u32 *)(offset + (u32)link_base0 + 0xB0);
                *(u32 *)object = (*(u32 *)object & high_mask) | (*entry0 & low_mask);

                link_base1 = *rootp;
                entry1 = (u32 *)(offset + (u32)link_base1 + 0xB0);
                *entry1 = (*entry1 & high_mask) | ((u32)object & low_mask);
                ASM_KEEP(object);

                other_base = *rootp;
                next1 = 0;
                other = *(u8 **)(other_base + 0x8D0);
                link_base1 = other_base;
                if (other != 0) {
                    register u32 limit1 ASM_REG("$2");
                    limit1 = 0x108D4;
                    next1 = other + 0xC;
                    next1 = (u8 *)((u32)next1 & -(u32)(next1 <= link_base1 + limit1));
                }

                *(u8 **)(other_base + 0x8D0) = next1;
                value = func_8006D9DC(0, 0, 0, 0);
                func_8006F49C(other, 0, 0, (u16)value, 0);

                link_base2 = *rootp;
                entry2 = (u32 *)(offset + (u32)link_base2 + 0xB0);
                *(u32 *)other = (*(u32 *)other & high_mask) | (*entry2 & low_mask);

                link_base1 = *rootp;
                entry3 = (u32 *)(offset + (u32)link_base1 + 0xB0);
                *entry3 = (*entry3 & high_mask) | ((u32)other & low_mask);
                ASM_KEEP(other);
            }
        }

        link_base1 = *(u8 **)(current - 8);
        current = link_base1 + 0x20;
    } while (link_base1 != 0);

    ASM_CLOBBER("$4");
    return 0;
}

/* MECHANISM: A two-word coords frame object yields sp+0x18 and held s7=sp+0x1c.
   Split v0 bound live ranges and short ABI pins reproduce both pool/RMW regions.
   Prepared a0-a3 plus ASM_USE2 fences sink the first-result copy into the jal slot. */
