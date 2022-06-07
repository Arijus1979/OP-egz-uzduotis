#pragma once

#include "main.h"

void SkipBOM(std::ifstream& in);
void read_file(stringstream &buffer);
void analyse(multiset <pair<string, int>> &data, stringstream& buffer);
void print_words(multiset <pair<string, int>> &data);
void search_url(stringstream& buffer);