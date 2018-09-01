#ifndef UTILS_H
#define UTILS_H

#include "includes.h"

int getdir (String dir, std::vector<std::string> &files);
bool isKeyOfMap(String &key, Dict &_map);
uint findWord(Words &_words, String *_word);
void removeCharsFromString( String &str, String &charsToRemove );
void cureString(String &line);

#endif // UTILS_H