/* Copyright (C) 1989, 1990, 1991, 1993, 1994 Aladdin Enterprises.  All rights reserved.
  
  This file is part of Aladdin Ghostscript.
  
  Aladdin Ghostscript is distributed with NO WARRANTY OF ANY KIND.  No author
  or distributor accepts any responsibility for the consequences of using it,
  or for whether it serves any particular purpose or works at all, unless he
  or she says so in writing.  Refer to the Aladdin Ghostscript Free Public
  License (the "License") for full details.
  
  Every copy of Aladdin Ghostscript must include a copy of the License,
  normally in a plain ASCII text file named PUBLIC.  The License grants you
  the right to copy, modify and redistribute Aladdin Ghostscript, but only
  under certain conditions described in the License.  Among other things, the
  License requires that the copyright notice and this notice be preserved on
  all copies.
*/

/* ialloc.h */
/* Interface to Ghostscript interpreter memory allocator */

#ifndef ialloc_INCLUDED
#  define ialloc_INCLUDED

#include "imemory.h"

/*
 * Define the interpreter memory manager instance.
 */
extern gs_dual_memory_t gs_imemory;
#define idmemory (&gs_imemory)
#define iimemory (gs_imemory.current)
#define imemory ((gs_memory_t *)iimemory)
#define iimemory_local (gs_imemory.space_local)
#define imemory_local ((gs_memory_t *)iimemory_local)
#define iimemory_global (gs_imemory.space_global)
#define imemory_global ((gs_memory_t *)iimemory_global)
#define iimemory_system (gs_imemory.space_system)
#define imemory_system ((gs_memory_t *)iimemory_system)

/*
 * Aliases for invoking the standard allocator interface.
 */
#define ialloc_bytes(nbytes, cname)\
  gs_alloc_bytes(imemory, nbytes, cname)
#define ialloc_struct(typ, pstype, cname)\
  gs_alloc_struct(imemory, typ, pstype, cname)
#define ialloc_byte_array(nelts, esize, cname)\
  gs_alloc_byte_array(imemory, nelts, esize, cname)
#define ialloc_struct_array(nelts, typ, pstype, cname)\
  gs_alloc_struct_array(imemory, nelts, typ, pstype, cname)
#define ifree_object(data, cname)\
  gs_free_object(imemory, data, cname)
#define ialloc_string(nbytes, cname)\
  gs_alloc_string(imemory, nbytes, cname)
#define ifree_string(data, nbytes, cname)\
  gs_free_string(imemory, data, nbytes, cname)

/* Initialize the interpreter's allocator. */
void ialloc_init(P3(gs_memory_t *, uint, bool));

/* Resize a string. */
#define iresize_string(data, oldn, newn, cname)\
  gs_resize_string(imemory, data, oldn, newn, cname)

/* ------ Internal routines ------ */

/* Initialize after a save. */
void ialloc_reset(P1(gs_ref_memory_t *));

/* Initialize after a save or GC. */
void ialloc_reset_free(P1(gs_ref_memory_t *));

/* Set the cached allocation limit of an alloctor from its GC parameters. */
void ialloc_set_limit(P1(gs_ref_memory_t *));

/* Reset the request values that identify the cause of a GC. */
void ialloc_reset_requested(P1(gs_dual_memory_t *));

/*
 * Local/global VM management.
 */

/* Get the space attribute of the current allocator. */
#define ialloc_space(dmem) ((dmem)->current_space)
#define icurrent_space ialloc_space(idmemory)
extern uint imemory_space(P1(gs_ref_memory_t *));

/* Select the allocation space. */
void ialloc_set_space(P2(gs_dual_memory_t *, uint));

/*
 * Ref-related facilities.
 */

#ifdef r_type				/* i.e., we know about refs */

/* Allocate and free ref arrays. */
#define ialloc_ref_array(paref, attrs, nrefs, cname)\
  gs_alloc_ref_array(iimemory, paref, attrs, nrefs, cname)
#define iresize_ref_array(paref, nrefs, cname)\
  gs_resize_ref_array(iimemory, paref, nrefs, cname)
#define ifree_ref_array(paref, cname)\
  gs_free_ref_array(iimemory, paref, cname)

/* Allocate a string ref. */
#define ialloc_string_ref(psref, attrs, nbytes, cname)\
  gs_alloc_string_ref(iimemory, psref, attrs, nbytes, cname)

/* Make a ref for a newly allocated structure. */
#define make_istruct(pref,attrs,ptr)\
  make_struct(pref, (attrs) | icurrent_space, ptr)
#define make_istruct_new(pref,attrs,ptr)\
  make_struct_new(pref, (attrs) | icurrent_space, ptr)
#define make_iastruct(pref,attrs,ptr)\
  make_astruct(pref, (attrs) | icurrent_space, ptr)
#define make_iastruct_new(pref,attrs,ptr)\
  make_astruct_new(pref, (attrs) | icurrent_space, ptr)

#endif					/* ifdef r_type */

#endif					/* ialloc_INCLUDED */
