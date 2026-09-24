# Explicit data pieces: verified build and fidelity integration

The tooling ([landed patch](gp_data_pieces/production/tools.patch)) replaces the
hand-edited CD layout experiment with an explicit module data-piece plan and a
normal generated Ninja build. The private E758 owner links all eight definitions
at their retail addresses. Fresh candidate compilation, the full-image gate and
genuine ASPSX agree on all 698 instruction words with zero masks. Production
sources, module manifest and assembler remain unchanged; the build and
verification tools are now integrated.

## Complete pipeline checks

The [generated module fixture](gp_data_pieces/module_fixture_receipt.json) adds
one experimental E758 owner to the existing 23, replacing its standalone compile
edge while retaining 869 physical / 884 logical rows. It uses the ordinary module
asset carver and generated linker script; there are no hand-edited link slots.
The complete 524,288-byte image matches retail, all eight small-data symbols have
real non-ABS ownership, and all 868 outside C objects remain byte-identical.

The [fresh verifier run](gp_data_pieces/verify_fixture_record.json) exercises the
actual private `compile_slus_units`, singular module candidate gate, traced
assembler self-check and genuine ASPSX 2.79 comparison. Both the member and the
complete emitted owner have exact, unmasked 698-word retail proof. The
[summary](gp_data_pieces/verify_fixture_receipt.json) binds its compiler output
and transformation hashes.

The [generic assembler arm](gp_data_pieces/generic_module_gate_receipt.json)
recompiles only this owner with the existing private corrected assembler, verifies
its transformation receipt and links through generated Ninja. It also matches
the entire retail image. The other 868 objects stay stock and unchanged; this
is not a whole-program generic-assembler transition. Rebuilding the owner with
stock restores its original object and image exactly.

Three [real candidate rejection tests](gp_data_pieces/candidate_gate_receipt.json)
change an initializer, change an instruction, or add unselected global storage.
The first two produce image mismatches; the third fails the data-piece contract.
Every test restores the canonical candidate source, original owner object and
retail image, and recomputes a valid transformation receipt afterward.

## Representation and checks

An optional module `data_pieces` list declares each symbol's source section and
alignment. Existing data records declare its exact extent, initializer bytes,
retail location and named destination section. Every selected datum must be
covered once. Legacy modules retain their original decoded metadata and carve
plans; without opted-in owners, generated Ninja is byte-identical.

The generic ELF transformer preserves every instruction and relocation record.
It retains the original object as `.unsplit.o` and writes a `.data-pieces.json`
receipt. Verification recomputes the transformation from that original and
compares both complete output bytes and the receipt. Only ordinary writable,
allocated MIPS GP small-data sections and explicit GLOBAL definitions are
supported. Ambiguous labels, unsupported section flags/metadata, unowned nonzero
bytes, section-base targets and out-of-span relocation addends are rejected.

Normal linking depends on per-owner verification stamps. A deleted sidecar
invalidates that check and fails the build. Recompilation may replace old
sidecars only after the new unsplit object validates; accidentally applying the
transform twice still fails. Interrupted or tampered artifact sets fail
verification. Candidate compilation, restoration and ownership proof use the
same API.

Genuine objects remain read-only. The fidelity view projects bounded, validated
initializer spans through the manifest plan, rejects uncovered targets instead
of masking them, and requires complete genuine function coverage. Ownership and
placement evidence bind the plan, transformer hash, pre/post object hashes and
whole-owner retail/genuine result. Existing placement criteria are unchanged.

## Validation and remaining work

The [implementation receipt](gp_data_pieces/implementation_receipt.json) records
135 existing regression tests, 30 private feature tests, and eight portable core
tests. The latter cover actual GNU links with nonzero data, GP/HI/LO/32-bit
relocations, NOBITS, malformed inputs, rebuilds, tampering and CLI verification.
The original candidate patch passed `git apply --check` against the pre-integration
code. Those receipts describe preparation; the final integration is recorded below.

The production tooling transaction is complete. All **159 tests** pass: 135
existing checks and 24 portable data-piece checks. Independent review found and
fixed one attribution diagnostic: ablation variants now compare against the
retained raw baseline, so unchanged assembler output is identified correctly.
A fresh [private genuine proof](gp_data_pieces/production/verify_fixture_record.json)
still matches all 698 owner words with zero masks after that fix.

The [integration receipt](gp_data_pieces/production/integration_receipt.json)
records the exact tool hashes, unchanged production inputs and all 869 unchanged
C objects. Generated Ninja remains identical to the pinned recipe; all 884 logical
rows remain present, and the entire executable matches retail. The [fresh ownership
receipt](gp_data_pieces/production/ownership_receipt.json) re-proves all 23 existing
owners. The accepted `t272` epilogue model remains explicitly labelled for
`slus/konami_runtime_w_80033D54`; it is not claimed as direct genuine equality.
Both existing placement certificates were regenerated and checked against the new
tool fingerprints. No data-piece owner or generic assembler transition is active.

The original candidate patch and private receipts above remain the preparation
checkpoint; the production directory records the final implementation and proof.
The [module workflow](../SLUS_MODULES.md#scattered-small-data-pieces) documents the
opt-in contract, sidecar lifecycle and complete-owner proof requirements. The
transform validates selected source sections, not every unrelated data section
in the object; actual storage and the complete image remain separate gates.

The [CD declaration inventory](gp_data_pieces/cd_contract.md) identifies the next
source work: signedness disagreements in byte/halfword state, the eight-byte
SDK result buffer versus F368's four-byte global union, and overlapping padded
address views. These views are not allocation evidence. Reconcile declarations
and measure every affected consumer, including F240 in `code2`, before activating
a CD ownership group or claiming its GP dependencies repaired. The current E758
fixture retains the previous aliases and pins and is a layout proof only.

Production remains **23 owners, 189 dependencies and 21 GP rows**. The prepared
18-function generic transition, self-increment consumers and three documented
MAIN coverage gaps retain their previous status. The goal remains active.

[Reproduction metadata](gp_data_pieces/reproducer.json) records private script
and test hashes. Receipts retained here replace local absolute paths with
placeholders; hashes of private original files refer to their unsanitized bytes.
