#include "common.h"
#include "m2c_compat.h"
#include "town/scene.h"

extern M2C_UNK D_800D0208;
extern M2C_UNK D_800D0248;
extern M2C_UNK D_800D0288;
extern M2C_UNK D_800D02E8;
extern M2C_UNK D_800D0348;
extern M2C_UNK D_800D03A8;
extern s32 *town_corrected_probe_samples;
extern s32 *D_800D040C;
extern s32 *town_primary_probe_samples;
extern s32 *town_probe_adjustment_samples;
extern s32 *town_secondary_probe_samples;
extern s32 *town_position_entry_samples;

/* Initialize six global pointers to their corresponding storage blocks. */
void initialize_six_global_pointers_corresponding_storage_blocks(void) {
    town_corrected_probe_samples = &D_800D0208;
    D_800D040C = &D_800D0248;
    town_primary_probe_samples = &D_800D0288;
    town_probe_adjustment_samples = &D_800D02E8;
    town_secondary_probe_samples = &D_800D0348;
    town_position_entry_samples = &D_800D03A8;
}
