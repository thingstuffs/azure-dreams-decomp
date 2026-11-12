#include "common.h"
#include "engine/runtime.h"
#include "engine/scene/cd_cohort_types.h"
#include "sdk/libcd.h"

/* Increment both retry counters, resetting counter1 and initializing the CD when counter1 reaches 0x401. */
void cd_inc_retry_counters(void)
{
    cd_driver_prefix[0].counter2++;
    cd_driver_prefix[0].counter1++;
    if (cd_driver_prefix[0].counter1 >= 0x401) {
        cd_driver_prefix[0].counter1 = 0;
        CdInit();
    }
}
