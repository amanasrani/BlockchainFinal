#pragma once
#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include "picosha2.h"
#include "block_transaction.h"
#include "boost/multiprecision/cpp_int.hpp"

typedef unsigned long long int uint64;

class Block_Header
{
	private:
		std::time_t timestamp;
		uint64 block_index;
		std::string previous_block_header_hash;
		boost::multiprecision::uint256_t nonce;
		std::string target;
		std::string block_header_string;
		uint64 nbits;
		static boost::multiprecision::uint256_t has_value_one;
		static uint64 block_index_so_far;
	public:
		Block_Header();
		Block_Header(std::string previous_block_header_hash, std::string target);
		std::time_t get_timestamp();
		void set_timestamp(std::time_t curr_time);
		uint64 get_block_index();
		void set_block_index(uint64 index);
		boost::multiprecision::uint256_t get_nonce();
		void set_nonce(boost::multiprecision::uint256_t value);
		std::string get_previous_block_header_hash();
		void set_previous_block_header_hash(std::string hash);
		std::string get_target();
		void set_target(std::string value);
		void compute_and_set_block_header_string();
		std::string get_block_header_string();
		void increment_nonce();
		void update_timestamp();
		static uint64 get_block_index_so_far();
		static void increment_block_index_so_far();
};

class Block
{
	private:
		Block_Header header;
		char is_genesis_block; //'Y' -> Yes, else 'N'
		uint64 txn_counter; //No of Block_Transactions Present in the Block
		std::vector<Block_Transaction> txns_vector;
		std::string block_string;
		std::string block_header_hash;
		void increment_txn_counter();
	public:
		Block(char is_genesis_block, std::string previous_block_header_hash, std::string target);
		Block_Header get_header();
		void set_header(Block_Header header_obj);
		uint64 get_txn_counter();
		void add_txn(Block_Transaction txn);
		Block_Transaction get_txn(int index);
		std::vector<Block_Transaction> get_all_txns();
		char get_is_genesis_block();
		void compute_and_set_block_string();
		std::string get_block_string();
		void compute_and_set_block_header_hash();
		std::string get_block_header_hash();
		std::string get_txns_concatenated_string();
		void generate_and_set_block_header(std::string previous_block_header_hash, std::string target);
        void increment_nonce();
};



