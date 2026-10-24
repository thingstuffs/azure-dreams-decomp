# Kewne phase boundary in the validation views

The final union identified one failing image among 1,496. The old bank_9c5800 view covered file 9C5800..9CB800 at runtime 8016B000. All explicitly owned entries end before 9CB000. Its final 0x800 imported bytes belong to the independently established next phase: bank_9cb000_run2 begins at file 9CB000 and runtime 80164800.

After registering the complete 480-byte factory at 9CB0B4, normalization also inserted that row in the overlapping older validation window. It projected the entry to 801708B4 instead of its proved 801648B4 and two relocation bytes differed. The same complete factory and next-phase bank already pass their full retail comparison.

The older view now stops at 9CB000. No explicit source entry is removed. The next phase retains its full 0x6000-byte window. Proof must compare the entire 0x5800-byte prefix, the entire next-phase window, and the concatenation of the prefix with the next phase's first 0x800 bytes against the original 0x6000-byte retail slice. No byte is omitted and no instruction is masked. The source rows, C, headers and native executable inputs are unchanged.
