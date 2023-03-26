# http.sys research
 A small research of http.sys

## Description
 This is a small study of http.sys. I was able to do some research on it, but I don't have time to finish them. I hope this will help someone.

## Vulnerabilities
The CVE-2023-23410 vulnerability consists of a Service name size overflow. You need to pass more than WORD, and call check via UlIsChannelBindChangeNeeded, then size is copied to WORD, and memori corpus is called when copying string in UNICODE with ASCII.


# About other files
  ## Binary
    Here you can find drivers of different versions, as well as httpapi.dll ( Not at the moment, but I will add it soon )
  ## Research
    Here are the decompiled researched functions of the driver. I hope it will help someone.
# Driver research
## Communication with the driver
 The driver communicates with the user mode application using IOCTLs. Between all this there is a layer in the form of httpapi.dll
## Functions
 ### UlCaptureChannelBindConfig
    This function is for configuring channel authentication. It is accessed either through http reqest handling or through setting for group ( IOCTL code: 0x12801D, or session ( IOCTL code: 0x12800D). You can also find versions of them in the repository. 
 ### UlpAllocateServiceNameContainer
    As the name implies, it allocates a container for server names. The only argument is the number of server names, if more than 64 it returns 0, instead of the allocated memory address (Allocate via ExAllocatePool3)
 ### UlpAddServiceNameToContainer
    It has 4 arguments (the first is the address of the allocation container, the second is the service name address, the third is the service name buffer, the fourth is the buffer length), it checks the length to avoid integer overflow ( For x64: pServiceNameLen >= 0xFFFFFFFFE8, for x86: 0xFFFFFFFFF4). If the length is valid, it allocates the length + 24 ( x86: 12 ), and writes to the container.
 ### UlpIsChannelBindConfigValid
    Again judging from the name, it validates the config, i.e. checks the flags for compatibility, and then goes through the whole buffer, checks if there is ".", if not it return false.
 ### UlCopyChannelBindConfig
    Copies the bind config, first argument from where, second argument to where.
 ### UlSetServerSessionProperty
     You can see by the name, it is only called in IOCTL handler (the correct name?)
 ### UlCopyAuthConfig
     Copies authentication settings (flags, schemes, reals, domains).
 ### UlpCaptureDigestParams
     Handles HTTP_SERVER_AUTHENTICATION_DIGEST_PARAMS from HTTP_SERVER_AUTHENTICATION_INFO.
 ### UlpCaptureBasicParams
     Handles HTTP_SERVER_AUTHENTICATION_BASIC_PARAMS from HTTP_SERVER_AUTHENTICATION_INFO.
 ### UlIsChannelBindChangeNeeded
    Compares 2 bind configs, and sets 3 argument result ( 1 if different )
 ### UlpIsServiceContainerEquivalent
    Compares all Service Name in the container. 
 ### UlExtractAndAppendAuthenticationResponseInfo
    Extracts authentication information from the request, and checks it 

The rest has either not been researched enough or is unimportant.
## Other
    \\Device\\Http\\Communication
    \\Device\\Http\\ClientSession
    \\Device\\Http\\ReqQueue


