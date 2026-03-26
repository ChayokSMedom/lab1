#include <iostream>
#include <cstring>
#include <cstddef>

class String {
 public:
  /// Destructor
  ~String();

  /// Default constructor
  String();

  /// Copy constructor
  /// <param name="rhs">Object to copy</param>
  String(const String& rhs);

  /// User-defined constructor
  /// <param name="data">Data to be placed in the created object</param>
  String(const char* data);

  /// Assignment operator
  /// <param name="rhs">Object to copy</param>
  /// <returns>Returns reference to self</returns>
  String& operator=(const String& rhs);

  /// Operator +=
  /// <param name="rhs">Object after the '+=' sign</param>
  /// <returns>Returns reference to self</returns>
  String& operator+=(const String& rhs);

  /// Operator *=
  /// <returns>Returns reference to self</returns>
  String& operator*=(unsigned int m);

  /// Operator ==
  /// <param name="rhs">Object after the '==' sign</param>
  /// <returns>Returns equality of two strings</returns>
  bool operator==(const String& rhs) const;

  /// Operator &lt;
  /// <param name="rhs">Object after the "&lt;" sign</param>
  /// <returns>Returns comparison result of two strings</returns>
  bool operator<(const String& rhs) const;

  /// Substring search function
  /// <param name="substr">Substring to find</param>
  /// <returns>Returns position of substr. If substring not found, returns -1</returns>
  size_t Find(const String& substr) const;

  /// Character replacement function, replaces all oldSymbol with newSymbol
  /// <param name="oldSymbol">Symbol to replace</param>
  /// <param name="newSymbol">Symbol to replace with</param>
  void Replace(char oldSymbol, char newSymbol);

  /// Returns string length
  /// <returns>Returns string length</returns>
  size_t Size() const;

  /// Checks if string is empty
  bool Empty() const;

  /// Operator []
  /// <example>
  /// <code>
  /// String str = "some string";
  /// char symbol = str[2]; // symbol == 'm'
  /// </code>
  /// </example>
  /// <param name="index"> Character index </param>
  /// <returns> Character value at index</returns>
  char operator[](size_t index) const;

  /// Operator []
  /// <example>
  /// <code>
  /// String str = "some string";
  /// str[0] = 'S'; // now str equals "Some string"
  /// </code>
  /// </example>
  /// <param name="index"> Character index </param>
  /// <returns> Reference to character at index</returns>
  char& operator[](size_t index);

  /// See example
  /// <example>
  /// <code>
  /// String str = "___some string___";
  /// str.RTrim('_'); // now str equals "___some string"
  /// </code>
  /// </example>
  /// <param name="symbol"> Symbol to trim </param>
  void RTrim(char symbol);

  /// See example
  /// <example>
  /// <code>
  /// String str = "___some string___";
  /// str.LTrim('_'); // now str equals "some string___"
  /// </code>
  /// </example>
  /// <param name="symbol"> Symbol to trim </param>
  void LTrim(char symbol);

  void swap(String& oth);

  friend std::ostream& operator<<(std::ostream&, const String&);

 private:
  char* Data;
};

/// Operator +
/// <example>
/// <code>
/// String a = "Hello";
/// String b = "World";
/// String c = a + b; // c equals "HelloWorld"
/// </code>
/// </example>
/// <returns>Returns string equal to a + b</returns>
String operator+(const String& a, const String& b);

/// Operator + for const char*
String operator+(const String& a, const char* b);
String operator+(const char* a, const String& b);

/// Operator *
String operator*(const String& a, unsigned int b);

/// Operator !=
bool operator!=(const String& a, const String& b);
bool operator!=(const String& a, const char* b);
bool operator!=(const char* a, const String& b);

/// Operator &gt;
bool operator>(const String& a, const String& b);
bool operator>(const String& a, const char* b);
bool operator>(const char* a, const String& b);

/// Operator == with const char*
bool operator==(const String& a, const char* b);
bool operator==(const char* a, const String& b);

/// Operator < with const char*
bool operator<(const String& a, const char* b);
bool operator<(const char* a, const String& b);

/// Output operator
/// <param name="out">Output stream</param>
/// <param name="str">String to output</param>
/// <returns>Returns reference to stream</returns>
std::ostream& operator<<(std::ostream& out, const String& str);



// Default constructor
String::String() : Data(nullptr) {
    Data = new char[1];
    Data[0] = '\0';
}

// User-defined constructor
String::String(const char* data) : Data(nullptr) {
    if (data == nullptr) {
        Data = new char[1];
        Data[0] = '\0';
    } else {
        size_t len = std::strlen(data);
        Data = new char[len + 1];
        std::strcpy(Data, data);
    }
}

// Copy constructor
String::String(const String& rhs) : Data(nullptr) {
    if (rhs.Data == nullptr) {
        Data = new char[1];
        Data[0] = '\0';
    } else {
        size_t len = std::strlen(rhs.Data);
        Data = new char[len + 1];
        std::strcpy(Data, rhs.Data);
    }
}

// Destructor
String::~String() {
    delete[] Data;
    Data = nullptr;
}

// Assignment operator
String& String::operator=(const String& rhs) {
    if (this != &rhs) {
        delete[] Data;

        if (rhs.Data == nullptr) {
            Data = new char[1];
            Data[0] = '\0';
        } else {
            size_t len = std::strlen(rhs.Data);
            Data = new char[len + 1];
            std::strcpy(Data, rhs.Data);
        }
    }
    return *this;
}

// Operator +=
String& String::operator+=(const String& rhs) {
    if (rhs.Data == nullptr) {
        return *this;
    }

    size_t old_len = Size();
    size_t rhs_len = rhs.Size();
    size_t new_len = old_len + rhs_len;

    char* new_data = new char[new_len + 1];

    if (Data != nullptr) {
        std::strcpy(new_data, Data);
    } else {
        new_data[0] = '\0';
    }

    std::strcat(new_data, rhs.Data);

    delete[] Data;
    Data = new_data;

    return *this;
}

// Operator *=
String& String::operator*=(unsigned int m) {
    if (m == 0 || Data == nullptr) {
        delete[] Data;
        Data = new char[1];
        Data[0] = '\0';
        return *this;
    }

    size_t old_len = Size();
    size_t new_len = old_len * m;

    char* new_data = new char[new_len + 1];
    new_data[0] = '\0';

    for (unsigned int i = 0; i < m; ++i) {
        std::strcat(new_data, Data);
    }

    delete[] Data;
    Data = new_data;

    return *this;
}

// Operator ==
bool String::operator==(const String& rhs) const {
    if (Data == nullptr && rhs.Data == nullptr) {
        return true;
    }
    if (Data == nullptr || rhs.Data == nullptr) {
        return false;
    }
    return std::strcmp(Data, rhs.Data) == 0;
}

// Operator <
bool String::operator<(const String& rhs) const {
    if (Data == nullptr && rhs.Data == nullptr) {
        return false;
    }
    if (Data == nullptr) {
        return true;
    }
    if (rhs.Data == nullptr) {
        return false;
    }
    return std::strcmp(Data, rhs.Data) < 0;
}

// Substring search function
size_t String::Find(const String& substr) const {
    if (Data == nullptr || substr.Data == nullptr) {
        return static_cast<size_t>(-1);
    }

    char* result = std::strstr(Data, substr.Data);
    if (result == nullptr) {
        return static_cast<size_t>(-1);
    }

    return result - Data;
}

// Character replacement function
void String::Replace(char oldSymbol, char newSymbol) {
    if (Data == nullptr) {
        return;
    }

    for (size_t i = 0; Data[i] != '\0'; ++i) {
        if (Data[i] == oldSymbol) {
            Data[i] = newSymbol;
        }
    }
}

// Returns string length
size_t String::Size() const {
    if (Data == nullptr) {
        return 0;
    }
    return std::strlen(Data);
}

// Checks if string is empty
bool String::Empty() const {
    return Size() == 0;
}

// Const operator []
char String::operator[](size_t index) const {
    if (Data == nullptr || index >= Size()) {
        return '\0';
    }
    return Data[index];
}

// Non-const operator []
char& String::operator[](size_t index) {
    static char dummy = '\0';
    if (Data == nullptr || index >= Size()) {
        return dummy;
    }
    return Data[index];
}

// Right trim
void String::RTrim(char symbol) {
    if (Data == nullptr) {
        return;
    }

    size_t len = Size();
    size_t new_len = len;

    while (new_len > 0 && Data[new_len - 1] == symbol) {
        new_len--;
    }

    if (new_len == len) {
        return;
    }

    char* new_data = new char[new_len + 1];
    std::strncpy(new_data, Data, new_len);
    new_data[new_len] = '\0';

    delete[] Data;
    Data = new_data;
}

// Left trim
void String::LTrim(char symbol) {
    if (Data == nullptr) {
        return;
    }

    size_t len = Size();
    size_t start = 0;

    while (start < len && Data[start] == symbol) {
        start++;
    }

    if (start == 0) {
        return;
    }

    size_t new_len = len - start;
    char* new_data = new char[new_len + 1];
    std::strcpy(new_data, Data + start);

    delete[] Data;
    Data = new_data;
}

void String::swap(String& oth) {
    std::swap(Data, oth.Data);
}

// ==================== GLOBAL OPERATORS ====================

// Operator +
String operator+(const String& a, const String& b) {
    String result(a);
    result += b;
    return result;
}

String operator+(const String& a, const char* b) {
    String result(a);
    result += String(b);
    return result;
}

String operator+(const char* a, const String& b) {
    String result(a);
    result += b;
    return result;
}

// Operator *
String operator*(const String& a, unsigned int b) {
    String result(a);
    result *= b;
    return result;
}

// Operator == with const char*
bool operator==(const String& a, const char* b) {
    return a == String(b);
}

bool operator==(const char* a, const String& b) {
    return String(a) == b;
}

// Operator !=
bool operator!=(const String& a, const String& b) {
    return !(a == b);
}

bool operator!=(const String& a, const char* b) {
    return !(a == b);
}

bool operator!=(const char* a, const String& b) {
    return !(a == b);
}

// Operator >
bool operator>(const String& a, const String& b) {
    return !(a < b) && !(a == b);
}

bool operator>(const String& a, const char* b) {
    return a > String(b);
}

bool operator>(const char* a, const String& b) {
    return String(a) > b;
}

// Operator < with const char*
bool operator<(const String& a, const char* b) {
    return a < String(b);
}

bool operator<(const char* a, const String& b) {
    return String(a) < b;
}

// Output operator
std::ostream& operator<<(std::ostream& out, const String& str) {
    if (str.Data != nullptr) {
        out << str.Data;
    }
    return out;
}

// ==================== DEMONSTRATION PROGRAM ====================

int main() {
    std::cout << "=== String Class Demonstration ===\n\n";

    // Testing constructors
    std::cout << "1. Constructors:\n";
    String empty;
    std::cout << "   Empty string: '" << empty << "' (length: " << empty.Size() << ")\n";

    String hello("Hello");
    std::cout << "   String from C-string: '" << hello << "' (length: " << hello.Size() << ")\n";

    String copy(hello);
    std::cout << "   Copy: '" << copy << "' (length: " << copy.Size() << ")\n";

    // Testing assignment operator
    std::cout << "\n2. Assignment operator:\n";
    String world("World");
    hello = world;
    std::cout << "   After hello = world: '" << hello << "'\n";
    std::cout << "   Self-assignment: ";
    hello = hello;
    std::cout << hello << " (should remain unchanged)\n";

    // Testing operator +=
    std::cout << "\n3. Operator +=:\n";
    String str1("Hello");
    String str2(" World");
    str1 += str2;
    std::cout << "   'Hello' += ' World' = '" << str1 << "'\n";
    str1 += "!";
    std::cout << "   'Hello World' += '!' = '" << str1 << "'\n";

    // Testing operator *
    std::cout << "\n4. Operator * and *=:\n";
    String str3("Ha");
    String str4 = str3 * 3;
    std::cout << "   'Ha' * 3 = '" << str4 << "'\n";
    str3 *= 4;
    std::cout << "   'Ha' *= 4 = '" << str3 << "'\n";

    // Testing comparison operators
    std::cout << "\n5. Comparison operators:\n";
    String a("Apple");
    String b("Banana");
    String c("Apple");

    std::cout << "   a = '" << a << "', b = '" << b << "', c = '" << c << "'\n";
    std::cout << "   a == c: " << (a == c ? "true" : "false") << "\n";
    std::cout << "   a != b: " << (a != b ? "true" : "false") << "\n";
    std::cout << "   a < b: " << (a < b ? "true" : "false") << "\n";
    std::cout << "   b > a: " << (b > a ? "true" : "false") << "\n";
    std::cout << "   a == \"Apple\": " << (a == "Apple" ? "true" : "false") << "\n";

    // Testing Find
    std::cout << "\n6. Substring search:\n";
    String text("Hello World");
    String sub1("World");
    String sub2("xyz");

    std::cout << "   In string '" << text << "' searching for '" << sub1 << "': position = "
              << text.Find(sub1) << "\n";
    std::cout << "   In string '" << text << "' searching for '" << sub2 << "': position = "
              << text.Find(sub2) << "\n";

    // Testing Replace
    std::cout << "\n7. Character replacement:\n";
    String replaceTest("Hello World");
    std::cout << "   Original: '" << replaceTest << "'\n";
    replaceTest.Replace('l', 'X');
    std::cout << "   After replacing 'l' with 'X': '" << replaceTest << "'\n";
    replaceTest.Replace('o', '0');
    std::cout << "   After replacing 'o' with '0': '" << replaceTest << "'\n";

    // Testing operator []
    std::cout << "\n8. Operator []:\n";
    String arrayTest("ABCDE");
    std::cout << "   String: '" << arrayTest << "'\n";
    std::cout << "   arrayTest[2] = '" << arrayTest[2] << "'\n";
    arrayTest[0] = 'Z';
    std::cout << "   After arrayTest[0] = 'Z': '" << arrayTest << "'\n";

    // Testing Trim
    std::cout << "\n9. Trim characters:\n";
    String trimTest("___Hello World___");
    std::cout << "   Original: '" << trimTest << "'\n";
    trimTest.LTrim('_');
    std::cout << "   After LTrim('_'): '" << trimTest << "'\n";
    trimTest.RTrim('_');
    std::cout << "   After RTrim('_'): '" << trimTest << "'\n";

    // Testing Empty
    std::cout << "\n10. Empty check:\n";
    String emptyStr;
    String nonEmptyStr("Text");
    std::cout << "   Empty string: " << (emptyStr.Empty() ? "empty" : "not empty") << "\n";
    std::cout << "   Non-empty string: " << (nonEmptyStr.Empty() ? "empty" : "not empty") << "\n";

    // Testing swap
    std::cout << "\n11. Swap content:\n";
    String swap1("First");
    String swap2("Second");
    std::cout << "   Before swap: swap1 = '" << swap1 << "', swap2 = '" << swap2 << "'\n";
    swap1.swap(swap2);
    std::cout << "   After swap: swap1 = '" << swap1 << "', swap2 = '" << swap2 << "'\n";

    // Testing operation chains
    std::cout << "\n12. Operation chains:\n";
    String chain1("A");
    String chain2("B");
    String chain3 = chain1 + chain2 + String("C");
    std::cout << "   'A' + 'B' + 'C' = '" << chain3 << "'\n";

    String chain4 = chain3 + "!" + String("!!");
    std::cout << "   Chain with const char*: '" << chain4 << "'\n";

    // Testing output operator
    std::cout << "\n13. Output operator:\n";
    std::cout << "   Output via cout: " << String("Works!") << std::endl;

    std::cout << "\n=== Demonstration completed ===\n";

    return 0;
}
