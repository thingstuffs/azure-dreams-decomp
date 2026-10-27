#ifndef MORE_FRAGMENT_B4F0C_H
#define MORE_FRAGMENT_B4F0C_H
#include "common.h"
#include "dungeon/level.h"
typedef struct { u8 pad24[0x24]; u8 x; u8 y; s8 flag; } FuncArg1;
typedef struct { u8 pad1c[0x1C]; u32 flags; u8 pad20[0x68]; u16 height; } FuncArg2;
extern s16 get_offset_map_cell_value_and_flags(s16 x, s16 y, s16 offset_index, u16 *flags);
s16 check_diagonal_side_height(s32 direction, s16 x, s16 y, s16 height);
struct Node;
extern void * find_eligible_actor_at_tile_and_height(struct Node *node, s32 x, s32 y_in, s16 value);
s32 clearance_word_coords(s32 direction, s32 x, s32 y, s16 height) __asm__("func_8009A540");
s32 terrain_height_words(s32 x, s32 y, s32 height) __asm__("func_800BCB04");
s16 terrain_height_short(s32 x, s32 y, s16 height) __asm__("func_800BCB04");
#endif
