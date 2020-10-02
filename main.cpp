#include <string>
#include <iostream>
#include <algorithm>
#include <bitset>
#include <fstream>

#include "util.h"
#include "file_handler.h"
#include "parser.h"
#include "tradutor.h"

using namespace std;

string set_output_filename(string input_filename, string extension)
{
    vector<string> temp;
    temp = split(input_filename, ".");
    return(temp[0] + "." + extension);
}

int main(int argc, char **argv) {
    
    if (argc < 2) return 0;

    Parser parser;
    Tradutor tradutor;
    string input_file = argv[1];
    string output_file = set_output_filename(input_file, "hack");
    string temp_file = set_output_filename(input_file, "tmp");
    FileHandler file_handler(input_file, temp_file);
    string line;
    string instruction;
    string value;
    
    int current_line = 0;
    int variable_address = 16;

    // load symbols
    while (file_handler.read_line(line))
    {
        instruction = line;
        line.clear();
        if (!parser.ignore_line(instruction))
        {
            if (parser.is_label(instruction))
            {
                value = parser.get_label(instruction);
                if (!tradutor.is_on_symbol_table(value))
                    tradutor.add_symbol(value, current_line);
            }
            else if (parser.is_variable(instruction))
            {
                value = parser.get_variable(instruction);
                if(!tradutor.is_on_symbol_table(value))
                {
                    tradutor.add_symbol(value, variable_address);
                    variable_address++;
                }
            } 
            current_line++;
        }
    }

    line.clear();
    value.clear();
    instruction.clear();
    file_handler.reset();

    // transfers symbols from symbol table to temp file
    while (file_handler.read_line(line))
    {
        instruction = line;
        if (parser.is_variable(instruction))
        {
            value = parser.get_variable(instruction);
            value = tradutor.get_symbol_value(value);
            instruction = value;
        }
        if (!(parser.is_label(instruction)))
            file_handler.write_line(instruction);
    }

    line.clear();
    value.clear();
    instruction.clear();
    file_handler.close_stream();
    file_handler.set_input_file(temp_file);
    file_handler.set_output_file(output_file);
    
    // now assemble
    while (file_handler.read_line(line))
    {
        instruction = line;
        
        line.clear();
        cout << line << endl;
        if (!parser.ignore_line(instruction))
        {
            if(parser.instruction_type(instruction))
            {
                parser.split_c(instruction);
                tradutor.concatenate(parser.get_dest(), parser.get_comp(), parser.get_jump());
                file_handler.write_line(tradutor.get_binary_instruction());
            }
            else
            {
                value = parser.get_value(instruction);
                value = tradutor.bitify(value);
                file_handler.write_line(value);
            }
        }
    }
    file_handler.close_stream();
}

