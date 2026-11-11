# Experimental original-style build. Production proof remains tools/build/gate_all.py.
.DEFAULT_GOAL := all
MAKEFLAGS += --no-builtin-rules
.SUFFIXES:
.DELETE_ON_ERROR:
.PHONY: all check configure
export TMPDIR := $(CURDIR)/build/.state/tmp
# Serial phases run at nice 10 at least. A caller that is already niced (the landing and lanes run make at nice 10)
# keeps its own priority: stacking another 10 put configure and check at 19, below the lanes they wait for. Never
# raises priority above the caller's.
NICE := nice -n $(shell n=$$(nice); if [ "$$n" -ge 10 ] 2>/dev/null; then echo 0; else echo $$((10 - n)); fi)
all: images
check: images
	@$(NICE) python3 tools/build/mkbuild.py check
configure: build/.state/setup.ok
	@$(NICE) python3 tools/build/mkbuild.py generate
# layout_inline.jsonl is not a prerequisite: every batch rewrites its source-derived extents, which bootstrap does not
# read, and generate (configure and the build.mk remake rule) runs bootstrap first, which rebuilds the views when its
# structure changes.
build/.state/setup.ok: $(wildcard tools/gate/*.py tools/gate/*.sh) tools/build/mk_slus_root.sh tools/build/mk_ovl_root.sh tools/build/configure.py tools/source_layout.py config/slus_006.14.yaml config/slus_modules.json config/slus_partitions.json ledger/rows.jsonl ledger/layout.jsonl ledger/tu_layout.jsonl
	@$(NICE) python3 tools/build/mkbuild.py bootstrap
build/build.mk: build/.state/setup.ok tools/build/mkbuild.py
	@$(NICE) python3 tools/build/mkbuild.py generate
ifeq ($(filter configure,$(MAKECMDGOALS)),)
include build/build.mk
endif

# Decoded code has an independent exact/recompressed image producer.
.PHONY: decoded-images decoded-check
all: decoded-images
check: decoded-images
decoded-check:
	@$(NICE) python3 tools/decoded_images.py check
decoded-images: build/.state/compiletools.ok
	@$(NICE) python3 tools/decoded_images.py build
