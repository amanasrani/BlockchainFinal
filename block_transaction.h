#pragma once
#include <iostream>
#include <ctime>
#include <string.h>
#include <vector>

using namespace std;

typedef unsigned long long int uint64;

class Block_Transaction
{
	private:
		static uint64 no_txns_gen_so_far;
		uint64 txn_no;
		uint64 txn_id;
		uint64 timestamp;
		std::string txn_hash;
		std::string prev_txn_hash;
		std::string txn_string;
		vector<char> queries; //holds type of each request (R/W/S) (C - Coinbase Txn)
        	uint64 client_id;
		char is_coinbase_txn; //'Y' -> Yes, else 'N'
	public:
		Block_Transaction(uint64 txn_id,char is_coinbase_txn,vector<char> queries,uint64 client_id,std::string prev_txn_hash);
		static uint64 get_no_txns_gen_so_far();
		uint64 get_txn_no();
		uint64 get_txn_id();
		void set_prev_txn_hash(Block_Transaction prev_txn);
		std::string get_prev_txn_hash();
		void compute_and_set_txn_hash();
		void compute_and_set_txn_data_string();
		std::string get_txn_data_string();
		std::string get_txn_hash();
		char get_is_coinbase_txn();
		uint64 get_client_id();
		void set_client_id(uint64 clientId);
		uint64 get_number_queries_in_txn();
		void set_number_queries_in_txn(uint64 numQueries);
		uint64 get_timestamp();
		void set_timestamp(uint64 timestamp);
		void set_txn_id(uint64 txnId);
		std::string get_queries_concatenated_string();
		void set_prev_txn_hash(std::string prev_hash);
};