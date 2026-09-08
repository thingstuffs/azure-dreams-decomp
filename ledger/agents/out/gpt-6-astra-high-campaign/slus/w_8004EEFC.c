#include "common.h"

/* Template struct copied wholesale (word-by-word) into a1's target. */
typedef struct S_8002E5D8 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} S_8002E5D8;

/* Template struct copied wholesale (word-by-word) into a2's target. */
typedef struct S_8002E5E8 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} S_8002E5E8;

extern S_8002E5D8 D_8002E5D8;
extern S_8002E5E8 D_8002E5E8;

/* The live entity struct that a1 points at: same 16 bytes as S_8002E5D8's
   template, but the tail word(s) are reinterpreted/patched as smaller
   fields right after the template copy. */
typedef struct {
    s32 unk0;
    s32 unk4;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    u8 unkE;
    u8 unkF;
} S_8004EEFC_a1;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} S_8004EEFC_a2;

typedef struct {
    s32 unk0;
    S_8004EEFC_a1 *unk4;
    S_8004EEFC_a2 *unk8;
} S_8004EEFC_a0;

/* Copy two templates into entity buffers, link them to the header, and apply defaults. */
void func_8004EEFC(S_8004EEFC_a0 *entity, S_8002E5D8 *main_data, S_8004EEFC_a2 *aux_data) {
    S_8002E5D8 *main_template = &D_8002E5D8;
    S_8002E5E8 *aux_template = &D_8002E5E8;
    s32 *aux_first_word;

    main_data->unk0 = main_template->unk0;
    aux_first_word = &aux_template->unk0;
    main_data->unk4 = main_template->unk4;
    main_data->unk8 = main_template->unk8;
    main_data->unkC = main_template->unkC;

    ((S_8002E5E8 *)aux_data)->unk0 = *aux_first_word;
    ((S_8002E5E8 *)aux_data)->unk4 = aux_template->unk4;
    ((S_8002E5E8 *)aux_data)->unk8 = aux_template->unk8;

    entity->unk4 = (S_8004EEFC_a1 *)main_data;
    entity->unk8 = aux_data;
    entity->unk0 = 0;

    entity->unk4->unk8 = -0xA0;
    entity->unk4->unkA = -0x78;
    entity->unk4->unkC = 0x200;
    entity->unk4->unkF = 4;
}
