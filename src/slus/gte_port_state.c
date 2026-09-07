/* Reference storage TU for the portable GTE register file.
 *
 * The gte_* port arm in include/common.h implements the GTE ops over ONE shared
 * register file, `g_gte`, declared `extern` in the header so that every TU sees
 * the same machine state (the control registers are written by libgte calls in
 * other TUs -- SetRotMatrix/SetTransMatrix/SetGeomOffset/... -- and read by the
 * ops here).  Exactly one TU must define the storage, by defining
 * GTE_PORT_STATE_OWNER before including common.h.
 *
 * Lives in src/ so build_nm.ninja links it (g_gte must resolve once a gte_*
 * row lands).  Under the byte-exact build the whole portable block is #ifdef
 * NON_MATCHING, so this TU compiles to an EMPTY object and the sha1 gate below
 * proves it contributes nothing to the matching link (verified at landing,
 * 2026-08-04).
 */
#define GTE_PORT_STATE_OWNER
#include "common.h"
