#include "common.h"

typedef struct S_8009F9E8_0 {
    u8 unk_00;
    u8 unk_01;
} S_8009F9E8_0;   /* p in func_8009F9E8 */


extern volatile u16 D_80013716;

typedef struct {
    u8 flags;
    u8 kind;
} DungeonEntry;


extern DungeonEntry D_80013720[];

void *func_8009F9E8(s32 arg0, s32 arg1) {
    s32 i;
    register s32 count ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s32 count_page;
    s32 kind;
    s32 kind70;
    s32 kind78;
    s32 kind80;
    s32 kind90;
    void *base;
    register void *p ASM_REG("$3");   /* MATCH pin: retail delay-slot fill depends on it */

    base = (void *)0x80010000;
    ASM_KEEP(base);   /* MATCH pin: retail branch polarity depends on it */
    count = 0x80010000;
    count = *(volatile u16 *)(count + 0x3716);
    i = count - 1;
    base = (void *)((u32)base | 0x3720);
    if (i < 0) {
        return base;
    }

    kind70 = 0x70;
    kind78 = 0x78;
    kind80 = 0x80;
    kind90 = 0x90;
    ASM_KEEP(kind70);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(kind78);   /* MATCH pin: load-bearing for the whole function shape */
    ASM_KEEP(kind80);   /* MATCH pin: load-bearing for the whole function shape */
    ASM_KEEP(kind90);   /* MATCH pin: retail register colouring depends on it */
    arg0 &= 0xFF;
    arg1 &= 0xFF;
    count_page = 0x80010000;
    ASM_KEEP(count_page);   /* MATCH pin: retail register colouring depends on it */
    count = i * 2;
    p = (void *)((u32)count + (u32)base);
    do {
        kind = ((S_8009F9E8_0 *)p)->unk_01 & 0xF8;
        if (kind == kind70 || kind == kind78 || kind == kind80 || kind == kind90) {
            if (((S_8009F9E8_0 *)p)->unk_01 == arg0 && (((S_8009F9E8_0 *)p)->unk_00 & 0x20) == arg1) {
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
