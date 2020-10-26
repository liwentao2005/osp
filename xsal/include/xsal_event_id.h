#ifndef XSAL_EVENT_ID_H
#   define XSAL_EVENT_ID_H
/*===========================================================================*/
/**
 * @file xsal_event_id.h
 *
 * System wide events IDs.
 *
 * %full_filespec:xsal_event_id.h~50.1.4.1.1.2.2.2.4.1.1.1.6:incl:ctc_ec#156 %
 * @version %version:50.1.4.1.1.2.2.2.4.1.1.1.6 %
 * @author  %derived_by:tjcthj %
 * @date    %date_modified:Sat Oct 12 16:26:47 2019 %
 *
 *------------------------------------------------------------------------------
 *
 * Copyright 2010 Delphi Technologies, Inc., All Rights Reserved.
 * Delphi Confidential
 *
 *------------------------------------------------------------------------------
 *
 * @section DESC DESCRIPTION:
 *   All system event IDs. This file defines all event IDs for the XSAL MDF.
 *
 * @section ABBR ABBREVIATIONS:
 *   - XSAL = eXtensible System Abstraction Layer.
 *
 * @section TINFO TRACEABILITY INFO:
 *   - Design Document(s):
 *
 *   - Requirements Document(s):
 *     BASA_SRS_Error_Management_0 4.doc
 *
 *   - Applicable Standards (in order of precedence: highest first):
 *     - <a href="http://kogespw1.delcoelect.com:8508/passthru/consumer?name=SW%20REF%20264.15D&doctype=K8DBSDoc">
 *       SW REF 264.15D "Delphi C Coding Standards" [12-Mar-2006]</a>
 *
 * @section DFS DEVIATIONS FROM STANDARDS:
 *   - None
 *
 * @defgroup xsal_events_grp Public event IDs
 * @{
 */
/*==========================================================================*/

/*===========================================================================*\
 * Header Files
\*===========================================================================*/
/*
#include "device_manager_domain.h"
#include "apm_event_id.h"
#include "eng_mode_event_id.h"
#include "gmlan_interface_event_id.h"
#include "periodic_event_ids.h"
#include "pm_event_id.h"
#include "ps_event_id.h"
#include "bt_as_event_id.h"
#include "bt_as_private_event_id.h"
#include "bt_cm_event_id.h"
#include "bt_cm_private_event_id.h"
#include "bt_socket_server_private_events.h"
#include "bt_diag_event_id.h"
#include "bt_diag_private_event_id.h"
#include "bt_hfp_event_id.h"
#include "bt_hfp_private_event_id.h"
#include "bt_pbap_event_id.h"
#include "bt_pbap_private_event_id.h"
#include "bt_map_private_event_id.h"
#include "bt_map_event_id.h"
#include "bt_msm_event_id.h"
#include "map_db_event_id.h"
#include "bt_storage_manager_event_id.h"
#include "phonebook_db_event_id.h"
#include "soh_event_id.h"
#include "pm_application_event_id.h"
#include "vip_desip_event_id.h"
#include "vip_proxy_event_id.h"
#include "xsal_msg_thread_event_id.h"
#include "xsalcpp_event_id.h"
#include "bt_spp_event_id.h"
#include "bt_spp_handler_event_id.h"
#include "bt_spp_private_event_id.h"
#include "bt_cm_spp_private_event_id.h"
#include "bt_pan_event_id.h"
#include "bt_pan_private_event_id.h"
#include "bt_dun_event_id.h"
#include "bt_dun_private_event_id.h"
#include "early_start_event_id.h"
#include "wifi_mgr_event_id.h"
#include "tuner_event_id.h"
#include "tuner_socket_server_event_id.h"
#include "systemstate_socket_event_id.h"
#include "engmode_socket_event_id.h"
#include "setting_socket_event_id.h"
#include "external_log_socket_event_id.h"
#include "ps_socket_event_id.h"
#  include "aps_core_event_id.h"
#  include "aps_core_wdog_event_id.h"
#include "aps_vr_event_id.h"
#include "aps_navi_event_id.h"
#include "touch_event_id.h"
#include "rawinput_manager_event_id.h"
#include "rawinput_simulation_event_id.h"
#include "security_mgr_event_id.h" 
#include "backup_camera_event_id.h"
#include "video_control_event_id.h"
#include "speech_core_event_id.h"
#include "prompt_manager_event_id.h"
#include "audio_mgr_event_id.h"
#include "aps_reminder_event_id.h"
#include "aps_tts_event_id.h"
#include "bt_strm_vpd_event_id.h"
#include "phone_call_mgr_event_id.h"
#include "draw_guidelines_event_id.h"
#include "bt_le_private_event_id.h"
#include "bt_le_event_id.h"
#include "sys_sounds_event_id.h"
#include "sound_playback_event_id.h"
#include "connection_manager_event_id.h"
#include "can_server_event_id.h"
#include "socklm_event_id.h"
#include "mfg_service_manager_event_id.h"
#include "pits_service_manager_event_id.h"
#include "FBL_Mgr_event_id.h"
#include "network_mgr_event_id.h"
#include "bt_spp_ss_client_private_event_id.h"
#include "ecnr_manager_event_id.h"
#include "can_aps_server_event_id.h"
#include "faceplate_control_event_id.h"
#include "hf_audio_processing_event_id.h"
#include "aps_system_event_id.h"
#include "dimming_event_id.h"
#include "periodic_event_ids.h"
#include "cals_event_id.h"
#include "aps_audio_event_id.h"
#include "audio_socket_server_event_id.h"
#include "mic_socket_server_event_id.h"
#include "pki_mgr_event_id.h"
#include "tbox_audio_mgr_event_id.h"
#include "source_manager_event_id.h"
#include "amfm_mngr_event_id.h"
#include "ed_term_event_id.h"
#include "animation_sync_event_id.h"
#include "usertime_mgr_event_id.h"
#include "hisip_device_manager_event.h"
#include "hisip_ap_node_xsal_event.h"
#include "hisip_M4_node_xsal_event.h"
#include "bev_socket_server_event_id.h"
#include "fbl_manager_event_id.h"
#include "tbox_interface_event_id.h"
#include "cluster_interface_event_id.h"
#include "apa_socket_server_event_id.h"
#include "thermal_dvfs_event_id.h"
#include "tbox_service_mgr_event_id.h"
#include "aps_proxy_event_id.h"
#include "aps_remotelog_event_id.h"
#include "dba_data_collection_event_id.h"
#include "dba_socketserver_event_id.h"
*/
/*===========================================================================*\
 * Exported Type Declarations
\*===========================================================================*/

#define HMI_CUSTOMIZATION_EV_BROADCAST_MESSAGE HMI_CUSTOMIZATION_BCM_CLIENT_EV_BROADCAST_MESSAGE

/**
 * System events that are private to the modules that define them, which means
 * they are intended only for local use by that module. These events are
 * "exposed" only to assign them unique values within the SAL_Event_Id_T enum.
 */
#define  SAL_PRIVATE_EVENTS \
   APM_PRIVATE_EVENTS \
   ENG_MODE_PRIVATE_EVENTS \
   GMLAN_INTERFACE_PRIVATE_EVENTS \
   BT_AS_PRIVATE_EVENTS \
   BT_CM_PRIVATE_EVENTS \
   BT_LE_PRIVATE_EVENTS \
   BT_SOCKET_SERVER_PRIVATE_EVENTS \
   BT_DIAG_PRIVATE_EVENTS \
   BT_HFP_PRIVATE_EVENTS \
   BT_MAP_PRIVATE_EVENTS \
   BT_PBAP_PRIVATE_EVENTS \
   BT_SPP_PRIVATE_EVENTS\
   BT_CM_SPP_PRIVATE_EVENTS \
   BT_SPP_SS_CLIENT_PRIVATE_EVENTS \
   BT_STORAGE_MANAGER_PRIVATE_EVENTS\
   BT_PAN_PRIVATE_EVENTS\
   BT_DUN_PRIVATE_EVENTS\
   BT_MSM_PRIVATE_EVENTS\
   BT_STRM_VPD_PRIVATE_EVENTS\
   MAPDB_PRIVATE_MESSAGE_EVENTS\
   MAPDB_PRIVATE_DATABASE_EVENTS \
   PBDB_PRIVATE_EVENTS \
   PM_PRIVATE_EVENTS \
   PS_PRIVATE_EVENTS \
   SALCPP_PRIVATE_EVENTS \
   SOH_PRIVATE_EVENTS \
   PM_APP_PRIVATE_EVENTS \
   VIP_DESIP_PRIVATE_EVENTS \
   VIP_PROXY_PRIVATE_EVENTS \
   XSALMT_PRIVATE_EVENTS \
   EARLY_START_PRIVATE_EVENTS \
   SYSTEMSTATE_SOCKETSERVER_PRIVATE_EVENTS \
   ENGMODE_SOCKETSERVER_PRIVATE_EVENTS \
   SETTING_SOCKETSERVER_PRIVATE_EVENTS \
   EXTLOG_SOCKETSERVER_PRIVATE_EVENTS \
   PS_SOCKETSERVER_PRIVATE_EVENTS \
   TUNER_SOCKET_SERVER_PRIVATE_EVENTS \
   AMFM_PRIVATE_EVENTS\
   TUNER_PRIVATE_EVENTS\
   SSM_PRIVATE_EVENTS\
   ED_TERM_PRIVATE_EVENTS\
   APS_CORE_PRIVATE_EVENTS\
   APS_CORE_WDOG_PRIVATE_EVENTS\
   WIFI_PRIVATE_EVENTS  \
   APS_VR_PRIVATE_EVENTS\
   APS_NAVI_PRIVATE_EVENTS\
   RAWINPUT_MANAGER_PRIVATE_EVENTS\
   SECURITY_MGR_PRIVATE_EVENTS\
   BUC_PRIVATE_EVENTS\
   VIDEO_CONTROL_PRIVATE_EVENTS\
   SPEECH_CORE_PRIVATE_EVENTS \
   PROMPT_MGR_PRIVATE_EVENTS \
   AUDIO_MGR_PRIVATE_EVENTS\
   APS_REMINDER_PRIVATE_EVENTS\
   APS_TTS_PRIVATE_EVENTS\
   PHONE_MGR_PRIVATE_EVENTS \
   DRAW_GUIDELINES_PRIVATE_EVENTS\
   MEDIA_DEVICE_DETECTORS_PRIVATE_EVENTS \
   MEDIA_DEV_MANAGER_PRIVATE_EVENTS \
   SSND_PRIVATE_EVENTS \
   SOUND_PLAYBACK_PRIVATE_EVENTS \
   CONNECTION_MANAGER_NETWORK_PRIVATE_EVENTS \
   SOCKLM_PRIVATE_EVENTS\
   CAN_SERVER_PRIVATE_EVENTS \
   PITS_MFG_SERVICE_PRIVATE_EVENTS \
   PITS_APPLICATION_PRIVATE_EVENTS \
   NETWORK_MGR_PRIVATE_EVENTS\
   FBL_MGR_PRIVATE_EVENTS\
   ECNR_MGR_PRIVATE_EVENTS\
   CAN_APS_SERVER_PRIVATE_EVENTS\
   FACEPLATE_CONTROL_PRIVATE_EVENTS\
   HFAP_PRIVATE_EVENTS\
   APS_SYSTEM_PRIVATE_EVENTS\
   DIMMING_PRIVATE_EVENTS\
   CALS_PRIVATE_EVENTS\
   RAWINPUT_SIMULATION_PRIVATE_EVENTS\
   AUDIO_SOCKET_SERVER_PRIVATE_EVENTS\
   APS_AUDIO_PRIVATE_EVENTS\
   MIC_SOCKET_SERVER_PRIVATE_EVENTS\
   PKI_PRIVATE_EVENTS\
   TBOX_AUDIO_MGR_PRIVATE_EVENTS \
   HISIP_AP_NODE_PRIVATE_EVENTS\
   HISIP_M4_NODE_PRIVATE_EVENTS\
   BEV_SOCKET_SERVER_PRIVATE_EVENTS\
   ANIMATION_SYNC_PRIVATE_EVENTS\
   USERTIME_MGR_PRIVATE_EVENTS\
   FBLMGR_COMMON_PRIVATE_EVENTS\
   TBOX_INTERFACE_PRIVATE_EVENTS\
   CLUSTER_INTERFACE_PRIVATE_EVENTS\
   APA_SOCKET_SERVER_PRIVATE_EVENTS\
   THERMAL_DVFS_PRIVATE_EVENTS\
   TBOX_SERVICE_MGR_PRIVATE_EVENTS\
   APS_REMOTELOG_PRIVATE_EVENTS\
   DBA_DATA_COLLECTION_PRIVATE_EVENTS\
   DBA_SOCKETSERVER_PRIVATE_EVENTS\

/**
 * System events that are public, which means the event ids can be used by
 * modules other than the one declaring them.
 *
 * @note "Public" events cannot be subscribed to
 * @see SAL_Send()
 */
#define  SAL_PUBLIC_EVENTS \
   APM_PUBLIC_EVENTS \
   ENG_MODE_PUBLIC_EVENTS \
   /*GMLAN_INTERFACE_PUBLIC_EVENTS*/ \
   PM_PUBLIC_EVENTS \
   BT_AS_PUBLIC_EVENTS \
   BT_CM_PUBLIC_EVENTS \
   BT_DIAG_PUBLIC_EVENTS \
   BT_HFP_PUBLIC_EVENTS \
   HFAP_PUBLIC_EVENTS \
   MIC_SOCKET_SERVER_PUBLIC_EVENTS \
   BT_MAP_PUBLIC_EVENTS \
   BT_PBAP_PUBLIC_EVENTS \
   PBDB_PUBLIC_EVENTS\
   BT_SPP_PUBLIC_EVENTS\
   BT_PAN_PUBLIC_EVENTS\
   BT_DUN_PUBLIC_EVENTS\
   BT_MSM_PUBLIC_EVENTS\
   MAPDB_PUBLIC_EVENTS\
   PS_PUBLIC_EVENTS \
   SALCPP_PUBLIC_EVENTS \
   SOH_PUBLIC_EVENTS \
   PM_APP_PUBLIC_EVENTS \
   VIP_DESIP_PUBLIC_EVENTS \
   VIP_PROXY_PUBLIC_EVENTS \
   XSALMT_PUBLIC_EVENTS \
   EARLY_START_PUBLIC_EVENTS \
   SYSTEMSTATE_SOCKETSERVER_PUBLIC_EVENTS \
   ENGMODE_SOCKETSERVER_PUBLIC_EVENTS \
   SETTING_SOCKETSERVER_PUBLIC_EVENTS \
   PS_SOCKETSERVER_PUBLIC_EVENTS \
   TUNER_SOCKET_SERVER_PUBLIC_EVENTS \
   AMFM_PUBLIC_EVENTS\
   TUNER_PUBLIC_EVENTS\
   SSM_PUBLIC_EVENTS \
   ED_TERM_PUBLIC_EVENTS\
   APS_CORE_PUBLIC_EVENTS\
   APS_CORE_WDOG_PUBLIC_EVENTS \
   WIFI_PUBLIC_EVENTS  \
   APS_VR_PUBLIC_EVENTS \
   APS_NAVI_PUBLIC_EVENTS \
   RAWINPUT_MANAGER_PUBLIC_EVENTS\
   SECURITY_MGR_PUBLIC_EVENTS\
   VIDEO_CONTROL_PUBLIC_EVENTS\
   SPEECH_CORE_PUBLIC_EVENTS \
   PROMPT_MGR_PUBLIC_EVENTS \
   AUDIO_MGR_PUBLIC_EVENTS\
   APS_REMINDER_PUBLIC_EVENTS \
   APS_TTS_PUBLIC_EVENTS \
   MEDIA_DEVICE_DETECTORS_PUBLIC_EVENTS \
   MEDIA_DEV_MANAGER_PUBLIC_EVENTS \
   FBL_MGR_PUBLIC_EVENTS\
   SSND_PUBLIC_EVENTS \
   CONNECTION_MANAGER_NETWORK_PUBLIC_EVENTS \
   SOCKLM_PUBLIC_EVENTS\
   CAN_SERVER_PUBLIC_EVENTS \
   PITS_MFG_SERVICE_PUBLIC_EVENTS \
   PITS_APPLICATION_PUBLIC_EVENTS \
   NETWORK_MGR_PUBLIC_EVENTS\
   ECNR_MGR_PUBLIC_EVENTS\
   CAN_APS_SERVER_PUBLIC_EVENTS\
   FACEPLATE_CONTROL_PUBLIC_EVENTS\
   APS_SYSTEM_PUBLIC_EVENTS\
   APS_PROXY_PUBLIC_EVENTS\
   DIMMING_PUBLIC_EVENTS\
   CALS_PUBLIC_EVENTS\
   RAWINPUT_SIMULATION_PUBLIC_EVENTS\
   PKI_PUBLIC_EVENTS\
   TBOX_AUDIO_MGR_PUBLIC_EVENTS \
   HISIP_AP_NODE_PUBLIC_EVENTS\
   HISIP_M4_NODE_PUBLIC_EVENTS\
   BEV_SOCKET_SERVER_PUBLIC_EVENTS\
   ANIMATION_SYNC_PUBLIC_EVENTS\
   USERTIME_MGR_PUBLIC_EVENTS\
   CLUSTER_INTERFACE_PUBLIC_EVENTS\
   APA_SOCKET_SERVER_PUBLIC_EVENTS\
   TBOX_SERVICE_MGR_PUBLIC_EVENTS \
   APS_REMOTELOG_PUBLIC_EVENTS\
   DBA_DATA_COLLECTION_PUBLIC_EVENTS\
   DBA_SOCKETSERVER_PUBLIC_EVENTS\


/**
 * System events that are available for use with the XSAL Publish/Subscribe
 * feature.
 *
 * @see SAL_Publish(), SAL_Subscribe()
 */
#define  SAL_PUBLISHED_EVENTS \
   APM_PUBLISHED_EVENTS \
   ENG_MODE_PUBLISHED_EVENTS \
   /*GMLAN_INTERFACE_PUBLISHED_EVENTS*/ \
   PM_PUBLISHED_EVENTS \
   BT_AS_PUBLISHED_EVENTS \
   BT_CM_PUBLISHED_EVENTS \
   BT_LE_PUBLISHED_EVENTS \
   BT_DIAG_PUBLISHED_EVENTS \
   BT_HFP_PUBLISHED_EVENTS \
   MIC_SOCKET_SERVER_PUBLISHED_EVENTS \
   BT_MAP_PUBLISHED_EVENTS \
   MAPDB_PUBLISHED_EVENTS \
   BT_PBAP_PUBLISHED_EVENTS \
   BT_SPP_PUBLISHED_EVENTS\
   BT_SPP_HANDLER_PUBLISHED_EVENTS\
   BT_STORAGE_MANAGER_PUBLISHED_EVENTS\
   BT_PAN_PUBLISHED_EVENTS\
   BT_DUN_PUBLISHED_EVENTS\
   BT_MSM_PUBLISHED_EVENTS\
   PBDB_PUBLISHED_EVENTS\
   FBL_MGR_PUBLISHED_EVENTS\
   PS_PUBLISHED_EVENTS \
   SALCPP_PUBLISHED_EVENTS \
   SOH_PUBLISHED_EVENTS \
   PM_APP_PUBLISHED_EVENTS \
   VIP_DESIP_PUBLISHED_EVENTS \
   VIP_PROXY_PUBLISHED_EVENTS \
   XSALMT_PUBLISHED_EVENTS \
   EARLY_START_PUBLISHED_EVENTS \
   SYSTEMSTATE_SOCKETSERVER_PUBLISHED_EVENTS \
   ENGMODE_SOCKETSERVER_PUBLISHED_EVENTS \
   SETTING_SOCKETSERVER_PUBLISHED_EVENTS \
   EXTLOG_SOCKETSERVER_PUBLISHED_EVENTS \
   PS_SOCKETSERVER_PUBLISHED_EVENTS \
   TUNER_SOCKET_SERVER_PUBLISHED_EVENTS \
   AMFM_PUBLISHED_EVENTS\
   TUNER_PUBLISHED_EVENTS\
   SSM_PUBLISHED_EVENTS\
   ED_TERM_PUBLISHED_EVENTS\
   APS_CORE_PUBLISHED_EVENTS\
   APS_CORE_WDOG_PUBLISHED_EVENTS \
   WIFI_PUBLISHED_EVENTS    \
   APS_VR_PUBLISHED_EVENTS \
   APS_NAVI_PUBLISHED_EVENTS \
   TOUCH_PROCESS_PUBLISHED_EVENTS \
   RAWINPUT_MANAGER_PUBLISHED_EVENTS\
   SECURITY_MGR_PUBLISHED_EVENTS\
   BUC_PUBLISHED_EVENTS\
   VIDEO_CONTROL_PUBLISHED_EVENTS\
   SPEECH_CORE_PUBLISHED_EVENTS \
   PROMPT_MGR_PUBLISHED_EVENTS \
   AUDIO_MGR_PUBLISHED_EVENTS\
   APS_REMINDER_PUBLISHED_EVENTS \
   APS_TTS_PUBLISHED_EVENTS \
   PHONE_MGR_PUBLISHED_EVENTS\
   DRAW_GUIDELINES_PUBLISHED_EVENTS\
   MEDIA_DEVICE_DETECTORS_PUBLISHED_EVENTS \
   MEDIA_DEV_MANAGER_PUBLISHED_EVENTS \
   SSND_PUBLISHED_EVENTS \
   CONNECTION_MANAGER_NETWORK_PUBLISHED_EVENTS \
   SOCKLM_PUBLISHED_EVENTS\
   CAN_SERVER_PUBLISHED_EVENTS \
   PITS_MFG_SERVICE_PUBLISHED_EVENTS \
   PITS_APPLICATION_PUBLISHED_EVENTS \
   NETWORK_MGR_PUBLISHED_EVENTS\
   ECNR_MGR_PUBLISHED_EVENTS \
   CAN_APS_SERVER_PUBLISHED_EVENTS\
   FACEPLATE_CONTROL_PUBLISHED_EVENTS\
   HFAP_PUBLISHED_EVENTS\
   APS_SYSTEM_PUBLISHED_EVENTS\
   DIMMING_PUBLISHED_EVENTS\
   PERIODIC_PUBLISHED_EVENTS\
   CALS_PUBLISHED_EVENTS\
   RAWINPUT_SIMULATION_PUBLISHED_EVENTS\
   PKI_PUBLISHED_EVENTS\
   TBOX_AUDIO_MGR_PUBLISHED_EVENTS \
   TBOX_SERVICE_MGR_PUBLISHED_EVENTS\
   HISIP_AP_NODE_PUBLISHED_EVENTS\
   HISIP_M4_NODE_PUBLISHED_EVENTS\
   BEV_SOCKET_SERVER_PUBLISHED_EVENTS\
   ANIMATION_SYNC_PUBLISHED_EVENTS\
   USERTIME_MGR_PUBLISHED_EVENTS\
   CLUSTER_INTERFACE_PUBLISHED_EVENTS\
   APA_SOCKET_SERVER_PUBLISHED_EVENTS\
   APS_REMOTELOG_PUBLISHED_EVENTS\
   DBA_DATA_COLLECTION_PUBLISHED_EVENTS\
   DBA_SOCKETSERVER_PUBLISHED_EVENTS\





/* Expand event declarations to be the id tag followed by a comma. */
#  undef  SAL_EVENT
#  define SAL_EVENT(id,descr) id,
#  define SAL_PRIVATE_EVENT(id,descr)   SAL_EVENT(id, descr)
#  define SAL_PUBLIC_EVENT(id,descr)    SAL_EVENT(id, descr)
#  define SAL_PUBLISHED_EVENT(id,descr) SAL_EVENT(id, descr)

/**
 * System wide event identifiers.
 *
 * All published event identifiers need to be listed in this typedef between
 * SAL_EVG_FIRST_PUBLISHED_EVENT_ID and SAL_EVG_LAST_PUBLISHED_EVENT_ID.
 *
 * Public events are those that are shared between modules but are not
 * available for use with SAL_Publish() and SAL_Subscribe(). These are assigned
 * values between SAL_EVG_LAST_PUBLISHED_EVENT_ID and SAL_EV_FIRST_PRIVATE_ID.
 *
 * Tasks can use private event IDs starting at SAL_EV_FIRST_PRIVATE_ID. Private
 * events include timer IDs, internal message sent via SAL_Send(), etc.
 */
typedef enum SAL_Event_Id_Tag
{
   /** RESERVED for XSAL, must be first; do not change! */
   SAL_FIRST_EVENT_ID = 0,
   SAL_EVG_FIRST_PUBLISHED_EVENT_ID = SAL_FIRST_EVENT_ID,

   //SAL_PUBLISHED_EVENTS

   /** RESERVED for XSAL, must be last published event id; do not change! */
   SAL_EVG_LAST_PUBLISHED_EVENT_ID,

   //SAL_PUBLIC_EVENTS

   /** First private event identifier value. */
   SAL_EV_FIRST_PRIVATE_ID,

   //SAL_PRIVATE_EVENTS

   SAL_LAST_EVENT_ID /* Must be last - do not move! */
}
SAL_Event_Id_T;


/**
 * Needed by XSAL to allocate space events. Do not change!
 */
#   define SAL_MAX_EVENTS (SAL_LAST_EVENT_ID-SAL_FIRST_EVENT_ID)

/*===========================================================================*/
/*!
 * @file xsal_event_id.h
 *
 * 29Nov2017  Rahul Chirayil (vzm576)
 * ctc_ec#202404: Update animation sync process.
 *
 * 29Nov2017  Rahul Chirayil (vzm576)
 * ctc_ec#202346: Integrate animation sync component to project.
 *
 * 14-Nov-2017 dzphcr
 *   - Task ctc_ec#200933:[ICI2.0][BT] Added PBDB_PUBLIC_EVENTS x-macro
 *
 * 24-Fed-2017 wangshihua
 *  Add pki events
 *
 * 11-Jan-2017 dzphcr
 *   - Task ctc_ec#173126:[ICI2.0][BT] Move MAPDB_EVG_DB_ERROR event  from public to publish group
 *
 * 23-Nov-2016 Luis Solis Rev 36.1.9
 *   - Task ctc_ec#169696: [NGI2][Media] Integrate Gracenote with 4.4 kernel support
 *
 * 03-Nov-2016  Haneef Syed
 *   - Task: ctc_ec#165748: HF Audio processing integration
 *
 * - 20-Sept-2016 dzphcr
 *   -Task: ctc_ec#162791: Added SPP ss client private event.
 *
 * 19-Sep-2016 Sanju Nediyaparambath Rev 35
 * + ctc_ec#162759:Added BT_TELEPHONY_PRIVATE_EVENTS for Call Timer Implementation
 *
 * 5-Sep-2016 Yuan Kanglin
 * + ctc_ec#161927:[NGI2][Network_Mgr] integrate network manager
 *
 * 29Aug2016  Devaraj Herle (rz35sz)
 * ctc_ec#161433: Integrating PITS Baseline to project
 *
 * -17-aug-2016 Yuan Kangin
 *   Add connection manager event
 * 
 * - 08-aug-2016 dzphcr Rev 22
 *   -Task: ctc_ec#159971: Added SPP related events.
 *
 * 12-July-2016 Gouri Naik
 * + ctc_ec#157494 Added AudioMgr
 * 
 * 23-Dec-2014 wangshuquan
 * + ctc_ec#94471 commit digital aux code
 * 
 * -12-Nov-2014 Lu Yinyin  69
 * -Add carplay event
 *
 * -03-Jun-2014 Milan Tian
 *  -Add vr navi naf interface event
 *
 * -8-Jan-2014 Bao Qifan 67
 * -Task: 56878 - [NGK PITS] add screen check function for pits
 *
 *
 * 25-Feb-2014 wang min remove old HMI from project
 * + bbc_sgmnglv\support\NAF\bbc_onstar_native_interface\bb_gmlan_gateway_native_interface\bb_gmlan_gateway_nai_imp\_src\GMLANGateway_Client.cpp
 * + bbc_sgmnglv\processes\system_persistence\nglv_board_options_ps.cpp
 *
 * 07-Jan-2014 Zheng,Sam
 * Remove the old/obsolute bb: bbc_sgmnglv/support/most/hmi_clients/bb_gmsbx14_alert_manager_client, and clean-up some related code in global cfg/ and system_callouts
 * Remove those XSAL-messages in global cfg/ files, as below
 * + bbc_sgmnglv/cfg/os/xsal_event_id.h
 * + bbc_sgmnglv/cfg/os/xsal_application_id.h
 * + bbc_sgmnglv/cfg/os/xsal_thread_id.h
 * + bbc_sgmnglv/cfg/os/xsal_thread_id.h
 * + bbc_sgmnglv/cfg/core/dbg_trace_cfg.h
 * + bbc_sgmnglv/cfg/core/dbg_trace_acfg.h
 * Remote system_callouts
 * + bbc_sgmnglv/processes/system_callouts/system_xsal_attr_callouts.c
 *
 * -18-Dec-2013 Ethan 54
 *  -Add onstar event
 *
 * -12-Dec-2013 Gene Hu 62
 * -Add TSC event
 *
 * -18-Nov-2013 HuiBin Li 52
 *  -Add XENA event
 *
 * -15-Nov-2013 Alex Lu Rev 50
 * -Task: 51680 - add nav most server event
 *
 * - 14-Nov-2013 Ethan Liu An Rev 50
 *   -Add NAF Onstar module
 *
 * - 07-Nov-2013 Ethan Liu Rev 49
 *   -Add GMLAN CUST private events
 *
 *  -30-Oct-2013 wang bing Rev 48 
 *  -Add HMI SYSCOMMONIF_PRIVATE_EVENTS.
 *
 * - 14-Aug-2013 Paul Xia An Rev 47
 *   -Add Map session and Map db module
 *
 * - 31-Jul-2013 Angelo An Rev 46
 *   -Add MirrorLink Mgr module
 *
 * - 23-Jul-2013 wang bing Li Rev 45
 *   -Add naf calibration module
 *
 * - 15-Jul-2013 HuiBin Li Rev 44
 *   -Add reminder module
 *
 * -09-July-2013 Ethan Liu Rev43
 *  -Add faceplate public event ID
 *
 * -05-Jul-2013 Ray Zhang Rev42
 *  -Add the connection manager event ID
 *
 * -26-June-2013 Angelo An Rev40
 *  -Add the MirrorLink event ID
 *
 *  -11-Jun-2013 Ray Zhang Rev 39
 *  -Add PAN DUN client event ID
 *
 *  -11-Jun-2013 Ray Zhang Rev 37
 *  -Add PAN DUN event ID
 *
 * -30-May-2013 Alex Lu Rev 36
 * -Task: 39806 - add NAV_DR_PUBLISHED_EVENTS & NAV_DR_PRIVATE_EVENTS
 *
 *  -27-May-2013 Ray Zhang Rev 35
 *  -Remove Phonebook client events
 *
 *  -30-Apr-2013 Ray Zhang Rev 32
 *  -Add SPP events.
 *  -Remove phone process events.
 *  -Remove bluetooth process events.
 *
 *  -22-Apr-2013 Wang Le Rev 31 
 *  -Add key manager client module events.   
 *   
 *  -19-Apr-2013 Paul Xia Rev 30 
 *  -Add bt_storage_mgr and phonebook_db.
 *
 *  -18-Apr-2013 Arthur C Rev 29 
 *  -Add Naf Loader EVENTS.
 *
 *  -25-Mar-2013 shaofei Rev 27 
 *  -Add  Most EVENTS.
 *
 *  -28-Feb-2013 wang bing Rev 26 
 *  -Add HMI REARCAMERA_PRIVATE_EVENTS.
 *
 * -25-Feb-2013 Zhang Hang Rev 25
 *  -Add Layer Manager events.
 *   
 * -22-Feb-2013 Arthur Chen Rev 24
 *  -Add MSGs for VI.
 *   
 * -5-Feb-2013 Danny Kong Rev 23 
 *  -Add TEST_MEDIA_PLAYER_CLIENT.
 *
 * -30-Jan-2013 Li Hui Rev 22 
 *  -Add video control.
 *
 *
 * -21-Jan-2013 Shaofei   Rev 21  
 *  add vr handler event
 *
 * -16-Jan-2013 Danny Kong   Rev 20   
 *  add diag client handler event
 *
 * -08-Jan-2013 Bao Qifan   Rev 19   ctc_ec#33077
 *   - Add sinad event
 *
 * -25-dec-2012 li huibin
 *   - Add touchscreen event
 *
 * -24-Dec-2012 Alex Lu Rev 15
 * -Add gps event 
 *
 * - 30-nov-2012 Peggy
 *   - Add dimming event
 *
 * - 15-nov-2012 Ethan Liu Rev 13
 *   - Add FACEPLATE CONTROL events
 *
 * - 15-Nov-2012 Zhang Hang Rev 12
 *   - Remove xsal timer event because it is removed in new xsal version. 
 *
 * - 13-Nov-2012 Wang Shihua Rev 11
 *   - Add wifi manager events. 
 *
 * - 07-Nov-2012 Wang Le Rev 10
 *   - Add engineering mode and setting events. 
 *
 * - 06-nov-2012 Ethan Liu Rev 9
 *   - Add GMLAN CUSTOMIZATION events
 *
 * - 23-oct-2012 Zhang Hang Rev 8
 *   - Add native app interface events.
 *
 * - 22-Mar-2012 Larry Piekarski Rev 108
 *   - Task 84768: Add a Shutdown Watchdog timer.
 *
 * - 13-Mar-2012 Madhurima L Rev 107
 *   - Task 82485: Added alert Manager client
 *
 * - 13-Mar-2012 Sowmya K Rev 106
 *   - Task 82137: Added customization SBZA client
 *
 * - 09-Mar-2012 Gouri Naik Rev 105
 *   - Task#81456 Removed MISC_PUBLISHED_EVENTS.
 *
 * - 03-Mar-2012 Sowmya K Rev 104
 *   - Task 80084: Integrated Customization PA Client. 
 *
 * - 01-March-2012 Natesh.K.N Rev 103
 *  - Task 80071:Integrate customizations common events
 *
 * - 29-Feb-2012 Larry Piekarski Rev 102
 *   - Task 79582: Remove ICR bb_theft_lock block
 *
 * - 24-Feb-2012 Coppock, Jonathan (dzhk56) Rev 101
 *   - Task kok_basa#78217: "TMC: Integrate the following - bb_fm_tuner_server 20120222,
 *                                                          bb_pits_services 20120223,
 *                                                          bb_tuner_server_helper 20120221,
 *                                                          bbc_tmc_tuner 20120223_1"
 *     + Integrate TMC/MOST/PITS changes together that use the new TMC BBC and API.
 *
 * - 21-Feb-2012 Kamalakanta Barik Rev 100
 *   - Task 77786: Integrated Phonebook Manager and Phonebook Server.
 *
 * - 20-Feb-2012 Petter Gustafsson Rev 99
 *   - Task 77357: Integrated Bluetooth Streaming VPD.
 *
 * - 16-Feb-2012 Keerthika Pandiselvan Rev 98
 *   - Task 76482: Integrate OnstarTBTNavigation Server.
 *
 * - 13-Feb-2012 Larry Piekarski Rev 97
 *   - Task 75958: Removed unneeded bb_swc
 *
 * - 13-Feb-2012 Larry Piekarski Rev 96
 *   - Task 75660: Removed the Video Control block.
 *
 * - 07-Feb-2012 Gouri Naik Rev 95
 *   - kok_basa#74631 Added GMLAN_CHIMES_PRIVATE_EVENT list
 *
 * - 02-Feb-2012 Manuel Robledo Rev 94
 *   - Task 73725: Integrate customization_object_computation_settings_server and onstar_personal_calling into AE
 *
 * - 25-Jan-2012 Coppock, Jonathan (dzhk56) Rev 93
 *   - Task kok_basa#71622: "TMC: Integrate bbc_tmc_tuner release 20120125 into the aa1024ae SBX project"
 *     + Define the callout that publishes the external LDICE RDS TMC groups to the external TMC decoder.
 *     + Implement a new thread dedicated to decoding TMC from external sources.
 *     + Implement the decoder for the new external TMC decoding thread.
 *     + Publish the decoded external TMC data in the external TMC decoder to the TMC Manager.
 *     + Implement publishing of the external TMC data by the TMC Manager to the system.
 *     + Modify TMC station info and TMC data structures to include and use tuner index types.
 *
 * - 19-Jan-2012 Kavya Narayan  Rev 92
 *   -Task 70220: Added publish event id list for gmlan chimes module
 *
 * - 18-Jan-2012 Diptiman Roy  Rev 91
 *   -Task 70201: Integrated Customization Memory Settings Client
 *
 * - 17-Jan-2012 Diptiman Roy  Rev 90
 *   -Task 69961: Re-integrated Updated Customization Doors Locks Client
 *
 * -17-Jan-2012 Natesh.K.N Rev 89
 *   -Task 69933: Integrate Golden ics client
 *
 *   11-Jan-2011 Arturo Lopez  Rev 88
 *   - SCR kok_basa#18945, task kok_basa#68858
 *   AVP Server update: redefined process deployment strategy
 *
 * - 09-Jan-2012 Diptiman Roy Rev 87
 *   - Task 68165: Integrated Customization DoorsLocks Client
 *
 * - 06-Jan-2012 Larry Piekarski Rev 86
 *   - Task 67792: Removed bb_preset_manager
 *
 * -06-Jan-2012 P Anith Raj Rev 85
 *   -Task 67773: Integrate Golden CustomizationECC Client
 *
 * -02-Jan-2012 Natesh.K.N Rev 84
 *   -Task 66849: Integrate Golden AVManagerClient
 *
 * -30-Dec-2011 Natesh.K.N Rev 83
 *   -Task 66645: Integrate Golden AuxiliaryInputJackClient
 *
 * -26-Dec-2011 Anith Raj Rev 82
 *  - Task 66151: Integrate Customization BCM client
 *
 * - 23-Dec-2011 Jevan sp Rev 81
 *   - Task 66142: Integrated golden dab fm tuner client.
 *
 * -23-Dec-2011 Manuel Robledo Rev 80
 *   - Task 66043: Integrate customization_doors_locks_server and customization_pa_server into AE
 *
 * - 23-Dec-2011 Jevan sp Rev 79
 *   - Task 65967: Integrated golden audio disk player 
 *
 * -21-Dec-2011 Keerthika Pandiselvan Rev 78
 *   -Task 65395: Integrated mdf_customization_ipc_server and mdf_customization_sbza_server
 *
 * - 20-Dec-2011 Wanda Jimenez   Rev 77
 *   Task 64837: Integrate MTP VPD in SBX project.
 *
 * - 20-Dec-2011 Coppock, Jonathan (dzhk56) Rev 76
 *   - Task kok_basa#65211: "TMC: Integrate bbc_tmc_tuner release 20111219 into the aa1024ae SBX project"
 *     + Add configurable debug trace capability for analyzing timing of TMC threads and events.
 *     + Move the TMC background tuner to a new very low priority thread.
 *     + Add checks to TMC API proxy functions to suppress sending messages when the receiving thread isn't running.
 *
 * 19-Dec-2011 Keerthika Pandiselvan 75
 *  -Task 64857: Integrate mdf_customization_memory_settings_server 
 *
 * 19-Dec-2011 Rashmi Alok Rev 74
 *  -Task 65029:Rename OnstarDataSettings Client as per Golden client
 *
 * - 15-Dec-2011 Goran Davidsson Rev 73
 *   - Task 61707:Integrate BT Connection Manager
 *
 * - 14-Dec-2011 Rashmi Alok Rev 72
 *   - Task 64229:Integrate Amplifier Client
 *
 * -13-DEC-2011 David A. Johnson Rev 71
 *  - Task 64067: Integrate Phonebook Client
 *
 * -10-Dec-2011 Anith Raj Rev 70
 *  - Task 63556:Integrate BluetoothSettings Client
 *
 * -10-Dec-2011 Sonia Sood Rev 69
 *  - Task 63367:Modify Onstar Audio Server Event name and file name
 *
 * -10-Dec-2011 Anith Raj Rev 68
 *  - Task 63556:Integrate BluetoothSettings Client
 *
 * -09-Dec-2011 Rashmi Alok Rev 67
 *  - Task 63296:Integrate OnstarDataSettings Client
 *
 * -08-Dec-2011 Manuel Robledo Rev 66
 *   - Task 62683: Integrate customization_ecc_server into AE
 *
 * - 08-Dec-2011 Natesh.K.N Rev 65
 *  - Task 62961:Integrate Golden AM tuner Client
 *
 * - 07-Dec-2011 Zhang Hang Rev 64
 *   - Task 62752: Integrate LVM Interface server & engine.
 *
 * - 07-Dec-2011 Keerthika Pandiselvan Rev 63
 *   - Task 62124: Integration of mdf_customization_bcm_server
 *
 * -05-Dec-2011 Natesh.K.N Rev 62
 *   - Task 62261:Integrate Golden Fm tuner Client
 *
 * - 21-Nov-2011 Sowmya K Rev 61
 *   - Task 60199: Integration of OnstarDataSettings server
 *
 * - 04-Nov-2011 Larry Piekarski Rev 60
 *   - Task 56992: Added App Man to Most Servers
 *
 * -28-Oct-2011 Rashmi Alok Rev 58
 *  Task 56125: Integrate Golden System State Client
 *
 * - 26-Oct-2011 Wanda Jimenez   Rev 57
 *   Task 53225: Include IPOD VDP in the SBX projec.
 *
 *  -26-Oct-2011 Per Karlsson  Rev 56
 *   - Task 55780:Integrated Telephone Server
 *
 *  -25-Oct-2011 Per Karlsson  Rev 55
 *   - Task 55332:Bluetooth Settings Golden sever update
 *
 *  -25-Oct-2011 Natesh.K.N  Rev 54
 *   - Task 55489:Integrated OnStarAudioClient
 *
 * - 18-Oct-2011 Chris Baker
 *   Task kok_basa#54134 Revision 53
 *   - Removed BT_CM Process events.
 *
 * - 17-Oct-2011 Larry Piekarski Rev 52
 *   - Task 53880: Integrated Goldenized AVManager Server
 *
 * - 14-Oct-2011 Chris Baker
 *   Task kok_basa#53413 Revision 50
 *   - Added phone call manager events.
 *
 * - 13-Oct-2011 Chris Baker
 *   Task kok_basa#53194 Revision 49
 *   - Added HF Phone events.
 *
 * - 11-Oct-2011 Chris Baker
 *   Task kok_basa#53176 Revision 48
 *   - Added BT_CM Process events (process started/stopped).
 *
 * - 12-Oct-2011 Sowmya K Rev 47
 *  - Task 53031: Added OnstarAudioserver events
 *
 * - 11-OCT-2011 David A. Johnson  Rev 46
 *   Task kok_basa#52927: Integrate MediaPlayerClient into hmi_radio_process
 *   - Added debug module ID for MediaPlayerClient.
 *
 * - 10-Oct-2011 Larry Piekarski Rev 45
 *   - Task 52794: Integrated Goldenized ICS Controls Server
 *
 * - 10-Oct-2011 Darinka Lopez  Rev 44
 * - SCR kok_basa#14298: Integrate PITs handler
 *
 * - 07-Oct-2011 Larry Piekarski Rev 43
 *   - Task 52581: Integrated Goldenized System State Server. Fixed file revision.
 *
 * - 05-Oct-2011 Coppock, Jonathan (dzhk56) Rev 42.1.5
 *   - SCR kok_basa#15950: "TMC: Integrate the TMC module into the SBX project"
 *   - Task kok_basa#52295: "TMC: Integrate the TMC module into the SBX project"
 *     + Initial integration of the TMC BBC into the SBX project.
 *
 *  -01-Oct-2011 Natesh.K.N  Rev 42.1.3
 *   - Task kok_basa 51803: Integrate Favourites Client
 *
 *   30-Sep-2011 Manuel Robledo Rev 42.1.2
 *   Task kok_basa#51092 Integrate HVACSettings to most servers
 *
 *   30-Sep-2011 Wanda Jimenez Rev 42.1.1
 *   Task kok_basa#51431 Integrate MediaPlayer to most servers
 *
 *  - 28 Sept-2011 Gouri Naik Rev 42
 *   -Task kok_basa#50824 Amplifier server events added.
 *
 *  - 26 Sept-2011 Shaoli Dai Rev 41
 *      Integrated favorites manager Servers
 *
 * - 26-Sep-2011 Jaime Almeida  Rev 40
 *   - SCR kok_basa#15266/Task kok_basa#50236: SBX MARS Integration in SBX (IT113839)
 *     - Add back Media_Player, MSD VPD(Engine) and MSM messages.
 *
 * - 20 Sept-2011 Dan Carman
 *      Integrated new AVManager and MOST Servers
 *      Removed media messages
 *
 * - 14-Sep-2011 Jaime Almeida  Rev 38
 *   - SCR kok_basa#14536/Task kok_basa#48065: Integrate MSD VPD in SBX.
 *     - Add MSD VPD and MSM messages.
 *
 * -14-Sept-2011 Gouri Naik  Rev 37
 * - Task kok_basa 48552: Amplifier server events added.
 *
 * -07-Sept-2011 Arturo lopez  Rev 36
 * - Task kok_basa 47860: Integrate player into Silverbox project.
 *
 *   04-Sep-2011 Lipchik_Chris Rev 35
 *   SCR kok_basa#13774/Task kok_basa#47410
 *   Integrate and test latest AM/FM, DAB, Tuner Mgr & Tuner Driver BBs.
 *
 * - 31-Aug-2011 Larry Piekarski  Rev 34
 *   - Task 46952: Remove unneeded RSA module.
 *
 * - 29-Aug-2011 Larry Piekarski Rev 33
 *   - Task 46403: Move callouts to process specific folders. Removed unused
 *     stub file.
 *
 * - 24-Aug-2011 Larry Piekarski  Rev 32
 *   - Task 46014: Updated to the golden GMLAN Gateway Client
 *
 * 18-Aug-2011 Oscar Vega  Rev 31
 * Task kok_basa#44847: Integrate calibrations into main application.
 *
 *   16-Aug-2011 Chris Lipchik  Rev 30
 *   SCR kok_basa#13587/Task kok_basa#43603
 *   Integrate latest Tuner BBs including DAB.
 *
 * - 15-AUG-2011 David A. Johnson  Rev 29
 *   Task kok_basa#44322: Add bb_gmsbx14_DABFMTunerClient to process_hmi_radio
 *   - Added events for DABFMTunerClient.
 *
 * - 12-AUG-2011 David A. Johnson  Rev 28
 *   Task kok_basa#44170: Add bb_gmsbx14_GMLANGatewayClient to process_hmi_radio
 *   - Added events for GMLANGatewayClient.
 *
 * 9-Aug-2011 David Mooar  Rev 27
 * SCR kok_basa#10539: Implement Language Selection in GMLAN Gateway Server.
 *
 * - 04-AUG-2011 David A. Johnson  Rev 25
 *   Task kok_basa#42894: Add AuxiliaryInputJackClient to process_hmi_radio
 *   - Added events for AuxiliaryInputJackClient.
 *
 * - 02-AUG-2011 David A. Johnson  Rev 24
 *   Task kok_basa#42403: Add bb_gmsbx14_BluetoothSettingsClient to process_hmi_radio
 *   - Added events for BluetoothSettingsClient.
 *
 * - 29-JUL-2011 David A. Johnson  Rev 23
 *   Task kok_basa#42023: Add bb_gmsbx14_AudioDiskPlayer to process_hmi_radio
 *   - Added ADPCLIENT events.
 *
 * - 26-JUL-2011 Gouri Naik  Rev 22
 *   Task kok_basa#41662: Pull Chimes_Facade to main project.
 *   - Added CHIMES events.
 *
 * - 20-JUL-2011 David A. Johnson  Rev 21
 *   Task kok_basa#40737: Add bb_gmsbx14_FavoritesManagerClient to process_hmi_radio
 *   - Added FavoritesManagerServer events.
 *
 * - 19-Jul-2011 Jaime Almeida  Rev 20
 *   SCR kok_basa#12244/Task kok_basa#40026: Integrate AllGo DeviceManager and Gateway.
 *   - Added DAG events.
 *
 * - 13-Jul-2011 Chris Baker  Rev 19
 *   Task 40067: Integrate Bluetooth Stack and Fb Server
 *   - Added Bluetooth events.
 *
 * 07-Ju1-2011 Juan Carlos Castillo  Rev 18
 * SCR kok_basa#10713 Integrate bb_gm_diag_handler to aa1024ae project
 *
 * - 05-Ju1-2011 Wanda Jimenez  Rev 17
 *   - Task 38587: Integrate bb_MediaPlayerServer
 *
 * 04-May-2011 Natesh.K.N  Rev 12
 * SCR kok_basa#8497: HMI Events
 *
 * 22-March-2011 David Mooar  Rev 7
 * SCR kok_basa#6657: Initial GMLAN Interface.
 */
/*===========================================================================*/
/** @} doxygen end group */
#endif /* XSAL_EVENT_ID_H */
