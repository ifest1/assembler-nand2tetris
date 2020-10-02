#include <iostream>
#include <string>
#include <bitset>
#include "tradutor.h"

using namespace std;

Tradutor::Tradutor()
{
    reset();
    init_jump_bits_map();
    init_comp_bits_map();
    init_dest_bits_map();
    init_symbol_table();
    init_remaining_predef_symbols();
}

void Tradutor::init_jump_bits_map()
{
    jump_bits = {
        {"", "000"},
        {"JGT", "001"},
        {"JEQ", "010"},
        {"JGE", "011"},
        {"JLT", "100"},
        {"JNE", "101"},
        {"JLE", "110"},
        {"JMP", "111"}
    };
}

void Tradutor::init_dest_bits_map()
{
    dest_bits = {
    {"", "000"},
    {"M", "001"},
    {"D", "010"},
    {"A", "100"},
    {"MD", "011"},
    {"AM", "101"},
    {"AD", "110"},
    {"AMD", "111"}
    };
}

void Tradutor::init_comp_bits_map()
{
    comp_bits = {
    {"0", "0101010"},
    {"1", "0111111"},
    {"-1", "0111010"},
    {"D", "0001100"},
    {"A", "0110000"},
    {"!D", "0001101"},
    {"!A", "0110001"},
    {"-D", "0001111"},
    {"-A", "0110011"},
    {"D+1", "0011111"},
    {"A+1", "0110111"},
    {"D-1", "0001110"},
    {"A-1", "0110010"},
    {"D+A", "0000010"},
    {"D-A", "0010011"},
    {"A-D", "0000111"},
    {"D&A", "0000000"},
    {"D|A", "0010101"},
    {"M", "1110000"},
    {"!M", "1110001"},
    {"-M", "1110011"},
    {"M+1", "1110111"},
    {"M-1", "1110010"},
    {"D+M", "1000010"},
    {"D-M", "1010011"},
    {"M-D", "1000111"},
    {"D&M", "1000000"},
    {"D|M", "1010101"}
    };
}

void Tradutor::init_symbol_table()
{
    string r;
    for(int i = 0; i <= 15; i++)
    {
        r = to_string(i);
        symbol_table["R"+r] = i;
    }
}

void Tradutor::init_remaining_predef_symbols()
{
    symbol_table["SCREEN"] = 16384;
    symbol_table["KBD"] = 24576;
    symbol_table["SP"] = 0;
    symbol_table["LCL"] = 1;
    symbol_table["ARG"] = 2;
    symbol_table["THIS"] = 3;
    symbol_table["THAT"] = 4;
}


string Tradutor::bitify(string raw_value) { return get_bit_sequence_from_int(stoi(raw_value)); }

void Tradutor::reset() { binary_instruction.clear(); value.clear(); }

void Tradutor::concatenate(string dest, string comp, string jump) { binary_instruction = "111" + comp_bits[comp] + dest_bits[dest] + jump_bits[jump]; }

bool Tradutor::is_on_symbol_table(string key) { return symbol_table.count(key); }

void Tradutor::add_symbol(string key, int value) { symbol_table[key] = value; }

string Tradutor::get_symbol_value(string key) { return "@"+to_string(symbol_table[key]); }

string Tradutor::get_binary_instruction() { return binary_instruction; }

string Tradutor::get_bit_sequence_from_int(int t) { return bitset<16>(t).to_string(); }

