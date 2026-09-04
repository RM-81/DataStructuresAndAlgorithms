#include <iostream>
#include <string>
#include <cassert>
using namespace std;

// Function prototype
bool isValidExpression(const string& expression);

// Test helper function
void runTest(const string& expression, bool expected, const string& testName) {
    bool result = isValidExpression(expression);
    if (result == expected) {
        cout << "[PASS] " << testName << endl;
    } else {
        cout << "[FAIL] " << testName << endl;
        cout << "       Expression: \"" << expression << "\"" << endl;
        cout << "       Expected: " << (expected ? "true" : "false") 
             << ", Got: " << (result ? "true" : "false") << endl;
    }
}

int main() {
    cout << "========================================" << endl;
    cout << "   Syntax Checker Test Suite" << endl;
    cout << "========================================" << endl;
    cout << endl;

    // Test 1: Basic Valid Cases
    cout << "Test Group 1: Basic Valid Cases" << endl;
    cout << "--------------------------------" << endl;
    runTest("()", true, "Test 1.1: Simple parentheses");
    runTest("[]", true, "Test 1.2: Simple square brackets");
    runTest("{}", true, "Test 1.3: Simple curly braces");
    runTest("()[]{}", true, "Test 1.4: Multiple bracket types");
    cout << endl;

    // Test 2: Nested Valid Cases
    cout << "Test Group 2: Nested Valid Cases" << endl;
    cout << "--------------------------------" << endl;
    runTest("{[]}", true, "Test 2.1: Nested brackets - type 1");
    runTest("{[()]}", true, "Test 2.2: Nested brackets - type 2");
    runTest("((()))", true, "Test 2.3: Multiple nested parentheses");
    runTest("[[[{}]]]", true, "Test 2.4: Deep nesting");
    runTest("()[]{}()", true, "Test 2.5: Sequential valid brackets");
    cout << endl;

    // Test 3: Valid Expressions with Content
    cout << "Test Group 3: Valid Expressions with Content" << endl;
    cout << "--------------------------------------------" << endl;
    runTest("(3 + 5) * 2", true, "Test 3.1: Simple arithmetic");
    runTest("[(2 + 3) * {4 - 1}]", true, "Test 3.2: Complex arithmetic");
    runTest("((a + b) * (c - d))", true, "Test 3.3: Variables with operators");
    runTest("{x + [y * (z - 5)]}", true, "Test 3.4: Mixed nested with content");
    runTest("func(arr[i], obj{key})", true, "Test 3.5: Function call syntax");
    cout << endl;

    // Test 4: Basic Invalid Cases
    cout << "Test Group 4: Basic Invalid Cases" << endl;
    cout << "----------------------------------" << endl;
    runTest("(", false, "Test 4.1: Single opening parenthesis");
    runTest(")", false, "Test 4.2: Single closing parenthesis");
    runTest("[", false, "Test 4.3: Single opening bracket");
    runTest("]", false, "Test 4.4: Single closing bracket");
    runTest("{", false, "Test 4.5: Single opening brace");
    runTest("}", false, "Test 4.6: Single closing brace");
    cout << endl;

    // Test 5: Mismatched Brackets
    cout << "Test Group 5: Mismatched Brackets" << endl;
    cout << "----------------------------------" << endl;
    runTest("(]", false, "Test 5.1: Parenthesis-bracket mismatch");
    runTest("[}", false, "Test 5.2: Bracket-brace mismatch");
    runTest("{)", false, "Test 5.3: Brace-parenthesis mismatch");
    runTest("(3 + 5]", false, "Test 5.4: Mismatch with content");
    runTest("[{(})]", false, "Test 5.5: Interleaved mismatch");
    cout << endl;

    // Test 6: Unbalanced Brackets
    cout << "Test Group 6: Unbalanced Brackets" << endl;
    cout << "----------------------------------" << endl;
    runTest("((3 + 5)", false, "Test 6.1: Missing closing parenthesis");
    runTest("(3 + 5))", false, "Test 6.2: Extra closing parenthesis");
    runTest("[(2 + 3)", false, "Test 6.3: Missing closing bracket");
    runTest("[(2 + 3])", false, "Test 6.4: Extra closing parenthesis");
    runTest("((a + b) * (c - d)]", false, "Test 6.5: Wrong closing bracket");
    runTest("{[(])}", false, "Test 6.6: Incorrect nesting order");
    cout << endl;

    // Test 7: Reverse Order Issues
    cout << "Test Group 7: Reverse Order Issues" << endl;
    cout << "-----------------------------------" << endl;
    runTest(")(", false, "Test 7.1: Reversed parentheses");
    runTest("][", false, "Test 7.2: Reversed brackets");
    runTest("}{", false, "Test 7.3: Reversed braces");
    runTest(")3 + 5(", false, "Test 7.4: Reversed with content");
    cout << endl;

    // Test 8: Edge Cases
    cout << "Test Group 8: Edge Cases" << endl;
    cout << "------------------------" << endl;
    runTest("", true, "Test 8.1: Empty string");
    runTest("2 + 3 * 4", true, "Test 8.2: No brackets");
    runTest("abc xyz 123", true, "Test 8.3: Only letters and numbers");
    runTest("+-*/", true, "Test 8.4: Only operators");
    runTest("   ", true, "Test 8.5: Only spaces");
    cout << endl;

    // Test 9: Complex Valid Cases
    cout << "Test Group 9: Complex Valid Cases" << endl;
    cout << "----------------------------------" << endl;
    runTest("(()())", true, "Test 9.1: Multiple pairs in sequence");
    runTest("{[()()]}", true, "Test 9.2: Nested sequential pairs");
    runTest("((((((((()))))))})", false, "Test 9.3: Deep nesting with mismatch");
    runTest("(((((((())))))))", true, "Test 9.4: Very deep valid nesting");
    runTest("{[({}[])]}", true, "Test 9.5: Complex nested structure");
    cout << endl;

    // Test 10: Real-World Examples
    cout << "Test Group 10: Real-World Examples" << endl;
    cout << "-----------------------------------" << endl;
    runTest("if (x > 0) { return arr[x]; }", true, "Test 10.1: If statement");
    runTest("for (int i = 0; i < n; i++) { sum += arr[i]; }", true, "Test 10.2: For loop");
    runTest("while (stack.empty()) { process(); }", true, "Test 10.3: While loop");
    runTest("function(param1, param2, arr[0])", true, "Test 10.4: Function call");
    runTest("{{nested}, [array]}", true, "Test 10.5: JSON-like structure");
    cout << endl;

    // Test 11: Stress Tests
    cout << "Test Group 11: Stress Tests" << endl;
    cout << "---------------------------" << endl;
    
    // Generate long valid expression
    string longValid = "";
    for (int i = 0; i < 100; i++) longValid += "(";
    for (int i = 0; i < 100; i++) longValid += ")";
    runTest(longValid, true, "Test 11.1: 100 nested parentheses");
    
    // Generate long invalid expression (missing one closing)
    string longInvalid = "";
    for (int i = 0; i < 100; i++) longInvalid += "(";
    for (int i = 0; i < 99; i++) longInvalid += ")";
    runTest(longInvalid, false, "Test 11.2: 100 opening, 99 closing");
    
    // Mixed long expression
    string mixedLong = "";
    for (int i = 0; i < 50; i++) mixedLong += "([{";
    for (int i = 0; i < 50; i++) mixedLong += "}])";
    runTest(mixedLong, true, "Test 11.3: 50 mixed nested brackets");
    
    cout << endl;
    cout << "========================================" << endl;
    cout << "   All Tests Completed!" << endl;
    cout << "========================================" << endl;

    return 0;
}
