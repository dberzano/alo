#ifndef ALO_JSONMAP_READER_DDL2JSON_H
#define ALO_JSONMAP_READER_DDL2JSON_H

#include "AliMpDDL.h"
#include "AliDAQ.h"
#include <vector>
#include "json.h"

template<typename WRITER>
void all_ddl2json(std::string topkey, const std::vector<AliMpDDL*>& ddls,
        const std::vector<std::vector<int> >& desperddl, 
        WRITER& w) 
{
    w.StartObject();
    w.Key(topkey.c_str());
    w.StartArray();
    int i = 0;
    for ( auto& ddl: ddls) {
        w.StartObject();
        w.Key("id");
        w.Int(AliDAQ::DdlID("MUONTRK",ddl->GetId()));
        WriteArray(w,"des",desperddl[i++]);
        w.EndObject();
    }
    w.EndArray();
    w.EndObject();
}

#endif
