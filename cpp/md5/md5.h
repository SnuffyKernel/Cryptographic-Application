#pragma once

#include <cstdint>
#include <memory.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define LITTLE_ENDIAN 0
#define BIG_ENDIAN    1


std::vector<uint8_t> MD5(void* original_input, uint64_t size);
std::string md5hash_to_string(std::vector<uint8_t> hash, std::string hex_char, const bool file);