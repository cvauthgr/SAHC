#include <cstddef>
#include <bitset>
#include <cstdlib>
#include <print>
#include <string>

#include "esoteric.h"

//#define PRINT_DETAILS
//#define RUN_ALL

enum executionMethod
{
    leftToRight,
    rightToLeft,
    randomBitMutation,
};

template <std::size_t numbersOfRuns=100,std::size_t sizeOfBitString=8>
requires (numbersOfRuns >= 1 && sizeOfBitString >= 2)
class SAHC
{

private :

    std::bitset<sizeOfBitString> targetBitString = { } ;
    std::bitset<sizeOfBitString> currentBitString = { } ;
    std::size_t currentBitStringInverseHammingDistance { } ;
    bool targetFound = false ;
    
    void generateStarterBitString ()
    {
        int bitStringRandomPosition { } ;
        
        for(std::size_t index {0uz} ; index < sizeOfBitString ; index ++)
        {
            bitStringRandomPosition = prng::getInt(0,static_cast<int>(sizeOfBitString-1)) ;

            currentBitString.flip(bitStringRandomPosition);
        }

        #ifdef PRINT_DETAILS
        std::println("Pseudorandomly generated initial bit string : {}",currentBitString.to_string());
        #endif

        return ;   
    }

public :

    SAHC() = default ;
    ~SAHC() = default ;

    std::size_t targetCurrentInverseHammingDistance()
    {
        currentBitStringInverseHammingDistance = 0 ;
        
        for(std::size_t positionIndex { } ; positionIndex < sizeOfBitString ; positionIndex ++)
        {
            if(currentBitString[positionIndex] == targetBitString[positionIndex])
                currentBitStringInverseHammingDistance += 1 ;
        }

        return currentBitStringInverseHammingDistance ; 
    }

    void mutateCurrentBitStringRightToLeft()
    {
        currentBitStringInverseHammingDistance = targetCurrentInverseHammingDistance() ;

        #ifdef PRINT_DETAILS
        std::println("Inverse hamming distance of current bit string : {} ,against target : {} is Hamming distance : {}",currentBitString.to_string(),targetBitString.to_string(),currentBitStringInverseHammingDistance);
        #endif
        
        if(currentBitStringInverseHammingDistance == sizeOfBitString)
        {
            std::println("Target reached : {} == {}",currentBitString.to_string(),targetBitString.to_string()) ;
            targetFound = true ;
        }
        else if(currentBitStringInverseHammingDistance == 0)
        {
            #ifdef PRINT_DETAILS
            std::println("Current bit string is the opposite of target, flipping all current bit string bits...");
            #endif
            
            currentBitString.flip();
            
            std::println("Target matched : {} == {}",currentBitString.to_string(),targetBitString.to_string()) ;
            targetFound = true ;
        }

        static std::size_t positionIndex = 0 ;

        currentBitString.flip(positionIndex) ;

        std::size_t oldHammingDistance = currentBitStringInverseHammingDistance ;

        if(targetCurrentInverseHammingDistance() > oldHammingDistance)
        {
            if(positionIndex != (sizeOfBitString-1))
                positionIndex += 1 ;
            
            return ;
        }
        else
            currentBitString.flip(positionIndex) ;

        if(positionIndex == (sizeOfBitString -1))
            positionIndex = 0 ;

        if(positionIndex != (sizeOfBitString - 1))
            positionIndex += 1 ;
            
        return ;
    }

    void mutateCurrentBitStringLeftToRight()
    {
        currentBitStringInverseHammingDistance = targetCurrentInverseHammingDistance() ;

        #ifdef PRINT_DETAILS
        std::println("Inverse hamming distance of current bit string : {} ,against target : {} is Hamming distance : {}",currentBitString.to_string(),targetBitString.to_string(),currentBitStringInverseHammingDistance);
        #endif
        
        if(currentBitStringInverseHammingDistance == sizeOfBitString)
        {
            std::println("Target reached : {} == {}",currentBitString.to_string(),targetBitString.to_string()) ;
            targetFound = true ;
        }
        else if(currentBitStringInverseHammingDistance == 0)
        {
            #ifdef PRINT_DETAILS
            std::println("Current bit string is the opposite of target, flipping all current bit string bits...");
            #endif
            
            currentBitString.flip();
            
            std::println("Target matched : {} == {}",currentBitString.to_string(),targetBitString.to_string()) ;
            targetFound = true ;
        }

        static std::size_t positionIndex = sizeOfBitString - 1 ;

        #ifdef PRINT_DETAILS
        std::println("Current position index : {}",positionIndex);
        #endif

        std::println("First flip in function , value of positionIndex -> {}",positionIndex) ;
        currentBitString.flip(positionIndex) ;

        #ifdef PRINT_DETAILS
        std::println("Current bit string state : {}",currentBitString.to_string());
        #endif

        std::size_t oldInverseHammingDistance = currentBitStringInverseHammingDistance ;

        #ifdef PRINT_DETAILS
        std::println("Old inverse hamming distance : {}",oldInverseHammingDistance);
        #endif

        if(targetCurrentInverseHammingDistance() > oldInverseHammingDistance)
        {
            #ifdef PRINT_DETAILS
            std::println("New bit string better");
            #endif

            std::println("Position index , line 167 : {}",positionIndex);
            if(positionIndex != 0)
                positionIndex -= 1 ; //<- IT'S HERE RAAAAAAAAAAAAAA
            std::println("Position index , line 169 : {}",positionIndex);
            
            return;
        }
        else
        {
            #ifdef PRINT_DETAILS
            std::println("Old bit string better");
            #endif

            std::println("Old inverse hamming distance : {}",oldInverseHammingDistance);
            currentBitString.flip(positionIndex);
        }
        
        if(positionIndex == 0)
        {
            #ifdef PRINT_DETAILS
            std::println("Position index reset");
            #endif

            std::println("Position index , line 189 : {}",positionIndex);
            positionIndex = sizeOfBitString - 1 ; //<- Here
            std::println("Position index , line 191 : {}",positionIndex);

            #ifdef PRINT_DETAILS
            std::println("New position index : {}",positionIndex);
            #endif

            return ;
        }

        std::println("Position index , line 200 : {}",positionIndex);
        positionIndex -= 1 ; // <- Or here 
        std::println("Position index , line 202 : {}",positionIndex);
        
        return ;
    }

    void mutateRandomBit()
    {
        currentBitStringInverseHammingDistance = targetCurrentInverseHammingDistance() ;

        #ifdef PRINT_DETAILS
        std::println("Inverse hamming distance of current bit string : {} ,against target : {} is Hamming distance : {}",currentBitString.to_string(),targetBitString.to_string(),currentBitStringInverseHammingDistance);
        #endif
        
        if(currentBitStringInverseHammingDistance == sizeOfBitString)
        {
            std::println("Target reached : {} == {}",currentBitString.to_string(),targetBitString.to_string()) ;
            targetFound = true ;
        }
        else if(currentBitStringInverseHammingDistance == 0)
        {
            #ifdef PRINT_DETAILS
            std::println("Current bit string is the opposite of target, flipping all current bit string bits...");
            #endif
            
            currentBitString.flip();
            
            std::println("Target matched : {} == {}",currentBitString.to_string(),targetBitString.to_string()) ;
            targetFound = true ;
        }

        static std::size_t positionIndex {} ;

        positionIndex = prng::getInt(0,static_cast<int>(sizeOfBitString-1)) ;

        currentBitString.flip(positionIndex) ;

        std::size_t oldHammingDistance = currentBitStringInverseHammingDistance ;

        if(targetCurrentInverseHammingDistance() > oldHammingDistance)
        {
            return ;
        }
        else
            currentBitString.flip(positionIndex) ;
               
        return ;
    }

    void acquireTargetBitString(std::string bitString)
    {
        targetBitString = static_cast<std::bitset<sizeOfBitString>>(bitString) ;
        
        #ifdef PRINT_DETAILS
        std::println("Acquired target bit string : {}",targetBitString.to_string());
        #endif

        return ;
    }

    void initializeRun([[maybe_unused]] executionMethod method)
    {        
        generateStarterBitString() ;
        
        targetCurrentInverseHammingDistance() ;
        
        for(std::size_t executionCounter {0uz} ; executionCounter < numbersOfRuns ; executionCounter ++)
        {
            if(targetFound)
                goto EARLY_FINISH ;
            
            switch(method)
            {
                case executionMethod::leftToRight : mutateCurrentBitStringLeftToRight() ;
                break ;
                case executionMethod::rightToLeft : mutateCurrentBitStringRightToLeft() ;
                break ;
                case executionMethod::randomBitMutation : mutateRandomBit() ;
                break ;
                default : mutateCurrentBitStringLeftToRight() ;
            }
        
            #ifdef PRINT_DETAILS
            std::println("Current bit string : {} ,generation count : {}",currentBitString.to_string(),executionCounter+1);
            #endif
        }
        
        std::println("Hilltop evaluation concluded closest match to be : {}",currentBitString.to_string()) ;

        EARLY_FINISH :
            return ;
        
    }

};

int main()
{
    
    for(std::size_t Iteration_index = {0uz} ; Iteration_index <= 5 ; Iteration_index ++)
    {    
        SAHC<10,8> GAleftToRight { } ;

        std::println("LEFT TO RIGHT MUTATION");
    
        GAleftToRight.acquireTargetBitString("11110000") ;
        GAleftToRight.initializeRun(executionMethod::leftToRight);  

        SAHC<10,8> GArandom { } ;

        std::println("RANDOM BIT MUTATION");

        GArandom.acquireTargetBitString("11110000") ;
        GArandom.initializeRun(executionMethod::randomBitMutation);

        SAHC<10,8> GArightToLeft { } ;

        std::println("RIGHT TO LEFT MUTATION");

        GArightToLeft.acquireTargetBitString("11110000");            
        GArightToLeft.initializeRun(executionMethod::rightToLeft);
     }
    
    return 0;
}
