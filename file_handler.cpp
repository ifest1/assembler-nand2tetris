#include "file_handler.h"
#include <fstream>
#include <iostream>

using namespace std;

//initialization
FileHandler::FileHandler(string input_filename, string output_filename)
{
    set_input_file(input_filename);
    set_output_file(output_filename);
}

// file init
void FileHandler::set_input_file(string filename)
{
    input_file.open(filename);
}

void FileHandler::set_output_file(string filename)
{
    output_file.open(filename);
}

// operations
bool FileHandler::read_line(string &line)
{
    return (input_file.is_open() && getline(input_file, line));
}

void FileHandler::write_line(string line)
{
    output_file << line << endl;
}


void FileHandler::close_stream()
{
    input_file.close();
    output_file.close();
}