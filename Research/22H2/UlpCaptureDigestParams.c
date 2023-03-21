__int64 __fastcall UlpCaptureDigestParams(__int64 pBasicInformation, char a2, _QWORD *a3, _WORD *a4, _QWORD *a5, _WORD *a6)
{
    char v8; // r10
    unsigned int v10; // r8d
    void *v11; // rsi
    __int16 v12; // cx
    void *v13; // rdi
    __int16 v14; // ax
    size_t v15; // r15
    size_t uBufferSize; // r15
    const void *v17; // r14
    void *Pool3; // rax
    void *v19; // rax
    __int16 v21; // [rsp+34h] [rbp-64h]
    unsigned int v22; // [rsp+38h] [rbp-60h]
    void *Src; // [rsp+50h] [rbp-48h]

    v8 = a2;
    v10 = 0;
    v22 = 0;
    v11 = 0i64;
    v12 = 0;
    v21 = 0;
    v13 = 0i64;
    v14 = 0;
    *a3 = 0i64;
    *a4 = 0;
    *a5 = 0i64;
    *a6 = 0;
    v15 = *(unsigned __int16 *)(pBasicInformation + 32);
    Src = *(void **)(pBasicInformation + 40);
    if ( !(_WORD)v15 )
    {
LABEL_2:
        uBufferSize = *(unsigned __int16 *)(pBasicInformation + 16);
        v17 = *(const void **)(pBasicInformation + 24);
        if ( (_WORD)uBufferSize )
        {
            UlProbeWideString((unsigned __int64)v17, (unsigned __int16)uBufferSize, v8);
            Pool3 = (void *)ExAllocatePool3(66i64, (unsigned int)uBufferSize, 1146645589i64, &UxLowPriorityPool);
            v13 = Pool3;
            if ( !Pool3 )
            {
                v10 = -1073741670;
                v22 = -1073741670;
                if ( (BYTE4(WPP_MAIN_CB.Queue.Wcb.DeviceRoutine) & 0x20) != 0 )
                {
                    WPP_SF_D(11i64, &WPP_6ccb77abfc8c35a9db1a527b2c060c39_Traceguids, 3221225626i64);
                    v10 = -1073741670;
                }

                goto LABEL_14;
            }

            memmove(Pool3, v17, uBufferSize);
            v14 = uBufferSize;
            v12 = v21;
            v10 = 0;
        }

        *a3 = v11;
        *a4 = v12;
        v11 = 0i64;
        *a5 = v13;
        *a6 = v14;
        goto LABEL_14;
    }

    UlProbeWideString(*(_QWORD *)(pBasicInformation + 40), (unsigned __int16)v15, a2);
    v19 = (void *)ExAllocatePool3(66i64, v15, 1146645589i64, &UxLowPriorityPool);
    v11 = v19;
    if ( v19 )
    {
        memmove(v19, Src, v15);
        v12 = v15;
        v21 = v15;
        v14 = 0;
        v10 = 0;
        v8 = a2;
        goto LABEL_2;
    }

    v10 = -1073741670;
    v22 = -1073741670;
    if ( (BYTE4(WPP_MAIN_CB.Queue.Wcb.DeviceRoutine) & 0x20) != 0 )
    {
        WPP_SF_D(10i64, &WPP_6ccb77abfc8c35a9db1a527b2c060c39_Traceguids, 3221225626i64);
        v10 = -1073741670;
    }

LABEL_14:
    if ( v11 )
    {
        ExFreePoolWithTag(v11, 0);
        return v22;
    }

    return v10;
}