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
#include "psa_manifest/tfm_ss_core_test.h"

#define TFM_SP_CORE_TEST_NDEPS                                  (3)
#define TFM_SP_CORE_TEST_NSERVS                                 (10)
#if TFM_LVL == 3
#define TFM_SP_CORE_TEST_NASSETS                                (1 + 1)
#else
#define TFM_SP_CORE_TEST_NASSETS                                (1)
#endif
#define TFM_SP_CORE_TEST_NIRQS                                  (0)

/* Memory region declaration */
#if TFM_LVL == 3
REGION_DECLARE(Image$$, PT_TFM_SP_CORE_TEST_PRIVATE, _DATA_START$$Base);
REGION_DECLARE(Image$$, PT_TFM_SP_CORE_TEST_PRIVATE, _DATA_END$$Base);
#endif
extern uint8_t tfm_sp_core_test_stack[];

/* Entrypoint function declaration */
extern void core_test_init(void);

/* partition load info type definition */
struct partition_tfm_sp_core_test_load_info_t {
    /* common length load data */
    struct partition_load_info_t    load_info;
    /* per-partition variable length load data */
    uintptr_t                       stack_addr;
    uintptr_t                       heap_addr;
    uint32_t                        deps[TFM_SP_CORE_TEST_NDEPS];
    struct service_load_info_t      services[TFM_SP_CORE_TEST_NSERVS];
#if TFM_LVL == 3
    struct asset_desc_t             assets[TFM_SP_CORE_TEST_NASSETS];
#else
    struct asset_desc_t             assets[TFM_SP_CORE_TEST_NASSETS];
#endif
} __attribute__((aligned(4)));

/* Partition load, deps, service load data. Put to a dedicated section. */
const struct partition_tfm_sp_core_test_load_info_t tfm_sp_core_test_load
    __attribute__((used, section(".part_load"))) = {
    .load_info = {
        .psa_ff_ver                 = 0x0100 | PARTITION_INFO_MAGIC,
        .pid                        = TFM_SP_CORE_TEST,
        .flags                      = 0
                                    | SPM_PART_FLAG_IPC
                                    | SPM_PART_FLAG_PSA_ROT
                                    | PARTITION_PRI_NORMAL,
        .entry                      = ENTRY_TO_POSITION(core_test_init),
        .stack_size                 = 0x0380,
        .heap_size                  = 0,
        .ndeps                      = TFM_SP_CORE_TEST_NDEPS,
        .nservices                  = TFM_SP_CORE_TEST_NSERVS,
        .nassets                    = TFM_SP_CORE_TEST_NASSETS,
        .nirqs                      = TFM_SP_CORE_TEST_NIRQS,
    },
    .stack_addr                     = (uintptr_t)tfm_sp_core_test_stack,
    .heap_addr                      = 0,
    .deps = {
        SPM_CORE_TEST_2_INVERT_SID,
        SPM_CORE_TEST_2_GET_EVERY_SECOND_BYTE_SID,
        SPM_CORE_TEST_2_SLAVE_SERVICE_SID,
    },
    .services = {
        {
            .name_strid             = STRING_PTR_TO_STRID("SPM_CORE_TEST_INIT_SUCCESS"),
            .signal                 = SPM_CORE_TEST_INIT_SUCCESS_SIGNAL,
            .sid                    = 0x0000F020,
            .flags                  = 0
                                    | SERVICE_FLAG_NS_ACCESSIBLE
                                    | SERVICE_VERSION_POLICY_STRICT,
            .version                = 1,
        },
        {
            .name_strid             = STRING_PTR_TO_STRID("SPM_CORE_TEST_DIRECT_RECURSION"),
            .signal                 = SPM_CORE_TEST_DIRECT_RECURSION_SIGNAL,
            .sid                    = 0x0000F021,
            .flags                  = 0
                                    | SERVICE_FLAG_NS_ACCESSIBLE
                                    | SERVICE_VERSION_POLICY_STRICT,
            .version                = 1,
        },
        {
            .name_strid             = STRING_PTR_TO_STRID("SPM_CORE_TEST_SS_TO_SS"),
            .signal                 = SPM_CORE_TEST_SS_TO_SS_SIGNAL,
            .sid                    = 0x0000F024,
            .flags                  = 0
                                    | SERVICE_FLAG_NS_ACCESSIBLE
                                    | SERVICE_VERSION_POLICY_STRICT,
            .version                = 1,
        },
        {
            .name_strid             = STRING_PTR_TO_STRID("SPM_CORE_TEST_SS_TO_SS_BUFFER"),
            .signal                 = SPM_CORE_TEST_SS_TO_SS_BUFFER_SIGNAL,
            .sid                    = 0x0000F025,
            .flags                  = 0
                                    | SERVICE_FLAG_NS_ACCESSIBLE
                                    | SERVICE_VERSION_POLICY_STRICT,
            .version                = 1,
        },
        {
            .name_strid             = STRING_PTR_TO_STRID("SPM_CORE_TEST_OUTVEC_WRITE"),
            .signal                 = SPM_CORE_TEST_OUTVEC_WRITE_SIGNAL,
            .sid                    = 0x0000F026,
            .flags                  = 0
                                    | SERVICE_FLAG_NS_ACCESSIBLE
                                    | SERVICE_VERSION_POLICY_STRICT,
            .version                = 1,
        },
        {
            .name_strid             = STRING_PTR_TO_STRID("SPM_CORE_TEST_PERIPHERAL_ACCESS"),
            .signal                 = SPM_CORE_TEST_PERIPHERAL_ACCESS_SIGNAL,
            .sid                    = 0x0000F027,
            .flags                  = 0
                                    | SERVICE_FLAG_NS_ACCESSIBLE
                                    | SERVICE_VERSION_POLICY_STRICT,
            .version                = 1,
        },
        {
            .name_strid             = STRING_PTR_TO_STRID("SPM_CORE_TEST_GET_CALLER_CLIENT_ID"),
            .signal                 = SPM_CORE_TEST_GET_CALLER_CLIENT_ID_SIGNAL,
            .sid                    = 0x0000F028,
            .flags                  = 0
                                    | SERVICE_FLAG_NS_ACCESSIBLE
                                    | SERVICE_VERSION_POLICY_STRICT,
            .version                = 1,
        },
        {
            .name_strid             = STRING_PTR_TO_STRID("SPM_CORE_TEST_SPM_REQUEST"),
            .signal                 = SPM_CORE_TEST_SPM_REQUEST_SIGNAL,
            .sid                    = 0x0000F029,
            .flags                  = 0
                                    | SERVICE_FLAG_NS_ACCESSIBLE
                                    | SERVICE_VERSION_POLICY_STRICT,
            .version                = 1,
        },
        {
            .name_strid             = STRING_PTR_TO_STRID("SPM_CORE_TEST_BLOCK"),
            .signal                 = SPM_CORE_TEST_BLOCK_SIGNAL,
            .sid                    = 0x0000F02A,
            .flags                  = 0
                                    | SERVICE_FLAG_NS_ACCESSIBLE
                                    | SERVICE_VERSION_POLICY_STRICT,
            .version                = 1,
        },
        {
            .name_strid             = STRING_PTR_TO_STRID("SPM_CORE_TEST_NS_THREAD"),
            .signal                 = SPM_CORE_TEST_NS_THREAD_SIGNAL,
            .sid                    = 0x0000F02B,
            .flags                  = 0
                                    | SERVICE_FLAG_NS_ACCESSIBLE
                                    | SERVICE_VERSION_POLICY_STRICT,
            .version                = 1,
        },
    },
#if TFM_LVL == 3
    .assets                         = {
        {
            .mem.addr_x             = PART_REGION_ADDR(PT_TFM_SP_CORE_TEST_PRIVATE, _DATA_START$$Base),
            .mem.addr_y             = PART_REGION_ADDR(PT_TFM_SP_CORE_TEST_PRIVATE, _DATA_END$$Base),
            .attr                   = ASSET_MEM_RD_BIT | ASSET_MEM_WR_BIT,
        },
        {
            .dev.addr_ref           = PTR_TO_REFERENCE(TFM_PERIPHERAL_FPGA_IO),
            .attr                   = ASSET_DEV_REF_BIT,
        },
    },
#else
    .assets                         = {
        {
            .dev.addr_ref           = PTR_TO_REFERENCE(TFM_PERIPHERAL_FPGA_IO),
            .attr                   = ASSET_DEV_REF_BIT,
        },
    },
#endif
};

/* Placeholder for partition and service runtime space. Do not reference it. */
static struct partition_t tfm_sp_core_test_partition_runtime_item
    __attribute__((used, section(".bss.part_runtime")));
static struct service_t tfm_sp_core_test_service_runtime_item[TFM_SP_CORE_TEST_NSERVS]
    __attribute__((used, section(".bss.serv_runtime")));
