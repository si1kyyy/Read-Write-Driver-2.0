#pragma once
#include <ntifs.h>
#include "errorCode.h"
#include <ntimage.h>
#include <intrin.h>
#include "symtool.h"

typedef struct _RTL_PROCESS_MODULE_INFORMATION {
	HANDLE Section;                 // Not filled in
	PVOID MappedBase;
	PVOID ImageBase;
	ULONG ImageSize;
	ULONG Flags;
	USHORT LoadOrderIndex;
	USHORT InitOrderIndex;
	USHORT LoadCount;
	USHORT OffsetToFileName;
	UCHAR  FullPathName[256];
} RTL_PROCESS_MODULE_INFORMATION, * PRTL_PROCESS_MODULE_INFORMATION;

typedef struct _RTL_PROCESS_MODULES {
	ULONG NumberOfModules;
	RTL_PROCESS_MODULE_INFORMATION Modules[1];
} RTL_PROCESS_MODULES, * PRTL_PROCESS_MODULES;

typedef struct _MY_ATTACH_OBJ {
	ULONG64 cr0;
	ULONG64 cr3;
	ULONG64 cr4;
} MY_ATTACH_OBJ, * PMY_ATTACH_OBJ;

typedef enum _SYSTEM_INFORMATION_CLASS {
	SystemBasicInformation,
	SystemProcessorInformation,             // obsolete...delete
	SystemPerformanceInformation,
	SystemTimeOfDayInformation,
	SystemPathInformation,
	SystemProcessInformation,
	SystemCallCountInformation,
	SystemDeviceInformation,
	SystemProcessorPerformanceInformation,
	SystemFlagsInformation,
	SystemCallTimeInformation,
	SystemModuleInformation,
	SystemLocksInformation,
	SystemStackTraceInformation,
	SystemPagedPoolInformation,
	SystemNonPagedPoolInformation,
	SystemHandleInformation,
	SystemObjectInformation,
	SystemPageFileInformation,
	SystemVdmInstemulInformation,
	SystemVdmBopInformation,
	SystemFileCacheInformation,
	SystemPoolTagInformation,
	SystemInterruptInformation,
	SystemDpcBehaviorInformation,
	SystemFullMemoryInformation,
	SystemLoadGdiDriverInformation,
	SystemUnloadGdiDriverInformation,
	SystemTimeAdjustmentInformation,
	SystemSummaryMemoryInformation,
	SystemMirrorMemoryInformation,
	SystemPerformanceTraceInformation,
	SystemObsolete0,
	SystemExceptionInformation,
	SystemCrashDumpStateInformation,
	SystemKernelDebuggerInformation,
	SystemContextSwitchInformation,
	SystemRegistryQuotaInformation,
	SystemExtendServiceTableInformation,
	SystemPrioritySeperation,
	SystemVerifierAddDriverInformation,
	SystemVerifierRemoveDriverInformation,
	SystemProcessorIdleInformation,
	SystemLegacyDriverInformation,
	SystemCurrentTimeZoneInformation,
	SystemLookasideInformation,
	SystemTimeSlipNotification,
	SystemSessionCreate,
	SystemSessionDetach,
	SystemSessionInformation,
	SystemRangeStartInformation,
	SystemVerifierInformation,
	SystemVerifierThunkExtend,
	SystemSessionProcessInformation,
	SystemLoadGdiDriverInSystemSpace,
	SystemNumaProcessorMap,
	SystemPrefetcherInformation,
	SystemExtendedProcessInformation,
	SystemRecommendedSharedDataAlignment,
	SystemComPlusPackage,
	SystemNumaAvailableMemory,
	SystemProcessorPowerInformation,
	SystemEmulationBasicInformation,
	SystemEmulationProcessorInformation,
	SystemExtendedHandleInformation,
	SystemLostDelayedWriteInformation,
	SystemBigPoolInformation,
	SystemSessionPoolTagInformation,
	SystemSessionMappedViewInformation,
	SystemHotpatchInformation,
	SystemObjectSecurityMode,
	SystemWatchdogTimerHandler,
	SystemWatchdogTimerInformation,
	SystemLogicalProcessorInformation,
	SystemWow64SharedInformation,
	SystemRegisterFirmwareTableInformationHandler,
	SystemFirmwareTableInformation,
	SystemModuleInformationEx,
	SystemVerifierTriageInformation,
	SystemSuperfetchInformation,
	SystemMemoryListInformation,
	SystemFileCacheInformationEx,
	MaxSystemInfoClass  // MaxSystemInfoClass should always be the last enum
} SYSTEM_INFORMATION_CLASS;


typedef struct _PEB32
{
	UCHAR InheritedAddressSpace;                                            //0x0
	UCHAR ReadImageFileExecOptions;                                         //0x1
	UCHAR BeingDebugged;                                                    //0x2
	union
	{
		UCHAR BitField;                                                     //0x3
		struct
		{
			UCHAR ImageUsesLargePages : 1;                                    //0x3
			UCHAR IsProtectedProcess : 1;                                     //0x3
			UCHAR IsLegacyProcess : 1;                                        //0x3
			UCHAR IsImageDynamicallyRelocated : 1;                            //0x3
			UCHAR SkipPatchingUser32Forwarders : 1;                           //0x3
			UCHAR SpareBits : 3;                                              //0x3
		};
	};
	ULONG Mutant;                                                           //0x4
	ULONG ImageBaseAddress;                                                 //0x8
	ULONG Ldr;                                                              //0xc

}PEB32, * PPEB32;
typedef struct _PEB_LDR_DATA32
{
	ULONG Length;                                                           //0x0
	UCHAR Initialized;                                                      //0x4
	ULONG SsHandle;                                                         //0x8
	LIST_ENTRY32 InLoadOrderModuleList;                               //0xc
	LIST_ENTRY32 InMemoryOrderModuleList;                             //0x14
	LIST_ENTRY32 InInitializationOrderModuleList;                     //0x1c
	ULONG Entr32yInProgress;                                                  //0x24
	UCHAR ShutdownInProgress;                                               //0x28
	ULONG ShutdownThreadId;                                                 //0x2c
}PEB_LDR_DATA32, * PPEB_LDR_DATA32;

typedef struct _LDR_DATA_TABLE_ENTRY32
{
	LIST_ENTRY32 InLoadOrderLinks;                                    //0x0
	LIST_ENTRY32 InMemoryOrderLinks;                                  //0x8
	LIST_ENTRY32 InInitializationOrderLinks;                          //0x10
	ULONG DllBase;                                                          //0x18
	ULONG EntryPoint;                                                       //0x1c
	ULONG SizeOfImage;                                                      //0x20
	UNICODE_STRING32 FullDllName;                                     //0x24
	UNICODE_STRING32 BaseDllName;                                     //0x2c
}LDR_DATA_TABLE_ENTRY32, * PLDR_DATA_TABLE_ENTRY32;

typedef struct _PEB_LDR_DATA64
{
	ULONG Length;                                                           //0x0
	UCHAR Initialized;                                                      //0x4
	VOID* SsHandle;                                                         //0x8
	struct _LIST_ENTRY InLoadOrderModuleList;                               //0x10
	struct _LIST_ENTRY InMemoryOrderModuleList;                             //0x20
	struct _LIST_ENTRY InInitializationOrderModuleList;                     //0x30
	VOID* EntryInProgress;                                                  //0x40
	UCHAR ShutdownInProgress;                                               //0x48
	VOID* ShutdownThreadId;                                                 //0x50
}PEB_LDR_DATA64, * PPEB_LDR_DATA64;

typedef struct _LDR_DATA_TABLE_ENTRY64
{
	struct _LIST_ENTRY InLoadOrderLinks;                                    //0x0
	struct _LIST_ENTRY InMemoryOrderLinks;                                  //0x10
	struct _LIST_ENTRY InInitializationOrderLinks;                          //0x20
	VOID* DllBase;                                                          //0x30
	VOID* EntryPoint;                                                       //0x38
	ULONG SizeOfImage;                                                      //0x40
	struct _UNICODE_STRING FullDllName;                                     //0x48
	struct _UNICODE_STRING BaseDllName;                                     //0x58
	ULONG Flags;                                                            //0x68
	USHORT LoadCount;                                                       //0x6c
	USHORT TlsIndex;                                                        //0x6e
	union
	{
		struct _LIST_ENTRY HashLinks;                                       //0x70
		struct
		{
			VOID* SectionPointer;                                           //0x70
			ULONG CheckSum;                                                 //0x78
		};
	};
	union
	{
		ULONG TimeDateStamp;                                                //0x80
		VOID* LoadedImports;                                                //0x80
	};
	struct _ACTIVATION_CONTEXT* EntryPointActivationContext;                //0x88
	VOID* PatchInformation;                                                 //0x90
	struct _LIST_ENTRY ForwarderLinks;                                      //0x98
	struct _LIST_ENTRY ServiceTagLinks;                                     //0xa8
	struct _LIST_ENTRY StaticLinks;                                         //0xb8
	VOID* ContextInformation;                                               //0xc8
	ULONGLONG OriginalBase;                                                 //0xd0
	union _LARGE_INTEGER LoadTime;                                          //0xd8
}LDR_DATA_TABLE_ENTRY64, * PLDR_DATA_TABLE_ENTRY64;

typedef struct _TEB64
{
	struct _NT_TIB64 NtTib;                                                 //0x0
	ULONGLONG EnvironmentPointer;                                           //0x38
	UCHAR ClientId[0x10];                                           //0x40
	ULONGLONG ActiveRpcHandle;                                              //0x50
	ULONGLONG ThreadLocalStoragePointer;                                    //0x58
	ULONGLONG ProcessEnvironmentBlock;                                      //0x60
	ULONG LastErrorValue;                                                   //0x68
	ULONG CountOfOwnedCriticalSections;                                     //0x6c
	ULONGLONG CsrClientThread;                                              //0x70
	ULONGLONG Win32ThreadInfo;                                              //0x78
	ULONG User32Reserved[26];                                               //0x80
	ULONG UserReserved[5];                                                  //0xe8
	ULONGLONG WOW32Reserved;                                                //0x100
	ULONG CurrentLocale;                                                    //0x108
	ULONG FpSoftwareStatusRegister;                                         //0x10c
	ULONGLONG ReservedForDebuggerInstrumentation[16];                       //0x110
	ULONGLONG SystemReserved1[30];                                          //0x190
	CHAR PlaceholderCompatibilityMode;                                      //0x280
	UCHAR PlaceholderHydrationAlwaysExplicit;                               //0x281
	CHAR PlaceholderReserved[10];                                           //0x282
	ULONG ProxiedProcessId;                                                 //0x28c
	UCHAR _ActivationStack[0x28];                    //0x290
	UCHAR WorkingOnBehalfTicket[8];                                         //0x2b8
	LONG ExceptionCode;                                                     //0x2c0
	UCHAR Padding0[4];                                                      //0x2c4
	ULONGLONG ActivationContextStackPointer;                                //0x2c8
	ULONGLONG InstrumentationCallbackSp;                                    //0x2d0
	ULONGLONG InstrumentationCallbackPreviousPc;                            //0x2d8
	ULONGLONG InstrumentationCallbackPreviousSp;                            //0x2e0
	ULONG TxFsContext;                                                      //0x2e8
	UCHAR InstrumentationCallbackDisabled;                                  //0x2ec
	UCHAR UnalignedLoadStoreExceptions;                                     //0x2ed
	UCHAR Padding1[2];                                                      //0x2ee
	UCHAR GdiTebBatch[0x4E8];                                    //0x2f0
	UCHAR RealClientId[0x10];                                       //0x7d8
	ULONGLONG GdiCachedProcessHandle;                                       //0x7e8
	ULONG GdiClientPID;                                                     //0x7f0
	ULONG GdiClientTID;                                                     //0x7f4
	ULONGLONG GdiThreadLocalInfo;                                           //0x7f8
	ULONGLONG Win32ClientInfo[62];                                          //0x800
	ULONGLONG glDispatchTable[233];                                         //0x9f0
	ULONGLONG glReserved1[29];                                              //0x1138
	ULONGLONG glReserved2;                                                  //0x1220
	ULONGLONG glSectionInfo;                                                //0x1228
	ULONGLONG glSection;                                                    //0x1230
	ULONGLONG glTable;                                                      //0x1238
	ULONGLONG glCurrentRC;                                                  //0x1240
	ULONGLONG glContext;                                                    //0x1248
	ULONG LastStatusValue;                                                  //0x1250
	UCHAR Padding2[4];                                                      //0x1254
	struct _STRING64 StaticUnicodeString;                                   //0x1258
	WCHAR StaticUnicodeBuffer[261];                                         //0x1268
	UCHAR Padding3[6];                                                      //0x1472
	ULONGLONG DeallocationStack;                                            //0x1478
	ULONGLONG TlsSlots[64];                                                 //0x1480
	struct LIST_ENTRY64 TlsLinks;                                           //0x1680
	ULONGLONG Vdm;                                                          //0x1690
	ULONGLONG ReservedForNtRpc;                                             //0x1698
	ULONGLONG DbgSsReserved[2];                                             //0x16a0
	ULONG HardErrorMode;                                                    //0x16b0
	UCHAR Padding4[4];                                                      //0x16b4
	ULONGLONG Instrumentation[11];                                          //0x16b8
	struct _GUID ActivityId;                                                //0x1710
	ULONGLONG SubProcessTag;                                                //0x1720
	ULONGLONG PerflibData;                                                  //0x1728
	ULONGLONG EtwTraceData;                                                 //0x1730
	ULONGLONG WinSockData;                                                  //0x1738
	ULONG GdiBatchCount;                                                    //0x1740
	union
	{
		struct _PROCESSOR_NUMBER CurrentIdealProcessor;                     //0x1744
		ULONG IdealProcessorValue;                                          //0x1744
		struct
		{
			UCHAR ReservedPad0;                                             //0x1744
			UCHAR ReservedPad1;                                             //0x1745
			UCHAR ReservedPad2;                                             //0x1746
			UCHAR IdealProcessor;                                           //0x1747
		};
	};
	ULONG GuaranteedStackBytes;                                             //0x1748
	UCHAR Padding5[4];                                                      //0x174c
	ULONGLONG ReservedForPerf;                                              //0x1750
	ULONGLONG ReservedForOle;                                               //0x1758
	ULONG WaitingOnLoaderLock;                                              //0x1760
	UCHAR Padding6[4];                                                      //0x1764
	ULONGLONG SavedPriorityState;                                           //0x1768
	ULONGLONG ReservedForCodeCoverage;                                      //0x1770
	ULONGLONG ThreadPoolData;                                               //0x1778
	ULONGLONG TlsExpansionSlots;                                            //0x1780
	ULONGLONG DeallocationBStore;                                           //0x1788
	ULONGLONG BStoreLimit;                                                  //0x1790
	ULONG MuiGeneration;                                                    //0x1798
	ULONG IsImpersonating;                                                  //0x179c
	ULONGLONG NlsCache;                                                     //0x17a0
	ULONGLONG pShimData;                                                    //0x17a8
	ULONG HeapData;                                                         //0x17b0
	UCHAR Padding7[4];                                                      //0x17b4
	ULONGLONG CurrentTransactionHandle;                                     //0x17b8
	ULONGLONG ActiveFrame;                                                  //0x17c0
	ULONGLONG FlsData;                                                      //0x17c8
	ULONGLONG PreferredLanguages;                                           //0x17d0
	ULONGLONG UserPrefLanguages;                                            //0x17d8
	ULONGLONG MergedPrefLanguages;                                          //0x17e0
	ULONG MuiImpersonation;                                                 //0x17e8
	union
	{
		volatile USHORT CrossTebFlags;                                      //0x17ec
		USHORT SpareCrossTebBits : 16;                                        //0x17ec
	};
	union
	{
		USHORT SameTebFlags;                                                //0x17ee
		struct
		{
			USHORT SafeThunkCall : 1;                                         //0x17ee
			USHORT InDebugPrint : 1;                                          //0x17ee
			USHORT HasFiberData : 1;                                          //0x17ee
			USHORT SkipThreadAttach : 1;                                      //0x17ee
			USHORT WerInShipAssertCode : 1;                                   //0x17ee
			USHORT RanProcessInit : 1;                                        //0x17ee
			USHORT ClonedThread : 1;                                          //0x17ee
			USHORT SuppressDebugMsg : 1;                                      //0x17ee
			USHORT DisableUserStackWalk : 1;                                  //0x17ee
			USHORT RtlExceptionAttached : 1;                                  //0x17ee
			USHORT InitialThread : 1;                                         //0x17ee
			USHORT SessionAware : 1;                                          //0x17ee
			USHORT LoadOwner : 1;                                             //0x17ee
			USHORT LoaderWorker : 1;                                          //0x17ee
			USHORT SkipLoaderInit : 1;                                        //0x17ee
			USHORT SpareSameTebBits : 1;                                      //0x17ee
		};
	};
	ULONGLONG TxnScopeEnterCallback;                                        //0x17f0
	ULONGLONG TxnScopeExitCallback;                                         //0x17f8
	ULONGLONG TxnScopeContext;                                              //0x1800
	ULONG LockCount;                                                        //0x1808
	LONG WowTebOffset;                                                      //0x180c
	ULONGLONG ResourceRetValue;                                             //0x1810
	ULONGLONG ReservedForWdf;                                               //0x1818
	ULONGLONG ReservedForCrt;                                               //0x1820
	struct _GUID EffectiveContainerId;                                      //0x1828
}TEB64, * PTEB64;

typedef struct _CONTEXT32
{
	ULONG ContextFlags;                                                     //0x0
	ULONG Dr0;                                                              //0x4
	ULONG Dr1;                                                              //0x8
	ULONG Dr2;                                                              //0xc
	ULONG Dr3;                                                              //0x10
	ULONG Dr6;                                                              //0x14
	ULONG Dr7;                                                              //0x18
	UCHAR FloatSave[0x70];                                   //0x1c
	ULONG SegGs;                                                            //0x8c
	ULONG SegFs;                                                            //0x90
	ULONG SegEs;                                                            //0x94
	ULONG SegDs;                                                            //0x98
	ULONG Edi;                                                              //0x9c
	ULONG Esi;                                                              //0xa0
	ULONG Ebx;                                                              //0xa4
	ULONG Edx;                                                              //0xa8
	ULONG Ecx;                                                              //0xac
	ULONG Eax;                                                              //0xb0
	ULONG Ebp;                                                              //0xb4
	ULONG Eip;                                                              //0xb8
	ULONG SegCs;                                                            //0xbc
	ULONG EFlags;                                                           //0xc0
	ULONG Esp;                                                              //0xc4
	ULONG SegSs;                                                            //0xc8
	UCHAR ExtendedRegisters[512];                                           //0xcc
}CONTEXT32, * PCONTEXT32;

NTSTATUS ZwQuerySystemInformation(SYSTEM_INFORMATION_CLASS SystemInformationClass, PVOID SystemInformation, ULONG SystemInformationLength, PULONG ReturnLength);
NTKERNELAPI ULONG_PTR NTAPI PsGetProcessPeb(PEPROCESS proc);;
NTSTATUS MmCopyVirtualMemory(
	IN PEPROCESS FromProcess,
	IN CONST VOID* FromAddress,
	IN PEPROCESS ToProcess,
	OUT PVOID ToAddress,
	IN SIZE_T BufferSize,
	IN KPROCESSOR_MODE PreviousMode,
	OUT PSIZE_T NumberOfBytesCopied
);
typedef NTSTATUS
(NTAPI
	* pZwProtectVirtualMemory)(
		__in HANDLE ProcessHandle,
		__inout PVOID* BaseAddress,
		__inout PSIZE_T RegionSize,
		__in ULONG NewProtect,
		__out PULONG OldProtect
		);
typedef NTSTATUS
(*PsSuspendThreadProc)(
	IN PETHREAD Thread,
	OUT PULONG PreviousSuspendCount OPTIONAL
	);
typedef NTSTATUS
(*PsResumeThreadProc)(
	IN PETHREAD Thread,
	OUT PULONG PreviousSuspendCount OPTIONAL,
	ULONG64 val1
	);
NTKERNELAPI
NTSTATUS
ObReferenceObjectByName(
	__in PUNICODE_STRING ObjectName,
	__in ULONG Attributes,
	__in_opt PACCESS_STATE AccessState,
	__in_opt ACCESS_MASK DesiredAccess,
	__in POBJECT_TYPE ObjectType,
	__in KPROCESSOR_MODE AccessMode,
	__inout_opt PVOID ParseContext,
	__out PVOID* Object
);
NTKERNELAPI
NTSTATUS
PsReferenceProcessFilePointer(
	IN PEPROCESS Process,
	OUT PVOID* pFilePointer
);


extern POBJECT_TYPE* IoDriverObjectType;


NTSTATUS
NTAPI
ZwTraceControl(
	_In_ ULONG FunctionCode,
	_In_reads_bytes_opt_(InBufferLen) PVOID InBuffer,
	_In_ ULONG InBufferLen,
	_Out_writes_bytes_opt_(OutBufferLen) PVOID OutBuffer,
	_In_ ULONG OutBufferLen,
	_Out_ PULONG ReturnLength);

EXTERN_C SKSTATUS GlbGetBuildNumber(PULONG buildNumber);
EXTERN_C VOID CpMySleepSec(LONGLONG time);
EXTERN_C VOID CpMySleepMin(LONGLONG time);
//FORCEINLINE
BOOLEAN
RemoveEntryList32(
	_In_ PLIST_ENTRY32 Entry
);
//FORCEINLINE
BOOLEAN
RemoveEntryList64(
	_In_ PLIST_ENTRY Entry
);
EXTERN_C LPSTR PsGetProcessImageFileName(PEPROCESS Process);
EXTERN_C void MyAttack(ULONG64 cr3, MY_ATTACH_OBJ* obj);
EXTERN_C void MyDeatch(MY_ATTACH_OBJ* obj);



#define xorstr(str) ::jm::xor_string([]() { return str; }, std::integral_constant<std::size_t, sizeof(str) / sizeof(*str)>{}, std::make_index_sequence<::jm::detail::_buffer_size<sizeof(str)>()>{})
#define xorstr_(str) xorstr(str).crypt_get()