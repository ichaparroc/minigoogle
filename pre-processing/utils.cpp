#include "utils.h"

int getdir ( String dir, std::vector<std::string> &files ){
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        std::cout << "Error(" << errno << ") opening " << dir << std::endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(String(dirp->d_name));
    }
    closedir(dp);
    return 0;
}


bool isKeyOfMap(String &key, Dict &_map){
    if (_map.count(key)>0)
      return true;
    else 
      return false;
}


uint findWord(Words &_words, String *_word){
    String *t;
    uint i;
    for (i=0; i<_words.size(); ++i) {
        t = &_words[i].text;
        if( t->size() == _word->size() ){
            if( t->at(0) == _word->at(0) ){
            if( t[0] == _word[0] ){
                return i;
            }
            }
        }
     }
     return _words.size();
}


void removeCharsFromString( String &str, String &charsToRemove ){
    for ( unsigned int i = 0; i < charsToRemove.size(); ++i ) {
      str.erase( remove(str.begin(), str.end(), charsToRemove[i]), str.end() );
   }
}


void cureString(String &line){
    char _char;
    uint     c;

    for ( c=0; c < line.size(); ++c){
        _char = line.at(c);

        // Is Special Characters?
        if( (47<_char && _char< 58) ||
            (64<_char && _char< 91) ||
            (96<_char && _char<123)  ){
            // Es bueno
        }else{
            // a: char([131-134,142,143,160])
            if( _char=='\340' || _char=='\341' || _char=='\342'  || _char=='\343'  || _char=='\344' || _char=='\345' || _char=='\346')
                {
                    line = line.substr(0,c)+"á"+line.substr(c+1);
                }

            else if( _char=='\300' || _char=='\301' || _char=='\302'  || _char=='\303'  || _char=='\304' || _char=='\305' || _char=='\306' )
            //(130<_char && _char<135) || _char==142 || _char==143 || _char==160  || _char==181 )
                {
                    line = line.substr(0,c)+"Á"+line.substr(c+1);
                }
            
            // e: char([136-138,130,144])
            else if( _char=='\350' || _char=='\351' || _char=='\352' || _char=='\353')
                {
                    line = line.substr(0,c)+"\303\251"+line.substr(c+1);
                }
            else if(_char=='\310' || _char=='\311' || _char=='\312' || _char=='\313' )
            //(135<_char && _char<139) || _char==130 || _char==144 || _char==-23 )
                {
                    line = line.substr(0,c)+"É"+line.substr(c+1);
                }
            // i: char([139-141,161])
            else if( _char=='\354' || _char=='\355' || _char=='\356' || _char=='\357')
                {
                    line = line.substr(0,c)+"í"+line.substr(c+1);
                }
            else if( _char=='\314' || _char=='\315' || _char=='\316' || _char=='\317')
            //(138<_char && _char<142) || _char==161 || _char==214 )
                {
                    line = line.substr(0,c)+"Í"+line.substr(c+1);
                }

            // o: char([147-149,153,162])
            else if( _char=='\362' || _char=='\363' || _char=='\364' || _char=='\365' || _char=='\366' )
                {
                    line = line.substr(0,c)+"ó"+line.substr(c+1);
                }
            else if( _char=='\322' || _char=='\323' || _char=='\324' || _char=='\325' || _char=='\326')
            // (146<_char && _char<150) || _char==153 || _char==162  || _char==224 )
                {
                    line = line.substr(0,c)+"Ó"+line.substr(c+1);
                }

            // u: char([129,150,151,154,163])
            else if( _char=='\371' || _char=='\372' || _char=='\373' || _char=='\374' )
                {
                    line = line.substr(0,c)+"ú"+line.substr(c+1);
                }
            else if( _char=='\331' || _char=='\332' || _char=='\333' || _char=='\334')
            //_char==129 || _char==150 || _char==151 || _char==154 || _char==163 || _char==23)
                {
                    line = line.substr(0,c)+"Ú"+line.substr(c+1);
                }

            // n: char([164,165]) 
            else if( _char=='\361' )
                {
                    line = line.substr(0,c)+"ñ"+line.substr(c+1);
                }
            else if( _char=='\321' )
            //_char==164 || _char==165)
                {
                    line = line.substr(0,c)+"Ñ"+line.substr(c+1);
                }

            // Bad :c
            else{
                
            }
        }
    }
}