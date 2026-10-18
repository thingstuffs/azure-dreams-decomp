# Physical byte maps and placement views

Decision 60b, LL6 on B13. Each `config/link/<container>/<image>.json` has a complete
counterpart in `link/<container>/<image>.tsv`; large images have numbered TSV parts.
All 443 exported load/link views, the 54 town modules and 37 leftover slices are
mapped. The compact files expand to `azure-clean.linklist.v1`. They preserve every
original TU object, geometry, layout tag and symbol map. `config/link/` remains the
compilation catalogue. The rollout requires identical placement indices and
rebinding tables; it creates no new compiled C.

The five IDs in `physical_roots.json` tile 50,952,192 physical bytes. Other maps
are overlapping views. Only physical-root rows in generated `coverage.tsv` may be
summed. The checker compares each view's labels at every boundary with those roots.

Regenerate from committed code/configuration plus a user-owned US disc BIN/ISO:

```sh
python3 tools/census/regenerate.py --disc /path/to/Azure_Dreams.bin \
  --output /tmp/azure-census --check
python3 tools/byte_map.py check --catalogue link \
  --physical-roots link/physical_roots.json --complete-containers
```

The first command needs no existing lane files, extracted containers or detector
cache. It runs the census, writes regenerated maps to the temporary output and
compares the exact file set and every byte to git. `diff empty` is success.
`tools/census/` contains the implementation/tests; `config/census/` contains its
small checked inputs and rule registry. Each metadata row cites a committed rule
ID such as `census:format:vab` or `census:noncode:decode`. See `docs/LINK_LISTS.md`
for the fixed TSV columns, part/profile encoding, full commands and precedence.
Adjacent equal metadata rules are merged; new asset extents are rehashed. No file
exceeds 2 MB. The files contain metadata and hashes, never retail payloads.

All seven census labels survive: proven code, library code, strongly code, proven
data, terminal non-code awaiting typing, padding/leftover, and unknown. Strongly
code remains separate from registered C. Terminal non-code is not a hold. Unknown
remains explicit, including inside development leftovers. The accepted 69 bounded
reads and three strict prefixes pass the original source/extent/hash checks;
541 stale historical proposals remain excluded. Census-owned partial instances
and SLUS linked extents retain their labels without creating C placements.

`leftovers/` preserves bounded development-slice hashes and structure audits.
Recovered code keeps its census label; coverage separately excludes leftover code
from game-code totals. Optional NPC/shop descriptor bounds and two exact slice
occurrences each are proved. Complete twin allocations, shared compiled TUs,
four shop placements and runtime non-loading remain bounded evidence holds.
