#include "common.h"
#include "shared/entity.h"

/* 8-byte buffer copied from a global and indexed by a masked byte offset */
typedef struct {
    u8 b[8];
} S_800498A0_Buf8;

extern S_800498A0_Buf8 texture_masked_byte_values[];

/* Copies the global lookup table and returns the byte selected by the low three field bits. */
s32 lookup_masked_byte_table(ActorRecord *actor) {
    S_800498A0_Buf8 lookup_table = texture_masked_byte_values[0];
    return lookup_table.b[actor->flags14 & 7];
}
