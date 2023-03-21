__int64 __fastcall UlCaptureChannelBindConfig(__int64 a1, __int64 pChannelBinding, __int64 pDstChannelBindConfig, IRP *IRP, char bRaiseException)
{
    IRP *pIRP; // r12
    volatile signed __int32 *pAllocatedServiceNameContainer; // rdi
    BOOLEAN bIsX86; // al
    unsigned __int64 pServiceNamesArray; // r13
    __int64 iNumberOfServiceNames; // rbx
    __int64 v11; // rcx
    __int64 iSizeOfServiceNames; // rdx
    int uAllignForServiceName; // r8d
    __int64 ErrorCode2; // r8
    __int64 iCurrentServiceName; // r14
    unsigned __int64 pServiceName_1; // rsi
    int uBaseType; // r12d
    unsigned __int64 pServiceNameBuffer; // rax
    unsigned int pServiceNameSize; // esi
    unsigned __int64 pServiceName; // rsi
    unsigned int ServiceNameToContainerErrorCode; // eax
    __int64 v22; // rcx
    __int64 v23; // rdx
    unsigned int uErrorCode; // [rsp+30h] [rbp-88h]
    volatile signed __int32 *pServiceNameContainer_0; // [rsp+40h] [rbp-78h]
    __int128 pChannelBindConfig; // [rsp+48h] [rbp-70h] BYREF
    volatile signed __int32 *pAllocatedServiceNameContainer_1; // [rsp+58h] [rbp-60h]
    int v29; // [rsp+60h] [rbp-58h]
    int v30; // [rsp+64h] [rbp-54h]
    const void *pServiceNameBuffer_0; // [rsp+68h] [rbp-50h]
    unsigned __int64 pServiceNameBuffer_1; // [rsp+70h] [rbp-48h]
    unsigned __int64 v33; // [rsp+78h] [rbp-40h]
    unsigned __int64 pServiceName_2; // [rsp+80h] [rbp-38h]

    pIRP = IRP;
    uErrorCode = 0;
    pChannelBindConfig = 0i64;
    pAllocatedServiceNameContainer_1 = 0i64;
    pAllocatedServiceNameContainer = 0i64;
    pServiceNameContainer_0 = 0i64;
    bIsX86 = IoIs32bitProcess(IRP);
    *(_QWORD *)((char *)&pChannelBindConfig + 4) = *(_QWORD *)pChannelBinding;
    if ( bIsX86 )
    {
        pServiceNamesArray = *(unsigned int *)(pChannelBinding + 8);
        v33 = pServiceNamesArray;               // not used...
        iNumberOfServiceNames = *(unsigned int *)(pChannelBinding + 12);
        if ( (unsigned int)iNumberOfServiceNames > 0x40 )
        {
            uErrorCode = 0xC000000D;
            if ( (BYTE4(WPP_MAIN_CB.Queue.Wcb.DeviceRoutine) & 0x20) == 0 )
                goto LABEL_35;

            v11 = 39i64;

LABEL_33:
            ErrorCode2 = 3221225485i64;

LABEL_34:
            WPP_SF_D(v11, &WPP_6ccb77abfc8c35a9db1a527b2c060c39_Traceguids, ErrorCode2);
            goto LABEL_35;
        }

        iSizeOfServiceNames = 4 * iNumberOfServiceNames;
        uAllignForServiceName = 4;
    }
    else
    {
        pServiceNamesArray = *(_QWORD *)(pChannelBinding + 8);
        v33 = pServiceNamesArray;
        iNumberOfServiceNames = *(unsigned int *)(pChannelBinding + 16);
        if ( (unsigned int)iNumberOfServiceNames > 0x40 )
        {
            uErrorCode = -1073741811;
            if ( (BYTE4(WPP_MAIN_CB.Queue.Wcb.DeviceRoutine) & 0x20) == 0 )
                goto LABEL_35;

            v11 = 40i64;
            goto LABEL_33;
        }

        iSizeOfServiceNames = 8 * iNumberOfServiceNames;
        uAllignForServiceName = 8;
    }

    UlProbeForRead(pServiceNamesArray, iSizeOfServiceNames, uAllignForServiceName, bRaiseException);
    pAllocatedServiceNameContainer = (volatile signed __int32 *)UlpAllocateServiceNameContainer(iNumberOfServiceNames);
    pServiceNameContainer_0 = pAllocatedServiceNameContainer;
    if ( !pAllocatedServiceNameContainer )
    {
        ErrorCode2 = 0xC0000454i64;
        uErrorCode = 0xC0000454;
        if ( (BYTE4(WPP_MAIN_CB.Queue.Wcb.DeviceRoutine) & 0x20) == 0 )
            goto LABEL_35;

        v11 = 41i64;
        goto LABEL_34;
    }

    iCurrentServiceName = 0i64;
    v30 = 0;                                    // not used
    while ( (unsigned int)iCurrentServiceName < (unsigned int)iNumberOfServiceNames )
    {
        if ( IoIs32bitProcess(pIRP) )
        {
            pServiceName_1 = *(unsigned int *)(pServiceNamesArray + 4 * iCurrentServiceName);
            pServiceName_2 = pServiceName_1;
            UlProbeForRead((unsigned int)pServiceName_1, 4i64, 4, bRaiseException);
            uBaseType = *(_DWORD *)pServiceName_1;
            v29 = uBaseType;
            if ( uBaseType != 2 && uBaseType != 1 )
            {
                uErrorCode = -1073741811;
                if ( (BYTE4(WPP_MAIN_CB.Queue.Wcb.DeviceRoutine) & 0x20) == 0 )
                    break;

                v11 = 42i64;
                goto LABEL_33;
            }

            UlProbeForRead(pServiceName_1, 12i64, 4, bRaiseException);
            pServiceNameBuffer = *(unsigned int *)(pServiceName_1 + 4);
            pServiceNameBuffer_0 = (const void *)pServiceNameBuffer;
            pServiceNameSize = *(_DWORD *)(pServiceName_1 + 8);
        }
        else
        {
            pServiceName = *(_QWORD *)(pServiceNamesArray + 8 * iCurrentServiceName);
            pServiceName_2 = pServiceName;
            UlProbeForRead(pServiceName, 4i64, 8, bRaiseException);
            uBaseType = *(_DWORD *)pServiceName;
            v29 = uBaseType;
            if ( uBaseType != 2 && uBaseType != 1 )
            {
                uErrorCode = 030000000015;
                if ( (BYTE4(WPP_MAIN_CB.Queue.Wcb.DeviceRoutine) & 0x20) == 0 )
                    break;

                v11 = 43i64;
                goto LABEL_33;
            }

            UlProbeForRead(pServiceName, 24i64, 8, bRaiseException);
            pServiceNameBuffer = *(_QWORD *)(pServiceName + 8);
            pServiceNameSize = *(_DWORD *)(pServiceName + 16);
            pServiceNameBuffer_0 = (const void *)pServiceNameBuffer;
        }

        pServiceNameBuffer_1 = pServiceNameBuffer;// not used - wtf ida??
        if ( pServiceNameSize > 0xFFFC )
        {
            uErrorCode = 030000000015;          // Status / Error code?
            if ( (BYTE4(WPP_MAIN_CB.Queue.Wcb.DeviceRoutine) & 0x20) == 0 )
                break;

            v11 = 44i64;
            goto LABEL_33;
        }

        UlProbeForRead(pServiceNameBuffer, pServiceNameSize, 1, bRaiseException);
        ServiceNameToContainerErrorCode = UlpAddServiceNameToContainer((__int64)pAllocatedServiceNameContainer, uBaseType, pServiceNameBuffer_0, pServiceNameSize);
        uErrorCode = ServiceNameToContainerErrorCode;
        if ( ServiceNameToContainerErrorCode )
        {
            if ( (BYTE4(WPP_MAIN_CB.Queue.Wcb.DeviceRoutine) & 0x20) == 0 )
                break;

            v11 = 45i64;
            ErrorCode2 = ServiceNameToContainerErrorCode;
            goto LABEL_34;
        }

        iCurrentServiceName = (unsigned int)(iCurrentServiceName + 1);
        v30 = iCurrentServiceName;
        pIRP = IRP;
    }

LABEL_35:
    if ( !uErrorCode )
    {
        pAllocatedServiceNameContainer_1 = pAllocatedServiceNameContainer;// wtf not used??
        LODWORD(pChannelBindConfig) = pChannelBindConfig | 1;
        if ( UlpIsChannelBindConfigValid((__int64)&pChannelBindConfig) )
        {
            UlCleanupChannelBindConfig(pDstChannelBindConfig);
            UlCopyChannelBindConfig(pDstChannelBindConfig, (unsigned int *)&pChannelBindConfig);
            v23 = a1;
            if ( (*(_BYTE *)(a1 + 1738) & 0x20) != 0 )
                McTemplateK0uqq_EtwWriteTransfer(a1 + 1664);// Write registration handle ( a1 + 1664 ). Not needed x86/x64 checks? 

            if ( ((__int64)WPP_MAIN_CB.Queue.Wcb.DeviceContext & 2) != 0 )
                WPP_SF_HLL(v22, v23, SWORD2(pChannelBindConfig), 1, iNumberOfServiceNames);// Trace message
        }
        else
        {
            uErrorCode = 030000000015;
        }
    }

    if ( pAllocatedServiceNameContainer && _InterlockedExchangeAdd(pAllocatedServiceNameContainer, 0xFFFFFFFF) == 1 )// if memory allocated -> free
        UlFreeServiceNameContainer(pServiceNameContainer_0);

    return uErrorCode;
}