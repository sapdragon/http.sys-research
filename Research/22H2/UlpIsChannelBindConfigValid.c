char __fastcall UlpIsChannelBindConfigValid(__int64 pBindConfig)
{
    unsigned int uHardening; // edx
    int uFlags; // r8d
    __int64 v3; // rax
    int bEmpty; // r8d
    __int64 iCurrentServiceName; // r10
    unsigned int iNumberOfServiceNames; // ebx
    __int64 pServiceName; // rdx
    int uTypeOfName; // ecx
    unsigned int iSomethingSize; // r9d
    __int64 iSomeIterator; // rcx
    __int64 v12; // rcx
    unsigned int v13; // r9d

    uHardening = *(_DWORD *)(pBindConfig + 4);
    if ( uHardening > 2 )
        return 0;

    uFlags = *(_DWORD *)(pBindConfig + 8);
    if ( (uFlags & 0xFFFFFFC0) != 0 || (uFlags & 0x21) == 32 || uHardening == 1 && (uFlags & 0x23) == 35 )// checks the compatibility of flags
        return 0;

    v3 = *(_QWORD *)(pBindConfig + 16);
    bEmpty = *(_DWORD *)(pBindConfig + 8) & 4;
    iCurrentServiceName = 0i64;
    iNumberOfServiceNames = *(_DWORD *)(v3 + 16);
    if ( iNumberOfServiceNames )
    {
        while ( 1 )
        {
            pServiceName = *(_QWORD *)(*(_QWORD *)(v3 + 8) + 8 * iCurrentServiceName);
            uTypeOfName = *(_DWORD *)pServiceName;// char* ( 2)  / wchar_t* ( 1 ) 
            if ( !*(_DWORD *)pServiceName || uTypeOfName > 2 || uTypeOfName == 1 && (*(_DWORD *)(pServiceName + 16) & 1) != 0 )
                break;

            if ( !bEmpty )                      // Executed if the number of names is greater than 0
            {
                if ( uTypeOfName == 2 )
                {
                    iSomethingSize = *(_DWORD *)(pServiceName + 16);// 19 in Windbg ( r9 )
                    iSomeIterator = 0i64;
                    if ( !iSomethingSize )
                        return 0;

                    while ( *(_BYTE *)(iSomeIterator + *(_QWORD *)(pServiceName + 8)) != 46 )// check if name contain '.'
                    {
                        iSomeIterator = (unsigned int)(iSomeIterator + 1);
                        if ( (unsigned int)iSomeIterator >= iSomethingSize )
                            return 0;           // tyt lomaesa naxyi
                    }
                }
                else
                {

                    if ( uTypeOfName != 1 )
                        return 0;

                    v12 = 0i64;
                    v13 = *(_DWORD *)(pServiceName + 16) >> 1;
                    if ( !v13 )
                        return 0;

                    while ( *(_WORD *)(*(_QWORD *)(pServiceName + 8) + 2 * v12) != 46 )
                    {
                        v12 = (unsigned int)(v12 + 1);
                        if ( (unsigned int)v12 >= v13 )
                            return 0;
                    }
                }
            }

            iCurrentServiceName = (unsigned int)(iCurrentServiceName + 1);
            if ( (unsigned int)iCurrentServiceName >= iNumberOfServiceNames )
                return 1;
        }

        return 0;
    }

    return 1;
}