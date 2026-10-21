#include "common.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_floor.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"

/* Sparse views for fields not covered by the existing record types. */
typedef struct {
    u8 pad_00[0x3716];
    s16 field_3716;
    s16 field_3718;
    s16 field_371A;
} Page8001FieldView_81337E8C;


typedef struct S_8016EE8C_0 {
    u8 pad_00[0xAB];
    s8 unk_AB;
    u8 pad_AC[0x3];
    s8 unk_AF;
} S_8016EE8C_0;

typedef struct S_8016EE8C_1 {
    u8 pad_00[0x296C];
    s32 unk_296C;
} S_8016EE8C_1;   /* page_800e in begin_multi_form_ring_script */

typedef struct S_8016EE8C_2 {
    u8 pad_00[0x3714];
    u16 unk_3714;
    u8 pad_3716[0x6];
    s32 unk_371C;
} S_8016EE8C_2;   /* page_8001 in begin_multi_form_ring_script */


typedef struct S_8016EE8C_4 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_8016EE8C_4;

typedef struct S_8016EE8C_5 {
    u8 pad_00[0xAC];
    s32 unk_AC;
} S_8016EE8C_5;


void unlink_entity_node();                         /* extern */
void create_multi_form_segment_ring();                   /* extern */
extern s32 D_80173C94;
extern s32 D_80173D5C;
extern s32 beldo_actor_nodes;
extern s32 D_80175DC4;
extern s16 beldo_script_timer;

/* Reset shared state and update the two occupied object slots. */
void begin_multi_form_ring_script(void) {
    s32 object_data;
    s32 slot_offset;
    s32 slot_index;
    void *active_data;
    void *page_8001;
    void *page_800e;
    void *object_header;

    slot_index = 0;
    page_8001 = (void *)0x80010000;
    page_800e = (void *)0x800E0000;
    active_data = beldo_actor_nodes + 0x20;
    ((S_8016EE8C_0 *)active_data)->unk_AF = 1;
    (((Page8001FieldView_81337E8C *)page_8001)->field_371A) = 0;
    (((Page8001FieldView_81337E8C *)page_8001)->field_3718) = 0;
    (((Page8001FieldView_81337E8C *)page_8001)->field_3716) = 0;
    g_dungeon_status.active_actor = 0;
    beldo_script_timer = 0;
    ((S_8016EE8C_1 *)page_800e)->unk_296C = (s32) (((S_8016EE8C_1 *)page_800e)->unk_296C | 0x08000000);
    ((S_8016EE8C_2 *)page_8001)->unk_3714 = (u16) ((((S_8016EE8C_2 *)page_8001)->unk_3714 | 9) & 0xFFEF);
    ((S_8016EE8C_2 *)page_8001)->unk_371C = (s32) D_80173C94;
    D_80175DC4 = D_80173D5C;
    ((S_8016EE8C_0 *)active_data)->unk_AB = 0;
    do {
        slot_offset = slot_index * 4;
        object_data = ((S_8016EE8C_5 *)((slot_offset + ((EntityRec *)(((s32 *)&dungeon_actor_ring_anchor)))->x.v)))->unk_AC;
        if (object_data != 0) {
            unlink_entity_node(object_data);
            object_header = ((S_8016EE8C_5 *)((slot_offset + ((EntityRec *)(((s32 *)&dungeon_actor_ring_anchor)))->x.v)))->unk_AC
            - 0x20;
            ((S_8016EE8C_4 *)object_header)->unk_10 = (s32) (((S_8016EE8C_4 *)object_header)->unk_10 | 0x80000000);
        }
        slot_index += 1;
    } while (slot_index < 2);
    create_multi_form_segment_ring(&view_reference_entity.x.v);
}

/* MECHANISM: A 40-byte frame falls out naturally from s0-s3: s2 holds the
   relocatable D_800E3D7C page across calls, while s3 holds 0x80000000.
   Short-lived 0x80010000/0x800E0000 page locals preserve direct displacements
   and avoid the extra address-add/register hold that caused the residue. */
