#include "postfixCalc.hpp"
#include "LLStack.hpp"

unsigned postfixCalculator(const std::vector<std::string> & entries)
{
    LLStack<unsigned int> NewStack;

    if(entries.size() < 3)
    {
        if(entries.size() == 1)
        {
            if (entries[0] == "+" || entries[0] == "-" || entries[0] == "*" || entries[0] == "/")
            {
                throw CannotEvaluateException ("One element and operator");
            }
            else
            {
                unsigned int a = atoi(entries[0].c_str());
                NewStack.push(a);
            }
        }
        else
        {
            throw CannotEvaluateException ("Less element");
        }
    }
    else
    {
        for (size_t i = 0; i < entries.size(); i++) 
        {
            if (entries[i] == "+")
            {
                if(NewStack.size() < 2)
                {
                    throw CannotEvaluateException ("Stack is empty");
                }
                else
                {
                    unsigned int a = NewStack.top();
                    NewStack.pop();
                    unsigned int b = NewStack.top();
                    NewStack.pop();
                    unsigned int c = b + a;
                    NewStack.push(c);
                }
            }   
            else if (entries[i] == "-")
            {
                if(NewStack.size() < 2)
                {
                    throw CannotEvaluateException ("Stack is empty");
                }
                else
                {
                    unsigned int a = NewStack.top();
                    NewStack.pop();
                    unsigned int b = NewStack.top();
                    NewStack.pop();
                    unsigned int c = b - a;
                    NewStack.push(c);
                }
            }
            else if (entries[i] == "*")
            {
                if(NewStack.size() < 2)
                {
                    throw CannotEvaluateException ("Stack is empty");
                }
                else
                {
                    unsigned int a = NewStack.top();
                    NewStack.pop();
                    unsigned int b = NewStack.top();
                    NewStack.pop();
                    unsigned int c = b * a;
                    NewStack.push(c);
                }
            }
            else if (entries[i] == "/")
            {
                if(NewStack.size() < 2)
                {
                    throw CannotEvaluateException ("Stack is empty");
                }
                else
                {
                    unsigned int a = NewStack.top();
                    NewStack.pop();
                    unsigned int b = NewStack.top();
                    NewStack.pop();
                    unsigned int c = b / a;
                    NewStack.push(c);
                }
            }
            else
            {
                unsigned int a = atoi(entries[i].c_str());
                NewStack.push(a);
            }
        }
    }
    if(NewStack.size() != 1)
    {
        throw CannotEvaluateException ("Too many numbers in there");
    }
    return NewStack.top();
}
    

	

	 
