# Experimental original-style build. Production proof remains tools/build/gate_all.py.
.DEFAULT_GOAL := all
MAKEFLAGS += --no-builtin-rules
.SUFFIXES:
.DELETE_ON_ERROR:
.PHONY: all check configure
export TMPDIR := $(CURDIR)/build/.state/tmp
all: images
check: images
	@nice -n 10 python3 tools/build/mkbuild.py check
configure: build/.state/setup.ok
	@nice -n 10 python3 tools/build/mkbuild.py generate
build/.state/setup.ok: $(wildcard tools/gate/*.py tools/gate/*.sh) tools/build/mk_slus_root.sh tools/build/mk_ovl_root.sh tools/build/configure.py tools/source_layout.py config/slus_006.14.yaml config/slus_modules.json config/slus_partitions.json ledger/rows.jsonl ledger/layout.jsonl ledger/layout_inline.jsonl ledger/tu_layout.jsonl
	@nice -n 10 python3 tools/build/mkbuild.py bootstrap
build/build.mk: build/.state/setup.ok tools/build/mkbuild.py
	@nice -n 10 python3 tools/build/mkbuild.py generate
ifeq ($(filter configure,$(MAKECMDGOALS)),)
include build/build.mk
endif

# Decoded code has an independent exact/recompressed image producer.
.PHONY: decoded-images decoded-check
all: decoded-images
check: decoded-images
decoded-check:
	@nice -n 10 python3 tools/decoded_images.py check
decoded-images: build/.state/compiletools.ok
	@nice -n 10 python3 tools/decoded_images.py build
