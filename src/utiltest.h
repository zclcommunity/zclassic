// Copyright (c) 2016 The Zclassic developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ZCLASSIC_UTIL_TEST_H
#define ZCLASSIC_UTIL_TEST_H

#include "key_io.h"
#include "wallet/wallet.h"
#include "zclassic/JoinSplit.hpp"
#include "zclassic/Note.hpp"
#include "zclassic/NoteEncryption.hpp"
#include "zclassic/zip32.h"

// Sprout
CWalletTx GetValidSproutReceive(ZCJoinSplit& params,
                                const libzclassic::SproutSpendingKey& sk,
                                CAmount value,
                                bool randomInputs,
                                int32_t version = 2);
CWalletTx GetInvalidCommitmentSproutReceive(ZCJoinSplit& params,
                                const libzclassic::SproutSpendingKey& sk,
                                CAmount value,
                                bool randomInputs,
                                int32_t version = 2);
libzclassic::SproutNote GetSproutNote(ZCJoinSplit& params,
                                   const libzclassic::SproutSpendingKey& sk,
                                   const CTransaction& tx, size_t js, size_t n);
CWalletTx GetValidSproutSpend(ZCJoinSplit& params,
                              const libzclassic::SproutSpendingKey& sk,
                              const libzclassic::SproutNote& note,
                              CAmount value);

// Sapling
static const std::string T_SECRET_REGTEST = "cND2ZvtabDbJ1gucx9GWH6XT9kgTAqfb6cotPt5Q5CyxVDhid2EN";

struct TestSaplingNote {
    libzclassic::SaplingNote note;
    SaplingMerkleTree tree;
};

const Consensus::Params& RegtestActivateSapling();

void RegtestDeactivateSapling();

libzclassic::SaplingExtendedSpendingKey GetTestMasterSaplingSpendingKey();

CKey AddTestCKeyToKeyStore(CBasicKeyStore& keyStore);

/**
 * Generate a dummy SaplingNote and a SaplingMerkleTree with that note's commitment.
 */
TestSaplingNote GetTestSaplingNote(const libzclassic::SaplingPaymentAddress& pa, CAmount value);

CWalletTx GetValidSaplingReceive(const Consensus::Params& consensusParams,
                                 CBasicKeyStore& keyStore,
                                 const libzclassic::SaplingExtendedSpendingKey &sk,
                                 CAmount value);

#endif // ZCLASSIC_UTIL_TEST_H
