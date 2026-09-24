# Function-level bridge inventory for historical GP `gp_01`

The historical 20-row `gp_01` graph is partly an artifact of collector-row granularity. References in `code.c` and `code2.c` occur in a small set of named functions, even though the current registry records those collectors with 221 and 32 `defs` entries. This supports evaluating function-level groupings; shared-symbol reachability does not prove a historical retail translation-unit boundary.

## Collector identities and path/hash limits

| Local source | Local SHA-256 | Current registry ID and `c_path` | Registry `defs` | Current split recipe |
|---|---|---|---:|---|
| `src/slus/code.c` | `1c1afc31d56af7f3505ad1a9e54c4c21023aac81b2314ad3581dbeadf1e28b16` | `slus/code` / `src/code.c` | 221 | `2.7.2` |
| `src/slus/code2.c` | `443e6c482c7a5fe6fcf53c5381384618acac6adb06cff6d287aea2386f65c2bb` | `slus/code2` / `src/code2.c` | 32 | `2.8.1` |

The checked-out source files are under `src/slus/`; `ledger/splits/slus.jsonl` and `ledger/rows.jsonl` name logical paths `src/code.c` and `src/code2.c`, neither of which exists at that path in this checkout. The registry row SHA values therefore are reported separately in `inventory.json` from the hashes of the local `src/slus/` files; primary review confirms that both registry hashes exactly match the frozen `raw/slus/` copies. The logical paths are relative to the exported build root. Neither distinction is a historical source-map claim.

## Symbol-to-function map

| GP symbol | Collector source occurrence(s) | Historical `gp_01` row adjacency |
|---|---|---|
| `D_80080B94` | `func_80050CAC` code.c:944; TU extern `code.c:937` | `slus/code` |
| `D_80080B98` | `func_80050CAC` code.c:945; TU extern `code.c:938` | `slus/code`, `slus/w_80050DA8`, `slus/w_80050E20` |
| `D_800814C8` | `func_8003F5D4` code.c:94; `func_8003F5E0` code.c:100 | `slus/code` |
| `D_800814E0` | `func_80041110` code.c:187; `func_80041110` code.c:188; `func_80041110` code.c:189; TU extern `code.c:182`; `func_800410FC` code2.c:51; TU extern `code2.c:47` | `slus/code`, `slus/code2`, `slus/w_80041134` |
| `D_80081540` | `func_8004AE98` code.c:593; TU extern `code.c:585` | `slus/code`, `slus/w_8004B08C` |
| `D_80081550` | `func_8004DCE0` code.c:724 | `slus/code`, `slus/w_8004DCEC`, `slus/w_8004DE88`, `slus/w_8004DF8C` |
| `D_80081554` | `func_8004DDB4` code.c:730 | `slus/code`, `slus/w_8004DCA8`, `slus/w_8004DD2C`, `slus/w_8004DDE4`, `slus/w_8004E130` |
| `D_80081558` | `func_8004DDB4` code.c:731 | `slus/code`, `slus/w_8004DD2C`, `slus/w_8004DDE4`, `slus/w_8004E130` |
| `D_80080B1B` | `func_80048DA0` code2.c:271; TU extern `code2.c:263` | `slus/code2` |
| `D_80080B1C` | `func_80048DA0` code2.c:273; TU extern `code2.c:264` | `slus/code2` |
| `D_800814D0` | `func_8003F240` code2.c:302; TU extern `code2.c:297` | `slus/code2`, `slus/w_8003E34C`, `slus/w_8003E758`, `slus/w_8003F2A4`, `slus/w_8003F368` |

`docs/evidence/fidelity_gp_symbols.tsv` records the same collector source lines for the GP symbol rows. Function association above comes from the local source bodies. Extern declarations are identified separately from function references.

## Current function ownership and grouping constraints

Current `ledger/rows.jsonl` maps the collector functions to `slus/code` (recipe `2.7.2`) or `slus/code2` (recipe `2.8.1`). The same function names also appear in some separately extracted `slus/w_*` rows; all matching row IDs and exact current split recipes are enumerated in `inventory.json`. These are name occurrences in frozen registry `defs`, which also include references; overlap does not establish duplicate emitted definitions. `func_80041134` already has the individual row `slus/w_80041134` at `2.8.1`. No mapped function name appears in `config/slus_modules.json` module membership, so no per-function module recipe override was observed there.

The strongest collector-to-collector bridge is `D_800814E0`: it is referenced by `func_80041110` in `code.c`, `func_800410FC` in `code2.c`, and `func_80041134` in the separate individual source. Other graph edges similarly attach to only the listed function sites: `D_800814D0` ties `func_8003F240` to four extracted rows; `D_80081540/50/54/58` tie functions in `code.c` to nearby extracted rows with mixed recipes. Thus the graph is actionable as candidate function groups without making `code.c` and `code2.c` one mega-TU.

Any follow-up partition must preserve current row identity and provenance for the full collector `defs` lists; moving one function into an existing individual ID without an explicit registry migration would make the current mapping ambiguous. The separate `gp_e0_function_group` receipts cover the three E0 functions as prototype evidence (44 words, exact stock/generic/genuine per the parent’s receipt review), but mark frozen-row registry compatibility false. The subsequent linked receipt also proves a complete private retail-exact image. That physical-link result does not migrate current rows or grant a production ownership certificate.

This inventory uses the historical `gp_remaining38` snapshot only for the `gp_01` component edges and uses the current ledger/split/config for present identities and recipes. It does not claim a complete emitted-function count, reconstructed source ownership, or historical retail TU boundaries. No compile or link was run for this inventory.

Full line occurrences, current registry rows, recipes, hashes, and source-path flags are in [inventory.json](inventory.json).
