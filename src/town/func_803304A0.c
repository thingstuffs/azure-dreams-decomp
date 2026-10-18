#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"


typedef struct S_8001ACA0_4 {
    u8 pad_00[0x8];
    void * unk_08;
} S_8001ACA0_4;   /* ((S_8001ACA0_3 *)(((Rec_D_80016000 *)D_80016000)->unk_24))->unk_68 in copy_current_record_components_3 */


typedef struct S_8001ACA0_0 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
} S_8001ACA0_0;   /* arg0 in copy_current_record_components_3 */



/* Copy three 16-bit components from the current nested record to the output. */
void copy_current_record_components_3(S_8001ACA0_0 *components) {
    MovingPosition *source_record;

    source_record = ((S_8001ACA0_4 *)(((TownResourceLinks *)D_80016000->unk_24)->unk_68))->unk_08;
    components->unk_00 = (u16) source_record->unk_02;
    components->unk_02 = (u16) source_record->unk_06;
    components->unk_04 = (u16) source_record->unk_0A;
}
