#ifndef TXT_H
#define TXT_H

#include "includes.h"
#include "utils.h"

class TxT
{
private:
    // Parameters
    Words  _w;  
    uint   _idDoc;
    String _link;

    // Purge
    std::vector<int>   _blacklist;
    void purgeNumbers          ();
    void purgeSpecialCharacters();
    void purgeUppercase        ();
    void purgeBadWords         ();
    void purgeLittleWords      ();

    // Analyze
    uint _size = 0;

public:
    // Constructors
    TxT();
    TxT(uint idDocument, String WebAddress);

    // Basic operations
    void add(String &text, bool istitle = false);
    void setDocumentID(uint &idDocument){ _idDoc = idDocument; }
    void setWebAddress(uint &WebAddress){ _link  = WebAddress; }

    // Purge
    void runPurge();

    // Analize words
    void analyzeWords();

    // Getting
    Words  getWords     (){ return _w;        }
    uint   getDocumentID(){ return _idDoc;    }
    String getWebAddress(){ return _link;     }
    uint   getSize      (){ if(_size == 0) return _w.size(); 
                            else           return   _size  ;}
};

#endif // TXT_H


