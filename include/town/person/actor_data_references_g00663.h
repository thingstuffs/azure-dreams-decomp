#ifndef TOWN_PERSON_ACTOR_DATA_REFERENCES_G00663_H
#define TOWN_PERSON_ACTOR_DATA_REFERENCES_G00663_H
/* Actor data references (G00663). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D58B8. */

#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

typedef struct S_800C6440_2 {
    u8 pad_00[0x4];
    s32 * unk_04;
} S_800C6440_2;

typedef struct S_800C645C_1 {
    u8 pad_00[0x80];
    void * unk_80;
} S_800C645C_1;

/* arg0 in set_linked_data_pointers_variant_2 */
typedef struct S_800C645C_2 {
    u8 pad_00[0x4];
    s32 * unk_04;
} S_800C645C_2;

typedef struct S_800C645C_0 {
    u8 pad_00[0x7C];
    s32 ** unk_7C;
} S_800C645C_0;

typedef struct S_800C6478_0 {
    u8 pad_00[0x80];
    void * unk_80;
} S_800C6478_0;

/* arg0 in set_linked_data_pointer_variant_3 */
typedef struct S_800C6478_1 {
    u8 pad_00[0x4];
    s32 * unk_04;
} S_800C6478_1;

typedef s32 unk32;

typedef struct S_800C648C_0 {
    u8 pad_00[0x7C];
    s32 ** unk_7C;
    void ** unk_80;
} S_800C648C_0;

/* arg0 in check_actor_data_references_match */
typedef struct S_800C648C_1 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_800C648C_1;

/* ((S_800C645C_1 *)arg0)->unk_80 in set_linked_data_pointers_variant_2 */
/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_800D58F4;
/* ((S_800C6478_0 *)arg0)->unk_80 in set_linked_data_pointer_variant_3 */
extern M2C_UNK D_800D5930;

extern M2C_UNK D_800D58B8;
/* Functions defined in this translation unit. */
void set_linked_data_pointers_variant_1(Rec_func_80094268_arg0 *record);
void set_linked_data_pointers_variant_2(S_800C645C_0 *object);
void set_linked_data_pointer_variant_3(S_800C6478_0 *object);
s32 check_actor_data_references_match(S_800C648C_0 *actor);

#endif
