#include <iostream>
#include <ctime>
#include <string.h>
#include "block_transaction.h"
#include "picosha2.h"

uint64 Block_Transaction::no_txns_gen_so_far = 0;

Block_Transaction::Block_Transaction(uint64 txn_id, char is_coinbase_txn, vector<char> queries, uint64 client_id, std::string prev_txn_hash)
{
	this->txn_no = no_txns_gen_so_far;
	this->is_coinbase_txn = is_coinbase_txn;
	this->queries = queries;
	this->timestamp = std::time(nullptr);
	this->txn_id = txn_id;
	this->client_id = client_id;
	this->prev_txn_hash = prev_txn_hash;
	this->txn_hash = "";
	this->compute_and_set_txn_hash();
	no_txns_gen_so_far = no_txns_gen_so_far + 1;
}

uint64 Block_Transaction::get_no_txns_gen_so_far()
{
	return no_txns_gen_so_far;
}

uint64 Block_Transaction::get_txn_no()
{
	return txn_no;
}

void Block_Transaction::set_prev_txn_hash(Block_Transaction prev_txn)
{
	this->prev_txn_hash = prev_txn.get_txn_hash();
}

void Block_Transaction::set_prev_txn_hash(std::string prev_hash)
{
	this->prev_txn_hash = prev_hash;
}

std::string Block_Transaction::get_prev_txn_hash()
{
	return this->prev_txn_hash;
}

std::string Block_Transaction::get_txn_hash()
{
	return this->txn_hash;
}

std::string Block_Transaction::get_txn_data_string()
{
	this->compute_and_set_txn_data_string();
	return this->txn_string;
}

void Block_Transaction::compute_and_set_txn_hash()
{
	this->compute_and_set_txn_data_string();
	this->txn_hash = picosha2::hash256_hex_string(this->txn_string);
}

void Block_Transaction::compute_and_set_txn_data_string()
{
	this->txn_string = "{Transaction Number: " + std::to_string(txn_no) +", Transaction ID: " + std::to_string(txn_id) + ", Timestamp: " + std::to_string(timestamp) + ", Previous Transaction Hash: " + prev_txn_hash + ", Transaction Hash: " + txn_hash + ", Queries: "+ get_queries_concatenated_string() + "Client ID: " + std::to_string(client_id) + ", IS_COINBASE_TRANSACTION: " + is_coinbase_txn + "}";
}

char Block_Transaction::get_is_coinbase_txn()
{
	return this->is_coinbase_txn;
}

uint64 Block_Transaction::get_client_id()
{
	return this->client_id;
}

void Block_Transaction::set_client_id(uint64 clientId)
{
	this->client_id = clientId;
}

uint64 Block_Transaction::get_timestamp()
{
	return this->timestamp;
}

void Block_Transaction::set_timestamp(uint64 timestamp)
{
	this->timestamp = timestamp;
}

uint64 Block_Transaction::get_txn_id()
{
	return this->txn_id;
}

void Block_Transaction::set_txn_id(uint64 txnId)
{
	this->txn_id = txnId;
}

std::string Block_Transaction::get_queries_concatenated_string()
{
	std::string result = "";
	for(uint64 i = 0; i < queries.size(); i++)
	{
		result = result + queries[i] + ',';
	}
	return result;
}
