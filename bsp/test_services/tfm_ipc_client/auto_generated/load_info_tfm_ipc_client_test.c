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
#include "psa_manifest/tfm_ipc_client_test.h"

#define TFM_SP_IPC_CLIENT_TEST_NDEPS                            (5)
#define TFM_SP_IPC_CLIENT_TEST_NSERVS                           (6)
#if TFM_LVL == 3
#define TFM_SP_IPC_CLIENT_TEST_NASSETS                          (0 + 1)
#else
#define TFM_SP_IPC_CLIENT_TEST_NASSETS                          (0)
#endif
#define TFM_SP_IPC_CLIENT_TEST_NIRQS                            (0)

/* Memory region declaration */
#if TFM_LVL == 3
REGION_DECLARE(Image$$, PT_TFM_SP_IPC_CLIENT_TEST_PRIVATE, _DATA_START$$Base);
REGION_DECLARE(Image$$, PT_TFM_SP_IPC_CLIENT_TEST_PRIVATE, _DATA_END$$Base);
#endif
extern uint8_t tfm_sp_ipc_client_test_stack[];

/* Entrypoint function declaration */
extern void ipc_client_test_main(void);

/* partition load info type definition */
struct partition_tfm_sp_ipc_client_test_load_info_t {
    /* common length load data */
    struct partition_load_info_t    load_info;
    /* per-partition variable length load data */
    uintptr_t                       stack_addr;
    uintptr_t                       heap_addr;
    uint32_t                        deps[TFM_SP_IPC_CLIENT_TEST_NDEPS];
    struct service_load_info_t      services[TFM_SP_IPC_CLIENT_TEST_NSERVS];
#if TFM_LVL == 3
    struct asset_desc_t             assets[TFM_SP_IPC_CLIENT_TEST_NASSETS];
#else
#endif
} __attribute__((aligned(4)));

/* Partition load, deps, service load data. Put to a dedicated section. */
const struct partition_tfm_sp_ipc_client_test_load_info_t tfm_sp_ipc_client_test_load
    __attribute__((used, section(".part_load"))) = {
    .load_info = {
        .psa_ff_ver                 = 0x0100 | PARTITION_INFO_MAGIC,
        .pid                        = TFM_SP_IPC_CLIENT_TEST,
        .flags                      = 0
                                    | SPM_PART_FLAG_IPC
                                    | PARTITION_PRI_NORMAL,
        .entry                      = ENTRY_TO_POSITION(ipc_client_test_main),
        .stack_size                 = 0x0300,
        .heap_size                  = 0,
        .ndeps                      = TFM_SP_IPC_CLIENT_TEST_NDEPS,
        .nservices                  = TFM_SP_IPC_CLIENT_TEST_NSERVS,
        .nassets                    = TFM_SP_IPC_CLIENT_TEST_NASSETS,
        .nirqs                      = TFM_SP_IPC_CLIENT_TEST_NIRQS,
    },
    .stack_addr                     = (uintptr_t)tfm_sp_ipc_client_test_stack,
    .heap_addr                      = 0,
    .deps = {
        IPC_SERVICE_TEST_PSA_ACCESS_APP_READ_ONLY_MEM_SID,
        IPC_SERVICE_TEST_PSA_ACCESS_APP_MEM_SID,
        IPC_SERVICE_TEST_BASIC_SID,
        IPC_SERVICE_TEST_APP_ACCESS_PSA_MEM_SID,
        TFM_SECURE_CLIENT_2_SID,
    },
    .services = {
        {
            .name_strid             = STRING_PTR_TO_STRID("IPC_CLIENT_TEST_BASIC"),
            .signal                 = IPC_CLIENT_TEST_BASIC_SIGNAL,
            .sid                    = 0x0000F060,
            .flags                  = 0
                                    | SERVICE_FLAG_NS_ACCESSIBLE
                                    | SERVICE_VERSION_POLICY_STRICT,
            .version                = 1,
        },
        {
            .name_strid             = STRING_PTR_TO_STRID("IPC_CLIENT_TEST_PSA_ACCESS_APP_MEM"),
            .signal                 = IPC_CLIENT_TEST_PSA_ACCESS_APP_MEM_SIGNAL,
            .sid                    = 0x0000F061,
            .flags                  = 0
                                    | SERVICE_FLAG_NS_ACCESSIBLE
                                    | SERVICE_VERSION_POLICY_STRICT,
            .version                = 1,
        },
        {
            .name_strid             = STRING_PTR_TO_STRID("IPC_CLIENT_TEST_PSA_ACCESS_APP_READ_ONLY_MEM"),
            .signal                 = IPC_CLIENT_TEST_PSA_ACCESS_APP_READ_ONLY_MEM_SIGNAL,
            .sid                    = 0x0000F062,
            .flags                  = 0
                                    | SERVICE_FLAG_NS_ACCESSIBLE
                                    | SERVICE_VERSION_POLICY_STRICT,
            .version                = 1,
        },
        {
            .name_strid             = STRING_PTR_TO_STRID("IPC_CLIENT_TEST_APP_ACCESS_PSA_MEM"),
            .signal                 = IPC_CLIENT_TEST_APP_ACCESS_PSA_MEM_SIGNAL,
            .sid                    = 0x0000F063,
            .flags                  = 0
                                    | SERVICE_FLAG_NS_ACCESSIBLE
                                    | SERVICE_VERSION_POLICY_STRICT,
            .version                = 1,
        },
        {
            .name_strid             = STRING_PTR_TO_STRID("IPC_CLIENT_TEST_MEM_CHECK"),
            .signal                 = IPC_CLIENT_TEST_MEM_CHECK_SIGNAL,
            .sid                    = 0x0000F064,
            .flags                  = 0
                                    | SERVICE_FLAG_NS_ACCESSIBLE
                                    | SERVICE_VERSION_POLICY_STRICT,
            .version                = 1,
        },
        {
            .name_strid             = STRING_PTR_TO_STRID("IPC_CLIENT_TEST_RETRIEVE_APP_MEM"),
            .signal                 = IPC_CLIENT_TEST_RETRIEVE_APP_MEM_SIGNAL,
            .sid                    = 0x0000F065,
            .flags                  = 0
                                    | SERVICE_FLAG_NS_ACCESSIBLE
                                    | SERVICE_VERSION_POLICY_STRICT,
            .version                = 1,
        },
    },
#if TFM_LVL == 3
    .assets                         = {
        {
            .mem.addr_x             = PART_REGION_ADDR(PT_TFM_SP_IPC_CLIENT_TEST_PRIVATE, _DATA_START$$Base),
            .mem.addr_y             = PART_REGION_ADDR(PT_TFM_SP_IPC_CLIENT_TEST_PRIVATE, _DATA_END$$Base),
            .attr                   = ASSET_MEM_RD_BIT | ASSET_MEM_WR_BIT,
        },
    },
#else
#endif
};

/* Placeholder for partition and service runtime space. Do not reference it. */
static struct partition_t tfm_sp_ipc_client_test_partition_runtime_item
    __attribute__((used, section(".bss.part_runtime")));
static struct service_t tfm_sp_ipc_client_test_service_runtime_item[TFM_SP_IPC_CLIENT_TEST_NSERVS]
    __attribute__((used, section(".bss.serv_runtime")));
