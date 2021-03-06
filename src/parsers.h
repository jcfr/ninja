// Copyright 2011 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef NINJA_PARSERS_H_
#define NINJA_PARSERS_H_

#include <string>
#include <vector>

using namespace std;

struct BindingEnv;

struct Token {
  enum Type {
    NONE,
    UNKNOWN,
    IDENT,
    RULE,
    BUILD,
    SUBNINJA,
    INCLUDE,
    NEWLINE,
    EQUALS,
    COLON,
    PIPE,
    PIPE2,
    INDENT,
    OUTDENT,
    TEOF
  };
  explicit Token(Type type) : type_(type) {}

  void Clear() { type_ = NONE; }
  string AsString() const;

  Type type_;
  const char* pos_;
  const char* end_;
};

struct Tokenizer {
  Tokenizer(bool whitespace_significant)
      : whitespace_significant_(whitespace_significant),
        token_(Token::NONE), line_number_(1),
        last_indent_(0), cur_indent_(-1) {}

  void Start(const char* start, const char* end);
  bool Error(const string& message, string* err);
  // Call Error() with "expected foo, got bar".
  bool ErrorExpected(const string& expected, string* err);

  const Token& token() const { return token_; }

  void SkipWhitespace(bool newline=false);
  bool Newline(string* err);
  bool ExpectToken(Token::Type expected, string* err);
  bool ReadIdent(string* out);
  bool ReadToNewline(string* text, string* err);

  Token::Type PeekToken();
  void ConsumeToken();

  bool whitespace_significant_;

  const char* cur_;
  const char* end_;

  const char* cur_line_;
  Token token_;
  int line_number_;
  int last_indent_, cur_indent_;
};

struct MakefileParser {
  MakefileParser();
  bool Parse(const string& input, string* err);

  Tokenizer tokenizer_;
  string out_;
  vector<string> ins_;
};

struct State;

struct ManifestParser {
  struct FileReader {
    virtual bool ReadFile(const string& path, string* content, string* err) = 0;
  };

  ManifestParser(State* state, FileReader* file_reader);

  bool Load(const string& filename, string* err);
  bool Parse(const string& input, string* err);

  bool ParseRule(string* err);
  // Parse a key=val statement.  If expand is true, evaluate variables
  // within the value immediately.
  bool ParseLet(string* key, string* val, bool expand, string* err);
  bool ParseEdge(string* err);

  // Parse either a 'subninja' or 'include' line.
  bool ParseFileInclude(Token::Type type, string* err);

  State* state_;
  BindingEnv* env_;
  FileReader* file_reader_;
  Tokenizer tokenizer_;
};

#endif  // NINJA_PARSERS_H_
