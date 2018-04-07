#pragma once
#include <vector>
#include "block.h"

class Blockchain
{
	private:
		vector<Block> blockchain;

	public:
		Blockchain();
		vector<Block> get_entire_blockchain();
		void add_block_to_chain(Block block);
		bool is_block_valid(Block block);
		Block get_latest_block();
		std::string get_blockchain_string();
		Block gen_genesis_block();
		void print_entire_blockchain();
};
