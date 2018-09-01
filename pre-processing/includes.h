#ifndef INCLUDES_H
#define INCLUDES_H

#define INF 9999999999

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <iostream>
#include <fstream>
#include <string>

#include <codecvt>
#include <cassert>
#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <locale>
#include <sstream>

#include <math.h> 
#include <algorithm>
#include <iterator>
#include <vector>
#include <map>

typedef unsigned int uint;
typedef std::string  String;

struct Word{
    String  text;
    double value = 0;
    
    Word(String _txt, bool _key): text(_txt){
        if(_key) value = 1.0;
    }
};

typedef std::vector<Word>      Words;
typedef std::map<String,double> Dict;
typedef std::vector<Dict>     Bucket;

#endif // INCLUDES_H