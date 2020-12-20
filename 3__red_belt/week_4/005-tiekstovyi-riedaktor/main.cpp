#include <bits/stdc++.h>
#include <profile.h>

using namespace std;

// 2^7 = 128
// 2^15 = 3e4
// 2^31 = 2e9
// 2^63 = 9e18

#ifdef MASLO

#include "tests.h"

void txt() {
    freopen("input.txt", "r", stdin);
    return;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("output.txt", "w", stdout);
}

struct Prerun {
  Prerun() {
      txt();
      TestAll();
  }
};

Prerun maslo;
#endif
// ==========================================
#include <string>
#include "test_runner.h"

class Editor {
 public:
  Editor();
  void Left();   // сдвинуть курсор влево
  void Right();  // сдвинуть курсор вправо
  void Insert(char token);   // вставить символ token
  void Copy(size_t tokens);  // cкопировать
  // не более tokens символов,
  // начиная с текущей позиции курсора
  void Cut(size_t tokens);  // вырезать не более tokens символов,
  // начиная с текущей позиции курсора
  void Paste();  // вставить содержимое буфера
  // в текущую позицию курсора
  string GetText() const;  // получить текущее содержимое
  // текстового редактора
 private:
  list<char> text_{};
  list<char> buffer_{};
  list<char>::iterator pos_;
};

Editor::Editor() : pos_(text_.end()) {}

void Editor::Left() {
    if (pos_ == text_.begin()) { return; }
    --pos_;
}

void Editor::Right() {
    if (pos_ == text_.end()) { return; }
    ++pos_;
}

void Editor::Insert(char token) {
    text_.insert(pos_, token);
}

void Editor::Copy(size_t tokens) {
    auto end = pos_;
    for (std::size_t i = 0; i < tokens && end != text_.end(); ++i) {
        end++;
    }
    buffer_.assign(pos_, end);
}

void Editor::Cut(size_t tokens) {
    Copy(tokens);
    auto size = buffer_.size();
    pos_ = text_.erase(pos_, next(pos_, size));
}

void Editor::Paste() {
    text_.insert(pos_, buffer_.begin(), buffer_.end());
}

string Editor::GetText() const {
    return std::string(text_.begin(), text_.end());
}



void TypeText(Editor &editor, const string &text) {
    for (char c : text) {
        editor.Insert(c);
    }
}

void TestEditing() {
    {
        Editor editor;
        
        const size_t text_len = 12;
        const size_t first_part_len = 7;
        TypeText(editor, "hello, world");
        for (size_t i = 0; i < text_len; ++i) {
            editor.Left();
        }
        editor.Cut(first_part_len);
        for (size_t i = 0; i < text_len - first_part_len; ++i) {
            editor.Right();
        }
        TypeText(editor, ", ");
        editor.Paste();
        editor.Left();
        editor.Left();
        editor.Cut(3);
        
        ASSERT_EQUAL(editor.GetText(), "world, hello");
    }
    {
        Editor editor;
        
        TypeText(editor, "misprnit");
        editor.Left();
        editor.Left();
        editor.Left();
        editor.Cut(1);
        editor.Right();
        editor.Paste();
        
        ASSERT_EQUAL(editor.GetText(), "misprint");
    }
}

void TestReverse() {
    Editor editor;
    
    const string text = "esreveR";
    for (char c : text) {
        editor.Insert(c);
        editor.Left();
    }
    
    ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
    Editor editor;
    ASSERT_EQUAL(editor.GetText(), "");
    
    editor.Left();
    editor.Left();
    editor.Right();
    editor.Right();
    editor.Copy(0);
    editor.Cut(0);
    editor.Paste();
    
    ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
    Editor editor;
    
    editor.Paste();
    TypeText(editor, "example");
    editor.Left();
    editor.Left();
    editor.Paste();
    editor.Right();
    editor.Paste();
    editor.Copy(0);
    editor.Paste();
    editor.Left();
    editor.Cut(0);
    editor.Paste();
    
    ASSERT_EQUAL(editor.GetText(), "example");
}

int main() {
    {
        LOG_DURATION("time taken:");
        TestRunner tr;
        RUN_TEST(tr, TestEditing);
        RUN_TEST(tr, TestReverse);
        RUN_TEST(tr, TestNoText);
        RUN_TEST(tr, TestEmptyBuffer);
    }
    return 0;
}

// ==========================================
