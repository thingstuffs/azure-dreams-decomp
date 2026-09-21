## NEW TODAY (2026-09-21): recovered INLINE HELPERS with narrow interfaces

An astra lane took `dungeon/func_809A38E4` from 37 pins to 2 with one move: eight repeated `center + ((radius * trig) >> 8)`
expressions became calls to `static __inline__ s16 project_ring_coordinate(s32 radius, s32 trig, u16 center)` assigned to
int locals (work/native_lane/r64_astra_loop/REPORT.md). The inlined helper's narrow parameter and return conversions are
real insns while `loop.c` runs (they kept that loop above the size at which a constant would be hoisted) and vanish in later
passes. Where a row repeats one expression shape several times next to its pins - or carries runs of `ASM_USE*`/keeps that
look like padding - consider that the original had a small static inline helper (or macro) with `short`/`u8` parameters or a
narrow return, and measure it (`cc1 -dL` prints each loop's "real insns" and the movables it moved).
