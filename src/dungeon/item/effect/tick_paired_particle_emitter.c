#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity_height_offsets.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"

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

extern u8 D_800C4640[];
extern u8 D_800DF564[];

extern s32 rand(void);
extern s32 register_node(void *, void *);

/* Spawn two effects at the source position and decrement its remaining count. */
void tick_paired_particle_emitter(FuncArg *source) {
    s32 effect_index;
    FuncSub *effect_state;
    ObjectNodeHeader *effect_item;
    SpriteFrameState *effect_block;
    ObjectPosition *effect_pos;
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
    height_offsets = entity_height_offsets;
    tile_data = D_800DF564;
    do {
        effect_item = allocate_flagged_object_node(0x202);
        if (effect_item != 0) {
            effect_item->update_callback = effect_def;
            effect_state = (FuncSub *)((u8 *)effect_item + 0x20);
            register_node(effect_item, project_sprite_chain);
            effect_state->field12 = (random_values[0] & 0xF) + 0x10;
            effect_state->field16 = random_values[1];
            source_pos = (FuncData *)source->data;
            effect_pos = effect_item->position;
            x = source_pos->x;
            effect_pos->x.w.i = x;
            effect_state->fieldC = x;
            y = ((FuncData *)source->data)->y;
            effect_pos->y.w.i = y;
            effect_state->fieldE = y;
            source_meta = (FuncMeta *)source->meta;
            effect_pos->z.w.i = ((FuncData *)source->data)->z - *(u8 *)(source_meta->index + (s32)height_offsets)
                - (random_values[2] & 0xF);
            effect_state->field1C = source->data;
            effect_block = effect_item->sprite;
            effect_block->flags = 0xC;
            effect_block->source = tile_data;
            if (effect_index != 0) {
                effect_block->tpage_abr = 0x20;
            } else {
                effect_block->tpage_abr = 0x60;
            }
            effect_state->field2 = 8;
            effect_state->field18 = effect_index;
        }
        effect_index -= 1;
    } while (effect_index >= 0);
    {
        u16 remaining;
        remaining = source->count - 1;
        source->count = remaining;
        if ((remaining << 0x10) <= 0) {
            u16 *source_flags;
            source_flags = (u16 *)source - 1;
            *source_flags = *source_flags | 0x8000;
            object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
            g_dungeon_status.activity_counts.parts.pending_action_count = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1;
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
