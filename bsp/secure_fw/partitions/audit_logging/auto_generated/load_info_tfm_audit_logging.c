/*
 * Copyright (c) 2021, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

/*********** WARNING: This is an auto-generated file. Do not edit! ***********/

#include <stdint.h>
#include <stddef.h>
#include "region.h"
#include "spm_ipc.h"
#include "load/irq_defs.h"
#include "load/partition_defs.h"
#include "load/service_defs.h"
#include "load/asset_defs.h"
#include "tfm_peripherals_def.h"
#include "psa_manifest/pid.h"
#include "psa_manifest/sid.h"
#include "psa_manifest/tfm_audit_logging.h"

#define TFM_SP_AUDIT_LOG_NDEPS                                  (0)
#define TFM_SP_AUDIT_LOG_NSERVS                                 (0)
#if TFM_LVL == 3
#define TFM_SP_AUDIT_LOG_NASSETS                                (1 + 1)
#else
#define TFM_SP_AUDIT_LOG_NASSETS                                (1)
#endif
#define TFM_SP_AUDIT_LOG_NIRQS                                  (0)

/* Memory region declaration */
#if TFM_LVL == 3
REGION_DECLARE(Image$$, PT_TFM_SP_AUDIT_LOG_PRIVATE, _DATA_START$$Base);
REGION_DECLARE(Image$$, PT_TFM_SP_AUDIT_LOG_PRIVATE, _DATA_END$$Base);
#endif
extern uint8_t tfm_sp_audit_log_stack[];

/* Entrypoint function declaration */
extern void audit_core_init(void);

/* partition load info type definition */
struct partition_tfm_sp_audit_log_load_info_t {
    /* common length load data */
    struct partition_load_info_t    load_info;
    /* per-partition variable length load data */
    uintptr_t                       stack_addr;
    uintptr_t                       heap_addr;
#if TFM_LVL == 3
    struct asset_desc_t             assets[TFM_SP_AUDIT_LOG_NASSETS];
#else
    struct asset_desc_t             assets[TFM_SP_AUDIT_LOG_NASSETS];
#endif
} __attribute__((aligned(4)));

/* Partition load, deps, service load data. Put to a dedicated section. */
const struct partition_tfm_sp_audit_log_load_info_t tfm_sp_audit_log_load
    __attribute__((used, section(".part_load"))) = {
    .load_info = {
        .psa_ff_ver                 = 0x0100 | PARTITION_INFO_MAGIC,
        .pid                        = TFM_SP_AUDIT_LOG,
        .flags                      = 0
                                    | SPM_PART_FLAG_IPC
                                    | SPM_PART_FLAG_PSA_ROT
                                    | PARTITION_PRI_NORMAL,
        .entry                      = ENTRY_TO_POSITION(audit_core_init),
        .stack_size                 = 0x0200,
        .heap_size                  = 0,
        .ndeps                      = TFM_SP_AUDIT_LOG_NDEPS,
        .nservices                  = TFM_SP_AUDIT_LOG_NSERVS,
        .nassets                    = TFM_SP_AUDIT_LOG_NASSETS,
        .nirqs                      = TFM_SP_AUDIT_LOG_NIRQS,
    },
    .stack_addr                     = (uintptr_t)tfm_sp_audit_log_stack,
    .heap_addr                      = 0,
#if TFM_LVL == 3
    .assets                         = {
        {
            .mem.addr_x             = PART_REGION_ADDR(PT_TFM_SP_AUDIT_LOG_PRIVATE, _DATA_START$$Base),
            .mem.addr_y             = PART_REGION_ADDR(PT_TFM_SP_AUDIT_LOG_PRIVATE, _DATA_END$$Base),
            .attr                   = ASSET_MEM_RD_BIT | ASSET_MEM_WR_BIT,
        },
#ifdef AUDIT_UART_REDIRECTION
        {
            .dev.addr_ref           = PTR_TO_REFERENCE(TFM_PERIPHERAL_UART1),
            .attr                   = ASSET_DEV_REF_BIT,
        },
#endif
    },
#else
    .assets                         = {
#ifdef AUDIT_UART_REDIRECTION
        {
            .dev.addr_ref           = PTR_TO_REFERENCE(TFM_PERIPHERAL_UART1),
            .attr                   = ASSET_DEV_REF_BIT,
        },
#endif
    },
#endif
};

/* Placeholder for partition and service runtime space. Do not reference it. */
static struct partition_t tfm_sp_audit_log_partition_runtime_item
    __attribute__((used, section(".bss.part_runtime")));
