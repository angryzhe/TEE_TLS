add_subdirectory(nullverifier)

include(FindSgxDcapQuoteVerify)

if(HOST OR WASM OR TDX)
    if(WASM OR SGXDCAPQV_FOUND)
        add_subdirectory(sgx-ecdsa)
    else()
        message(WARNING "It will not build sgx_ecdsa verifier due to libsgx_dcap_quoteverify.so not found")
    endif()
    add_subdirectory(sev-snp)
    add_subdirectory(sev)
    # disabled for envoy since SM3 is not supported in boringssl
    # add_subdirectory(csv)
endif()

if(TDX OR SGX)
    if(SGXDCAPQV_FOUND)
        add_subdirectory(tdx-ecdsa)
    else()
        message(WARNING "It will not build tdx_ecdsa verifier due to libsgx_dcap_quoteverify.so not found")
    endif()
endif()

if(OCCLUM OR SGX)
    add_subdirectory(sgx-ecdsa-qve)
endif()

if(SGX)
    add_subdirectory(sgx-la)
endif()
