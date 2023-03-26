NTSTATUS __fastcall UlIsChannelBindChangeNeeded(int *a1, __int64 pChannelConfig, bool *bIsChanged)
{
    int flagsValue; // eax
    __int64 sFirstContainerName; // rcx
    __int64 pNamesArray; // rdx
    NTSTATUS bResult; // eax
    char v8; // [rsp+30h] [rbp+8h] BYREF

    flagsValue = *a1;
    v8 = 0;
    if ( (flagsValue & 1) == 0 || a1[1] != *(_DWORD *)(pChannelConfig + 4) || a1[2] != *(_DWORD *)(pChannelConfig + 8) )
        goto LABEL_10;

    sFirstContainerName = *((_QWORD *)a1 + 2);
    pNamesArray = *(_QWORD *)(pChannelConfig + 16);
    if ( !sFirstContainerName )
    {
        if ( !pNamesArray )
        {
            *bIsChanged = 0;
            return 0;
        }

LABEL_10:
        *bIsChanged = 1;
        return 0;
    }

    if ( !pNamesArray )
        goto LABEL_10;

    bResult = UlpIsServiceContainerEquivalent(sFirstContainerName, pNamesArray, &v8);// Compare strings xd
    if ( bResult < 0 )
        return bResult;

    *bIsChanged = v8 == 0;
    return 0;
}