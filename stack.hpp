#include <string.h>

struct Stack {
  size_t size;
  size_t capacity;
  char** stack;

  Stack() : size(0), capacity(10), stack(new char*[capacity]) {}

  Stack(const Stack&) = delete;
  Stack& operator=(const Stack&) = delete;

  ~Stack() {
    for (size_t i = 0; i < size; ++i) {
      delete[] stack[i];
    }
    delete[] stack;
  }
};

size_t Size(const Stack* s) {
  if (s == nullptr) {
    return 0;
  }
  return s->size;
}

void Push(Stack* s, const char* str) {
  if (s == nullptr || str == nullptr) {
    return;
  }

  size_t len = strlen(str);

  if (s->size == s->capacity) {
    s->capacity *= 2;
    char** tmp = new char*[s->capacity];

    for (size_t i = 0; i < s->size; ++i) {
      tmp[i] = s->stack[i];
    }

    delete[] s->stack;
    s->stack = tmp;
  }

  s->stack[s->size] = new char[len + 1];
  for (size_t i = 0; i < len; ++i) {
    s->stack[s->size][i] = str[i];
  }
  s->stack[s->size][len] = '\0';

  s->size += 1;
}

void Pop(Stack* s) {
  if (s != nullptr && s->size > 0) {
    delete[] s->stack[s->size - 1];
    s->size -= 1;
  }
}

const char* Top(const Stack* s) {
  if (s != nullptr && s->size > 0) {
    return s->stack[s->size - 1];
  }
  return nullptr;
}

void Clear(Stack* s) {
  if (s == nullptr) {
    return;
  }

  for (size_t i = 0; i < s->size; ++i) {
    delete[] s->stack[i];
  }
  s->size = 0;

  delete[] s->stack;
  s->capacity = 10;
  s->stack = new char*[s->capacity];
}