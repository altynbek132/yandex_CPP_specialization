#include "json.h"
#include "utils.h"

using namespace std;

namespace Json {

Document::Document(Node root) : root(move(root)) {}

const Node& Document::GetRoot() const {
    return root;
}

Node LoadNode(string_view& input);

Node LoadArray(string_view& input) {
    vector<Node> result;

    for (char c; c = input[0], !input.empty() && c != ']';) {
        if (c == ',') {
            input.remove_prefix(1);
        }
        result.push_back(LoadNode(input));
    }

    return Node(move(result));
}

Node LoadInt(string_view& input) {
    int result = 0;
    while (isdigit(input[0])) {
        result *= 10;
        result += ReadChar(input) - '0';
    }
    return Node(result);
}

string_view ReadDouble(string_view input) {
    uint8_t dot_count = 0;
    return ReadTokenWhile(input, [&dot_count](const auto ch) {
        if (isdigit(ch)) {
            return true;
        }
        if (ch == '.') {
            return ++dot_count <= 1;
        }
        return false;
    });
}

Node LoadDouble(string_view& input) {
    return Node(ConvertToDouble(ReadDouble(input)));
}

Node LoadString(string_view& input) {
    string line = string(ReadToken(input, "\""));
    return Node(move(line));
}

Node LoadDict(string_view& input) {
    map<string, Node> result;

    for (char c; c = ReadChar(input), !input.empty() && c != '}';) {
        if (c == ',') {
            c = ReadChar(input);
        }

        string key = LoadString(input).AsString();
        c = ReadChar(input);
        result.emplace(move(key), LoadNode(input));
    }

    return Node(move(result));
}

Node LoadNode(string_view& input) {
    const char c = input[0];
    auto first_char_removed_input = input.substr(1);

    if (c == '[') {
        return LoadArray(input = first_char_removed_input);
    } else if (c == '{') {
        return LoadDict(input = first_char_removed_input);
    } else if (c == '"') {
        return LoadString(input = first_char_removed_input);
    } else {
        const auto [lhs, rhs] = SplitTwo(input, [](const auto ch) { return isdigit(ch); });
        if (!rhs.empty() && rhs[0] == '.') {
            return LoadDouble(input);
        }
        return LoadInt(input);
    }
}

Document Load(istream& input) {
    string input_str(std::istreambuf_iterator<char>(input), {});
    string_view input_sv = input_str;
    return Document{LoadNode(input_sv)};
}

}  // namespace Json
