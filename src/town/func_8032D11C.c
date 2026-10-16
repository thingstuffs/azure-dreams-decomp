#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */

extern void townApplySelectedEntryValues(void *, s32);
/* Forward the context and request to townApplySelectedEntryValues. */
void townForwardContextRequestToHandlerD(void *context, s32 request) {
    townApplySelectedEntryValues(context, request);
}
