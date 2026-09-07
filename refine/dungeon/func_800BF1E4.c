#include "common.h"

typedef struct {
    u8 pad0[2];
    u16 count;
    u8 pad4[0x18];
    void *data;
    u8 pad20[8];
    void *meta;
} FuncArg;

typedef struct {
    u8 pad0[2];
    u16 x;
    u8 pad4[2];
    u16 y;
    u8 pad8[2];
    u16 z;
} FuncData;

typedef struct {
    u8 pad0[0x13];
    u8 index;
} FuncMeta;

typedef struct {
    u8 pad0[2];
    u16 field2;
    u8 pad4[8];
    u16 fieldC;
    u16 fieldE;
    u8 pad10[2];
    s16 field12;
    u8 pad14[2];
    u16 field16;
    s16 field18;
    u8 pad1A[2];
    void *field1C;
} FuncSub;

typedef struct {
    u8 pad0[8];
    void *field8;
    u8 padC[4];
    s16 field10;
    u8 pad12[2];
    s16 field14;
} FuncBlock;

typedef struct {
    u8 pad0[8];
    FuncData *data_block;
    FuncBlock *block;
    void *field10;
} FuncItem;

typedef struct {
    u8 pad0[0xA];
    u16 fieldA;
} FuncTable;

extern u8 D_80045340[];
extern u8 D_800DDC40[];
extern u8 D_800C4640[];
extern u8 D_800DF564[];
extern s32 D_800814A0[3];
extern FuncTable D_80083460;

extern s32 rand(void);
extern void *func_8003FC64(s32);
extern s32 func_8004491C(void *, void *);

/* Spawn two effects at the source position and decrement its remaining count. */
void func_800C4944(FuncArg *source) {
    register s32 effect_index ASM_REG("$18");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    FuncSub *effect_state;
    FuncItem *effect_item;
    FuncBlock *effect_block;
    FuncData *effect_pos;
    FuncData *source_pos;
    FuncMeta *source_meta;
    u8 *effect_def;
    u8 *height_offsets;
    u8 *tile_data;
    u16 x;
    u16 y;
    s32 random_values[3];

    random_values[0] = rand();
    random_values[1] = rand();
    random_values[2] = rand();
    effect_index = 1;
    effect_def = D_800C4640;
    height_offsets = D_800DDC40;
    tile_data = D_800DF564;
    loop:
    effect_item = func_8003FC64(0x202);
    if (effect_item != 0) {
        effect_item->field10 = effect_def;
        effect_state = (FuncSub *)((u8 *)effect_item + 0x20);
        func_8004491C(effect_item, D_80045340);
        effect_state->field12 = (random_values[0] & 0xF) + 0x10;
        effect_state->field16 = random_values[1];
        source_pos = (FuncData *)source->data;
        effect_pos = effect_item->data_block;
        x = source_pos->x;
        effect_pos->x = x;
        effect_state->fieldC = x;
        y = ((FuncData *)source->data)->y;
        effect_pos->y = y;
        effect_state->fieldE = y;
        source_meta = (FuncMeta *)source->meta;
        effect_pos->z = ((FuncData *)source->data)->z - *(u8 *)(source_meta->index + (s32)height_offsets) - (random_values[2] & 0xF);
        effect_state->field1C = source->data;
        effect_block = effect_item->block;
        effect_block->field14 = 0xC;
        effect_block->field8 = tile_data;
        if (effect_index != 0) {
            effect_block->field10 = 0x20;
        } else {
            effect_block->field10 = 0x60;
        }
        effect_state->field2 = 8;
        effect_state->field18 = effect_index;
    }
    effect_index -= 1;
    if (effect_index >= 0) {
        goto loop;
    }
    {
        u16 remaining;
        remaining = source->count - 1;
        source->count = remaining;
        if ((remaining << 0x10) <= 0) {
            u16 *source_flags;
            source_flags = (u16 *)source - 1;
            *source_flags = *source_flags | 0x8000;
            D_800814A0[0] = D_800814A0[0] | 0x8000;
            D_80083460.fieldA = D_80083460.fieldA - 1;
        }
    }
}

/* MECHANISM: rowbase TRUE-SPACE row (region xfer_dungeon_A3000, delta 0x7FFE5760,
   true base 0x800C4944).  Three residues, three separate levers:
   1. Retail reloads `source->data` a THIRD time for the z field (word 53, which is
      what fills that load-delay slot); the warm cdk idiom held the first pointer
      live from the x load all the way through z and emitted a nop instead.
      Spelling z as its own `((FuncData *)source->data)->z` deref restores it.
   2. That reload flips gcc's callee-save assignment (source -> $s2, effect_index -> $s3);
      retail is source -> $s3, effect_index -> $s2.  Pinning `effect_index` to $s2 restores
      both roles and every $s2/$s3-bearing word in the function.
   3. `height_offsets[source_meta->index]` is a POINTER-array ref, so gcc canonicalises the address
      add base-first (`addu v0,s5,v0`).  Retail has `addu v0,v0,s5` -- an integer
      addition that keeps source order.  Writing the index first against an
      integer-cast base reproduces it. */
