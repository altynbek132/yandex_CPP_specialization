#include "json.h"
#include "output_reload.h"
#include "utils.h"

using namespace std;

namespace Json {

Document::Document(Node root) : root(move(root)) {}

const Node& Document::GetRoot() const {
    return root;
}

ostream& operator<<(ostream& os, const Document& document) {
    os << document.root;
    return os;
}

Node LoadNode(string_view& input);

Node LoadArray(string_view& input) {
    TrimLeft(input);
    vector<Node> result;

    for (char c; c = input[0], !input.empty() && c != ']'; TrimLeft(input)) {
        if (c == ',') {
            input.remove_prefix(1);
        }
        result.push_back(LoadNode(input));
    }
    if (!input.empty() && input.front() == ']') {
        input.remove_prefix(1);
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

string_view ReadDouble(string_view& input) {
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

Node LoadBool(string_view& input) {
    auto str = ReadTokenWhile(input, [](const auto ch) { return isalpha(ch); });
    if (str == "true") {
        return Node(true);
    } else if (str == "false") {
        return Node(false);
    }
    std::stringstream error;
    error << "expected bool, got :" << str;
    throw std::invalid_argument(error.str());
}

Node LoadDict(string_view& input) {
    TrimLeft(input);
    map<string, Node> result;

    for (char c; c = ReadChar(input), !input.empty() && c != '}'; TrimLeft(input)) {
        if (c == ',') {
            TrimLeft(input);
            // '"' symbol
            c = ReadChar(input);
        }

        string key = LoadString(input).AsString();
        TrimLeft(input);
        // ':' symbol
        c = ReadChar(input);
        result.emplace(move(key), LoadNode(input));
    }

    return Node(move(result));
}

Node LoadNode(string_view& input) {
    TrimLeft(input);
    const char c = input[0];
    auto first_char_removed_input = input.substr(1);

    switch (c) {
        case '[': {
            return LoadArray(input = first_char_removed_input);
        }
        case '{': {
            return LoadDict(input = first_char_removed_input);
        }
        case '"': {
            return LoadString(input = first_char_removed_input);
        }
        case 't':
        case 'f': {
            return LoadBool(input);
        }
        default:
            const auto [lhs, rhs] = SplitTwo(input, [](const auto ch) { return isdigit(ch); });
            if (!rhs.empty() && isdigit(rhs[0])) {
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

std::ostream& operator<<(ostream& os, const Node& node) {
    if (holds_alternative<vector<Node>>(node)) {
        auto& value = get<vector<Node>>(node);
        ::operator<<(os, value);
    } else if (holds_alternative<map<string, Node>>(node)) {
        auto& value = get<map<string, Node>>(node);
        ::operator<<(os, value);
    } else if (holds_alternative<int>(node)) {
        auto& value = get<int>(node);
        os << value;
    } else if (holds_alternative<double>(node)) {
        auto& value = get<double>(node);
        os << value;
    } else if (holds_alternative<string>(node)) {
        auto& value = get<string>(node);
        os << "\"" << value << "\"";
    } else if (holds_alternative<bool>(node)) {
        auto& value = get<bool>(node);
        os << std::boolalpha << value;
    }
    return os;
}
}  // namespace Json
