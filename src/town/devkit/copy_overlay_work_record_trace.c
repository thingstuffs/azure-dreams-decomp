#include "common.h"
#include "town/devkit.h"
#include "town/data.h"

/* Overlay work diagnostics in the scene-test image linked at zero.
 * The trace also appears in the devkit image linked at 0x80700000. */

extern OvWork D_000045F8;            /* ov_work */
extern char D_000034D0[];            /* Label and integer format. */
extern char D_000034DC[];            /* Label for the source kind. */
extern char D_000034E4[];            /* Label for the copied kind. */
extern char D_000034F4[];            /* Format for a source-location trace. */
extern char D_00003508[];            /* Source filename for the trace. */

/* Copy the overlay work record, trace both kind fields, log the source location and flush the trace. */
void copy_overlay_work_record_trace(OvWork *p) {
    D_000045F8 = *p;
    overlay_trace_methods->print(D_000034D0, D_000034DC, p->kind);
    overlay_trace_methods->print(D_000034D0, D_000034E4, D_000045F8.kind);
    overlay_trace_methods->print(D_000034F4, D_00003508, 47);
    overlay_trace_methods->flush(0);
}
