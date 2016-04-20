//
//  utils.h
//  FinalRun
//
//  Created by Steven Hurtado, Aaron Bourque, Lahari Manchikanti, Renzo Rodriguez, and Kemley Nieva on 4/3/16.
//  Copyright © 2016 GroupCOP3503. All rights reserved.
//

#ifndef utils_h
#define utils_h


class Utils
{
public:
    //splits string txt anywhere a char ch is found
    //stores substring in vector strs
    //returns size of vector
    static unsigned int split(const std::string & txt, std::vector<std::string> &strs, char ch)
    {
        int pos = txt.find(ch);
        int initialPos = 0;
        
        strs.clear();
        
        while(pos != std::string::npos)
        {
            strs.push_back(txt.substr(initialPos, pos - initialPos + 1));
            initialPos = pos + 1;
            
            pos = txt.find(ch, initialPos);
        }
        
        strs.push_back(txt.substr(initialPos, std::min<int>(pos, txt.size() - (initialPos + 1))));
        
        return strs.size();
    }
};


#endif /* utils_h */
