#include <iostream>
#include <ctime>
#include <string.h>
#include "block.h"

using namespace std;

//TODO: Override '<<' operator for each class so that cout prints the class members

uint64 Block_Header::block_index_so_far = 1;
boost::multiprecision::uint256_t Block_Header::has_value_one = 1;

//Function Definitions for Block_Header
Block_Header::Block_Header()
{
}

Block_Header::Block_Header(std::string previous_block_header_hash, std::string target)
{
	this->timestamp = std::time(nullptr);
	this->block_index = this->block_index_so_far;
	this->previous_block_header_hash = previous_block_header_hash;
	this->nonce = 0;
	this->target = target;
	this->nbits = 0;
}

std::time_t Block_Header::get_timestamp()
{
	return this->timestamp;
}

void Block_Header::set_timestamp(std::time_t curr_time)
{
	this->timestamp = curr_time;
}

void Block_Header::update_timestamp()
{
	this->timestamp = std::time(nullptr);
}

void Block_Header::increment_nonce()
{

	boost::multiprecision::add(this->nonce, this->nonce, has_value_one);
}

uint64 Block_Header::get_block_index()
{
	return this->block_index;
}

void Block_Header::set_block_index(uint64 index)
{
	this->block_index = index;
}

boost::multiprecision::uint256_t Block_Header::get_nonce()
{
	return this->nonce;
}

void Block_Header::set_nonce(boost::multiprecision::uint256_t value)
{
	this->nonce = value;
}

std::string Block_Header::get_previous_block_header_hash()
{
	return this->previous_block_header_hash;
}

void Block_Header::set_previous_block_header_hash(std::string hash)
{
	this->previous_block_header_hash = hash;
}

std::string Block_Header::get_target()
{
	return this->target;
}

void Block_Header::set_target(std::string value)
{
	this->target = value;
}

void Block_Header::compute_and_set_block_header_string()
{
	this->block_header_string = "{Timestamp: " + std::to_string(this->timestamp) + ", Block Index: " +  std::to_string(this->block_index) + ", Previous Block Header Hash: " + this->previous_block_header_hash + ", Nonce: " + this->nonce.template convert_to<std::string>() + ", Target: " + this->target + "}";
}

std::string Block_Header::get_block_header_string()
{
	return this->block_header_string;
}

uint64 Block_Header::get_block_index_so_far()
{
	return block_index_so_far;
}

void Block_Header::increment_block_index_so_far()
{
	block_index_so_far = block_index_so_far + 1;
}


//Function Definitions for Block
void Block::generate_and_set_block_header(std::string previous_block_header_hash, std::string target)
{
	this->header = Block_Header(previous_block_header_hash, target);
}

Block::Block(char is_genesis_block, std::string previous_block_header_hash, std::string target)
{
	generate_and_set_block_header(previous_block_header_hash, target);
	this->txn_counter = 0;
	this->is_genesis_block = is_genesis_block;
	this->block_header_hash = "";
	this->block_string = "";
}

char Block::get_is_genesis_block()
{
	return this->is_genesis_block;
}

Block_Header Block::get_header()
{
	return this->header;
}

void Block::set_header(Block_Header header_obj)
{
	this->header = header_obj;
}

void Block::increment_txn_counter()
{
	this->txn_counter = this->txn_counter + 1;
}

uint64 Block::get_txn_counter()
{
	return this->txn_counter;
}

void Block::add_txn(Block_Transaction txn)
{
	this->txns_vector.push_back(txn);
	this->increment_txn_counter();
}

Block_Transaction Block::get_txn(int index)
{
	return this->txns_vector[index];
}

vector<Block_Transaction> Block::get_all_txns()
{
	return this->txns_vector;
}

void Block::compute_and_set_block_string()
{
	this->header.compute_and_set_block_header_string();
	this->compute_and_set_block_header_hash();
	this->block_string = "{Transaction Count: " + std::to_string(this->txn_counter) + ", IS_GENESIS_BLOCK: " +  this->is_genesis_block + ", Block Header: " + this->header.get_block_header_string() + ", Block Header Hash: " + this->block_header_hash + ", Transactions: " +  get_txns_concatenated_string() + "}";
}

std::string Block::get_block_string()
{
	return this->block_string;
}

void Block::compute_and_set_block_header_hash()
{
	this->header.compute_and_set_block_header_string();
	block_header_hash = picosha2::hash256_hex_string(this->header.get_block_header_string());
}

std::string Block::get_block_header_hash()
{
	return this->block_header_hash;
}

std::string Block::get_txns_concatenated_string()
{
	std::string result;
	for(uint64 i = 0; i < this->txns_vector.size(); i++)
	{
		this->txns_vector[i].compute_and_set_txn_data_string();
		result = result + this->txns_vector[i].get_txn_data_string();
	}
	return result;
}

void Block::increment_nonce()
{
    this->header.increment_nonce();
}

