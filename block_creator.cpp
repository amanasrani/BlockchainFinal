#include <iostream>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <thread>
#include "block_creator.h"

//TODO: Miner must call compute_and_set_block_string() after finding a successful block and sending it for validation
//to everyone else (i.e. POW code must call it.)

Block_Creator::Block_Creator(int no_of_non_coinbase_txns, uint64 server_id)
{
	this->no_of_non_coinbase_txns = no_of_non_coinbase_txns;
	this->no_txns_per_block = no_of_non_coinbase_txns + 1;
	this->server_id = server_id;
}

Block Block_Creator::generate_block(vector<Block_Transaction> &unconfirmed_txns_vector, Block previous_block, std::unordered_map<uint64, Block_Transaction> &confirmed_txns_map,std::string hash_of_last_txn_prior_to_coinbase)
{
	//Removing Confirmed Txns from the Unconfirmed Txns
	remove_all_confirmed_txns(unconfirmed_txns_vector, confirmed_txns_map);

	//Create a New Block
	Block block = Block('N',previous_block.get_block_header_hash(),previous_block.get_header().get_target());

	//Add a Coinbase Txn
	block.add_txn(gen_coinbase_txn(hash_of_last_txn_prior_to_coinbase));

	//No of Txns in a Block depends on the size of the unconfirmed_txns available
	uint64 txn_count = unconfirmed_txns_vector.size() < no_of_non_coinbase_txns ? unconfirmed_txns_vector.size() : no_of_non_coinbase_txns;

	//Adding Txns to the Block
	for(uint64 i = 0; i < txn_count; i++)
	{
		block.add_txn(unconfirmed_txns_vector[i]);
	}
	return block;
}

void Block_Creator::remove_all_confirmed_txns(vector<Block_Transaction> &unconfirmed_txns_vector, std::unordered_map<uint64, Block_Transaction> &confirmed_txns_map)
{
	//Iterate through the unconfirmed txns and if any of them are confirmed already,
	//remove them from the unconfirmed txns
	for(uint64 i = 0; i < unconfirmed_txns_vector.size(); i++)
	{
		uint64 txn_no = unconfirmed_txns_vector[i].get_txn_no();
		if(confirmed_txns_map.count(txn_no) != 0)
		{
			unconfirmed_txns_vector.erase(next(begin(unconfirmed_txns_vector), i));
		}
	}
}

Block_Transaction Block_Creator::gen_coinbase_txn(std::string hash_of_last_txn_prior_to_coinbase)
{
	vector<char> queries;
	queries.push_back('C');
	
	//TODO: Replace client_id of 9999999 with the ID of the Server Mining the Block which will help add some randomness
	Block_Transaction coinbase_txn = Block_Transaction(9999999,'Y',queries,server_id,hash_of_last_txn_prior_to_coinbase);
	coinbase_txn.compute_and_set_txn_data_string();
	return coinbase_txn;
}

void Block_Creator::set_server_id(uint64 server_id)
{
	this->server_id = server_id;
}

uint64 Block_Creator::get_server_id()
{
	return this->server_id;
}

void Block_Creator::set_no_of_non_coinbase_txns(int no)
{
	this->no_of_non_coinbase_txns = no;
	this->no_txns_per_block = no_of_non_coinbase_txns + 1;
}

int Block_Creator::get_no_of_non_coinbase_txns()
{
	return this->no_of_non_coinbase_txns;
}
