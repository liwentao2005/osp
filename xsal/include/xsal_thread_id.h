#ifndef XSAL_THREAD_ID_H
#   define XSAL_THREAD_ID_H
/*===========================================================================*/
/**
 * @file xsal_thread_id.h
 *
 *   Configuration file assigns thread ids for each process in the system.
 *
 * %full_filespec:xsal_thread_id.h~63.1.7.2.2.1.2.2.4.1.4:incl:ctc_ec#147 %
 * @version %version:63.1.7.2.2.1.2.2.4.1.4 %
 * @author  %derived_by:tjcthj %
 * @date    %date_modified:Sat Oct 12 16:26:50 2019 %
 *
 *------------------------------------------------------------------------------
 *
 * Copyright 2011 Delphi Technologies, Inc., All Rights Reserved.
 * Delphi Confidential
 *
 *------------------------------------------------------------------------------
 *
 * @section DESC DESCRIPTION:
 *
 *   Thread IDs must be unique within each process. This file provides the single
 *   location for the assignment of these IDS.
 *
 *    A seperate enumeration should be defined for each process
 *
 * @section ABBR ABBREVIATIONS:
 *
 * @section TRACE TRACEABILITY INFO:
 *   - Design Document(s):
 *
 *   - Requirements Document(s):
 *
 *   - Applicable Standards (in order of precedence: highest first):
 *     - <a href="http://kogespw1.delcoelect.com:8508/passthru/consumer?name=SW%20REF%20264.15D&doctype=K8DBSDoc">
 *       SW REF 264.15D "Delphi C Coding Standards" [12-Mar-2006]</a>
 *
 * @section DFS DEVIATIONS FROM STANDARDS:
 *   - None
 *
 */
/*==========================================================================*/

/*===========================================================================*
 * Header Files
 *===========================================================================*/
#include "xsal_settings.h"

/*===========================================================================*
 * #define Constants
 *===========================================================================*/

/*===========================================================================*
 * #define MACROS
 *===========================================================================*/

/*===========================================================================*
 * Custom Type Declarations
 *===========================================================================*/

/**
 * This type provides unique thread IDs for APP_PROCMAN
 */

enum Procman_Thread_Id_Tag
{
  NAME_SERVER_THREAD = XSAL_FIRST_APPLICATION_THREAD_ID,
  XSAL_TIMER_THREAD_ID,
  TIMER_TICK_THREAD_ID,
  PM_MAIN_THREAD,
  PM_EXIT_MONITOR_THREAD,

  PM_LAST_THREAD_ID
};


/**
 * This type provides unique thread IDs for EARLY_START_PROCESS_ID
 */
enum Early_Start_Thread_Id_Tag
{
   EARLY_START_NO_THREAD_ID = 0,   /* DO NOT MOVE. Must be first in list. */

   ANIMATED_SPLASH_THREAD_ID = XSAL_FIRST_APPLICATION_THREAD_ID,
   ES_APPLICATION_MANAGER_THREAD_ID,
   ES_XSALMT_THREAD_ID,
   GMLAN_RX_THREAD_ID,
   GMLAN_TX_THREAD_ID,
   SOH_MANAGER_THREAD_ID,
   VIP_DESIP_RECEIVE_THREAD_ID,
   VIP_DESIP_TRANSMIT_THREAD_ID,
   VIDEO_CONTROL_THREAD_ID,
   LAYER_MANAGER_THREAD_ID,
   LAYER_MANAGER_XENA_THREAD_ID,
   LAYER_MANAGER_FLUSH_THREAD_ID,
   VIDEO_CAPTURE_THREAD_ID,
   XENA_ACCEPT_THREAD_ID,
   XENA_MSG_THREAD_ID,
   DRAW_GUIDELINES_THREAD_ID,
   DRAW_GUIDELINES_IMPLEMENTATION_THREAD_ID,
   HW_INITIALIZE_THREAD_ID,/* add by YangJF */
   PS_THREAD_ID,/*add by hzlyvm*/
   CAN_SERVER_THREAD_ID,     /*add by csj*/
   ES_SECURITY_LAUNCH_ID,    /*add by csj*/
   CALS_THREAD_ID,			/*add by hzlyvm*/
   BEV_SOCKET_SERVER_THREAD_ID,			/*add by hzlyvm*/
   APA_SOCKET_SERVER_THREAD_ID,			/*add by hzlyvm*/
   HISIP_AP_RX_THREAD_ID,/* add by zhiwei chen */
   HISIP_M4_RX_THREAD_ID,/* add by zhiwei chen */
   BACKGROUND_THREAD_ID,/* add by zhiwei chen */
   BEV_FRAME_DUMP_THREAD_ID,			/*add by liuchen*/
   SOH_HELPER_THREAD_ID,
   EARLY_START_LAST_THREAD_ID     /* DO NOT MOVE. Must be last in list. */
};

enum Flash_Service_Thread_Id_Tag
{
   FLASH_NO_THREAD_ID = 0,   /* DO NOT MOVE. Must be first in list. */

   FLASH_APPLICATION_MANAGER_THREAD_ID = XSAL_FIRST_APPLICATION_THREAD_ID,
   FBL_MGR_THREAD_ID,
   FBL_LAUNCHER_THREAD_ID,
   FBL_WORK_THREAD_ID,
   FBL_HMI_THREAD_ID,
   FBL_GEM_THREAD_ID,
   TBOX_SS_THREAD_ID,
   TBOX_DISP_THREAD_ID,
   TBOX_TEST_THREAD_ID,
   FMC_THREAD_ID,
   FMB_THREAD_ID,
   HSM_OTA_THREAD_ID,
   HSM_MNF_THREAD_ID,
   CGM_TEST_THREAD_ID,
   FLASH_LAST_THREAD_ID
};


/**
 * This type provides unique thread IDs for SBX_PROCESS_ID
 */
enum SBX_Core_Thread_Id_Tag
{
   SYSTEM_NO_THREAD_ID = 0,   /* DO NOT MOVE. Must be first in list. */

   APPLICATION_MANAGER_THREAD_ID = XSAL_FIRST_APPLICATION_THREAD_ID,
   AUDIO_MGR_TASK_ID,
   SSND_THREAD_ID,
   SOUND_PLAYBACK_THREAD_ID,
   CONNECTION_MANAGER_THREAD_ID,
   DIAG_CLIENTS_HANDLER_THREAD_ID,
   DIMMING_GM_THREAD_ID,
   ED_TERM_THREAD_ID,
   ED_TERM_RXTX_TCP_THREAD_ID,
   GM_DIAG_HANDLER_THREAD_ID,
   PITS_MFG_SERVICE_THREAD_ID,
   PITS_APPLICATION_THREAD_ID,
   PHONE_CALL_MGR_THREAD_ID,
   TUNER_SOCKETSERVER_THREAD_ID,
   AMFM_THREAD_ID,
   AMFM_BGND_THREAD_ID,
   RDS_DEC_THREAD_ID,
   TUNER_MGR_THREAD_ID,
   XSALMT_THREAD_ID,
   XSALMT_PRIORITY_THREAD_ID,
   PM_APP_THREAD_ID,
   SYSTEM_STATE_SERVER_THREAD_ID = PM_APP_THREAD_ID,
   SYSTEMSTATE_SOCKETSERVER_THREAD_ID,
   AV_MANAGER_SERVER_THREAD_ID,
   VIRTUALSOURCE_PROMPT_SERVER_THREAD_ID,
   ENG_MODE_THREAD_ID,
   ENG_MODE_OUTPUT_FILE_THREAD_ID,
   ENGMODE_SOCKETSERVER_THREAD_ID,
   ENGMODE_LINUX_LOG_MGR_THREAD_ID,
   ENGMODE_ANDROID_LOG_MGR_THREAD_ID,
   SETTING_SOCKETSERVER_THREAD_ID,
   PS_SOCKETSERVER_THREAD_ID,
   AUDIO_SOCKETSERVER_THREAD_ID,
   MIC_SOCKETSERVER_THREAD_ID,
   SBX_SECURITY_LAUNCH_ID,    /*add by csj*/
   NETWORK_MGR_THREAD_ID,
   NETWORK_MGR_EVENT_THREAD_ID,
   ECNR_MGR_MSG_THREAD_ID,
   HFAP_MSG_THREAD_ID,
   TBOX_AUDIO_MGR_THREAD_ID,
   EXTERNAL_LOG_SOCKETSERVER_THREAD_ID, /* add by Baodong Kan@20170516 */
   VIP_DIAG_PROXY_THREAD_ID,
   ANIMATION_SYNC_TASK_ID,
   USERTIME_MGR_THREAD_ID,
   cluster_client_THREAD_ID, /*ADD by bo.hu, 20180313*/
   DBA_DATA_COLLECTION_THREAD_ID,
   DBA_SOCKET_SERVER_THREAD_ID,
   SYSTEM_LAST_THREAD_ID     /* DO NOT MOVE. Must be last in list. */
};


enum ECD_Thread_Id_Tag
{
	ECD_NO_THREAD_ID = 0,	/* DO NOT MOVE. Must be first in list. */
	ECD_APPLICATION_MANAGER_THREAD_ID = XSAL_FIRST_APPLICATION_THREAD_ID,	
	ECD_IF_THREAD_ID,
	ECD_TX_THREAD_ID,
	ECD_RX_THREAD_ID
};


#define VO_MSG_THREAD_ID          XSALMT_THREAD_ID
#define SSM_THREAD_ID             AV_MANAGER_SERVER_THREAD_ID

/**
 * This type provides unique thread ids for the threads in the nglv_bluetoothd
 * process.
 * add by dzyfvd
 */
enum CM_Thread_Id_Tag
{
   BT_CM_NO_THREAD_ID = 0,   /* DO NOT MOVE. Must be first in list. */

   BT_CM_APPLICATION_MANAGER_THREAD_ID = XSAL_FIRST_APPLICATION_THREAD_ID,
   BETULA_EVENT_THREAD,      /**< handles Betula API -> XSAL translation */
   BT_XSAL_GATEWAY_THREAD,   /**< handles XSAL Proxy -> Betula API translation */
   BETULA_TRANSPORT_THREAD,  /**< placeholder thread ID to add stack threads to SAL_Initial_Thread_Attrs structure */
   BT_CM_SPP_THREAD,         /* SPP handler thread */
   BT_SOCKETSERVER_THREAD,

   BT_MAP_SESSION_MGR_THREAD_ID,
   MAPDB_SERVER_THREAD_ID,

   BT_STORAGE_MANAGER_XSAL_RECEIVE_THREAD,
   PBDB_SERVER_THREAD_ID,
   PBDB_CONTACT_THREAD_ID,
   BT_LE_THREAD, /** handles the messages from the betula LE module */
   BT_STRM_VPD_THREAD,          /*handles the message from Betula and BT_STRM_VPD_CLIENT*/
   BT_CM_LAST_THREAD_ID      /* DO NOT MOVE. Must be last in list. */
};

#define BUC_THREAD_ID                 XSALMT_THREAD_ID


/**
 * This type provides unique thread ids for the threads in the nglv_wifi
 * process.
 * add by lz34m9
 */
enum NGLV_Wifi_Thread_Id_Tag
{
   WIFI_APM_THREAD_ID = XSAL_FIRST_APPLICATION_THREAD_ID,
   WIFI_PROCESS_CTL_THREAD_ID,
   WIFI_MGR_THREAD_ID,
   WIFI_DIAGNOSE_THREAD_ID,
   WIFI_SOCKETSERVER_THREAD_ID,
   WIFI_ANDROID_IDC_GATEWAY_THREAD_ID,
   WIFI_LAST_THREAD_ID     /* DO NOT MOVE. Must be last in list. */
};

#define WIFI_MAX_ANONYMOUS_THREAD 6

/**
 * This type provides unique thread ids for the threads in the vr
 * process.
 * add by qz3lqw
 */
enum SPEECH_MGR_Thread_Id_Tag
{
   SPEECH_APM_THREAD_ID = XSAL_FIRST_APPLICATION_THREAD_ID,
   SPEECH_CORE_PROCESS_CTRL_THREAD_ID,
   SPEECH_ASAP_SERVER_CTRL_THREAD_ID,
   SPEECH_ASAP_CLIENT_CTRL_THREAD_ID,
   SPEECH_PROMPT_MANAGER_THREAD_ID,
   SPEECH_VR_MANAGER_THREAD_ID,
   PROMPT_MGR_REMINDER_HANDLER_THREAD_ID,
   PROMPT_MGR_REMINDER_WORKER_THREAD_ID,
   VR_MGR_REMINDER_HANDLER_THREAD_ID,
   VR_MGR_NAVI_HANDLER_THREAD_ID,
   SPEECH_MGR_LAST_THREAD_ID     /* DO NOT MOVE. Must be last in list. */
};

/**
 * This type provides unique thread IDs for TOUCH_PROCESS_ID
 */
enum Touch_Thread_Id_Tag
{
   TOUCH_NO_THREAD_ID = 0,   /* DO NOT MOVE. Must be first in list. */

   TOUCH_APPLICATION_MANAGER_THREAD_ID  = XSAL_FIRST_APPLICATION_THREAD_ID,
   GESTURE_MANAGER_THREAD_ID,
   TOUCHSCREEN_MSG_THREAD_ID,
   TOUCHSCREEN_COLLECT_THREAD_ID,
   TSC_DAEMON_THREAD_ID,
   TSC_PROCESS_THREAD_ID,
   TSC_COORDINATE_THREAD_ID,
   RAWINPUT_MANAGER_MAIN_THREAD_ID,
   RAWINPUT_TOUCH_COLLECT_THREAD_ID,
   RAWINPUT_KEY_COLLECT_THREAD_ID,
   RAWINPUT_SIMULATION_MAIN_THREAD_ID,
   RAWINPUT_SIMULATION_COLLECT_THREAD_ID,
   RAWINPUT_SIMULATION_SOCKET_THREAD_ID,
   RAWINPUT_TOUCH_VALUES_SEND_TO_M4_THREAD_ID,
   TOUCH_LAST_THREAD_ID     /* DO NOT MOVE. Must be last in list. */
};
#define GESTURE_THREAD_ID     GESTURE_MANAGER_THREAD_ID
#define TOUCHSCREEN_THREAD_ID TOUCHSCREEN_MSG_THREAD_ID
#define TS_COLLECT_THREAD_ID  TOUCHSCREEN_COLLECT_THREAD_ID

/**
 * This type provides unique thread ids for carplay process
 */
enum Media_Manager_Threads_Tag
{
   MEDIA_PROCESS_APM_THREAD_ID = XSAL_FIRST_APPLICATION_THREAD_ID,
   /* Add additional thread IDs here */
   MEDIA_PROCESS_DEV_MANAGER_THREAD_ID,
   MEDIA_PROCESS_USB_WORKER_THREAD_ID,
   MEDIA_PROCESS_ANALOG_AUX_JACK_DETECTOR_THREAD_ID,
   MEDIA_PROCESS_DIGITAL_AUX_JACK_DETECTOR_THREAD_ID,
   MEDIA_PROCESS_BT_AUDIO_MANAGER_THREAD_ID,
   MEDIA_PROCESS_BT_AUDIO_SUPPLIER_THREAD_ID,
   MEDIA_PROCESS_BT_AUDIO_PLAYER_THREAD_ID,
   MEDIA_PROCESS_IPOD_DETECTOR_THREAD_ID,
   MEDIA_PROCESS_LAST_THREAD_ID      /* DO NOT MOVE. Must be last in list. */
};

/**
 * This type provides unique thread ids for aps_core process
 */
enum APS_Core_Thread_Id_Tag
{
   APS_CORE_PROCESS_APM_THREAD_ID = XSAL_FIRST_APPLICATION_THREAD_ID,
   APS_CORE_PROCESS_CTL_THREAD_ID,
   APS_CORE_WDOG_THREAD_ID,    /* handles events from SS bus  */
   APS_VR_THREAD_ID,             /* handles events from Android VR Service */
   APS_TTS_THREAD_ID,            /* handles events from Android TTS Service */
   APS_REMINDER_THREAD_ID,       /* handles events from Android Reminder apk */
   BT_SPP_SS_CLIENT_THREAD,      /* handles spp/pty messages from Android side */
   APS_REMINDER_TRIGGER_CHK_THREAD_ID,
   APS_REMINDER_DB_SERVER_THREAD_ID,
   BT_LE_GATTC_IDC_GATEWAY_THREAD, /* handles messages from the Android socket client */
   CAN_APS_SERVER_THREAD_ID,  /*add by jlz*/
   CAN_APS_SERVER_CONTROL_THREAD_ID,
   APS_AUDIO_THREAD_ID,          /*handles events from Android Audio Service*/
   APS_SYSTEM_MAIN_THREAD_ID,        /*handles platform level events for Android And Linux */
   APS_NAVI_THREAD_ID,             /* handles events from Android NAVI Service */
   APS_NAVI_CONTROL_THREAD_ID,
   APS_REMOTELOG_THREAD_ID,
   APS_CORE_LAST_THREAD_ID      /* DO NOT MOVE. Must be last in list. */
};

enum Security_Mgr_Thread_Id_Tag
{
   SECURITY_APM_THREAD_ID = XSAL_FIRST_APPLICATION_THREAD_ID,
   SECURITY_MGR_THREAD_ID,
   SECURITY_MGR_LAST_THREAD_ID      /* DO NOT MOVE. Must be last in list. */
};


/** * For pki process. * add by lz34m9 */
enum NGLV_PKI_Thread_Id_Tag {   
    PKI_APM_THREAD_ID = XSAL_FIRST_APPLICATION_THREAD_ID,  
    PKI_PROCESS_CTL_THREAD_ID,  
    PKI_MGR_THREAD_ID,   
    PKI_LAST_THREAD_ID /* DO NOT MOVE. Must be last in list. */
};


/**
*this type provide unique thread id for tbox service process
*/
enum Tbox_Service_Thread_Id_Tag
{
    TBOX_APM_THREAD_ID = XSAL_FIRST_APPLICATION_THREAD_ID,
    TBOX_MESSAGE_RECEIVE_THREAD_ID,
    TBOX_REALLOG_MESSAGE_RECEIVE_THREAD_ID,
    TBOX_MESSAGE_DISPATCH_THREAD_ID,
    TBOX_MESSAGE_SEND_THREAD_ID,
    V2X_MESSAGE_RECEIVE_THREAD_ID,
    V2X_MESSAGE_DISPATCH_THREAD_ID,
    V2X_MESSAGE_SEND_THREAD_ID,
    V2X_REALLOG_MESSAGE_RECEIVE_THREAD_ID,
    TBOX_LAST_THREAD_ID  /* DO NOT MOVE. Must be last in list. */
};

/*===========================================================================*/
/*!
 * @file xsal_thread_id.h
 *
 * @section RH REVISION HISTORY (top to bottom: last revision to first revision)
 *
 * 29Nov2017  Rahul Chirayil (vzm576)
 * ctc_ec#202346: Integrate animation sync component to project.
 *
 * 11-Jul-2017 Ashwini Sidhaye(pj5njw)
 * ctc_ec#188769: Added DIAG_PROXY thread ID
 *
 * 24-Fed-2017 wangshihua
 *  Add pki threads
 *
 * 21-Feb-2017 Gouri Naik Rev 49
 *   - 
 *
 * 23-Nov-2016 Luis Solis Rev 46.1.15
 *   - Task ctc_ec#169696: [NGI2][Media] Integrate Gracenote with 4.4 kernel support
 *
 * 03-Nov-2016  Haneef Syed
 *   - Task: ctc_ec#165748: HF Audio processing integration
 *
 * 28-Sep-2016  pjr6cf  Rev 46.1.3  
 * ctc_ec#task163427[NGI2][Bluetooth]: BT Message API Interface changes
 *
 * 5-Sep-2016 Yuan Kanglin
 * + ctc_ec#161927:[NGI2][Network_Mgr] integrate network manager
 *
 * 29Aug2016  Devaraj Herle (rz35sz)
 * ctc_ec#161433: Integrating PITS Baseline to project
 *
 * 25-Aug-2016 Arun.R.Sundararaju@delphi.com (mz7kvv) Rev 40
 * + Task:ctc_ec#161189: Add WIFI_ANDROID_IDC_GATEWAY_THREAD_ID for APS handling.
 *
 * 24-Aug-2016 Luis Solis (tzg0f7) Rev 39
 * + Task ctc_ec#161106: [NGI2][Media] Ask driver capabilities for digital aux source
 *
 * 19-Aug-2016 dzphcr Rev 36
 * + Task:ctc_ec#160774: Move SPP SS client thread from bt_connection_mgr to aps_core
 *
 * 17-Aug-2016 Punith Gangadhara 26
 * + ctc_ec#160595 Added GATTC_HANDLER thread to APS_Core process
 *
 * 8-August-2016 Raja
 * +  ctc_ec# 159818 Added system sound block
 *
 * - 08-aug-2016 dzphcr Rev 24
 *   -Task: ctc_ec#159971: Added SPP related thread Ids.
 *
 * 12-July-2016 Gouri Naik
 * + ctc_ec#157494   Audio Mgr added
 *
 * 23-Dec-2014 wangshuquan
 * + ctc_ec#94471 commit digital aux code
 *
 * -27-Nov-2014 fangyan
 * ctc_ec#90826 : update WIFI SDK 6.2.1
 *                modify max anonymous threads.
 *
 * -12-Nov-2014 Lu Yinyin
 *   -Add carplay thread id
 *
 * - 03-Jun-2014 Milan Tian
 *  - add VR_NAVI_NATIVE_INTERFACE_THREAD_ID
 *
 * - 14-May-2014 Wang Le Rev 85
 *   - add LAYER_MANAGER_XENA_THREAD_ID.  
 * 
 * 25-Feb-2014 wang min remove old HMI from project
 * + bbc_sgmnglv\support\NAF\bbc_onstar_native_interface\bb_gmlan_gateway_native_interface\bb_gmlan_gateway_nai_imp\_src\GMLANGateway_Client.cpp
 * + bbc_sgmnglv\processes\system_persistence\nglv_board_options_ps.cpp
 *
 * -8-Jan-2014 Bao Qifan 75
 * -Task: 56878 - [NGK PITS] add screen check function for pits
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
 * -12-Dec-2013 Gene Hu 69
 * -Add TSC_DAEMON_THREAD_ID,TSC_PROCESS_THREAD_ID,TSC_COORDINATE_THREAD_ID,
 *
 * -18-Nov-2013 HuiBin Li 62
 *  -Add XENA_ACCEPT_THREAD_ID and XENA_MSG_THREAD_ID
 *
 * -15-Nov-2013 Alex Lu Rev 50
 * -Task: 51680 - add nav most server
 *
 * - 14-Nov-2013 Ethan Liu An Rev 61
 *   -Add NAF Onstar module
 *
 * - 16-Oct-2013 Wang Le Rev 60
 *   -Delete most_server process and move the relative thread to nglv_core process
 *
 * - 14-Aug-2013 Paul Xia An Rev 53
 *   -Add Map session and Map db module
 *
 * - 13-Aug-2013 Wang Shihua  Rev 52
 *   -Add Wifi diagnose thread id module
 *
 * - 31-Jul-2013 Angelo An  Rev 51
 *   -Add MirrorLink Mgr module
 *
 * - 23-Jul-2013 wang bing  Rev 50
 *   -Add naf calibration module
 *
 * - 15-Jul-2013 HuiBin Li Rev 49
 *   -Add reminder module
 *
 * -05-Jul-2013 Ray Zhang 48
 *  -add CONNECTION_MANAGER_THREAD_ID
 *
 * -26-June-2013 Angelo An Rev 46
 *  -Add the thread both for MirrorLink and MirrorLink Client (just for testing)
 *
 * -13-Jun-2013 Ray Zhang Rev 45
 * - add PANDUN_CLIENT_THREAD_ID
 *
 * -30-May-2013 Alex Lu Rev 41
 * -Task: 39806 - add NAV_DR_THREAD_ID
 *
 * -21-May-2013 Arthur C 40
 *  -Add USDT TX thread ID. 
 *
 * -16-May-2013 Wang Shihua 40
 *  -Change wifi thread id name and add wifi native interface thread id
 *
 * -30-Apr-2013 Ray Zhang 39
 *  -Change CM_Thread_Id_Tag based on latest bluetooth module
 *  -Add BLUETOOTH_SETTINGS_CLIENT_THREAD_ID, TELEPHONE_CLIENT_THREAD_ID in NAF_Interface_Thread_Id_Tag
 *
 * -22-Apr-2013 Wang Le 38
 *  -Add key manager client module thread id. 
 *
 * -19-Apr-2013 Paul Xia 37
 *  -Add bt_storage_mgr and phonebook_db.
 *
 * -18-Apr-2013 Arthur C 36
 *  -Add NAF_LOADER_THREAD_ID 
 *
 * -17-Apr-2013 Li HuiBin 35
 *  -Add TS_COLLECT_THREAD_ID 
 *
 * -08-Apr-2013 Wang Le 34
 *  -Add AV_CONNECTION_MANAGER_THREAD_ID and AV_MANAGER_SERVER_THREAD_ID 
 *
 * -27-Mar-2013 Zhang Hang 33
 *  -Add layer manager flush thread id
 *
 *	-19-March-2013 shaofei 32
 *	Add  MOST TTS_MOST_SERVER_THREAD_ID
 *
 *	-28-Feb-2013 wang bing 31
 *	Add  HMI REARCAMERA_THREAD_ID	
 *
 * -25-Feb-2013 Zhang Hang 30
 *  -Add layer manager thread id
 *
 * -22-Feb-2013 Arthur Chen 22 
 *  -Add VEHICLEINFORMATION_Thread_Id_Tag
 *
 * -5-Feb-2013 Danny Kong 21 
 *  -Add TEST_HMI_Radio_Thread_Id_Tag
 *
 * -31-Jan-2013 Judy Zhu 20 
 *  -Add most app thread in NGLV CORE.
 *
 * -30-Jan-2013 Li Hui 19  
 *  -Add video control.
 *
 *
 * 23-Jan-2013 Danny Kong  Rev 25
 *  - Add media test client
 *
 * 21-Jan-2013 shaofei  Rev 24
 *  - Add vr id
 *
 * 17-Jan-2013 Danny Kong  Rev 23
 *  - Add diag client handler
 *
 *- 08-Jan-2013 Bao Qifan Rev 22
 *   - add sinad related thread id(SINAD_TASK_THREAD_ID,SINAD_PROCLOOP_THREAD_ID,)
 *
 *- 03-Jan-2013 Danny Kong Rev 19
 *   - add sd copy thread id
 *
 * - 03-Jan-2013 Ethan Liu Rev 18
 *   - remove GMLAN_CUSTOMIZATION_RECEIVE_THREAD_ID
 *
 * -25-dec-2012 li huibin Rev 17
 *   - Add TOUCHSCREEN_THREAD_ID & GESTURE_THREAD_ID,
 *
 * -24-Dec-2012 Alex Lu Rev 16
 *  -Add GPS thread id 
 *
 * - 30-nov-2012 Peggy
 *   - Add DIMMING_GM_THREAD_ID
 *
 * - 15-nov-2012 Ethan Liu Rev 14
 *   - Add FACEPLATE CONTROL thread
 *
 * - 15-Nov-2012 Danny Kong  Rev 13
 *   -Add SD engine thread IDs;
 *
 * - 13-Nov-2012 Ginger Jiang(qzb3mh)  Rev 12
 *   -Add wifi manager thread IDs;
 *
 * - 08-Nov-2012 Ginger Jiang(qzb3mh)  Rev 11
 *   -Add a thread ID for HMI message handler;
 *
 * - 07-Nov-2012 Wang Le Rev 10
 *   - Add engineering mode and setting thread message id. 
 *
 * - 06-nov-2012 Ethan Liu Rev 9
 *   - Add GMLAN CUSTOMIZATION threads
 *
 * - 23-oct-2012 Zhang Hang Rev 8
 *   - Add thread of naf interface.
 *
 * - 18-Oct-2012 Zhou Joey(cz1x9b)  Rev 6
 *   ctc_ec#30572:[GMLAN] - Enable gmlan tx message,confirm LSCAN tx work normally;
 *
 * - 24-Aug-2012 Zhang Hang  Rev 4
 *   Fake gmlan tx thead id. Temporarily solution to disable messive gmlan tx message. Need to remove after gmlan working.
 *
 */
/*===========================================================================*/
#endif /* XSAL_THREAD_ID_H */
