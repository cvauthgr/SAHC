#include <cstddef>
#include <bitset>
#include <cstdlib>
#include <print>
#include <string>

#include "esoteric.h"

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
    std::size_t stepsToGoal = 0 ;
    
    void generateStarterBitString ()
    {
        int bitStringRandomPosition { } ;
        
        for(std::size_t index {0uz} ; index < sizeOfBitString ; index ++)
        {
            bitStringRandomPosition = prng::getInt(0,static_cast<int>(sizeOfBitString-1)) ;

            currentBitString.flip(bitStringRandomPosition);
        }

        std::println("Pseudorandomly generated initial bit string : {}",currentBitString.to_string());

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
        if(targetFound)
            return;
        
        currentBitStringInverseHammingDistance = targetCurrentInverseHammingDistance() ;
        
        if(currentBitStringInverseHammingDistance == sizeOfBitString)
        {
            std::println("Target reached : {} == {}",currentBitString.to_string(),targetBitString.to_string()) ;
            std::println("Steps to goal : {}",stepsToGoal) ;
            targetFound = true ;
        }
        else if(currentBitStringInverseHammingDistance == 0)
        {
            std::println("Current bit string is the opposite of target, flipping all current bit string bits...");
            
            currentBitString.flip();
            
            std::println("Target matched : {} == {}",currentBitString.to_string(),targetBitString.to_string()) ;
            std::println("Steps to goal : 1") ;
            targetFound = true ;
        }

        static std::size_t positionIndex = 0 ;

        currentBitString.flip(positionIndex) ;

        stepsToGoal ++ ; //Practically not counting steps but independent calls to the mutation function 

        std::size_t oldHammingDistance = currentBitStringInverseHammingDistance ;

        if(targetCurrentInverseHammingDistance() > oldHammingDistance)
        {
            std::println("Found a better bit string -> {} | Step : {}",currentBitString.to_string(),stepsToGoal);
            
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
        if(targetFound)
            return;
        
        currentBitStringInverseHammingDistance = targetCurrentInverseHammingDistance() ;
        
        if(currentBitStringInverseHammingDistance == sizeOfBitString)
        {
            std::println("Target reached : {} == {}",currentBitString.to_string(),targetBitString.to_string()) ;
            std::println("Steps to goal : {}",stepsToGoal) ;
            targetFound = true ;
        }
        else if(currentBitStringInverseHammingDistance == 0)
        {
            std::println("Current bit string is the opposite of target, flipping all current bit string bits...");
            currentBitString.flip();
            
            std::println("Target matched : {} == {}",currentBitString.to_string(),targetBitString.to_string()) ;
            std::println("Steps to goal : 1") ;
            targetFound = true ;
        }

        static std::size_t positionIndex = sizeOfBitString - 1 ;
        
        currentBitString.flip(positionIndex) ;

        stepsToGoal ++ ;

        std::size_t oldInverseHammingDistance = currentBitStringInverseHammingDistance ;

        if(targetCurrentInverseHammingDistance() > oldInverseHammingDistance)
        {
            std::println("Found a better bit string -> {} | Step : {}",currentBitString.to_string(),stepsToGoal);            
            
            if(positionIndex != 0)
                positionIndex -= 1 ; 
            
            return;
        }
        else
        {
            currentBitString.flip(positionIndex);
        }
        
        if(positionIndex == 0)
        {
            positionIndex = sizeOfBitString - 1 ;

            return ;
        }

        positionIndex -= 1 ; 
        
        return ;
    }

    void mutateRandomBit()
    {
        if(targetFound)
            return;
        
        currentBitStringInverseHammingDistance = targetCurrentInverseHammingDistance() ;
        
        if(currentBitStringInverseHammingDistance == sizeOfBitString)
        {
            std::println("Target reached : {} == {}",currentBitString.to_string(),targetBitString.to_string()) ;
            std::println("Steps to goal : {}",stepsToGoal) ;
            targetFound = true ;
        }
        else if(currentBitStringInverseHammingDistance == 0)
        {
            std::println("Current bit string is the opposite of target, flipping all current bit string bits...");
            currentBitString.flip();
            
            std::println("Target matched : {} == {}",currentBitString.to_string(),targetBitString.to_string()) ;
            std::println("Steps to goal : 1") ;
            targetFound = true ;
        }

        static std::size_t positionIndex {} ;

        positionIndex = prng::getInt(0,static_cast<int>(sizeOfBitString-1)) ;

        currentBitString.flip(positionIndex) ;

        stepsToGoal ++ ;

        std::size_t oldHammingDistance = currentBitStringInverseHammingDistance ;

        if(targetCurrentInverseHammingDistance() > oldHammingDistance)
        {
            std::println("Found a better bit string -> {} | Step : {}",currentBitString.to_string(),stepsToGoal) ;            
            return ;
        }
        else
            currentBitString.flip(positionIndex) ;
               
        return ;
    }

    void acquireTargetBitString(std::string bitString)
    {
        targetBitString = static_cast<std::bitset<sizeOfBitString>>(bitString) ;
        
        std::println("Target : {}",targetBitString.to_string()) ;

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
    
        }
        
        std::println("Hilltop evaluation concluded closest match to be : {}",currentBitString.to_string()) ;
        std::println("Steps to goal : {}",stepsToGoal) ;

        EARLY_FINISH :
            return ;
        
    }

};

int main()
{
    
    for(std::size_t Iteration_index = {0uz} ; Iteration_index <= 10 ; Iteration_index ++)
    {    
        SAHC<10,8> GAleftToRight { } ;

        std::println("LEFT TO RIGHT MUTATION");
    
        GAleftToRight.acquireTargetBitString("11110000") ;
        GAleftToRight.initializeRun(executionMethod::leftToRight);  

        // SAHC<10,8> GArandom { } ;

        // std::println("RANDOM BIT MUTATION");

        // GArandom.acquireTargetBitString("11110000") ;
        // GArandom.initializeRun(executionMethod::randomBitMutation);

        // SAHC<10,8> GArightToLeft { } ;

        // std::println("RIGHT TO LEFT MUTATION");

        // GArightToLeft.acquireTargetBitString("11110000");            
        // GArightToLeft.initializeRun(executionMethod::rightToLeft);
     }
    
    return 0;
}
