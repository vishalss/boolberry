// Copyright (c) 2012-2013 The Cryptonote developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <list>
#include "serialization/keyvalue_serialization.h"
#include "currency_core/currency_basic.h"
#include "currency_protocol/blobdatatype.h"
namespace currency
{


#define BC_COMMANDS_POOL_BASE 2000


  /************************************************************************/
  /*                                                                      */
  /************************************************************************/
  struct block_complete_entry
  {
    blobdata block;
    std::list<blobdata> txs;
    BEGIN_KV_SERIALIZE_MAP()
      KV_SERIALIZE(block)
      KV_SERIALIZE(txs)
    END_KV_SERIALIZE_MAP()
  };

  /************************************************************************/
  /*                                                                      */
  /************************************************************************/
  struct connection_info
    {
      bool incoming;
      bool localhost;
      bool local_ip;

      std::string ip;
      std::string port;

      std::string peer_id;

      uint64_t recv_count;
      uint64_t recv_idle_time;

      uint64_t send_count;
      uint64_t send_idle_time;

      std::string state;

      uint64_t live_time;

      uint64_t avg_download;
      uint64_t current_download;

      uint64_t avg_upload;
      uint64_t current_upload;

      BEGIN_KV_SERIALIZE_MAP()
        KV_SERIALIZE(incoming)
        KV_SERIALIZE(localhost)
        KV_SERIALIZE(local_ip)
        KV_SERIALIZE(ip)
        KV_SERIALIZE(port)
        KV_SERIALIZE(peer_id)
        KV_SERIALIZE(recv_count)
        KV_SERIALIZE(recv_idle_time)
        KV_SERIALIZE(send_count)
        KV_SERIALIZE(send_idle_time)
        KV_SERIALIZE(state)
        KV_SERIALIZE(live_time)
        KV_SERIALIZE(avg_download)
        KV_SERIALIZE(current_download)
        KV_SERIALIZE(avg_upload)
        KV_SERIALIZE(current_upload)
      END_KV_SERIALIZE_MAP()
  };

  /************************************************************************/
  /*                                                                      */
  /************************************************************************/
  struct NOTIFY_NEW_BLOCK
  {
    const static int ID = BC_COMMANDS_POOL_BASE + 1;

    struct request
    {
      block_complete_entry b;
      uint64_t current_blockchain_height;
      uint32_t hop;

      BEGIN_KV_SERIALIZE_MAP()
        KV_SERIALIZE(b)
        KV_SERIALIZE(current_blockchain_height)
        KV_SERIALIZE(hop)
      END_KV_SERIALIZE_MAP()
    };
  };

  /************************************************************************/
  /*                                                                      */
  /************************************************************************/
  struct NOTIFY_NEW_TRANSACTIONS
  {
    const static int ID = BC_COMMANDS_POOL_BASE + 2;

    struct request
    {
      std::list<blobdata>   txs;

      BEGIN_KV_SERIALIZE_MAP()
        KV_SERIALIZE(txs)
      END_KV_SERIALIZE_MAP()
    };
  };
  /************************************************************************/
  /*                                                                      */
  /************************************************************************/
  struct NOTIFY_REQUEST_GET_OBJECTS
  {
    const static int ID = BC_COMMANDS_POOL_BASE + 3;

    struct request
    {
      std::list<crypto::hash>    txs;
      std::list<crypto::hash>    blocks;

      BEGIN_KV_SERIALIZE_MAP()
        KV_SERIALIZE_CONTAINER_POD_AS_BLOB(txs)
        KV_SERIALIZE_CONTAINER_POD_AS_BLOB(blocks)
      END_KV_SERIALIZE_MAP()
    };
  };

  struct NOTIFY_RESPONSE_GET_OBJECTS
  {
    const static int ID = BC_COMMANDS_POOL_BASE + 4;

    struct request
    {
      std::list<blobdata>              txs;
      std::list<block_complete_entry>  blocks;
      std::list<crypto::hash>               missed_ids;
      uint64_t                         current_blockchain_height;

      BEGIN_KV_SERIALIZE_MAP()
        KV_SERIALIZE(txs)
        KV_SERIALIZE(blocks)
        KV_SERIALIZE_CONTAINER_POD_AS_BLOB(missed_ids)
        KV_SERIALIZE(current_blockchain_height)
      END_KV_SERIALIZE_MAP()
    };
  };

  struct CORE_SYNC_DATA
  {
    uint64_t current_height;
    crypto::hash  top_id;
    uint64_t last_checkpoint_height;

    BEGIN_KV_SERIALIZE_MAP()
      KV_SERIALIZE(current_height)
      KV_SERIALIZE_VAL_POD_AS_BLOB(top_id)
      KV_SERIALIZE(last_checkpoint_height)
    END_KV_SERIALIZE_MAP()
  };

  struct NOTIFY_REQUEST_CHAIN
  {
    const static int ID = BC_COMMANDS_POOL_BASE + 6;

    struct request
    {
      std::list<crypto::hash> block_ids; /*IDs of the first 10 blocks are sequential, next goes with pow(2,n) offset, like 2, 4, 8, 16, 32, 64 and so on, and the last one is always genesis block */

      BEGIN_KV_SERIALIZE_MAP()
        KV_SERIALIZE_CONTAINER_POD_AS_BLOB(block_ids)
      END_KV_SERIALIZE_MAP()
    };
  };

  struct NOTIFY_RESPONSE_CHAIN_ENTRY
  {
    const static int ID = BC_COMMANDS_POOL_BASE + 7;

    struct request
    {
      uint64_t start_height;
      uint64_t total_height;
      std::list<crypto::hash> m_block_ids;

      BEGIN_KV_SERIALIZE_MAP()
        KV_SERIALIZE(start_height)
        KV_SERIALIZE(total_height)
        KV_SERIALIZE_CONTAINER_POD_AS_BLOB(m_block_ids)
      END_KV_SERIALIZE_MAP()
    };
  };

}
