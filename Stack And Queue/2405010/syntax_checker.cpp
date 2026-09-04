#include <stack>
#include <string>
using namespace std;

/**
 * Helper function to check if an opening bracket matches a closing bracket
 * @param opening: The opening bracket character
 * @param closing: The closing bracket character
 * @return true if they form a matching pair, false otherwise
 */
bool isMatchingPair(char opening, char closing) {
    if((opening =='(' && closing ==')') || (opening =='{' && closing =='}') || (opening =='[' && closing ==']'))
    {
        return true;
    }
    else
    {
        // TODO: Implement this helper function
        // Check if opening and closing brackets match
        // Valid pairs: (), [], {}
        return false; // Replace this with your implementation
    }
}

/**
 * Checks if brackets in an arithmetic expression are properly matched
 * @param expression: A string containing an arithmetic expression
 * @return true if all brackets are properly matched and balanced, false otherwise
 */
bool isValidExpression(const string& expression) {
    stack<char>checker;
    // TODO: Implement the syntax checker using std::stack
    for(int i=0;i<expression.length();i++)
    {
        char bracket=expression[i];
        if(bracket=='(' || bracket=='{' || bracket=='[')
        {
            checker.push(bracket);
        }
        else if(bracket==')' || bracket=='}' || bracket==']')
        {
            if(checker.size()==0)
            {
                return false;
            }
            else if(isMatchingPair(checker.top(),bracket)==true)
            {
                checker.pop();
            }
            else if(isMatchingPair(checker.top(),bracket)==false)
            {
                return false;
            }        
        }
    }
    if(checker.size()==0)
    {
        return true;
    }
    else
    {
        return false;
    }
    //Replace this with your implementation
}
