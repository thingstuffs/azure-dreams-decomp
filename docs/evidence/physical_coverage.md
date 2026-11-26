# Physical byte coverage

Regenerate the [summary table](physical_coverage.tsv) after changing ownership
records. Supply the linked executable and the GNU linker map from the same
build.

```sh
python3 tools/physical_census.py \
  --slus-map build_slus/build/slus_006.14.map \
  --slus-image build_slus/build/slus_006.14
```

The tool checks each disc container against its recorded size and SHA-1.
For SLUS it checks executable equality, the map's loaded address and extent,
and the bounds and disjointness of its input allocations. Use `--disc-root`
when the extracted inputs are outside the source checkout.

C ownership is the physical union of registered source rows and native
allocations. The program text, module data and explicit alignment use
separate counts. `tools/coverage.py` and `tools/status.py` share the overlay
allocation rules. C placements are a subset of C ownership. Every physical
root contributes its bytes once, including entries inherited through
nested views. Retail imports with recorded hashes and verified zero-fill
have their own classes. The `--json` output adds import and unknown counts
by reason.

The monster-bank transfer class covers pending bytes inside the normal Dungeon
loads. Its extents come from the loader's formula and are pinned by hash; the
entry pointer of each bank (its first word, read from the disc) is checked to
lie inside the load window; review of the receipts is pending. The check
verifies each transfer's sector range, destination and disc hash against the
checked loader record. A missing manifest is an error. For
placement receipts it also checks the recorded loader and resident helper
bytes against the two disc files. The class records the static load path.
Runtime use and the format of data inside the bank remain open.
