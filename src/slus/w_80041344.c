#include "common.h"

#include "common.h"

typedef struct {
    u16 cmd;
    u16 size;
    s32 offset;
    union {
        struct { u16 x, y, w; } t;
        struct { s32 a, b; } m;
    } u;
} S_80041344;

extern void *jtbl_8002D630[];
extern u32 D_80080A8C;
extern void func_8004068C(void *src, void *dst);
extern void func_8003F80C(void *src, s32 x, s32 y, s32 flags);
extern void LoadImage(void *rect, void *data);
extern void DrawSync(s32 mode);
extern void *memcpy(void *dst, void *src, s32 size);

/* Process resource commands to upload images, copy data, and relocate pointers. */
void func_80041344(s32 data_base, void *scratch)
{
    S_80041344 *entry = (S_80041344 *)data_base;
    u16 entry_size;
    s32 color_index, item_index, item_count;
    s32 reloc_addr;
    s32 vram_offset, palette_count;
    s32 cmd_index;
    u16 *color;
    void *src;
    void *src_addr;
    s32 flags;
    S_80041344 *command;
    void **handlers = jtbl_8002D630;
    static void *const keepalive[] = {
        &&LA, &&LB, &&LC, &&LD, &&LE, &&LF, &&LG, &&LH, &&LI
    };
    (void)keepalive;

    for (;;) {
        cmd_index = entry->cmd - 1;
        command = entry;
        if ((u32)cmd_index >= 9) {
            return;
        }
        goto *handlers[cmd_index];

LA:
        func_8004068C((void *)(data_base + command->offset), scratch);
        LoadImage((void *)&entry->u, scratch);
        DrawSync(0);
        goto next;
LB:
        LoadImage((void *)&entry->u, (void *)(data_base + command->offset));
        DrawSync(0);
        goto next;
LC:
        vram_offset = entry->u.t.x;
        palette_count = entry->u.t.y;
        src_addr = (void *)command->offset;
        flags = (s16)entry->u.t.w;
        src = ((void *)((void *)(data_base + (s32)src_addr)));
        goto call_tile;
LD:
        cmd_index = entry->u.t.w;
        vram_offset = entry->u.t.x;
        palette_count = entry->u.t.y;
        src_addr = (void *)command->offset;
        cmd_index |= 2;
        src = ((void *)((void *)(data_base + (s32)src_addr)));
        goto sign_flags;
LE:
        src = (void *)(data_base + command->offset);
        item_count = entry->u.t.y << 4;
        color = (u16 *)src + 1;
        for (item_index = 1; item_index < item_count; item_index++) {
            *color |= 0x8000;
            color++;
        }
        cmd_index = entry->u.t.w;
        vram_offset = entry->u.t.x;
        palette_count = entry->u.t.y;
        cmd_index |= 4;
        goto sign_flags;
LF:
        src = (void *)(data_base + command->offset);
        color = (u16 *)src;
        item_count = entry->u.t.y;
        for (item_index = 0; item_index < item_count; item_index++) {
            color++;
            for (color_index = 1; color_index < 16; color_index++) {
                *color |= 0x8000;
                color++;
            }
        }
        cmd_index = entry->u.t.w;
        vram_offset = entry->u.t.x;
        palette_count = entry->u.t.y;
        cmd_index |= 2;
sign_flags:
        item_index = (u32)cmd_index << 16;
        item_index >>= 16;
        flags = item_index;
call_tile:
        func_8003F80C(src, vram_offset, palette_count, flags);
        DrawSync(0);
        goto next;
LG:
        src_addr = (void *)command->offset;
        func_8004068C((void *)(data_base + (s32)src_addr),
                      (void *)(D_80080A8C + command->u.m.a));
        goto next;
LH:
        src_addr = (void *)0x80080000;
        memcpy((void *)((u32 *)src_addr)[0x2A3],
               (void *)(data_base + command->offset),
               command->u.m.b + command->u.m.a);
        goto next;
LI:
        reloc_addr = data_base + command->offset;
        for (item_index = entry->u.t.x; item_index > 0; item_index--) {
            *(s32 *)(reloc_addr + 4) = data_base + *(s32 *)(reloc_addr + 4);
        }
next:
        entry_size = entry->size;
        entry = (S_80041344 *)((u8 *)entry + entry_size);
        if (entry_size == 0) {
            *(u32 *)0x80080A8C = 0;
            return;
        }
    }
    return;
}
