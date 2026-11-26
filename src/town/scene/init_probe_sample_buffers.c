#include "common.h"
#include "m2c_compat.h"
#include "town/scene.h"
#include "town/data.h"
#include "town/scene/corrected_probe_samples_data.h"
#include "town/scene/secondary_probe_samples_data.h"

extern Vec4i D_800D0208[4];
extern TownProbeSample D_800D0248[4];
extern M2C_UNK D_800D0288;
extern M2C_UNK D_800D02E8;
extern TownProbeSample D_800D0348[6];
extern M2C_UNK D_800D03A8;
extern TownProbeSample *D_800D040C;
extern s32 *town_primary_probe_samples;

/* Initialize six global pointers to their corresponding storage blocks. */
void init_probe_sample_buffers(void) {
    town_corrected_probe_samples = D_800D0208;
    D_800D040C = D_800D0248;
    town_primary_probe_samples = &D_800D0288;
    town_probe_adjustment_samples = &D_800D02E8;
    town_secondary_probe_samples = D_800D0348;
    town_position_entry_samples = &D_800D03A8;
}
