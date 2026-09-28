# Type consolidation tools (round 78, docs/TYPE_CONSOLIDATION.md)

Run from a LANE COPY, not in place: the drivers treat `Path(__file__).parent.parent` as their lane directory
(outputs, candidates and census go there). To start a new consolidation lane:

    mkdir -p work/native_lane/<lane> && cp -r tools/consolidate work/native_lane/<lane>/tools \
      && cp -r tools/consolidate/objects work/native_lane/<lane>/objects

| file | role |
|---|---|
| consolidate.py | rewrite a row onto a shared object: `S[k]`, scalar `S`, `*S`, `&S`, local view-typedef members -> fields (`emit_field`); m2c's `u8 *s = &var; ((V *)s)->m` idiom -> direct or typed access (`rewrite_pointers`); data-declared code addresses -> the function name (`rewrite_funcaddr`) |
| layout.py | field layout from an access census (widths, signedness from lh/lhu, union sites) |
| drive3.py | several objects' rewrites in one text, verified once per plan (fold first, then plain) |
| drive_ptr.py | the pointer-fold driver |
| pins2.py | erase each pin alone and all together on migrated text (pin effect check) |
| objects/<var>.json | one spec per object: address, size, type, field names with evidence |

Landing: an `apply*.sh` in the lane (see work/native_lane/r78_types_pilot/apply3.sh): land.lock, sha check,
refuses pin/scaffolding growth, verify.py every row, gate_all (isolated build_ovl_gate) + SLUS SHA-1, restores
everything on any failure, resumable. Land a cross-binary sample first.
