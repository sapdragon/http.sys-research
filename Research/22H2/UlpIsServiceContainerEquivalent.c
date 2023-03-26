NTSTATUS __fastcall UlpIsServiceContainerEquivalent(__int64 pBindConfig, __int64 a2, _BYTE *bCompareFlag)
{
    char v5; // al
    __int64 iCurrentServiceName; // r14
    __int64 pServiceName; // rbx
    USHORT iServiceNameLength; // ax
    NTSTATUS result; // eax
    char v10; // r15
    __int64 v11; // r12
    __int64 v12; // r15
    USHORT v13; // ax
    NTSTATUS v14; // r13d
    LONG v15; // r13d
    __int64 v16; // rax
    struct _STRING SourceString; // [rsp+20h] [rbp-30h] BYREF
    struct _UNICODE_STRING DestinationString; // [rsp+30h] [rbp-20h] BYREF
    UNICODE_STRING String2; // [rsp+40h] [rbp-10h] BYREF
    char v20; // [rsp+90h] [rbp+40h]

    DestinationString = 0i64;
    String2 = 0i64;
    v5 = 0;
    SourceString = 0i64;
    while ( 1 )
    {
        iCurrentServiceName = 0i64;
        v20 = v5;
        if ( *(_DWORD *)(pBindConfig + 16) )    // amount of services == 0?
            break;

LABEL_21:
        if ( v5 )                               // wtf shiza brr
        {
            *bCompareFlag = 1;
            return 0;
        }

        v16 = pBindConfig;
        pBindConfig = a2;
        a2 = v16;
        v5 = 1;
    }

    while ( 1 )
    {
        pServiceName = *(_QWORD *)(*(_QWORD *)(pBindConfig + 8) + 8 * iCurrentServiceName);
        iServiceNameLength = *(_WORD *)(pServiceName + 16);
        if ( *(_DWORD *)pServiceName == 1 )     // wchar
        {
            DestinationString.Length = *(_WORD *)(pServiceName + 16);
            DestinationString.MaximumLength = iServiceNameLength;
            DestinationString.Buffer = *(PWSTR *)(pServiceName + 8);
        }
        else                                    // ascii ( 2 )
        {
            SourceString.Length = *(_WORD *)(pServiceName + 16);
            SourceString.MaximumLength = iServiceNameLength;
            SourceString.Buffer = *(PCHAR *)(pServiceName + 8);
            result = RtlAnsiStringToUnicodeString(&DestinationString, &SourceString, 1u);
            if ( result )
                return result;
        }

        v10 = 0;
        v11 = 0i64;
        if ( *(_DWORD *)(a2 + 16) )
            break;

LABEL_16:
        if ( *(_DWORD *)pServiceName == 2 )
            RtlFreeUnicodeString(&DestinationString);

        if ( !v10 )
        {
            *bCompareFlag = 0;
            return 0;
        }

        iCurrentServiceName = (unsigned int)(iCurrentServiceName + 1);
        if ( (unsigned int)iCurrentServiceName >= *(_DWORD *)(pBindConfig + 16) )
        {
            v5 = v20;
            goto LABEL_21;
        }
    }

    while ( 1 )
    {
        v12 = *(_QWORD *)(*(_QWORD *)(a2 + 8) + 8 * v11);
        v13 = *(_WORD *)(v12 + 16);
        if ( *(_DWORD *)v12 == 1 )
        {
            String2.Length = *(_WORD *)(v12 + 16);
            String2.MaximumLength = v13;
            String2.Buffer = *(PWSTR *)(v12 + 8);
            goto LABEL_10;
        }

        SourceString.Length = *(_WORD *)(v12 + 16);
        SourceString.MaximumLength = v13;
        SourceString.Buffer = *(PCHAR *)(v12 + 8);
        v14 = RtlAnsiStringToUnicodeString(&String2, &SourceString, 1u);
        if ( v14 )
            break;

LABEL_10:
        v15 = RtlCompareUnicodeString(&DestinationString, &String2, 1u);
        if ( *(_DWORD *)v12 == 2 )
            RtlFreeUnicodeString(&String2);

        if ( !v15 )
        {
            v10 = 1;
            goto LABEL_16;
        }

        v11 = (unsigned int)(v11 + 1);
        if ( (unsigned int)v11 >= *(_DWORD *)(a2 + 16) )
        {
            v10 = 0;
            goto LABEL_16;
        }
    }

    if ( *(_DWORD *)pServiceName == 2 )
        RtlFreeUnicodeString(&DestinationString);

    return v14;
}