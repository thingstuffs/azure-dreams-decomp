#ifndef SHARED_OT_LINK_H
#define SHARED_OT_LINK_H

/* Ordering-table links through explicit address/tag masks: the getaddr/setaddr/addPrim shape of PsyQ's libgpu, written
 * with the masks held in locals (retail keeps them in registers across loops that have no loop notes).
 * OT_SETADDR(p, OT_GETADDR(ot, m), t, m) masks the address twice - getaddr inside setaddr - exactly as the expansion
 * of `setaddr(p, getaddr(ot))` does; combine folds the second AND (r96: dungeon/func_800CA184, dungeon/func_81910A9C). */
#define OT_GETADDR(p, amask)            (*(u32 *)(p) & (amask))
#define OT_SETADDR(p, a, tmask, amask)  (*(u32 *)(p) = (*(u32 *)(p) & (tmask)) | ((u32)(a) & (amask)))

#endif
