void __fastcall UlCleanupChannelBindConfig(__int64 pDstChannelBindConfig)
{
    volatile signed __int32 *pServceNamesArray; // rcx

    if ( (*(_DWORD *)pDstChannelBindConfig & 1) != 0 )
    {
        pServceNamesArray = *(volatile signed __int32 **)(pDstChannelBindConfig + 16);
        if ( pServceNamesArray )
        {
            if ( _InterlockedExchangeAdd(pServceNamesArray, 0xFFFFFFFF) == 1 )
                UlFreeServiceNameContainer(*(_QWORD **)(pDstChannelBindConfig + 16));
        }

        *(_DWORD *)pDstChannelBindConfig &= ~1u;
    }
}