#ifndef XSAL_APPLICATION_ID_H
#   define XSAL_APPLICATION_ID_H
/*===========================================================================*/
/**
 * @file xsal_application_id.h
 *
 * This file defines the system wide application ids for aa1024ae. Its contents are
 * unique to a given system.
 *
 * %full_filespec:xsal_application_id.h~0.1 %
 * @version %version:0.1 %
 * @author  %derived_by:wentao %
 * @date    %date_modified:Fri Oct 23 16:26:45 2020 %
 *
 *------------------------------------------------------------------------------
 *
 * Copyright 2020 Whyte Technologies, Inc., All Rights Reserved.
 * Whyte Confidential
 *
 *------------------------------------------------------------------------------
 *
 * @ingroup xsal_data_types_grp
 * @{
 */
/*==========================================================================*/

/**
 * Uses X MACROs to define the enumeration tags and names for the system's
 * application ids.
 */
#   define SAL_APPLICATION_IDS\
    X(APP_PROCMAN           ,    "procman"                 ) /*  1 - PROCMAN must be first */ \
    X(EARLY_START_PROCESS_ID,    "Early Start Process"     ) /*  2  */ \
    X(SBX_PROCESS_ID        ,    "silver box Main Process" ) /*  3  */ \
    X(BT_CM_PROCESS_ID,          "Bluetooth Daemon"        ) /*  4  */ \
    X(WIFI_PROCESS_ID,           "wifi Daemon"             ) /*  5  */ \
    X(SPEECH_MGR_PROCESS_ID,     "Speech manager"          ) /*  6  */ \
    X(MEDIA_PROCESS_ID     ,     "MEDIA Process"           ) /*  7  */ \
    X(TOUCH_PROCESS_ID,          "Touch Process"           ) /*  8  */ \
    X(APS_CORE_PROCESS_ID,       "APS_Core"                ) /*  9  */ \
    X(SECURITY_MGR_PROCESS_ID,   "Security_Mgr_PROCESS"    ) /*  10  */\
    X(CONSOLE_APP_PROCESS_ID,    "Console Functional Test" ) /*  11  */\
    X(APP_ECD,                   "ecd process"             ) /*  12  */\
    X(PKI_PROCESS_ID,            "PKI process"             ) /*  13 */ \
    X(APP_DSPLOGGER ,            "dsplogger"               ) /*  14  */\
    X(APP_MCORE_LOGGER ,         "Mcorelogger"             ) /*  15  */\
	X(APP_VDSPLOGGER ,           "VDSPlogger"              ) /*  15  */\
	X(FLASH_SERVICE_PROCESS_ID , "FlashService"            ) /*  16  */\
	X(TBOX_TEST_PROCESS_ID ,     "TBox TestApp"            ) /*  18  */\
	X(TBOX_SERVICE_PROCESS_ID,   "TBoxService process"     ) /*  19  */\
	X(CGM_TEST_PROCESS_ID,       "CGM TestApp"             ) /*  20  */\


#   undef X
#   define X(a,b) a, /* Create list of enumeration tags */
/**
 * Each application (process) that needs to use XSAL messaging must have
 * a unique "application id". This "app id" is part of the "addressing
 * mechanism" for sending messages between applications. The list of
 * app ids is unique to a system. This enumeration assigns values to the
 * application ids.
 *
 * @note Application IDs must be greater than 0.
 */
typedef enum SAL_Application_Id_Tag
{
   SAL_NO_APP_ID = 0,

   SAL_APPLICATION_IDS

   SAL_LAST_APP_ID
}
SAL_Application_Id_T;

#   undef X

/*
 * Assign process ids to individual modules:
 */
#   define XSAL_TIMER_APP_ID                                APP_PROCMAN

#   define ANIMATED_SPLASH_APP_ID                           EARLY_START_PROCESS_ID
#   define ES_APM_APP_ID                                    EARLY_START_PROCESS_ID
#   define ES_XSALMT_APP_ID                                 EARLY_START_PROCESS_ID
#   define CHIMES_APP_ID                                    EARLY_START_PROCESS_ID
#   define GMLAN_INTERFACE_PROCESS_ID                       EARLY_START_PROCESS_ID
#   define SOH_APP_ID                                       EARLY_START_PROCESS_ID
#   define VIP_APP_ID                                       EARLY_START_PROCESS_ID
#   define VIDEO_CONTROL_APP_ID                             EARLY_START_PROCESS_ID
#   define LAYER_MANAGER_APP_ID                             EARLY_START_PROCESS_ID
#   define PS_APP_ID                                        EARLY_START_PROCESS_ID
#   define LAYERMANAGER_APP_ID                              EARLY_START_PROCESS_ID
#   define XENA_PROCESS_ID                                  EARLY_START_PROCESS_ID
#   define CALS_APP_ID                                  	EARLY_START_PROCESS_ID
#   define HISIP_AP_NODE_RX_APP_ID                 			EARLY_START_PROCESS_ID
#   define HISIP_M4_NODE_RX_APP_ID                 			EARLY_START_PROCESS_ID
#   define BEV_SOCKET_SERVER_APP_ID                 		EARLY_START_PROCESS_ID

#   define AJE_APP_ID                                       SBX_PROCESS_ID
#   define ALLGO_GATEWAY_APP_ID                             SBX_PROCESS_ID
#   define APM_APP_ID                                       SBX_PROCESS_ID
#   define APP_MOST                                         SBX_PROCESS_ID
#   define APP_XSALCPP                                      SBX_PROCESS_ID
#   define ASR_MGR_APP_ID                                   SBX_PROCESS_ID
#   define AUDIO_TASK_APP_ID                                SBX_PROCESS_ID
#   define AUMGR_TASK_APP_ID                                SBX_PROCESS_ID
#   define AUMUTEMGR_TASK_APP_ID                            SBX_PROCESS_ID
#   define BTSTRM_VPD_APP_ID                                SBX_PROCESS_ID
#   define CONNECTION_MANAGER_APP_ID                        SBX_PROCESS_ID
#   define DAB_APP_ID                                       SBX_PROCESS_ID
#   define DIMMING_APP_ID                                   SBX_PROCESS_ID
#   define DIAG_CLIENTS_HANDLER_APP_ID                      SBX_PROCESS_ID
#   define DAJE_APP_ID                                      SBX_PROCESS_ID
#   define FBL_LINKER_APP_ID                                SBX_PROCESS_ID
#   define GM_DIAG_HANDLER_PROCESS_ID                       SBX_PROCESS_ID
#   define GPS_APP_ID                                       SBX_PROCESS_ID
#   define DR_APP_ID                                        SBX_PROCESS_ID
#   define IPODE_APP_ID                                     SBX_PROCESS_ID
#   define LVME_APP_ID                                      SBX_PROCESS_ID
#   define MSDE_APP_ID                                      SBX_PROCESS_ID
#   define HDE_APP_ID                                       SBX_PROCESS_ID
#   define CDE_APP_ID                                       SBX_PROCESS_ID
#   define RTP_APP_ID                                       SBX_PROCESS_ID
#   define SM_APP_ID                                        SBX_PROCESS_ID
#   define SDE_APP_ID                                       SBX_PROCESS_ID
#   define MSM_APP_ID                                       SBX_PROCESS_ID
#   define MTPAS_APP_ID                                     SBX_PROCESS_ID
#   define MTPE_APP_ID                                      SBX_PROCESS_ID
#   define PITS_APP_ID                                      SBX_PROCESS_ID
#   define SCREEN_CHECK_APP_ID                              SBX_PROCESS_ID
#   define SINAD_APP_ID                                     SBX_PROCESS_ID
#   define PPE_APP_ID                                       SBX_PROCESS_ID
#   define PROMPT_MGR_APP_ID                                SBX_PROCESS_ID
#   define SSND_APP_ID                                      SBX_PROCESS_ID
#   define RSE_APP_ID                                       SBX_PROCESS_ID
#   define TIMESHIFT_MANAGER_APP_ID                         SBX_PROCESS_ID
#   define TMC_TUNER_APP_ID                                 SBX_PROCESS_ID
/*Tuner*/
#   define TUNER_SOCKETSERVER_APP_ID                        SBX_PROCESS_ID
#   define TUNER_MGR_APP_ID                                 SBX_PROCESS_ID
#   define AMFM_APP_ID                 						SBX_PROCESS_ID
#   define AMFM_BGND_TASK_APP_ID       						SBX_PROCESS_ID
#   define RDS_DEC_APP_ID        							SBX_PROCESS_ID
/*****/
#   define VIS_INTERFACE_APP_ID                             SBX_PROCESS_ID
#   define VMSD_APP_ID                                      SBX_PROCESS_ID
#   define VUI_MANAGER_APP_ID                               SBX_PROCESS_ID
#   define XSALMT_APP_ID                                    SBX_PROCESS_ID
#   define ML_MGR_APP_ID                                    SBX_PROCESS_ID
#   define NAV_MOST_SERVER_APP_ID                           SBX_PROCESS_ID
#   define FBL_MGR_APP_ID                                   SBX_PROCESS_ID
#   define AM_TUNER_APP_ID                                  SBX_PROCESS_ID
#   define AMPLIFIER_SERVER_APP_ID                          SBX_PROCESS_ID
#   define AUXILIARY_INPUT_JACK_SERVER_APP_ID               SBX_PROCESS_ID
#   define AV_CONNECTION_MANAGER_APP_ID                     SBX_PROCESS_ID
#   define AV_MANAGER_SERVER_APP_ID                         SBX_PROCESS_ID
#   define BLUETOOTH_SETTINGS_SERVER_APP_ID                 SBX_PROCESS_ID
#   define DAB_FM_TUNER_SERVER_APP_ID                       SBX_PROCESS_ID
#   define FAVORITES_MANAGER_APP_ID                         SBX_PROCESS_ID
#   define FM_TUNER_APP_ID                                  SBX_PROCESS_ID
#   define GMLAN_GATEWAY_APP_ID                             SBX_PROCESS_ID
#   define ICS_CONTROLS_APP_ID                              SBX_PROCESS_ID
#   define HVAC_SETTINGS_APP_ID                             SBX_PROCESS_ID
#   define LVM_INTERFACE_SERVER_APP_ID                      SBX_PROCESS_ID
#   define MEDIA_PLAYER_APP_ID                              SBX_PROCESS_ID
#   define AUDIODISK_PLAYER_APP_ID                          SBX_PROCESS_ID
#   define TBOX_AUDIO_MGR_APP_ID                            SBX_PROCESS_ID
#   define ONSTAR_DATA_SETTINGS_APP_ID                      SBX_PROCESS_ID
#   define ONSTAR_PERSONAL_CALLING_APP_ID                   SBX_PROCESS_ID
#   define ONSTAR_TBT_NAVIGATION_APP_ID                     SBX_PROCESS_ID
#   define SYSTEM_STATE_SERVER_APP_ID                       SBX_PROCESS_ID
#   define PM_APP_APP_ID                                    SBX_PROCESS_ID
#   define SYSTEMSTATE_SOCKETSERVER_APP_ID                  PM_APP_APP_ID
#   define SSM_APP_ID                                       SBX_PROCESS_ID
#   define TELEPHONE_SERVER_APP_ID                          SBX_PROCESS_ID
#   define TTS_MOST_SERVER_APP_ID                           SBX_PROCESS_ID
#   define RTP_MOST_SERVER_APP_ID                           SBX_PROCESS_ID
#   define CARPLAY_PHONE_SERVER_APP_ID                      SBX_PROCESS_ID
#   define CARPLAY_PROMPT_SERVER_APP_ID                     SBX_PROCESS_ID
#   define CARPLAY_MEDIA_SERVER_APP_ID                      SBX_PROCESS_ID
#   define PROGRAMMING_MASTER_APP_ID                        SBX_PROCESS_ID
#   define VIRTUALSOURCE_PROMPT_SERVER_APP_ID               SBX_PROCESS_ID
#   define ENG_MODE_APP_ID                                  SBX_PROCESS_ID
#   define ENGMODE_SOCKETSERVER_APP_ID                      SBX_PROCESS_ID
#   define ENGMODE_LINUX_LOG_MGR_APP_ID                     SBX_PROCESS_ID
#   define ENGMODE_ANDROID_LOG_MGR_APP_ID                   SBX_PROCESS_ID
#   define SETTING_SOCKETSERVER_APP_ID                      SBX_PROCESS_ID
#   define PS_SOCKETSERVER_APP_ID                           SBX_PROCESS_ID
#   define AUDIO_MGR_APP_ID                                 SBX_PROCESS_ID
#   define PHONE_CALL_MGR_APP_ID                            SBX_PROCESS_ID
#   define PITS_APP_ID                                      SBX_PROCESS_ID
#   define NETWORK_MGR_PROCESS_ID                           SBX_PROCESS_ID
#   define ECNR_MGR_APP_ID                                  SBX_PROCESS_ID
#   define HF_AUDIO_PROCESSING_APP_ID                       SBX_PROCESS_ID
#   define MIC_PROCESS_ID                                   SBX_PROCESS_ID
#   define EXTERNAL_LOG_SOCKETSERVER_APP_ID                 SBX_PROCESS_ID
#   define VIP_DIAG_PROXY_APP_ID                            SBX_PROCESS_ID
#   define ANIMATION_SYNC_APP_ID                            SBX_PROCESS_ID
#   define USERTIME_MGR_APP_ID                              SBX_PROCESS_ID
#   define CLUSTER_CLIENT_APP_ID                            SBX_PROCESS_ID
#   define DBA_DATA_COLLECTION_APP_ID                       SBX_PROCESS_ID
#   define DBA_SOCKET_SERVER_APP_ID                         SBX_PROCESS_ID

#   define BLUETOOTHD_APM_APP_ID                            BT_CM_PROCESS_ID
#   define BT_XSAL_GATEWAY_APP_ID                           BT_CM_PROCESS_ID
#   define BT_LE_HANDLER_APP_ID                             BT_CM_PROCESS_ID
#   define PBDB_APP_ID                                      BT_CM_PROCESS_ID
#   define BTSM_APP_ID                                      BT_CM_PROCESS_ID
#   define MAPDB_APP_ID                                     BT_CM_PROCESS_ID
#   define BT_MAP_SESSION_MGR_APP_ID                        BT_CM_PROCESS_ID
#   define BT_SOCKETSERVER_APP_ID                        	BT_CM_PROCESS_ID

#   define WIFI_MGR_APP_ID                                  WIFI_PROCESS_ID

#   define SPEECH_MGR_APP_ID                                SPEECH_MGR_PROCESS_ID

#   define TOUCH_SCREEN_APP_ID                              TOUCH_PROCESS_ID
#   define TSC_APP_ID                                       TOUCH_PROCESS_ID

#   define APS_CORE_APP_ID                                  APS_CORE_PROCESS_ID
#   define BT_SPP_SS_CLIENT_APP_ID                          APS_CORE_PROCESS_ID
#   define APS_SYSTEM_PROCESS_ID                            APS_CORE_PROCESS_ID

#   define SECURITY_MGR_APP_ID			                    SECURITY_MGR_PROCESS_ID

/* Add for pki */
#   define PKI_MGR_APP_ID                                   PKI_PROCESS_ID

/*add for tbox*/
#   define TBOX_APP_ID                                      TBOX_SERVICE_PROCESS_ID
/*
 * The following blocks share an execution context supplied by
 * bb_xsal_msg_thread via an XSAL message thread.
 */
#   define BUC_APP_ID                                       ES_XSALMT_APP_ID
#   define GMLAN_CHIMES_APP_ID                              ES_XSALMT_APP_ID

#   define VO_APP_ID                                        XSALMT_APP_ID
#   define HF_PHONE_APP_ID                                  XSALMT_APP_ID
#   define BLUETOOTHD_LISTENER_APP_ID                       XSALMT_APP_ID

/**
 * Application ID associated with first application.
 */
#   define SAL_FIRST_APP_ID 1

/**
 * Used by XSAL to size arrays based on number of applications.
 */
#   define SAL_MAX_APPS (SAL_LAST_APP_ID-SAL_FIRST_APP_ID)

/*===========================================================================*/
/** @} doxygen end group */
#endif /* XSAL_APPLICATION_ID_H */
