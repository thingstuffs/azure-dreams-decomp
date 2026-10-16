#include "common.h"

typedef struct {
    u16 type;
    u16 next;
    u32 source;
    u16 x;
    u16 y;
    s16 flags;
} StreamCommand;


extern void setByteOne(u8 *);
extern s32 Control_CD(s32, void *, void *);
extern u8 *func_8004068C(u8 *, u8 *);
extern void uploadVramRowAndCache(s32, s32, s32, s32);
extern s32 DrawSync(s32);
extern s32 LoadImage(void *, void *);
extern void *memcpy(void *, const void *, u32);
extern s32 D_80081480;
extern s32 D_8008148C;

/* Processes a command stream for VRAM uploads, tile caching, memory copies, and pointer relocation. */
void func_80041588(u32 *stream_ref, u8 *state, s32 execute)
{
    StreamCommand *cmd;
    u8 *base;
    u8 *buffer;
    u8 *data;
    u16 *color;
    u32 *words;
    s32 item_idx;
    s32 color_idx;
    s32 flags;
    
    s32 item_count;
    s32 command_idx;
    s32 src_addr;
    s32 vram_offset;
    s32 tile_count;
    s32 buffer_addr;
    void *tile_src;
    u32 *input;

    input = stream_ref;
    cmd = (StreamCommand *)state;
    if (execute == 0) {
        Control_CD(6, input, 0);
        *(u8 *)cmd = 0;
        Control_CD(0xFF, setByteOne, cmd);
        return;
    }

    base = (u8 *)(*input & 0x7FFFFF);
    cmd = (StreamCommand *)((u32)base | 0x80000000);
    base = (u8 *)cmd;
    DrawSync(0);
    buffer_addr = D_8008148C;
    D_80081480 = buffer_addr;
    buffer = (u8 *)buffer_addr;

    while (1) {
        command_idx = cmd->type - 1;
        words = (u32 *)cmd;
        switch (command_idx) {
        default:
            return;

        case 0:
        func_8004068C(base + words[1], buffer);
        LoadImage(&cmd->x, buffer);
        DrawSync(0);
        if (cmd->next == 0) {
            return;
        }
        cmd = (StreamCommand *)((u8 *)cmd + cmd->next);
        continue;

        case 4:
        LoadImage(&cmd->x, base + words[1]);
        DrawSync(0);
        if (cmd->next == 0) {
            return;
        }
        cmd = (StreamCommand *)((u8 *)cmd + cmd->next);
        continue;

        case 1:
        vram_offset = cmd->x;
        tile_count = cmd->y;
        tile_src = (void *)words[1];
        flags = cmd->flags;
        src_addr = (s32)((void *)((void *)(base + (s32)tile_src)));
        goto call_tile;

        case 5:
        item_count = (u16)cmd->flags;
        vram_offset = cmd->x;
        tile_count = cmd->y;
        tile_src = (void *)words[1];
        item_count |= 2;
        src_addr = (s32)((void *)((void *)(base + (s32)tile_src)));
        goto convert_flags;

        case 6:
        src_addr = (s32)(base + words[1]);
        item_count = (s32)cmd->y << 4;
        data = (u8 *)src_addr;
        color = (u16 *)(data + 2);
        item_idx = 1;
        while (item_idx < item_count) {
            *color |= 0x8000;
            item_idx++;
            color++;
        }
        goto masked_tile;

        case 7:
        src_addr = (s32)(base + words[1]);
        item_count = cmd->y;
        data = (u8 *)src_addr;
        color = (u16 *)data;
        item_idx = 0;
        if (item_count != 0) {
            do {
                color++;
                color_idx = 1;
                do {
                    *color |= 0x8000;
                    color_idx++;
                    color++;
                } while (color_idx < 16);
                item_idx++;
            } while (item_idx < item_count);
        }

    masked_tile:
        item_count = (u16)cmd->flags;
        vram_offset = cmd->x;
        tile_count = cmd->y;
        item_count |= 2;
    convert_flags:
        item_idx = (u32)item_count << 16;
        flags = item_idx >> 16;
    call_tile:
        uploadVramRowAndCache(src_addr, vram_offset, tile_count, flags);
        DrawSync(0);
        goto advance;

        case 2:
        func_8004068C(base + words[1], (u8 *)words[2]);
        if (cmd->next == 0) {
            return;
        }
        cmd = (StreamCommand *)((u8 *)cmd + cmd->next);
        continue;

        case 3:
        memcpy((void *)words[2], base + words[1], words[3]);
        if (cmd->next == 0) {
            return;
        }
        cmd = (StreamCommand *)((u8 *)cmd + cmd->next);
        continue;

        case 8:
        item_idx = cmd->x;
        data = base + words[1];
        if (item_idx > 0) {
            u32 reloc_base = (u32)base | 0x80000000;
            data += 4;
            do {
                *(u32 *)data += reloc_base;
                item_idx--;
                data += 8;
            } while (item_idx > 0);
        }
        }
    advance:
        if (cmd->next == 0) {
            return;
        }
        cmd = (StreamCommand *)((u8 *)cmd + cmd->next);
    }
}
