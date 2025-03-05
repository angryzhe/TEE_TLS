/* Copyright (c) 2022 Intel Corporation
 * Copyright (c) 2020-2022 Alibaba Cloud
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _CRYPTO_H
#define _CRYPTO_H

#include <stdbool.h>
#include <openssl/evp.h>
#include "sevapi.h"
#include "utils.h"

#ifdef OPENSSL_IS_BORINGSSL
// BN_lebin2bn was missing in boringssl before this commit. https://github.com/google/boringssl/commit/004317217f81b14c764748f42c5ea88fd05fea3c
#define BN_lebin2bn BN_le2bn
#endif

bool digest_sha(const void *msg, size_t msg_len, uint8_t *digest, size_t digest_len,
		SHA_TYPE hash_algo);
bool verify_message(sev_sig *sig, EVP_PKEY **evp_key_pair, const uint8_t *msg, size_t length,
		    const SEV_SIG_ALGO algo);

#endif /* _CRYPTO_H */
