__int64 __fastcall UlpCaptureBasicParams(__int64 pBasicParams, char bIsWriteOperation, _QWORD *pOutput, _WORD *pLenPtr)
{
    unsigned int uErrorCode; // ebx
    void *pAllocatedMemory; // rdi
    __int16 uLength_1; // ax
    __int64 uLength; // rdx
    void *Pool3; // rax

    uErrorCode = 0;
    pAllocatedMemory = 0i64;
    uLength_1 = 0;
    *pOutput = 0i64;
    *pLenPtr = 0;
    uLength = *(unsigned __int16 *)(pBasicParams + 48);
    if ( !(_WORD)uLength )
        goto LABEL_7;

    UlProbeWideString(*(_QWORD *)(pBasicParams + 56), uLength, bIsWriteOperation);
    Pool3 = (void *)ExAllocatePool3(66i64, *(unsigned __int16 *)(pBasicParams + 48), 1096313941i64, &UxLowPriorityPool);
    pAllocatedMemory = Pool3;
    if ( Pool3 )
    {
        memmove(Pool3, *(const void **)(pBasicParams + 56), *(unsigned __int16 *)(pBasicParams + 48));
        uLength_1 = *(_WORD *)(pBasicParams + 48);

LABEL_7:
        *pOutput = pAllocatedMemory;
        *pLenPtr = uLength_1;
        return uErrorCode;
    }

    uErrorCode = 0xC000009A;
    if ( (BYTE4(WPP_MAIN_CB.Queue.Wcb.DeviceRoutine) & 0x20) != 0 )
        WPP_SF_D(13i64, &WPP_6ccb77abfc8c35a9db1a527b2c060c39_Traceguids, 0xC000009Ai64);

    return uErrorCode;
}