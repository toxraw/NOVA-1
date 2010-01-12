/*
 * I/O Advanced Programmable Interrupt Controller (I/O APIC)
 *
 * Copyright (C) 2006-2009, Udo Steinberg <udo@hypervisor.org>
 *
 * This file is part of the NOVA microhypervisor.
 *
 * NOVA is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * NOVA is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License version 2 for more details.
 */

#include "ioapic.h"
#include "pd.h"
#include "stdio.h"

Slab_cache Ioapic::cache (sizeof (Ioapic), 8);

Ioapic::Ioapic (Paddr phys) : reg_base ((hwdev_addr -= PAGE_SIZE) | (phys & PAGE_MASK))
{
    Pd::kern.Space_mem::insert (hwdev_addr, 0,
                                Ptab::Attribute (Ptab::ATTR_NOEXEC      |
                                                 Ptab::ATTR_GLOBAL      |
                                                 Ptab::ATTR_UNCACHEABLE |
                                                 Ptab::ATTR_WRITABLE),
                                phys & ~PAGE_MASK);

    trace (TRACE_APIC, "APIC:%#lx ID:%#x VER:%#x IRT:%#x PRQ:%u",
           phys, id(), version(), irt_max(), prq());
}
