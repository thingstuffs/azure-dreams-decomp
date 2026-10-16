#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */

extern void townProcessCheckedEntry(void *, s32);
/* Forward the context and request to townProcessCheckedEntry. */
void townForwardContextRequestToHandlerC68(void *context, s32 request) {
    townProcessCheckedEntry(context, request);
}
