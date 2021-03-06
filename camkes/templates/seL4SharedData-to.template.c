/*#
 *# Copyright 2014, NICTA
 *#
 *# This software may be distributed and modified according to the terms of
 *# the BSD 2-Clause license. Note that NO WARRANTY is provided.
 *# See "LICENSE_BSD2.txt" for details.
 *#
 *# @TAG(NICTA_BSD)
 #*/

#include <camkes/dataport.h>
#include <stdlib.h>

/*? macros.show_includes(me.to_instance.type.includes) ?*/

/*- set p = Perspective(dataport=me.to_interface.name) -*/
#define SHM_ALIGN (1 << 12)
struct {
    char content[ROUND_UP_UNSAFE(sizeof(/*? show(me.to_interface.type) ?*/),
        PAGE_SIZE_4K)];
} /*? p['dataport_symbol'] ?*/
        __attribute__((aligned(SHM_ALIGN)))
        __attribute__((section("shared_/*? me.to_interface.name ?*/")))
        __attribute__((externally_visible));
/*- do register_shared_variable('%s_data' % me.name, p['dataport_symbol']) -*/

volatile /*? show(me.to_interface.type) ?*/ * /*? me.to_interface.name ?*/ =
    (volatile /*? show(me.to_interface.type) ?*/ *) & /*? p['dataport_symbol'] ?*/;

int /*? me.to_interface.name ?*/__run(void) {
    /* Nothing required. */
    return 0;
}

int /*? me.to_interface.name ?*/_wrap_ptr(dataport_ptr_t *p, void *ptr) {
    if ((uintptr_t)ptr < (uintptr_t)/*? me.to_interface.name ?*/ ||
            (uintptr_t)ptr >= (uintptr_t)/*? me.to_interface.name ?*/ + sizeof(/*? show(me.to_interface.type) ?*/)) {
        return -1;
    }
    p->id = /*? id ?*/;
    p->offset =  (off_t)((uintptr_t)ptr - (uintptr_t)/*? me.to_interface.name ?*/);
    return 0;
}

void * /*? me.to_interface.name ?*/_unwrap_ptr(dataport_ptr_t *p) {
    if (p->id == /*? id ?*/) {
        return (void*)((uintptr_t)/*? me.to_interface.name ?*/ + (uintptr_t)p->offset);
    } else {
        return NULL;
    }
}
