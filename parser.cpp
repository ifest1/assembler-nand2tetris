#include <iostream>
#include <string>
#include <algorithm>
#include "parser.h"
#include "util.h"

using namespace std;

Parser::Parser()
{
}

bool Parser::ignore_line(string line)
{
    return (!line.rfind("//", 0) || !line.rfind("\r", 0));
}

bool Parser::instruction_type(string instruction)
{
    if (instruction.find('@') != string::npos)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void Parser::split_c(string instruction)
{
    reset();

    vector<string> values;
    values = split(instruction, "//");
    values = split(values[0], ";");

    if (values.size() > 1)
    {
        jump = values[1];
        values.pop_back();
    }
    else
    {
        jump = "";
    }

    values = split(values[0], "=");

    if (values.size() > 1)
    {
        dest = values[0]; comp = values[1];
    }
    else
    {
        comp = values[0];
    }
    clear_spaces();
}

string Parser::get_a_value(string value)
{
    del_char(value, '@'); 
    del_char(value, ' ');
    return value;
}


void Parser::clear_spaces()
{
    del_char(dest, ' '); 
    del_char(comp, ' '); 
    del_char(jump, ' ');

    dest.erase(remove(dest.begin(), dest.end(), '\r'), dest.end());
    comp.erase(remove(comp.begin(), comp.end(), '\r'), comp.end());
    jump.erase(remove(jump.begin(), jump.end(), '\r'), jump.end());
}

void Parser::reset()
{
    jump.clear(); comp.clear(); dest.clear();
}

string Parser::get_dest() { return dest; }
string Parser::get_comp() { return comp; }
string Parser::get_jump() { return jump; }
