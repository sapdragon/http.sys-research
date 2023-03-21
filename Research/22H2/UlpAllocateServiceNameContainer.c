__int64 __fastcall UlpAllocateServiceNameContainer(unsigned int iAmountOfServiceNames)
{
    __int64 result; // rax

    if ( iAmountOfServiceNames > 0x40 )
        return 0i64;

    result = ExAllocatePool3(256i64, 8 * iAmountOfServiceNames + 24, 1197042773i64, &UxLowPriorityPool);
    if ( result )
    {
        *(_DWORD *)result = 1;
        *(_QWORD *)(result + 8) = result + 24;
        *(_DWORD *)(result + 16) = iAmountOfServiceNames;
    }

    return result;
}