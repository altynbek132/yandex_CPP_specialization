#pragma once

#include <deque>
#include <istream>
#include <list>
#include <map>
#include <ostream>
#include <set>
#include <string>
#include <vector>
using namespace std;
/*
document_input содержит не более 50000 документов
D
каждый документ содержит не более 1000 слов
Wid
общее число различных слов во всех документах не превосходит 15000
Uw
максимальная длина одного слова — 100 символов, слова состоят из строчных латинских букв и разделены одним или
несколькими пробелами
L
query_input содержит не более 500 000 запросов, каждый запрос содержит от 1 до 10 слов.
Q, Wiq
 * */
class InvertedIndex {
   public:
    struct Entry {
        size_t docid, hitcount;
        friend ostream& operator<<(ostream& os, const Entry& entry);
    };

    InvertedIndex() = default;
    InvertedIndex(InvertedIndex&&) = default;
    InvertedIndex& operator=(InvertedIndex&&) = default;
    explicit InvertedIndex(istream& document_input);

    const vector<Entry>& Lookup(string_view word) const;

    const string& GetDocument(size_t id) const { return docs[id]; }
    const deque<string>& GetDocuments() const { return docs; }

#ifdef MASLO
    friend ostream& operator<<(ostream& os, const InvertedIndex& index);
#endif  // MASLO

   private:
    map<string_view, vector<Entry>> word_to_stat;
    deque<string> docs;
};

class SearchServer {
   public:
    SearchServer() = default;
    SearchServer(SearchServer&&) = default;
    SearchServer& operator=(SearchServer&&) = default;

    explicit SearchServer(istream& document_input);
    void UpdateDocumentBase(istream& document_input);
    void AddQueriesStream(istream& query_input, ostream& search_results_output);

#ifdef MASLO
    friend ostream& operator<<(ostream& os, const SearchServer& server);
#endif  // MASLO

   private:
    InvertedIndex index;
};
