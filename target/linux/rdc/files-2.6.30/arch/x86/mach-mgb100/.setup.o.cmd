cmd_arch/x86/mach-mgb100/setup.o := i486-openwrt-linux-uclibc-gcc -Wp,-MD,arch/x86/mach-mgb100/.setup.o.d  -nostdinc -isystem /home/lintel/openwrt-rdc/staging_dir/toolchain-i386_gcc-4.1.2_uClibc-0.9.30.1/usr/lib/gcc/i486-openwrt-linux-uclibc/4.1.2/include -Iinclude  -I/home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include -include include/linux/autoconf.h -D__KERNEL__ -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -fno-delete-null-pointer-checks -Os -m32 -msoft-float -mregparm=3 -freg-struct-return -mpreferred-stack-boundary=2 -march=i486 -Wa,-mtune=generic32 -ffreestanding -DCONFIG_AS_CFI=1 -DCONFIG_AS_CFI_SIGNAL_FRAME=1 -pipe -Wno-sign-compare -fno-asynchronous-unwind-tables -mno-sse -mno-mmx -mno-sse2 -mno-3dnow -fno-stack-protector -fomit-frame-pointer -Wdeclaration-after-statement -Wno-pointer-sign   -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(setup)"  -D"KBUILD_MODNAME=KBUILD_STR(setup)"  -c -o arch/x86/mach-mgb100/setup.o arch/x86/mach-mgb100/setup.c

deps_arch/x86/mach-mgb100/setup.o := \
  arch/x86/mach-mgb100/setup.c \
  include/linux/init.h \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/hotplug.h) \
  include/linux/compiler.h \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
  include/linux/compiler-gcc.h \
    $(wildcard include/config/arch/supports/optimized/inlining.h) \
    $(wildcard include/config/optimize/inlining.h) \
  include/linux/compiler-gcc4.h \
  include/linux/section-names.h \
  include/linux/stringify.h \
  include/linux/i2c.h \
    $(wildcard include/config/i2c/boardinfo.h) \
  include/linux/types.h \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/lbd.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
    $(wildcard include/config/64bit.h) \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/types.h \
    $(wildcard include/config/x86/32.h) \
    $(wildcard include/config/x86/64.h) \
    $(wildcard include/config/highmem64g.h) \
  include/asm-generic/int-ll64.h \
  include/linux/posix_types.h \
  include/linux/stddef.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/posix_types.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/posix_types_32.h \
  include/linux/module.h \
    $(wildcard include/config/modversions.h) \
    $(wildcard include/config/unused/symbols.h) \
    $(wildcard include/config/generic/bug.h) \
    $(wildcard include/config/kallsyms.h) \
    $(wildcard include/config/markers.h) \
    $(wildcard include/config/tracepoints.h) \
    $(wildcard include/config/tracing.h) \
    $(wildcard include/config/module/unload.h) \
    $(wildcard include/config/smp.h) \
    $(wildcard include/config/sysfs.h) \
  include/linux/list.h \
    $(wildcard include/config/debug/list.h) \
  include/linux/poison.h \
  include/linux/prefetch.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/processor.h \
    $(wildcard include/config/x86/vsmp.h) \
    $(wildcard include/config/cc/stackprotector.h) \
    $(wildcard include/config/x86/ds.h) \
    $(wildcard include/config/x86/ptrace/bts.h) \
    $(wildcard include/config/paravirt.h) \
    $(wildcard include/config/x86/debugctlmsr.h) \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/processor-flags.h \
    $(wildcard include/config/vm86.h) \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/vm86.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/ptrace.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/ptrace-abi.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/segment.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/math_emu.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/sigcontext.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/current.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/percpu.h \
    $(wildcard include/config/x86/64/smp.h) \
  include/asm-generic/percpu.h \
    $(wildcard include/config/debug/preempt.h) \
    $(wildcard include/config/have/setup/per/cpu/area.h) \
  include/linux/threads.h \
    $(wildcard include/config/nr/cpus.h) \
    $(wildcard include/config/base/small.h) \
  include/linux/percpu-defs.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/cpufeature.h \
    $(wildcard include/config/x86/invlpg.h) \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/required-features.h \
    $(wildcard include/config/x86/minimum/cpu/family.h) \
    $(wildcard include/config/math/emulation.h) \
    $(wildcard include/config/x86/pae.h) \
    $(wildcard include/config/x86/cmpxchg64.h) \
    $(wildcard include/config/x86/cmov.h) \
    $(wildcard include/config/x86/use/3dnow.h) \
    $(wildcard include/config/x86/p6/nop.h) \
  include/linux/bitops.h \
    $(wildcard include/config/generic/find/first/bit.h) \
    $(wildcard include/config/generic/find/last/bit.h) \
    $(wildcard include/config/generic/find/next/bit.h) \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/bitops.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/alternative.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/asm.h \
  include/asm-generic/bitops/sched.h \
  include/asm-generic/bitops/hweight.h \
  include/asm-generic/bitops/fls64.h \
  include/asm-generic/bitops/ext2-non-atomic.h \
  include/asm-generic/bitops/le.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/byteorder.h \
  include/linux/byteorder/little_endian.h \
  include/linux/swab.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/swab.h \
    $(wildcard include/config/x86/bswap.h) \
  include/linux/byteorder/generic.h \
  include/asm-generic/bitops/minix.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/system.h \
    $(wildcard include/config/ia32/emulation.h) \
    $(wildcard include/config/x86/32/lazy/gs.h) \
    $(wildcard include/config/x86/ppro/fence.h) \
    $(wildcard include/config/x86/oostore.h) \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/cmpxchg.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/cmpxchg_32.h \
    $(wildcard include/config/x86/cmpxchg.h) \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/nops.h \
    $(wildcard include/config/mk7.h) \
  include/linux/kernel.h \
    $(wildcard include/config/preempt/voluntary.h) \
    $(wildcard include/config/debug/spinlock/sleep.h) \
    $(wildcard include/config/prove/locking.h) \
    $(wildcard include/config/printk.h) \
    $(wildcard include/config/dynamic/debug.h) \
    $(wildcard include/config/ring/buffer.h) \
    $(wildcard include/config/numa.h) \
    $(wildcard include/config/ftrace/mcount/record.h) \
  /home/lintel/openwrt-rdc/staging_dir/toolchain-i386_gcc-4.1.2_uClibc-0.9.30.1/usr/lib/gcc/i486-openwrt-linux-uclibc/4.1.2/include/stdarg.h \
  include/linux/linkage.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/linkage.h \
    $(wildcard include/config/x86/alignment/16.h) \
  include/linux/log2.h \
    $(wildcard include/config/arch/has/ilog2/u32.h) \
    $(wildcard include/config/arch/has/ilog2/u64.h) \
  include/linux/typecheck.h \
  include/linux/ratelimit.h \
  include/linux/param.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/param.h \
    $(wildcard include/config/hz.h) \
  include/linux/dynamic_debug.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/bug.h \
    $(wildcard include/config/bug.h) \
    $(wildcard include/config/debug/bugverbose.h) \
  include/asm-generic/bug.h \
    $(wildcard include/config/generic/bug/relative/pointers.h) \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/div64.h \
  include/linux/irqflags.h \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/irqsoff/tracer.h) \
    $(wildcard include/config/preempt/tracer.h) \
    $(wildcard include/config/trace/irqflags/support.h) \
    $(wildcard include/config/x86.h) \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/irqflags.h \
    $(wildcard include/config/debug/lock/alloc.h) \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/page.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/page_types.h \
  include/linux/const.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/page_32_types.h \
    $(wildcard include/config/highmem4g.h) \
    $(wildcard include/config/page/offset.h) \
    $(wildcard include/config/4kstacks.h) \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/page_32.h \
    $(wildcard include/config/hugetlb/page.h) \
    $(wildcard include/config/debug/virtual.h) \
    $(wildcard include/config/flatmem.h) \
    $(wildcard include/config/x86/3dnow.h) \
  include/linux/string.h \
    $(wildcard include/config/binary/printf.h) \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/string.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/string_32.h \
  include/asm-generic/memory_model.h \
    $(wildcard include/config/discontigmem.h) \
    $(wildcard include/config/sparsemem/vmemmap.h) \
    $(wildcard include/config/sparsemem.h) \
  include/asm-generic/page.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/pgtable_types.h \
    $(wildcard include/config/compat/vdso.h) \
    $(wildcard include/config/proc/fs.h) \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/pgtable_32_types.h \
    $(wildcard include/config/highmem.h) \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/pgtable-2level_types.h \
  include/asm-generic/pgtable-nopud.h \
  include/asm-generic/pgtable-nopmd.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/msr.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/msr-index.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/errno.h \
  include/asm-generic/errno.h \
  include/asm-generic/errno-base.h \
  include/linux/errno.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/desc_defs.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/ds.h \
  include/linux/err.h \
  include/linux/personality.h \
  include/linux/cpumask.h \
    $(wildcard include/config/disable/obsolete/cpumask/functions.h) \
    $(wildcard include/config/hotplug/cpu.h) \
    $(wildcard include/config/cpumask/offstack.h) \
    $(wildcard include/config/debug/per/cpu/maps.h) \
  include/linux/bitmap.h \
  include/linux/cache.h \
    $(wildcard include/config/arch/has/cache/line/size.h) \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/cache.h \
    $(wildcard include/config/x86/l1/cache/shift.h) \
  include/linux/stat.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/stat.h \
  include/linux/time.h \
  include/linux/seqlock.h \
  include/linux/spinlock.h \
    $(wildcard include/config/debug/spinlock.h) \
    $(wildcard include/config/generic/lockbreak.h) \
    $(wildcard include/config/preempt.h) \
  include/linux/preempt.h \
    $(wildcard include/config/preempt/notifiers.h) \
  include/linux/thread_info.h \
    $(wildcard include/config/compat.h) \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/thread_info.h \
    $(wildcard include/config/debug/stack/usage.h) \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/ftrace.h \
    $(wildcard include/config/function/tracer.h) \
    $(wildcard include/config/dynamic/ftrace.h) \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/atomic.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/atomic_32.h \
    $(wildcard include/config/m386.h) \
  include/asm-generic/atomic.h \
  include/linux/bottom_half.h \
  include/linux/spinlock_types.h \
  include/linux/spinlock_types_up.h \
  include/linux/lockdep.h \
    $(wildcard include/config/lockdep.h) \
    $(wildcard include/config/lock/stat.h) \
    $(wildcard include/config/generic/hardirqs.h) \
  include/linux/spinlock_up.h \
  include/linux/spinlock_api_up.h \
  include/linux/math64.h \
  include/linux/kmod.h \
  include/linux/gfp.h \
    $(wildcard include/config/zone/dma.h) \
    $(wildcard include/config/zone/dma32.h) \
  include/linux/mmzone.h \
    $(wildcard include/config/force/max/zoneorder.h) \
    $(wildcard include/config/unevictable/lru.h) \
    $(wildcard include/config/memory/hotplug.h) \
    $(wildcard include/config/arch/populates/node/map.h) \
    $(wildcard include/config/flat/node/mem/map.h) \
    $(wildcard include/config/cgroup/mem/res/ctlr.h) \
    $(wildcard include/config/have/memory/present.h) \
    $(wildcard include/config/need/node/memmap/size.h) \
    $(wildcard include/config/need/multiple/nodes.h) \
    $(wildcard include/config/have/arch/early/pfn/to/nid.h) \
    $(wildcard include/config/sparsemem/extreme.h) \
    $(wildcard include/config/nodes/span/other/nodes.h) \
    $(wildcard include/config/holes/in/zone.h) \
    $(wildcard include/config/arch/has/holes/memorymodel.h) \
  include/linux/wait.h \
  include/linux/numa.h \
    $(wildcard include/config/nodes/shift.h) \
  include/linux/nodemask.h \
  include/linux/pageblock-flags.h \
    $(wildcard include/config/hugetlb/page/size/variable.h) \
  include/linux/bounds.h \
  include/linux/memory_hotplug.h \
    $(wildcard include/config/have/arch/nodedata/extension.h) \
    $(wildcard include/config/memory/hotremove.h) \
  include/linux/notifier.h \
  include/linux/mutex.h \
    $(wildcard include/config/debug/mutexes.h) \
  include/linux/rwsem.h \
    $(wildcard include/config/rwsem/generic/spinlock.h) \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/rwsem.h \
  include/linux/srcu.h \
  include/linux/topology.h \
    $(wildcard include/config/sched/smt.h) \
    $(wildcard include/config/sched/mc.h) \
  include/linux/smp.h \
    $(wildcard include/config/use/generic/smp/helpers.h) \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/topology.h \
    $(wildcard include/config/x86/ht.h) \
    $(wildcard include/config/x86/64/acpi/numa.h) \
  include/asm-generic/topology.h \
  include/linux/elf.h \
  include/linux/elf-em.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/elf.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/user.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/user_32.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/auxvec.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/vdso.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/desc.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/ldt.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/mmu.h \
  include/linux/kobject.h \
  include/linux/sysfs.h \
  include/linux/kref.h \
  include/linux/moduleparam.h \
    $(wildcard include/config/alpha.h) \
    $(wildcard include/config/ia64.h) \
    $(wildcard include/config/ppc64.h) \
  include/linux/marker.h \
  include/linux/tracepoint.h \
  include/linux/rcupdate.h \
    $(wildcard include/config/classic/rcu.h) \
    $(wildcard include/config/tree/rcu.h) \
    $(wildcard include/config/preempt/rcu.h) \
  include/linux/completion.h \
  include/linux/rcuclassic.h \
    $(wildcard include/config/rcu/cpu/stall/detector.h) \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/local.h \
  include/linux/percpu.h \
    $(wildcard include/config/have/dynamic/per/cpu/area.h) \
  include/linux/slab.h \
    $(wildcard include/config/slab/debug.h) \
    $(wildcard include/config/debug/objects.h) \
    $(wildcard include/config/slub.h) \
    $(wildcard include/config/slob.h) \
    $(wildcard include/config/debug/slab.h) \
  include/linux/slab_def.h \
    $(wildcard include/config/kmemtrace.h) \
  include/trace/kmemtrace.h \
  include/linux/kmalloc_sizes.h \
  include/linux/pfn.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/module.h \
    $(wildcard include/config/m486.h) \
    $(wildcard include/config/m586.h) \
    $(wildcard include/config/m586tsc.h) \
    $(wildcard include/config/m586mmx.h) \
    $(wildcard include/config/mcore2.h) \
    $(wildcard include/config/m686.h) \
    $(wildcard include/config/mpentiumii.h) \
    $(wildcard include/config/mpentiumiii.h) \
    $(wildcard include/config/mpentiumm.h) \
    $(wildcard include/config/mpentium4.h) \
    $(wildcard include/config/mk6.h) \
    $(wildcard include/config/mk8.h) \
    $(wildcard include/config/x86/elan.h) \
    $(wildcard include/config/mcrusoe.h) \
    $(wildcard include/config/mefficeon.h) \
    $(wildcard include/config/mwinchipc6.h) \
    $(wildcard include/config/mwinchip3d.h) \
    $(wildcard include/config/mcyrixiii.h) \
    $(wildcard include/config/mviac3/2.h) \
    $(wildcard include/config/mviac7.h) \
    $(wildcard include/config/mgeodegx1.h) \
    $(wildcard include/config/mgeode/lx.h) \
  include/linux/i2c-id.h \
  include/linux/mod_devicetable.h \
  include/linux/device.h \
    $(wildcard include/config/debug/devres.h) \
  include/linux/ioport.h \
  include/linux/klist.h \
  include/linux/pm.h \
    $(wildcard include/config/pm/sleep.h) \
  include/linux/semaphore.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/device.h \
    $(wildcard include/config/acpi.h) \
    $(wildcard include/config/dmar.h) \
  include/linux/pm_wakeup.h \
    $(wildcard include/config/pm.h) \
  include/linux/sched.h \
    $(wildcard include/config/sched/debug.h) \
    $(wildcard include/config/no/hz.h) \
    $(wildcard include/config/detect/softlockup.h) \
    $(wildcard include/config/detect/hung/task.h) \
    $(wildcard include/config/core/dump/default/elf/headers.h) \
    $(wildcard include/config/bsd/process/acct.h) \
    $(wildcard include/config/taskstats.h) \
    $(wildcard include/config/audit.h) \
    $(wildcard include/config/inotify/user.h) \
    $(wildcard include/config/epoll.h) \
    $(wildcard include/config/posix/mqueue.h) \
    $(wildcard include/config/keys.h) \
    $(wildcard include/config/user/sched.h) \
    $(wildcard include/config/schedstats.h) \
    $(wildcard include/config/task/delay/acct.h) \
    $(wildcard include/config/fair/group/sched.h) \
    $(wildcard include/config/sched/cfs.h) \
    $(wildcard include/config/rt/group/sched.h) \
    $(wildcard include/config/sched/bfs.h) \
    $(wildcard include/config/blk/dev/io/trace.h) \
    $(wildcard include/config/sysvipc.h) \
    $(wildcard include/config/auditsyscall.h) \
    $(wildcard include/config/rt/mutexes.h) \
    $(wildcard include/config/task/xacct.h) \
    $(wildcard include/config/cpusets.h) \
    $(wildcard include/config/cgroups.h) \
    $(wildcard include/config/futex.h) \
    $(wildcard include/config/fault/injection.h) \
    $(wildcard include/config/latencytop.h) \
    $(wildcard include/config/function/graph/tracer.h) \
    $(wildcard include/config/have/unstable/sched/clock.h) \
    $(wildcard include/config/preempt/bkl.h) \
    $(wildcard include/config/group/sched.h) \
    $(wildcard include/config/mm/owner.h) \
  include/linux/capability.h \
    $(wildcard include/config/security/file/capabilities.h) \
  include/linux/timex.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/timex.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/tsc.h \
    $(wildcard include/config/x86/tsc.h) \
  include/linux/jiffies.h \
  include/linux/rbtree.h \
  include/linux/mm_types.h \
    $(wildcard include/config/split/ptlock/cpus.h) \
    $(wildcard include/config/want/page/debug/flags.h) \
    $(wildcard include/config/mmu.h) \
    $(wildcard include/config/mmu/notifier.h) \
  include/linux/auxvec.h \
  include/linux/prio_tree.h \
  include/linux/page-debug-flags.h \
    $(wildcard include/config/page/poisoning.h) \
    $(wildcard include/config/page/debug/something/else.h) \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/cputime.h \
  include/asm-generic/cputime.h \
  include/linux/sem.h \
  include/linux/ipc.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/ipcbuf.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/sembuf.h \
  include/linux/signal.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/signal.h \
  include/asm-generic/signal.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/siginfo.h \
  include/asm-generic/siginfo.h \
  include/linux/path.h \
  include/linux/pid.h \
  include/linux/proportions.h \
  include/linux/percpu_counter.h \
  include/linux/seccomp.h \
    $(wildcard include/config/seccomp.h) \
  include/linux/rtmutex.h \
    $(wildcard include/config/debug/rt/mutexes.h) \
  include/linux/plist.h \
    $(wildcard include/config/debug/pi/list.h) \
  include/linux/resource.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/resource.h \
  include/asm-generic/resource.h \
  include/linux/timer.h \
    $(wildcard include/config/timer/stats.h) \
    $(wildcard include/config/debug/objects/timers.h) \
  include/linux/ktime.h \
    $(wildcard include/config/ktime/scalar.h) \
  include/linux/debugobjects.h \
    $(wildcard include/config/debug/objects/free.h) \
  include/linux/hrtimer.h \
    $(wildcard include/config/high/res/timers.h) \
  include/linux/task_io_accounting.h \
    $(wildcard include/config/task/io/accounting.h) \
  include/linux/latencytop.h \
  include/linux/cred.h \
    $(wildcard include/config/security.h) \
  include/linux/key.h \
    $(wildcard include/config/sysctl.h) \
  include/linux/sysctl.h \
  include/linux/aio.h \
    $(wildcard include/config/aio.h) \
  include/linux/workqueue.h \
  include/linux/aio_abi.h \
  include/linux/uio.h \
  include/linux/i2c-gpio.h \
  include/linux/platform_device.h \
  include/linux/leds.h \
    $(wildcard include/config/leds/triggers.h) \
    $(wildcard include/config/leds/trigger/ide/disk.h) \
  include/linux/mtd/physmap.h \
    $(wildcard include/config/mtd/partitions.h) \
    $(wildcard include/config/mtd/cmdline/parts.h) \
  include/linux/mtd/mtd.h \
    $(wildcard include/config/mtd/debug.h) \
    $(wildcard include/config/mtd/debug/verbose.h) \
  include/linux/mtd/compatmac.h \
  include/mtd/mtd-abi.h \
  include/linux/mtd/partitions.h \
  include/linux/clocksource.h \
    $(wildcard include/config/clocksource/watchdog.h) \
    $(wildcard include/config/generic/time/vsyscall.h) \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/io.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/io_32.h \
  include/asm-generic/iomap.h \
  include/linux/vmalloc.h \
  include/linux/gpio_keys.h \
  include/linux/input.h \
  include/linux/fs.h \
    $(wildcard include/config/dnotify.h) \
    $(wildcard include/config/quota.h) \
    $(wildcard include/config/inotify.h) \
    $(wildcard include/config/debug/writecount.h) \
    $(wildcard include/config/file/locking.h) \
    $(wildcard include/config/block.h) \
    $(wildcard include/config/fs/xip.h) \
    $(wildcard include/config/migration.h) \
  include/linux/limits.h \
  include/linux/ioctl.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/ioctl.h \
  include/asm-generic/ioctl.h \
  include/linux/kdev_t.h \
  include/linux/dcache.h \
  include/linux/rculist.h \
  include/linux/radix-tree.h \
  include/linux/fiemap.h \
  include/linux/quota.h \
  include/linux/dqblk_xfs.h \
  include/linux/dqblk_v1.h \
  include/linux/dqblk_v2.h \
  include/linux/dqblk_qtree.h \
  include/linux/nfs_fs_i.h \
  include/linux/nfs.h \
  include/linux/sunrpc/msg_prot.h \
  include/linux/fcntl.h \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/fcntl.h \
  include/asm-generic/fcntl.h \
  include/linux/version.h \
  include/linux/mtd/map.h \
    $(wildcard include/config/mtd/map/bank/width/1.h) \
    $(wildcard include/config/mtd/map/bank/width/2.h) \
    $(wildcard include/config/mtd/map/bank/width/4.h) \
    $(wildcard include/config/mtd/map/bank/width/8.h) \
    $(wildcard include/config/mtd/map/bank/width/16.h) \
    $(wildcard include/config/mtd/map/bank/width/32.h) \
    $(wildcard include/config/mtd/map/bank/width/xx.h) \
    $(wildcard include/config/mtd/complex/mappings.h) \
  /home/lintel/openwrt-rdc/build_dir/linux-rdc/linux-2.6.30.10/arch/x86/include/asm/unaligned.h \
  include/linux/unaligned/access_ok.h \
  include/linux/unaligned/generic.h \
  include/linux/root_dev.h \
  include/linux/major.h \

arch/x86/mach-mgb100/setup.o: $(deps_arch/x86/mach-mgb100/setup.o)

$(deps_arch/x86/mach-mgb100/setup.o):
