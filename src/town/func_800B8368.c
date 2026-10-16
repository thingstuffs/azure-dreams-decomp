#include "common.h"
#include "m2c_compat.h"

void *townLayoutThreeDisplayElements(s32, void *, s32);                            /* extern */
void townBuildDisplayEntryString();                /* extern */
void townFormatAndDisplayEntityStats();                /* extern */
void townPopulateDisplayRows();                /* extern */

/* Run four setup routines with the supplied context and data. */
void townInitializeDisplayEntry(s32 context, void * data, s32 value) {
    townLayoutThreeDisplayElements(context, data, value);
    townBuildDisplayEntryString(context, data);
    townFormatAndDisplayEntityStats(context, data);
    townPopulateDisplayRows(context, data);
}
