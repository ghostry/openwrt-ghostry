/*
 * drivers/mtd/brcmnand/brcmnand.h
 *
 *  Copyright (c) 2005,2006 Broadcom Corp.
 *  
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 * Data structures for Broadcom NAND controller
 * 
 * when     who     what
 * 20060729 tht     Original coding
 */


#ifndef _BRCMNAND_PRIV_H_
#define _BRCMNAND_PRIV_H_

#include <linux/autoconf.h>
#include <linux/vmalloc.h>

#if 1
#include <bcmtypes.h>
#include <linux/mtd/brcmnand.h> 
#include <linux/mtd/bchp_nand.h>
#else /* TAKE OUT */
#include <asm/brcmstb/common/bcmtypes.h>
#include <linux/mtd/brcmnand.h> 
#include <asm/brcmstb/common/brcmstb.h>
#endif

#if defined( CONFIG_MTD_BRCMNAND_EDU )
#define BRCMNAND_malloc(size) kmalloc(size, GFP_DMA)
#define BRCMNAND_free(addr) kfree(addr)
#else
#define BRCMNAND_malloc(size) vmalloc(size)
#define BRCMNAND_free(addr) vfree(addr)
#endif

/**
 * brcmnand_scan - [BrcmNAND Interface] Scan for the BrcmNAND device
 * @param mtd       MTD device structure
 * @param maxchips  Number of chips to scan for
 *
 * This fills out all the not initialized function pointers
 * with the defaults.
 * The flash ID is read and the mtd/chip structures are
 * filled with the appropriate values.
 *
 * THT: For now, maxchips should always be 1.
 */
extern int brcmnand_scan(struct mtd_info *mtd , int maxchips );

/**
 * brcmnand_release - [BrcmNAND Interface] Free resources held by the
 *  BrcmNAND device
 * @param mtd       MTD device structure
 */
extern void brcmnand_release(struct mtd_info *mtd);

/* BrcmNAND BBT interface */
extern int brcmnand_scan_bbt(struct mtd_info *mtd, struct nand_bbt_descr *bd);
extern int brcmnand_default_bbt(struct mtd_info *mtd);

extern int brcmnand_update_bbt (struct mtd_info *mtd, loff_t offs);

extern void* get_brcmnand_handle(void);

extern void print_oobbuf(const unsigned char* buf, int len);
extern void print_databuf(const unsigned char* buf, int len);

#ifdef CONFIG_MTD_BRCMNAND_CORRECTABLE_ERR_HANDLING
extern int brcmnand_cet_update(struct mtd_info *mtd, loff_t from, int *status);
extern int brcmnand_cet_prepare_reboot(struct mtd_info *mtd);
extern int brcmnand_cet_erasecallback(struct mtd_info *mtd, u_int32_t addr);
extern int brcmnand_create_cet(struct mtd_info *mtd);
#endif

#endif
