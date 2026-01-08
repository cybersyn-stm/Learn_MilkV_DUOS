cmd_/home/cybersyn/duos/my-duos-project/kernelmode/ssd1306_demo_misc/src/ssd1306.mod.o := /home/cybersyn/duo-buildroot-sdk-v2/host-tools/gcc/riscv64-linux-musl-x86_64/bin/riscv64-unknown-linux-musl-gcc -Wp,-MMD,/home/cybersyn/duos/my-duos-project/kernelmode/ssd1306_demo_misc/src/.ssd1306.mod.o.d -nostdinc -isystem /home/cybersyn/duo-buildroot-sdk-v2/host-tools/gcc/riscv64-linux-musl-x86_64/bin/../lib/gcc/riscv64-unknown-linux-musl/10.2.0/include -I/home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/arch/riscv/include -I./arch/riscv/include/generated -I/home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include -I./include -I/home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/arch/riscv/include/uapi -I./arch/riscv/include/generated/uapi -I/home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi -I./include/generated/uapi -include /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/kconfig.h -include /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/compiler_types.h -D__KERNEL__ -fmacro-prefix-map=/home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/= -Wall -Wundef -Werror=strict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -fshort-wchar -fno-PIE -Werror=implicit-function-declaration -Werror=implicit-int -Werror=return-type -Wno-format-security -std=gnu89 -mabi=lp64 -march=rv64imac -Wa,-march=rv64imafdcv0p7 -mno-save-restore -DCONFIG_PAGE_OFFSET=0xffffffe000000000 -mcmodel=medany -mstrict-align -fno-delete-null-pointer-checks -Wno-frame-address -Wno-format-truncation -Wno-format-overflow -Wno-address-of-packed-member -Os -Wframe-larger-than=2048 -fstack-protector-strong -Wno-unused-but-set-variable -Wimplicit-fallthrough -Wno-unused-const-variable -fomit-frame-pointer -Wdeclaration-after-statement -Wvla -Wno-pointer-sign -Wno-stringop-truncation -Wno-zero-length-bounds -Wno-array-bounds -Wno-stringop-overflow -Wno-restrict -Wno-maybe-uninitialized -fno-strict-overflow -fno-stack-check -Werror=date-time -Werror=incompatible-pointer-types -Werror=designated-init -Wno-packed-not-aligned  -DMODULE -mno-relax  -DKBUILD_BASENAME='"ssd1306.mod"' -DKBUILD_MODNAME='"ssd1306"' -c -o /home/cybersyn/duos/my-duos-project/kernelmode/ssd1306_demo_misc/src/ssd1306.mod.o /home/cybersyn/duos/my-duos-project/kernelmode/ssd1306_demo_misc/src/ssd1306.mod.c

source_/home/cybersyn/duos/my-duos-project/kernelmode/ssd1306_demo_misc/src/ssd1306.mod.o := /home/cybersyn/duos/my-duos-project/kernelmode/ssd1306_demo_misc/src/ssd1306.mod.c

deps_/home/cybersyn/duos/my-duos-project/kernelmode/ssd1306_demo_misc/src/ssd1306.mod.o := \
    $(wildcard include/config/module/unload.h) \
    $(wildcard include/config/retpoline.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/kconfig.h \
    $(wildcard include/config/cc/version/text.h) \
    $(wildcard include/config/cpu/big/endian.h) \
    $(wildcard include/config/booger.h) \
    $(wildcard include/config/foo.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/compiler_types.h \
    $(wildcard include/config/have/arch/compiler/h.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/cc/has/asm/inline.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/compiler_attributes.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/compiler-gcc.h \
    $(wildcard include/config/arch/use/builtin/bswap.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/module.h \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/sysfs.h) \
    $(wildcard include/config/modules/tree/lookup.h) \
    $(wildcard include/config/livepatch.h) \
    $(wildcard include/config/unused/symbols.h) \
    $(wildcard include/config/module/sig.h) \
    $(wildcard include/config/generic/bug.h) \
    $(wildcard include/config/kallsyms.h) \
    $(wildcard include/config/smp.h) \
    $(wildcard include/config/tracepoints.h) \
    $(wildcard include/config/tree/srcu.h) \
    $(wildcard include/config/bpf/events.h) \
    $(wildcard include/config/jump/label.h) \
    $(wildcard include/config/tracing.h) \
    $(wildcard include/config/event/tracing.h) \
    $(wildcard include/config/ftrace/mcount/record.h) \
    $(wildcard include/config/kprobes.h) \
    $(wildcard include/config/have/static/call/inline.h) \
    $(wildcard include/config/constructors.h) \
    $(wildcard include/config/function/error/injection.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/list.h \
    $(wildcard include/config/debug/list.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/types.h \
    $(wildcard include/config/have/uid16.h) \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/arch/dma/addr/t/64bit.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
    $(wildcard include/config/64bit.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/types.h \
  arch/riscv/include/generated/uapi/asm/types.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/asm-generic/types.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/asm-generic/int-ll64.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/asm-generic/int-ll64.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/arch/riscv/include/uapi/asm/bitsperlong.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/asm-generic/bitsperlong.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/asm-generic/bitsperlong.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/posix_types.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/stddef.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/stddef.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/compiler_types.h \
  arch/riscv/include/generated/uapi/asm/posix_types.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/asm-generic/posix_types.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/poison.h \
    $(wildcard include/config/illegal/pointer/value.h) \
    $(wildcard include/config/page/poisoning/zero.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/const.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/vdso/const.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/const.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/kernel.h \
    $(wildcard include/config/preempt/voluntary.h) \
    $(wildcard include/config/debug/atomic/sleep.h) \
    $(wildcard include/config/preempt/rt.h) \
    $(wildcard include/config/mmu.h) \
    $(wildcard include/config/prove/locking.h) \
    $(wildcard include/config/panic/timeout.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/limits.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/limits.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/vdso/limits.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/linkage.h \
    $(wildcard include/config/arch/use/sym/annotations.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/stringify.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/export.h \
    $(wildcard include/config/modversions.h) \
    $(wildcard include/config/module/rel/crcs.h) \
    $(wildcard include/config/have/arch/prel32/relocations.h) \
    $(wildcard include/config/trim/unused/ksyms.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/arch/riscv/include/asm/linkage.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/compiler.h \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/stack/validation.h) \
  arch/riscv/include/generated/asm/rwonce.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/asm-generic/rwonce.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/kasan-checks.h \
    $(wildcard include/config/kasan.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/kcsan-checks.h \
    $(wildcard include/config/kcsan.h) \
    $(wildcard include/config/kcsan/ignore/atomics.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/bitops.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/bits.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/vdso/bits.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/build_bug.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/arch/riscv/include/asm/bitops.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/irqflags.h \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/irqsoff/tracer.h) \
    $(wildcard include/config/preempt/tracer.h) \
    $(wildcard include/config/trace/irqflags/support.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/typecheck.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/arch/riscv/include/asm/irqflags.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/arch/riscv/include/asm/processor.h \
    $(wildcard include/config/vector/emu.h) \
    $(wildcard include/config/compat.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/vdso/processor.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/arch/riscv/include/asm/vdso/processor.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/arch/riscv/include/asm/barrier.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/asm-generic/barrier.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/arch/riscv/include/asm/ptrace.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/arch/riscv/include/uapi/asm/ptrace.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/arch/riscv/include/asm/csr.h \
    $(wildcard include/config/vector/1/0.h) \
    $(wildcard include/config/riscv/m/mode.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/arch/riscv/include/asm/asm.h \
    $(wildcard include/config/xip/kernel.h) \
  arch/riscv/include/generated/asm/percpu.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/asm-generic/percpu.h \
    $(wildcard include/config/debug/preempt.h) \
    $(wildcard include/config/have/setup/per/cpu/area.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/threads.h \
    $(wildcard include/config/nr/cpus.h) \
    $(wildcard include/config/base/small.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/percpu-defs.h \
    $(wildcard include/config/debug/force/weak/per/cpu.h) \
    $(wildcard include/config/amd/mem/encrypt.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/asm-generic/bitops/__ffs.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/asm-generic/bitops/ffz.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/asm-generic/bitops/fls.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/asm-generic/bitops/__fls.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/asm-generic/bitops/fls64.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/asm-generic/bitops/find.h \
    $(wildcard include/config/generic/find/first/bit.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/asm-generic/bitops/sched.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/asm-generic/bitops/ffs.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/asm-generic/bitops/hweight.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/asm-generic/bitops/arch_hweight.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/asm-generic/bitops/const_hweight.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/asm-generic/bitops/non-atomic.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/asm-generic/bitops/le.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/arch/riscv/include/uapi/asm/byteorder.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/byteorder/little_endian.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/byteorder/little_endian.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/swab.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/swab.h \
  arch/riscv/include/generated/uapi/asm/swab.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/asm-generic/swab.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/byteorder/generic.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/asm-generic/bitops/ext2-atomic.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/log2.h \
    $(wildcard include/config/arch/has/ilog2/u32.h) \
    $(wildcard include/config/arch/has/ilog2/u64.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/minmax.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/printk.h \
    $(wildcard include/config/message/loglevel/default.h) \
    $(wildcard include/config/console/loglevel/default.h) \
    $(wildcard include/config/console/loglevel/quiet.h) \
    $(wildcard include/config/early/printk.h) \
    $(wildcard include/config/printk/nmi.h) \
    $(wildcard include/config/printk.h) \
    $(wildcard include/config/dynamic/debug.h) \
    $(wildcard include/config/dynamic/debug/core.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/init.h \
    $(wildcard include/config/strict/kernel/rwx.h) \
    $(wildcard include/config/strict/module/rwx.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/kern_levels.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/cache.h \
    $(wildcard include/config/arch/has/cache/line/size.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/kernel.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/sysinfo.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/arch/riscv/include/asm/cache.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/ratelimit_types.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/param.h \
  arch/riscv/include/generated/uapi/asm/param.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/asm-generic/param.h \
    $(wildcard include/config/hz.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/asm-generic/param.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/spinlock_types.h \
    $(wildcard include/config/debug/spinlock.h) \
    $(wildcard include/config/debug/lock/alloc.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/spinlock_types_up.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/lockdep_types.h \
    $(wildcard include/config/prove/raw/lock/nesting.h) \
    $(wildcard include/config/preempt/lock.h) \
    $(wildcard include/config/lockdep.h) \
    $(wildcard include/config/lock/stat.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/rwlock_types.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/dynamic_debug.h \
  arch/riscv/include/generated/asm/div64.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/asm-generic/div64.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/stat.h \
  arch/riscv/include/generated/uapi/asm/stat.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/asm-generic/stat.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/stat.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/time.h \
    $(wildcard include/config/arch/uses/gettimeoffset.h) \
    $(wildcard include/config/posix/timers.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/math64.h \
    $(wildcard include/config/arch/supports/int128.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/vdso/math64.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/time64.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/vdso/time64.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/time.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/time_types.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/time32.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/timex.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/timex.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/arch/riscv/include/asm/timex.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/vdso/time32.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/vdso/time.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/uidgid.h \
    $(wildcard include/config/multiuser.h) \
    $(wildcard include/config/user/ns.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/highuid.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/kmod.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/umh.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/gfp.h \
    $(wildcard include/config/highmem.h) \
    $(wildcard include/config/zone/dma.h) \
    $(wildcard include/config/zone/dma32.h) \
    $(wildcard include/config/zone/device.h) \
    $(wildcard include/config/numa.h) \
    $(wildcard include/config/pm/sleep.h) \
    $(wildcard include/config/contig/alloc.h) \
    $(wildcard include/config/cma.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/mmdebug.h \
    $(wildcard include/config/debug/vm.h) \
    $(wildcard include/config/debug/virtual.h) \
    $(wildcard include/config/debug/vm/pgflags.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/bug.h \
    $(wildcard include/config/bug/on/data/corruption.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/arch/riscv/include/asm/bug.h \
    $(wildcard include/config/generic/bug/relative/pointers.h) \
    $(wildcard include/config/debug/bugverbose.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/asm-generic/bug.h \
    $(wildcard include/config/bug.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/instrumentation.h \
    $(wildcard include/config/debug/entry.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/mmzone.h \
    $(wildcard include/config/force/max/zoneorder.h) \
    $(wildcard include/config/memory/isolation.h) \
    $(wildcard include/config/zsmalloc.h) \
    $(wildcard include/config/shadow/call/stack.h) \
    $(wildcard include/config/memcg.h) \
    $(wildcard include/config/sparsemem.h) \
    $(wildcard include/config/memory/hotplug.h) \
    $(wildcard include/config/compaction.h) \
    $(wildcard include/config/discontigmem.h) \
    $(wildcard include/config/transparent/hugepage.h) \
    $(wildcard include/config/flat/node/mem/map.h) \
    $(wildcard include/config/page/extension.h) \
    $(wildcard include/config/deferred/struct/page/init.h) \
    $(wildcard include/config/have/memoryless/nodes.h) \
    $(wildcard include/config/need/multiple/nodes.h) \
    $(wildcard include/config/flatmem.h) \
    $(wildcard include/config/sparsemem/vmemmap.h) \
    $(wildcard include/config/sparsemem/extreme.h) \
    $(wildcard include/config/memory/hotremove.h) \
    $(wildcard include/config/have/arch/pfn/valid.h) \
    $(wildcard include/config/holes/in/zone.h) \
    $(wildcard include/config/arch/has/holes/memorymodel.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/spinlock.h \
    $(wildcard include/config/preemption.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/preempt.h \
    $(wildcard include/config/preempt/count.h) \
    $(wildcard include/config/trace/preempt/toggle.h) \
    $(wildcard include/config/preempt/notifiers.h) \
  arch/riscv/include/generated/asm/preempt.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/asm-generic/preempt.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/thread_info.h \
    $(wildcard include/config/thread/info/in/task.h) \
    $(wildcard include/config/have/arch/within/stack/frames.h) \
    $(wildcard include/config/hardened/usercopy.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/restart_block.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/arch/riscv/include/asm/current.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/arch/riscv/include/asm/thread_info.h \
    $(wildcard include/config/set/fs.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/arch/riscv/include/asm/page.h \
    $(wildcard include/config/page/offset.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/pfn.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/asm-generic/memory_model.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/asm-generic/getorder.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/bottom_half.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/lockdep.h \
    $(wildcard include/config/debug/locking/api/selftests.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/smp.h \
    $(wildcard include/config/up/late/init.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/errno.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/errno.h \
  arch/riscv/include/generated/uapi/asm/errno.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/asm-generic/errno.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/asm-generic/errno-base.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/cpumask.h \
    $(wildcard include/config/cpumask/offstack.h) \
    $(wildcard include/config/hotplug/cpu.h) \
    $(wildcard include/config/debug/per/cpu/maps.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/bitmap.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/string.h \
    $(wildcard include/config/binary/printf.h) \
    $(wildcard include/config/fortify/source.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/string.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/arch/riscv/include/asm/string.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/atomic.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/arch/riscv/include/asm/atomic.h \
    $(wildcard include/config/generic/atomic64.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/arch/riscv/include/asm/cmpxchg.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/arch/riscv/include/asm/fence.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/atomic-fallback.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/asm-generic/atomic-long.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/smp_types.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/llist.h \
    $(wildcard include/config/arch/have/nmi/safe/cmpxchg.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/arch/riscv/include/asm/mmiowb.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/asm-generic/mmiowb.h \
    $(wildcard include/config/mmiowb.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/spinlock_up.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/rwlock.h \
    $(wildcard include/config/preempt.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/spinlock_api_up.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/wait.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/wait.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/numa.h \
    $(wildcard include/config/nodes/shift.h) \
    $(wildcard include/config/numa/keep/meminfo.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/seqlock.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/mutex.h \
    $(wildcard include/config/mutex/spin/on/owner.h) \
    $(wildcard include/config/debug/mutexes.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/osq_lock.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/debug_locks.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/ww_mutex.h \
    $(wildcard include/config/debug/ww/mutex/slowpath.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/nodemask.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/pageblock-flags.h \
    $(wildcard include/config/hugetlb/page.h) \
    $(wildcard include/config/hugetlb/page/size/variable.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/page-flags-layout.h \
    $(wildcard include/config/numa/balancing.h) \
    $(wildcard include/config/kasan/sw/tags.h) \
  include/generated/bounds.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/mm_types.h \
    $(wildcard include/config/have/aligned/struct/page.h) \
    $(wildcard include/config/userfaultfd.h) \
    $(wildcard include/config/swap.h) \
    $(wildcard include/config/have/arch/compat/mmap/bases.h) \
    $(wildcard include/config/membarrier.h) \
    $(wildcard include/config/aio.h) \
    $(wildcard include/config/mmu/notifier.h) \
    $(wildcard include/config/arch/want/batched/unmap/tlb/flush.h) \
    $(wildcard include/config/iommu/support.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/mm_types_task.h \
    $(wildcard include/config/split/ptlock/cpus.h) \
    $(wildcard include/config/arch/enable/split/pmd/ptlock.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/auxvec.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/auxvec.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/arch/riscv/include/uapi/asm/auxvec.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/rbtree.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/rcupdate.h \
    $(wildcard include/config/preempt/rcu.h) \
    $(wildcard include/config/tiny/rcu.h) \
    $(wildcard include/config/rcu/stall/common.h) \
    $(wildcard include/config/no/hz/full.h) \
    $(wildcard include/config/rcu/nocb/cpu.h) \
    $(wildcard include/config/tasks/rcu/generic.h) \
    $(wildcard include/config/tasks/rcu.h) \
    $(wildcard include/config/tasks/rcu/trace.h) \
    $(wildcard include/config/tasks/rude/rcu.h) \
    $(wildcard include/config/tree/rcu.h) \
    $(wildcard include/config/debug/objects/rcu/head.h) \
    $(wildcard include/config/prove/rcu.h) \
    $(wildcard include/config/rcu/boost.h) \
    $(wildcard include/config/arch/weak/release/acquire.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/rcutree.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/rwsem.h \
    $(wildcard include/config/rwsem/spin/on/owner.h) \
    $(wildcard include/config/debug/rwsems.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/err.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/completion.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/swait.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/uprobes.h \
    $(wildcard include/config/uprobes.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/workqueue.h \
    $(wildcard include/config/debug/objects/work.h) \
    $(wildcard include/config/freezer.h) \
    $(wildcard include/config/wq/watchdog.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/timer.h \
    $(wildcard include/config/debug/objects/timers.h) \
    $(wildcard include/config/no/hz/common.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/ktime.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/jiffies.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/vdso/jiffies.h \
  include/generated/timeconst.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/vdso/ktime.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/timekeeping.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/timekeeping32.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/debugobjects.h \
    $(wildcard include/config/debug/objects.h) \
    $(wildcard include/config/debug/objects/free.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/arch/riscv/include/asm/mmu.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/page-flags.h \
    $(wildcard include/config/arch/uses/pg/uncached.h) \
    $(wildcard include/config/memory/failure.h) \
    $(wildcard include/config/idle/page/tracking.h) \
    $(wildcard include/config/thp/swap.h) \
    $(wildcard include/config/ksm.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/memory_hotplug.h \
    $(wildcard include/config/arch/has/add/pages.h) \
    $(wildcard include/config/have/arch/nodedata/extension.h) \
    $(wildcard include/config/have/bootmem/info/node.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/notifier.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/srcu.h \
    $(wildcard include/config/tiny/srcu.h) \
    $(wildcard include/config/srcu.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/rcu_segcblist.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/srcutree.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/rcu_node_tree.h \
    $(wildcard include/config/rcu/fanout.h) \
    $(wildcard include/config/rcu/fanout/leaf.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/topology.h \
    $(wildcard include/config/use/percpu/numa/node/id.h) \
    $(wildcard include/config/sched/smt.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/arch_topology.h \
    $(wildcard include/config/generic/arch/topology.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/percpu.h \
    $(wildcard include/config/need/per/cpu/embed/first/chunk.h) \
    $(wildcard include/config/need/per/cpu/page/first/chunk.h) \
  arch/riscv/include/generated/asm/topology.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/asm-generic/topology.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/sysctl.h \
    $(wildcard include/config/sysctl.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/sysctl.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/elf.h \
    $(wildcard include/config/arch/use/gnu/property.h) \
    $(wildcard include/config/arch/have/elf/prot.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/arch/riscv/include/asm/elf.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/elf.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/elf-em.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/compat.h \
    $(wildcard include/config/arch/has/syscall/wrapper.h) \
    $(wildcard include/config/x86/x32/abi.h) \
    $(wildcard include/config/compat/old/sigaction.h) \
    $(wildcard include/config/odd/rt/sigaction.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/sem.h \
    $(wildcard include/config/sysvipc.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/sem.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/ipc.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/rhashtable-types.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/ipc.h \
  arch/riscv/include/generated/uapi/asm/ipcbuf.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/asm-generic/ipcbuf.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/refcount.h \
  arch/riscv/include/generated/uapi/asm/sembuf.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/asm-generic/sembuf.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/socket.h \
    $(wildcard include/config/proc/fs.h) \
  arch/riscv/include/generated/uapi/asm/socket.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/asm-generic/socket.h \
  arch/riscv/include/generated/uapi/asm/sockios.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/asm-generic/sockios.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/sockios.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/uio.h \
    $(wildcard include/config/arch/has/uaccess/flushcache.h) \
    $(wildcard include/config/arch/has/copy/mc.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/uio.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/socket.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/if.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/libc-compat.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/hdlc/ioctl.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/fs.h \
    $(wildcard include/config/read/only/thp/for/fs.h) \
    $(wildcard include/config/fs/posix/acl.h) \
    $(wildcard include/config/security.h) \
    $(wildcard include/config/cgroup/writeback.h) \
    $(wildcard include/config/ima.h) \
    $(wildcard include/config/file/locking.h) \
    $(wildcard include/config/fsnotify.h) \
    $(wildcard include/config/fs/encryption.h) \
    $(wildcard include/config/fs/verity.h) \
    $(wildcard include/config/epoll.h) \
    $(wildcard include/config/unicode.h) \
    $(wildcard include/config/quota.h) \
    $(wildcard include/config/fs/dax.h) \
    $(wildcard include/config/mandatory/file/locking.h) \
    $(wildcard include/config/block.h) \
    $(wildcard include/config/migration.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/wait_bit.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/kdev_t.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/kdev_t.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/dcache.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/rculist.h \
    $(wildcard include/config/prove/rcu/list.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/rculist_bl.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/list_bl.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/bit_spinlock.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/lockref.h \
    $(wildcard include/config/arch/use/cmpxchg/lockref.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/stringhash.h \
    $(wildcard include/config/dcache/word/access.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/hash.h \
    $(wildcard include/config/have/arch/hash.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/path.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/list_lru.h \
    $(wildcard include/config/memcg/kmem.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/shrinker.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/radix-tree.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/xarray.h \
    $(wildcard include/config/xarray/multi.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/kconfig.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/local_lock.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/local_lock_internal.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/pid.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/capability.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/capability.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/semaphore.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/fcntl.h \
    $(wildcard include/config/arch/32bit/off/t.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/fcntl.h \
  arch/riscv/include/generated/uapi/asm/fcntl.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/asm-generic/fcntl.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/openat2.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/migrate_mode.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/percpu-rwsem.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/rcuwait.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/sched/signal.h \
    $(wildcard include/config/sched/autogroup.h) \
    $(wildcard include/config/bsd/process/acct.h) \
    $(wildcard include/config/taskstats.h) \
    $(wildcard include/config/audit.h) \
    $(wildcard include/config/stack/growsup.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/signal.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/signal_types.h \
    $(wildcard include/config/old/sigaction.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/signal.h \
  arch/riscv/include/generated/uapi/asm/signal.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/asm-generic/signal.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/asm-generic/signal.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/asm-generic/signal-defs.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/arch/riscv/include/uapi/asm/sigcontext.h \
  arch/riscv/include/generated/uapi/asm/siginfo.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/asm-generic/siginfo.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/sched.h \
    $(wildcard include/config/virt/cpu/accounting/native.h) \
    $(wildcard include/config/sched/info.h) \
    $(wildcard include/config/schedstats.h) \
    $(wildcard include/config/fair/group/sched.h) \
    $(wildcard include/config/rt/group/sched.h) \
    $(wildcard include/config/rt/mutexes.h) \
    $(wildcard include/config/uclamp/task.h) \
    $(wildcard include/config/uclamp/buckets/count.h) \
    $(wildcard include/config/cgroup/sched.h) \
    $(wildcard include/config/blk/dev/io/trace.h) \
    $(wildcard include/config/tasks/trace/rcu.h) \
    $(wildcard include/config/psi.h) \
    $(wildcard include/config/compat/brk.h) \
    $(wildcard include/config/cgroups.h) \
    $(wildcard include/config/blk/cgroup.h) \
    $(wildcard include/config/stackprotector.h) \
    $(wildcard include/config/arch/has/scaled/cputime.h) \
    $(wildcard include/config/virt/cpu/accounting/gen.h) \
    $(wildcard include/config/posix/cputimers.h) \
    $(wildcard include/config/posix/cpu/timers/task/work.h) \
    $(wildcard include/config/keys.h) \
    $(wildcard include/config/detect/hung/task.h) \
    $(wildcard include/config/io/uring.h) \
    $(wildcard include/config/auditsyscall.h) \
    $(wildcard include/config/ubsan.h) \
    $(wildcard include/config/ubsan/trap.h) \
    $(wildcard include/config/task/xacct.h) \
    $(wildcard include/config/cpusets.h) \
    $(wildcard include/config/x86/cpu/resctrl.h) \
    $(wildcard include/config/futex.h) \
    $(wildcard include/config/perf/events.h) \
    $(wildcard include/config/rseq.h) \
    $(wildcard include/config/task/delay/acct.h) \
    $(wildcard include/config/fault/injection.h) \
    $(wildcard include/config/latencytop.h) \
    $(wildcard include/config/kunit.h) \
    $(wildcard include/config/function/graph/tracer.h) \
    $(wildcard include/config/kcov.h) \
    $(wildcard include/config/bcache.h) \
    $(wildcard include/config/vmap/stack.h) \
    $(wildcard include/config/gcc/plugin/stackleak.h) \
    $(wildcard include/config/x86/mce.h) \
    $(wildcard include/config/sched/cvitek.h) \
    $(wildcard include/config/arch/task/struct/on/stack.h) \
    $(wildcard include/config/debug/rseq.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/sched.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/shm.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/shm.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/asm-generic/hugetlb_encode.h \
  arch/riscv/include/generated/uapi/asm/shmbuf.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/asm-generic/shmbuf.h \
  arch/riscv/include/generated/asm/shmparam.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/asm-generic/shmparam.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/kcov.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/kcov.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/plist.h \
    $(wildcard include/config/debug/plist.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/hrtimer.h \
    $(wildcard include/config/high/res/timers.h) \
    $(wildcard include/config/time/low/res.h) \
    $(wildcard include/config/timerfd.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/hrtimer_defs.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/timerqueue.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/seccomp.h \
    $(wildcard include/config/seccomp.h) \
    $(wildcard include/config/have/arch/seccomp/filter.h) \
    $(wildcard include/config/seccomp/filter.h) \
    $(wildcard include/config/checkpoint/restore.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/seccomp.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/arch/riscv/include/asm/seccomp.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/arch/riscv/include/asm/unistd.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/arch/riscv/include/uapi/asm/unistd.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/asm-generic/unistd.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/asm-generic/seccomp.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/unistd.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/resource.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/resource.h \
  arch/riscv/include/generated/uapi/asm/resource.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/asm-generic/resource.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/asm-generic/resource.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/latencytop.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/sched/prio.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/sched/types.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/task_io_accounting.h \
    $(wildcard include/config/task/io/accounting.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/posix-timers.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/alarmtimer.h \
    $(wildcard include/config/rtc/class.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/task_work.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/rseq.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/kcsan.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/sched/jobctl.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/sched/task.h \
    $(wildcard include/config/have/exit/thread.h) \
    $(wildcard include/config/arch/wants/dynamic/task/struct.h) \
    $(wildcard include/config/have/arch/thread/struct/whitelist.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/uaccess.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/fault-inject-usercopy.h \
    $(wildcard include/config/fault/injection/usercopy.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/instrumented.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/arch/riscv/include/asm/uaccess.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/arch/riscv/include/asm/pgtable.h \
    $(wildcard include/config/va/bits.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/sizes.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/arch/riscv/include/asm/pgtable-bits.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/asm-generic/pgtable-nopud.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/asm-generic/pgtable-nop4d.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/arch/riscv/include/asm/tlbflush.h \
    $(wildcard include/config/no/sfence/vma.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/arch/riscv/include/asm/smp.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/irqreturn.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/arch/riscv/include/asm/pgtable-64.h \
  arch/riscv/include/generated/asm/extable.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/asm-generic/extable.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/cred.h \
    $(wildcard include/config/debug/credentials.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/key.h \
    $(wildcard include/config/key/notifications.h) \
    $(wildcard include/config/net.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/assoc_array.h \
    $(wildcard include/config/associative/array.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/sched/user.h \
    $(wildcard include/config/fanotify.h) \
    $(wildcard include/config/posix/mqueue.h) \
    $(wildcard include/config/bpf/syscall.h) \
    $(wildcard include/config/watch/queue.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/ratelimit.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/rcu_sync.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/delayed_call.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/uuid.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/uuid.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/errseq.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/ioprio.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/sched/rt.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/iocontext.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/fs_types.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/fs.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/ioctl.h \
  arch/riscv/include/generated/uapi/asm/ioctl.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/asm-generic/ioctl.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/asm-generic/ioctl.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/quota.h \
    $(wildcard include/config/quota/netlink/interface.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/percpu_counter.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/dqblk_xfs.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/dqblk_v1.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/dqblk_v2.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/dqblk_qtree.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/projid.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/quota.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/nfs_fs_i.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/aio_abi.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/arch/riscv/include/asm/compat.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/sched/task_stack.h \
    $(wildcard include/config/debug/stack/usage.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/uapi/linux/magic.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/asm-generic/compat.h \
    $(wildcard include/config/compat/for/u64/alignment.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/arch/riscv/include/uapi/asm/elf.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/arch/riscv/include/asm/cacheinfo.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/cacheinfo.h \
    $(wildcard include/config/acpi/pptt.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/cpu.h \
    $(wildcard include/config/pm/sleep/smp.h) \
    $(wildcard include/config/pm/sleep/smp/nonzero/cpu.h) \
    $(wildcard include/config/hotplug/smt.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/node.h \
    $(wildcard include/config/hmem/reporting.h) \
    $(wildcard include/config/memory/hotplug/sparse.h) \
    $(wildcard include/config/hugetlbfs.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/device.h \
    $(wildcard include/config/debug/devres.h) \
    $(wildcard include/config/energy/model.h) \
    $(wildcard include/config/generic/msi/irq/domain.h) \
    $(wildcard include/config/pinctrl.h) \
    $(wildcard include/config/generic/msi/irq.h) \
    $(wildcard include/config/dma/ops.h) \
    $(wildcard include/config/dma/declare/coherent.h) \
    $(wildcard include/config/dma/cma.h) \
    $(wildcard include/config/arch/has/sync/dma/for/device.h) \
    $(wildcard include/config/arch/has/sync/dma/for/cpu.h) \
    $(wildcard include/config/arch/has/sync/dma/for/cpu/all.h) \
    $(wildcard include/config/dma/ops/bypass.h) \
    $(wildcard include/config/of.h) \
    $(wildcard include/config/devtmpfs.h) \
    $(wildcard include/config/sysfs/deprecated.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/dev_printk.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/energy_model.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/jump_label.h \
    $(wildcard include/config/have/arch/jump/label/relative.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/kobject.h \
    $(wildcard include/config/uevent/helper.h) \
    $(wildcard include/config/debug/kobject/release.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/sysfs.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/kernfs.h \
    $(wildcard include/config/kernfs.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/idr.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/kobject_ns.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/kref.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/sched/cpufreq.h \
    $(wildcard include/config/cpu/freq.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/sched/topology.h \
    $(wildcard include/config/sched/debug.h) \
    $(wildcard include/config/sched/mc.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/sched/idle.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/ioport.h \
    $(wildcard include/config/io/strict/devmem.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/klist.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/pm.h \
    $(wildcard include/config/vt/console/sleep.h) \
    $(wildcard include/config/pm.h) \
    $(wildcard include/config/pm/clk.h) \
    $(wildcard include/config/pm/generic/domains.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/overflow.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/device/bus.h \
    $(wildcard include/config/acpi.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/device/class.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/device/driver.h \
  arch/riscv/include/generated/asm/device.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/asm-generic/device.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/pm_wakeup.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/cpuhotplug.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/moduleparam.h \
    $(wildcard include/config/alpha.h) \
    $(wildcard include/config/ia64.h) \
    $(wildcard include/config/ppc64.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/rbtree_latch.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/error-injection.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/asm-generic/error-injection.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/tracepoint-defs.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/static_key.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/static_call_types.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/arch/riscv/include/asm/module.h \
    $(wildcard include/config/module/sections.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/asm-generic/module.h \
    $(wildcard include/config/have/mod/arch/specific.h) \
    $(wildcard include/config/modules/use/elf/rel.h) \
    $(wildcard include/config/modules/use/elf/rela.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/build-salt.h \
    $(wildcard include/config/build/salt.h) \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/elfnote.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/include/linux/vermagic.h \
  include/generated/utsrelease.h \
  /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/arch/riscv/include/asm/vermagic.h \

/home/cybersyn/duos/my-duos-project/kernelmode/ssd1306_demo_misc/src/ssd1306.mod.o: $(deps_/home/cybersyn/duos/my-duos-project/kernelmode/ssd1306_demo_misc/src/ssd1306.mod.o)

$(deps_/home/cybersyn/duos/my-duos-project/kernelmode/ssd1306_demo_misc/src/ssd1306.mod.o):
