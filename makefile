#PLUGINS+=plugins/branch_count.c
#PLUGINS+=plugins/soft_div.c
#PLUGINS+=plugins/tb_count.c
#PLUGINS+=plugins/mtrace.c plugins/mtrace.S
#PLUGINS+=plugins/cachesim/cachesim.c plugins/cachesim/cachesim.S plugins/cachesim/cachesim_model.c
#PLUGINS+=plugins/poc_log_returns.c
#PLUGINS+=plugins/instruction_mix.c
#PLUGINS+=plugins/strace.c
#PLUGINS+=plugins/symbol_example.c
#PLUGINS+=plugins/memcheck/memcheck.S plugins/memcheck/memcheck.c plugins/memcheck/naive_stdlib.c
#PLUGINS+=plugins/follow_exec.c

# OPTS= -DDBM_LINK_UNCOND_IMM
# OPTS+=-DDBM_INLINE_UNCOND_IMM
# OPTS+=-DDBM_LINK_COND_IMM
# OPTS+=-DDBM_LINK_CBZ
# OPTS+=-DDBM_LINK_TBZ
# OPTS+=-DDBM_TB_DIRECT #-DFAST_BT
# OPTS+=-DLINK_BX_ALT
# OPTS+=-DDBM_INLINE_HASH
# OPTS+=-DDBM_TRACES #-DTB_AS_TRACE_HEAD #-DBLXI_AS_TRACE_HEAD
#OPTS+=-DCC_HUGETLB -DMETADATA_HUGETLB


VERSION?=$(shell git describe --abbrev=8 --dirty --always || echo '\<nogit\>')
CFLAGS+=-D_GNU_SOURCE -g -std=gnu99 -O0 -Wunused-variable 
CFLAGS+=-DVERSION=\"$(VERSION)\"

COMP=GCC
ifeq ($(findstring clang, $(CC)), clang)
	COMP=CLANG
endif


ifdef ($(MORELLO))
	COMP=CLANG

endif

ELF_PATCH=morello_elf
MUSL_LIB=../../morello-aarch64/morello/musl-bin/lib/

ifeq ($(MORELLO), pure-linux-mieshim)
	CFLAGS+=-mabi=purecap -c -nostdinc -isystem ../../morello-aarch64/morello/musl-bin/include/ -ferror-limit=10 
	CFLAGS+= --target=aarch64-linux-gnu  -march=morello+c64 -I/home/sysadmin/moate/libelf/include 
endif	


ifeq ($(MORELLO), pure-freebsd)
	CFLAGS+=-DMORELLOBSD -D_BSD_SOURCE -v
	CFLAGS+=-mabi=purecap -femulated-tls --sysroot=$(CHERIOUTPUT)/rootfs-morello-purecap -ferror-limit=10 -Wcheri-provenance
	CFLAGS+=-B $(CHERIOUTPUT)/morello-sdk/bin/ -mcpu=rainier  -target aarch64-unknown-freebsd13  -march=morello+c64 
endif	

#ifeq ($(COMP), CLANG)
#	CFLAGS+=-no-integrated-as
#endif


LDFLAGS+=-static -ldl
LIBS=-lelf -lpthread -lz
HEADERS=*.h makefile
ifeq ($(MORELLO), pure-freebsd)
	INCLUDES=-I$(FREEBSD) -I$(CHERIOUTPUT)/rootfs-morello-purecap/usr/include/cheri/ -I. 
	INCLUDES+=/home/sysadmin/moate/zlib-1.2.13/install/include
else ifeq ($(MORELLO), pure-linux-mieshim)
	INCLUDES=-I/home/sysadmin/moate/libelf/lib/ /home/sysadmin/moate/libelf/include
else
	INCLUDES=-I/usr/include/libelf -I.
endif

SOURCES= common.c dbm.c traces.c syscalls.c dispatcher.c signals.c util.S
SOURCES+=api/helpers.c api/plugin_support.c api/branch_decoder_support.c api/load_store.c api/internal.c api/hash_table.c
SOURCES+=elf/elf_loader.o elf/symbol_parser.o

#HEADERS += api/emit_a64c.h
#LDFLAGS += -Wl,--image-base=$(or $(TEXT_SEGMENT),0x600000)
#PIE += pie/pie-a64c-field-decoder.o pie/pie-a64c-encoder.o pie/pie-a64c-decoder.o
#SOURCES += arch/aarch64c/dispatcher_aarch64c.S arch/aarch64c/dispatcher_aarch64c.c
#SOURCES += arch/aarch64c/scanner_a64c.c
#SOURCES += api/emit_a64c.c

ARCH=$(shell $(CC) -dumpmachine | awk -F '-' '{print $$1}')
ifeq ($(MORELLO), pure-linux-mieshim)
	HEADERS += api/emit_a64c.h 
	LDFLAGS += -Wl,--image-base=$(or $(TEXT_SEGMENT),0x7000000000)
	LDFLAGS += -fuse-ld=lld $(MUSL_LIB)/crt1.o $(MUSL_LIB)/crti.o $(CLANG_RESOURCE_DIR)/lib/linux/clang_rt.crtbegin-morello.o -I /home/sysadmin/moate/libelf/include
	LDFLAGS += $(CLANG_RESOURCE_DIR)/lib/linux/libclang_rt.builtins-morello.a 
    LDFLAGS += $(CLANG_RESOURCE_DIR)/lib/linux/clang_rt.crtend-morello.o $(MUSL_LIB)/crtn.o -nostdlib -L$(MUSL_LIB) -lc
	LDFLAGS += /home/sysadmin/moate/zlib-1.2.13/install/lib/libz.a
	PIE += pie/pregenerated/pie-a64c-field-decoder.o pie/pregenerated/pie-a64c-encoder.o pie/pregenerated/pie-a64c-decoder.o
	SOURCES += arch/aarch64c/dispatcher_aarch64c.S arch/aarch64c/dispatcher_aarch64c.c
	SOURCES += arch/aarch64c/scanner_a64c.c
	SOURCES += api/emit_a64c.c
else ifdef $(MORELLO)
	HEADERS += api/emit_a64c.h
	LDFLAGS += -Wl,--image-base=$(or $(TEXT_SEGMENT),0x7000000000)
	PIE += pie/pregenerated/pie-a64c-field-decoder.o pie/pregenerated/pie-a64c-encoder.o pie/pregenerated/pie-a64c-decoder.o
	SOURCES += arch/aarch64c/dispatcher_aarch64c.S arch/aarch64c/dispatcher_aarch64c.c
	SOURCES += arch/aarch64c/scanner_a64c.c
	SOURCES += api/emit_a64c.c
else ifeq ($(findstring arm, $(ARCH)), arm)
	CFLAGS += -march=armv7-a -mfpu=neon
	LDFLAGS += -Wl,-Ttext-segment=$(or $(TEXT_SEGMENT),0xa8000000)
	HEADERS += api/emit_arm.h api/emit_thumb.h
	PIE = pie/pie-arm-encoder.o pie/pie-arm-decoder.o pie/pie-arm-field-decoder.o
	PIE += pie/pie-thumb-encoder.o pie/pie-thumb-decoder.o pie/pie-thumb-field-decoder.o
	SOURCES += arch/aarch32/dispatcher_aarch32.S arch/aarch32/dispatcher_aarch32.c
	SOURCES += arch/aarch32/scanner_t32.c arch/aarch32/scanner_a32.c
	SOURCES += api/emit_arm.c api/emit_thumb.c
else ifeq ($(ARCH),aarch64)
	HEADERS += api/emit_a64.h
	LDFLAGS += -Wl,-Ttext-segment=$(or $(TEXT_SEGMENT),0x7000000000)
	PIE += pie/pie-a64-field-decoder.o pie/pie-a64-encoder.o pie/pie-a64-decoder.o
	SOURCES += arch/aarch64/dispatcher_aarch64.S arch/aarch64/dispatcher_aarch64.c
	SOURCES += arch/aarch64/scanner_a64.c
	SOURCES += api/emit_a64.c
endif


ifdef PLUGINS
	CFLAGS += -DPLUGINS_NEW
endif

.PHONY: pie clean cleanall

all:
	$(info MAMBO: detected architecture "$(ARCH)")
	@$(MAKE) --no-print-directory pie && $(MAKE) --no-print-directory $(or $(OUTPUT_FILE),dbm)
	$(ELF_PATCH) dbm

pie:
	@$(MAKE) --no-print-directory -C pie/ native

%.o: %.c %.h
	$(info MAMBO :-)
	$(CC) $(CFLAGS) -c -o $@ $<

$(or $(OUTPUT_FILE),dbm): $(HEADERS) $(SOURCES) $(PLUGINS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OPTS) $(INCLUDES) -o $@ $(SOURCES) $(PLUGINS) $(PIE) $(LIBS) $(PLUGIN_ARGS)

cachesim:
	PLUGINS="plugins/cachesim/cachesim.c plugins/cachesim/cachesim.S plugins/cachesim/cachesim_model.c" OUTPUT_FILE=mambo_cachesim make

memcheck:
	PLUGINS="plugins/memcheck/memcheck.S plugins/memcheck/memcheck.c plugins/memcheck/naive_stdlib.c" OUTPUT_FILE=mambo_memcheck make

clean:
	rm -f dbm elf/elf_loader.o elf/symbol_parser.o

cleanall: clean
	$(MAKE) -C pie/ clean

api/emit_%.c: pie/pie-%-encoder.c api/generate_emit_wrapper.rb
	ruby api/generate_emit_wrapper.rb $< > $@

api/emit_%.h: pie/pie-%-encoder.c api/generate_emit_wrapper.rb
	ruby api/generate_emit_wrapper.rb $< header > $@
