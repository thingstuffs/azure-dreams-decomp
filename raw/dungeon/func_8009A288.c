#include "common.h"

extern volatile u16 D_80013716;

typedef struct {
    u8 flags;
    u8 kind;
} DungeonEntry;

#define FIELD(ptr, type, offset) (*(type *)((s8 *)(ptr) + (offset)))

extern DungeonEntry D_80013720[];

void *func_8009F9E8(s32 arg0, s32 arg1) {
    register s32 i ASM_REG("$6");
    register s32 count ASM_REG("$2");
    register s32 count_page ASM_REG("$8");
    s32 kind;
    s32 kind70;
    s32 kind78;
    s32 kind80;
    s32 kind90;
    register void *base ASM_REG("$7");
    register void *p ASM_REG("$3");

    base = (void *)0x80010000;
    ASM_KEEP(base);
    count = 0x80010000;
    ASM_KEEP(count);
    count = *(volatile u16 *)(count + 0x3716);
    ASM_KEEP(count);
    i = count - 1;
    base = (void *)((u32)base | 0x3720);
    if (i < 0) {
        return base;
    }

    ASM_KEEP(i);
    kind70 = 0x70;
    kind78 = 0x78;
    kind80 = 0x80;
    kind90 = 0x90;
    ASM_KEEP(kind70);
    ASM_KEEP(kind78);
    ASM_KEEP(kind80);
    ASM_KEEP(kind90);
    arg0 &= 0xFF;
    arg1 &= 0xFF;
    count_page = 0x80010000;
    ASM_KEEP(count_page);
    count = i * 2;
    ASM_KEEP(count);
    p = (void *)((u32)count + (u32)base);
    ASM_KEEP(p);
    do {
        kind = FIELD(p, u8, 1) & 0xF8;
        if (kind == kind70 || kind == kind78 || kind == kind80 || kind == kind90) {
            if (FIELD(p, u8, 1) == arg0 && (FIELD(p, u8, 0) & 0x20) == arg1) {
                return p;
            }
        } else {
            return (*(volatile u16 *)(count_page + 0x3716) * 2) + base;
        }
        i--;
        p -= 2;
    } while (i >= 0);

    return base;
}

/* MECHANISM: The true-space function is a frameless leaf; both apparent calls are
   local jumps to its shared return epilogue. The two-byte record stride and u8
   field widths preserve the retail loop, masks, and pointer-return behavior. */
