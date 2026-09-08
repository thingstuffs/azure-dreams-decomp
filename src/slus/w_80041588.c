#include "common.h"

#ifdef NON_MATCHING
#define TBL_PAGE ((u8 *)jtbl_8002D658)
#define TBL_OFFSET 0
#else
#define TBL_PAGE ((u8 *)0x80030000)
#define TBL_OFFSET (-0x29A8)
#endif

typedef struct {
    u16 type;
    u16 next;
    u32 source;
    u16 x;
    u16 y;
    s16 flags;
} StreamCommand;

typedef struct {
    s32 value;
    s32 pad4;
    s32 pad8;
} LargeWord;

extern void func_8003E140(u8 *);
extern s32 func_8003E4FC(s32, void *, void *);
extern u8 *func_8004068C(u8 *, u8 *);
extern void func_8003F80C(s32, s32, s32, s32);
extern s32 DrawSync(s32);
extern s32 LoadImage(void *, void *);
extern void *memcpy(void *, const void *, u32);
extern LargeWord D_80081480;
extern LargeWord D_8008148C;
extern void *jtbl_8002D658[];

/* Processes a command stream for VRAM uploads, tile caching, memory copies, and pointer relocation. */
void func_80041588(u32 *stream_ref, u8 *state, s32 execute)
{
    StreamCommand *cmd;
    u8 *base;
    u8 *buffer;
    u8 *data;
    u16 *color;
    register u32 *words ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    void **table;
    s32 item_idx;
    s32 color_idx;
    register s32 flags ASM_REG("$7");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    register s32 raw_flags ASM_REG("$3");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    s32 item_count;
    s32 command_idx;
    s32 src_addr;
    s32 vram_offset;
    s32 tile_count;
    s32 buffer_addr;
    register void *tile_src ASM_REG("$4");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    u32 *input;
    static void *const case_labels[] = {
        &&case_1, &&case_2, &&case_3, &&case_4, &&case_5,
        &&case_6, &&case_7, &&case_8, &&case_9
    };

    input = stream_ref;
    cmd = (StreamCommand *)state;
    if (execute == 0) {
        func_8003E4FC(6, input, 0);
        *(u8 *)cmd = 0;
        func_8003E4FC(0xFF, func_8003E140, cmd);
        return;
    }

    base = (u8 *)(*input & 0x7FFFFF);
    cmd = (StreamCommand *)((u32)base | 0x80000000);
    base = (u8 *)cmd;
    DrawSync(0);
    {
        register u8 *table_page ASM_REG("$2") = TBL_PAGE;   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
        ASM_KEEP_NV(table_page);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        buffer_addr = D_8008148C.value;
        ASM_KEEP_NV(buffer_addr);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        table = (void **)(table_page + TBL_OFFSET);
    }
    buffer = (u8 *)buffer_addr;
    D_80081480.value = (s32)buffer;

dispatch:
    command_idx = cmd->type - 1;
    words = (u32 *)cmd;
    if ((u32)command_idx >= 9) {
        goto done;
    }
    goto *table[command_idx];

case_1:
    func_8004068C(base + words[1], buffer);
    LoadImage(&cmd->x, buffer);
    goto sync;

case_2:
    LoadImage(&cmd->x, base + words[1]);
    goto sync;

case_3:
    vram_offset = cmd->x;
    tile_count = cmd->y;
    tile_src = (void *)words[1];
    flags = cmd->flags;
    tile_src = (void *)(base + (s32)tile_src);
    src_addr = (s32)tile_src;
    goto call_tile;

case_4:
    raw_flags = (u16)cmd->flags;
    vram_offset = cmd->x;
    tile_count = cmd->y;
    tile_src = (void *)words[1];
    raw_flags |= 2;
    tile_src = (void *)(base + (s32)tile_src);
    src_addr = (s32)tile_src;
    goto convert_flags;

case_5:
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

case_6:
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
    raw_flags = (u16)cmd->flags;
    vram_offset = cmd->x;
    tile_count = cmd->y;
    raw_flags |= 2;
convert_flags:
    flags = (s16)raw_flags;
    ASM_KEEP(raw_flags);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
call_tile:
    func_8003F80C(src_addr, vram_offset, tile_count, flags);
sync:
    DrawSync(0);
    goto advance;

case_7:
    func_8004068C(base + words[1], (u8 *)words[2]);
    goto advance;

case_8:
    memcpy((void *)words[2], base + words[1], words[3]);
    goto advance;

case_9:
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
advance:
    if (cmd->next == 0) {
        goto done;
    }
    cmd = (StreamCommand *)((u8 *)cmd + cmd->next);
    goto dispatch;
done:
    return;
}
