#include <vector>
#include <assert.h>
#include <iostream>
#include "blockchain.h"

bool Blockchain::is_block_valid(Block block)
{
	return true;
}

Blockchain::Blockchain()
{
	this->blockchain.push_back(Blockchain::gen_genesis_block());
}

void Blockchain::add_block_to_chain(Block block)
{
	this->blockchain.push_back(block);
}


Block Blockchain::gen_genesis_block()
{
	Block genesis_block = Block('Y',"0000000000000000000000000000000000000000000000000000000000000000","0000FFFFFFFF0000000000000000000000000000000000000000000000000000");
	genesis_block.compute_and_set_block_string();
	return genesis_block;
}

Block Blockchain::get_latest_block()
{
	return this->blockchain.back();
}

void Blockchain::print_entire_blockchain()
{
	cout << "======================================================================== Blockchain ======================================================================== " <<endl;
	for(uint64 i = 0; i < blockchain.size(); i++)
	{
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Block No " << i << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << endl;
		cout << ((Block)blockchain[i]).get_block_string();
		cout << "************************************************************************ End of Block ************************************************************************ " << endl;
	}
	cout << "===================================================================== End of Blockchain ===================================================================== " <<endl;
}