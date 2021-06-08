#include "search_server.h"
#include "iterator_range.h"
#include "parse.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include "test_runner.h"

void ProcessUpdateDocumentBase(istream& document_input, SearchServer& srv) {
    auto new_index = InvertedIndex(document_input);
    auto index_access = srv.index_sync.GetAccess();
    swap(index_access.ref_to_value, new_index);
}
SearchServer::SearchServer(istream& document_input) {
    ProcessUpdateDocumentBase(document_input, *this);
}
void SearchServer::UpdateDocumentBase(istream& document_input) {
    async_tasks.push_back(async(ProcessUpdateDocumentBase, ref(document_input), ref(*this)));
}

void ProcessAddQueriesStream(istream& query_input, ostream& search_results_output, SearchServer& srv) {
    vector<size_t> docid_count;
    vector<int64_t> docids;

    for (string current_query; getline(query_input, current_query);) {
        const auto words = SplitIntoWordsView(current_query);
        {
            auto index_access = srv.index_sync.GetAccess();
            auto& index = index_access.ref_to_value;
            const auto size = index.GetDocuments().size();
            docid_count.assign(size, 0);
            docids.resize(size);

            for (auto& word : words) {
                for (auto& [docid, hitcount] : index.Lookup(word)) {
                    docid_count[docid] += hitcount;
                }
            }
        }
        iota(docids.begin(), docids.end(), 0);

        partial_sort(docids.begin(), Head(docids, 5).end(), docids.end(),
                     [&docid_count](int64_t lhs, int64_t rhs) {
                         return make_pair(docid_count[lhs], -lhs) > make_pair(docid_count[rhs], -rhs);
                     });

        search_results_output << current_query << ':';
        for (auto docid : Head(docids, 5)) {
            auto hitcount = docid_count[docid];
            if (!hitcount) {
                break;
            }
            search_results_output << " {"
                                  << "docid: " << docid << ", "
                                  << "hitcount: " << hitcount << '}';
        }
        search_results_output << endl;
    }
}

void SearchServer::AddQueriesStream(istream& query_input, ostream& search_results_output) {
    async_tasks.push_back(
        async(ProcessAddQueriesStream, ref(query_input), ref(search_results_output), ref(*this)));
}

// log(Uw) * L
const vector<InvertedIndex::Entry>& InvertedIndex::Lookup(string_view word) const {
    if (auto it = word_to_stat.find(word); it != word_to_stat.end()) {
        return it->second;
    } else {
        static const vector<Entry> emptyStats;
        return emptyStats;
    }
}

InvertedIndex::InvertedIndex(istream& document_input) {
    for (string current_document; getline(document_input, current_document);) {
        // Wid * L + log(Uw) * L
        docs.push_back(move(current_document));  // Wid * L
        const size_t docid = docs.size() - 1;
        for (auto word : SplitIntoWordsView(docs.back())) {
            // log(Uw) * L
            auto& stats = word_to_stat[word];
            if (!stats.empty() && stats.back().docid == docid) {
                stats.back().hitcount++;
            } else {
                stats.push_back({docid, 1});
            }
        }
    }
}

#ifdef MASLO
ostream& operator<<(ostream& os, const SearchServer& server) {
    // os << "index_sync: " << server.index_sync.GetAccess();
    return os;
}
ostream& operator<<(ostream& os, const InvertedIndex& index) {
    os << "word_to_stat: " << index.word_to_stat << " docs: " << index.docs;
    return os;
}
ostream& operator<<(ostream& os, const InvertedIndex::Entry& entry) {
    os << "docid: " << entry.docid << " hitcount: " << entry.hitcount;
    return os;
}
#endif  // MASLO
