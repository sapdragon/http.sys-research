__int64 __fastcall UlpAddServiceNameToContainer(__int64 pServiceNameContainter, int pServiceName, const void *pServiceNameBuffer, unsigned int pServiceNameLen)
{
    __int64 v4; // r12
    size_t v6; // rbp
    unsigned int ErrorCode; // ebx
    __int64 Pool3; // rax
    __int64 v11; // rsi

    v4 = *(unsigned int *)(pServiceNameContainter + 20);
    v6 = pServiceNameLen;
    if ( pServiceNameLen >= 0xFFFFFFE8 || pServiceNameLen == 0 )
    {
        return 0xC000000D;
    }
    else
    {
        Pool3 = ExAllocatePool3(258i64, pServiceNameLen + 24, 0x48596C55i64, &UxLowPriorityPool);
        ErrorCode = 0;
        v11 = Pool3;
        if ( Pool3 )
        {
            *(_DWORD *)Pool3 = pServiceName;
            *(_QWORD *)(Pool3 + 8) = Pool3 + 24;
            *(_DWORD *)(Pool3 + 16) = v6;
            memmove((void *)(Pool3 + 24), pServiceNameBuffer, v6);
            *(_QWORD *)(*(_QWORD *)(pServiceNameContainter + 8) + 8 * v4) = v11;
            ++*(_DWORD *)(pServiceNameContainter + 20);
        }
        else
        {
            return 0xC000009A;
        }
    }

    return ErrorCode;                           // IDA Pro shiza? No its error code brrrrr
}