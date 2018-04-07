#pragma once

#include <iostream>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <thread>
#include <vector>
#include <unordered_map>
#include "picosha2.h"
#include "block_creator.h"
#include "blockchain.h"

class Miner_Main
{
	private:
		static bool hex_greater(std::string first, std::string second);
		static void proof_of_work(Block &block);
	public:
		static std::unordered_map<uint64, Block_Transaction> confirmed_txns_map;
		static vector<Block_Transaction> unconfirmed_txns;
		static Blockchain blockchain;
		static Block_Creator block_creator;
		static Block mine_valid_block();
		static void add_txns_to_confirmed_txns_map(vector<Block_Transaction> txns);
		static bool add_block_to_chain(Block block);
		static void gen_txn_and_add_to_unconfirmed_txns(Block_Transaction txn);
		static void print_unconfirmed_txns_vector();
		static void print_confirmed_txns();
		static void print_entire_blockchain();
};
