# Residual collector GP accesses: bounded inventory

This note covers only the post-ready26 residual collector sites named for this
audit: `func_8003F5D4` / `func_8003F5E0` in `code.c`, and
`func_80048DA0` in `code2.c`, plus direct callers of the two accessors. It is
not a full-repair or whole-source ownership claim. The supplied bridge report
documents historical `gp_01` row connectivity; its edges are not treated as a
current component. Current local source hashes match the bridge inventory's
local `code.c` and `code2.c` hashes.

## Symbols and asset bytes

| Symbol and C view | Source access | Asset `54240.bin` view |
|---|---|---|
| `D_800814C8` — `extern int` in `include/globals.h:9`; direct use in `code.c` | `func_8003F5D4` reads/returns it (`code.c:92–95`); `func_8003F5E0` stores its argument (`98–100`). | Address `0x800814C8`, mapped file interval `0xA88–0xA8C`; four bytes `00000000`. |
| `D_80080B18` — `extern u8[16]` in `code2.c:262` | `func_80048DA0` assigns it to a byte pointer and returns `table[index]` without a local bounds check (`267–275`). | Address `0x80080B18`, declared span `0xD8–0xE8`; bytes `00 02 05 00 00 00 00 00 00 01 03 03 02 02 02 02`. |
| `D_80080B1B` — `extern u8` in `code2.c:263` | Written as `count + 5` (`271`). | Address `0x80080B1B`, asset offset `0xDB`, initial byte `00`; this is byte 3 within the declared D_80080B18 span. |
| `D_80080B1C` — `extern u8` in `code2.c:264` | Written as `count * 2 + 5` (`273`). | Address `0x80080B1C`, asset offset `0xDC`, initial byte `00`; this is byte 4 within the declared D_80080B18 span. |

The byte view above is taken directly from the selected asset. The declared
array and scalar names overlap by address; this records C declaration and
asset-byte facts, not separate retail allocation extents or historical TU
boundaries. This bounded audit did not inspect target ELF sections or prove the
asset's ownership or section class.

## Current source and caller context

The current logical registry rows are `slus/code` (`src/code.c`, 221
registered `defs`, recipe `2.7.2` with default flags) and `slus/code2`
(`src/code2.c`, 32 registered `defs`, recipe `2.8.1` with default flags).
Registered `defs` counts include references and are not emitted-function
counts. In the checkout the corresponding local files are `src/slus/code.c`
and `src/slus/code2.c`; the bridge inventory records the registry source hashes
separately from those local hashes.

`D_800814C8` occurs as a direct global access only in the two `code.c`
functions within the scoped source search. Their current direct function
callers are:

| Caller row | Observed call | Current recipe |
|---|---|---|
| `slus/w_8004425C` | `func_8004425C` calls setter `func_8003F5E0` with `((s32 *)&D_80081480)[3]` (`w_8004425C.c:45–46, 87`). | `2.7.2`, default flags. |
| `slus/w_8004450C` | `func_8004450C` calls setter with `D_8008148C_alias2.field_0` (`w_8004450C.c:25–27, 47`). | `2.7.2`, default flags. |
| `slus/w_800558FC` | `func_800558FC` calls getter and stores its result into one of several globals (`w_800558FC.c:5, 12, 16 onward`). | `2.7.2-cdk -G0`. |

The first two caller rows use the same recipe as `code.c` and form observed
call-graph links to the setter; they do not themselves name or access
`D_800814C8`. The getter caller has a different recipe. These are grouping
facts for review, not a module-membership recommendation. In the current row
ledger, names such as `func_8003F5E0` also appear in caller-row `defs`; the
bridge report cautions that such lists include references and do not establish
duplicate emitted bodies.

`func_80048DA0` is the only `src/slus` textual occurrence of its name found by
the bounded direct-caller scan. Its table and counter references are confined
to that function and its declarations in `code2.c`. No existing whole-row
caller/partner for this function was identified in the inspected current
source. Its `table[index]` read has no local bounds check, so valid-index range
is not established here.

The current `config/slus_modules.json` has 23 modules and contains none of the
target function or symbol names. The companion bridge JSON's earlier
`config_check.module_count` is 19; the direct current-config check is the
count reported here. Its historical `gp_01` component membership is not used
as current module membership.

## Existing collector/module workflow facts

`docs/SLUS_MODULES.md` describes modules as one physical aggregator while
keeping canonical row fragments and logical row IDs. The manifest validator in
`tools/build/slus_modules.py` requires a nonempty member list, unique member
row/source/object stems and functions, and a single module recipe. It expands a
physical module edge back into per-row logical edges. `load_manifest` also
requires each member ID to match its source stem.

`tools/build/slus_partitions.py` supports explicit function-level partitions
of a collector parent: the plan names its canonical logical row/source, frozen
raw-source hash, original recipe and full function set; each part assigns a
nonoverlapping subset to a named destination module. It renders a remainder
and function-only fragments, checks exact emitted-function coverage, and
projects the generated remainder back to the original logical row. It refuses
an empty remainder. `validate_context` prevents the partition parent from
also being a module aggregator or whole-row module member, and prevents a
function from being owned both ways.

Under those observed validators, a collector-only partition destination still
needs a destination module in the module manifest, and that module currently
needs at least one whole-row member. For the `code.c` setter, the two caller
rows above are recipe-aligned rows to review as possible anchors if primary
evidence supports a larger context; adjacency or call references alone do not
settle that choice. No comparable direct-call row was found for the `code2.c`
table accessor. Do not attach unrelated rows just to satisfy the current
manifest shape. The logical `src/code.c` / `src/code2.c` paths also differ from
the local `src/slus/code.c` / `src/slus/code2.c` paths, as documented in the
bridge report; a partition plan's source-path resolution must respect the
build-root mapping.

## Targeted follow-up for primary review

1. Decide whether the accessor caller rows are a source-evidenced context for
   any `code.c` function partition; the setter callers share the current
   `2.7.2` recipe, while the getter caller uses `2.7.2-cdk -G0`.
2. For `func_80048DA0`, first establish whether any source-supported
   whole-row partner exists; this bounded scan found none. A pure collector
   owner would require changing or extending the current module/member workflow
   rather than inventing an unrelated member row.
3. Keep data proof separate from these declaration facts: review the actual
   object section/binding/relocation data and selected storage contract before
   claiming ownership. The asset bytes alone establish neither.

No compile, production edit, ELF inspection, or historical source-map claim was
made for this inventory.
