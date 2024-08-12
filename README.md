# http.sys Research

A comprehensive study of the http.sys driver

## Description

This document presents a concise investigation into http.sys. While the research is not exhaustive, it aims to provide valuable insights for further exploration.

## Vulnerabilities

### CVE-2023-23410

This vulnerability involves a Service name size overflow. The exploitation process is as follows:
1. Pass a value larger than WORD
2. Call the check via `UlIsChannelBindChangeNeeded`
3. The size is then copied to WORD
4. Memory corruption occurs when copying a string in UNICODE with ASCII

## File Structure

### Binary

This directory contains:
- Drivers of different versions
- httpapi.dll (To be added soon)

### Research

This section includes decompiled and analyzed functions of the driver, intended to assist further research.

## Driver Analysis

### Driver Communication

The driver communicates with user-mode applications using IOCTLs. httpapi.dll serves as an intermediary layer in this process.

### Key Functions

#### UlCaptureChannelBindConfig

Purpose: Configures channel authentication
Access: Through HTTP request handling or setting for:
- Group (IOCTL code: 0x12801D)
- Session (IOCTL code: 0x12800D)

#### UlpAllocateServiceNameContainer

- Allocates a container for server names
- Single argument: number of server names
- Returns 0 if more than 64 names, otherwise returns allocated memory address
- Memory allocation via ExAllocatePool3

#### UlpAddServiceNameToContainer

Arguments:
1. Address of allocation container
2. Service name address
3. Service name buffer
4. Buffer length

Function:
- Checks length to prevent integer overflow
  - x64: pServiceNameLen >= 0xFFFFFFFFE8
  - x86: 0xFFFFFFFFF4
- If valid, allocates memory (length + 24 for x64, length + 12 for x86)
- Writes to the container

#### UlpIsChannelBindConfigValid

- Validates config
- Checks flags for compatibility
- Scans buffer for "."
- Returns false if "." is not found

#### UlCopyChannelBindConfig

Copies bind config from source to destination

#### UlSetServerSessionProperty

Called in IOCTL handler (naming accuracy to be confirmed)

#### UlCopyAuthConfig

Copies authentication settings (flags, schemes, realms, domains)

#### UlpCaptureDigestParams

Processes HTTP_SERVER_AUTHENTICATION_DIGEST_PARAMS from HTTP_SERVER_AUTHENTICATION_INFO

#### UlpCaptureBasicParams

Handles HTTP_SERVER_AUTHENTICATION_BASIC_PARAMS from HTTP_SERVER_AUTHENTICATION_INFO

#### UlIsChannelBindChangeNeeded

- Compares two bind configs
- Sets third argument result (1 if different)

#### UlpIsServiceContainerEquivalent

Compares all Service Names in the container

#### UlExtractAndAppendAuthenticationResponseInfo

Extracts and verifies authentication information from the request

Note: Other functions are either insufficiently researched or deemed less significant.

## Additional Information

Relevant device paths:
- `\\Device\\Http\\Communication`
- `\\Device\\Http\\ClientSession`
- `\\Device\\Http\\ReqQueue`
