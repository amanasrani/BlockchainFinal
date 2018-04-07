#pragma once
#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <unordered_map>
#include "block.h"

typedef unsigned long long int uint64;

class Block_Creator
{
	private:
		uint64 no_of_non_coinbase_txns;
		uint64 no_txns_per_block;
		uint64 server_id;
	public:
		Block_Creator(int no_of_non_coinbase_txns, uint64 server_id);
		Block generate_block(vector<Block_Transaction> &unconfirmed_txns_vector, Block previous_block, std::unordered_map<uint64, Block_Transaction> &confirmed_txns_map,std::string hash_of_last_txn_prior_to_coinbase);
		void remove_all_confirmed_txns(vector<Block_Transaction> &unconfirmed_txns_vector, std::unordered_map<uint64, Block_Transaction> &confirmed_txns_map);
		Block_Transaction gen_coinbase_txn(std::string hash_of_last_txn_prior_to_coinbase);
		void set_server_id(uint64 server_id);
		uint64 get_server_id();
		void set_no_of_non_coinbase_txns(int no);
		int get_no_of_non_coinbase_txns();
};

