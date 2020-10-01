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

string set_output_filename(string input_filename)
{
    vector<string> temp;
    temp = split(input_filename, ".");
    return(temp[0] + ".hack");
}

int main(int argc, char **argv) {
    
    if (argc < 2) return 0;
    Parser parser;
    Tradutor tradutor;
    
    string input_file = argv[1];
    string output_file = set_output_filename(input_file);
    
    FileHandler file_handler(input_file, output_file);

    string line;
    string instruction;

    while (file_handler.read_line(line))
    {

        instruction = line;
        line.clear();
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
                tradutor.set_a_value(parser.get_a_value(instruction));
                file_handler.write_line(tradutor.get_a_value());
            }
        }
        else
        {
            cout << "Blank" << endl;
        }
        
    }
    file_handler.close_stream();
}

