# Explicit data pieces: private build and fidelity integration

The [candidate tooling patch](gp_data_pieces/candidate_tools.patch) replaces the
hand-edited CD layout experiment with an explicit module data-piece plan and a
normal generated Ninja build. The private E758 owner links all eight definitions
at their retail addresses. Fresh candidate compilation, the full-image gate and
genuine ASPSX agree on all 698 instruction words with zero masks. Production
sources, module manifest and assembler remain unchanged.

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
The complete patch passes `git apply --check` against the current production
code. These are preparation results, not an activation receipt.

Before landing the tooling, finish portable tests for the manifest, build adapter,
fidelity projection and evidence checks; the corresponding private tests already
pass. Then integrate under the landing lock, run the production gates, refresh
all affected ownership evidence and existing placement certificates, and verify
legacy objects and status. There is no need to change assembler semantics for
this representation step.

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
