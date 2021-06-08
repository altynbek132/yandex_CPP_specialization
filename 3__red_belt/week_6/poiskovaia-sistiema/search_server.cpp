#include "search_server.h"
#include "iterator_range.h"
#include "parse.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include "test_runner.h"

SearchServer::SearchServer(istream& document_input) : index(document_input) {}

// D * (Wid * L + log(Uw) * L)
void SearchServer::UpdateDocumentBase(istream& document_input) {
    index = InvertedIndex(document_input);
}

void SearchServer::AddQueriesStream(istream& query_input, ostream& search_results_output) {
    const auto size = index.GetDocuments().size();
    vector<size_t> docid_count(size);
    vector<int64_t> docids(size);

    for (string current_query; getline(query_input, current_query);) {
        const auto words = SplitIntoWordsView(current_query);
        docid_count.assign(size, 0);

        for (auto& word : words) {
            for (auto& [docid, hitcount] : index.Lookup(word)) {
                docid_count[docid] += hitcount;
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

#ifdef MASLO
ostream& operator<<(ostream& os, const SearchServer& server) {
    os << "index: " << server.index;
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
