#include "miner_main.h"
#include <utility>

std::unordered_map<uint64, Block_Transaction> Miner_Main::confirmed_txns_map;
vector<Block_Transaction> Miner_Main::unconfirmed_txns;
Blockchain Miner_Main::blockchain = Blockchain();
Block_Creator Miner_Main::block_creator = Block_Creator(9,9999999);

Block Miner_Main::mine_valid_block()
{
	//Get Previous Txn Hash for Coinbase Transaction which will be generated
	std::string prev_txn_hash = "0000000000000000000000000000000000000000000000000000000000000000";
	uint64 prev_txn_no = Block_Transaction::get_no_txns_gen_so_far() - 1;

	std::unordered_map<uint64,Block_Transaction>::iterator it;
	it = Miner_Main::confirmed_txns_map.find(prev_txn_no);

	if (it != confirmed_txns_map.end())
	{
		prev_txn_hash = ((Block_Transaction)it->second).get_txn_hash();
	}
	else if(!unconfirmed_txns.empty())
	{
		for(uint64 i = 0; i < unconfirmed_txns.size(); i++ )
		{
			if(unconfirmed_txns[i].get_txn_no() > prev_txn_no)
			{
				break;
			}
			if(unconfirmed_txns[i].get_txn_no() == prev_txn_no)
			{
				prev_txn_hash = unconfirmed_txns[i].get_txn_hash();
			}
		}
	}
	//End

	Block new_block = block_creator.generate_block(unconfirmed_txns,blockchain.get_latest_block(),confirmed_txns_map,prev_txn_hash);
	proof_of_work(new_block);
	new_block.compute_and_set_block_string();
	return new_block;
}

bool Miner_Main::hex_greater(std::string first, std::string second)
{
    /* Comparisons based on size */
    int firstSize = first.size();
    int secondSize = second.size();
    if(firstSize > secondSize)
        return true;
    else if(firstSize < secondSize)
        return false;

    /* Convert to lower case, for case insentitive Comparisons */
    std::transform(first.begin(), first.end(), first.begin(), ::tolower);
    std::transform(second.begin(), second.end(), second.begin(), ::tolower);

    /* Call the std::string operator>(...) which compare strings lexicographically */
    if(first > second)
        return true;

    /* In other cases first hex string is not greater */
    return false;
}


void Miner_Main::proof_of_work(Block &block)
{
  (block.get_header()).update_timestamp();
  block.compute_and_set_block_header_hash();
  std::string hash_str = block.get_block_header_hash();
  std::string target = (block.get_header()).get_target();
  while(hex_greater(hash_str, target))
  {
    block.increment_nonce();
    block.compute_and_set_block_string();
    hash_str = block.get_block_header_hash();
    cout<< hash_str << endl << (block.get_header()).get_nonce()<< endl;
  }
}

void Miner_Main::add_txns_to_confirmed_txns_map(vector<Block_Transaction> txns)
{

	for(uint64 i = 0; i < txns.size(); i++)
	{
		Block_Transaction txn = txns[i];
		std::pair<uint64, Block_Transaction> obj (txn.get_txn_no(),txn);
		confirmed_txns_map.insert(obj);
	}
}

bool Miner_Main::add_block_to_chain(Block block)
{
	if(blockchain.is_block_valid(block))
	{
		add_txns_to_confirmed_txns_map((vector<Block_Transaction>)block.get_all_txns());
		blockchain.add_block_to_chain(block);
		Block_Header::increment_block_index_so_far();
		return true;
	}
	return false;
}

void Miner_Main::gen_txn_and_add_to_unconfirmed_txns(Block_Transaction txn)
{
	std::string prev_txn_hash = "0000000000000000000000000000000000000000000000000000000000000000";
	uint64 prev_txn_no = Block_Transaction::get_no_txns_gen_so_far() - 2;

	std::unordered_map<uint64,Block_Transaction>::iterator it;
	it = confirmed_txns_map.find(prev_txn_no);

	if (it != confirmed_txns_map.end())
	{
		prev_txn_hash = ((Block_Transaction)it->second).get_txn_hash();
	}
	else if(!unconfirmed_txns.empty())
	{
		for(uint64 i = 0; i < unconfirmed_txns.size(); i++ )
		{
			if(unconfirmed_txns[i].get_txn_no() > prev_txn_no)
			{
				break;
			}
			if(unconfirmed_txns[i].get_txn_no() == prev_txn_no)
			{
				prev_txn_hash = unconfirmed_txns[i].get_txn_hash();
			}
		}
	}

	txn.set_prev_txn_hash(prev_txn_hash);
	txn.compute_and_set_txn_data_string();
	unconfirmed_txns.push_back(txn);
}

void Miner_Main::print_unconfirmed_txns_vector()
{
	std::cout << "UNCONFIRMED TRANSACTIONS:" << endl;
	std::cout << "=======================================================================================" << endl;
	for(uint64 i = 0; i < unconfirmed_txns.size(); i++ )
	{
		std::cout << unconfirmed_txns[i].get_txn_data_string() << endl;
	}
	std::cout << "=======================================================================================" << endl;
}

void Miner_Main::print_confirmed_txns()
{
	std::cout << "CONFIRMED TRANSACTIONS:" << endl;
	std::cout << "=======================================================================================" << endl;

	for(auto it = confirmed_txns_map.begin(); it != confirmed_txns_map.end(); ++it)
	{
		std::cout << "Txn No: " << it->first << ",Transaction: " << ((Block_Transaction)it->second).get_txn_data_string() << endl;
	}
	std::cout << "=======================================================================================" << endl;
}

void Miner_Main::print_entire_blockchain()
{
	blockchain.print_entire_blockchain();
}
