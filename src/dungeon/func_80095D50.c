#include "shared/game_work.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef struct Rec
{
    u8 pad[0x5c];
    u8 *next;
}
Rec;
extern s32 func_8009A350(s16 x, s16 y, s16 offset_index, u16 *flags);
extern s32 func_800A41F0(u8 *);
/* Finds an eligible entry at the requested coordinates after checking the tile to the left. */
void *func_8009B4B0(u8 *entry, s16 x, s16 y)
{
    u16 tile_flags;
    u8 *list_head;
    u16 tile_x;
    u16 tile_y;
    tile_x = x;
    tile_y = y;
    list_head = entry;
    if (((func_8009A350((s16) (tile_x - 1), y, 0, &tile_flags) << 0x10) == 0) || ((tile_flags & 0x3300) != 0)) {
        entry = ((Rec *) entry)->next + 0x20;
        if (entry != list_head) {
            do {
                u8 *entry_data = *((u8 **) (entry - 0x14));
                if ((((*((u8 *) (entry_data + 0x24))) == tile_x) && ((*((u8 *) (entry_data + 0x25))) == tile_y))
                    && ((func_800A41F0(entry) << 0x10) != 0)) {
                    return entry;
                }
                entry = ((Rec *) entry)->next + 0x20;
            }
            while (entry != list_head);
        }
    }
    return 0;
}
