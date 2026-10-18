#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_D_80082D58.h"


typedef struct S_8009ED7C_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_8009ED7C_1;

typedef struct S_8009ED7C_2_pre {
    u16 unk_00;
} S_8009ED7C_2_pre;   /* the 0x2 bytes before arg0 in move_toward_target_finalize_countdown_expires, addressed as arg0[-1] */


M2C_UNK func_80033D08();                      /* extern */
void unlink_scene_list_node();                      /* extern */
void call_the_same_context_both_processing_routines();             /* extern */
void handle_resolve_bounding_box_overlaps_linked_colliders_along_least_penetrating_axis();             /* extern */
void add_motion_deltas_to_position();                      /* extern */
M2C_UNK itm_mon_koyaw_set(); /* extern */
void dispatch_paired_table_values();                            /* extern */
typedef struct {
    s32 words[0x15];
} Record84;
extern Record84 D_80100AF8;
extern s32 D_80100B50[];
extern s32 D_80100B68;

/* Move toward the target and finalize the object when its countdown expires. */
void move_toward_target_finalize_countdown_expires(void *object, s32 context, EntityRec *motion) {
    s32 *target_pos;
    s32 *global_flags;
    u16 ticks_or_flags;

    target_pos = D_80100B50;
    motion->unk_0C = (s32) ((s32) (((S_8009ED7C_1 *)target_pos)->unk_00 - motion->x.v) / 2);
    motion->unk_10 = (s32) ((s32) (((S_8009ED7C_1 *)target_pos)->unk_04 - motion->y.v) / 2);
    motion->flags14 = (s32) ((s32) (((S_8009ED7C_1 *)target_pos)->unk_08 - motion->z.v) / 2);
    add_motion_deltas_to_position(motion);
    call_the_same_context_both_processing_routines(context, motion);
    handle_resolve_bounding_box_overlaps_linked_colliders_along_least_penetrating_axis(context, motion);
    ticks_or_flags = ((Rec_D_80082D58 *)object)->unk_6C.as_u16 - 1;
    ((Rec_D_80082D58 *)object)->unk_6C.as_u16 = ticks_or_flags;
    if ((ticks_or_flags << 0x10) <= 0) {
        itm_mon_koyaw_set(D_80100B68, object + 0x4C, &D_80100AF8, 0);
        unlink_scene_list_node(object);
        func_80033D08(object);
        ticks_or_flags = ((S_8009ED7C_2_pre *)object)[-1].unk_00;
        global_flags = ((s32 *)(&object_flag_block));
        (*(u16 *)((u8 *)object + -2)) = (u16) (ticks_or_flags | 0x8000);
        *global_flags = *global_flags | 0x8000;
        dispatch_paired_table_values();
    }
}
