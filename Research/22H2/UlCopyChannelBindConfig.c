volatile signed __int32 *__fastcall UlCopyChannelBindConfig(__int64 pDstChannel, unsigned int *pSourceChannel)
{
    unsigned int valueTwo; // eax
    volatile signed __int32 *uReturnValue; // rax

    *(_DWORD *)pDstChannel = *pSourceChannel;
    *(_DWORD *)(pDstChannel + 8) = pSourceChannel[2];
    valueTwo = pSourceChannel[1];
    *(_QWORD *)(pDstChannel + 16) = 0i64;
    *(_DWORD *)(pDstChannel + 4) = valueTwo;
    uReturnValue = (volatile signed __int32 *)*pSourceChannel;
    if ( ((unsigned __int8)uReturnValue & 1) != 0 )
    {
        uReturnValue = (volatile signed __int32 *)*((_QWORD *)pSourceChannel + 2);
        if ( uReturnValue )
        {
            _InterlockedIncrement(uReturnValue);
            uReturnValue = (volatile signed __int32 *)*((_QWORD *)pSourceChannel + 2);
            *(_QWORD *)(pDstChannel + 16) = uReturnValue;
        }
    }

    return uReturnValue;
}