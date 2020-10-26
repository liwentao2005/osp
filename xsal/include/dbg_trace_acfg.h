#ifndef DBG_TRACE_ACFG_H
#   define DBG_TRACE_ACFG_H
/*===========================================================================*/
/**
 * @file dbg_trace_acfg.h
 *
 *   Defines default configurations for the debug trace module.
 *
 * %full_filespec:dbg_trace_acfg.h~53.1.4:incl:ctc_ec#149 %
 * @version %version:53.1.4 %
 * @author  %derived_by:tjcthj %
 * @date    %date_modified:Sat Oct 12 16:26:39 2019 %
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
 *   The contents of this file are project-specific and must be configured by
 *   a project using the debug trace module.
 *
 * @section ABBR ABBREVIATIONS:
 *   - TR - TRace
 *
 * @section TRACE TRACEABILITY INFO:
 *   - Design Document(s):
 *     - SDD_10016705_BASA_dbg_trace.doc
 *
 *   - Requirements Document(s):
 *     - BASA_SRS_Error_Management_1.2.doc
 *
 *   - Applicable Standards (in order of precedence: highest first):
 *     - <a href="http://kogespw1.delcoelect.com:8508/passthru/consumer?name=SW%20REF%20264.15D&doctype=K8DBSDoc">
 *       SW REF 264.15D "Delphi C Coding Standards" [12-Mar-2006]</a>
 *
 * @section DFS DEVIATIONS FROM STANDARDS:
 *   - none
 *
 * @addtogroup dbg_trace_client
 * @{
 */
/*==========================================================================*/

/*===========================================================================*
 * Header Files
 *===========================================================================*/


/* ! The inclusion of header files should NOT be inside the extern "C" block */
#   ifdef __cplusplus
extern "C"
{
#   endif                       /* __cplusplus */
/*===========================================================================*
 * Exported Preprocessor #define X-MACROS
 *===========================================================================*/

/**
 * Only define TR_DISABLE_EM_FILE_ID if the system is going to use an
 * alternate method for identifying files for trace than by sharing the
 * EM module's EM_F_ID.
 */
/*#   define TR_DISABLE_EM_FILE_ID 1 */

/**
 * Defines the default compile-time verbosity of the debug trace logic.
 *
 * @note
 *
 *   - Can be overridden on a per-file basis by defining TR_COMPILE_VERBOSE
 *     in the file prior to including dbg_trace.h.
 *
 *   - The value must be one of: TR_COMPILE_DISABLED, TR_COMPILE_COMPACT, or
 *     TR_COMPILE_VERBOSE.
 *
 *   - Because this is a compile-time option, nothing can be done at run time
 *     that is not compatible with the verbosity a file is compiled with; e.g.,
 *     if tracing is compiled out (TR_COMPILE_DISABLE), for a file, then there
 *     is no way to get trace information from the file without re-compiling it
 *     with a different setting.
 */
#   define TR_DEFAULT_COMPILE_VERBOSITY TR_COMPILE_VERBOSE

/**
 * Defines the default minimum level of informational trace messages that are
 * enabled at compile-time for a file.
 *
 * @note
 *
 *   - This can be overridden on a per-file basis by defining
 *     TR_COMPILE_INFO_LEVEL in the file prior to including dbg_trace.h.
 *
 *   - The value must be set to one of the trace levels: TR_LVL_FAULT,
 *     TR_LVL_WARN, TR_LVL_NOTIFY, TR_LVL_INFO_HI, TR_LVL_INFO_MID, or
 *     TR_LVL_INFO_LO.
 *
 *   - The fault and warning trace messages are not affected by this setting -
 *     they cannot be compiled out; however, setting the level to either
 *     TR_LVL_FAULT or TR_LVL_WARN will cause all other levels to be compiled
 *     out.
 *
 *   - Because this is a compile-time option, nothing can be done at run time
 *     that is not compatible with the INFO level selection a file is compiled
 *     with; e.g., if TR_LVL_INFO_HI is the setting a file is compiled with,
 *     there is no way to get TR_LVL_INFO_MID or TR_LVL_INFO_LO trace
 *     information from the file without re-compiling it with a different
 *     setting.
 */
#   define TR_DEFAULT_COMPILE_INFO_LEVEL TR_LVL_INFO_LO

#   undef Tr_Module_ID    /* Remove any stray definitions from other modules */
#   undef Tr_Module_ID_EQ /* Remove any stray definitions from other modules */

/**
 * X-Macro to defining enumeration for a module ID
 */
#   define Tr_Module_ID(ID, name) ID,

/**
 * X-Macro to defining enumeration for a module ID, and assign it a specific value.
 */
#   define Tr_Module_ID_EQ(ID, id_value, name) ID=id_value,

/**
 * This X MACRO declares the project-specific list of modules ids in the system.
 * There is a corresponding X MACRO in the implementation configuration that
 * MUST have the same list of modules (a compile-time check is made for this).
 * Whenever you change this X MACRO, you MUST make an equivalent change to the
 * other one. The implementation X MACRO is kept separate so that a re-compile
 * of the entire program is not triggered by an adjustment to the initial trace
 * level settings. If these settings were part of this X MACRO (in the API),
 * all modules would need to be recompiled due to such a change even though none
 * of them would be affected (only the dbg_trace implementation changes for the
 * initial level settings). All this X MACRO does is declare the symbols used
 * for the modules' IDs and associates a text description with those module ids.
 */
#   define Tr_Module_IDs\
   Tr_Module_ID(APPLICATION_MANAGER_MODULE_ID                       , "Application Manager"                     ) \
   Tr_Module_ID(AUDIO_MODULE_ID                                     , "Audio Task Manager"                      ) \
   Tr_Module_ID(AUMGR_HSM_MODULE_ID                                 , "Audio Mgr HSM"                           ) \
   Tr_Module_ID(BASE_DRIVERS_MODULE_ID                              , "Base Drivers"                            ) \
   Tr_Module_ID(BLUETOOTH_MODULE_ID                                 , "Bluetooth Mgr/Driver"                    ) \
   Tr_Module_ID(BTSTRM_VPD_ENGINE_MODULE_ID                         , "Bluetooth Stream VPD Engine"             ) \
   Tr_Module_ID(BT_AS_MODULE_ID                                     , "Bluetooth AS Proxy"                      ) \
   Tr_Module_ID(BT_AUDIO_MANAGER_ID                                 , "Bluetooth Audio manager"                 ) \
   Tr_Module_ID(BT_CM_MODULE_ID                                     , "BT Connection Mgr"                       ) \
   Tr_Module_ID(BT_LE_MODULE_ID                                     , "BT LE Mgr"                               ) \
   Tr_Module_ID(BT_CM_PROCESS_MODULE_ID                             , "BT Connection Mgr Proces"                ) \
   Tr_Module_ID(BT_DIAG_MODULE_ID                                   , "BT Diag"                                 ) \
   Tr_Module_ID(BT_HFP_MODULE_ID                                    , "Bluetooth HFP Proxy"                     ) \
   Tr_Module_ID(BT_MAP_MODULE_ID                                    , "Bluetooth MAP Module"                    ) \
   Tr_Module_ID(BT_MSG_INTERFACE_MODULE_ID                          , "Bluetooth message interface"             ) \
   Tr_Module_ID(PHONEBOOKDB_INTERFACE_MODULE_ID                     , "Bluetooth Phonebook interface"           ) \
   Tr_Module_ID(BT_PHONEBOOK_SERVER_MODULE_ID                       , "Phone Book Server"                       ) \
   Tr_Module_ID(BT_PHONEBOOK_INTERFACE_ID                           , "Bluetooth Phonebook interface"           ) \
   Tr_Module_ID(BT_PBAP_MODULE_ID                                   , "PBAP Proxy"                              ) \
   Tr_Module_ID(BT_SM_MODULE_ID                                     , "Bluetooth Storage Manager"               ) \
   Tr_Module_ID(BT_SPP_MODULE_ID                                    , "Bluetooth SPP Proxy"                     ) \
   Tr_Module_ID(BT_PAN_MODULE_ID                                    , "Bluetooth PAN Proxy"                     ) \
   Tr_Module_ID(BT_DUN_MODULE_ID                                    , "Bluetooth DUN Proxy"                     ) \
   Tr_Module_ID(BT_UTIL_MODULE_ID                                   , "BT utility"                              ) \
   Tr_Module_ID(BUC_MODULE_ID                                       , "Backup Camaera Mgr"                      ) \
   Tr_Module_ID(CALLOUTS_MODULE_ID                                  , "Callouts Modules"                        ) \
   Tr_Module_ID(CALS_MODULE_ID                                      , "Calibrations Module"                     ) \
   Tr_Module_ID(CONNECTION_MANAGER_MODULE_ID                        , "Connection Manager"                      ) \
   Tr_Module_ID(CPP_UTIL_MODULE_ID                                  , "C++ Utilities"                           ) \
   Tr_Module_ID(DBG_TRACE_MODULE_ID                                 , "Debug Trace Module"                      ) \
   Tr_Module_ID(DEVICE_MANAGER_ID                                   , "Media Detector Module"                   ) \
   Tr_Module_ID(DEVICE_MANAGER_TEST_ID                              , "Test Media Detector Module"              ) \
   Tr_Module_ID(DIMMING_GM_MODULE_ID                                , "LCD Dimming Module"                      ) \
   Tr_Module_ID(EARLY_START_MODULE_ID                               , "Early Startup Module"                    ) \
   Tr_Module_ID(ENGINEERING_MODE_MODULE_ID                          , "Engineering Mode Module"                 ) \
   Tr_Module_ID(SETTING_MODULE_ID                                   , "Setting Module"                          ) \
   Tr_Module_ID(EXTERNAL_LOG_MODULE_ID                              , "External Log Module"                     ) \
   Tr_Module_ID(FACEPLATE_CONTROL_MODULE_ID                         , "Faceplate control"                       ) \
   Tr_Module_ID(FBL_MGR_MODULE_ID                                   , "FBL Mgr"                                 ) \
   Tr_Module_ID(GMLAN_INTERFACE_MODULE_ID                           , "GMLAN Interface"                         ) \
   Tr_Module_ID(HFAP_MODULE_ID                                      , "Handsfree Audio Processing"              ) \
   Tr_Module_ID(HSM_ENGINE_MODULE_ID                                , "State Machine Engine"                    ) \
   Tr_Module_ID(INTERRUPTS_MODULE_ID                                , "Interrupts"                              ) \
   Tr_Module_ID(IO_MODULE_ID                                        , "I/O callouts"                            ) \
   Tr_Module_ID(MANUFACTURING_CALS_MODULE_ID                        , "Manufacturing Cals"                      ) \
   Tr_Module_ID(SM_MODULE_ID                                        , "SM"                                      ) \
   Tr_Module_ID(PERSISTENT_STORAGE_MODULE_ID                        , "Persistent Storage"                      ) \
   Tr_Module_ID(PHONE_CALL_MGR_MODULE_ID                            , "Phone Call Manager"                      ) \
   Tr_Module_ID(PHONEBOOKDB_CONTACT_MODULE_ID                       , "Phonebook DB Contact"                    ) \
   Tr_Module_ID(PHONEBOOKDB_PROXY_MODULE_ID                         , "Phonebook DB Proxy"                      ) \
   Tr_Module_ID(PHONEBOOKDB_SERVER_MODULE_ID                        , "Phonebook DB Server"                     ) \
   Tr_Module_ID(PHONEBOOKDB_DATABASE_MODULE_ID                      , "Phonebook Database"                      ) \
   Tr_Module_ID(PITS_MODULE_ID                                      , "PITS"                                    ) \
   Tr_Module_ID(PROCESS_HANDLER_MODULE_ID                           , "Process Handler"                         ) \
   Tr_Module_ID(PROCMAN_MODULE_ID                                   , "Process Manager"                         ) \
   Tr_Module_ID(SBX_CORE_MODULE_ID                                  , "Main SBX Process"                        ) \
   Tr_Module_ID(SIGDBG_MODULE_ID                                    , "SIGnal DeBuG"                            ) \
   Tr_Module_ID(SOH_MODULE_ID                                       , "State of Health Manager"                 ) \
   Tr_Module_ID(SSND_MODULE_ID                                      , "System Sounds"                           ) \
   Tr_Module_ID(SYSTEM_STATE_SERVER_MODULE_ID                       , "System State Server"                     ) \
   Tr_Module_ID(TEST_MODULE_ID                                      , "TEST"                                    ) \
   Tr_Module_ID(TUNER_PRESET_MGR_MODULE_ID                          , "Tuner preset Manager"                    ) \
   Tr_Module_ID(TUNER_MGR_MODULE_ID                                 , "Tuner Manager"                           ) \
   Tr_Module_ID(UTILITIES_MODULE_ID                                 , "Utilities"                               ) \
   Tr_Module_ID(VIP_DESIP_MODULE_ID                                 , "VIP DESIP Interface"                     ) \
   Tr_Module_ID(VO_MODULE_ID                                        , "Virtual Operator"                        ) \
   Tr_Module_ID(WIFI_MGR_MODULE_ID                                  , "Wifi manager"                            ) \
   Tr_Module_ID(WIFI_PROXY_MODULE_ID                                , "Wifi proxy"                              ) \
   Tr_Module_ID(WIFI_DIAGNOSE_MODULE_ID                             , "Wifi diagnose"                           ) \
   Tr_Module_ID(WIFI_NATIVE_APP_INTERFACE_MODULE_ID                 , "Wifi Native App"                         ) \
   Tr_Module_ID(XSAL_ATTR_MODULE_ID                                 , "XSAL attributes"                         ) \
   Tr_Module_ID(XSAL_BUFFER_MODULE_ID                               , "XSAL buffer"                             ) \
   Tr_Module_ID(XSAL_CONDVAR_MODULE_ID                              , "XSAL Cond Var"                           ) \
   Tr_Module_ID(XSAL_IPC_MODULE_ID                                  , "XSAL IPC"                                ) \
   Tr_Module_ID(XSAL_MSG_MODULE_ID                                  , "XSAL Messaging"                          ) \
   Tr_Module_ID(XSAL_MSG2_MODULE_ID                                 , "XSAL Messaging"                          ) \
   Tr_Module_ID(XSAL_MUTEX_MODULE_ID                                , "XSAL Mutex"                              ) \
   Tr_Module_ID(XSAL_NS_MODULE_ID                                   , "XSAL Name Server"                        ) \
   Tr_Module_ID(XSAL_Q_MODULE_ID                                    , "XSAL Message Queue"                      ) \
   Tr_Module_ID(XSAL_RWLOCK_MODULE_ID                               , "XSAL RW Lock"                            ) \
   Tr_Module_ID(XSAL_SEM_MODULE_ID                                  , "XSAL Semaphore"                          ) \
   Tr_Module_ID(XSAL_SHM_MODULE_ID                                  , "XSAL Shared Memory"                      ) \
   Tr_Module_ID(XSAL_THREAD_MODULE_ID                               , "XSAL Thread"                             ) \
   Tr_Module_ID(XSAL_TIME_MODULE_ID                                 , "XSAL Time"                               ) \
   Tr_Module_ID(XSAL_UTILITIES_MODULE_ID                            , "XSAL Helper Functions"                   ) \
   Tr_Module_ID(XSALCPP_MODULE_ID                                   , "XSAL CPP"                                ) \
   Tr_Module_ID(XSALMT_MODULE_ID                                    , "XSAL Message Thread"                     ) \
   Tr_Module_ID(SOCKET_CLIENT_MODULE_ID                             , "SOCKET CLIENT"                           ) \
   Tr_Module_ID(SOCKET_SERVER_MODULE_ID                             , "SOCKET SERVER"                           ) \
   Tr_Module_ID(SYNC_HELPER_MODULE_ID                               , "Synchronization module"                  ) \
   Tr_Module_ID(POSIX_TIMER_MODULE_ID                               , "POSIX based timer module"                ) \
   Tr_Module_ID(THREADSAFE_Q_MODULE_ID                              , "THREADSAFE Q"                            ) \
   Tr_Module_ID(SPEECH_MGR_MODULE_ID                                , "Speech manager module"                   ) \
   Tr_Module_ID(SPEECH_MGR_PROCESS_MODULE_ID                        , "Speech Process"                          ) \
   Tr_Module_ID(VIDEO_CONTROL_MODULE_ID                             , "Video Control"                           ) \
   Tr_Module_ID(RVS_GUIDELINES_MODULE_ID                            , "Video Control"                           ) \
   Tr_Module_ID(MAPDB_SESSION_MODULE_ID                             , "Map DB Session"                          ) \
   Tr_Module_ID(MAPDB_PROXY_MODULE_ID                               , "MAP DB Proxy"                            ) \
   Tr_Module_ID(MAPDB_SERVER_MODULE_ID                              , "Map DB Server"                           ) \
   Tr_Module_ID(BT_MAP_SESSION_MODULE_ID                            , "Bluetooth MAP Session Module"            ) \
   Tr_Module_ID(REMINDER_MODULE_ID                                  , "Reminder module"                         ) \
   Tr_Module_ID(TOUCH_PROCESS_MODULE_ID                             , "Touch process "                          ) \
   Tr_Module_ID(DRAW_GUIDELINES_MODULE_ID                           , "draw guidelines process"                 ) \
   Tr_Module_ID(BEV_SOCKET_SERVER_MODULE_ID                         , "BEV socket server module  "              ) \
   Tr_Module_ID(APA_SOCKET_SERVER_MODULE_ID                         , "APA socket server module  "              ) \
   Tr_Module_ID(APS_CORE_APP_MODULE_ID                              , "APS_Core Module"                         ) \
   Tr_Module_ID(APS_VR_MODULE_ID                                    , "APS_vr Module"                           ) \
   Tr_Module_ID(APS_NAVI_MODULE_ID                                  , "APS_navi Module"                         ) \
   Tr_Module_ID(APS_TTS_MODULE_ID                                   , "APS_tts Module"                          ) \
   Tr_Module_ID(APS_REMINDER_MODULE_ID                              , "APS_reminder Module"                     ) \
   Tr_Module_ID(APS_BT_LE_GATTC_MODULE_ID                           , "APS_GattC Module"                        ) \
   Tr_Module_ID(RAWINPUT_MANAGER_MODULE_ID                          , "RawInput Module"                         ) \
   Tr_Module_ID(SECURITY_MGR_MODULE_ID                              , "Security Mgr Module"                     ) \
   Tr_Module_ID(FLASH_CERTIFICATE_MGR_MODULE_ID                     , "Certificate Manager Module"              ) \
   Tr_Module_ID(AUDIO_MGR                                           , "Audio Manager"                           ) \
   Tr_Module_ID(CAN_SERVER_MODULE_ID                                , "CAN Server Storage"                      ) \
   Tr_Module_ID(BT_INTERFACE_MODULE_ID                              , "Interface Module"                        ) \
   Tr_Module_ID(SOCKLM_MODULE_ID                                    , "scoklm Module"                           ) \
   Tr_Module_ID(NETWORK_MGR_MODULE_ID                               , "Network Mgr"                             ) \
   Tr_Module_ID(SPIDEV_MODULE_ID                                    , "Library spidev"                          ) \
   Tr_Module_ID(NETWORK_MGR_PROXY_MODULE_ID                         , "Network Mgr proxy"                       ) \
   Tr_Module_ID(ECNR_MGR_MODULE_ID                                  , "ECNR mgr"                                ) \
   Tr_Module_ID(ECNR_DBG_MODULE_ID                                  , "ECNR dbg"                                ) \
   Tr_Module_ID(CAN_APS_SERVER_MODULE_ID                            , "CAN APS SERVER"                          ) \
   Tr_Module_ID(APS_SYSTEM_MODULE_ID                                , "APS SYSTEM SERVER"                       ) \
   Tr_Module_ID(ECD_CORE_ID 													  , "ECD_CORE_ID"					                ) \
   Tr_Module_ID(MIC_MGR_MODULE_ID                                   , "mic mgr"                                 ) \
   Tr_Module_ID(RAWINPUT_SIMULATION_MODULE_ID                       , "RAWINPUT_SIMULATION"                     ) \
   Tr_Module_ID(PKI_MGR_MODULE_ID                                   , "PKI manager"                             ) \
   Tr_Module_ID(TBOX_AUDIO_MGR_MODULE_ID                            , "TBOX_AUDIO_MGR"                          ) \
   Tr_Module_ID(TBOX_SERVICE_MGR_MODULE_ID                          , "TBOX_SERVICE_MGR"                        ) \
   Tr_Module_ID(CARLIFE_MODULE_ID                                   , "Carlife Manager"                         ) \
   Tr_Module_ID(AM_FM_DRV_MODULE_ID                                 , "AM/FM Driver"                            ) \
   Tr_Module_ID(AM_FM_MNGR_MODULE_ID                                , "AM/FM Tuner Manager"	                   ) \
   Tr_Module_ID(AM_FM_MNGR_TR_INF_MODULE_ID                         , "AM/FM Mngr Info Traces"                 ) \
   Tr_Module_ID(AM_FM_MNGR_TR_EVT_MODULE_ID                         , "AM/FM Mngr Event Traces"                ) \
   Tr_Module_ID(AM_FM_MNGR_TR_REP_MODULE_ID                         , "AM/FM Mngr Report Traces"               ) \
   Tr_Module_ID(AM_FM_TEST_MODULE_ID                                , "AM/FM Test" 			                   ) \
   Tr_Module_ID(AM_FM_REPORTS_MODULE_ID 	                        , "AM/FM Reports Test" 	                   ) \
   Tr_Module_ID(AM_FM_EMI_MODULE_ID 		                        , "AM/FM EMI"				               ) \
   Tr_Module_ID(AM_FM_QUAL_MODULE_ID		                        , "AM/FM QUAL" 			                   ) \
   Tr_Module_ID(AM_FM_AMLIST_MODULE_ID		                        , "AM/FM AMLIST"			               ) \
   Tr_Module_ID(AM_FM_SEEK_MODULE_ID		                        , "AM/FM SEEK" 			                   ) \
   Tr_Module_ID(AM_FM_AFLIST_MODULE_ID		                        , "AM/FM AFLIST"			               ) \
   Tr_Module_ID(AM_FM_BACKGROUND_MODULE_ID	                        , "AM/FM BACKGROUND"		               ) \
   Tr_Module_ID(AM_FM_BGND_AM_MODULE_ID 	                        , "AM/FM BGND AM-BAND" 	                   ) \
   Tr_Module_ID(AM_FM_BGND_FM_MODULE_ID 	                        , "AM/FM BGND FM-BAND" 	                   ) \
   Tr_Module_ID(AM_FM_BGND_NETWORK_MODULE_ID                        , "AM/FM BGND NETWORKS"	                   ) \
   Tr_Module_ID(AM_FM_BGND_TRAFFIC_MODULE_ID                        , "AM/FM BGND TRAFFIC" 	                   ) \
   Tr_Module_ID(AM_FM_BGND_AF_MODULE_ID 	                        , "AM/FM BGND AF LIST" 	                   ) \
   Tr_Module_ID(AM_FM_BGND_PD_MODULE_ID 	                        , "AM/FM BGND PHASEDIV"	                   ) \
   Tr_Module_ID(AM_FM_FGND_MODULE_ID		                        , "AM/FM FGND" 			                   ) \
   Tr_Module_ID(AM_FM_PL_MODULE_ID			                        , "AM/FM PL"				               ) \
   Tr_Module_ID(AM_FM_SCROLLPSN_MODULE_ID	                        , "AM/FM SCROLLING PS" 	                   ) \
   Tr_Module_ID(AM_FM_SPECTRUM_MODULE_ID	                        , "AM/FM SPECTRUM" 		                   ) \
   Tr_Module_ID(RDS_DECODER_MODULE_ID		                        , "RDS DECODER"			                   ) \
   Tr_Module_ID(RDS_DECODER_RT_MODULE_ID	                        , "RDS DECODER RT" 		                   ) \
   Tr_Module_ID(RDS_DECODERSYNC_MODULE_ID	                        , "RDS DECODER SYNC"		               ) \
   Tr_Module_ID(AM_FM_PARAM_MODULE_ID		                        , "AM/FM PARAMETER"		                   ) \
   Tr_Module_ID(AM_TUNER_SERVER_MODULE_ID	                        , "AM Tuner Server"		                   ) \
   Tr_Module_ID(FM_TUNER_SERVER_MODULE_ID	                        , "FM Tuner Server"		                   ) \
   Tr_Module_ID(HISIP_AP_DEVICE_CORE_ID		                        , "hisip ap node"				           ) \
   Tr_Module_ID(HISIP_M4_DEVICE_CORE_ID		                        , "hisip m4 node"				           ) \
   Tr_Module_ID(CLUSTER_SOCKER_CLIENT_ID	                        , "cluster socket client"		           ) \
   Tr_Module_ID(DSPLOGGER_MODULE_ID	                                , "dsp logger"		                       ) \
   Tr_Module_ID(USERTIME_MGR_MODULE_ID                              , "user time manager"		               ) \
   Tr_Module_ID(DBA_SERVER_MODULE_ID                                , "DBA Server"		                       ) \

   /* end of X-macro (dont remove this line) */

/*===========================================================================*
 * Exported Type Declarations
 *===========================================================================*/

/**
 * Project specific list of modules ID used by Debug / Trace module for asserts
 * and tracing.
 */
typedef enum Tr_Module_ID_Tag
{
   TR_MODULE_UNKNOWN, /* 0 = "unknown" module       */
   Tr_Module_IDs      /* Declare list of module ids */
   TR_NUM_MODULE_IDS
}
Tr_Module_ID_T;


#   ifdef __cplusplus
}                               /* extern "C" */
#   endif                       /* __cplusplus */
/*===========================================================================*/
/*!
 * @file dbg_trace_acfg.h
 *
 * @section RH REVISION HISTORY (top to bottom: last revision to first revision)
 *
 * 23-Oct-2017 dzphcr
 *  + Task ctc_ec#198740 [ICI2.0][BT]: Added module id, PHONEBOOKDB_DATABASE_MODULE_ID.
 *
 * 28-Sept-2017 dzphcr    
 * Task ctc_ec#197114: Added module id, BT_UTIL_MODULE_ID
 *
 * 24-Feb-2017 Wangshihua
 *   - Added pki mgr module id
 *
 * 21-Feb-2017 Gouri Naik
 *   - Added Mic wrapper
 *
 * 5-Dec-2016 Jinlong Wang
 *   - remove ununsed debug module name from cfg file and acfg file.
 *
 * 20-Nov-2016 Luis Solis Rev 20
 *   - Task ctc_ec#169319: [NGI2][Media] Inegrate console_gracenote tests
 *
 * 18-Nov-2016 Luis Solis Rev 20
 *   - Task ctc_ec#169319: [NGI2][Media] Gracenote: Integrate content recognition bbc
 *
 * 28-Sep-2016  pjr6cf  Rev 19  
 * ctc_ec#task163427[NGI2][Bluetooth]: BT Message API Interface changes
 *
 * 13-Sep-2016 Luis Solis
 * + task ctc_ec#162455: [NGI2][Media] Update console_device_manager test
 *
 * 5-Sep Yuan Kanglin
 * + ctc_ec#161927:[NGI2][Network_Mgr] integrate network manager
 *
 * 29Aug2016  Devaraj Herle (rz35sz)
 * ctc_ec#161433: Integrating PITS Baseline to project
 *
 * 17-Aug-2016 Punith Gangadhara
 * + ctc_ec#160595 Added APS_GattC block
 *
 * 12-July-2016 Gouri Naik
 * + ctc_ec#157494 Added Audio_Mgr block.
 *
 * 23-Dec-2014 wangshuquan
 * + ctc_ec#94471 commit digital aux code
 *
 * 12-Nov-2014 Lu Yinyin
 * -Add CARPLAY_SERVICE_MODULE_ID and CARPLAY_APP_MODULE_ID
 *
 * 03-Jun-2014 Milan Tian
 * -Add VR NAVI NAF diagnose module(VR_NAVI_NATIVE_INTERFACE_MODULE_ID)
 *
 * 25-Feb-2014 wang min remove old HMI from project
 * + bbc_sgmnglv\support\NAF\bbc_onstar_native_interface\bb_gmlan_gateway_native_interface\bb_gmlan_gateway_nai_imp\_src\GMLANGateway_Client.cpp
 * + bbc_sgmnglv\processes\system_persistence\nglv_board_options_ps.cpp
 *
 * -8-Jan-2014 Bao Qifan 58
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
 * -12-Dec-2013 Gene Hu 55
 * -Add TSC_MODULE_ID
 *
 * -5-Dec-2013 Alex Lu 49
 * -Task: 53752 - fix the compiling warning 
 *
 * -18-Nov-2013 HuiBin Li 48
 *  -Add XENA_GATEWAY_MODULE_ID
 *
 * -15-Nov-2013 Alex Lu Rev 47 
 * -Task: 51680 - add nav most server module
 *
 * - 14-Nov-2013 Ethan Liu An Rev 46
 *   -Add NAF Onstar module
 *
 * - 14-Aug-2013 Paul Xia An Rev 45
 *   -Add Map session and Map db module
 *
 * - 13-Aug-2013 Wang Shihua An Rev 44
 *   -Add Wifi diagnose module
 *
 * - 31-Jul-2013 Angelo An Rev 43
 *   -Add MirrorLink Mgr module
 *
  * - 23-Jul-2013 wang bing Rev 42
 *   -Add naf calbration module
 *
 * - 15-Jul-2013 HuiBin Li Rev 41
 *   -Add reminder module
 *
 * - 05-Jul-2013 Ray Zhang Rev 40
 *   -Add connection manager module
 *
 * - 26-June-2013 Angelo An Rev 39
 *   -Add MIRRORLINK module
 * 
 * - 13-Jun-2013 Ray Zhang Rev 38
 *   -Add PAN DUN client module
 * 
 * - 11-Jun-2013 Ray Zhang Rev 36
 *   -Add PAN DUN module
 *
 * -30-May-2013 Alex Lu Rev 35
* -Task: 39806 - add NAV_DR_MODULE_ID
 * 
 * - 30-Apr-2013 Ray Zhang Rev 34
 *   -Add SPP module.
 *
 * - 22-Apr-2013 Wang Le Rev 32
 *   -Add key manager client module.
 * 
 * - 19-Apr-2013 Paul Xia Rev 32
 *   -Add bt_storage_mgr and phonebook_db.
 *
 * - 18-Apr-2013 Arthur C Rev 31
 *   -Add Naf Loader.
 *
 * - 25-Mar-2013 shao fei Rev 30
 *   -Add tts most server modules.
 *
 * - 1-Mar-2013 Ginger Jiang Rev 29
 *   -Add avmodule source handler modules.
 *
 * - 28-FEB-2013 wangbing Rev 28
 *   -Add HMI RearCamera module
 *
 * - 25-FEB-2013 Zhang Hang Rev 27
 *   -Add layer manager module.
 *
 * - 21-FEB-2013 Arthur Chen Rev 26
 *   -Add vehicle information module.
 *
 * - 4-FEB-2013 ShaofeiRev 25
 *   -Add vr hmi module
 *
 * - 31-Jan-2013 Judy Zhu Rev 24
 *   -Add most_app register module
 *
 * - 30-Jan-2013 Li Hui Rev 23
 *   -Add video control 
 *
 * - 21-Jan-2013 shaofei Rev 22
 *   -[vr]add vr module  
 *
 * - 08-Jan-2013 Bao Qifan Rev 19 ctc_ec#33077
 *   -[NGK PITS]add sinad module  
 *
 * - 25-dec-2012 li huibin Rev 18
 *   -add touchscreen module  
 *
 * -  24-Dec-2012 Alex Lu Rev 17
 *  - Add NAV_GPS_MODULE_ID
 * 
 * - 19-Dec-2012 Danny Kong Rev 16
 *   - Add DIAG_CLIENTS_HANDLER_MODULE_ID 
 *
 * - 15-nov-2012 Ethan Liu Rev 15
 *   - Add FACEPLATE CONTROL module
 *
 * - 13-Nov-2012 Wang Shihua Rev 14
 *   - Add wifi module 
 *
 * - 07-Nov-2012 Wang Le Rev 13
 *   - Modify the file histroy rev 
 *
 * - 06-nov-2012 Ethan Liu Rev 12
 *   - Add GMLAN CUSTOMIZATION module
 *
 * - 06-Nov-2012 Wang Le Rev 11
 *   - Task 31527: Add engineering mode and setting module id
 *	
 * - 23-oct-2012 Zhang Hang Rev 10
 *   - Add NAF interface module 
 *
 * - 28-JUN-2012 David A. Johnson Rev 142
 *   - Task 106034: Integrate and enable iType fonts
 *
 * - 22-jun-2012 Sowmya K  Rev 140
 *   Task kok_basa#104517: Integrating DevelopmentScreenClient Client
 *
 * - 07-jun-2012 Kevin W. Kaster  Rev 139
 *   Task kok_basa#101458: Bring HFAP to tip
 *
 * - 11-Jun-2012 Coppock, Jonathan (dzhk56) Rev 138
 *   - Task kok_basa#102294: "TMC: Integrate bbc_tmc_tuner release 20120611 into the aa1024ae SBX project"
 *     + Initial implementation of the Si4749 quality functionality.
 *     + Since the TMC code was redesigned, re-implement the publishing of PI for the tuner status event.
 *
 * - 07-Jun-2012 Larry Piekarski Rev 137
 *   - Task 102028: Enabled warnings for string formats.
 *
 * - 26-May-2012 Phil Cotton Rev 136
 *   Task 98500: Integrate Timeshift Play/Stop/Pause Functionality info AE
 *
 * - 18-May-2012 Phil Cotton Rev 135
 *   - Task 97715: Integrate Timeshift Building Block Into AE
 *
 * - 18-May-2012 David Mooar Rev 134
 *   - Task 97628: Onstar audio redesign.
 *
 *  -16-May-2012 Goran Davidsson  Rev 131.1.1/133
 *   - Task 94710:Added trace module ID for BT_CM_Module
 *
 * - 11-May-2012 Petter Gustafsson Rev 132
 *   - Task 94169: Added PBAP
 *
 * - 17-Apr-2012 Neeraj Ramesh Rev 131
 *   - Task 90720: Added system callouts for tuner_server_helper
 *
 *  -17-April-2012 Sowmya K  Rev 130
 *   -Task kok_basa#89963:Added OnstarPersonalCalling Client
 *
 * - 16-April-2012 Jeevan SP Rev 129
 *   -Task 90268: Added Backup camera client
 *
 *  -12-April-2012 Kavya Narayan  Rev 128
 *   -Task kok_basa#89645:Added trace module ID for Audio block HSM modules
 *
 *   -07-April-2012 Raja  Rev 127
 *   -Task 88843:Added Onstar TBT Navigation Client
 *
 * - 03-April-2012 Sowmya K Rev 126
 *   -Task 87781: Added CustomizationIPC client
 *
 * - 03-April-2012 Gouri Naik Rev 125
 *   -Task 86997: Added AUDIO_MUTE_MODULE_ID
 *
 * - 03-April-2012 Natesh.K.N Rev 124
 *   -Task 86972: Add USB Reprogramming Support from HMI
 *
 * 23-Mar-2012 Oscar Vega Rev 123
 * - Task 841262: Implement MID 20/21/22/23.
 *
 * - 21-Mar-2012 Coppock, Jonathan (dzhk56) Rev 122
 *   - Task kok_basa#84400: "TMC: Integrate bbc_tmc_tuner release 20120321 into the aa1024ae SBX project"
 *     + Implement a fake AMFM local station list and fake AMFM station list publishing to the TMC module
 *       to simulate the AMFM LDICE station list functionality.
 *     + Implement tune PI functionality.
 *     + Remove thread alive checks from the TMC proxy, as they aren't valid across processes.
 *     + Remove TMC initialization failure assert, and replace it with a Tr_Fault for initialization
 *       failure and a Tr_Notify for initialization success.
 *     + Add Detroit TMC stations to the fake AMFM station list publication.
 *
 * - 13-Mar-2012 Madhurima L Rev 121
 *   - Task 82485: Added alert manager client
 *
 * - 13-Mar-2012 Sowmya K Rev 120
 *   - Task 82137: Added customization SBZA client
 *
 * - 03-Mar-2012 Sowmya K Rev 119
 *   - Task 80084: Added customization PA client
 *
 * - 02-Mar-2012 Doug Kuhlman
 *   Added new am/fm trace modules.
 *
 * - 29-Feb-2012 Larry Piekarski Rev 117
 *   - Task 79582: Remove ICR bb_theft_lock block
 *
 * - 27-FEB-2012 David A. Johnson  Rev 116
 *   Task kok_basa#79170 : Add warnings to SysSounds stubs to show ringtones
 *
 * - 27-Feb-2012 Kavya Narayan Rev 115
 *   - Task 79100: removed gm_pwm_amp related dependencies.
 *
 * - 24-Feb-2012 Coppock, Jonathan (dzhk56) Rev 114
 *   - Task kok_basa#78217: "TMC: Integrate the following - bb_fm_tuner_server 20120222,
 *                                                          bb_pits_services 20120223,
 *                                                          bb_tuner_server_helper 20120221,
 *                                                          bbc_tmc_tuner 20120223_1"
 *     + Integrate TMC/MOST/PITS changes together that use the new TMC BBC and API.
 *
 * - 21-Feb-2012 Kamalakanta Barik Rev 112
 *   - Task 77786: Integrated Phonebook Manager and Phonebook Server. 
 *
 * - 20-Feb-2012 Petter Gustafsson Rev 111
 *   - Task 77357: Integrated Bluetooth Streaming VPD. 
 * 
 * - 16-Feb-2012 Keerthika Pandiselvan Rev 110
 *   - Task 76482: Integrate OnstarTBTNavigation Server.
 *
 * - 13-Feb-2012 Larry Piekarski Rev 109
 *   - Task 75660: Removed the Video Control block.
 *
 * - 06-Feb-2012 Coppock, Jonathan (dzhk56) Rev 108
 *   - Task kok_basa#74552: "TMC: Integrate bbc_tmc_tuner release 20120206 into the aa1024ae SBX project"
 *     + Receive and validate RDS groups with the Si4749 TMC tuner.
 *
 * - 02-Feb-2012 Manuel Robledo Rev 107
 *   - Task 73725: Integrate customization_object_computation_settings_server and onstar_personal_calling into AE
 *
 * - 27-Jan-2012 Larry Piekarski Rev 106
 *   - Task 72447: Temporarily turn off format warnings.
 *
 * - 25-Jan-2012 Coppock, Jonathan (dzhk56) Rev 105
 *   - Task kok_basa#71622: "TMC: Integrate bbc_tmc_tuner release 20120125 into the aa1024ae SBX project"
 *     + Define the callout that publishes the external LDICE RDS TMC groups to the external TMC decoder.
 *     + Implement a new thread dedicated to decoding TMC from external sources.
 *     + Implement the decoder for the new external TMC decoding thread.
 *     + Publish the decoded external TMC data in the external TMC decoder to the TMC Manager.
 *     + Implement publishing of the external TMC data by the TMC Manager to the system.
 *     + Modify TMC station info and TMC data structures to include and use tuner index types.
 *
 * - 20-Jan-2012 Mark Elkins Rev 104
 *   - Task 70885: AV Manager Server has duplicated debug trace ID's -- Integrate into AA1024AE project
 *
 * -20-Jan-2012 Rashmi Alok Rev 103
 *   -Task 70815: added persistence for hmi - valet 
 *
 * - 18-Jan-2012 Diptiman Roy  Rev 102
 *   -Task 70201: Integrated Customization Memory Settings Client
 *
 * - 17-Jan-2012 Diptiman Roy  Rev 101
 *   -Task 69961: Re-integrated Updated Customization Doors Locks Client
 *
 * -17-Jan-2012 Natesh.K.N Rev 100
 *   -Task 69933: Integrate Golden ics client
 *
 * - 09-Jan-2012 Diptiman Roy Rev 99
 *   - Task 68165: Integrated Customization DoorsLocks Client
 *
 * -06-Jan-2012 Shaoli Dai Rev 98
 *   -Task 67703: Integrate Favorites Manager Server
 *
 * -06-Jan-2012 P Anith Raj Rev 97
 *   -Task 67773: Integrate Golden CustomizationECC Client
 *
 * - 03-Jan-2012 Larry Piekarski Rev 96
 *   - Task 67051: Moved Internal/MOST amp Cal PS function to system_persistence.
 *
 * -02-Jan-2012 Natesh.K.N Rev 95
 *   -Task 66849: Integrate Golden AVManagerClient
 *
 * -30-Dec-2011 Natesh.K.N Rev 94
 *   -Task 66645: Integrate Golden AuxiliaryInputJackClient
 *
 * -26-Dec-2011 Anith Raj Rev 93
 *  - Task 66151: Integrate Customization BCM client
 *
 * - 26-Dec-2011 Jeevan sp Rev 92
 *   - Task 66142: Integrated golden dab fm tuner client
 *
 * - 23-Dec-2011 Larry Piekarski Rev 91
 *   - Task 66049: Consolidate XSAL attr callouts into a common system wide 
 *     file.
 *
 * -23-Dec-2011 Manuel Robledo Rev 90
 *   - Task 66043: Integrate customization_doors_locks_server and customization_pa_server into AE
 *
 * - 23-Dec-2011 Jeevan sp Rev 89
 *   - Task 65967: Integrated golden audio disk player 
 *
 * - 21-Dec-2011 Keerthika Pandiselvan Rev 88
 *   - Task 65395: Integrated mdf_customization_ipc_server and mdf_customization_sbza_server
 *
 * - 20-Dec-2011 Larry Piekarski Rev 87
 *   - Task 65375: Integrate bb_block_list
 *
 * - 20-Dec-2011 Wanda Jimenez   Rev 86
 *   Task 64837: Integrate MTP VPD in SBX project.
 *
 * 19-Dec-2011 Rashmi Alok Rev 84
 *  - Task 65029:Rename OnstarDataSettings Client as per Golden client
 *
 * - 14-Dec-2011 Rashmi Alok Rev 83
 *   - Task 64229:Integrate Amplifier Client
 *
 * - 13-DEC-2011 David A. Johnson  Rev 82
 *   Task kok_basa#64067: Add bb_gmsbx14_phonebook_client to process_hmi_radio
 *   - Added debug module ID for Phonebook Client.
 *
 * -12-Dec-2011 Anith Raj Rev 81
 *  - Task 63666:Integrate TelephoneClient
 *
 * -10-Dec-2011 Anith Raj Rev 80
 *  - Task 63556:Integrate BluetoothSettings Client
 *
 *-09-Dec-2011 Rashmi Alok Rev 79
 * - Task 63296:Integrate OnstarDataSettings Client
 *
 * -08-Dec-2011 Manuel Robledo Rev 78
 *   - Task 62683: Integrate customization_ecc_server into AE
 *
 * - 08-Dec-2011 Natesh.K.N Rev 77
 *  - Task 62961:Integrate Golden AM tuner Client
 *
 * - 07-Dec-2011 Zhang Hang Rev 76
 *   - Task 62752: Integrate LVM Interface server & engine.
 *
 * - 07-Dec-2011 Keerthika Pandiselvan Rev 75
 *   - Task 62124: Integration of mdf_customization_bcm_server
 *
 * -05-Dec-2011 Natesh.K.N Rev 74
 *   - Task 62261:Integrate Golden Fm tuner Client
 *
 * - 28-Nov-2011 Coppock, Jonathan (dzhk56) Rev 73
 *   - SCR kok_basa#17325: "TMC: Refactor the TMC Decoder from 200C to XSAL conventions"
 *   - Task kok_basa#61204: "TMC: Integrate bbc_tmc_tuner release 20111123 into the aa1024ae SBX project"
 *     + Modified threads to be shutdown with events.
 *     + Moved queue size definitions to project-level callouts.
 *     + Moved message size definitions out of config files back into block files.
 *     + Cleaned up callouts, config files, and templates.
 *     + Replaced deprecated EM trace references with current PBC trace references.
 *     + Cleaned up the TMC Decoder task.
 *     + Converted remaining proxy functions from 200C to XSAL conventions.
 *     + Converted 200C tick timers to XSAL millisecond timers.
 *
 * - 23-Nov-2011 Larry Piekarski Rev 72
 *   - Task 59007: Created an Early Start process and moved some of the
 *     functionality from SBX Core into that process to improve startup time.
 *
 * - 23-Nov-2011 Dariusz Dabrowski 71
 *   - Task 60590: Integration of most_app module
 *
 * - 21-Nov-2011 Sowmya K Rev 70
 *   - Task 60199: Integration of OnstarDataSettings module
 *
 * - 14-Nov-2011 Larry Piekarski Rev 69
 *   - Task 58560: Updated to latest debug trace with Notify level.
 *
 * - 04-Nov-2011 Larry Piekarski Rev 68
 *   - Task 56992: Added App Man to Most Servers
 *
 * - 31-Oct-2011 Larry Piekarski Rev 66
 *   - Task 56428: Integrate new AV Manager Server which enables internal audio.
 *
 * -28-Oct-2011 Rashmi Alok Rev 65
 *  Task 56125: Integrate Golden System State Client
 *
 * - 26-Oct-2011 Wanda Jimenez   Rev 64
 *   Task 53225: Include IPOD VDP in the SBX projec.
 *
 *  -25-Oct-2011 Natesh.K.N  Rev 62
 *   - Task 55489:Integrated OnStarAudioClient
 *
 * - 17-Oct-2011 Larry Piekarski Rev 61
 *   - Task 53880: Integrated Goldenized AVManager Server
 *
 * - 14-Oct-2011 Chris Baker
 *   Task kok_basa#53413 Revision 60
 *   - Added phone call manager module.
 *
 * - 13-Oct-2011 Mario Castro  Rev 59
 *   Task kok_basa#53220: Integrate Flash Manager cluster in order to detect
 *   reprogramming files in the USB.
 *
 * - 13-Oct-2011 Chris Baker
 *   Task kok_basa#53194 Revision 58
 *   - Added HF Phone modules.
 *
 * - 11-Oct-2011 Chris Baker
 *   Task kok_basa#53176 Revision 57
 *   - Added BT CM process module ID.
 *
 * - 12-Oct-2011 Sowmya K Rev 56
 *    Task 53031: Integrated OnstarAudio Server
 *
 * - 11-OCT-2011 David A. Johnson  Rev 55
 *   Task kok_basa#52927: Integrate MediaPlayerClient into hmi_radio_process
 *   - Added debug module ID for MediaPlayerClient.
 *
 * -10-Oct-2011 Darinka Lopez  Rev 54
 * - SCR kok_basa#14298: Integrate PITs handler
 *
 * - 05-Oct-2011 Coppock, Jonathan (dzhk56) Rev 53
 *   - SCR kok_basa#15950: "TMC: Integrate the TMC module into the SBX project"
 *   - Task kok_basa#52295: "TMC: Integrate the TMC module into the SBX project"
 *     + Initial integration of the TMC BBC into the SBX project.
 *
 *  -05-Oct-2011 Natesh.K.N  Rev 52
 *   - Task kok_basa 52209:Integrate HVAC Settings Client
 *
 * -01-Oct-2011 Natesh.K.N  Rev 51
 * - Task kok_basa 51803: Integrate Favourites Client
 *
 * -30-Sept-2011 Manuel Robledo  Rev 49.1.1
 * - Task kok_basa 51092: Integrate HVAC Settings Server
 *
 * -26-Sept-2011 Shaoli Dai  Rev 48
 * - Task kok_basa 49157: Integrate Favorite Manager Server
 *
 * - 14-Sep-2011 Jaime Almeida  Rev 47
 *   - SCR kok_basa#14536/Task kok_basa#48065: Integrate MSD VPD in SBX.
 *     - Add MSM_MODULE_ID, MSD_VPD_MODULE_ID and MUSIC_BROWSER_MODULE_ID.
 *
 * -07-Sept-2011 Arturo lopez  Rev 46
 * - Task kok_basa 47860: Integrate player into Silverbox project.
 *
 * - 31-Aug-2011 Larry Piekarski  Rev 45
 *   - Task 46952: Remove unneeded RSA module.
 *
 * - 24-Aug-2011 Larry Piekarski  Rev 44
 *   - Task 46014: Updated to the golden GMLAN Gateway Client
 *
 * - 23-Aug-2011 Larry Piekarski  Rev 43
 *   - Task 45690: Updated to tip on GMLAN Gateway Server, which updated the names
 *     to destinguish between the Server and the Client.
 *
 * 18-Aug-2011 Oscar Vega  Rev 42
 * Task kok_basa#44847: Integrate calibrations into main application.
 *
 *   16-Aug-2011 Chris Lipchik  Rev 41
 *   SCR kok_basa#13587/Task kok_basa#43603
 *   Integrate latest Tuner BBs including DAB.
 *
 * - 15-AUG-2011 David A. Johnson  Rev 40
 *   Task kok_basa#44322: Add bb_gmsbx14_DABFMTunerClient to process_hmi_radio
 *   - Added debug module ID for DABFMTunerClient.
 *
 * - 11-Aug-2011 Kevin W. Kaster  Rev 39
 *   Task kok_basa#44074: Integrate alsa-lib and PCM_Stream
 *   - Added PCM_STREAM_MODULE_ID entry.
 *
 * - 12-AUG-2011 David A. Johnson  Rev 38
 *   Task kok_basa#44170: Add bb_gmsbx14_GMLANGatewayClient to process_hmi_radio
 *   - Added debug module ID for GMLANGatewayClient.
 *
 * 9-Aug-2011 David Mooar  Rev 37
 * SCR kok_basa#10539: Implement Language Selection in GMLAN Gateway Server.
 *
 *   07-Aug-2011 Lipchik_Chris Rev 34
 *   SCR kok_basa#13141/Task kok_basa#43120
 *   Integrated new bbc_amfm_tuner_g BB to eliminate unnecessary Trace info.
 *
 * - 05-AUG-2011 Manuel Robledo  Rev 33
 *   Task kok_basa#43082: Integrate AuxiliaryInputJackServer
 *   - Added debug module ID for AuxiliaryInputJacServer.
 *
 * - 04-AUG-2011 David A. Johnson  Rev 33
 *   Task kok_basa#42894: Add AuxiliaryInputJackClient to process_hmi_radio
 *   - Added debug module ID for AuxiliaryInputJackClient.
 *
 * - 02-AUG-2011 David A. Johnson  Rev 32
 *   Task kok_basa#42403: Add bb_gmsbx14_BluetoothSettingsClient to process_hmi_radio
 *   - Added debug module ID for BluetoothSettingsClient.
 *
 * - 29-JUL-2011 David A. Johnson  Rev 31
 *   Task kok_basa#42023: Add bb_gmsbx14_AudioDiskPlayer to process_hmi_radio
 *   - Added debug module ID AudioDiskPlayerClient.
 *
 * - 28-Jul-2011 Chris Baker  Rev 30
 *   Task kok_basa#41916: Update BT XSAL proxy to match ICR
 *   - Added debug module IDs for AS and HFP proxies.
 *
 * - 26-JUL-2011 Gouri Naik  Rev 29
 *   Task kok_basa#41662: Pull Chimes Facade
 *   - Added CHIMES_MODULE_ID
 *
 * - 20-JUL-2011 David A. Johnson  Rev 28
 *   Task kok_basa#40737: Add bb_gmsbx14_FavoritesManagerClient to process_hmi_radio
 *   - Added HMI_FAVMANAGERCLIENT_MODULE_ID
 *
 * - 19-Jul-2011 Jaime Almeida  Rev 27
 *   SCR kok_basa#12244/Task kok_basa#40026: Integrate AllGo DeviceManager and Gateway.
 *   - Add ALLGO_GATEWAY_MODULE_ID.
 *
 * - 13-Jul-2011 Chris Baker  Rev 26
 *   Task 40067: Integrate Bluetooth Stack and Fb Server
 *   - Add BLUETOOTH_SETTINGS_SERVER_MODULE_ID.
 *   - Re-Add BLUETOOTH_MODULE_ID.
 *
 * - 12-Jul-2011 Larry Piekarski  Rev 25
 *   - Task 39436: Updated to tip of Debug Trace
 *
 * - 08-Ju1-2011 Juan Carlos Castillo  Rev 24
 *   - SCR kok_basa#10713 Integrate bb_gm_diag_handler to aa1024ae project
 *
 * - 08-Jul-2011 Larry Piekarski  Rev 23
 *   - Task 39229: Removed Eli
 *
 * - 08-Jul-2011 Larry Piekarski  Rev 22
 *   - Task 39197: BASAize Most Servers
 *
 * - 05-Ju1-2011 Wanda Jimenez  Rev 21
 *   - Task 38587: Integrate bb_MediaPlayerServer
 *
 * - 29-Jun-2011 Larry Piekarski  Rev 20
 *   - Task 37984: Added trace message with firmware version info. Removed unused
 *                 ID's.
 *
 * 8-June-2011 Gouri Naik  Rev 17
 * SCR kok_basa#9728: Integrate bb_AmplifierServer.
 *
 * 14-May-2011 David Mooar  Rev 12
 * SCR kok_basa#9488: Integrate bb_AVManagerServer.
 *
 * 04-May-2011 Natesh.K.N  Rev 11
 * SCR kok_basa#8497: Add HMI Module ID
 *
 * 28-April-2011 David Mooar  Rev 9
 * SCR kok_basa#8888: Integrate audio blocks.
 *
 * 25-April-2011 David Mooar  Rev 8
 * SCR kok_basa#8516: Integrate dsp_774x building blocks, and hd radio.
 *
 * 29-March-2011 David Mooar  Rev 6
 * SCR kok_basa#7448: Integrate BTCS.
 *
 */
/*===========================================================================*/
/** @} doxygen end group */
#endif                          /* DBG_TRACE_ACFG_H */
