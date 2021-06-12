#include "ini.h"

namespace Ini {

pair<string_view, string_view> Split(string_view line, char by) {
    size_t pos = line.find(by);
    string_view left = line.substr(0, pos);

    if (pos < line.size() && pos + 1 < line.size()) {
        return {left, line.substr(pos + 1)};
    } else {
        return {left, string_view()};
    }
}
Section& Document::AddSection(string name) {
    return sections[name];
}
const Section& Document::GetSection(const string& name) const {
    return sections.at(name);
}
size_t Document::SectionCount() const {
    return sections.size();
}
Document Load(istream& input) {
    Document doc;

    string line;
    Section* last_section_p;
    while (getline(input, line)) {
        if (line.empty()) {
            continue;
        }
        if (line.front() == '[') {
            string_view sv = line;
            sv.remove_prefix(1);
            sv.remove_suffix(1);
            last_section_p = &doc.AddSection(string(sv));
        } else {
            auto [key, value] = Split(line, '=');
            auto& last_section = *last_section_p;
            last_section[string(key)] = value;
        }
    }

    return doc;
}
}  // namespace Ini
