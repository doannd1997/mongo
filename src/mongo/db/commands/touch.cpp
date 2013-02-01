/** @file touch.cpp
    compaction of deleted space in pdfiles (datafiles)
*/

/**
 *    Copyright (C) 2012 10gen Inc.
 *
 *    This program is free software: you can redistribute it and/or  modify
 *    it under the terms of the GNU Affero General Public License, version 3,
 *    as published by the Free Software Foundation.
 *
 *    This program is distributed in the hope that it will be useful,b
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Affero General Public License for more details.
 *
 *    You should have received a copy of the GNU Affero General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "pch.h"

#include "mongo/db/commands.h"
#include "mongo/db/d_concurrency.h"
#include "mongo/db/curop-inl.h"
#include "mongo/db/index.h"
#include "mongo/db/pdfile.h"
#include "mongo/util/timer.h"

namespace mongo {

    class TouchCmd : public Command {
    public:
        virtual LockType locktype() const { return NONE; }
        virtual bool adminOnly() const { return false; }
        virtual bool slaveOk() const { return true; }
        virtual bool maintenanceMode() const { return true; }
        virtual bool logTheOp() { return false; }
        virtual void help( stringstream& help ) const {
            help << "touch collection\n"
                "Page in all pages of memory containing every extent for the given collection\n"
                "{ touch : <collection_name>, [data : true] , [index : true] }\n"
                " at least one of data or index must be true; default is both are false\n";
        }
        virtual bool requiresAuth() { return true; }
        TouchCmd() : Command("touch") { }

        virtual bool run(const string& db, 
                         BSONObj& cmdObj, 
                         int, 
                         string& errmsg, 
                         BSONObjBuilder& result, 
                         bool fromRepl) {
            ::abort();
            return false;
#if 0
            string coll = cmdObj.firstElement().valuestr();
            if( coll.empty() || db.empty() ) {
                errmsg = "no collection name specified";
                return false;
            }
                        
            string ns = db + '.' + coll;
            if ( ! NamespaceString::normal(ns.c_str()) ) {
                errmsg = "bad namespace name";
                return false;
            }

            bool touch_indexes( cmdObj["index"].trueValue() );
            bool touch_data( cmdObj["data"].trueValue() );

            if ( ! (touch_indexes || touch_data) ) {
                errmsg = "must specify at least one of (data:true, index:true)";
                return false;
            }
            bool ok = touch( ns, errmsg, touch_data, touch_indexes, result );
            return ok;
#endif
        }

#if 0
        bool touch( std::string& ns, 
                    std::string& errmsg, 
                    bool touch_data, 
                    bool touch_indexes, 
                    BSONObjBuilder& result ) {

            if (touch_data) {
                log() << "touching namespace " << ns << endl;
                ::abort();
                touchNs( ns );
                log() << "touching namespace " << ns << " complete" << endl;
            }

            if (touch_indexes) {
                // enumerate indexes
                std::vector< std::string > indexes;
                {
                    Client::ReadContext ctx(ns);
                    NamespaceDetails *nsd = nsdetails(ns.c_str());
                    massert( 16153, "namespace does not exist", nsd );
                    
                    NamespaceDetails::IndexIterator ii = nsd->ii(); 
                    while ( ii.more() ) {
                        IndexDetails& idx = ii.next();
                        indexes.push_back( idx.indexNamespace() );
                    }
                }
                for ( std::vector<std::string>::const_iterator it = indexes.begin(); 
                      it != indexes.end(); 
                      it++ ) {
                    ::abort();
                    touchNs( *it );
                }
            }
            return true;
        }
#endif
        
    };
    static TouchCmd touchCmd;
}
