# Completed private six-version census

The [evidence packet](CENSUS_EVIDENCE.md), [scoped tables](census_report/tables.md),
and [summary](census_report/summary.json) record the final 57-file GP proposal.
All 6,767 registered rows pass the pipeline/scorer comparison and trace self-check;
6,600 match a common genuine ASPSX version and 167 retain differences. Compared
with the live ledger's 189 dependencies, 22 identities leave and none enter.
These are private candidate counts, not an installed production ledger.

The retail comparator masks 872 words across 302 overlay rows. Its zero unmasked
differences do not prove those masked bytes; SLUS has zero masks, and the separate
full SLUS image and 2,175 active overlay-window gates provide byte comparisons.
The 22 parked movie rows are included in the registered census, not the active
overlay gate. Three unregistered MAIN routines are outside this census.

The original full run preserves two source-contract failures. Both canonical
source repairs were remeasured separately; the reconciled journal replaces exactly
those records with explicit old/new provenance. Neither the original journal nor
the original failures were overwritten.

The [code remainder probe](code_metadata_probe/receipt.json) distinguishes extern
metadata enabling a store scheduling pass from GP-relative addressing: stripping
extern directives and disabling the scheduling pass produce identical listings
and objects, with zero GPREL relocations in all three arms. No external-GP rows
remain detected. The sink pass fires nowhere; its separate removal proposal still
requires its own gates and owner sign-off.

## Archive and replay

[archive.json](archive.json) records original source hashes, archived content
hashes, and compressed-file hashes separately. Text paths are scrubbed to `<repo>`
and `<reference-repo>`; receipt hashes describing original inputs remain unchanged.
The large original and reconciled journals are deterministic gzip files. Read
them with `gzip -dc`; do not recursively search decompressed journals.

For reproduction, restore these scripts and artifacts at their recorded
`work/native_lane/gp_partition_only_tools/` paths in a fresh workspace, expand
the path placeholders, decompress journals, and restore the separately archived
transition/source-review inputs. Follow `CENSUS_EVIDENCE.md`; scripts refuse to
overwrite the original experiment directories. Local historical compilers,
genuine ASPSX binaries, retail inputs and preceding fixtures remain prerequisites.
The archive is evidence, not a self-contained toolchain distribution. Do not
install private census keys into the production ledger; production needs a fresh
census after cache and source activation.

## Registered-row comparison scope

The [dependency-import follow-up](../dependency_projection/README.md) records one
data-only row and two objects whose extra inline helper has no symbol in the
linked image. Those helpers are not directly retail-compared. The 6,767 count is
registered rows, not a count of directly compared retail functions. The follow-up
also archives the 167-row private ledger projection and provenance refusal checks;
it does not install the private census or alter the reviewed transition.
